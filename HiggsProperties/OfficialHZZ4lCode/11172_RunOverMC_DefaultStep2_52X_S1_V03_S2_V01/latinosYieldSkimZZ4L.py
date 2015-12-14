import FWCore.ParameterSet.Config as cms

# CMSSW Regular Stuff
process = cms.Process("SKIM")

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

#Options
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#Message Logger Stuff
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 100

isMC = True
is42X = False
doEleCalibration = False # is42X ## OFF in synchronization exercises
datasetType = 'Fall11' if isMC else 'Jan16ReReco'

if is42X:
    if isMC:
        process.GlobalTag.globaltag = 'START42_V14B::All'   #for 42X MC
    else:
        process.GlobalTag.globaltag = 'GR_R_42_V25::All'  #for 42X DATA
else:
    if isMC:
        process.GlobalTag.globaltag = 'START52_V9::All'   #for 52X MC
    else:
        process.GlobalTag.globaltag = 'GR_R_52_V7::All'   #for 52X DATA


process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring('root://pcmssd12//data/mangano/MC/8TeV/hzz/reco/ggHToZZTo4L_M-120_Summer12_S7.003048678E92.root')
)
if is42X:
    if isMC: process.source.fileNames = cms.untracked.vstring('root://pcmssd12//data/gpetrucc/7TeV/hzz/aod/HToZZTo4L_M-120_Fall11S6.00215E21D5C4.root')
else:
   if isMC: process.source.fileNames = cms.untracked.vstring('file:/tmp/chenyi/FCB28165-FF95-E111-82EC-00261894387D.root')

process.out = cms.OutputModule("PoolOutputModule",
    outputCommands =  cms.untracked.vstring(),
    fileName = cms.untracked.string('/tmp/chenyi/hzz4lSkim.root')
)

# Electron calibration
if doEleCalibration :
    if not hasattr(process, 'RandomNumberGeneratorService'):
        process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService")
    process.RandomNumberGeneratorService.gsfElectrons = cms.PSet(
       initialSeed = cms.untracked.uint32(1),
       engineName = cms.untracked.string('TRandom3')
    )
    process.load("EgammaCalibratedGsfElectrons.CalibratedElectronProducers.calibratedGsfElectrons_cfi")
    process.gsfElectrons = process.calibratedGsfElectrons.clone()
    process.gsfElectrons.isMC = isMC
    process.gsfElectrons.inputDataset = datasetType
    process.gsfElectrons.updateEnergyError = cms.bool(True)
    process.gsfElectrons.isAOD = cms.bool(True)

# pat sequence
process.load("PhysicsTools.PatAlgos.patSequences_cff")
### this is necessary to avoid the conflict between PAT and RECO configurations
### see: https://hypernews.cern.ch/HyperNews/CMS/get/JetMET/1357.html
process.kt6PFJets.doRhoFastjet = True
process.kt6PFJets.doAreaFastjet = True
process.kt6PFJets.voronoiRfact = 0.9
process.kt6PFJets.Rho_EtaMax   = cms.double( 4.4)
###


from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.jetTools import *
from PhysicsTools.PatAlgos.tools.helpers import *
from PhysicsTools.PatAlgos.tools.tauTools import *
from PhysicsTools.PatAlgos.tools.trigTools import *
from PhysicsTools.PatAlgos.tools.pfTools import *

removeAllPATObjectsBut(process, ['Electrons', 'Muons', 'Photons', 'Jets'])

print "Adding back the cleaning sequence"

process.load("PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff")
process.cleanPatElectrons.checkOverlaps.muons.deltaR = 0.05
process.cleanPatPhotons.checkOverlaps.electrons.requireNoOverlaps = True
process.cleanPatJets.checkOverlaps = cms.PSet(
        muons = cms.PSet(
           src       = cms.InputTag("cleanPatMuons"),
           algorithm = cms.string("byDeltaR"),
           preselection        = cms.string(""),
           deltaR              = cms.double(0.5),
           checkRecoComponents = cms.bool(False),
           pairCut             = cms.string(""),
           requireNoOverlaps   = cms.bool(False),
        ),
        electrons = cms.PSet(
           src       = cms.InputTag("cleanPatElectrons"),
           algorithm = cms.string("byDeltaR"),
           preselection        = cms.string(""),
           deltaR              = cms.double(0.5),
           checkRecoComponents = cms.bool(False),
           pairCut             = cms.string(""),
           requireNoOverlaps   = cms.bool(False),
        ),
        photons = cms.PSet(
           src       = cms.InputTag("cleanPatPhotons"),
           algorithm = cms.string("byDeltaR"),
           preselection        = cms.string(""),
           deltaR              = cms.double(0.5),
           checkRecoComponents = cms.bool(False),
           pairCut             = cms.string(""),
           requireNoOverlaps   = cms.bool(False),
        )
)


