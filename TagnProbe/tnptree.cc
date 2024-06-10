#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <math.h>
#include <vector>
#include <TVector3.h>
#include <TLorentzVector.h>

// Define a structure to store event variables
struct Event {
  Int_t numelectron;
  std::vector<double>* ele_e= nullptr;
  std::vector<double>* ele_eSC= nullptr;
  std::vector<double>* ele_pt= nullptr;
  std::vector<double>* ele_eta= nullptr;
  std::vector<double>* ele_etaSC= nullptr;
  std::vector<double>* ele_phi= nullptr;
  std::vector<double>* ele_phiSC= nullptr;
  std::vector<double>* ele_ch= nullptr;
  std::vector<double>* ele_iso= nullptr;
  std::vector<bool>* ele_veto= nullptr;//
  std::vector<bool>* ele_isLoose= nullptr;
  std::vector<bool>* ele_isMedium= nullptr;
  std::vector<bool>* ele_isTight= nullptr;
  std::vector<int>* ele_ismvaLoose= nullptr;
  std::vector<int>* ele_ismvaTight= nullptr;
  std::vector<double>* ele_dEtaIn= nullptr;
  std::vector<double>* ele_dPhiIn= nullptr;
  std::vector<double>* ele_hOverE= nullptr;
  std::vector<double>* ele_full5x5_sigmaIetaIeta= nullptr;
  std::vector<double>* ele_isoChargedHadrons= nullptr;
  std::vector<double>* ele_isoNeutralHadrons= nullptr;
  std::vector<double>* ele_isoPhotons= nullptr;
  std::vector<double>* ele_isoChargedFromPU= nullptr;
  std::vector<double>* ele_relCombIsoWithEA= nullptr;
  std::vector<double>* ele_ooEmooP= nullptr;
  std::vector<Int_t>*  ele_passConversionVeto_= nullptr; 

  float met_e;
  float met_pt;
  float met_px;
  float met_py;
  float met_phi;
  float met_significance;
  
  // Add more variables as needed
};

