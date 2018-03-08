#ifndef KHISTO_H
#define KHISTO_H

//custom headers
#include "KMap.h"
#include "KChecker.h"
#include "KFactory.h"
#include "KParser.h"
#include "KBase.h"

//ROOT headers
#include <TH1.h>
#include <TH2.h>
#include <TH1F.h>
#include <TProfile.h>

//STL headers
#include <vector>
#include <string>
#include <array>

using namespace std;

//---------------------------------------------------------------
//little class to store value & weight pairs for filling histos
class KValue {
	public:
		//constructor
		KValue() : values(0), weights(0) {}
		//accessors
		void Fill(double v, double w=1){
			values.push_back(v);
			weights.push_back(w);
		}
		double & GetValue(int iv) { return values[iv]; }
		double & GetWeight(int iw) { return weights[iw]; }
		int GetSize() { return values.size(); }
		
	protected:
		//member variables
		vector<double> values;
		vector<double> weights;
	
};

//forward declarations
class KMCWeightSelector;
class KFakeHLTSelector;
class KHisto;

//---------------------------------------------------------------
//base class for fillers - virtual methods, etc.
class KFiller : public KChecker {
	public:
		//constructors
		KFiller() : KChecker(), khtmp(0) {}
		KFiller(string name_, OptionMap* localOpt_, KHisto* khtmp_) : KChecker(name_, localOpt_), khtmp(khtmp_) {}
		
		//destructor
		virtual ~KFiller() {}
	
		//accessors
		virtual void Fill(KValue& value, double weight) {}
		//default mode for branch checking (useful if no special cases)
		virtual void CheckBranches(){
			ListBranches();
			for(const auto& branch : branches){
				looper->fChain->SetBranchStatus(branch.c_str(),1);
			}
		}
		virtual void ListBranches() {} //derived classes use this to fill branch list
		
	protected:
		//member variables
		KHisto* khtmp;
		vector<string> branches;
};
typedef KFactory<KFiller,string,OptionMap*,KHisto*> KFillerFactory;
#define REGISTER_FILLER(a) REGISTER_MACRO2(KFillerFactory,KFiller_##a,a)

//---------------------------------------------------------------
//extension of KFiller for per-jet histos (jet index, flattening)
//todo: allow different jet collections (not just AK8)?
class KJetFiller : public KFiller {
	public:
		//constructors
		KJetFiller() : KFiller() {}
		KJetFiller(string name_, OptionMap* localOpt_, KHisto* khtmp_, vector<unsigned> indices_) : KFiller(name_, localOpt_, khtmp_), indices(indices_) {}
		
		//destructor
		virtual ~KJetFiller() {}
	
		//accessors
		virtual void Fill(KValue& value, double weight){
			double w = weight;
			
			//loop over specified jets
			for(auto index : indices){
				double w = weight;
				w *= GetWeight(index);
				FillPerJet(value,w,index);
			}
		}
		virtual void FillPerJet(KValue& value, double weight, unsigned index) {}
		//defined below KHisto def (uses class method)
		virtual double GetWeight(unsigned index);
		
	protected:
		//member variables
		vector<unsigned> indices;	
};
typedef KFactory<KFiller,string,OptionMap*,KHisto*,vector<unsigned>> KJetFillerFactory;
#define REGISTER_JETFILLER(a) REGISTER_MACRO2(KJetFillerFactory,KJetFiller_##a,a)