process.cleanPatCandidateSummary.candidates = cms.VInputTag(
        cms.InputTag("cleanPatElectrons"),
        cms.InputTag("cleanPatMuons"),
        cms.InputTag("cleanPatPhotons"),
        cms.InputTag("cleanPatJets"),
)
process.cleanPatCandidates.remove(process.cleanPatTaus)

process.patDefaultSequence += process.cleanPatCandidates

print "Removing the PAT counter modules, don't need them"

process.patDefaultSequence.remove(process.countPatElectrons)
process.patDefaultSequence.remove(process.countPatMuons)
process.patDefaultSequence.remove(process.countPatPhotons)
process.patDefaultSequence.remove(process.countPatJets)

# Trigger filter
from WWAnalysis.SkimStep.triggerInformation_cff import *
addTriggerPaths(process)

process.preLeptonSequence = cms.Sequence()

process.load('WWAnalysis.SkimStep.vertexFiltering_cff')
#process.preLeptonSequence += process.firstVertexIsGood ## Not necessarily
process.preLeptonSequence += process.goodPrimaryVertices

process.load("CommonTools.ParticleFlow.pfNoPileUp_cff")
process.preLeptonSequence += process.pfNoPileUpSequence

if doEleCalibration :
    process.preLeptonSequence += process.gsfElectrons

# Rho calculations
from WWAnalysis.SkimStep.rhoCalculations_cff import addRhoVariables
addRhoVariables(process,process.preLeptonSequence)

# generator stuff
from WWAnalysis.SkimStep.generatorInformation_cff import addGeneratorInfo
if isMC: addGeneratorInfo(process,process.preLeptonSequence)

#  ______ _           _                     _____      _   _
# |  ____| |         | |                   |  __ \    | | | |
# | |__  | | ___  ___| |_ _ __ ___  _ __   | |__) |_ _| |_| |__
# |  __| | |/ _ \/ __| __| '__/ _ \| '_ \  |  ___/ _` | __| '_ \
# | |____| |  __/ (__| |_| | | (_) | | | | | |  | (_| | |_| | | |
# |______|_|\___|\___|\__|_|  \___/|_| |_| |_|   \__,_|\__|_| |_|
#

process.patElectrons.embedPFCandidate = False
process.patElectrons.embedSuperCluster = True
process.patElectrons.embedTrack = True
process.patElectrons.addElectronID = True
process.electronMatch.matched = "prunedGen"
process.patElectrons.userData.userFloats.src = cms.VInputTag(
    cms.InputTag("eleSmurfPF03"),
    cms.InputTag("eleSmurfPF04"),
    cms.InputTag("electronPFIsoChHad01"),
    cms.InputTag("electronPFIsoNHad01"),
    cms.InputTag("electronPFIsoPhoton01"),
    cms.InputTag("electronPFIsoChHad02"),
    cms.InputTag("electronPFIsoNHad02"),
    cms.InputTag("electronPFIsoPhoton02"),
    cms.InputTag("electronPFIsoChHad03"),
    cms.InputTag("electronPFIsoNHad03"),
    cms.InputTag("electronPFIsoPhoton03"),
    cms.InputTag("electronPFIsoChHad04"),
    cms.InputTag("electronPFIsoNHad04"),
    cms.InputTag("electronPFIsoPhoton04"),
    cms.InputTag("electronPFIsoChHad05"),
    cms.InputTag("electronPFIsoNHad05"),
    cms.InputTag("electronPFIsoPhoton05"),
    cms.InputTag("electronPFIsoChHadPU03"),
    cms.InputTag("electronPFIsoChHadPU04"),
    cms.InputTag("convValueMapProd","dist"),
    cms.InputTag("convValueMapProd","dcot"),
    cms.InputTag("convValueMapProd","passVtxConvert"),
    cms.InputTag("rhoEl")
)


