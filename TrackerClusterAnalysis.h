//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 22 09:49:30 2018 by ROOT version 6.12/07
// from TTree ttree/ttree
// found on file: histo.root
//////////////////////////////////////////////////////////

#ifndef TrackerClusterAnalysis_h
#define TrackerClusterAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>


// Header file for the classes stored in the TTree if any.

class TrackerClusterAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           tree_track_nclusters;
   Double_t        tree_track_pt;
   Double_t        tree_track_eta;
   Double_t        tree_track_phi;
   Int_t           tree_track_nhits;
   Double_t        tree_track_NChi2;
   Int_t           tree_Cluster_subDet[1000];   //[tree_track_nclusters]
   Int_t           tree_Cluster_PetalSide[1000];   //[tree_track_nclusters]
   Int_t           tree_Cluster_LayerNbr[1000];   //[tree_track_nclusters]
   Int_t           tree_Cluster_WheelSide[1000];   //[tree_track_nclusters]
   Double_t        tree_Cluster_charge[1000];   //[tree_track_nclusters]
   Double_t        tree_Cluster_path[1000];   //[tree_track_nclusters]
   Double_t        tree_Cluster_tsosx[1000];   //[tree_track_nclusters]
   Double_t        tree_Cluster_tsosy[1000];   //[tree_track_nclusters]
   Double_t        tree_Cluster_SoverN[1000];   //[tree_track_nclusters]
   Double_t        tree_Cluster_noise[1000];   //[tree_track_nclusters]
   Int_t           tree_Cluster_width[1000];   //[tree_track_nclusters]
   Double_t        tree_Cluster_barycenter[1000];   //[tree_track_nclusters]
   Int_t           tree_Cluster_detID[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_locX[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_locY[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_globX[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_globY[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_globZ[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_tsosglobX[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_tsosglobY[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_tsosglobZ[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_LocalTracj_X[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_LocalTracj_Y[1000];   //[tree_track_nclusters]
   Float_t         tree_Cluster_LocalTracj_Z[1000];   //[tree_track_nclusters]
   
   
   Int_t           tree_Strips_nstrip;
   Int_t           tree_Strips_idFirst[1000];   //[tree_track_nclusters]
   Int_t           tree_Strips_idLast[1000];   //[tree_track_nclusters]
   Int_t           tree_Strips_stripCharges[164];   //[tree_Strips_nstrip]
   Float_t         tree_Strips_stripGains[164];   //[tree_Strips_nstrip]
   Float_t         tree_Strips_stripNoises[164];   //[tree_Strips_nstrip]
   Bool_t          tree_Strips_stripQualitiesBad[164];   //[tree_Strips_nstrip]
   Int_t           runNumber;
   Int_t           eventNumber;
   Int_t           lumiBlock;

   // List of branches
   TBranch        *b_tree_track_nclusters;   //!
   TBranch        *b_tree_track_pt;   //!
   TBranch        *b_tree_track_eta;   //!
   TBranch        *b_tree_track_phi;   //!
   TBranch        *b_tree_track_nhits;   //!
   TBranch        *b_tree_track_NChi2;   //!
   TBranch        *b_tree_Cluster_subDet;   //!
   TBranch        *b_tree_Cluster_PetalSide;   //!
   TBranch        *b_tree_Cluster_LayerNbr;   //!
   TBranch        *b_tree_Cluster_WheelSide;   //!
   TBranch        *b_tree_Cluster_charge;   //!
   TBranch        *b_tree_Cluster_path;   //!
   TBranch        *b_tree_Cluster_tsosx;   //!
   TBranch        *b_tree_Cluster_tsosy;   //!
   TBranch        *b_tree_Cluster_SoverN;   //!
   TBranch        *b_tree_Cluster_noise;   //!
   TBranch        *b_tree_Cluster_width;   //!
   TBranch        *b_tree_Cluster_barycenter;   //!
   TBranch        *b_tree_Cluster_detID;   //!
   TBranch        *b_tree_Cluster_locX;   //!
   TBranch        *b_tree_Cluster_locY;   //!
   TBranch        *b_tree_Cluster_globX;   //!
   TBranch        *b_tree_Cluster_globY;   //!
   TBranch        *b_tree_Cluster_globZ;   //!
   TBranch        *b_tree_Cluster_tsosglobX;   //!
   TBranch        *b_tree_Cluster_tsosglobY;   //!
   TBranch        *b_tree_Cluster_tsosglobZ;   //!
   TBranch        *b_tree_Cluster_LocalTracj_X;   //!
   TBranch        *b_tree_Cluster_LocalTracj_Y;   //!
   TBranch        *b_tree_Cluster_LocalTracj_Z;   //!
   TBranch        *b_tree_Strips_nstrip;   //!
   TBranch        *b_tree_Strips_idFirst;   //!
   TBranch        *b_tree_Strips_idLast;   //!
   TBranch        *b_tree_Strips_stripCharges;   //!
   TBranch        *b_tree_Strips_stripGains;   //!
   TBranch        *b_tree_Strips_stripNoises;   //!
   TBranch        *b_tree_Strips_stripQualitiesBad;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_lumiBlock;   //!

   TrackerClusterAnalysis(TTree *tree=0, TString inputName = "", TString outputName = "");
   virtual ~TrackerClusterAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   
   TString outputName_;
};

#endif

#ifdef TrackerClusterAnalysis_cxx
TrackerClusterAnalysis::TrackerClusterAnalysis(TTree *tree, TString inputName,TString outputName ) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

   if (tree == 0 && inputName !="") {/* 
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("histo.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("histo.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("histo.root:/analysis");
      dir->GetObject("ttree",tree); */
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(inputName.Data() );
       if (!f || !f->IsOpen()) {
         f = new TFile(inputName.Data() );
      }
      TString directory = inputName+":/analysis";
      TDirectory * dir = (TDirectory*)f->Get(directory.Data() );
      dir->GetObject("ttree",tree);
      outputName_ = outputName;

   }
   Init(tree);
}

TrackerClusterAnalysis::~TrackerClusterAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TrackerClusterAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TrackerClusterAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TrackerClusterAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("tree_track_nclusters", &tree_track_nclusters, &b_tree_track_nclusters);
   fChain->SetBranchAddress("tree_track_pt", &tree_track_pt, &b_tree_track_pt);
   fChain->SetBranchAddress("tree_track_eta", &tree_track_eta, &b_tree_track_eta);
   fChain->SetBranchAddress("tree_track_phi", &tree_track_phi, &b_tree_track_phi);
   fChain->SetBranchAddress("tree_track_nhits", &tree_track_nhits, &b_tree_track_nhits);
   fChain->SetBranchAddress("tree_track_NChi2", &tree_track_NChi2, &b_tree_track_NChi2);
   fChain->SetBranchAddress("tree_Cluster_subDet", tree_Cluster_subDet, &b_tree_Cluster_subDet);
   fChain->SetBranchAddress("tree_Cluster_PetalSide", tree_Cluster_PetalSide, &b_tree_Cluster_PetalSide);
   fChain->SetBranchAddress("tree_Cluster_LayerNbr", tree_Cluster_LayerNbr, &b_tree_Cluster_LayerNbr);
   fChain->SetBranchAddress("tree_Cluster_WheelSide", tree_Cluster_WheelSide, &b_tree_Cluster_WheelSide);
   fChain->SetBranchAddress("tree_Cluster_charge", tree_Cluster_charge, &b_tree_Cluster_charge);
   fChain->SetBranchAddress("tree_Cluster_path", tree_Cluster_path, &b_tree_Cluster_path);
   fChain->SetBranchAddress("tree_Cluster_tsosx", tree_Cluster_tsosx, &b_tree_Cluster_tsosx);
   fChain->SetBranchAddress("tree_Cluster_tsosy", tree_Cluster_tsosy, &b_tree_Cluster_tsosy);
   fChain->SetBranchAddress("tree_Cluster_SoverN", tree_Cluster_SoverN, &b_tree_Cluster_SoverN);
   fChain->SetBranchAddress("tree_Cluster_noise", tree_Cluster_noise, &b_tree_Cluster_noise);
   fChain->SetBranchAddress("tree_Cluster_width", tree_Cluster_width, &b_tree_Cluster_width);
   fChain->SetBranchAddress("tree_Cluster_barycenter", tree_Cluster_barycenter, &b_tree_Cluster_barycenter);
   fChain->SetBranchAddress("tree_Cluster_detID", tree_Cluster_detID, &b_tree_Cluster_detID);
   fChain->SetBranchAddress("tree_Cluster_locX", tree_Cluster_locX, &b_tree_Cluster_locX);
   fChain->SetBranchAddress("tree_Cluster_locY", tree_Cluster_locY, &b_tree_Cluster_locY);
   fChain->SetBranchAddress("tree_Cluster_globX", tree_Cluster_globX, &b_tree_Cluster_globX);
   fChain->SetBranchAddress("tree_Cluster_globY", tree_Cluster_globY, &b_tree_Cluster_globY);
   fChain->SetBranchAddress("tree_Cluster_globZ", tree_Cluster_globZ, &b_tree_Cluster_globZ);
   fChain->SetBranchAddress("tree_Cluster_tsosglobX", tree_Cluster_tsosglobX, &b_tree_Cluster_tsosglobX);
   fChain->SetBranchAddress("tree_Cluster_tsosglobY", tree_Cluster_tsosglobY, &b_tree_Cluster_tsosglobY);
   fChain->SetBranchAddress("tree_Cluster_tsosglobZ", tree_Cluster_tsosglobZ, &b_tree_Cluster_tsosglobZ);
   
   fChain->SetBranchAddress("tree_Cluster_LocalTracj_X", tree_Cluster_LocalTracj_X, &b_tree_Cluster_LocalTracj_X);
   fChain->SetBranchAddress("tree_Cluster_LocalTracj_Y", tree_Cluster_LocalTracj_Y, &b_tree_Cluster_LocalTracj_Y);
   fChain->SetBranchAddress("tree_Cluster_LocalTracj_Z", tree_Cluster_LocalTracj_Z, &b_tree_Cluster_LocalTracj_Z);
   
   fChain->SetBranchAddress("tree_Strips_nstrip", &tree_Strips_nstrip, &b_tree_Strips_nstrip);
   fChain->SetBranchAddress("tree_Strips_idFirst", tree_Strips_idFirst, &b_tree_Strips_idFirst);
   fChain->SetBranchAddress("tree_Strips_idLast", tree_Strips_idLast, &b_tree_Strips_idLast);
   fChain->SetBranchAddress("tree_Strips_stripCharges", tree_Strips_stripCharges, &b_tree_Strips_stripCharges);
   fChain->SetBranchAddress("tree_Strips_stripGains", tree_Strips_stripGains, &b_tree_Strips_stripGains);
   fChain->SetBranchAddress("tree_Strips_stripNoises", tree_Strips_stripNoises, &b_tree_Strips_stripNoises);
   fChain->SetBranchAddress("tree_Strips_stripQualitiesBad", tree_Strips_stripQualitiesBad, &b_tree_Strips_stripQualitiesBad);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   Notify();
}

Bool_t TrackerClusterAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TrackerClusterAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TrackerClusterAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TrackerClusterAnalysis_cxx
