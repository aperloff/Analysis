#ifndef KCOMMONSELECTORS_H
#define KCOMMONSELECTORS_H

//custom headers
#include "KSelection.h"

//ROOT headers
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>

//STL headers
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//----------------------------------------------------
//selects events based on HLT line
class KHLTSelector : public KSelector {
	public:
		//constructor
		KHLTSelector() : KSelector() { }
		KHLTSelector(string name_, OptionMap* localOpt_) : KSelector(name_,localOpt_) { 
			//get selected line from options
			localOpt->Get("HLTLines",HLTLines);
			debug = localOpt->Get("debug",false);
		}
		virtual void CheckBranches(){
			looper->fChain->SetBranchStatus("TriggerNames",1);
			looper->fChain->SetBranchStatus("TriggerPass",1);
		}
		
		//this selector doesn't add anything to tree
		
		//used for non-dummy selectors
		virtual bool Cut() {
			//skip if no line provided
			if(HLTLines.size()==0) return true;
			
			//initial loop over trigger names to find indices (position is consistent for all events)
			if(HLTIndices.empty()){
				for(unsigned h = 0; h < HLTLines.size(); h++){
					vector<string>::iterator lb = lower_bound(looper->TriggerNames->begin(),looper->TriggerNames->end(),HLTLines[h]);
					if(debug){
						cout << HLTLines[h] << " " << *lb << endl;
					}
					if(lb != looper->TriggerNames->end() && lb->find(HLTLines[h]) != std::string::npos){
						HLTIndices.push_back(distance(looper->TriggerNames->begin(),lb));
					}
				}
				if(debug){
					for(unsigned h = 0; h < HLTIndices.size(); h++){
						cout << HLTLines[h] << ": " << HLTIndices[h] << endl;
					}
				}
			}
			
			//loop over trigger names
			bool goodTrigger = false;
			for(unsigned h = 0; h < HLTIndices.size(); h++){
				unsigned index = HLTIndices[h];
				//check:
				//1) if the decision was true (the line fired)
				//2) if the line was not prescaled (currently ignored)
				if(looper->TriggerPass->at(index)==1) {
					goodTrigger = true;
					break;
				}
			}
			//skip event if finished searching and no HLT lines found
			return goodTrigger;
		}
		
		//member variables
		vector<string> HLTLines;
		vector<unsigned> HLTIndices;
		bool debug;
};
REGISTER_SELECTOR(HLT);

//----------------------------------------------------
//selects events based on HT value
class KHTSelector : public KSelector {
	public:
		//constructor
		KHTSelector() : KSelector() { }
		KHTSelector(string name_, OptionMap* localOpt_) : KSelector(name_,localOpt_), HTmin(500) { 
			//check for option
			localOpt->Get("HTmin",HTmin);
			doGen = localOpt->Get("gen",false);
		}
		virtual void CheckBranches(){
			looper->fChain->SetBranchStatus("HT",1);
			if(doGen) looper->fChain->SetBranchStatus("GenHT",1);
		}
		
		//this selector doesn't add anything to tree
		
		//used for non-dummy selectors
		virtual bool Cut() {
			if(doGen) return looper->GenHT > HTmin;
			else return looper->HT > HTmin;
		}
		
		//member variables
		double HTmin;
		bool doGen;
};
REGISTER_SELECTOR(HT);

//----------------------------------------------------
//selects events based on a cut along the HT/DeltaPhi plane
class KHTRatioSelector : public KSelector {
	public:
		//constructor
		KHTRatioSelector() : KSelector() { }
		KHTRatioSelector(string name_, OptionMap* localOpt_) : KSelector(name_,localOpt_) { 
			//check for option
            doHTDPhiCut = localOpt->Get("HTDPhi",false);
		}
		virtual void CheckBranches(){
			looper->fChain->SetBranchStatus("HT",1);
			looper->fChain->SetBranchStatus("HT5",1);
			if(doHTDPhiCut) looper->fChain->SetBranchStatus("DeltaPhi1",1);
		}

		//this selector doesn't add anything to tree

		//used for non-dummy selectors
		virtual bool Cut() {
			//cout << "HTDPhiCutOn=" << doHTDPhiCut << " HT=" << looper->HT << " HT5="
			//	 << looper->HT5 << " DeltaPhi1=" << looper->DeltaPhi1 << " Decision="
			//	 << (looper->DeltaPhi1 > ((1.025*looper->HT5/looper->HT)-0.5875)) << endl;
            //line slope from: https://indico.cern.ch/event/769759/contributions/3198262/attachments/1744238/2823253/HT5_noisyForwardJets.pdf
            //x1 = 1.5 y1 = 0.95
            //x2 = 3.5 y2 = 3.0
            //slope = (3-0.95)/(3.5-1.5) = 1.025
            //y = mx + b == > 0.95 = 1.025 *1.5 + b == > b = -0.5875            
            if(doHTDPhiCut) return looper->DeltaPhi1 >= ((1.025*looper->HT5/looper->HT)-0.5875);
            else return looper->HT5/looper->HT <= 2.0;
		}

