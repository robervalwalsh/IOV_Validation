#define SignalOverNoisePlot_cxx
#include "SignalOverNoisePlot.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <iostream>

void SignalOverNoisePlot::Loop()
{

   TFile * output = new TFile(outputName_.Data(), "recreate");
   
   TH1F * SoverN_TIB  = new TH1F("SoverN_TIB",  "signal over noise for TIB",  100, 0, 100);
   TH1F * SoverN_TOB  = new TH1F("SoverN_TOB",  "signal over noise for TOB",  100, 0, 100);
   TH1F * SoverN_TIDp = new TH1F("SoverN_TIDp", "signal over noise for TID+", 100, 0, 100);
   TH1F * SoverN_TIDm = new TH1F("SoverN_TIDm", "signal over noise for TID-", 100, 0, 100);
   TH1F * SoverN_TECp = new TH1F("SoverN_TECp", "signal over noise for TEC+", 100, 0, 100);
   TH1F * SoverN_TECm = new TH1F("SoverN_TECm", "signal over noise for TEC-", 100, 0, 100);


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(tree_track_pt < 1   ) continue;
      if(tree_track_NChi2 >10) continue;
      
      
     
      
      
      for(int iclu=0; iclu<tree_track_nclusters; iclu++){
        double mag = pow(
        tree_Cluster_LocalTracj_X[iclu]*tree_Cluster_LocalTracj_X[iclu]+
        tree_Cluster_LocalTracj_Y[iclu]*tree_Cluster_LocalTracj_Y[iclu]+
        tree_Cluster_LocalTracj_Z[iclu]*tree_Cluster_LocalTracj_Z[iclu]
	       , 0.5);
	float cosRZ = fabs(tree_Cluster_LocalTracj_Z[iclu])/mag ;
        cout << "************" << endl;
        cout  << tree_Cluster_LocalTracj_X[iclu] << endl;
        cout  << tree_Cluster_LocalTracj_Y[iclu] << endl;
        cout  << tree_Cluster_LocalTracj_Z[iclu] << endl;
        cout  <<mag  << endl;
        cout  << cosRZ << endl;
  
	if(tree_Cluster_subDet[iclu] == 0) SoverN_TIB->Fill(tree_Cluster_SoverN[iclu]*cosRZ);
	if(tree_Cluster_subDet[iclu] == 1) SoverN_TOB->Fill(tree_Cluster_SoverN[iclu]*cosRZ);
	if(tree_Cluster_subDet[iclu] == 2) {
	  if(tree_Cluster_WheelSide[iclu] == 2) SoverN_TIDp->Fill(tree_Cluster_SoverN[iclu]*cosRZ);
	  if(tree_Cluster_WheelSide[iclu] == 1) SoverN_TIDm->Fill(tree_Cluster_SoverN[iclu]*cosRZ);
	}  
	if(tree_Cluster_subDet[iclu] == 3) {
	  if(tree_Cluster_WheelSide[iclu] == 2) SoverN_TECp->Fill(tree_Cluster_SoverN[iclu]*cosRZ);
	  if(tree_Cluster_WheelSide[iclu] == 1) SoverN_TECm->Fill(tree_Cluster_SoverN[iclu]*cosRZ);
	}  
	
	
      }
      
   }
   
   output->Write();
}
