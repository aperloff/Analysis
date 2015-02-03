#ifndef KSET_H
#define KSET_H

//custom headers
#include "KMap.h"
#include "KBase.h"
#include "KBuilder.h"
#include "KLegend.h"

//ROOT headers
#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <THStack.h>

//STL headers
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//------------------------------------------------------------------------------------------
//set class: has children and a parent (KBase or KBase-derived)
//           inherits from KBase to allow for sets of sets
//           default value for color
class KSet : public KBase {
	public:
		//constructor
		KSet() : KBase() { localOpt->Set<Color_t>("color",kBlack); }
		KSet(string name_, OptionMap* localOpt_, OptionMap* globalOpt_) : KBase(name_, localOpt_, globalOpt_) {
			if(!localOpt->Has("color")) localOpt->Set<Color_t>("color",kBlack);
		}
		//destructor
		virtual ~KSet() {}
		
		virtual void AddChild(KBase* ch){
			children.push_back(ch);
			//cout << this->name << " added child " << children[children.size()-1]->GetName() << endl;
			ch->SetParent(this);
		}
		vector<KBase*>& GetChildren() { return children; }
		KBase* GetParent() { return parent; }
		void SetParent(KBase* p) { parent = p; }
		//default build for sets
		virtual void Build(){
			//first, all children build
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->Build();
			}
			//then loop to add up histos (only resetting current histo for children once)
			HMit sit;
			for(sit = MyHistos.GetTable().begin(); sit != MyHistos.GetTable().end(); sit++){
				GetHisto(sit->first); //this will propagate to children
				for(unsigned c = 0; c < children.size(); c++){ //include option to subtract histos, off by default
					htmp->Add(children[c]->GetHisto(), children[c]->GetLocalOpt()->Get("subtract",false) ? -1 : 1);				
				}
			}
		}
		//resetting current histo propagates to children for consistency
		virtual TH1* GetHisto(string hname){
			TH1* hist = MyHistos.Get(hname);
			etmp = MyErrorBands.Get(hname); //it's okay for etmp to be null
			if(hist) {
				stmp = hname;
				htmp = hist;
				for(unsigned c = 0; c < children.size(); c++){
					children[c]->GetHisto(hname); //ignore returned pointer
				}
				return htmp;
			}
			else return NULL; //do not reset if the histo does not exist
		}
		//provides size of entries for the legend
		virtual void GetLegendInfo(KLegend* kleg) { kleg->CheckSize(name); }
		virtual void CloseFile(){
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->CloseFile();
			}
		}
		//divide current histo by bin width, set implementation
		virtual void BinDivide(){
			KBase::BinDivide();
		
			//scale children for consistency
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->BinDivide();
			}
		}
		
	protected:
		//member variables
		KBase* parent; //overloaded variable name
		vector<KBase*> children;
};

//------------------------------
//specialization for data histos
class KSetData: public KSet {
	public:
		//constructor
		KSetData() : KSet() {}
		KSetData(string name_, OptionMap* localOpt_, OptionMap* globalOpt_) : KSet(name_, localOpt_, globalOpt_) {}
		//destructor
		virtual ~KSetData() {}
		
		//sum up lumi when adding children
		void AddChild(KBase* ch){
			KSet::AddChild(ch);
			double intlumi, intlumi_ch;
			intlumi = intlumi_ch = 0;
			if(ch->GetLocalOpt()->Get("intlumi",intlumi_ch)) {
				localOpt->Get("intlumi",intlumi);
				localOpt->Set("intlumi",intlumi + intlumi_ch);
			}
		}	
		//add function - does formatting
		TH1* AddHisto(string s, TH1* h){
			KBase::AddHisto(s,h);
			
			//add to children
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->AddHisto(s,h);
			}
			
			Color_t color;
			localOpt->Get("color",color);
			//formatting
			htmp->SetLineColor(color);
			htmp->SetMarkerColor(color);
			htmp->SetFillColor(0);
			htmp->SetMarkerStyle(20);
			
			return htmp;
		}
		//adds histo to legend
		void AddToLegend(TLegend* leg) {
			//only draw horizontal line if horizontal error bar is enabled
			if(globalOpt->Get("horizerrbars",false) || htmp->GetXaxis()->IsVariableBinSize()){
				leg->AddEntry(htmp,name.c_str(),"pel");
			}
			//note: this setting only works in ROOT 5.34.11+
			else leg->AddEntry(htmp,name.c_str(),"pe");
		}
		//draw function
		void Draw(TPad* pad) {
			pad->cd();
			htmp->Draw("PE same");
		}
		
};

//------------------------------
//specialization for MC histos
class KSetMC: public KSet {
	public:
		//constructor
		KSetMC() : KSet() {}
		KSetMC(string name_, OptionMap* localOpt_, OptionMap* globalOpt_) : KSet(name_, localOpt_, globalOpt_) {}
		//destructor
		virtual ~KSetMC() {}