		//member variables;
		bool doHTDPhiCut;
};
REGISTER_SELECTOR(HTRatio);

//----------------------------------------------------
//selects events based on MHT value
class KMHTSelector : public KSelector {
	public:
		//constructor
		KMHTSelector() : KSelector() { }
		KMHTSelector(string name_, OptionMap* localOpt_) : KSelector(name_,localOpt_), MHTmin(200) { 
			//check for option
			localOpt->Get("MHTmin",MHTmin);
			doGen = localOpt->Get("gen",false);
		}
		virtual void CheckBranches(){
			looper->fChain->SetBranchStatus("MHT",1);
			if(doGen) looper->fChain->SetBranchStatus("GenMHT",1);
		}
		
		//this selector doesn't add anything to tree
		
		//used for non-dummy selectors
		virtual bool Cut() {
			if(doGen) return looper->GenMHT > MHTmin;
			else return looper->MHT > MHTmin;
		}
		
		//member variables
		double MHTmin;
		bool doGen;
};
REGISTER_SELECTOR(MHT);

//----------------------------------------------------
//selects events based on a diagonal cut along the HT/MHT plane
class KMHTHTRatioSelector : public KSelector {
	public:
		//constructor
		KMHTHTRatioSelector() : KSelector() { }
		KMHTHTRatioSelector(string name_, OptionMap* localOpt_) : KSelector(name_,localOpt_), debug(0) { 
			//check for option
			localOpt->Get("debug",debug);
		}
		virtual void CheckBranches(){
			looper->fChain->SetBranchStatus("HT",1);
			looper->fChain->SetBranchStatus("MHT",1);
		}

		//this selector doesn't add anything to tree

		//used for non-dummy selectors
		virtual bool Cut() {
			ratio = looper->MHT/looper->HT;
			if (debug) cout << "HT=" << looper->HT << " MHT=" << looper->MHT << " Ratio=" << ratio << endl;
			return ratio <= 1.0;
		}

		//member variables;
		bool debug;
		double ratio;
};
REGISTER_SELECTOR(MHTHTRatio);

//---------------------------------------------------------------
//forward declaration
class KMCWeightSelector;

//------------------------------------------------------
//single photon selector
class KPhotonSelector : public KSelector {
	public:
		//constructor
		KPhotonSelector() : KSelector() { }
		KPhotonSelector(string name_, OptionMap* localOpt_) : KSelector(name_,localOpt_) {
			//check option
			loose = localOpt->Get("loose",true);
			veto = localOpt->Get("veto",false);
			trigger = localOpt->Get("trigger",false);
		}
		virtual void CheckBranches(){
			looper->fChain->SetBranchStatus("Photons",1);
			looper->fChain->SetBranchStatus("Photons_fullID",1);
		}

		//this selector doesn't add anything to tree
		
		//used for non-dummy selectors
		virtual bool Cut() {
			int NumPhotons = 0;
			if(loose){
				NumPhotons = looper->Photons->size();
			}
			else{
				//tighten up ID
				for(unsigned p = 0; p < looper->Photons->size(); ++p){
					if(looper->Photons_fullID->at(p) and (!trigger || looper->Photons->at(p).Pt()>200)) ++NumPhotons;
				}
			}
			
			return NumPhotons==(veto? 0 : 1);
		}
		
		//member variables
		bool loose;
		bool veto;
		bool trigger;
};
REGISTER_SELECTOR(Photon);

