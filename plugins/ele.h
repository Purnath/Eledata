// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

//class to extract electron information
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
// #include "CommonTools/Egamma/interface/ConversionTools.h"
// #include "CommonTools/Egamma/interface/EffectiveAreas.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

//Transient track for impact parameter
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/IPTools/interface/IPTools.h"

//class to extract vertex information
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

//classes to save data
#include "TTree.h"
#include "TFile.h"
#include<vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

// some common header files
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Candidate/interface/Candidate.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class Eledata : public edm::one::EDAnalyzer<edm::one::SharedResources>
{
public:
  explicit Eledata(const edm::ParameterSet&);
  ~Eledata();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  
  // ----------member data --------------------------
  edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
  edm::EDGetTokenT<double> rhoToken_;
  
  // AOD case data members
  // edm::EDGetToken electronToken_;
  // edm::EDGetTokenT<reco::VertexCollection> vtxToken_;
  // edm::EDGetTokenT<reco::ConversionCollection> conversionsToken_;

  // MiniAOD case data members
  edm::EDGetToken electronsMiniAODToken_;
  // edm::EDGetTokenT<reco::VertexCollection> vtxMiniAODToken_;
  edm::EDGetTokenT<reco::ConversionCollection> conversionsMiniAODToken_;


  Float_t rho_;      // the rho variable
  
  TTree *mtree;
  int numelectron; //number of electrons in the event
  std::vector<double> ele_e;
  std::vector<double> ele_eSC;
  std::vector<double> ele_pt;
  // std::vector<double> ele_px;
  // std::vector<double> ele_py;
  // std::vector<double> ele_pz;
  std::vector<double> ele_eta;
  std::vector<double> ele_etaSC;
  std::vector<double> ele_phi;
  std::vector<double> ele_phiSC;
  std::vector<double> ele_ch;
  std::vector<double> ele_iso;
  std::vector<bool> ele_veto;//
  std::vector<bool> ele_isLoose;
  std::vector<bool> ele_isMedium;
  std::vector<bool> ele_isTight;
  // std::vector<double> ele_dxy;
  // std::vector<double> ele_dz;
  // std::vector<double> ele_dxyError;
  // std::vector<double> ele_dzError;
  std::vector<int> ele_ismvaLoose;
  std::vector<int> ele_ismvaTight;
  // std::vector<double> ele_ip3d;	
  // std::vector<double> ele_sip3d;
  
  std::vector<double> ele_dEtaIn;
  std::vector<double> ele_dPhiIn;
  std::vector<double> ele_hOverE;
  std::vector<double> ele_full5x5_sigmaIetaIeta;
  std::vector<double> ele_isoChargedHadrons;
  std::vector<double> ele_isoNeutralHadrons;
  std::vector<double> ele_isoPhotons;
  std::vector<double> ele_isoChargedFromPU;
  std::vector<double> ele_relCombIsoWithEA;
  std::vector<double> ele_ooEmooP;

  std::vector<Int_t>  ele_passConversionVeto_;     
  EffectiveAreas   effectiveAreas_;
  
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
