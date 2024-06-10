#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TString.h>
#include <TFormula.h>
#include <math.h>
#define pi (4*atan(1.0))

void zPlotter(TString filename, TString outfilename) {
  // Open the input ROOT file
  TFile *file = TFile::Open(filename);
  
  // Check if the file is open
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }
  
  // Get the tree from the file
  TTree *tree = (TTree*)file->Get("TwoElecEvents");
  
  // Create variables to store branch values
  Int_t n_elecs;
  Double_t Pt_ll, M_ll,Eta_ll;

  double probe_Ele_e, tag_Ele_e;
  double probe_sc_e, tag_sc_e;
  Double_t tag_Ele_pt, probe_Ele_pt;
  Double_t tag_Ele_eta, probe_Ele_eta;
  double probe_sc_eta, tag_sc_eta;
  Double_t tag_Ele_phi, probe_Ele_phi;
  double probe_sc_phi, tag_sc_phi;
  double probe_Ele_iso, tag_Ele_iso;
  Bool_t probe_Ele_veto, tag_Ele_veto;
  Bool_t probe_Ele_isLoose, tag_Ele_isLoose;
  Bool_t probe_Ele_isMedium, tag_Ele_isMedium;
  Bool_t tag_Ele_isTight, probe_Ele_isTight;
  Double_t tag_Ele_ch, probe_Ele_ch;
  double probe_Ele_dEtaIn, tag_Ele_dEtaIn;
  double probe_Ele_dPhiIn, tag_Ele_dPhiIn;
  double probe_Ele_hOverE, tag_Ele_hOverE;
  double probe_Ele_full5x5_sigmaIetaIeta, tag_Ele_full5x5_sigmaIetaIeta;
  double probe_Ele_isoChargedHadrons, tag_Ele_isoChargedHadrons;
  double probe_Ele_isoNeutralHadrons, tag_Ele_isoNeutralHadrons;
  double probe_Ele_isoPhotons, tag_Ele_isoPhotons;
  double probe_Ele_isoChargedFromPU, tag_Ele_isoChargedFromPU;
  double probe_Ele_relCombIsoWithEA, tag_Ele_relCombIsoWithEA;
  double probe_Ele_ooEmooP, tag_Ele_ooEmooP;
  Bool_t probe_Ele_passConversionVeto_, tag_Ele_passConversionVeto_ ;
  
  Float_t met_e,met_pt,met_phi;
  
  // Set branch addresses
  tree->SetBranchAddress("n_elecs", &n_elecs);
  tree->SetBranchAddress("Pt_ll", &Pt_ll);
  tree->SetBranchAddress("M_ll", &M_ll);
  tree->SetBranchAddress("Eta_ll", &Eta_ll);
  
  //tag branches
  tree->SetBranchAddress("tag_Ele_e", &tag_Ele_e);  
  tree->SetBranchAddress("tag_sc_e", &tag_sc_e);
  tree->SetBranchAddress("tag_Ele_pt", &tag_Ele_pt);
  tree->SetBranchAddress("tag_Ele_eta", &tag_Ele_eta);
  tree->SetBranchAddress("tag_sc_eta", &tag_sc_eta);
  tree->SetBranchAddress("tag_Ele_phi", &tag_Ele_phi);
  tree->SetBranchAddress("tag_sc_phi", &tag_sc_phi);
  tree->SetBranchAddress("tag_Ele_iso", &tag_Ele_iso);
  tree->SetBranchAddress("tag_Ele_isTight", &tag_Ele_isTight);
  tree->SetBranchAddress("tag_Ele_ch", &tag_Ele_ch);
  tree->SetBranchAddress("tag_Ele_dEtaIn", &tag_Ele_dEtaIn);
  tree->SetBranchAddress("tag_Ele_dPhiIn", &tag_Ele_dPhiIn);
  tree->SetBranchAddress("tag_Ele_hOverE", &tag_Ele_hOverE);
  tree->SetBranchAddress("tag_Ele_full5x5_sigmaIetaIeta", &tag_Ele_full5x5_sigmaIetaIeta);
  tree->SetBranchAddress("tag_Ele_isoChargedHadrons", &tag_Ele_isoChargedHadrons);
  tree->SetBranchAddress("tag_Ele_isoNeutralHadrons", &tag_Ele_isoNeutralHadrons);
  tree->SetBranchAddress("tag_Ele_isoPhotons", &tag_Ele_isoPhotons);
  tree->SetBranchAddress("tag_Ele_isoChargedFromPU", &tag_Ele_isoChargedFromPU);
  tree->SetBranchAddress("tag_Ele_relCombIsoWithEA", &tag_Ele_relCombIsoWithEA);
  tree->SetBranchAddress("tag_Ele_ooEmooP", &tag_Ele_ooEmooP);
  tree->SetBranchAddress("tag_Ele_passConversionVeto_", &tag_Ele_passConversionVeto_);

  tree->SetBranchAddress("probe_Ele_e", &probe_Ele_e);
  tree->SetBranchAddress("probe_sc_e", &probe_sc_e);
  tree->SetBranchAddress("probe_Ele_pt", &probe_Ele_pt);
  tree->SetBranchAddress("probe_Ele_eta", &probe_Ele_eta);
  tree->SetBranchAddress("probe_sc_eta", &probe_sc_eta);
  tree->SetBranchAddress("probe_Ele_phi", &probe_Ele_phi);
  tree->SetBranchAddress("probe_sc_phi", &probe_sc_phi);
  tree->SetBranchAddress("probe_Ele_iso", &probe_Ele_iso);
  tree->SetBranchAddress("probe_Ele_isTight", &probe_Ele_isTight);
  tree->SetBranchAddress("probe_Ele_ch", &probe_Ele_ch);
  tree->SetBranchAddress("probe_Ele_dEtaIn", &probe_Ele_dEtaIn);
  tree->SetBranchAddress("probe_Ele_dPhiIn", &probe_Ele_dPhiIn);
  tree->SetBranchAddress("probe_Ele_hOverE", &probe_Ele_hOverE);
  tree->SetBranchAddress("probe_Ele_full5x5_sigmaIetaIeta", &probe_Ele_full5x5_sigmaIetaIeta);
  tree->SetBranchAddress("probe_Ele_isoChargedHadrons", &probe_Ele_isoChargedHadrons);
  tree->SetBranchAddress("probe_Ele_isoNeutralHadrons", &probe_Ele_isoNeutralHadrons);
  tree->SetBranchAddress("probe_Ele_isoPhotons", &probe_Ele_isoPhotons);
  tree->SetBranchAddress("probe_Ele_isoChargedFromPU", &probe_Ele_isoChargedFromPU);
  tree->SetBranchAddress("probe_Ele_relCombIsoWithEA", &probe_Ele_relCombIsoWithEA);
  tree->SetBranchAddress("probe_Ele_ooEmooP", &probe_Ele_ooEmooP);
  tree->SetBranchAddress("probe_Ele_passConversionVeto_", &probe_Ele_passConversionVeto_);
  
  tree->SetBranchAddress("met_e", &met_e);
  tree->SetBranchAddress("met_pt", &met_pt);
  tree->SetBranchAddress("met_phi", &met_phi);
  
  
  // Create a new ROOT file for writing
  TFile *outputFile = new TFile(outfilename, "recreate");
  
  //Define pt and eta bins
  double Et_bins[7] = {10, 20, 35, 50, 100, 200, 500};
  double eta_bins[6] = {0, 0.8, 1.4, 1.6, 2.1, 2.5};
  double pt_bins[8] = {10, 20, 30, 40, 50, 60, 80, 100};
  double pt_bins2[7] = {20, 30, 40, 50, 60, 80, 100};
  double M_ll_bins[61];
  for(int m=0;m<61;m++)M_ll_bins[m]=60+m;
  TString Et_binname[7] = {"10","20","35","50","100","200","500"};
  TString eta_binname[6] = {"0","0p8","1p4","1p6","2p1","2p5"};
  TString pt_binname[8] = {"10","20","30","40","50","60","80","100"};
  
  // Create a histogram
  TH1F *pass_M = new TH1F("M_pass","M_ll Distribution",60, M_ll_bins );
  TH1F *tot_M = new TH1F("M_total","M_ll Distribution",60, M_ll_bins );;
  TH1F *pass_hist[7][5];
  TH1F *tot_hist[7][5];
  TH1F *pass_pt_hist[5];
  TH1F *pass_E_hist[5];
  TH1F *tot_pt_hist[5];
  TH1F *tot_E_hist[5]; 
  TH1F *tot_Et  = new TH1F("E_total","Et Dist", 6,Et_bins );
  TH1F *tot_pt  = new TH1F("pt_total","pt Distribution", 6,pt_bins2 );
  TH1F *tot_eta = new TH1F("eta_total","eta Distribution", 5,eta_bins );
  TH1F *tot_phi = new TH1F("phi_total","phi Distribution", 10,-pi,pi );
  TH1F *pass_Et  = new TH1F("E_pass","Et Dist", 6,Et_bins );
  TH1F *pass_pt = new TH1F("pt_pass","pt Distribution", 6,pt_bins2 );
  TH1F *pass_eta= new TH1F("eta_pass","eta Distribution", 5,eta_bins );
  TH1F *pass_phi= new TH1F("phi_pass","phi Distribution", 10,-pi,pi);

  for(int ieta = 0;ieta<5;ieta++){
    TString pt_pass_histname = "pt_eta_";
    pt_pass_histname += eta_binname[ieta] + "_" + eta_binname[ieta+1] + "_passprobe";
    TString pt_tot_histname = "pt_eta_";
    pt_tot_histname += eta_binname[ieta] + "_" + eta_binname[ieta+1] + "_totprobe";
    TString E_pass_histname = "E_eta_";
    E_pass_histname += eta_binname[ieta] + "_" + eta_binname[ieta+1] + "_passprobe";
    TString E_tot_histname = "E_eta_";
    E_tot_histname += eta_binname[ieta] + "_" + eta_binname[ieta+1] + "_totprobe";
    pass_pt_hist[ieta] = new TH1F(pt_pass_histname,"Pt Distribution", 7,pt_bins);
    tot_pt_hist[ieta] = new TH1F(pt_tot_histname,"Pt Distribution", 7,pt_bins);
    pass_E_hist[ieta] = new TH1F(E_pass_histname,"E_{T} Distribution", 6,Et_bins);
    tot_E_hist[ieta] = new TH1F(E_tot_histname,"E_{T} Distribution", 6,Et_bins);
    for(int ipt = 0;ipt<7;ipt++){
      TString pass_name = "pt_";
      pass_name += pt_binname[ipt] + "_" + pt_binname[ipt+1] + "_eta_" + eta_binname[ieta] + "_" + eta_binname[ieta+1] + "_passprobe";
      TString tot_name = "pt_";
      tot_name += pt_binname[ipt] + "_" + pt_binname[ipt+1] + "_eta_" + eta_binname[ieta] + "_" + eta_binname[ieta+1] + "_totprobe";
      
      pass_hist[ipt][ieta] = new TH1F(pass_name,"Invariant Mass Distribution", 60, M_ll_bins);
      tot_hist[ipt][ieta] = new TH1F(tot_name,"Invariant Mass Distribution", 60,  M_ll_bins);
    }
  }
  auto pass_pt_M = new TH2F("Z_Peak pass_pt-M_ll", "M_ll vs pt-passing probe", 7,pt_bins,60, M_ll_bins);
  auto pass_eta_M = new TH2F("Z_Peak pass_eta-M_ll", "M_ll vs eta-passing probe", 5,eta_bins,60, M_ll_bins);
  auto tot_pt_M = new TH2F("Z_Peak tot_pt-M_ll", "M_ll vs pt-total probe", 7,pt_bins,60, M_ll_bins);
  auto tot_eta_M = new TH2F("Z_Peak tot_eta-M_ll", "M_ll vs eta-total probe", 5,eta_bins,60, M_ll_bins);
  // Variable to store the total number of events passing the selection criteria
  Int_t totalEvents = 0;
  
  // Loop over the entries in the tree
  Long64_t nEntries = tree->GetEntries();
  for (Long64_t i = 0; i < nEntries; ++i) {
    if (i%10000==0)
      std::cout<<i/10000<<"\t";
    tree->GetEntry(i);

    TLorentzVector Met;
    Met.SetPtEtaPhiE(met_pt,0.0,met_phi,met_e);
    Double_t met_mt = Met.Mt();
    
    // Apply selection criteria. 
    if (tag_Ele_isTight == 1 &&
	tag_Ele_pt >= 35 &&
	probe_Ele_pt >= 10 &&
	( tag_Ele_ch * probe_Ele_ch) < 0 &&
	abs(tag_Ele_eta) <= 2.5 &&
	abs(probe_Ele_eta) <= 2.5 &&
	M_ll > 60 && M_ll < 120 &&
	met_pt<20.0) {
      // Fill the histogram with M_ll
      tot_Et->Fill(probe_Ele_e);
      tot_pt->Fill(probe_Ele_pt);
      tot_eta->Fill(abs(probe_Ele_eta));
      tot_phi->Fill(probe_Ele_phi);

      // if(Pt_ll>=30 && Pt_ll<=50
      // 	 && Eta_ll>=2.0 && Eta_ll<=2.5)
      tot_M->Fill(M_ll);
      
      tot_pt_M->Fill(probe_Ele_pt,M_ll);
      tot_eta_M->Fill(abs(probe_Ele_eta),M_ll);

      if(probe_Ele_isTight == 1){
	pass_pt_M->Fill(probe_Ele_pt,M_ll);
	pass_eta_M->Fill(abs(probe_Ele_eta),M_ll);
        // if(Pt_ll>=30 && Pt_ll<=50
	//  && Eta_ll>=2.0 && Eta_ll<=2.5)
	pass_M->Fill(M_ll);

	
	pass_Et->Fill(probe_Ele_e);
	pass_pt->Fill(probe_Ele_pt);
	pass_eta->Fill(abs(probe_Ele_eta));
	pass_phi->Fill(probe_Ele_phi);
      
      }
      
      // Increment the totalEvents count
      totalEvents++;
      for(int ieta = 0;ieta<5;ieta++){
	if(probe_Ele_eta>=eta_bins[ieta] && probe_Ele_eta<eta_bins[ieta+1]){
	  tot_pt_hist[ieta]->Fill(probe_Ele_pt);
	  tot_E_hist[ieta]->Fill(probe_Ele_e);
	}
	if(probe_Ele_isTight == 1){
	  pass_pt_hist[ieta]->Fill(probe_Ele_pt);
	  pass_E_hist[ieta]->Fill(probe_Ele_e);
	}
	for(int ipt = 0;ipt<7;ipt++){
	  if(probe_Ele_pt>=pt_bins[ipt] && probe_Ele_pt<pt_bins[ipt+1] &&
	     probe_Ele_eta>=eta_bins[ieta] && probe_Ele_eta<eta_bins[ieta+1]){
	    //Total probe
	    tot_hist[ipt][ieta]->Fill(M_ll);
	    //Passing probe
	    if(probe_Ele_isTight == 1)
	      pass_hist[ipt][ieta]->Fill(M_ll);
	  }
	}
      }
    }
  }
  
  // Write the histogram to the output file
  for(int ieta = 0;ieta<5;ieta++){
    tot_pt_hist[ieta]->Write();
    tot_E_hist[ieta]->Write();
    for(int ipt = 0;ipt<7;ipt++){
      tot_hist[ipt][ieta]->Write();
      pass_hist[ipt][ieta]->Write();
    }
  }
  
  tot_pt_M->SetDrawOption("lego2");
  tot_eta_M->SetDrawOption("lego2");
  pass_pt_M->SetDrawOption("lego2");
  pass_eta_M->SetDrawOption("lego2");
  
  tot_pt_M->Write();
  tot_eta_M->Write();
  pass_pt_M->Write();
  pass_eta_M->Write();

  tot_Et->Write();
  tot_pt->Write();
  tot_eta->Write();
  tot_phi->Write();
  tot_M->Write();
  pass_Et->Write();
  pass_pt->Write();
  pass_eta->Write();
  pass_phi->Write();
  pass_M->Write(); 
  
  // Close the output file
  outputFile->Close();
  
  // Close the input file
  file->Close();
}

void zPlots() {
  TString fileName = "..\\TagnProbe\\SingleElec_Run2015MiniAOD.root";
  TString MCfileName = "..\\TagnProbe\\MC_DY_M50_Run2015MiniAOD.root";
  TString outfileName = "Ztoll_M_dist.root";
  TString MCoutfileName = "MCZtoll_M_dist.root";
  zPlotter(fileName,outfileName);
  zPlotter(MCfileName,MCoutfileName);
  
}