//---------------------------------------------------------------
//class to store and apply RA2 binning
class KRA2BinSelector : public KSelector {
	public:
		//constructor
		KRA2BinSelector() : KSelector() { }
		KRA2BinSelector(string name_, OptionMap* localOpt_) : KSelector(name_,localOpt_), RA2Exclusive(true), DoBTagSF(false), bqty(-1), debug(0), MCWeight(0) { 
			//assemble member vars from user input
			localOpt->Get("RA2VarNames",RA2VarNames);
			
			for(unsigned q = 0; q < RA2VarNames.size(); ++q){
				if(RA2VarNames[q]=="BTags") bqty = q;

				stringstream pre;
				pre << "RA2Var" << q;
				
				vector<float> min, max;
				localOpt->Get(pre.str()+"Min",min);
				localOpt->Get(pre.str()+"Max",max);
				if(min.size() != max.size()){
					cout << "Input error: vector length mismatches in " << pre.str() << " min and max specification. RA2 binning will not be computed." << endl;
					depfailed = true;
					return;
				}
				
				vector<unsigned> bins;
				localOpt->Get(pre.str()+"Bins",bins);
				if(q>0 && bins.size()!=all_bins[0].size()){
					cout << "Input error: vector length mismatches in " << pre.str() << " bins specification. RA2 binning will not be computed." << endl;
					depfailed = true;
					return;	
				}
				
				//store member vars
				RA2VarMin.push_back(min);
				RA2VarMax.push_back(max);
				all_bins.push_back(bins);
			}
			
			//create map of RA2 bin IDs to bin numbers
			for(unsigned b = 0; b < all_bins[0].size(); ++b){
				vector<unsigned> bin_id;
				bin_id.reserve(all_bins.size());
				for(unsigned q = 0; q < all_bins.size(); ++q){
					bin_id.push_back(all_bins[q][b]);
				}
				IDtoBinNumber[bin_id] = b+1; //bin numbers start at 1
			}
			
			//check other options
			RA2Exclusive = localOpt->Get("RA2Exclusive",true);
			localOpt->Get("RA2debug",debug);
			if(forceadd and not depfailed) canfail = false;
		}
		void CheckLabels(){
			//check if (shared) bin labels have already been created
			if(sel->GetGlobalOpt()->Has("RA2bin_labels")){
				sel->GetGlobalOpt()->Get("RA2bin_labels",labels);
			}
			else {
				//create map of bin labels (in case they are requested)
				labels.reserve(all_bins[0].size());
				string prefix = "";
				localOpt->Get("RA2prefix",prefix);
				bool suffix = localOpt->Get("RA2suffix",true);
				for(unsigned b = 0; b < all_bins[0].size(); ++b){
					stringstream label;
					if(prefix.size()>0) {
						label << prefix;
						if(suffix) label << "_";
					}
					for(unsigned q = 0; q < all_bins.size(); ++q){
						if(!suffix) continue;
						label << RA2VarNames[q] << all_bins[q][b]; //the specific bin label: currently just the bin number
						if(q<all_bins.size()-1) label << "_";
					}
					labels.push_back(label.str());
				}
				
				//store labels in global options
				sel->GetGlobalOpt()->Set<vector<string> >("RA2bin_labels",labels);
			}
		}
		//implemented in KBuilderSelectors or KSkimmerSelectors to avoid dependencies
		virtual void CheckDeps();
		virtual void CheckBase();
		virtual void CheckBranches(){
			for(unsigned q = 0; q < RA2VarNames.size(); ++q){
				looper->fChain->SetBranchStatus(RA2VarNames[q].c_str(),1);
			}
		}
		virtual void SetBranches(){
			if(!tree) return;

			//default values
			RA2binBranch = 0;
			tree->Branch("RA2bin",&RA2binBranch,"RA2binBranch/i");
			//only for mc
			if(base->IsMC()) tree->Branch("RA2bins","std::vector<unsigned>",&RA2binsBranch,32000,0);
		}
		
		//used for non-dummy selectors
		virtual bool Cut() {
			if(depfailed) return false;
			
			//mode to add tree branches
			if(forceadd){
				//reset vars
				RA2binBranch = 0;
				
				DoBTagSF = false;
				vector<vector<unsigned>> RA2binVectmp;
				vector<unsigned> RA2binstmp = GetBinNumbers(RA2binVectmp);
				if(RA2binstmp.size()>0) RA2binBranch = RA2binstmp[0];
				
				//check all separate btag bins for SFs
				if(base->IsMC()){
					DoBTagSF = true;
					RA2binsBranch = GetBinNumbers(RA2binVectmp);
				}
				
				//passthrough
				return true;
			}
			else {
				RA2bins = GetBinNumbers(RA2binVec);
			}
			
			return RA2bins.size()!=0;
		}
		