process.load("WWAnalysis.Tools.convValueMapProd_cfi")
process.convValueMapProd.conversionLabel = "allConversions"
process.load("WWAnalysis.Tools.electronPFIsoMapProd_cfi")
process.eleSmurfPF03 = process.electronPFIsoMapProd.clone()
process.eleSmurfPF03.deltaR = 0.3
process.eleSmurfPF04 = process.electronPFIsoMapProd.clone()
process.eleSmurfPF04.deltaR = 0.4
process.load("WWAnalysis.Tools.electronEGammaPFIsoProd_cfi")
process.preElectronSequence = cms.Sequence(process.convValueMapProd + process.eleSmurfPF03 + process.eleSmurfPF04 + process.pfEGammaIsolationSingleType)
process.preElectronSequence += process.electronPFIsoChHadPU03 + process.electronPFIsoChHadPU04

#Set the Pat Electrons to use the eID
from WWAnalysis.SkimStep.electronIDs_cff import addElectronIDs
eidModules = addElectronIDs(process,process.preElectronSequence)
process.patElectrons.electronIDSources = cms.PSet()
for module in eidModules:
    setattr(process.patElectrons.electronIDSources,module.label(),cms.InputTag(module.label()))



#  __  __                     _____      _   _
# |  \/  |                   |  __ \    | | | |
# | \  / |_   _  ___  _ __   | |__) |_ _| |_| |__
# | |\/| | | | |/ _ \| '_ \  |  ___/ _` | __| '_ \
# | |  | | |_| | (_) | | | | | |  | (_| | |_| | | |
# |_|  |_|\__,_|\___/|_| |_| |_|   \__,_|\__|_| |_|
#


process.patMuons.embedPFCandidate = False
process.patMuons.embedTrack = True
process.patMuons.userData.userFloats.src = cms.VInputTag(
    cms.InputTag("muSmurfPF"),
    cms.InputTag("muonPFIsoChHad01"),
    cms.InputTag("muonPFIsoNHad01"),
    cms.InputTag("muonPFIsoPhoton01"),
    cms.InputTag("muonPFIsoChHad02"),
    cms.InputTag("muonPFIsoNHad02"),
    cms.InputTag("muonPFIsoPhoton02"),
    cms.InputTag("muonPFIsoChHad03"),
    cms.InputTag("muonPFIsoNHad03"),
    cms.InputTag("muonPFIsoPhoton03"),
    cms.InputTag("muonPFIsoChHad04"),
    cms.InputTag("muonPFIsoNHad04"),
    cms.InputTag("muonPFIsoPhoton04"),
    cms.InputTag("muonPFIsoChHad05"),
    cms.InputTag("muonPFIsoNHad05"),
    cms.InputTag("muonPFIsoPhoton05"),
    cms.InputTag("rhoMu"),
    cms.InputTag("muonPFIsoNHad03pt05"),
    cms.InputTag("muonPFIsoPhoton03pt05"),
    cms.InputTag("muonPFIsoNHad04pt05"),
    cms.InputTag("muonPFIsoPhoton04pt05"),
    cms.InputTag("muonPFIsoChHadPU03"),
    cms.InputTag("muonPFIsoChHadPU04"),
)
process.patMuons.userData.userInts.src = cms.VInputTag(
    cms.InputTag("pfMuId"),
)
process.patMuons.isolationValues = cms.PSet()
process.muonMatch.matched = "prunedGen"
process.load("WWAnalysis.Tools.muonPFIsoMapProd_cfi")
process.muSmurfPF = process.muonPFIsoMapProd.clone()
process.load("WWAnalysis.Tools.muonPFIsoProd_cfi")
process.load("WWAnalysis.Tools.pfMuId_cfi")
process.preMuonSequence = cms.Sequence(
    process.muSmurfPF +
    process.pfMuonIsolationSingleType +
    process.pfMuId
)


