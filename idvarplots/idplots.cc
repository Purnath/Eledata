#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
void idplots() {
  const char* dataFile = "..\\myElectrons1.root";
  const char* mcFile = "..\\myMCElectrons1.root";

  gStyle->SetOptStat(0);
  gStyle->SetPaintTextFormat("1.2f");
  // Open the root files
  TFile* file = TFile::Open(dataFile);
  TFile* mcfile = TFile::Open(mcFile);
  
  // Check if files are opened successfully
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening data file: " << dataFile << std::endl;
    return;
  }
  if (!mcfile || mcfile->IsZombie()) {
    std::cerr << "Error opening MC file: " << mcFile << std::endl;
    return;
  }
  
  // Navigate to the directory containing the TTree
  TDirectoryFile* dir = dynamic_cast<TDirectoryFile*>(file->Get("elecs"));
  if (!dir) {
    std::cerr << "Error: Directory not found!" << std::endl;
    file->Close();
    return;
  }
  
  // Navigate to the directory containing the TTree
  TDirectoryFile* mcdir = dynamic_cast<TDirectoryFile*>(mcfile->Get("elecs"));
  if (!mcdir) {
    std::cerr << "Error: Directory not found!" << std::endl;
    mcfile->Close();
    return;
  }
  
  // Get the tree from data file
  TTree* dataTree = (TTree*)dir->Get("Events");
  
  // Check if the tree exists in data file
  if (!dataTree) {
    std::cerr << "Error: Tree not found in data file." << std::endl;
    file->Close();
    mcfile->Close();
    return;
  }
  
  // Get the tree from MC file
  TTree* mcTree = (TTree*)mcdir->Get("Events");
  
  // Check if the tree exists in MC file
  if (!mcTree) {
    std::cerr << "Error: Tree not found in MC file." << std::endl;
    file->Close();
    mcfile->Close();
    return;
  }
  
  // Define variables to store data from the tree
  Int_t numelecs;
  Int_t numelecsMC;
  std::vector<double>* elept= nullptr;
  std::vector<double>* eleptMC= nullptr;
  std::vector<double>* eta= nullptr;
  std::vector<double>* etaMC= nullptr;
  std::vector<double>* ch= nullptr;
  std::vector<double>* chMC= nullptr;
  std::vector<bool>* ele_isTight= nullptr;
  std::vector<bool>* ele_isTightMC= nullptr;
  std::vector<double>* dEtaIn = nullptr;
  std::vector<double>* dEtaInMC = nullptr;
  std::vector<double>* dPhiIn = nullptr;
  std::vector<double>* dPhiInMC = nullptr;
  std::vector<double>* hbE= nullptr;
  std::vector<double>* hbEMC= nullptr;
  std::vector<double>* sig= nullptr;
  std::vector<double>* sigMC= nullptr;
  std::vector<double>* rCI= nullptr;
  std::vector<double>* rCIMC= nullptr;
  std::vector<double>* ooEmooP= nullptr;
  std::vector<double>* ooEmooPMC= nullptr;
  
  // Set branch addresses for data tree
  dataTree->SetBranchAddress("numberelectron",&numelecs);
  dataTree->SetBranchAddress("ele_pt", &elept);
  dataTree->SetBranchAddress("ele_eta", &eta);
  dataTree->SetBranchAddress("ele_ch", &ch);
  dataTree->SetBranchAddress("ele_isTight",&ele_isTight);
  dataTree->SetBranchAddress("ele_dEtaIn", &dEtaIn);
  dataTree->SetBranchAddress("ele_dPhiIn", &dPhiIn);
  dataTree->SetBranchAddress("ele_hOverE", &hbE);
  dataTree->SetBranchAddress("ele_full5x5_sigmaIetaIeta", &sig);
  dataTree->SetBranchAddress("ele_relCombIsoWithEA", &rCI);
  dataTree->SetBranchAddress("ele_ooEmooP",&ooEmooP);
  
  // Set branch addresses for MC tree
  mcTree->SetBranchAddress("numberelectron",&numelecsMC);
  mcTree->SetBranchAddress("ele_pt", &eleptMC);
  mcTree->SetBranchAddress("ele_eta", &etaMC);
  mcTree->SetBranchAddress("ele_ch", &chMC);
  mcTree->SetBranchAddress("ele_isTight",&ele_isTightMC);
  mcTree->SetBranchAddress("ele_dEtaIn", &dEtaInMC);
  mcTree->SetBranchAddress("ele_dPhiIn", &dPhiInMC);
  mcTree->SetBranchAddress("ele_hOverE", &hbEMC);
  mcTree->SetBranchAddress("ele_full5x5_sigmaIetaIeta", &sigMC);
  mcTree->SetBranchAddress("ele_relCombIsoWithEA", &rCIMC); 
  mcTree->SetBranchAddress("ele_ooEmooP",&ooEmooPMC);
  
  TFile* outputFile = new TFile("IDvarplots.root", "recreate");
  
  // Create histograms
  TH1F* deb= new TH1F("detainb", "Data Histogram", 40, -0.01, 0.01);
  TH1F* demcb = new TH1F("detainmcb", "MC Histogram", 40, -0.01, 0.01);
  TH1F* deec= new TH1F("detainec", "Data Histogram", 40, -0.01, 0.01);
  TH1F* demcec = new TH1F("detainmcec", "MC Histogram", 40, -0.01, 0.01);
  
  TH1F* dphb = new TH1F("dphiinb", "Data Histogram", 40, -0.045, 0.045);
  TH1F* dphmcb = new TH1F("dphiinmcb", "MC Histogram", 40, -0.045, 0.045); 
  TH1F* dphec = new TH1F("dphiinec", "Data Histogram", 40, -0.1, 0.1);
  TH1F* dphmcec = new TH1F("dphiinmcec", "MC Histogram", 40, -0.1, 0.1);
  
  TH1F* heb = new TH1F("hoverEb", "Data Histogram", 40, 0.,0.065);
  TH1F* hemcb = new TH1F("hoverEmcb", "MC Histogram", 40, .0, 0.065); 
  TH1F* heec = new TH1F("hoverEec", "Data Histogram", 40, 0.0, 0.065);
  TH1F* hemcec = new TH1F("hoverEmcec", "MC Histogram", 40, 0.0, 0.065); 

  TH1F* sigb = new TH1F("", "Data Histogram", 40, 5.e-3, 10.5e-3);
  TH1F* sigmcb = new TH1F("", "MC Histogram", 40, 5.e-3, 10.5e-3); 
  TH1F* sigec = new TH1F("", "Data Histogram", 40, 15.e-3, 30.e-3);
  TH1F* sigmcec = new TH1F("", "MC Histogram", 40, 15.e-3, 30.e-3);
  
  TH1F* relb = new TH1F("", "Data Histogram", 40, 0.0,0.037);
  TH1F* relmcb = new TH1F("", "MC Histogram", 40, 0.0,0.037); 
  TH1F* relec = new TH1F("", "Data Histogram", 40, 0.0, 0.07);
  TH1F* relmcec = new TH1F("", "MC Histogram", 40, 0.0, 0.07);  

  TH1F* empb = new TH1F("", "Data Histogram", 40, 0.0,0.013);
  TH1F* empmcb = new TH1F("", "MC Histogram", 40, 0.0,0.013); 
  TH1F* empec = new TH1F("", "Data Histogram", 40, 0.0, 0.013);
  TH1F* empmcec = new TH1F("", "MC Histogram", 40, 0.0, 0.013);  
  
  // Fill histograms
  for (int i = 0; i < dataTree->GetEntries(); ++i) {
    if (i%10000==0)
      std::cout<<i/10000<<"\t";
    dataTree->GetEntry(i);
    if(numelecs==2 && ((*ch)[0]*(*ch)[1])<0 || 1){
      for (int j =0;j<numelecs;j++){
	if(abs((*eta)[j])<1.48  && (*ele_isTight)[j]==1){
	  deb->Fill((*dEtaIn)[j]);
	  dphb->Fill((*dPhiIn)[j]);
	  heb->Fill((*hbE)[j]);
	  sigb->Fill((*sig)[j]);
	  relb->Fill((*rCI)[j]);
	  empb->Fill((*ooEmooP)[j]);
	}
	else if(abs((*eta)[j])>1.48 && abs((*eta)[j])<3.0
		&& (*ele_isTight)[j]==1){
	  deec->Fill((*dEtaIn)[j]);
	  dphec->Fill((*dPhiIn)[j]);
	  heec->Fill((*hbE)[j]);
	  sigec->Fill((*sig)[j]);
	  relec->Fill((*rCI)[j]);
	  empec->Fill((*ooEmooP)[j]);
	}
      }
    }
  }
  for (int i = 0; i < mcTree->GetEntries(); ++i) {
    if (i%10000==0)
      std::cout<<i/10000<<"\t";
    mcTree->GetEntry(i);
    if(numelecsMC==2 && ((*chMC)[0]*(*chMC)[1])<0 || 1){
      for (int j =0;j<numelecsMC;j++) {
	if(abs((*etaMC)[j])<1.48  && (*ele_isTightMC)[j]==1){
	  demcb->Fill((*dEtaInMC)[j]);
	  dphmcb->Fill((*dPhiInMC)[j]);
	  hemcb->Fill((*hbEMC)[j]);
	  sigmcb->Fill((*sigMC)[j]);
	  relmcb->Fill((*rCIMC)[j]);
	  empmcb->Fill((*ooEmooPMC)[j]);
	}
	else if(abs((*etaMC)[j])>1.48 && abs((*etaMC)[j])<3.0
		&& (*ele_isTightMC)[j]==1){
	  demcec->Fill((*dEtaInMC)[j]);
	  dphmcec->Fill((*dPhiInMC)[j]);
	  hemcec->Fill((*hbEMC)[j]);
	  sigmcec->Fill((*sigMC)[j]);
	  relmcec->Fill((*rCIMC)[j]);
	  empmcec->Fill((*ooEmooPMC)[j]);
	}
      }
    }
  }
  demcb-> Scale ( deb -> Integral()/ demcb -> Integral());
  dphmcb-> Scale ( dphb -> Integral()/ dphmcb -> Integral());
  hemcb-> Scale ( heb -> Integral()/ hemcb -> Integral());
  sigmcb-> Scale ( sigb -> Integral()/ sigmcb -> Integral());
  relmcb-> Scale ( relb -> Integral()/ relmcb -> Integral());
  empmcb-> Scale ( empb -> Integral()/ empmcb -> Integral());

  demcec-> Scale ( deec -> Integral()/ demcec -> Integral());
  dphmcec-> Scale ( dphec -> Integral()/ dphmcec -> Integral());
  hemcec-> Scale ( heec -> Integral()/ hemcec -> Integral());
  sigmcec-> Scale ( sigec -> Integral()/ sigmcec -> Integral());
  relmcec-> Scale ( relec -> Integral()/ relmcec -> Integral()); 
  empmcec-> Scale ( empec -> Integral()/ empmcec -> Integral());
  
  // Create canvas
  TCanvas* c1 = new TCanvas("", "deetainb", 800, 700);
  c1->SetBottomMargin(0.5);
  // Draw histograms
  deb->SetMarkerStyle(20); // Set marker style for data
  deb->SetMarkerSize(1.2); // Set marker size for data
  deb->SetLineColor(kBlack); // Set line color for data
  demcb->SetFillColor(kAzure+6); // Set fill color for MC
  demcb->SetLineColor(kBlue); // Set line color for MC
  demcb->SetFillStyle(1001); // Set fill style for MC
  demcb -> SetTitle( "" );
  demcb -> GetXaxis() -> SetLabelSize(0);
  demcb -> GetXaxis() -> SetTitleSize(0);
  demcb -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  deb->GetYaxis()->SetTitle("Events");
  demcb->GetYaxis()->SetTitle("Events");
  deb->GetYaxis()->SetTitleOffset(0.8);
  demcb->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad11 ( " pad11 " ," pad11 " ,0 ,0.3 ,1 ,1);
  pad11.SetLogy( true );
  pad11.Draw();
  pad11.cd();
  demcb -> Draw( " h " );
  deb-> Draw( " pe , same " );
  
  TPaveText *pt1 = new TPaveText(0.1,0.89,0.6,1,"NDC");
  pt1->SetBorderSize(0);
  pt1->SetFillColor(0);
  pt1->SetFillStyle(0);
  pt1->AddText("CMS Open Data #sqrt{s}=13 TeV (2015)");
  //pt1->AddText("");
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiodeb = new TH1F("ratiodeb", "Data/MC Ratio", 40, -0.01, 0.01); // Change binning as needed
  ratiodeb = (TH1F*)deb->Clone();
  ratiodeb->Divide(demcb);
  // Fill ratio histogram
  // for (int bin = 1; bin <= deb->GetNbinsX(); ++bin) {
  //   double dataBinContent = deb->GetBinContent(bin);
  //   double mcBinContent = demcb->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiodeb->SetBinContent(bin, ratio);
  // }
  
  
  // Add legend
  TLegend* l1 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l1->SetBorderSize(0);
  l1->SetHeader("Barrel");
  l1->AddEntry(deb, "Data", "lep"); // Add entry for data
  l1->AddEntry(demcb, "Z->ee(MC)", "f"); // Add entry for MC
  l1->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiodeb->SetMarkerStyle(20); // Set marker style
  ratiodeb->SetMarkerSize(1.2); // Set marker size
  ratiodeb->SetLineColor(kBlack); // Set line color
  ratiodeb -> SetTitle( "" );
  ratiodeb -> GetXaxis() -> SetTitle("#Delta#eta_{in}");  
  ratiodeb -> GetXaxis() -> SetTitleOffset(0.8);
  ratiodeb -> GetXaxis() -> SetLabelSize(0.12);
  ratiodeb -> GetXaxis() -> SetMaxDigits(2);
  ratiodeb -> GetXaxis() -> SetTitleSize(0.15);
  ratiodeb -> GetYaxis() -> SetLabelSize(0.1);
  ratiodeb -> GetYaxis() -> SetTitleSize(0.15);
  ratiodeb -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiodeb -> GetYaxis() -> SetTitleOffset(0.3);
  
  c1->cd ();
  TPad pad12( "pad12" ,"pad12" ,0 ,0.0 ,1 ,0.3);
  pad12.Draw();
  pad12.cd();
  ratiodeb->Draw( "pe" );
  
  pad11.SetBottomMargin (0);
  pad12.SetTopMargin(0);
  pad12.SetBottomMargin(0.3);
    
  TLine line1 (-0.01 ,1 ,0.01,1);
  line1.SetLineColor ( kBlack );
  line1.SetLineStyle(2);
  line1.SetLineWidth (2);
  line1.Draw ( " same " );
  
  // Save canvas to file
  c1->SaveAs("dEtaInEB.png");
  c1->Write();
  // Clean up
  delete deb;
  delete demcb;
  delete ratiodeb;
  delete c1;

  
  TCanvas* c2 = new TCanvas("", "dphiinec", 800, 700);
  c2->SetBottomMargin(0.5);
  // Draw histograms
  deec->SetMarkerStyle(20); // Set marker style for data
  deec->SetMarkerSize(1.2); // Set marker size for data
  deec->SetLineColor(kBlack); // Set line color for data
  demcec->SetFillColor(kAzure+6); // Set fill color for MC
  demcec->SetLineColor(kBlue); // Set line color for MC
  demcec->SetFillStyle(1001); // Set fill style for MC
  demcec -> SetTitle( "" );
  demcec -> GetXaxis() -> SetLabelSize(0);
  demcec -> GetXaxis() -> SetTitleSize(0);
  demcec -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  deec->GetYaxis()->SetTitle("Events");
  demcec->GetYaxis()->SetTitle("Events");
  deec->GetYaxis()->SetTitleOffset(0.8);
  demcec->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad21 ( " pad21 " ," pad21 " ,0 ,0.3 ,1 ,1);
  pad21.SetLogy( true );
  pad21.Draw();
  pad21.cd();
  demcec -> Draw( " h " );
  deec-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiodeec = new TH1F("ratiodeec", "Data/MC Ratio", 40, -0.01, 0.01); // Change binning as needed
  
  ratiodeec = (TH1F*)deec->Clone();
  ratiodeec->Divide(demcec);
  // Fill ratio histogram
  // for (int bin = 1; bin <= deec->GetNbinsX(); ++bin) {
  //   double dataBinContent = deec->GetBinContent(bin);
  //   double mcBinContent = demcec->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiodeec->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l2 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l2->SetBorderSize(0);
  l2->SetHeader("Endcap");
  l2->AddEntry(deec, "Data", "lep"); // Add entry for data
  l2->AddEntry(demcec, "Z->ee(MC)", "f"); // Add entry for MC
  l2->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiodeec->SetMarkerStyle(20); // Set marker style
  ratiodeec->SetMarkerSize(1.2); // Set marker size
  ratiodeec->SetLineColor(kBlack); // Set line color
  ratiodeec -> SetTitle( "" );
  ratiodeec -> GetXaxis() -> SetTitle("#Delta#eta_{in}");  
  ratiodeec -> GetXaxis() -> SetTitleOffset(0.8);
  ratiodeec -> GetXaxis() -> SetLabelSize(0.12);
  ratiodeec -> GetXaxis() -> SetMaxDigits(2);
  ratiodeec -> GetXaxis() -> SetTitleSize(0.15);
  ratiodeec -> GetYaxis() -> SetLabelSize(0.1);
  ratiodeec -> GetYaxis() -> SetTitleSize(0.15);
  ratiodeec -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiodeec -> GetYaxis() -> SetTitleOffset(0.3);
  
  c2->cd ();
  TPad pad22( "pad22" ,"pad22" ,0 ,0.0 ,1 ,0.3);
  pad22.Draw();
  pad22.cd();
  ratiodeec->Draw( "pe" );
  
  pad21.SetBottomMargin (0);
  pad22.SetTopMargin(0);
  pad22.SetBottomMargin(0.3);
    
  TLine line2 (-0.01 ,1 ,0.01,1);
  line2.SetLineColor ( kBlack );
  line2.SetLineStyle(2);
  line2.SetLineWidth (2);
  line2.Draw ( " same " );
  
  // Save canvas to file
  c2->SaveAs("dEtaInEC.png");
  c2->Write();
  // Clean up
  delete deec;
  delete demcec;
  delete ratiodeec;
  delete c2;
  
  TCanvas* c3 = new TCanvas("", "dphiinb", 800, 700);
  c3->SetBottomMargin(0.5);
  // Draw histograms
  dphb->SetMarkerStyle(20); // Set marker style for data
  dphb->SetMarkerSize(1.2); // Set marker size for data
  dphb->SetLineColor(kBlack); // Set line color for data
  dphmcb->SetFillColor(kGreen-7); // Set fill color for MC
  dphmcb->SetLineColor(kGreen+2); // Set line color for MC
  dphmcb->SetFillStyle(1001); // Set fill style for MC
  dphmcb -> SetTitle( "" );
  dphmcb -> GetXaxis() -> SetLabelSize(0);
  dphmcb -> GetXaxis() -> SetTitleSize(0);
  dphmcb -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  dphb->GetYaxis()->SetTitle("Events");
  dphmcb->GetYaxis()->SetTitle("Events");
  dphb->GetYaxis()->SetTitleOffset(0.8);
  dphmcb->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad31 ( " pad31 " ," pad31 " ,0 ,0.3 ,1 ,1);
  pad31.SetLogy( true );
  pad31.Draw();
  pad31.cd();
  dphmcb -> Draw( " h " );
  dphb-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiodphb = new TH1F("ratiodphb", "Data/MC Ratio", 40, -0.045, 0.045); // Change binning as needed
  
  ratiodphb = (TH1F*)dphb->Clone();
  ratiodphb->Divide(dphmcb);
  // Fill ratio histogram
  // for (int bin = 1; bin <= dphb->GetNbinsX(); ++bin) {
  //   double dataBinContent = dphb->GetBinContent(bin);
  //   double mcBinContent = dphmcb->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiodphb->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l3 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l3->SetBorderSize(0);
  l3->SetHeader("Barrel");
  l3->AddEntry(dphb, "Data", "lep"); // Add entry for data
  l3->AddEntry(dphmcb, "Z->ee(MC)", "f"); // Add entry for MC
  l3->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiodphb->SetMarkerStyle(20); // Set marker style
  ratiodphb->SetMarkerSize(1.2); // Set marker size
  ratiodphb->SetLineColor(kBlack); // Set line color
  ratiodphb -> SetTitle( "" );
  ratiodphb -> GetXaxis() -> SetTitle("#Delta#phi_{in} in rad");  
  ratiodphb -> GetXaxis() -> SetTitleOffset(0.8);
  ratiodphb -> GetXaxis() -> SetLabelSize(0.12);
  ratiodphb -> GetXaxis() -> SetTitleSize(0.15);
  ratiodphb -> GetYaxis() -> SetLabelSize(0.1);
  ratiodphb -> GetYaxis() -> SetTitleSize(0.15);
  ratiodphb -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiodphb -> GetYaxis() -> SetTitleOffset(0.3);
  
  c3->cd ();
  TPad pad32( "pad32" ,"pad32" ,0 ,0.0 ,1 ,0.3);
  pad32.Draw();
  pad32.cd();
  ratiodphb->Draw( "pe" );
  
  pad31.SetBottomMargin (0);
  pad32.SetTopMargin(0);
  pad32.SetBottomMargin(0.3);
    
  TLine line3 (-0.045 ,1 ,0.045,1);
  line3.SetLineColor ( kBlack );
  line3.SetLineStyle(2);
  line3.SetLineWidth (2);
  line3.Draw ( " same " );
  
  // Save canvas to file
  c3->SaveAs("dPhiInEB.png");
  c3->Write();
  // Clean up
  delete dphb;
  delete dphmcb;
  delete ratiodphb;
  delete c3;

  
  TCanvas* c4 = new TCanvas("", "dphiinec", 800, 700);
  c4->SetBottomMargin(0.5);
  // Draw histograms
  dphec->SetMarkerStyle(20); // Set marker style for data
  dphec->SetMarkerSize(1.2); // Set marker size for data
  dphec->SetLineColor(kBlack); // Set line color for data
  dphmcec->SetFillColor(kGreen-7); // Set fill color for MC
  dphmcec->SetLineColor(kGreen+2); // Set line color for MC
  dphmcec->SetFillStyle(1001); // Set fill style for MC
  dphmcec -> SetTitle( "" );
  dphmcec -> GetXaxis() -> SetLabelSize(0);
  dphmcec -> GetXaxis() -> SetTitleSize(0);
  dphmcec -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  dphec->GetYaxis()->SetTitle("Events");
  dphmcec->GetYaxis()->SetTitle("Events");
  dphec->GetYaxis()->SetTitleOffset(0.8);
  dphmcec->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad41 ( " pad41 " ," pad41 " ,0 ,0.3 ,1 ,1);
  pad41.SetLogy( true );
  pad41.Draw();
  pad41.cd();
  dphmcec -> Draw( " h " );
  dphec-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiodphec = new TH1F("ratiodphec", "Data/MC Ratio", 40, -0.1, 0.1); // Change binning as needed
  
  ratiodphec = (TH1F*)dphec->Clone();
  ratiodphec->Divide(dphmcec);
  // Fill ratio histogram
  // for (int bin = 1; bin <= dphec->GetNbinsX(); ++bin) {
  //   double dataBinContent = dphec->GetBinContent(bin);
  //   double mcBinContent = dphmcec->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiodphec->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l4 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l4->SetBorderSize(0);
  l4->SetHeader("Endcap");
  l4->AddEntry(dphec, "Data", "lep"); // Add entry for data
  l4->AddEntry(dphmcec, "Z->ee(MC)", "f"); // Add entry for MC
  l4->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiodphec->SetMarkerStyle(20); // Set marker style
  ratiodphec->SetMarkerSize(1.2); // Set marker size
  ratiodphec->SetLineColor(kBlack); // Set line color
  ratiodphec -> SetTitle( "" );
  ratiodphec -> GetXaxis() -> SetTitle("#Delta#phi_{in} in rad ");
  ratiodphec -> GetXaxis() -> SetTitleOffset(0.8);
  ratiodphec -> GetXaxis() -> SetLabelSize(0.12);
  ratiodphec -> GetXaxis() -> SetTitleSize(0.15);
  ratiodphec -> GetYaxis() -> SetLabelSize(0.1);
  ratiodphec -> GetYaxis() -> SetTitleSize(0.15);
  ratiodphec -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiodphec -> GetYaxis() -> SetTitleOffset(0.3);
  
  c4->cd ();
  TPad pad42( "pad42" ,"pad42" ,0 ,0.0 ,1 ,0.3);
  pad42.Draw();
  pad42.cd();
  ratiodphec->Draw( "pe" );
  
  pad41.SetBottomMargin (0);
  pad42.SetTopMargin(0);
  pad42.SetBottomMargin(0.3);
    
  TLine line4 (-0.1 ,1 ,0.1,1);
  line4.SetLineColor ( kBlack );
  line4.SetLineStyle(2);
  line4.SetLineWidth (2);
  line4.Draw ( " same " );
  
  // Save canvas to file
  c4->SaveAs("dPhiInEC.png");
  c4->Write();
  // Clean up
  delete dphec;
  delete dphmcec;
  delete ratiodphec;
  delete c4;

  TCanvas* c5 = new TCanvas("", "hovereb", 800, 700);
  c5->SetBottomMargin(0.5);
  // Draw histograms
  heb->SetMarkerStyle(20); // Set marker style for data
  heb->SetMarkerSize(1.2); // Set marker size for data
  heb->SetLineColor(kBlack); // Set line color for data
  hemcb->SetFillColor(kOrange-2); // Set fill color for MC
  hemcb->SetLineColor(kOrange+5); // Set line color for MC
  hemcb->SetFillStyle(1001); // Set fill style for MC
  hemcb -> SetTitle( "" );
  hemcb -> GetXaxis() -> SetLabelSize(0);
  hemcb -> GetXaxis() -> SetTitleSize(0);
  hemcb -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  heb->GetYaxis()->SetTitle("Events");
  hemcb->GetYaxis()->SetTitle("Events");
  heb->GetYaxis()->SetTitleOffset(0.8);
  hemcb->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad51 ( " pad11 " ," pad11 " ,0 ,0.3 ,1 ,1);
  pad51.SetLogy( true );
  pad51.Draw();
  pad51.cd();
  hemcb -> Draw( " h " );
  heb-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratioheb = new TH1F("ratioheb", "Data/MC Ratio", 40, 0.0, 0.065); // Change binning as needed
  
  ratioheb = (TH1F*)heb->Clone();
  ratioheb->Divide(hemcb);
  // Fill ratio histogram
  // for (int bin = 1; bin <= heb->GetNbinsX(); ++bin) {
  //   double dataBinContent = heb->GetBinContent(bin);
  //   double mcBinContent = hemcb->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratioheb->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l5 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l5->SetBorderSize(0);
  l5->SetHeader("Barrel");
  l5->AddEntry(heb, "Data", "lep"); // Add entry for data
  l5->AddEntry(hemcb, "Z->ee(MC)", "f"); // Add entry for MC
  l5->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratioheb->SetMarkerStyle(20); // Set marker style
  ratioheb->SetMarkerSize(1.2); // Set marker size
  ratioheb->SetLineColor(kBlack); // Set line color
  ratioheb -> SetTitle( "" );
  ratioheb -> GetXaxis() -> SetTitle("H/E");  
  ratioheb -> GetXaxis() -> SetTitleOffset(0.8);
  ratioheb -> GetXaxis() -> SetLabelSize(0.12);
  ratioheb -> GetXaxis() -> SetTitleSize(0.15);
  ratioheb -> GetYaxis() -> SetLabelSize(0.1);
  ratioheb -> GetYaxis() -> SetTitleSize(0.15);
  ratioheb -> GetYaxis() -> SetTitle( "Data/MC" );
  ratioheb -> GetYaxis() -> SetTitleOffset(0.3);
  
  c5->cd ();
  TPad pad52( "pad52" ,"pad52" ,0 ,0.0 ,1 ,0.3);
  pad52.Draw();
  pad52.cd();
  ratioheb->Draw( "pe" );
  
  pad51.SetBottomMargin (0);
  pad52.SetTopMargin(0);
  pad52.SetBottomMargin(0.25);
    
  TLine line5 (0.0 ,1 ,0.065,1);
  line5.SetLineColor ( kBlack );
  line5.SetLineStyle(2);
  line5.SetLineWidth (2);
  line5.Draw ( " same " );
  
  // Save canvas to file
  c5->SaveAs("HOverE_EB.png");
  c5->Write();
  // Clean up
  delete heb;
  delete hemcb;
  delete ratioheb;
  delete c5;

  
  TCanvas* c6 = new TCanvas("", "hoverec", 800, 700);
  c6->SetBottomMargin(0.5);
  // Draw histograms
  heec->SetMarkerStyle(20); // Set marker style for data
  heec->SetMarkerSize(1.2); // Set marker size for data
  heec->SetLineColor(kBlack); // Set line color for data
  hemcec->SetFillColor(kOrange-2); // Set fill color for MC
  hemcec->SetLineColor(kOrange+5); // Set line color for MC
  hemcec->SetFillStyle(1001); // Set fill style for MC
  hemcec -> SetTitle( "" );
  hemcec -> GetXaxis() -> SetLabelSize(0);
  hemcec -> GetXaxis() -> SetTitleSize(0);
  hemcec -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  heec->GetYaxis()->SetTitle("Events");
  hemcec->GetYaxis()->SetTitle("Events");
  heec->GetYaxis()->SetTitleOffset(0.8);
  hemcec->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad61 ( " pad61 " ," pad61 " ,0 ,0.3 ,1 ,1);
  pad61.SetLogy( true );
  pad61.Draw();
  pad61.cd();
  hemcec -> Draw( " h " );
  heec-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratioheec = new TH1F("ratioheec", "Data/MC Ratio", 40, 0.0, 0.065); // Change binning as needed
  
  ratioheec = (TH1F*)heec->Clone();
  ratioheec->Divide(hemcec);
  // Fill ratio histogram
  // for (int bin = 1; bin <= heec->GetNbinsX(); ++bin) {
  //   double dataBinContent = heec->GetBinContent(bin);
  //   double mcBinContent = hemcec->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratioheec->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l6 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l6->SetBorderSize(0);
  l6->SetHeader("Endcap");
  l6->AddEntry(heec, "Data", "lep"); // Add entry for data
  l6->AddEntry(hemcec, "Z->ee(MC)", "f"); // Add entry for MC
  l6->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratioheec->SetMarkerStyle(20); // Set marker style
  ratioheec->SetMarkerSize(1.2); // Set marker size
  ratioheec->SetLineColor(kBlack); // Set line color
  ratioheec -> SetTitle( "" );
  ratioheec -> GetXaxis() -> SetTitle("H/E");  
  ratioheec -> GetXaxis() -> SetTitleOffset(0.8);
  ratioheec -> GetXaxis() -> SetLabelSize(0.12);
  ratioheec -> GetXaxis() -> SetTitleSize(0.15);
  ratioheec -> GetYaxis() -> SetLabelSize(0.1);
  ratioheec -> GetYaxis() -> SetTitleSize(0.15);
  ratioheec -> GetYaxis() -> SetTitle( "Data/MC" );
  ratioheec -> GetYaxis() -> SetTitleOffset(0.3);
  
  c6->cd ();
  TPad pad62( "pad62" ,"pad62" ,0 ,0.0 ,1 ,0.3);
  pad62.Draw();
  pad62.cd();
  ratioheec->Draw( "pe" );
  
  pad61.SetBottomMargin (0);
  pad62.SetTopMargin(0);
  pad62.SetBottomMargin(0.25);
    
  TLine line6 (0.0 ,1 ,0.065,1);
  line6.SetLineColor ( kBlack );
  line6.SetLineStyle(2);
  line6.SetLineWidth (2);
  line6.Draw ( " same " );
  
  // Save canvas to file
  c6->SaveAs("HOverE_EC.png");
  c6->Write();
  // Clean up
  delete heec;
  delete hemcec;
  delete ratioheec;
  delete c6;
  
  TCanvas* c7 = new TCanvas("", "full5x5sigietaietab", 800, 700);
  c7->SetBottomMargin(0.5);
  // Draw histograms
  sigb->SetMarkerStyle(20); // Set marker style for data
  sigb->SetMarkerSize(1.2); // Set marker size for data
  sigb->SetLineColor(kBlack); // Set line color for data
  sigmcb->SetFillColor(kRed-9); // Set fill color for MC
  sigmcb->SetLineColor(kRed-3); // Set line color for MC
  sigmcb->SetFillStyle(1001); // Set fill style for MC
  sigmcb -> SetTitle( "" );
  sigmcb -> GetXaxis() -> SetLabelSize(0);
  sigmcb -> GetXaxis() -> SetTitleSize(0);
  sigmcb -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  sigb->GetYaxis()->SetTitle("Events");
  sigmcb->GetYaxis()->SetTitle("Events");
  sigb->GetYaxis()->SetTitleOffset(0.8);
  sigmcb->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad71 ( " pad71 " ," pad71 " ,0 ,0.3 ,1 ,1);
  pad71.SetLogy( true );
  pad71.Draw();
  pad71.cd();
  sigmcb -> Draw( " h " );
  sigb-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiosigb = new TH1F("ratiosigb", "Data/MC Ratio", 40, 5.e-3, 10.5e-3); // Change binning as needed
  
  ratiosigb = (TH1F*)sigb->Clone();
  ratiosigb->Divide(sigmcb);
  // Fill ratio histogram
  // for (int bin = 1; bin <= sigb->GetNbinsX(); ++bin) {
  //   double dataBinContent = sigb->GetBinContent(bin);
  //   double mcBinContent = sigmcb->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiosigb->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l7 = new TLegend(); // Define legend position
  l7->SetBorderSize(0);
  l7->SetHeader("Barrel");
  l7->AddEntry(sigb, "Data", "lep"); // Add entry for data
  l7->AddEntry(sigmcb, "Z->ee(MC)", "f"); // Add entry for MC
  l7->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiosigb->SetMarkerStyle(20); // Set marker style
  ratiosigb->SetMarkerSize(1.2); // Set marker size
  ratiosigb->SetLineColor(kBlack); // Set line color
  ratiosigb -> SetTitle( "" );
  ratiosigb -> GetXaxis() -> SetTitle("#sigma_{i#etai#eta}");  
  ratiosigb -> GetXaxis() -> SetTitleOffset(0.8);
  ratiosigb -> GetXaxis() -> SetLabelSize(0.1);
  ratiosigb -> GetXaxis() -> SetMaxDigits(2);
  ratiosigb -> GetXaxis() -> SetTitleSize(0.15);
  ratiosigb -> GetYaxis() -> SetLabelSize(0.1);
  ratiosigb -> GetYaxis() -> SetTitleSize(0.15);
  ratiosigb -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiosigb -> GetYaxis() -> SetTitleOffset(0.3);
  
  c7->cd ();
  TPad pad72( "pad72" ,"pad72" ,0 ,0.0 ,1 ,0.3);
  pad72.Draw();
  pad72.cd();
  ratiosigb->Draw( "pe" );
  
  pad71.SetBottomMargin (0);
  pad72.SetTopMargin(0);
  pad72.SetBottomMargin(0.25);
    
  TLine line7 (5.e-3, 1, 10.5e-3, 1);
  line7.SetLineColor ( kBlack );
  line7.SetLineStyle(2);
  line7.SetLineWidth (2);
  line7.Draw ( " same " );
  
  // Save canvas to file
  c7->SaveAs("full5x5_sigma_ietaieta_EB.png");
  c7->Write();
  // Clean up
  delete sigb;
  delete sigmcb;
  delete ratiosigb;
  delete c7;

  
  TCanvas* c8 = new TCanvas("", "full5x5sigietaietaec", 800, 700);
  c8->SetBottomMargin(0.5);
  // Draw histograms
  sigec->SetMarkerStyle(20); // Set marker style for data
  sigec->SetMarkerSize(1.2); // Set marker size for data
  sigec->SetLineColor(kBlack); // Set line color for data
  sigmcec->SetFillColor(kRed-9); // Set fill color for MC
  sigmcec->SetLineColor(kRed-3); // Set line color for MC
  sigmcec->SetFillStyle(1001); // Set fill style for MC
  sigmcec -> SetTitle( "" );
  sigmcec -> GetXaxis() -> SetLabelSize(0);
  sigmcec -> GetXaxis() -> SetTitleSize(0);
  sigmcec -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  sigec->GetYaxis()->SetTitle("Events");
  sigmcec->GetYaxis()->SetTitle("Events");
  sigec->GetYaxis()->SetTitleOffset(0.8);
  sigmcec->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad81 ( " pad81 " ," pad81 " ,0 ,0.3 ,1 ,1);
  pad81.SetLogy( true );
  pad81.Draw();
  pad81.cd();
  sigmcec -> Draw( " h " );
  sigec-> Draw( " pe , same " );
    
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiosigec = new TH1F("ratiosigec", "Data/MC Ratio", 40, 15.e-3, 30.e-3); // Change binning as needed
  
  ratiosigec = (TH1F*)sigec->Clone();
  ratiosigec->Divide(sigmcec);
  // // Fill ratio histogram
  // for (int bin = 1; bin <= sigec->GetNbinsX(); ++bin) {
  //   double dataBinContent = sigec->GetBinContent(bin);
  //   double mcBinContent = sigmcec->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiosigec->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l8 = new TLegend(); // Define legend position
  l8->SetBorderSize(0);
  l8->SetHeader("Endcap");
  l8->AddEntry(sigec, "Data", "lep"); // Add entry for data
  l8->AddEntry(sigmcec, "Z->ee(MC)", "f"); // Add entry for MC
  l8->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiosigec->SetMarkerStyle(20); // Set marker style
  ratiosigec->SetMarkerSize(1.2); // Set marker size
  ratiosigec->SetLineColor(kBlack); // Set line color
  ratiosigec -> SetTitle( "" );
  ratiosigec -> GetXaxis() -> SetTitle("#sigma_{i#etai#eta}");  
  ratiosigec -> GetXaxis() -> SetTitleOffset(0.8);
  ratiosigec -> GetXaxis() -> SetLabelSize(0.1);
  ratiosigec -> GetXaxis() -> SetMaxDigits(2);
  ratiosigec -> GetXaxis() -> SetTitleSize(0.15);
  ratiosigec -> GetYaxis() -> SetLabelSize(0.1);
  ratiosigec -> GetYaxis() -> SetTitleSize(0.15);
  ratiosigec -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiosigec -> GetYaxis() -> SetTitleOffset(0.3);
  
  c8->cd ();
  TPad pad82( "pad82" ,"pad82" ,0 ,0.0 ,1 ,0.3);
  pad82.Draw();
  pad82.cd();
  ratiosigec->Draw( "pe" );
  
  pad81.SetBottomMargin (0);
  pad82.SetTopMargin(0);
  pad82.SetBottomMargin(0.25);
    
  TLine line8 (15.e-3, 1, 30.e-3, 1);
  line8.SetLineColor ( kBlack );
  line8.SetLineStyle(2);
  line8.SetLineWidth (2);
  line8.Draw ( " same " );
  
  // Save canvas to file
  c8->SaveAs("full5x5_sigma_ietaieta_EC.png");
  c8->Write();
  // Clean up
  delete sigec;
  delete sigmcec;
  delete ratiosigec;
  delete c8;

  TCanvas* c9 = new TCanvas("", "relcombisoweab", 800, 700);
  c9->SetBottomMargin(0.5);
  // Draw histograms
  relb->SetMarkerStyle(20); // Set marker style for data
  relb->SetMarkerSize(1.2); // Set marker size for data
  relb->SetLineColor(kBlack); // Set line color for data
  relmcb->SetFillColor(kYellow-9); // Set fill color for MC
  relmcb->SetLineColor(kYellow+3); // Set line color for MC
  relmcb->SetFillStyle(1001); // Set fill style for MC
  relmcb -> SetTitle( "" );
  relmcb -> GetXaxis() -> SetLabelSize(0);
  relmcb -> GetXaxis() -> SetTitleSize(0);
  relmcb -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  relb->GetYaxis()->SetTitle("Events");
  relmcb->GetYaxis()->SetTitle("Events");
  relb->GetYaxis()->SetTitleOffset(0.8);
  relmcb->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad91 ( " pad11 " ," pad11 " ,0 ,0.3 ,1 ,1);
  pad91.SetLogy( true );
  pad91.Draw();
  pad91.cd();
  relmcb -> Draw( " h " );
  relb-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiorelb = new TH1F("ratiorelb", "Data/MC Ratio", 40, 0.0, 0.037); // Change binning as needed
  
  ratiorelb = (TH1F*)relb->Clone();
  ratiorelb->Divide(relmcb);
  // Fill ratio histogram
  // for (int bin = 1; bin <= relb->GetNbinsX(); ++bin) {
  //   double dataBinContent = relb->GetBinContent(bin);
  //   double mcBinContent = relmcb->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiorelb->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l9 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l9->SetBorderSize(0);
  l9->SetHeader("Barrel");
  l9->AddEntry(relb, "Data", "lep"); // Add entry for data
  l9->AddEntry(relmcb, "Z->ee(MC)", "f"); // Add entry for MC
  l9->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiorelb->SetMarkerStyle(20); // Set marker style
  ratiorelb->SetMarkerSize(1.2); // Set marker size
  ratiorelb->SetLineColor(kBlack); // Set line color
  ratiorelb -> SetTitle( "" );
  ratiorelb -> GetXaxis() -> SetTitle("Rel_Comb_Iso_wEA");  
  ratiorelb -> GetXaxis() -> SetTitleOffset(0.8);
  ratiorelb -> GetXaxis() -> SetLabelSize(0.12);
  ratiorelb -> GetXaxis() -> SetTitleSize(0.15);
  ratiorelb -> GetXaxis() -> SetMaxDigits(2);
  ratiorelb -> GetYaxis() -> SetLabelSize(0.1);
  ratiorelb -> GetYaxis() -> SetTitleSize(0.15);
  ratiorelb -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiorelb -> GetYaxis() -> SetTitleOffset(0.3);
  
  c9->cd ();
  TPad pad92( "pad92" ,"pad92" ,0 ,0.0 ,1 ,0.3);
  pad92.Draw();
  pad92.cd();
  ratiorelb->Draw( "pe" );
  
  pad91.SetBottomMargin (0);
  pad92.SetTopMargin(0);
  pad92.SetBottomMargin(0.25);
    
  TLine line9 (0.0 ,1 ,0.037,1);
  line9.SetLineColor ( kBlack );
  line9.SetLineStyle(2);
  line9.SetLineWidth (2);
  line9.Draw ( " same " );
  
  // Save canvas to file
  c9->SaveAs("rel_CombIsoWEA_EB.png");
  c9->Write();
  // Clean up
  delete relb;
  delete relmcb;
  delete ratiorelb;
  delete c9;

  
  TCanvas* c10 = new TCanvas("", "relcombisoweec", 800, 700);
  c10->SetBottomMargin(0.5);
  // Draw histograms
  relec->SetMarkerStyle(20); // Set marker style for data
  relec->SetMarkerSize(1.2); // Set marker size for data
  relec->SetLineColor(kBlack); // Set line color for data
  relmcec->SetFillColor(kYellow-9); // Set fill color for MC
  relmcec->SetLineColor(kYellow+3); // Set line color for MC
  relmcec->SetFillStyle(1001); // Set fill style for MC
  relmcec -> SetTitle( "" );
  relmcec -> GetXaxis() -> SetLabelSize(0);
  relmcec -> GetXaxis() -> SetTitleSize(0);
  relmcec -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  relec->GetYaxis()->SetTitle("Events");
  relmcec->GetYaxis()->SetTitle("Events");
  relec->GetYaxis()->SetTitleOffset(0.8);
  relmcec->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad101 ( " pad101 " ," pad101 " ,0 ,0.3 ,1 ,1);
  pad101.SetLogy( true );
  pad101.Draw();
  pad101.cd();
  relmcec -> Draw( " h " );
  relec-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratiorelec = new TH1F("ratiorelec", "Data/MC Ratio", 40, 0.0, 0.07); // Change binning as needed
  
  ratiorelec = (TH1F*)relec->Clone();
  ratiorelec->Divide(relmcec);
  // Fill ratio histogram
  // for (int bin = 1; bin <= relec->GetNbinsX(); ++bin) {
  //   double dataBinContent = relec->GetBinContent(bin);
  //   double mcBinContent = relmcec->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratiorelec->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l10 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l10->SetBorderSize(0);
  l10->SetHeader("Endcap");
  l10->AddEntry(relec, "Data", "lep"); // Add entry for data
  l10->AddEntry(relmcec, "Z->ee(MC)", "f"); // Add entry for MC
  l10->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratiorelec->SetMarkerStyle(20); // Set marker style
  ratiorelec->SetMarkerSize(1.2); // Set marker size
  ratiorelec->SetLineColor(kBlack); // Set line color
  ratiorelec -> SetTitle( "" );
  ratiorelec -> GetXaxis() -> SetTitle("Rel_Comb_Iso_wEA");  
  ratiorelec -> GetXaxis() -> SetTitleOffset(0.8);
  ratiorelec -> GetXaxis() -> SetLabelSize(0.12);
  ratiorelec -> GetXaxis() -> SetMaxDigits(2);
  ratiorelec -> GetXaxis() -> SetTitleSize(0.15);
  ratiorelec -> GetYaxis() -> SetLabelSize(0.1);
  ratiorelec -> GetYaxis() -> SetTitleSize(0.15);
  ratiorelec -> GetYaxis() -> SetTitle( "Data/MC" );
  ratiorelec -> GetYaxis() -> SetTitleOffset(0.3);
  
  c10->cd ();
  TPad pad102( "pad102" ,"pad102" ,0 ,0.0 ,1 ,0.3);
  pad102.Draw();
  pad102.cd();
  ratiorelec->Draw( "pe" );
  
  pad101.SetBottomMargin (0);
  pad102.SetTopMargin(0);
  pad102.SetBottomMargin(0.25);
    
  TLine line10 (0.0 ,1 ,0.07,1);
  line10.SetLineColor ( kBlack );
  line10.SetLineStyle(2);
  line10.SetLineWidth (2);
  line10.Draw ( " same " );
  
  // Save canvas to file
  c10->SaveAs("rel_CombIsoWEA_EC.png");
  c10->Write();
  // Clean up
  delete relec;
  delete relmcec;
  delete ratiorelec;
  delete c10;

  TCanvas* c11 = new TCanvas("", "ooEmooP", 800, 700);
  c11->SetBottomMargin(0.5);
  // Draw histograms
  empb->SetMarkerStyle(20); // Set marker style for data
  empb->SetMarkerSize(1.2); // Set marker size for data
  empb->SetLineColor(kBlack); // Set line color for data
  empmcb->SetFillColor(kMagenta-9); // Set fill color for MC
  empmcb->SetLineColor(kMagenta-3); // Set line color for MC
  empmcb->SetFillStyle(1001); // Set fill style for MC
  empmcb -> SetTitle( "" );
  empmcb -> GetXaxis() -> SetLabelSize(0);
  empmcb -> GetXaxis() -> SetTitleSize(0);
  empmcb -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  empb->GetYaxis()->SetTitle("Events");
  empmcb->GetYaxis()->SetTitle("Events");
  empb->GetYaxis()->SetTitleOffset(0.8);
  empmcb->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad111 ( " pad11 " ," pad11 " ,0 ,0.3 ,1 ,1);
  pad111.SetLogy( true );
  pad111.Draw();
  pad111.cd();
  empmcb -> Draw( " h " );
  empb-> Draw( " pe , same " );
  
  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratioempb = new TH1F("ratioempb", "Data/MC Ratio", 40, 0.0, 0.013); // Change binning as needed
  
  ratioempb = (TH1F*)empb->Clone();
  ratioempb->Divide(empmcb);
  // Fill ratio histogram
  // for (int bin = 1; bin <= empb->GetNbinsX(); ++bin) {
  //   double dataBinContent = empb->GetBinContent(bin);
  //   double mcBinContent = empmcb->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratioempb->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l11 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l11->SetBorderSize(0);
  l11->SetHeader("Barrel");
  l11->AddEntry(empb, "Data", "lep"); // Add entry for data
  l11->AddEntry(empmcb, "Z->ee(MC)", "f"); // Add entry for MC
  l11->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratioempb->SetMarkerStyle(20); // Set marker style
  ratioempb->SetMarkerSize(1.2); // Set marker size
  ratioempb->SetLineColor(kBlack); // Set line color
  ratioempb -> SetTitle( "" );
  ratioempb -> GetXaxis() -> SetTitle("|1/E-1/P|");  
  ratioempb -> GetXaxis() -> SetTitleOffset(0.8);
  ratioempb -> GetXaxis() -> SetLabelSize(0.12);
  ratioempb -> GetXaxis() -> SetMaxDigits(2);
  ratioempb -> GetXaxis() -> SetTitleSize(0.15);
  ratioempb -> GetYaxis() -> SetLabelSize(0.1);
  ratioempb -> GetYaxis() -> SetTitleSize(0.15);
  ratioempb -> GetYaxis() -> SetTitle( "Data/MC" );
  ratioempb -> GetYaxis() -> SetTitleOffset(0.3);
  
  c11->cd ();
  TPad pad112( "pad112" ,"pad112" ,0 ,0.0 ,1 ,0.3);
  pad112.Draw();
  pad112.cd();
  ratioempb->Draw( "pe" );
  
  pad111.SetBottomMargin (0);
  pad112.SetTopMargin(0);
  pad112.SetBottomMargin(0.25);
    
  TLine line11 (0.0 ,1 ,0.013,1);
  line11.SetLineColor ( kBlack );
  line11.SetLineStyle(2);
  line11.SetLineWidth (2);
  line11.Draw ( " same " );
  
  // Save canvas to file
  c11->SaveAs("ooEmooP_EB.png");
  c11->Write();
  // Clean up
  delete empb;
  delete empmcb;
  delete ratioempb;
  delete c11;

  
  TCanvas* c12 = new TCanvas("", "hoverec", 800, 700);
  c12->SetBottomMargin(0.5);
  // Draw histograms
  empec->SetMarkerStyle(20); // Set marker style for data
  empec->SetMarkerSize(1.2); // Set marker size for data
  empec->SetLineColor(kBlack); // Set line color for data
  empmcec->SetFillColor(kMagenta-9); // Set fill color for MC
  empmcec->SetLineColor(kMagenta-3); // Set line color for MC
  empmcec->SetFillStyle(1001); // Set fill style for MC
  empmcec -> SetTitle( "" );
  empmcec -> GetXaxis() -> SetLabelSize(0);
  empmcec -> GetXaxis() -> SetTitleSize(0);
  empmcec -> GetYaxis() -> SetTitleSize(0.05);
  
  // Adjust axes
  empec->GetYaxis()->SetTitle("Events");
  empmcec->GetYaxis()->SetTitle("Events");
  empec->GetYaxis()->SetTitleOffset(0.8);
  empmcec->GetYaxis()->SetTitleOffset(0.8);
  
  
  TPad pad121 ( " pad121 " ," pad121 " ,0 ,0.3 ,1 ,1);
  pad121.SetLogy( true );
  pad121.Draw();
  pad121.cd();
  empmcec -> Draw( " h " );
  empec-> Draw( " pe , same " );

  pt1->Draw("same");
  
  // Create ratio histogram
  TH1F* ratioempec = new TH1F("ratioempec", "Data/MC Ratio", 40, 0.0, 0.013); // Change binning as needed
  
  ratioempec = (TH1F*)empec->Clone();
  ratioempec->Divide(empmcec);
  // Fill ratio histogram
  // for (int bin = 1; bin <= empec->GetNbinsX(); ++bin) {
  //   double dataBinContent = empec->GetBinContent(bin);
  //   double mcBinContent = empmcec->GetBinContent(bin);
  //   double ratio = (mcBinContent != 0) ? dataBinContent / mcBinContent : 0;
  //   ratioempec->SetBinContent(bin, ratio);
  // }
  
  // Add legend
  TLegend* l12 = new TLegend(0.7, 0.7, 0.85, 0.85); // Define legend position
  l12->SetBorderSize(0);
  l12->SetHeader("Endcap");
  l12->AddEntry(empec, "Data", "lep"); // Add entry for data
  l12->AddEntry(empmcec, "Z->ee(MC)", "f"); // Add entry for MC
  l12->Draw(); // Draw legend
  
  // Draw ratio histogram
  ratioempec->SetMarkerStyle(20); // Set marker style
  ratioempec->SetMarkerSize(1.2); // Set marker size
  ratioempec->SetLineColor(kBlack); // Set line color
  ratioempec -> SetTitle( "" );
  ratioempec -> GetXaxis() -> SetTitle("|1/E-1/P|");  
  ratioempec -> GetXaxis() -> SetTitleOffset(0.8);
  ratioempec -> GetXaxis() -> SetLabelSize(0.12);
  ratioempec -> GetXaxis() -> SetMaxDigits(2);
  ratioempec -> GetXaxis() -> SetTitleSize(0.15);
  ratioempec -> GetYaxis() -> SetLabelSize(0.1);
  ratioempec -> GetYaxis() -> SetTitleSize(0.15);
  ratioempec -> GetYaxis() -> SetTitle( "Data/MC" );
  ratioempec -> GetYaxis() -> SetTitleOffset(0.3);
  
  c12->cd ();
  TPad pad122( "pad122" ,"pad122" ,0 ,0.0 ,1 ,0.3);
  pad122.Draw();
  pad122.cd();
  ratioempec->Draw( "pe" );
  
  pad121.SetBottomMargin (0);
  pad122.SetTopMargin(0);
  pad122.SetBottomMargin(0.25);
    
  TLine line12 (0.0 ,1 ,0.013,1);
  line12.SetLineColor ( kBlack );
  line12.SetLineStyle(2);
  line12.SetLineWidth (2);
  line12.Draw ( " same " );
  
  // Save canvas to file
  c12->SaveAs("ooEmooP_EC.png");
  c12->Write();
  // Clean up
  delete empec;
  delete empmcec;
  delete ratioempec;
  delete c12;
  
  outputFile->Close();
  // Close the files
  file->Close();
  mcfile->Close();
}

