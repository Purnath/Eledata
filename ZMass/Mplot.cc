#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>
#include <TString.h>
#include <TStyle.h>

void Mplot()
{
  TFile *file1 = TFile::Open("..\\TotPassdists\\Ztoll_M_dist.root");
  if (!file1 || file1->IsZombie()) {
    std::cerr << "Error opening file: " << "..\\TotPassdists\\Ztoll_M_dist.root" << std::endl;
    return;
  }
  TFile *file2 = TFile::Open("..\\TotPassdists\\MCZtoll_M_dist.root");
  if (!file2 || file2->IsZombie()) {
    std::cerr << "Error opening file: " << "..\\TotPassdists\\MCZtoll_M_dist.root" << std::endl;
    return;
  }

  // Create a new ROOT file for writing
  TFile *outputFile = new TFile("M_plot.root", "recreate");
  
  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("1.2f");

  TH1F *h_total;
  TH1F *h_pass;
  TH1F *h_totalMC;
  TH1F *h_passMC;
  
  h_total = (TH1F*)file1->Get("M_total");
  h_pass = (TH1F*)file1->Get("M_pass");
  h_totalMC = (TH1F*)file2->Get("M_total");
  h_passMC = (TH1F*)file2->Get("M_pass");

  h_totalMC-> Scale ( h_total -> Integral()/ h_totalMC -> Integral());
  h_passMC-> Scale ( h_pass -> Integral()/ h_passMC -> Integral());
  
  h_totalMC->GetXaxis()->SetTitle("m_{ee} in (GeV)");
  h_total->GetXaxis()->SetTitle("m_{ee} in (GeV)");
  h_total->SetTitle("");
  h_totalMC->SetTitle("");
  h_pass->SetTitle("");
  h_passMC->SetTitle("");
  h_pass->GetXaxis()->SetTitle("m_{ee} in (GeV)");
  h_passMC->GetXaxis()->SetTitle("m_{ee} in (GeV)");
  
  h_total->GetYaxis()->SetTitle("Events");
  h_total -> GetYaxis() -> SetMaxDigits(2);
  h_pass->GetYaxis()->SetTitle("Events");
  h_totalMC->GetYaxis()->SetTitle("Events");
  h_totalMC -> GetYaxis() -> SetMaxDigits(2);
  
  h_pass-> GetYaxis() -> SetMaxDigits(2);
  //h_passMC->GetYaxis()->SetTitle("Events");

  TH1F *h_fail = (TH1F*)h_total->Clone();
  TH1F *h_failMC = (TH1F*)h_totalMC->Clone();

  h_fail->Add(h_pass,-1);
  h_failMC->Add(h_passMC,-1);
  
  TCanvas *c = new TCanvas("c","passing",800,700);      
  c->SetLogy(0);
  
  h_pass->SetLineColor(kRed);
  h_pass->SetMarkerStyle(20);
  h_pass->SetMarkerColor(kBlue);
  
  h_passMC->SetLineColor(kRed);
  h_passMC->SetMarkerStyle(20);
  h_passMC->SetMarkerColor(2);
      
  h_pass->SetTitle("");
  //h_pass->GetYaxis()->SetRangeUser(0,400);
  h_passMC->GetXaxis()->SetTitle("");
  h_passMC->GetYaxis()->SetTitle("");
  
  // TPad pad1 ( " pad1 " ," pad1 " ,0 ,0.3 ,1 ,1);
  //pad1.SetLogy( true );
  // pad1.Draw();
  // pad1.cd();
  h_pass -> Draw( " pe " );
  h_passMC-> Draw( "HIST LEP , same " );
      
  TPaveText *pt1 = new TPaveText(0.5,0.89,0.85,1,"NDC");
  pt1->SetBorderSize(0);
  pt1->SetFillColor(0);
  pt1->SetFillStyle(0);
  pt1->AddText("CMS #sqrt{s}=13 TeV (2015)");
  //pt1->AddText("");
  pt1->Draw("same");

  // TPaveText *pt2 = new TPaveText(0.6,0.5,0.85,0.7,"NDC");
  // pt2->SetBorderSize(0);
  // pt2->SetFillColor(0);
  // pt2->SetFillStyle(0);
  // pt2->AddText("30<p_{T}<50 GeV");
  // pt2->AddText("2<|#eta|<2.5");
  // pt2->Draw("same");

  // Add legend
  TLegend* l1 = new TLegend(0.6, 0.7, 0.85, 0.88); // Define legend position
  l1->SetBorderSize(0);
  l1->SetHeader("Passing");
  l1->AddEntry(h_pass, "Data", "aep"); // Add entry for data
  l1->AddEntry(h_passMC, "Z->ee(MC)", "lep"); // Add entry for MC
  l1->Draw(); // Draw legend

  c->Write();
  
  TString pngFileName = "M_passing.png";
  c->SaveAs(pngFileName.Data());
  c->Clear();
  
  delete h_pass;
  delete h_passMC;
  
  c->SetLogy(0);
  
  h_fail->SetLineColor(1);
  h_fail->SetMarkerStyle(20);
  h_fail->SetMarkerColor(kBlue);
  
  h_failMC->SetLineColor(kRed);
  h_failMC->SetMarkerStyle(20);
  h_failMC->SetMarkerColor(2);
      
  h_failMC->SetTitle("");
  
  //h_fail->GetYaxis()->SetRangeUser(0,4500);
  h_failMC->GetXaxis()->SetTitle("");
  h_failMC->GetYaxis()->SetTitle("");
  
  // TPad pad1 ( " pad1 " ," pad1 " ,0 ,0.3 ,1 ,1);
  //pad1.SetLogy( true );
  // pad1.Draw();
  // pad1.cd();
  h_fail -> Draw( " pe " );
  h_failMC-> Draw( " HIST Lep , same " );
      
  // TPaveText *pt1 = new TPaveText(0.1,0.89,0.45,1,"NDC");
  // pt1->SetBorderSize(0);
  // pt1->SetFillColor(0);
  // pt1->SetFillStyle(0);
  // pt1->AddText("CMS #sqrt{s}=13 TeV (2015)");
  //pt1->AddText("");
  pt1->Draw("same");
  //pt2->Draw("same");

  // Add legend
  //TLegend* l1 = new TLegend(); // Define legend position
  //l1->SetBorderSize(0);
  //l1->AddEntry(h_fail, "Data", "aep"); // Add entry for data
  //l1->AddEntry(h_failMC, "Z->ee(MC)", "l"); // Add entry for MC
  l1->SetHeader("Failing");
  l1->Draw(); // Draw legend

  c->Write();
  
  pngFileName = "M_failing.png";
  c->SaveAs(pngFileName.Data());
  c->Clear();
 
      
  // pad1.SetBottomMargin (0);
  // pad2.SetTopMargin(0);
  // pad2
  
  delete h_fail;
  delete h_failMC;
  delete c;

  outputFile->Close();
  file1->Close();
  file2->Close();
}