//---------------------------------------------------------------
//class to store properties of histograms and associated fillers
class KHisto : public KChecker {
	public:
		//constructors
		KHisto() : KChecker(), isSpecial(false), MCWeight(0), FakeHLT(0) {}
		KHisto(string name_, OptionMap* localOpt_, TH1* htmp_, KBase* base_) : KChecker(name_, localOpt_), htmp(htmp_), isSpecial(false), MCWeight(0), FakeHLT(0) {
			vector<string> vars;
			if(!localOpt->Get("vars",vars)){
				//split up histo variables from name (if not otherwise specified)
				KParser::process(name,'_',vars);
			}
			
			//initialization - checkers
			SetSelection(base_->GetSelection());
			SetBase(base_);

			if(htmp){
				//make fillers
				vector<unsigned> indices;
				string vname2;
				for(const auto& var: vars){
					if(IsPerJet(var,vname2,indices)) fillers.push_back(KJetFillerFactory::GetFactory().construct(var,var,localOpt,this,indices));
					else fillers.push_back(KFillerFactory::GetFactory().construct(var,var,localOpt,this));
				}
				
				//finish initializing fillers
				CheckFillers();
			}
			//if htmp is null, assume it is a special histo
			else {
				htmp = GetSpecial();
				isSpecial = true;
			}
		}
		
		//destructor
		virtual ~KHisto() {}
		
		//accessors
		virtual TH1* GetHisto() { return htmp; }
		virtual void Fill(){
			if(fillers.empty()) return; //nothing to do
			
			//weights
			double w = GetWeight();
			
			vector<KValue> values(fillers.size());
			for(unsigned i = 0; i < fillers.size(); ++i){
				fillers[i]->Fill(values[i],w);
			}
			
			//now fill the histogram
			if(fillers.size()==1){
				for(int ix = 0; ix < values[0].GetSize(); ix++){
					htmp->Fill(values[0].GetValue(ix), values[0].GetWeight(ix));
				}
			}
			else if(fillers.size()==2){
				//need to cast in order to use Fill(x,y,w)
				//these three cases allow for various x vs. y comparisons: same # entries per event, or 1 vs. N per event
				if(values[0].GetSize()==values[1].GetSize()) {
					for(int i = 0; i < values[0].GetSize(); i++){
						if(htmp->GetDimension()==1)
							static_cast<TProfile*>(htmp)->Fill(values[0].GetValue(i), values[1].GetValue(i), values[0].GetWeight(i)); //pick the x weight by default
						else if(htmp->GetDimension()==2)
							static_cast<TH2*>(htmp)->Fill(values[0].GetValue(i), values[1].GetValue(i), values[0].GetWeight(i)); //pick the x weight by default
					}
				}
				else if(values[0].GetSize()==1){
					for(int iy = 0; iy < values[1].GetSize(); iy++){
						if(htmp->GetDimension()==1)
							static_cast<TProfile*>(htmp)->Fill(values[0].GetValue(0), values[1].GetValue(iy), values[1].GetWeight(iy));
						else if(htmp->GetDimension()==2)
							static_cast<TH2*>(htmp)->Fill(values[0].GetValue(0), values[1].GetValue(iy), values[1].GetWeight(iy));
					}
				}
				else if(values[1].GetSize()==1){
					for(int ix = 0; ix < values[0].GetSize(); ix++){
						if(htmp->GetDimension()==1)
							static_cast<TProfile*>(htmp)->Fill(values[0].GetValue(ix), values[1].GetValue(0), values[0].GetWeight(ix));
						else if(htmp->GetDimension()==2)
							static_cast<TH2*>(htmp)->Fill(values[0].GetValue(ix), values[1].GetValue(0), values[0].GetWeight(ix));
					}
				}
			}
			else { //no support for other # of vars
			}
		}
		//defined in K(Builder/Skimmer)Selectors.h to avoid circular dependency
		virtual double GetWeight();
		virtual double GetWeightPerJet(unsigned index);
		virtual void Finalize(){
			if(sel->GetGlobalOpt()->Get("plotoverflow",false)){
				if(fillers.size()==2) return; //not implemented for 2D histos or profiles yet
				
				//temporary histo to calculate error correctly when adding overflow bin to last bin
				TH1* otmp = (TH1*)htmp->Clone();
				otmp->Reset("ICEM");
				int ovbin = htmp->GetNbinsX()+1;
				double err = 0.;
				otmp->SetBinContent(ovbin-1,htmp->IntegralAndError(ovbin,ovbin,err));
				otmp->SetBinError(ovbin-1,err);
				
				//add overflow bin to last bin
				htmp->Add(otmp);
				
				//remove overflow bin from htmp (for consistent integral/yield)
				htmp->SetBinContent(ovbin,0);
				htmp->SetBinError(ovbin,0);
				
				delete otmp;
			}
		}
		