		//build for MC sets
		virtual void Build(){
			//first, all children build
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->Build();
			}
			//then loop to add up histos (only resetting current histo for children once)
			HMit sit;
			for(sit = MyHistos.GetTable().begin(); sit != MyHistos.GetTable().end(); sit++){
				GetHisto(sit->first); //this will propagate to children
				for(unsigned c = 0; c < children.size(); c++){ //include option to subtract histos
					htmp->Add(children[c]->GetHisto(), children[c]->GetLocalOpt()->Get("subtract",false) ? -1 : 1);
				}
				
				//use alternative data-driven normalizations (fake tau, real ttbar) if everything is enabled
				double simerr = 0;
				double simyield = htmp->IntegralAndError(0,htmp->GetNbinsX()+1,simerr);
				double norm = 0;
				double normerr = 0;
				bool do_err_prop = false;
				TH1* htmp2 = 0;
				string normtype = "";
				if(localOpt->Get("normtype",normtype) && normtype=="faketau" && globalOpt->Get("dofaketau",false) && globalOpt->Get<double>("faketaunorm",norm)){
					if(globalOpt->Get<double>("faketauerr",normerr)) {
						do_err_prop = true;
						htmp2 = (TH1*)htmp->Clone();
					}
					htmp->Scale(norm/simyield);
				}
				else if(localOpt->Get("normtype",normtype) && normtype=="ttbar" && globalOpt->Get("dottbar",false) && globalOpt->Get<double>("ttbarnorm",norm)){
					if(globalOpt->Get<double>("ttbarerr",normerr)) {
						do_err_prop = true;
						htmp2 = (TH1*)htmp->Clone();
					}
					htmp->Scale(norm/simyield);
				}
				//don't bother scaling child histos...
				
				//replace bin errors using error propagation:
				//B' = B*C/I = B*C/(A+B)
				if(do_err_prop){
					for(int i = 1; i <= htmp->GetNbinsX()+1; i++){
						double sBn = 0;
						double B = htmp2->GetBinContent(i);
						double sB = htmp2->GetBinError(i);
						double I = simyield;
						double A = I - B;
						double sA = sqrt(simerr*simerr - sB*sB);
						double C = norm;
						double sC = normerr;
						
						sBn = 1./I*sqrt( A*A*C*C/(I*I)*sB*sB + B*B*C*C/(I*I)*sA*sA + B*B*sC*sC );
						htmp->SetBinError(i,sBn);
					}
					delete htmp2; htmp2 = 0;
				}
			}
		}		
		//add function - does formatting
		TH1* AddHisto(string s, TH1* h){
			KBase::AddHisto(s,h);
			
			//add to children
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->AddHisto(s,h);
			}
			
			Color_t color;
			localOpt->Get("color",color);
			//formatting
			htmp->SetFillColor(0);
			htmp->SetLineColor(color);
			htmp->SetMarkerColor(color);
			htmp->SetLineStyle(1);
			htmp->SetLineWidth(2);
			
			return htmp;
		}
		//adds histo to legend
		void AddToLegend(TLegend* leg) {
			leg->AddEntry(htmp,name.c_str(),"l");
		}
		//draw function
		void Draw(TPad* pad) {
			pad->cd();
			htmp->Draw("hist same");
		}
		
};

//----------------------------
//specialization for MC stacks
class KSetMCStack : public KSet {
	public:
		//constructor
		KSetMCStack() : KSet() {}
		KSetMCStack(string name_, OptionMap* localOpt_, OptionMap* globalOpt_) : KSet(name_, localOpt_, globalOpt_), shtmp(0) {}
		//destructor
		virtual ~KSetMCStack() {}

		//polymorphic add function for stacks (does formatting)
		TH1* AddHisto(string s, TH1* h){
			stmp = s;
			shtmp = new THStack(stmp.c_str(),stmp.c_str());
			MyStacks.Add(stmp,shtmp);
			
			//add to children
			for(unsigned c = 0; c < children.size(); c++){
				TH1* ctmp = children[c]->AddHisto(s,h);
				//fix formatting of ctmp for stack
				Color_t color;
				children[c]->GetLocalOpt()->Get("color",color);
				ctmp->SetFillColor(color);
				ctmp->SetLineColor(color);
				ctmp->SetMarkerColor(color);
				ctmp->SetLineWidth(1);
				string sigstack = "";
				if(globalOpt->Get("sigstack",sigstack) && children[c]->GetName()==sigstack){
					ctmp->SetFillColor(kWhite);
					ctmp->SetLineColor(kBlack);
					ctmp->SetMarkerColor(kBlack);
					ctmp->SetLineWidth(3);
				}
			}
			
			return NULL; //no histo yet, pointless return value
		}
		