		//functions
		vector<unsigned> GetBinNumbers(vector<vector<unsigned> >& bin_vec) {
			vector<vector<unsigned> > bins;
			bins.reserve(RA2VarNames.size());
			for(unsigned q = 0; q < RA2VarNames.size(); ++q){
				bins.push_back(GetBins(q));
				
				//skip loop if no bin was found for a value
				if(bins.back().size()==0) return vector<unsigned>();
			}
			
			//set up for variable # of for loops
			vector<unsigned> indices(RA2VarNames.size(),0);
			vector<unsigned> bin_num(RA2VarNames.size(),0);
			vector<unsigned> found_bins;
			vector<vector<unsigned>> found_bin_nums;
			FindBin(indices,bins,0,bin_num,found_bins,found_bin_nums);
			if(DoBTagSF and bqty>=0){
				//search for other possible btag bins
				vector<unsigned> extra_bins;
				vector<vector<unsigned>> extra_bin_nums;
				for(unsigned n = 0; n < found_bins.size(); ++n){
					unsigned borig = found_bin_nums[n][bqty];
					for(unsigned b = 0; b < RA2VarMax[bqty].size(); ++b){
						//avoid duplicates
						if(b==borig) continue;
						auto new_bin_num = found_bin_nums[n];
						new_bin_num[bqty] = b;
						auto it = IDtoBinNumber.find(new_bin_num);
						if(it != IDtoBinNumber.end()){
							extra_bins.push_back(it->second);
							extra_bin_nums.push_back(new_bin_num);
						}
					}
				}
				found_bins.insert(found_bins.end(),extra_bins.begin(),extra_bins.end());
				found_bin_nums.insert(found_bin_nums.end(),extra_bin_nums.begin(),extra_bin_nums.end());
			}
			bin_vec = found_bin_nums;
			return found_bins;
		}
		//recursive function to implement variable # of for loops
		//ref: http://stackoverflow.com/questions/9555864/variable-nested-for-loops
		void FindBin(vector<unsigned>& indices, vector<vector<unsigned> >& bins, unsigned pos, vector<unsigned>& bin_num, vector<unsigned>& found_bins, vector<vector<unsigned> >& found_bin_nums){
			for(indices[pos] = 0; indices[pos] < bins[pos].size(); indices[pos]++){
				bin_num[pos] = bins[pos][indices[pos]];
				if(pos == indices.size()-1){
					auto it = IDtoBinNumber.find(bin_num);
					if(it != IDtoBinNumber.end()){
						found_bins.push_back(it->second);
						found_bin_nums.push_back(bin_num);
					}
				}
				else {
					FindBin(indices,bins,pos+1,bin_num,found_bins,found_bin_nums);
				}
			}
		}
		
		vector<unsigned> GetBins(unsigned qty){
			//assume all values are floats
			vector<float> val;
			if(RA2VarNames[qty]=="NJets") val.push_back(looper->NJets);
			else if(RA2VarNames[qty]=="BTags") val.push_back(looper->BTags);
			else if(RA2VarNames[qty]=="MHT") val.push_back(looper->MHT);
			else if(RA2VarNames[qty]=="HT") val.push_back(looper->HT);
			else if(RA2VarNames[qty]=="GenMHT") val.push_back(looper->GenMHT);
			else if(RA2VarNames[qty]=="GenHT") val.push_back(looper->GenHT);
			//else if(RA2VarNames[qty]=="ak1p2Jets_sumJetMass") val.push_back(looper->ak1p2Jets_sumJetMass);
			else {}			
			
			vector<unsigned> bins;
			for(unsigned v = 0; v < val.size(); ++v){
				for(unsigned n = 0; n < RA2VarMin[qty].size(); ++n){
					if(val[v] > RA2VarMin[qty][n] && val[v] <= RA2VarMax[qty][n]) bins.push_back(n);
				}
			}
			return bins;
		}
		
		unsigned GetBin(string qty_name, const vector<unsigned>& bin_num){
			for(unsigned q = 0; q < RA2VarNames.size(); ++q){
				if(RA2VarNames[q]==qty_name) return bin_num[q];
			}
			return -1;
		}

		float GetBinMax(string qty_name, const vector<unsigned>& bin_num){
			for(unsigned q = 0; q < RA2VarNames.size(); ++q){
				if(RA2VarNames[q]==qty_name) return RA2VarMax[q][bin_num[q]];
			}
			return -1;
		}

		float GetBinMin(string qty_name, const vector<unsigned>& bin_num){
			for(unsigned q = 0; q < RA2VarNames.size(); ++q){
				if(RA2VarNames[q]==qty_name) return RA2VarMin[q][bin_num[q]];
			}
			return -1;
		}

	public:
		//member variables
		bool RA2Exclusive, DoBTagSF;
		int bqty;
		int debug;
		vector<vector<unsigned> > all_bins;
		vector<unsigned> RA2bins;
		vector<vector<unsigned> > RA2binVec;
		map<vector<unsigned>, unsigned> IDtoBinNumber;
		vector<string> RA2VarNames;
		vector<vector<float> > RA2VarMin, RA2VarMax;
		vector<string> labels;
		KMCWeightSelector* MCWeight;
		unsigned RA2binBranch;
		vector<unsigned> RA2binsBranch;
};
REGISTER_SELECTOR(RA2Bin);

#endif