		//common checkers
		virtual void CheckDeps(){
			MCWeight = sel->Get<KMCWeightSelector*>("MCWeight");
			FakeHLT = sel->Get<KFakeHLTSelector*>("FakeHLT");
		}
		virtual void CheckBase(){
			//do not use MCWeight with data
			if(base->IsData()) MCWeight = NULL;
		}
		//checkers for fillers
		virtual void CheckFillers() {
			for(auto filler : fillers){
				filler->SetSelection(sel);
				filler->SetBase(base);
			}
		}
		
		//helpers
		bool IsPerJet(const string& vname, string& vname2, vector<unsigned>& indices){
			if(vname.compare(0,10,"leadjetAK8")==0) {
				indices = {0};
				vname2 = vname.substr(10,string::npos);
			}
			else if(vname.compare(0,13,"subleadjetAK8")==0){
				indices = {1};
				vname2 = vname.substr(13,string::npos);
			}
			else if(vname.compare(0,10,"bothjetAK8")==0) {
				indices = {0,1};
				vname2 = vname.substr(10,string::npos);
			}
			else if(vname.compare(0,11,"thirdjetAK8")==0) {
				indices = {2};
				vname2 = vname.substr(11,string::npos);
			}
			else if(vname.compare(0,12,"fourthjetAK8")==0) {
				indices = {3};
				vname2 = vname.substr(12,string::npos);
			}
			else {
				indices.clear();
				vname2 = "";
			}
			return (!indices.empty());
		}
		
		//deal with special histos
		static bool IsSpecial(const string& s){
			static const array<string,3> specials{"cutflowRaw","cutflowAbs","cutflowRel"};
			for(const auto& special: specials){
				if(s==special) return true;
			}
			return false;
		}
		bool IsSpecial() { return isSpecial; }
		TH1* GetSpecial() {
			if(stmp=="cutflowRaw") return base->GetCutflow(KCutflow::CutRaw);
			else if(stmp=="cutflowAbs") return base->GetCutflow(KCutflow::CutAbs);
			else if(stmp=="cutflowRel") return base->GetCutflow(KCutflow::CutRel);
			else return NULL;
		}

		//member variables needed by fillers
		KMCWeightSelector* MCWeight;
		KFakeHLTSelector* FakeHLT;
		
	protected:
		//member variables
		string stmp;
		TH1* htmp;
		bool isSpecial;
		vector<KFiller*> fillers;
};

double KJetFiller::GetWeight(unsigned index){
	return khtmp->GetWeightPerJet(index);
}

//avoid circular dependency
//add a blank histo for future building
TH1* KBase::AddHisto(string s, TH1* h, OptionMap* omap){
	//avoid re-adding
	if(!GetHisto(s)){
		stmp = s;
		khtmp = NULL;
		if(h){
			htmp = (TH1*)h->Clone();
			htmp->Sumw2();					
		}
		//KHisto will generate special histo automatically (if h==NULL)
		//but don't make KHisto if no omap provided
		if(omap) khtmp = new KHisto(s,omap,h,this);
		if(!htmp and khtmp) htmp = khtmp->GetHisto();
		MyHistos.Add(stmp,htmp);
		if(khtmp) MyKHistos.Add(stmp,khtmp);
	}
	return htmp;
}
//in case of normalization to yield or other scaling
void KBase::Normalize(double nn, bool toYield){
	if(khtmp->IsSpecial()) return;
	double simyield = htmp->GetDimension()==2 ? ((TH2*)htmp)->Integral(0,htmp->GetNbinsX()+1,0,htmp->GetNbinsY()+1) : htmp->Integral(0,htmp->GetNbinsX()+1);
	if(toYield) htmp->Scale(nn/simyield);
	else htmp->Scale(nn);
}
#endif