		//polymorphic build for stacks
		void Build(){
			//first, all children build
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->Build();
			}
			
			//then loop to add up histos (only resetting current histo for children once)
			SMit sit;
			for(sit = MyStacks.GetTable().begin(); sit != MyStacks.GetTable().end(); sit++){
				GetHisto(sit->first); //this will propagate to children
				
				//sort vector of children according to current histo - BEFORE adding to stack
				//unless disabled by user
				if(!globalOpt->Get("nosort",false)) sort(children.begin(),children.end(),KComp());
				
				string sigstack = "";
				bool do_sigstack = globalOpt->Get("sigstack",sigstack);
				int c_sigstack = -1;
				for(unsigned c = 0; c < children.size(); c++){
					if(do_sigstack && children[c]->GetName()==sigstack) c_sigstack = c; //do not add stacked signal yet, just store index
					else shtmp->Add(children[c]->GetHisto());
				}
				
				//fill in htmp now that shtmp is built
				htmp = (TH1*)shtmp->GetStack()->Last();
				//build error band, enabled by default
				if(globalOpt->Get("errband",true)) BuildErrorBand();
				
				//add stacked signal histo after calculating error band
				if(c_sigstack > -1) shtmp->Add(children[c_sigstack]->GetHisto());				
			}
		}
		//polymorphic GetHisto for stacks
		TH1* GetHisto(string hname) {
			THStack* stk = MyStacks.Get(hname);
			etmp = MyErrorBands.Get(hname); //it's okay for etmp to be null
			if(stk) {
				stmp = hname;
				shtmp = stk;
				if(shtmp->GetStack()) htmp = (TH1*)shtmp->GetStack()->Last();
				else htmp = NULL; //might have a THStack but no GetStack during the histo building process
				for(unsigned c = 0; c < children.size(); c++){
					children[c]->GetHisto(hname); //ignore returned pointer
				}
				return htmp;
			}
			else return NULL; //do not reset if the histo does not exist
		}
		//provides size of entries for the legend
		void GetLegendInfo(KLegend* kleg) {
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->GetLegendInfo(kleg);
			}
			if(globalOpt->Get("errband",true)) kleg->CheckSize("uncertainty");
		}
		//adds child histos to legend
		void AddToLegend(TLegend* leg) {
			//sort vector of children according to current histo - BEFORE adding to legend
			if(!globalOpt->Get("nosort",false)) sort(children.begin(),children.end(),KComp());	
		
			//add to legend in reverse order so largest is first
			for(int c = children.size()-1; c >= 0; c--){
				TH1* ctmp = children[c]->GetHisto();
				string cname = children[c]->GetName();
				leg->AddEntry(ctmp,cname.c_str(),"f");
			}
			//error band enabled by default
			if(globalOpt->Get("errband",true)) leg->AddEntry(etmp,"uncertainty","f");
			//this assumes it has already been created previously... a little unsafe, but a pain in the ass otherwise
		}
		//draw function
		void Draw(TPad* pad) {
			pad->cd();
			shtmp->Draw("hist same");
			
			//error band enabled by default
			if(globalOpt->Get("errband",true)) etmp->Draw("2 same");
			
			if(globalOpt->Get("bgline",false)&&htmp){
				TH1* hoverlay = (TH1*)htmp->Clone();
				hoverlay->SetFillColor(0);
				hoverlay->SetLineColor(kBlack);
				hoverlay->SetMarkerColor(kBlack);
				hoverlay->SetLineStyle(1);
				hoverlay->SetLineWidth(2);
				hoverlay->Draw("hist same");
			}
		}
		//normalize all children histos
		void Normalize(double nn, bool toYield=true){
			double simyield = htmp->Integral(0,htmp->GetNbinsX()+1); //yield of summed histo
			
			//scale stack histos
			TObjArray* stack_array = shtmp->GetStack();
			for(unsigned s = 0; s < stack_array->GetSize(); s++){
				TH1* hist = (TH1*)stack_array->At(s);
				if(hist) hist->Scale(nn/simyield);
			}
			
			//scale children (directly to overall yield)
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->Normalize(nn/simyield,false);
			}
			
			//rebuild error band (enabled by default)
			if(globalOpt->Get("errband",true)) BuildErrorBand();
		}
		//divide current histo by bin width, stack implementation
		void BinDivide(){
			//scale stack histos
			TObjArray* stack_array = shtmp->GetStack();
			for(unsigned s = 0; s < stack_array->GetSize(); s++){
				TH1* hist = (TH1*)stack_array->At(s);
				for(int b = 1; b <= htmp->GetNbinsX(); b++){
					hist->SetBinContent(b,hist->GetBinContent(b)/hist->GetBinWidth(b));
					hist->SetBinError(b,hist->GetBinError(b)/hist->GetBinWidth(b));
				}
			}
		
			//scale children for consistency
			for(unsigned c = 0; c < children.size(); c++){
				children[c]->BinDivide();
			}
			
			//rebuild error band (enabled by default)
			if(globalOpt->Get("errband",true)) BuildErrorBand();
		}
		//print yield from children
		void PrintYield() { 
			KBase::PrintYield();
			//reverse order so largest will print first
			for(int c = children.size()-1; c >= 0; c--){
				cout << "    "; //indent children
				children[c]->PrintYield();
			}
		}
		//check special status for children also
		KBase* CheckSpecial(string special){
			if(name==special) return (KBase*)this;
			for(unsigned c = 0; c < children.size(); c++){
				if(children[c]->GetName()==special) return children[c];
			}
			return NULL;
		}
		
	protected:
		//new stack-based member variables
		THStack* shtmp;
		StackMap MyStacks;
};

