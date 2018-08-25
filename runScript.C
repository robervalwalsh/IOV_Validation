#include "TFile.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TString.h"
#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include "SignalOverNoisePlot.h"
#include "TStyle.h"
#include "TLegend.h"
#include <vector>


  
void producePlots(){
  
  
   gStyle->SetOptFile(0);
   gStyle->SetOptStat("mr"); // To display the mean and RMS: SetOptStat("mr");
   gStyle->SetStatColor(0); // kWhite
   gStyle->SetStatFont(42);
   //ROOT . gStyle . SetStatFontSize(0.025);
   gStyle->SetStatFontSize(0.04);
   gStyle->SetStatTextColor(1);
   gStyle->SetStatFormat("6.4g");
   gStyle->SetStatBorderSize(1);
   gStyle->SetStatH(0.1);
   gStyle->SetStatW(0.15);

   //gStyle->SetOptTitle(0);
   gStyle->SetTitleFont(42);
   gStyle->SetTitleColor(1);
   gStyle->SetTitleTextColor(1);
   gStyle->SetTitleFillColor(10);
   gStyle->SetTitleFontSize(0.05);
  
  
  TFile * histo_old = new TFile("output1.root");
  TFile * histo_new = new TFile("output2.root");
  

  std::vector<TH1F * > oldPlots;
  std::vector<TH1F * > newPlots;
  
  
  std::vector<TString> histonames; 
  histonames.push_back("SoverN_TIB");
  histonames.push_back("SoverN_TOB");
  histonames.push_back("SoverN_TIDp");
  histonames.push_back("SoverN_TIDm");
  histonames.push_back("SoverN_TECp");
  histonames.push_back("SoverN_TECm");
  
  TCanvas * c1 = new TCanvas("c", "c", 800, 600);
  for(unsigned int i=0; i<histonames.size(); i++){
  
    
    TH1F* histOld = (TH1F*)histo_old->Get(histonames[i].Data());
    TH1F* histNew = (TH1F*)histo_new->Get(histonames[i].Data());
    
    TCanvas * c1 = new TCanvas("c", "c", 800, 600);
    
    histOld->Draw();
    histNew->Draw("same");
    histNew->SetLineColor(2); 
    histNew->SetLineWidth(2); 
    histOld->SetLineWidth(2); 
    histOld->GetXaxis()->SetTitle("Signal Over Noise");
    histOld->GetYaxis()->SetTitle("#clusters");
    histOld->GetXaxis()->SetTitleOffset(0.5);
    histOld->GetYaxis()->SetTitleOffset(0.7);
    //histOld->GetXaxis()->SetTitleSize(1.5);
    //histOld->GetYaxis()->SetTitleSize(1.5);
      
    TLegend* qw = 0;
    qw = new TLegend(.60,.50,.80,.80);
    qw->SetShadowColor(0);
    qw->SetFillColor(0);
    qw->SetLineColor(0);
    qw->AddEntry( histOld,    "Old calibration"         ,"l");
    qw->AddEntry( histNew,    "New calibration"         ,"l");
    qw->Draw();
    
    TString outputfilename = histonames[i]+".png";
    c1->SaveAs(outputfilename.Data());
   
  }


}

void runScript(){
    
    TString FileName1 = "histo_Old.root";
    TString FileName2 = "histo_New.root";
    TTree * emptyTree = 0;
    
    gROOT->ProcessLine(".L SignalOverNoisePlot.C+");
    //TString command = "SignalOverNoisePlot(emptyTree, \""+FileName1.Data()+"\"output.root\\" )";
    SignalOverNoisePlot t1(emptyTree, FileName1.Data(), "output1.root");
    t1.Loop();
    
    SignalOverNoisePlot t2(emptyTree, FileName2.Data(), "output2.root");
    t2.Loop();
    
    producePlots();
}
 