void maketnptree(TString fileName, TString outfilename) {
  // Create a structure object to store event variables
  Event event;
  // Open the ROOT file
  TFile* file = TFile::Open(fileName);
  
  // Check if the file is open
  if (!file || file->IsZombie()) {
    std::cerr << "Error opening file: " << fileName << std::endl;
    return;
  }

  // Navigate to the directory containing the TTree
  TDirectoryFile* dir = dynamic_cast<TDirectoryFile*>(file->Get("elecs"));
  if (!dir) {
    std::cerr << "Error: Directory not found!" << std::endl;
    file->Close();
    return;
  }
  
  // Get the Events tree from the file
  TTree* tree = (TTree*)dir->Get("Events");
  
  // Check if the tree exists
  if (!tree) {
    std::cerr << "Error: Tree not found in file." << std::endl;
    file->Close();
    return;
  }
  std::cout<<"Here 1"<<std::endl;
  // Set the branch addresses for the tree variables
  tree->SetBranchAddress("met_e", &event.met_e);
  tree->SetBranchAddress("met_pt", &event.met_pt);
  tree->SetBranchAddress("met_px", &event.met_px);
  tree->SetBranchAddress("met_py", &event.met_py);
  tree->SetBranchAddress("met_phi", &event.met_phi);
  tree->SetBranchAddress("met_significance", &event.met_significance);
  
  tree->SetBranchAddress("numberelectron", &event.numelectron);
  tree->SetBranchAddress("ele_e", &event.ele_e);
  tree->SetBranchAddress("ele_eSC", &event.ele_eSC);
  tree->SetBranchAddress("ele_pt", &event.ele_pt);
  tree->SetBranchAddress("ele_eta", &event.ele_eta);
  tree->SetBranchAddress("ele_etaSC", &event.ele_etaSC);
  tree->SetBranchAddress("ele_phi", &event.ele_phi);
  tree->SetBranchAddress("ele_phiSC", &event.ele_phiSC);
  tree->SetBranchAddress("ele_ch", &event.ele_ch);
  tree->SetBranchAddress("ele_iso", &event.ele_iso);
  tree->SetBranchAddress("ele_veto", &event.ele_veto);
  tree->SetBranchAddress("ele_isLoose", &event.ele_isLoose);
  tree->SetBranchAddress("ele_isMedium", &event.ele_isMedium);
  tree->SetBranchAddress("ele_isTight", &event.ele_isTight);
  tree->SetBranchAddress("ele_ismvaLoose", &event.ele_ismvaLoose);
  tree->SetBranchAddress("ele_ismvaTight", &event.ele_ismvaTight);
  tree->SetBranchAddress("ele_dEtaIn", &event.ele_dEtaIn);
  tree->SetBranchAddress("ele_dPhiIn", &event.ele_dPhiIn);
  tree->SetBranchAddress("ele_hOverE", &event.ele_hOverE);
  tree->SetBranchAddress("ele_full5x5_sigmaIetaIeta", &event.ele_full5x5_sigmaIetaIeta);
  tree->SetBranchAddress("ele_isoChargedHadrons", &event.ele_isoChargedHadrons);
  tree->SetBranchAddress("ele_isoNeutralHadrons", &event.ele_isoNeutralHadrons);
  tree->SetBranchAddress("ele_isoPhotons", &event.ele_isoPhotons);
  tree->SetBranchAddress("ele_isoChargedFromPU", &event.ele_isoChargedFromPU);
  tree->SetBranchAddress("ele_relCombIsoWithEA", &event.ele_relCombIsoWithEA);
  tree->SetBranchAddress("ele_ooEmooP", &event.ele_ooEmooP);
  tree->SetBranchAddress("ele_passConversionVeto_", &event.ele_passConversionVeto_);
  // Add more branches as needed
  
  // Create a new ROOT file for writing
  // if(isMC==1) 
  //   TString outname = "MC_DY_M50_Run2015MiniAOD.root"; 
  // else
  //   TString outname = "SingleElec_Run2015MiniAOD.root";
  //TFile* outFile = new TFile("MC_DY_M50_Run2015MiniAOD.root", "recreate");
  
  TFile* outFile = new TFile(outfilename, "recreate");
  
  // Create a new tree for the modified event variables
  TTree* newTree = new TTree("TwoElecEvents", "Tree with modified event variables");
  std::cout<<"Here 2"<<std::endl;
  // Define branches with modified names and add some new branches
  Int_t n_elecs = 0;
  float met_e = 0.0;
  float met_pt = 0.0;
  float met_px = 0.0;
  float met_py = 0.0;
  float met_phi = 0.0;
  float met_significance = 0.0;
  double probe_Ele_e = 0.0, tag_Ele_e = 0.0;
  double probe_sc_e = 0.0, tag_sc_e = 0.0;
  double probe_Ele_pt = 0.0, tag_Ele_pt = 0.0;
  double probe_Ele_eta = 0.0, tag_Ele_eta = 0.0;
  double probe_sc_eta = 0.0, tag_sc_eta = 0.0;
  double probe_Ele_phi = 0.0, tag_Ele_phi = 0.0;
  double probe_sc_phi = 0.0, tag_sc_phi = 0.0;
  double probe_Ele_ch = 0.0, tag_Ele_ch = 0.0;
  double probe_Ele_iso = 0.0, tag_Ele_iso = 0.0;
  Bool_t probe_Ele_veto = 0, tag_Ele_veto = 0;
  Bool_t probe_Ele_isLoose = 0, tag_Ele_isLoose = 0;
  Bool_t probe_Ele_isMedium = 0, tag_Ele_isMedium = 0;
  Bool_t probe_Ele_isTight = 0, tag_Ele_isTight = 0;
  Bool_t probe_Ele_ismvaLoose = 0, tag_Ele_ismvaLoose = 0;
  Bool_t probe_Ele_ismvaTight = 0, tag_Ele_ismvaTight = 0;
  double probe_Ele_dEtaIn = 0.0, tag_Ele_dEtaIn = 0.0;
  double probe_Ele_dPhiIn = 0.0, tag_Ele_dPhiIn = 0.0;
  double probe_Ele_hOverE = 0.0, tag_Ele_hOverE = 0.0;
  double probe_Ele_full5x5_sigmaIetaIeta = 0.0, tag_Ele_full5x5_sigmaIetaIeta = 0.0;
  double probe_Ele_isoChargedHadrons = 0.0, tag_Ele_isoChargedHadrons = 0.0;
  double probe_Ele_isoNeutralHadrons = 0.0, tag_Ele_isoNeutralHadrons = 0.0;
  double probe_Ele_isoPhotons = 0.0, tag_Ele_isoPhotons = 0.0;
  double probe_Ele_isoChargedFromPU = 0.0, tag_Ele_isoChargedFromPU = 0.0;
  double probe_Ele_relCombIsoWithEA = 0.0, tag_Ele_relCombIsoWithEA = 0.0;
  double probe_Ele_ooEmooP = 0.0, tag_Ele_ooEmooP = 0.0;
  Bool_t probe_Ele_passConversionVeto_, tag_Ele_passConversionVeto_ = 0;

  double Pt_ll = 0.0,E_ll = 0.0, M_ll = 0.0, Eta_ll;
  //Met Branches of newtree
  newTree->Branch("met_e",&met_e);
  newTree->Branch("met_pt",&met_pt);
  newTree->Branch("met_px",&met_px);
  newTree->Branch("met_py",&met_py);
  newTree->Branch("met_phi",&met_phi);
  newTree->Branch("met_significance",&met_significance);
  // Branches of newtree
  newTree->Branch("n_elecs", &n_elecs);
  newTree->Branch("Pt_ll",&Pt_ll);
  newTree->Branch("M_ll",&M_ll);
  newTree->Branch("E_ll",&E_ll);
  newTree->Branch("Eta_ll",&Eta_ll);
  //tag Branches of newtree
  newTree->Branch("tag_Ele_e", &tag_Ele_e);
  newTree->Branch("tag_sc_e", &tag_sc_e);
  newTree->Branch("tag_Ele_pt", &tag_Ele_pt);
  newTree->Branch("tag_Ele_eta", &tag_Ele_eta);
  newTree->Branch("tag_sc_eta", &tag_sc_eta);
  newTree->Branch("tag_Ele_phi", &tag_Ele_phi);
  newTree->Branch("tag_sc_phi", &tag_sc_phi);
  newTree->Branch("tag_Ele_ch", &tag_Ele_ch);
  newTree->Branch("tag_Ele_iso", &tag_Ele_iso);
  newTree->Branch("tag_Ele_veto", &tag_Ele_veto);
  newTree->Branch("tag_Ele_isLoose", &tag_Ele_isLoose);
  newTree->Branch("tag_Ele_isMedium", &tag_Ele_isMedium);
  newTree->Branch("tag_Ele_isTight", &tag_Ele_isTight);
  newTree->Branch("tag_Ele_ismvaLoose", &tag_Ele_ismvaLoose);
  newTree->Branch("tag_Ele_ismvaTight", &tag_Ele_ismvaTight);
  newTree->Branch("tag_Ele_dEtaIn", &tag_Ele_dEtaIn);
  newTree->Branch("tag_Ele_dPhiIn", &tag_Ele_dPhiIn);
  newTree->Branch("tag_Ele_hOverE", &tag_Ele_hOverE);
  newTree->Branch("tag_Ele_full5x5_sigmaIetaIeta", &tag_Ele_full5x5_sigmaIetaIeta);
  newTree->Branch("tag_Ele_isoChargedHadrons", &tag_Ele_isoChargedHadrons);
  newTree->Branch("tag_Ele_isoNeutralHadrons", &tag_Ele_isoNeutralHadrons);
  newTree->Branch("tag_Ele_isoPhotons", &tag_Ele_isoPhotons);
  newTree->Branch("tag_Ele_isoChargedFromPU", &tag_Ele_isoChargedFromPU);
  newTree->Branch("tag_Ele_relCombIsoWithEA", &tag_Ele_relCombIsoWithEA);
  newTree->Branch("tag_Ele_ooEmooP", &tag_Ele_ooEmooP);
  newTree->Branch("tag_Ele_passConversionVeto_", &tag_Ele_passConversionVeto_);
  //probe branches of newTree
  newTree->Branch("probe_Ele_e", &probe_Ele_e);
  newTree->Branch("probe_sc_e", &probe_sc_e);
  newTree->Branch("probe_Ele_pt", &probe_Ele_pt);
  newTree->Branch("probe_Ele_eta", &probe_Ele_eta);
  newTree->Branch("probe_sc_eta", &probe_sc_eta);
  newTree->Branch("probe_Ele_phi", &probe_Ele_phi);
  newTree->Branch("probe_sc_phi", &probe_sc_phi);
  newTree->Branch("probe_Ele_ch", &probe_Ele_ch);
  newTree->Branch("probe_Ele_iso", &probe_Ele_iso);
  newTree->Branch("probe_Ele_veto", &probe_Ele_veto);
  newTree->Branch("probe_Ele_isLoose", &probe_Ele_isLoose);
  newTree->Branch("probe_Ele_isMedium", &probe_Ele_isMedium);
  newTree->Branch("probe_Ele_isTight", &probe_Ele_isTight);
  newTree->Branch("probe_Ele_ismvaLoose", &probe_Ele_ismvaLoose);
  newTree->Branch("probe_Ele_ismvaTight", &probe_Ele_ismvaTight);
  newTree->Branch("probe_Ele_dEtaIn", &probe_Ele_dEtaIn);
  newTree->Branch("probe_Ele_dPhiIn", &probe_Ele_dPhiIn);
  newTree->Branch("probe_Ele_hOverE", &probe_Ele_hOverE);
  newTree->Branch("probe_Ele_full5x5_sigmaIetaIeta", &probe_Ele_full5x5_sigmaIetaIeta);
  newTree->Branch("probe_Ele_isoChargedHadrons", &probe_Ele_isoChargedHadrons);
  newTree->Branch("probe_Ele_isoNeutralHadrons", &probe_Ele_isoNeutralHadrons);
  newTree->Branch("probe_Ele_isoPhotons", &probe_Ele_isoPhotons);
  newTree->Branch("probe_Ele_isoChargedFromPU", &probe_Ele_isoChargedFromPU);
  newTree->Branch("probe_Ele_relCombIsoWithEA", &probe_Ele_relCombIsoWithEA);
  newTree->Branch("probe_Ele_ooEmooP", &probe_Ele_ooEmooP);
  newTree->Branch("probe_Ele_passConversionVeto_", &probe_Ele_passConversionVeto_);
  // Add more new branches as needed

  std::cout<<"Here 3"<<std::endl;
  // Loop over the entries in the original tree
  long nEntries = tree->GetEntries();
  for (long i = 0; i < nEntries; ++i) {
    if (i%10000==0)
      std::cout<<i/10000<<"\t";
    // Get the i-th entry
    tree->GetEntry(i);
    //std::cout<<i<<std::endl;
    // Only add the event to the new tree if n_elecs is exactly 2
    if (event.numelectron == 2) {
      
      // Copy n_elecs as it is
      n_elecs = event.numelectron;
      met_e = event.met_e;
      met_pt = event.met_pt;
      met_px = event.met_px;
      met_py = event.met_py;
      met_phi = event.met_phi;
      met_significance = event.met_significance;
      
      // Find the index of the higher value in ele_pt (tag_Ele_pt) and use it to determine tag_Ele_eta
      size_t tag_index = 0;
      size_t probe_index = 1;
      if ((*event.ele_pt)[1] > (*event.ele_pt)[0]) {
	tag_index = 1;
	probe_index = 0;
      }
      
      // Assign values to tag_Ele_pt, probe_Ele_pt, tag_Ele_eta, and probe_Ele_eta
      tag_Ele_e = (*event.ele_e)[tag_index];
      tag_sc_e = (*event.ele_eSC)[tag_index];
      tag_Ele_pt = (*event.ele_pt)[tag_index];
      tag_Ele_eta = (*event.ele_eta)[tag_index];
      tag_sc_eta = (*event.ele_etaSC)[tag_index];
      tag_Ele_phi = (*event.ele_phi)[tag_index];
      tag_sc_phi = (*event.ele_phiSC)[tag_index];
      tag_Ele_ch = (*event.ele_ch)[tag_index];
      tag_Ele_iso = (*event.ele_iso)[tag_index];
      tag_Ele_veto = (*event.ele_veto)[tag_index];
      tag_Ele_isLoose = (*event.ele_isLoose)[tag_index];
      tag_Ele_isMedium = (*event.ele_isMedium)[tag_index];
      tag_Ele_isTight = (*event.ele_isTight)[tag_index];
      tag_Ele_ismvaLoose = (*event.ele_ismvaLoose)[tag_index];
      tag_Ele_ismvaTight = (*event.ele_ismvaTight)[tag_index];
      tag_Ele_dEtaIn = (*event.ele_dEtaIn)[tag_index];
      tag_Ele_dPhiIn = (*event.ele_dPhiIn)[tag_index];
      tag_Ele_hOverE = (*event.ele_hOverE)[tag_index];
      tag_Ele_full5x5_sigmaIetaIeta = (*event.ele_full5x5_sigmaIetaIeta)[tag_index];
      tag_Ele_isoChargedHadrons = (*event.ele_isoChargedHadrons)[tag_index];
      tag_Ele_isoNeutralHadrons = (*event.ele_isoNeutralHadrons)[tag_index];
      tag_Ele_isoPhotons = (*event.ele_isoPhotons)[tag_index];
      tag_Ele_isoChargedFromPU = (*event.ele_isoChargedFromPU)[tag_index];
      tag_Ele_relCombIsoWithEA = (*event.ele_relCombIsoWithEA)[tag_index];
      tag_Ele_ooEmooP = (*event.ele_ooEmooP)[tag_index];
      tag_Ele_passConversionVeto_ = (*event.ele_passConversionVeto_)[tag_index];
      
      probe_Ele_e = (*event.ele_e)[probe_index];
      probe_sc_e = (*event.ele_eSC)[probe_index];
      probe_Ele_pt = (*event.ele_pt)[probe_index];
      probe_Ele_eta = (*event.ele_eta)[probe_index];
      probe_sc_eta = (*event.ele_etaSC)[probe_index];
      probe_Ele_phi = (*event.ele_phi)[probe_index];
      probe_sc_phi = (*event.ele_phiSC)[probe_index];
      probe_Ele_ch = (*event.ele_ch)[probe_index];
      probe_Ele_iso = (*event.ele_iso)[probe_index];
      probe_Ele_veto = (*event.ele_veto)[probe_index];
      probe_Ele_isLoose = (*event.ele_isLoose)[probe_index];
      probe_Ele_isMedium = (*event.ele_isMedium)[probe_index];
      probe_Ele_isTight = (*event.ele_isTight)[probe_index];
      probe_Ele_ismvaLoose = (*event.ele_ismvaLoose)[probe_index];
      probe_Ele_ismvaTight = (*event.ele_ismvaTight)[probe_index];
      probe_Ele_dEtaIn = (*event.ele_dEtaIn)[probe_index];
      probe_Ele_dPhiIn = (*event.ele_dPhiIn)[probe_index];
      probe_Ele_hOverE = (*event.ele_hOverE)[probe_index];
      probe_Ele_full5x5_sigmaIetaIeta = (*event.ele_full5x5_sigmaIetaIeta)[probe_index];
      probe_Ele_isoChargedHadrons = (*event.ele_isoChargedHadrons)[probe_index];
      probe_Ele_isoNeutralHadrons = (*event.ele_isoNeutralHadrons)[probe_index];
      probe_Ele_isoPhotons = (*event.ele_isoPhotons)[probe_index];
      probe_Ele_isoChargedFromPU = (*event.ele_isoChargedFromPU)[probe_index];
      probe_Ele_relCombIsoWithEA = (*event.ele_relCombIsoWithEA)[probe_index];
      probe_Ele_ooEmooP = (*event.ele_ooEmooP)[probe_index];
      probe_Ele_passConversionVeto_ = (*event.ele_passConversionVeto_)[probe_index];

      TLorentzVector V_t, V_p, V_ll;
      V_t.SetPtEtaPhiE(tag_Ele_pt,tag_Ele_eta,tag_Ele_phi,tag_Ele_e);
      V_p.SetPtEtaPhiE(probe_Ele_pt,probe_Ele_eta,probe_Ele_phi,probe_Ele_e);
      V_ll = V_t+V_p;
      
      Pt_ll = V_ll.Pt();
      E_ll = V_ll.E();
      Eta_ll = V_ll.Eta();
      M_ll=V_ll.M();
      // Fill the new tree with modified variables
      newTree->Fill();
    }
  }
  
  // Write the new tree to the output file
  outFile->Write();
  
  // Close the files
  outFile->Close();
  file->Close();
}

void tnptree() {
  TString fileName = "..\\myElectrons1.root";
  TString MCfileName = "..\\myMCElectrons1.root";
  TString outfileName = "SingleElec_Run2015MiniAOD.root";
  TString MCoutfileName = "MC_DY_M50_Run2015MiniAOD.root";
  maketnptree(fileName,outfileName);
  maketnptree(MCfileName,MCoutfileName);
  
}