//-------------------------
//specialization for ratios
class KSetRatio: public KSet {
	public:
		//constructor
		KSetRatio() : KSet() {}
		KSetRatio(OptionMap* localOpt_, OptionMap* globalOpt_) : KSet("ratio", localOpt_, globalOpt_) { 
			localOpt->Set<Color_t>("color",kBlack);
			children.resize(2); 
		}
		//destructor
		virtual ~KSetRatio() {}
		
		//first child is numerator, second child is denominator
		void AddNumerator(KBase* numer){ children[0] = numer; }
		void AddDenominator(KBase* denom){ children[1] = denom; }
		
		//ratio class acts a little differently:
		//only builds from the current histo of numer and denom
		//(since some histos might not want ratios, and also has to wait for possible norm to yield)
		void Build(TH1* hrat_){
			stmp = children[0]->GetHistoName();
			TH1* hrat = (TH1*)hrat_->Clone();
			TH1* hdata = children[0]->GetHisto();
			TH1* hsim = children[1]->GetHisto();
			TH1* hsim0 = (TH1*)hsim->Clone();
			
			if(hrat->GetDimension()==1){ //data/mc
				//remove sim bin errors
				for(int b = 0; b <= hsim0->GetEntries(); b++){
					hsim0->SetBinError(b,0);
				}
				
				hrat->Divide(hdata,hsim0);
				Color_t color;
				localOpt->Get("color",color);
				//formatting
				hrat->SetLineColor(color);
				hrat->SetMarkerColor(color);
				hrat->SetMarkerStyle(20);
			}
			else if(hrat->GetDimension()==2){//(data-mc)/err
				hrat->Add(hdata,hsim,1,-1);
				for(int b = 0; b <= hrat->GetEntries(); b++){
					hrat->SetBinContent(b,hrat->GetBinContent(b)/hrat->GetBinError(b));
					hrat->SetBinError(b,0);
				}
			}
			
			htmp = hrat;
			MyHistos.Add(stmp,htmp);
			
			//error band enabled by default
			if(globalOpt->Get("errband",true)) BuildErrorBand();
		}
		//calculate ratio error band from denom
		TGraphAsymmErrors* BuildErrorBand(){
			TH1* hdata = children[0]->GetHisto();
			TH1* hsim = children[1]->GetHisto();
		
			//make sim error band
			TGraphAsymmErrors* erat = new TGraphAsymmErrors(htmp->GetNbinsX()+2); //under- and overflow
			for(int b = 0; b < erat->GetN(); b++){
				if(htmp->GetBinContent(b)>0){
					erat->SetPoint(b,htmp->GetBinCenter(b),1); //hypothesis: numer/denom = 1
					double width = htmp->GetBinWidth(b);
					erat->SetPointEXlow(b, width/2.);
					erat->SetPointEXhigh(b, width/2.);
					//y widths use error propagation for f = data/mc : sigma_f = sigma_mc*data/mc^2
					//(taking sigma_data = 0, since included in ratio point error bars)
					erat->SetPointEYlow(b, hsim->GetBinError(b)*hdata->GetBinContent(b)/(hsim->GetBinContent(b)*hsim->GetBinContent(b)));
					erat->SetPointEYhigh(b, hsim->GetBinError(b)*hdata->GetBinContent(b)/(hsim->GetBinContent(b)*hsim->GetBinContent(b)));
				}
			}
			erat->SetFillColor(kGray+1);
			erat->SetFillStyle(3013);
			
			MyErrorBands.Add(stmp,erat);
			etmp = erat;
			return erat;
		}
		
		//draw function
		void Draw(TPad* pad) {
			pad->cd();
			//error band enabled by default
			if(globalOpt->Get("errband",true)) etmp->Draw("2 same");
			htmp->Draw("PE same");
		}
		
};

#endif