process.muonPFIsoPhoton03pt05 = process.muonPFIsoPhoton03.clone(neutralHadronMinPt = cms.untracked.double(0.5), photonMinPt = cms.untracked.double(0.5))
process.muonPFIsoPhoton04pt05 = process.muonPFIsoPhoton04.clone(neutralHadronMinPt = cms.untracked.double(0.5), photonMinPt = cms.untracked.double(0.5))
process.muonPFIsoNHad03pt05 = process.muonPFIsoNHad03.clone(neutralHadronMinPt = cms.untracked.double(0.5), photonMinPt = cms.untracked.double(0.5))
process.muonPFIsoNHad04pt05 = process.muonPFIsoNHad04.clone(neutralHadronMinPt = cms.untracked.double(0.5), photonMinPt = cms.untracked.double(0.5))
process.preMuonSequence += (
    process.muonPFIsoNHad03pt05 +
    process.muonPFIsoNHad04pt05 +
    process.muonPFIsoPhoton03pt05 +
    process.muonPFIsoPhoton04pt05 +
    process.muonPFIsoChHadPU03 +
    process.muonPFIsoChHadPU04
)

if not isMC:
    removeMCMatching(process)




#      _      _      _____
#     | |    | |    / ____|
#     | | ___| |_  | (___   ___  __ _ _   _  ___ _ __   ___ ___
# _   | |/ _ \ __|  \___ \ / _ \/ _` | | | |/ _ \ '_ \ / __/ _ \
#| |__| |  __/ |_   ____) |  __/ (_| | |_| |  __/ | | | (_|  __/
# \____/ \___|\__| |_____/ \___|\__, |\__,_|\___|_| |_|\___\___|
#                                  | |
#                                  |_|

#Add L2L3Residual if on data:
if isMC:
    myCorrLabels = cms.vstring('L1FastJet', 'L2Relative', 'L3Absolute')
else:
    myCorrLabels = cms.vstring('L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual')

#all the other jets:
switchJetCollection(
    process,
    cms.InputTag('ak5PFJets'),
    doJTA        = True,
    doBTagging   = True,
    jetCorrLabel = ('AK5PF',myCorrLabels),
    doType1MET   = True,
    genJetCollection=cms.InputTag("ak5GenJets"),
    doJetID      = True
)

# only keep em above 7 GeV as the f'in smurfs
process.selectedPatJets.cut = "correctedJet('Uncorrected').pt > 7"


# Some stuff to save space
process.patJets.embedCaloTowers = False
process.patJets.addTagInfos = False
process.patJets.embedPFCandidates = False
process.patJets.addAssociatedTracks = False

process.boostedPatJets = cms.EDProducer("PatJetBooster",
    jetTag = cms.InputTag("cleanPatJets"),
    vertexTag = cms.InputTag("goodPrimaryVertices"),
)

process.slimPatJets = cms.EDProducer("PATJetSlimmer",
    src = cms.InputTag("boostedPatJets"),
    clearJetVars = cms.bool(True),
    clearDaughters = cms.bool(True),
    dropSpecific = cms.bool(False),
)

process.patDefaultSequence += (
    process.boostedPatJets *
    process.slimPatJets
)



#               _               _____      _ _           _   _
#    /\        | |             / ____|    | | |         | | (_)
#   /  \  _   _| |_ _ __ ___  | |     ___ | | | ___  ___| |_ _  ___  _ __  ___
#  / /\ \| | | | __| '__/ _ \ | |    / _ \| | |/ _ \/ __| __| |/ _ \| '_ \/ __|
# / ____ \ |_| | |_| | |  __/ | |___| (_) | | |  __/ (__| |_| | (_) | | | \__ \
#/_/    \_\__,_|\__|_|  \___|  \_____\___/|_|_|\___|\___|\__|_|\___/|_| |_|___/
#


process.reducedPFCands = cms.EDProducer("ReducedCandidatesProducer",
    srcCands = cms.InputTag("particleFlow",""),
    srcVertices = cms.InputTag("goodPrimaryVertices"),
    dz = cms.double(0.1),
    ptThresh = cms.double(0.0),
)

process.reducedPFNoPUCands = cms.EDProducer("ReducedCandidatesProducer",
    srcCands = cms.InputTag("pfNoPileUp",""),
    srcVertices = cms.InputTag("goodPrimaryVertices"),
    dz = cms.double(100000.0),
    ptThresh = cms.double(0.0),
)

process.autreSeq = cms.Sequence(process.reducedPFCands * process.reducedPFNoPUCands)

process.load("WWAnalysis.SkimStep.hzz4lDetectorIsolation_cff")

# make the crazy sequence
process.hzzIsoSequence = cms.Sequence(process.hzz4lDetectorIsolationSequence)


