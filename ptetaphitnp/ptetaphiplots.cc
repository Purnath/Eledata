#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TString.h>
#include <TFormula.h>
#include <math.h>
#define pi (4*atan(1.0))

void ptetaphiplots() {
  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("1.2f");
  // Open the input ROOT file
  TFile *file = TFile::Open("..\\TagnProbe\\SingleElec_Run2015MiniAOD.root","READ");
  
  // Check if the file is open
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening file: " << "..\\TagnProbe\\SingleElec_Run2015MiniAOD.root" << std::endl;
    return;
  }
  TFile *file2 = TFile::Open("..\\TagnProbe\\MC_DY_M50_Run2015MiniAOD.root","READ");
  if (!file2 || file2->IsZombie()) {
    std::cerr << "Error opening file: " << "..\\TagnProbe\\MC_DY_M50_Run2015MiniAOD.root" << std::endl;
    return;
  }
  // Get the tree from the file
  TTree *tree = (TTree*)file->Get("TwoElecEvents");
  TTree *tree2 = (TTree*)file2->Get("TwoElecEvents");
  
  // Create variables to store branch values

    // Set branch addresses for data
    Int_t n_elecs;
    Double_t Pt_ll, M_ll, Eta_ll;

    double probe_Ele_e, tag_Ele_e;
    double probe_sc_e, tag_sc_e;
    Double_t tag_Ele_pt, probe_Ele_pt;
    Double_t tag_Ele_eta, probe_Ele_eta;
    double probe_sc_eta, tag_sc_eta;
    Double_t tag_Ele_phi, probe_Ele_phi;
    double probe_sc_phi, tag_sc_phi;
    Bool_t tag_Ele_isTight, probe_Ele_isTight;
    Double_t tag_Ele_ch, probe_Ele_ch;

    tree->SetBranchAddress("n_elecs", &n_elecs);
    tree->SetBranchAddress("Pt_ll", &Pt_ll);
    tree->SetBranchAddress("M_ll", &M_ll);
    tree->SetBranchAddress("Eta_ll", &Eta_ll);
    tree->SetBranchAddress("tag_Ele_e", &tag_Ele_e);
    tree->SetBranchAddress("tag_sc_e", &tag_sc_e);
    tree->SetBranchAddress("tag_Ele_pt", &tag_Ele_pt);
    tree->SetBranchAddress("tag_Ele_eta", &tag_Ele_eta);
    tree->SetBranchAddress("tag_sc_eta", &tag_sc_eta);
    tree->SetBranchAddress("tag_Ele_phi", &tag_Ele_phi);
    tree->SetBranchAddress("tag_sc_phi", &tag_sc_phi);
    tree->SetBranchAddress("tag_Ele_isTight", &tag_Ele_isTight);
    tree->SetBranchAddress("tag_Ele_ch", &tag_Ele_ch);
    tree->SetBranchAddress("probe_Ele_e", &probe_Ele_e);
    tree->SetBranchAddress("probe_sc_e", &probe_sc_e);
    tree->SetBranchAddress("probe_Ele_pt", &probe_Ele_pt);
    tree->SetBranchAddress("probe_Ele_eta", &probe_Ele_eta);
    tree->SetBranchAddress("probe_sc_eta", &probe_sc_eta);
    tree->SetBranchAddress("probe_Ele_phi", &probe_Ele_phi);
    tree->SetBranchAddress("probe_sc_phi", &probe_sc_phi);
    tree->SetBranchAddress("probe_Ele_isTight", &probe_Ele_isTight);
    tree->SetBranchAddress("probe_Ele_ch", &probe_Ele_ch);

    // Set branch addresses for MC
    Int_t n_elecsMC;
    Double_t Pt_llMC, M_llMC, Eta_llMC;

    double probe_Ele_eMC, tag_Ele_eMC;
    double probe_sc_eMC, tag_sc_eMC;
    Double_t tag_Ele_ptMC, probe_Ele_ptMC;
    Double_t tag_Ele_etaMC, probe_Ele_etaMC;
    double probe_sc_etaMC, tag_sc_etaMC;
    Double_t tag_Ele_phiMC, probe_Ele_phiMC;
    double probe_sc_phiMC, tag_sc_phiMC;
    Bool_t tag_Ele_isTightMC, probe_Ele_isTightMC;
    Double_t tag_Ele_chMC, probe_Ele_chMC;

    tree2->SetBranchAddress("n_elecs", &n_elecsMC);
    tree2->SetBranchAddress("Pt_ll", &Pt_llMC);
    tree2->SetBranchAddress("M_ll", &M_llMC);
    tree2->SetBranchAddress("Eta_ll", &Eta_llMC);
    tree2->SetBranchAddress("tag_Ele_e", &tag_Ele_eMC);
    tree2->SetBranchAddress("tag_sc_e", &tag_sc_eMC);
    tree2->SetBranchAddress("tag_Ele_pt", &tag_Ele_ptMC);
    tree2->SetBranchAddress("tag_Ele_eta", &tag_Ele_etaMC);
    tree2->SetBranchAddress("tag_sc_eta", &tag_sc_etaMC);
    tree2->SetBranchAddress("tag_Ele_phi", &tag_Ele_phiMC);
    tree2->SetBranchAddress("tag_sc_phi", &tag_sc_phiMC);
    tree2->SetBranchAddress("tag_Ele_isTight", &tag_Ele_isTightMC);
    tree2->SetBranchAddress("tag_Ele_ch", &tag_Ele_chMC);
    tree2->SetBranchAddress("probe_Ele_e", &probe_Ele_eMC);
    tree2->SetBranchAddress("probe_sc_e", &probe_sc_eMC);
    tree2->SetBranchAddress("probe_Ele_pt", &probe_Ele_ptMC);
    tree2->SetBranchAddress("probe_Ele_eta", &probe_Ele_etaMC);
    tree2->SetBranchAddress("probe_sc_eta", &probe_sc_etaMC);
    tree2->SetBranchAddress("probe_Ele_phi", &probe_Ele_phiMC);
    tree2->SetBranchAddress("probe_sc_phi", &probe_sc_phiMC);
    tree2->SetBranchAddress("probe_Ele_isTight", &probe_Ele_isTightMC);
    tree2->SetBranchAddress("probe_Ele_ch", &probe_Ele_chMC);

    // Create histograms for data
    TH1F *tag_Et  = new TH1F("E_tag","E_T tag", 70,0,2500 );
    TH1F *tag_pt  = new TH1F("pt_tag","p_T tag", 70,0,900 );
    TH1F *tag_eta = new TH1F("eta_tag","|#eta| tag", 60,0,3.5 );
    TH1F *tag_phi = new TH1F("phi_tag","#phi tag", 50,-pi,pi );
    TH1F *prb_Et  = new TH1F("E_prb","Et probe", 70,0,1000 );
    TH1F *prb_pt  = new TH1F("pt_prb","pt probe", 70,0,350 );
    TH1F *prb_eta = new TH1F("eta_prb","|#eta| probe", 60,0,3.5 );
    TH1F *prb_phi = new TH1F("phi_prb","#phi probe", 50,-pi,pi );

    // Create histograms for MC
    TH1F *tag_Et_MC  = new TH1F("E_tag_MC","E_T tag MC", 70,0,2500 );
    TH1F *tag_pt_MC  = new TH1F("pt_tag_MC","p_T tag MC", 70,0,900 );
    TH1F *tag_eta_MC = new TH1F("eta_tag_MC","|#eta| tag MC", 60,0,3.5 );
    TH1F *tag_phi_MC = new TH1F("phi_tag_MC","#phi tag MC", 50,-pi,pi );
    TH1F *prb_Et_MC  = new TH1F("E_prb_MC","Et probe MC", 70,0,1000 );
    TH1F *prb_pt_MC  = new TH1F("pt_prb_MC","pt probe MC", 70,0,350 );
    TH1F *prb_eta_MC = new TH1F("eta_prb_MC","|#eta| probe MC", 60,0,3.5 );
    TH1F *prb_phi_MC = new TH1F("phi_prb_MC","#phi probe MC", 50,-pi,pi );

    // Loop over data entries and fill histograms
    Long64_t nentries = tree->GetEntries();
    for (Long64_t i = 0; i < nentries; i++) {
      if (i%10000==0)
	std::cout<<i/10000<<"\t";
      tree->GetEntry(i);
      tag_Et->Fill(tag_Ele_e);
      tag_pt->Fill(tag_Ele_pt);
      tag_eta->Fill(abs(tag_Ele_eta));
      tag_phi->Fill(tag_Ele_phi);
      prb_Et->Fill(probe_Ele_e);
      prb_pt->Fill(probe_Ele_pt);
      prb_eta->Fill(abs(probe_Ele_eta));
      prb_phi->Fill(probe_Ele_phi);
    }

    // Loop over MC entries and fill histograms
    Long64_t nentriesMC = tree2->GetEntries();
    for (Long64_t i = 0; i < nentriesMC; i++) {
      if (i%10000==0)
	std::cout<<i/10000<<"\t";
      tree2->GetEntry(i);
      tag_Et_MC->Fill(tag_Ele_eMC);
      tag_pt_MC->Fill(tag_Ele_ptMC);
      tag_eta_MC->Fill(abs(tag_Ele_etaMC));
      tag_phi_MC->Fill(tag_Ele_phiMC);
      prb_Et_MC->Fill(probe_Ele_eMC);
      prb_pt_MC->Fill(probe_Ele_ptMC);
      prb_eta_MC->Fill(abs(probe_Ele_etaMC));
      prb_phi_MC->Fill(probe_Ele_phiMC);
    }

    tag_Et_MC->Scale(tag_Et->Integral()/tag_Et_MC->Integral());
    tag_pt_MC->Scale(tag_pt->Integral()/tag_pt_MC->Integral());
    tag_eta_MC->Scale(tag_eta->Integral()/tag_eta_MC->Integral());
    tag_phi_MC->Scale(tag_phi->Integral()/tag_phi_MC->Integral());
    prb_Et_MC->Scale(prb_Et->Integral()/prb_Et_MC->Integral());
    prb_pt_MC->Scale(prb_pt->Integral()/prb_pt_MC->Integral());
    prb_eta_MC->Scale(prb_eta->Integral()/prb_eta_MC->Integral());
    prb_phi_MC->Scale(prb_phi->Integral()/prb_phi_MC->Integral());

    TFile *outputFile = new TFile("ptetaphi_plots.root", "recreate");
    
    // Create canvas and legends
    TCanvas *canvas = new TCanvas("canvas", "Data vs MC", 600, 600);
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);

    
    TPaveText *pt1 = new TPaveText(0.1,0.89,0.6,1,"NDC");
    pt1->SetBorderSize(0);
    pt1->SetFillColor(0);
    pt1->SetFillStyle(0);
    pt1->AddText("CMS Open Data #sqrt{s}=13 TeV (2015)");
    //pt1->AddText("");
    
  
    
    // Lambda function to draw and save histograms
    auto drawAndSave = [&](TH1F* dataHist, TH1F* mcHist, const char* title, const char* filename) {
        canvas->Clear();
	canvas->SetLogy(1);
        dataHist->SetMarkerStyle(20);
        mcHist->SetFillColor(kYellow-9);
	mcHist->SetLineColor(kYellow+3);
	mcHist->SetFillStyle(1001);
	mcHist->SetTitle("");
        mcHist->GetXaxis()->SetTitle(title);
        mcHist->GetYaxis()->SetTitle("Events");
        mcHist->GetYaxis()->SetRangeUser(0.9,1e6);
	dataHist->SetTitle("");
        dataHist->GetXaxis()->SetTitle(title);
        dataHist->GetYaxis()->SetTitle("Events");
        dataHist->GetYaxis()->SetRangeUser(0.9,1e6);
	mcHist->Draw("HIST");
	dataHist->Draw("E same");
	pt1->Draw("same");
        legend->AddEntry(dataHist, "Data", "p");
        legend->AddEntry(mcHist, "MC", "f");
        legend->Draw();
        canvas->SaveAs(filename);
	outputFile->cd();
	canvas->Write();
        legend->Clear();
    };

    // Draw and save histograms
    drawAndSave(tag_Et, tag_Et_MC, "Tag E_{T} in GeV", "tag_Et.png");
    drawAndSave(prb_Et, prb_Et_MC, "Probe E_{T} in GeV", "probe_Et.png");
    drawAndSave(tag_pt, tag_pt_MC, "Tag p_{T} in GeV", "tag_pt.png");
    drawAndSave(prb_pt, prb_pt_MC, "Probe p_{T} in GeV", "probe_pt.png");
    drawAndSave(tag_eta, tag_eta_MC, "Tag |#eta|", "tag_eta.png");
    drawAndSave(prb_eta, prb_eta_MC, "Probe |#eta|", "probe_eta.png");
    drawAndSave(tag_phi, tag_phi_MC, "Tag #phi in rad", "tag_phi.png");
    drawAndSave(prb_phi, prb_phi_MC, "Probe #phi in rad", "probe_phi.png");

    // Clean up
    delete canvas;
    delete legend;
    file->Close();
    file2->Close();
    outputFile->Close();
}
