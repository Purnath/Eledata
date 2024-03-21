import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
from FWCore.ParameterSet.VarParsing import VarParsing
import sys

process = cms.Process("EData")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 10000

from Configuration.AlCa.GlobalTag import GlobalTag

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#---- Needed configuration for dealing with transient tracks if required
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.Services_cff')


# inputFilesAOD = cms.untracked.vstring(
#     'root://eospublic.cern.ch//eos/opendata/cms/Run2015D/SingleElectron/AOD/08Jun2016-v1/10000/0001C591-5A2E-E611-92B2-848F69FD2925.root'
# )

inputFilesMiniAOD = cms.untracked.vstring(
    'root://eospublic.cern.ch//eos/opendata/cms/Run2015D/SingleElectron/MINIAOD/08Jun2016-v1/10000/001A703B-B52E-E611-BA13-0025905A60B6.root'
)

# useAOD = False 
# if useAOD == True :
#     inputFiles = inputFilesAOD
#     outputFile = "electron_ntuple.root"
#     print("AOD input files are used")
# else :
inputFiles = inputFilesMiniAOD
outputFile = "myElectrons.root"
print("MiniAOD input files are used")

process.source = cms.Source ("PoolSource", fileNames = inputFiles ) 

process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/76X_dataRun2_16Dec2015_v0.db')
process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

# if useAOD == True :
#     dataFormat = DataFormat.AOD
# else :
dataFormat = DataFormat.MiniAOD

switchOnVIDElectronIdProducer(process, dataFormat)
# define which IDs we want to produce
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff'
]

#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)


process.elecs = cms.EDAnalyzer('Eledata',
    rho      = cms.InputTag("fixedGridRhoFastjetAll"),
    beamSpot = cms.InputTag('offlineBeamSpot'),
    #
    # Objects specific to AOD format
    #
    # electrons    = cms.InputTag("gedGsfElectrons"),
    # vertices     = cms.InputTag("offlinePrimaryVertices"),
    # conversions  = cms.InputTag('allConversions'),
    #
    # Objects specific to MiniAOD format
    #
    electronsMiniAOD= cms.InputTag("slimmedElectrons"), 
    # verticesMiniAOD = cms.InputTag("offlineSlimmedPrimaryVertices"),
    conversionsMiniAOD = cms.InputTag('reducedEgamma:reducedConversions'),
    #
    # Effective areas for computing PU correction for isolations
    effAreasConfigFile = cms.FileInPath("RecoEgamma/ElectronIdentification/data/Spring15/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_25ns.txt")
    
)

process.TFileService = cms.Service("TFileService", fileName=cms.string(outputFile))

process.p = cms.Path(process.elecs)