#  _____                        _                _
# / ____|                      | |              | |
#| (___   ___  _ __ ___   ___  | |     ___ _ __ | |_ ___  _ __
# \___ \ / _ \| '_ ` _ \ / _ \ | |    / _ \ '_ \| __/ _ \| '_ \
# ____) | (_) | | | | | |  __/ | |___|  __/ |_) | || (_) | | | |
#|_____/ \___/|_| |_| |_|\___| |______\___| .__/ \__\___/|_| |_|
#                                         | |
#                                         |_|
# ____                  _   _
#|  _ \                | | (_)
#| |_) | ___   ___  ___| |_ _ _ __   __ _
#|  _ < / _ \ / _ \/ __| __| | '_ \ / _` |
#| |_) | (_) | (_) \__ \ |_| | | | | (_| |
#|____/ \___/ \___/|___/\__|_|_| |_|\__, |
#                                    __/ |
#                                   |___/

# First boost to get the IP values
# Then boost to add the PF isolation and the


# add track IP information?
process.load("WWAnalysis.AnalysisStep.leptonBoosting_cff")
process.preBoostedElectrons = process.boostedElectrons.clone( electronTag = cms.InputTag("cleanPatElectronsTriggerMatch") )
process.preBoostedMuons = process.boostedMuons.clone( muonTag = cms.InputTag("cleanPatMuonsTriggerMatch") )
process.patDefaultSequence += process.preBoostedElectrons
process.patDefaultSequence += process.preBoostedMuons

# add Iso deposits
process.load("WWAnalysis.AnalysisStep.isoAdding_cff")
process.boostedElectronsIso = process.isoAddedElectrons.clone( electronTag = "preBoostedElectrons" )
process.boostedMuonsIso = process.isoAddedMuons.clone( muonTag = "preBoostedMuons" )
from WWAnalysis.SkimStep.hzz4lDetectorIsolation_cff import muIsoFromDepsZZ4L, eleIsoFromDepsZZ4L
process.boostedMuonsIso.deposits     += muIsoFromDepsZZ4L
process.boostedElectronsIso.deposits += eleIsoFromDepsZZ4L

process.patDefaultSequence += process.hzzIsoSequence
process.patDefaultSequence += process.boostedElectronsIso
process.patDefaultSequence += process.boostedMuonsIso

# add MVA Id and MVA Iso
process.boostedElectronsBDTID = cms.EDProducer("PatElectronBoosterBDTID", src = cms.InputTag("boostedElectronsIso"))
process.boostedElectrons = cms.EDProducer("PatElectronBoosterBDTIso",
    src = cms.InputTag("boostedElectronsBDTID"),
    rho = cms.string("rhoElActiveArea"),
    effectiveAreaTarget = cms.string("Data2011")
)


process.boostedMuonsBDTID = cms.EDProducer("PatMuonBoosterBDTID",
                                           src = cms.InputTag("boostedMuonsIso"),
                                           vertexs = cms.InputTag("goodPrimaryVertices"),
                                           pfCands = cms.InputTag("particleFlow"),
                                           rho = cms.InputTag("kt6PFJets","rho","RECO"),
                                           dzCut = cms.double(0.2),
                                           outputName = cms.string("bdtidnontrigDZ"))


process.boostedMuonsBDTIso = cms.EDProducer("PatMuonBoosterBDTIso",
                                            src = cms.InputTag("boostedMuonsBDTID"),
                                            vertexs = cms.InputTag("goodPrimaryVertices"),
                                            pfCands = cms.InputTag("particleFlow"),
                                            rho = cms.InputTag("kt6PFJets","rho","RECO"),
                                            effectiveAreaTarget = cms.string("Fall11MC"),
                                            dzCut = cms.double(0.2),
                                            outputName = cms.string("bdtisonontrigDZ"))

process.boostedMuons = cms.EDProducer("PatMuonBoosterBDTIso",
                                      src = cms.InputTag("boostedMuonsBDTIso"),
                                      vertexs = cms.InputTag("goodPrimaryVertices"),
                                      pfCands = cms.InputTag("pfNoPileUp"),
                                      rho = cms.InputTag("kt6PFJets","rho","RECO"),
                                      effectiveAreaTarget = cms.string("Fall11MC"),
                                      dzCut = cms.double(999999.),
                                      outputName = cms.string("bdtisonontrigPFNOPU"))

##    _____ ____  ____    ____  _           _
##   |  ___/ ___||  _ \  |  _ \| |__   ___ | |_ ___  _ __  ___
##   | |_  \___ \| |_) | | |_) | '_ \ / _ \| __/ _ \| '_ \/ __|
##   |  _|  ___) |  _ <  |  __/| | | | (_) | || (_) | | | \__ \
##   |_|   |____/|_| \_\ |_|   |_| |_|\___/ \__\___/|_| |_|___/
##
##
process.load("WWAnalysis.Tools.fsrPhotons_cff")


##    ____  _           _
##   |  _ \| |__   ___ ( )___    ___  _ __   ___ ___   _ __ ___   ___  _ __ ___
##   | |_) | '_ \ / _ \|// __|  / _ \| '_ \ / __/ _ \ | '_ ` _ \ / _ \| '__/ _ \
##   |  _ <| | | | (_) | \__ \ | (_) | | | | (_|  __/ | | | | | | (_) | | |  __/
##   |_| \_\_| |_|\___/  |___/  \___/|_| |_|\___\___| |_| |_| |_|\___/|_|  \___|
##
##
if is42X:
  process.kt6PFJetsForIsoActiveArea = process.kt6PFJetsForIso.clone(voronoiRfact = -0.9)
  process.patMuons.userData.userFloats.src  += [ cms.InputTag("rhoMuActiveArea"), cms.InputTag("rhoMuFullEta") ]
  process.patElectrons.userData.userFloats.src  += [ cms.InputTag("rhoElActiveArea"), cms.InputTag("rhoElFullEta") ]
  process.rhoMuActiveArea = process.rhoMu.clone(rhoTag = cms.untracked.InputTag("kt6PFJetsForIsoActiveArea","rho","SKIM"))
  process.rhoElActiveArea = process.rhoEl.clone(rhoTag = cms.untracked.InputTag("kt6PFJetsForIsoActiveArea","rho","SKIM"))
  process.rhoMuFullEta    = process.rhoMu.clone(rhoTag = cms.untracked.InputTag("kt6PFJets","rho","SKIM"))
  process.rhoElFullEta    = process.rhoEl.clone(rhoTag = cms.untracked.InputTag("kt6PFJets","rho","SKIM"))
  process.preLeptonSequence.replace(process.kt6PFJetsForIso, process.kt6PFJetsForIso + process.kt6PFJetsForIsoActiveArea)
  process.preLeptonSequence.replace(process.rhoMu, process.rhoMu + process.rhoMuActiveArea + process.rhoMuFullEta)
  process.preLeptonSequence.replace(process.rhoEl, process.rhoEl + process.rhoElActiveArea + process.rhoElFullEta)
  process.boostedMuonsBDTID.rho = cms.InputTag("kt6PFJets","rho")
  process.boostedMuonsBDTIso.rho = cms.InputTag("kt6PFJets","rho")
  process.boostedMuons.rho = cms.InputTag("kt6PFJets","rho")
  process.rhoFsrPhoton.rhoTag = cms.untracked.InputTag("kt6PFJetsForIsoActiveArea","rho","SKIM")
else:
  process.patMuons.userData.userFloats.src     += [ cms.InputTag("rhoMuFullEta"), cms.InputTag("rhoMuCentralNeutral") ]
  process.patElectrons.userData.userFloats.src += [ cms.InputTag("rhoElFullEta"), cms.InputTag("rhoElCentralNeutral") ]
  process.rhoMuFullEta        = process.rhoMu.clone(rhoTag = cms.untracked.InputTag("kt6PFJets","rho","RECO"))
  process.rhoElFullEta        = process.rhoEl.clone(rhoTag = cms.untracked.InputTag("kt6PFJets","rho","RECO"))
  process.rhoMuCentralNeutral = process.rhoMu.clone(rhoTag = cms.untracked.InputTag("kt6PFJetsCentralNeutral","rho","RECO"))
  process.rhoElCentralNeutral = process.rhoEl.clone(rhoTag = cms.untracked.InputTag("kt6PFJetsCentralNeutral","rho","RECO"))
  process.preLeptonSequence.replace(process.rhoMu, process.rhoMu + process.rhoMuFullEta + process.rhoMuCentralNeutral)
  process.preLeptonSequence.replace(process.rhoEl, process.rhoEl + process.rhoElFullEta + process.rhoElCentralNeutral)
  process.rhoFsrPhoton.rhoTag = cms.untracked.InputTag("kt6PFJets","rho","RECO")
  process.rhoFsrPhotonCentralNeutral = process.rhoFsrPhoton.clone(rhoTag = cms.untracked.InputTag("kt6PFJetsCentralNeutral","rho","RECO"))
  process.fsrPhotonSequence.replace(process.rhoFsrPhoton, process.rhoFsrPhoton + process.rhoFsrPhotonCentralNeutral)
  process.boostedFsrPhotons.userData.userFloats.src += [ cms.InputTag("rhoFsrPhotonCentralNeutral") ]


process.patDefaultSequence += process.boostedElectronsBDTID
process.patDefaultSequence += process.boostedElectrons
process.patDefaultSequence += process.boostedMuonsBDTID
process.patDefaultSequence += process.boostedMuonsBDTIso
process.patDefaultSequence += process.boostedMuons
process.patDefaultSequence += process.fsrPhotonSequence



#   _____      _              _       _
#  / ____|    | |            | |     | |
# | (___   ___| |__   ___  __| |_   _| | ___
#  \___ \ / __| '_ \ / _ \/ _` | | | | |/ _ \
#  ____) | (__| | | |  __/ (_| | |_| | |  __/
# |_____/ \___|_| |_|\___|\__,_|\__,_|_|\___|
#

process.out.outputCommands =  cms.untracked.vstring(
    'drop *',
    'keep *_prunedGen_*_*',
    'keep GenEventInfoProduct_generator_*_*',
    'keep *_addPileupInfo_*_*',
    'keep *_TriggerResults_*_*',
    'keep *_goodPrimaryVertices_*_*',
    'keep *_offlineBeamSpot_*_*',
    'keep *_reducedPFCands_*_*',
    'keep *_reducedPFNoPUCands_*_*',
    'keep *_boostedElectrons_*_*',
    'keep *_boostedMuons_*_*',
    'keep *_boostedFsrPhotons_*_*',
    'keep *_cleanPatPhotons_*_*',
    'keep *_correctedHybridSuperClusters_*_*',
    'keep *_correctedMulti5x5SuperClustersWithPreshower_*_*',
    'keep *_slimPatJets_*_*',
    'keep *_pfMet_*_*',
    'keep *_*_rho_*',
)

process.prePatSequence  = cms.Sequence( process.preLeptonSequence + process.preElectronSequence + process.preMuonSequence )
process.postPatSequence = cms.Sequence( process.autreSeq )
process.pfPileUp.PFCandidates = 'particleFlow'
process.pfNoPileUp.bottomCollection = 'particleFlow'

# In order to use the good primary vertices everywhere (It would be nicer to set the proper inputTags in the first place)
massSearchReplaceAnyInputTag(process.prePatSequence,cms.InputTag("offlinePrimaryVertices"), cms.InputTag("goodPrimaryVertices"),True)
massSearchReplaceAnyInputTag(process.patDefaultSequence,cms.InputTag("offlinePrimaryVertices"), cms.InputTag("goodPrimaryVertices"),True)
massSearchReplaceAnyInputTag(process.postPatSequence,cms.InputTag("offlinePrimaryVertices"), cms.InputTag("goodPrimaryVertices"),True)
process.firstVertexIsGood.vertices = cms.InputTag("offlinePrimaryVertices")
process.goodPrimaryVertices.src = cms.InputTag("offlinePrimaryVertices")
process.pfPileUp.Vertices = cms.InputTag("offlinePrimaryVertices")

process.scrap      = cms.Path( process.noscraping )
process.outpath    = cms.EndPath(process.out)

## Skim conditions
process.load("WWAnalysis.SkimStep.hzz4lPreSkimFilter_cff")

process.patPath = cms.Path( process.hzz4lPreFilterSeq * process.prePatSequence * process.patDefaultSequence * process.postPatSequence)
#process.patPath = cms.Path( process.prePatSequence * process.patDefaultSequence * process.postPatSequence)

process.out.SelectEvents   = cms.untracked.PSet(SelectEvents = cms.vstring('patPath'))

process.schedule = cms.Schedule( process.patPath, process.scrap, process.outpath)
##############################################
#process.source.eventsToProcess = cms.untracked.VEventRange(
#    "1:122490", '1:1343', '1:177684'
#)
#process.muonPFIsoPhoton04.debug = cms.untracked.bool(True)
#process.electronPFIsoChHad04.debug = cms.untracked.bool(True)



