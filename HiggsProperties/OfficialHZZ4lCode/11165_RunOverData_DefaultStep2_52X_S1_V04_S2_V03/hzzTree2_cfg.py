import FWCore.ParameterSet.Config as cms

process = cms.Process("Tree")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

from glob import glob
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring())
#process.source.fileNames = [
#    'root://pcmssd12//data/gpetrucc/8TeV/hzz/skims/52X/2012_05_01/ggH_120_52X/hzz4lSkim_101_2_OyG.root',
#    'root://pcmssd12//data/gpetrucc/8TeV/hzz/skims/52X/2012_05_01/ggH_120_52X/hzz4lSkim_11_2_c7l.root',
#]
process.source.fileNames = [
      #'root://pcmssd12//data/gpetrucc/7TeV/hzz/step1/sync/S1_preV00/GluGluToHToZZTo4L_M-120_7TeV-powheg-pythia6_PU_S6_START42_V14B_40E86BD8-0BF0-E011-BA16-00215E21D5C4.root'
      'root://pcmssd12//data/gpetrucc/7TeV/hzz/step1/sync/S1_V01/GluGluToHToZZTo4L_M-120_7TeV-powheg-pythia6_PU_S6_START42_V14B_40E86BD8-0BF0-E011-BA16-00215E21D5C4.root'
      #'file:/afs/cern.ch/work/g/gpetrucc/HZZ/CMSSW_5_2_4_patch4/src/WWAnalysis/SkimStep/test/hzz4lSkim.4sync_v1.root'
]

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("WWAnalysis.AnalysisStep.hzz4l_selection_cff")
#process.load("WWAnalysis.AnalysisStep.zz4l.fixup_from_S1_preV00")
#process.load("WWAnalysis.AnalysisStep.zz4l.fixup_from_S1_V01")

process.load("WWAnalysis.AnalysisStep.zz4l.reSkim_cff")
process.load("WWAnalysis.AnalysisStep.zz4l.mcSequences_cff")
process.load("WWAnalysis.AnalysisStep.zz4l.recoFinalStateClassifiers_cff")
process.load("WWAnalysis.AnalysisStep.fourLeptonBlinder_cfi")
process.load("WWAnalysis.AnalysisStep.zz4lTree_cfi")

from WWAnalysis.AnalysisStep.hzz4l_selection_cff import *                         #conf1
#from WWAnalysis.AnalysisStep.zz4l.hzz4l_selection_mvaiso_tight_cff import *      #conf2
#from WWAnalysis.AnalysisStep.zz4l.hzz4l_selection_mvaiso_cff import *            #conf3
#from WWAnalysis.AnalysisStep.zz4l.hzz4l_selection_pfiso_pt53_cff import *        #conf4
#from WWAnalysis.AnalysisStep.zz4l.hzz4l_selection_prl_objs_cff import *          #conf5
#from WWAnalysis.AnalysisStep.zz4l.hzz4l_selection_2012_cff import *

isMC=False
is42X=False

if is42X:
    TRIGGER_FILTER = 'triggerFilter7TeV_MC' if isMC else 'triggerFilter7TeV_DATA'
else:
    TRIGGER_FILTER = 'triggerFilter8TeV'

### =========== BEGIN COMMON PART ==============

## 1) DEFINE LOOSE LEPTONS
process.looseMu = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("boostedMuons"),
    cut = cms.string(MUID_LOOSE),
)

process.looseElNoClean = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("boostedElectrons"),
    cut = cms.string(ELID_LOOSE),
)

## 2) LEPTONS CLEANING

process.looseEl = cms.EDProducer("PATElectronCleaner",
    src = cms.InputTag("looseElNoClean"),
    preselection = cms.string(""),
    checkOverlaps = cms.PSet(
        muons = cms.PSet(
           src = cms.InputTag("boostedMuons"),
           algorithm = cms.string("byDeltaR"),
           preselection = cms.string("userInt('pfMuId')>0 || isGlobalMuon"),
           deltaR  = cms.double(0.05),
           checkRecoComponents = cms.bool(False),
           pairCut  = cms.string(""),
           requireNoOverlaps  = cms.bool(True),
        )
    ),
    finalCut = cms.string(''),
)

process.looseLep = cms.EDProducer("CandViewMerger",
    src = cms.VInputTag("looseEl", "looseMu")
)

## 3) DEFINE GOOD LEPTONS

process.goodMu = cms.EDFilter("PATMuonSelector",
    src = cms.InputTag("looseMu"),
    cut = cms.string(MUID_GOOD),
)

process.goodEl = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("looseEl"),
    cut = cms.string(ELID_GOOD),
)

process.goodLep = cms.EDProducer("CandViewMerger",
    src = cms.VInputTag("goodMu", "goodEl")
)

process.countGoodLep = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("goodLep"),
    minNumber = cms.uint32(4),
)
process.countGoodLep3 = process.countGoodLep.clone(minNumber = 3)
process.countLooseLep = process.countGoodLep.clone(src = "looseLep")
process.countLooseLep3 = process.countLooseLep.clone(minNumber = 3)

process.countSequenceLLG = cms.Sequence(
    process.countLooseLep3 +
    process.countLooseLep  +
    process.countGoodLep3  +
    process.countGoodLep
)
process.countSequenceLGG = cms.Sequence(
    process.countLooseLep3 +
    process.countGoodLep3  +
    process.countLooseLep  +
    process.countGoodLep
)


## 4) MAKE Z CANDIDATES

process.goodLL = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("goodLep@+ goodLep@-"),
    cut = cms.string("")
)
process.zllAny = cms.EDProducer("SkimEvent2LProducer",
    src = cms.InputTag("goodLL"),
    pfMet = cms.InputTag("pfMet"),
    vertices = cms.InputTag("goodPrimaryVertices"),
    doMassRes = cms.bool(False),
)

process.zll = cms.EDFilter("SkimEvent2LSelector",
    src = cms.InputTag("zllAny"),
    cut = cms.string(SEL_ANY_Z),
)

process.oneZ = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("zll"),
    minNumber = cms.uint32(1),
)

process.bestZ = cms.EDFilter("SkimEvent2LSorter",
    src = cms.InputTag("zll"),
    sortBy = cms.string("abs(mass - 91.188)"),
    sortAscending = cms.bool(True),
    maxNumber = cms.uint32(1),
)

process.selectedZ1 = cms.EDFilter("SkimEvent2LSelector",
    src = cms.InputTag("bestZ"),
    cut = cms.string(SEL_BEST_Z1),
    filter = cms.bool(ARBITRATE_EARLY)
)


### =========== BEGIN SIGNAL PART ==============
# Here starts the ZZ step
process.zz = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("selectedZ1 zll" if ARBITRATE_EARLY else "zll zll"),
    cut = cms.string("deltaR(daughter(0).daughter(0).eta, daughter(0).daughter(0).phi, daughter(1).daughter(0).eta, daughter(1).daughter(0).phi)>0.01 &&"+
                     "deltaR(daughter(0).daughter(0).eta, daughter(0).daughter(0).phi, daughter(1).daughter(1).eta, daughter(1).daughter(1).phi)>0.01 &&"+
                     "deltaR(daughter(0).daughter(1).eta, daughter(0).daughter(1).phi, daughter(1).daughter(0).eta, daughter(1).daughter(0).phi)>0.01 &&"+
                     "deltaR(daughter(0).daughter(1).eta, daughter(0).daughter(1).phi, daughter(1).daughter(1).eta, daughter(1).daughter(1).phi)>0.01"),
)
process.oneZZ = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("zz"),
    minNumber = cms.uint32(1),
)

process.skimEvent4LNoArb = cms.EDProducer("SkimEvent4LProducer",
    src = cms.InputTag("zz"),
    reducedPFCands = cms.InputTag("reducedPFCands"),
    jets = cms.InputTag("slimPatJets"),
    pfMet = cms.InputTag("pfMet"),
    vertices = cms.InputTag("goodPrimaryVertices"),
    isMC = cms.bool(isMC),
    mcMatch = cms.InputTag(""),
    doswap = cms.bool(False if ARBITRATE_EARLY else True), # sort the two Z's to ensure that Z1 is closest to the nominal mass (unless fixed already)
    doMELA = cms.bool(True),
    melaQQZZHistos = cms.string("WWAnalysis/AnalysisStep/data/QQZZ8DTemplatesNotNorm.root"),
    doMassRes = cms.bool(True),
)

process.zz4lTreeNoArb = process.zz4lTree.clone(src = cms.InputTag("skimEvent4LNoArb"))


process.selectedZZs1 = cms.EDFilter("SkimEvent4LSelector",
    src = cms.InputTag("best4L" if ARBITRATE_EARLY else "skimEvent4LNoArb"),
    cut = cms.string(SEL_ZZ4L_STEP_1),
    filter = cms.bool(True),
)
process.selectedZZs2 = process.selectedZZs1.clone(
    src = "selectedZZs1",
    cut = SEL_ZZ4L_STEP_2,
)
process.selectedZZs3 = process.selectedZZs1.clone(
    src = "selectedZZs2",
    cut = SEL_ZZ4L_STEP_3,
)
process.selectedZZs4 = process.selectedZZs1.clone(
    src = "selectedZZs3",
    cut = SEL_ZZ4L_STEP_4,
)
process.selectedZZs5 = process.selectedZZs1.clone(
    src = "selectedZZs4",
    cut = SEL_ZZ4L_STEP_5,
)
process.selectedZZs6 = process.selectedZZs1.clone(
    src = "selectedZZs5",
    cut = SEL_ZZ4L_STEP_6,
)


process.best4Lpass1 = cms.EDProducer("SkimEvent4LSorterWithTies",
    src = cms.InputTag("skimEvent4LNoArb" if ARBITRATE_EARLY else "selectedZZs6"),
    sortBy = cms.string(SEL_ZZ4L_ARBITRATION_1),
    sortAscending = cms.bool(False),
    maxNumber = cms.uint32(1),
    keepTies = cms.bool(True),
)
process.best4L  = cms.EDProducer("SkimEvent4LSorterWithTies",
    src = cms.InputTag("best4Lpass1"),
    sortBy = cms.string(SEL_ZZ4L_ARBITRATION_2),
    sortAscending = cms.bool(False),
    maxNumber = cms.uint32(1),
    keepTies = cms.bool(False),
)

process.zz4lTree.src = cms.InputTag("selectedZZs6" if ARBITRATE_EARLY else "best4L")

if ARBITRATE_EARLY:
    process.zzCombinatoric = cms.Sequence(
        process.best4Lpass1 + process.best4L +
        process.selectedZZs1 + process.selectedZZs2 + process.selectedZZs3 + process.selectedZZs4 + process.selectedZZs5 + process.selectedZZs6
    )
else:
    process.zzCombinatoric = cms.Sequence(
        process.selectedZZs1 + process.selectedZZs2 + process.selectedZZs3 + process.selectedZZs4 + process.selectedZZs5 + process.selectedZZs6 +
        process.best4Lpass1 + process.best4L
    )

### =========== CONTROL SELECTION ==========================

### ========= INCLUSIVE MONITORING OF ALL LEPTONS  =============
process.muonTree = cms.EDFilter("ProbeTreeProducer",
    src = cms.InputTag("boostedMuons"),
    sortDescendingBy = cms.string("pt"),
    cut = cms.string(""),
    variables   = cms.PSet(
       pt     = cms.string("pt"),
       eta    = cms.string("eta"),
       phi    = cms.string("phi"),
       pfIsoChHad04      = cms.string("userFloat('pfChHadIso04')"),
       pfIsoNHad04_NoEA  = cms.string("userFloat('pfNHadIso04')"),
       pfIsoPhot04_NoEA  = cms.string("userFloat('pfPhotonIso04')"),
       pfIsoEAtot        = cms.string("userFloat('pfCombIso04EACorrEAtot')"),
       pfIsoComb04EACorr = cms.string("userFloat('pfCombIso04EACorr')"),
       bdtIso = cms.string("userFloat('bdtIso')"),
       sip  = cms.string("userFloat('sip')"),
       rho  = cms.string("userFloat('rhoMu')"),
       rhoAA  = cms.string("userFloat('rhoMuActiveArea')"),
    ),
    flags = cms.PSet(
       looseID = cms.string(MUID_LOOSE_NO_PT_CUT),
       mvaISO  = cms.string("userInt('mvaIso')"),
       newID  = cms.string("userInt('newID')"),
       prlID = cms.string("userInt('prlID')"),
    ),
    addRunLumiInfo = cms.bool(True),
)

process.electronTree = cms.EDFilter("ProbeTreeProducer",
    src = cms.InputTag("boostedElectrons"),
    sortDescendingBy = cms.string("pt"),
    cut = cms.string(""),
    variables   = cms.PSet(
       pt     = cms.string("pt"),
       eta    = cms.string("eta"),
       phi    = cms.string("phi"),
       pfIsoChHad04      = cms.string("userFloat('pfChHadIso04')"),
       pfIsoNHad04_NoEA  = cms.string("userFloat('pfNHadIso04')"),
       pfIsoPhot04_NoEA  = cms.string("userFloat('pfPhotonIso04')"),
       pfIsoEAtot        = cms.string("userFloat('pfCombIso04EACorrEAtot')"),
       pfIsoComb04EACorr = cms.string("userFloat('pfCombIso04EACorr')"),
       bdtID  = cms.string("userFloat('bdtID')"),
       bdtIso = cms.string("userFloat('bdtIso')"),
       sip  = cms.string("userFloat('sip')"),
       rho  = cms.string("userFloat('rhoEl')"),
       rhoAA  = cms.string("userFloat('rhoElActiveArea')"),
       missingHits = cms.string("gsfTrack.trackerExpectedHitsInner.numberOfHits"),
    ),
    flags = cms.PSet(
       looseID = cms.string(ELID_LOOSE_NO_PT_CUT),
       mvaISO = cms.string("userInt('mvaIso')"),
       mvaID  = cms.string("userInt('mvaID')"),
       newID = cms.string("userInt('newID')"),
       prlID = cms.string("userInt('prlID')"),
    ),
    addRunLumiInfo = cms.bool(True),
)


### ========= INCLUSIVE MONITORING OF ALL Z'S =============
process.anyZllTree = cms.EDFilter("ProbeTreeProducer",
    src = cms.InputTag("zll"),
    sortDescendingBy = cms.string("-abs(mass - 91.188)"),
    cut = cms.string(""),
    variables   = cms.PSet(
       l1pt     = cms.string("daughter(0).pt"),
       l1eta    = cms.string("daughter(0).eta"),
       l1phi    = cms.string("daughter(0).phi"),
       l1pdgId  = cms.string("daughter(0).pdgId"),
       l2pt     = cms.string("daughter(1).pt"),
       l2eta    = cms.string("daughter(1).eta"),
       l2phi    = cms.string("daughter(1).phi"),
       l2pdgId  = cms.string("daughter(1).pdgId"),
       zmass    = cms.string("mass"),
       zpt      = cms.string("pt"),
       zeta     = cms.string("eta"),
       zphi     = cms.string("phi"),
       l1tkIso  = cms.string("luserFloat(0,'tkZZ4L')"),
       l1ecalIso= cms.string("luserFloat(0,'ecalZZ4L')"),
       l1hcalIso= cms.string("luserFloat(0,'hcalZZ4L')"),
       l2tkIso  = cms.string("luserFloat(0,'tkZZ4L')"),
       l2ecalIso= cms.string("luserFloat(1,'ecalZZ4L')"),
       l2hcalIso= cms.string("luserFloat(1,'hcalZZ4L')"),
       l1combDetIso = cms.string("combinedIso(0)"),
       l2combDetIso = cms.string("combinedIso(1)"),
       pairCombDetIso = cms.string("combinedPairRelativeIso"),
       l1pfIsoComb04EACorr  = cms.string("luserFloat(0, 'pfCombIso04EACorr')"),
       l2pfIsoComb04EACorr  = cms.string("luserFloat(1, 'pfCombIso04EACorr')"),
       l1pfIsoChHad04  = cms.string("luserFloat(0, 'pfChHadIso04')"),
       l2pfIsoChHad04  = cms.string("luserFloat(1, 'pfChHadIso04')"),
       l1pfIsoNHad04  = cms.string("luserFloat(0, 'pfNHadIso04')"),
       l2pfIsoNHad04  = cms.string("luserFloat(1, 'pfNHadIso04')"),
       l1pfIsoPhoton04  = cms.string("luserFloat(0, 'pfPhotonIso04')"),
       l2pfIsoPhoton04  = cms.string("luserFloat(1, 'pfPhotonIso04')"),
       l1pfIsoEAtot     = cms.string("luserFloat(0, 'pfCombIso04EACorrEAtot')"),
       l2pfIsoEAtot     = cms.string("luserFloat(1, 'pfCombIso04EACorrEAtot')"),
       l1bdtID   = cms.string("luserFloat(0,'bdtID')"),
       l2bdtID   = cms.string("luserFloat(1,'bdtID')"),
       l1bdtIso  = cms.string("luserFloat(0,'bdtIso')"),
       l2bdtIso  = cms.string("luserFloat(1,'bdtIso')"),
       l1sip  = cms.string("luserFloat(0,'sip')"),
       l2sip  = cms.string("luserFloat(1,'sip')"),
       rho      = cms.string("luserFloat(1,'rhoEl') + luserFloat(1,'rhoMu')"),
       rhoAA    = cms.string("luserFloat(1,'rhoElActiveArea') + luserFloat(1,'rhoMuActiveArea')"),
       nvtx     = cms.string("numvertices"),
       massErr  = cms.string("userFloat('massErr')"),
    ),
    flags = cms.PSet(
       l1idNew  = cms.string("luserInt(0,'newID')"),
       l2idNew  = cms.string("luserInt(1,'newID')"),
       l1idPRL  = cms.string("luserInt(0,'prlID')"),
       l2idPRL  = cms.string("luserInt(1,'prlID')"),
       l1idMVA  = cms.string("luserInt(0,'mvaID')"),
       l2idMVA  = cms.string("luserInt(1,'mvaID')"),
       l1isoMVA  = cms.string("luserInt(0,'mvaIso')"),
       l2isoMVA  = cms.string("luserInt(1,'mvaIso')"),
    ),
    addRunLumiInfo = cms.bool(True),
)

process.zeetree = process.anyZllTree.clone(cut = cms.string("abs(daughter(1).pdgId) == 11"))
process.zeetree.variables.massErr  = cms.string("userFloat('massErr')")
process.zeetree.flags.l1ConvR  = cms.string("l(0).gsfTrack.trackerExpectedHitsInner.numberOfHits <= 1")
process.zeetree.flags.l2ConvR  = cms.string("l(1).gsfTrack.trackerExpectedHitsInner.numberOfHits <= 1")

process.zmmtree = process.anyZllTree.clone(cut = cms.string("abs(daughter(1).pdgId) == 13"))
process.zmmtree.variables.l1tkLayers =  cms.string("l(0).track.hitPattern.trackerLayersWithMeasurement")
process.zmmtree.variables.l2tkLayers =  cms.string("l(1).track.hitPattern.trackerLayersWithMeasurement")
process.zmmtree.flags.l1idGlb  = cms.string("l(0).isGlobalMuon")
process.zmmtree.flags.l2idGlb  = cms.string("l(1).isGlobalMuon")

# ========= FAKE RATE MEASUREMENT PART (Z + 1L) =================
process.looseMuCR = process.goodMu.clone(cut = MUID_LOOSE_CR)
process.looseElCR = process.goodEl.clone(cut = ELID_LOOSE_CR)
process.looseLepCR = process.goodLep.clone(src = [ 'looseMuCR', 'looseElCR' ])

process.metVeto = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("pfMet"),
    cut = cms.string("et < 25"),
    filter = cms.bool(True)
)
process.lepMinFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("looseLepCR"),
    minNumber = cms.uint32(3),
)

process.lepMaxFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag("looseLepCR"), ## note not CR
    minNumber = cms.uint32(4),
)

process.zPlusLep = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("selectedZ1 looseLepCR"),
    cut = cms.string("deltaR(daughter(0).daughter(0).eta, daughter(0).daughter(0).phi, daughter(1).eta, daughter(1).phi)>0.01 && "+
                     "deltaR(daughter(0).daughter(1).eta, daughter(0).daughter(1).phi, daughter(1).eta, daughter(1).phi)>0.01"),
    checkCharge = cms.bool(False)
)

process.zllmtree = cms.EDFilter("ProbeTreeProducer",
    src = cms.InputTag("zPlusLep"),
    cut = cms.string("abs(daughter(1).pdgId) == 13"),
    addRunLumiInfo = cms.bool(True),
    variables   = cms.PSet(
       zmass    = cms.string("daughter(0).mass"),
       met      = cms.string("daughter(0).masterClone.met"),
       l1pt     = cms.string("daughter(0).masterClone.daughter(0).pt"),
       l1eta    = cms.string("daughter(0).masterClone.daughter(0).eta"),
       l1phi    = cms.string("daughter(0).masterClone.daughter(0).phi"),
       l2pt     = cms.string("daughter(0).masterClone.daughter(1).pt"),
       l2eta    = cms.string("daughter(0).masterClone.daughter(1).eta"),
       l2phi    = cms.string("daughter(0).masterClone.daughter(1).phi"),
       pt       = cms.string("daughter(1).pt"),
       eta      = cms.string("daughter(1).eta"),
       phi      = cms.string("daughter(1).phi"),
       tkIso    = cms.string("daughter(1).masterClone.userFloat('tkZZ4L')"),
       ecalIso  = cms.string("daughter(1).masterClone.userFloat('ecalZZ4L')"),
       hcalIso  = cms.string("daughter(1).masterClone.userFloat('hcalZZ4L')"),
       rho      = cms.string("daughter(1).masterClone.userFloat('rhoMu')"),
       rhoAA    = cms.string("daughter(1).masterClone.userFloat('rhoMuActiveArea')"),
       bdtIdDz = cms.string("daughter(1).masterClone.userFloat('bdtidnontrigDZ')"),
       bdtIso  = cms.string("daughter(1).masterClone.userFloat('bdtIso')"),
       bdtIsoDz = cms.string("daughter(1).masterClone.userFloat('bdtisonontrigDZ')"), # deprecated
       bdtIsoPnp = cms.string("daughter(1).masterClone.userFloat('bdtisonontrigPFNOPU')"), # deprecated
       pfIsoChHad04       = cms.string("daughter(1).masterClone.userFloat('pfChHadIso04')"),
       pfIsoNHad04_NoEA   = cms.string("daughter(1).masterClone.userFloat('pfNHadIso04')"),
       pfIsoPhoton04_NoEA = cms.string("daughter(1).masterClone.userFloat('pfPhotonIso04')"),
       pfCombRelIso04EACorr = cms.string("daughter(1).masterClone.userFloat('pfCombRelIso04EACorr')"),
       sip    = cms.string("daughter(1).masterClone.userFloat('sip')"),
       sip3d = cms.string("daughter(1).masterClone.userFloat('ip')/daughter(1).masterClone.userFloat('ipErr')"),
       numvertices = cms.string("daughter(0).masterClone.numvertices"),
    ),
    flags = cms.PSet(
       globalmu = cms.string("daughter(1).masterClone.isGlobalMuon"),
       trackermu = cms.string("daughter(1).masterClone.isTrackerMuon"),
       newID  = cms.string("daughter(1).masterClone.userInt('newID')"),
       prlID  = cms.string("daughter(1).masterClone.userInt('prlID')"),
       mvaIso = cms.string("daughter(1).masterClone.userInt('mvaIso')"),
       pfid   = cms.string("daughter(1).masterClone.userInt('pfMuId')"),
       id     = cms.string("daughter(1).masterClone.isGlobalMuon && daughter(1).masterClone.track.numberOfValidHits() > 10"),
       id2012 = cms.string("daughter(1).masterClone.isGlobalMuon && daughter(1).masterClone.track.hitPattern.trackerLayersWithMeasurement > 5"),
       l1trig   = cms.string("daughter(0).daughter(0).masterClone.triggerObjectMatchesByPath('HLT_Mu17_Mu8_v*').size() > 0 || " +
                             "daughter(0).daughter(0).masterClone.triggerObjectMatchesByPath('HLT_Mu13_Mu8_v*').size() > 0"),
       l2trig   = cms.string("daughter(0).daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Mu17_Mu8_v*').size() > 0 || " +
                             "daughter(0).daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Mu13_Mu8_v*').size() > 0"),
       l3trig   = cms.string("daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Mu17_Mu8_v*').size() > 0 || " +
                             "daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Mu13_Mu8_v*').size() > 0"),
    )
)

process.zlletree = cms.EDFilter("ProbeTreeProducer",
    src = cms.InputTag("zPlusLep"),
    cut = cms.string("abs(daughter(1).pdgId) == 11"),
    addRunLumiInfo = cms.bool(True),
    variables   = cms.PSet(
       zmass    = cms.string("daughter(0).mass"),
       met      = cms.string("daughter(0).masterClone.met"),
       pt       = cms.string("daughter(1).pt"),
       l1pt     = cms.string("daughter(0).masterClone.daughter(0).pt"),
       l1eta    = cms.string("daughter(0).masterClone.daughter(0).eta"),
       l1phi    = cms.string("daughter(0).masterClone.daughter(0).phi"),
       l2pt     = cms.string("daughter(0).masterClone.daughter(1).pt"),
       l2eta    = cms.string("daughter(0).masterClone.daughter(1).eta"),
       l2phi    = cms.string("daughter(0).masterClone.daughter(1).phi"),
       eta      = cms.string("daughter(1).eta"),
       phi      = cms.string("daughter(1).phi"),
       tkIso    = cms.string("daughter(1).masterClone.userFloat('tkZZ4L')"),
       ecalIso  = cms.string("daughter(1).masterClone.userFloat('ecalZZ4L')"),
       hcalIso  = cms.string("daughter(1).masterClone.userFloat('hcalZZ4L')"),
       rho      = cms.string("daughter(1).masterClone.userFloat('rhoEl')"),
       rhoAA    = cms.string("daughter(1).masterClone.userFloat('rhoElActiveArea')"),
       bdtIdYtDz = cms.string("daughter(1).masterClone.userFloat('bdtIDTrig')"),
       bdtIdNtDz = cms.string("daughter(1).masterClone.userFloat('bdtID')"),
       bdtIsoNtDz = cms.string("daughter(1).masterClone.userFloat('bdtIso')"),
       bdtID     = cms.string("daughter(1).masterClone.userFloat('bdtID')"),
       bdtIso    = cms.string("daughter(1).masterClone.userFloat('bdtIso')"),
       pfIsoChHad04       = cms.string("daughter(1).masterClone.userFloat('pfChHadIso04')"),
       pfIsoNHad04_NoEA   = cms.string("daughter(1).masterClone.userFloat('pfNHadIso04')"),
       pfIsoPhoton04_NoEA = cms.string("daughter(1).masterClone.userFloat('pfPhotonIso04')"),
       pfCombRelIso04EACorr = cms.string("daughter(1).masterClone.userFloat('pfCombRelIso04EACorr')"),
       sip    = cms.string("daughter(1).masterClone.userFloat('sip')"),
       nmisshits = cms.string('daughter(1).masterClone.gsfTrack.trackerExpectedHitsInner.numberOfHits'),
       numvertices = cms.string("daughter(0).masterClone.numvertices"),
    ),
    flags = cms.PSet(
       newID  = cms.string("daughter(1).masterClone.userInt('newID')"),
       prlID  = cms.string("daughter(1).masterClone.userInt('prlID')"),
       mvaIso = cms.string("daughter(1).masterClone.userInt('mvaIso')"),
       mvaID  = cms.string("daughter(1).masterClone.userInt('mvaID')"),
       id     = cms.string("test_bit(daughter(1).masterClone.electronID('cicTight'),0) == 1 && daughter(1).masterClone.gsfTrack.trackerExpectedHitsInner.numberOfHits <= 1"),
       l1trig   = cms.string("daughter(0).daughter(0).masterClone.triggerObjectMatchesByPath('HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*').size() > 0 || " +
                             "daughter(0).daughter(0).masterClone.triggerObjectMatchesByPath('HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*').size() > 0"),
       l2trig   = cms.string("daughter(0).daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*').size() > 0 || " +
                             "daughter(0).daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*').size() > 0"),
       l3trig   = cms.string("daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*').size() > 0 || " +
                             "daughter(1).masterClone.triggerObjectMatchesByPath('HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*').size() > 0")
    )
)

# ========= FAKE RATE APPLICATION PART (Z + 2L) =================
process.diLepCRbare = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("looseLepCR looseLepCR"),
    cut = cms.string(SEL_ANY_CR_Z),
    checkCharge = cms.bool(False)
)

process.diLepCR = cms.EDProducer("SkimEvent2LProducer",
    src = cms.InputTag("diLepCRbare"),
    pfMet = cms.InputTag("pfMet"),
    vertices = cms.InputTag("goodPrimaryVertices")
)

process.zx = cms.EDProducer("CandViewShallowCloneCombiner",
    decay = cms.string("selectedZ1 diLepCR"),
    cut = cms.string("deltaR(daughter(0).daughter(0).eta, daughter(0).daughter(0).phi, daughter(1).daughter(0).eta, daughter(1).daughter(0).phi)>0.01 &&"+
                     "deltaR(daughter(0).daughter(0).eta, daughter(0).daughter(0).phi, daughter(1).daughter(1).eta, daughter(1).daughter(1).phi)>0.01 &&"+
                     "deltaR(daughter(0).daughter(1).eta, daughter(0).daughter(1).phi, daughter(1).daughter(0).eta, daughter(1).daughter(0).phi)>0.01 &&"+
                     "deltaR(daughter(0).daughter(1).eta, daughter(0).daughter(1).phi, daughter(1).daughter(1).eta, daughter(1).daughter(1).phi)>0.01"),
    checkCharge = cms.bool(False)
)

process.skimEventZX = cms.EDProducer("SkimEvent4LProducer",
    src = cms.InputTag("zx"),
    reducedPFCands = cms.InputTag("reducedPFCands"),
    jets = cms.InputTag("slimPatJets"),
    pfMet = cms.InputTag("pfMet"),
    vertices = cms.InputTag("goodPrimaryVertices"),
    isMC = cms.bool(isMC),
    mcMatch = cms.InputTag(""),
    doMELA = cms.bool(True),
    melaQQZZHistos = cms.string("WWAnalysis/AnalysisStep/data/QQZZ8DTemplatesNotNorm.root"),
    doswap = cms.bool(False) ## Leave the Z1 as is
)

process.anyZxTree = process.zz4lTree.clone( src = "skimEventZX")

process.skimEventZXcut1 = process.selectedZZs1.clone( src = "skimEventZX" )
process.skimEventZXcut2 = process.selectedZZs2.clone( src = "skimEventZXcut1" )
process.skimEventZXcut3 = process.selectedZZs3.clone( src = "skimEventZXcut2" )
process.skimEventZXcut4 = process.selectedZZs4.clone( src = "skimEventZXcut3" )
process.skimEventZXsort1 = process.best4Lpass1.clone( src = "skimEventZXcut4" )
process.bestZX = process.best4L.clone( src = "skimEventZXsort1")
process.zxTree = process.zz4lTree.clone( src = "bestZX")

# Setting up paths
skimseq = process.reskim
if SKIM_SEQUENCE != 'reskim':
    skimseq = getattr(process, SKIM_SEQUENCE)
if TRIGGER_FILTER:
    skimseq += getattr(process, TRIGGER_FILTER)

process.common = cms.Sequence(
    process.reboosting +
    skimseq +
    process.looseMu +
    process.looseElNoClean + process.looseEl +
    process.looseLep +
    process.goodMu +
    process.goodEl +
    process.goodLep +
    process.goodLL +
    process.zllAny +
    process.zll +
    process.bestZ
)

process.zzPath = cms.Path(
    process.fourLeptonBlinder +
    process.common +
    process.oneZ +
    process.selectedZ1 +
    process.zz     +
    process.oneZZ  +
    process.skimEvent4LNoArb +  process.zz4lTreeNoArb +
    process.zzCombinatoric +
    process.zz4lTree
)
if FOUR_LEPTON_FILTER_PRE_Z:
    process.zzPath.replace(process.oneZ, process.countSequenceLLG + process.oneZ)
if FOUR_LEPTON_FILTER_POST_Z:
    process.zzPath.replace(process.zz, process.countSequenceLLG + process.zz)

process.count4lPath  = cms.Path(
    process.common +
    process.countGoodLep
)

process.leptonPath = cms.Path(
    process.common +
    process.muonTree + process.electronTree
)

process.zPath = cms.Path(
    process.common +
    process.oneZ +
    process.zmmtree + process.zeetree
)

process.zlPath = cms.Path(
    process.common +
    process.bestZ +
    process.selectedZ1 +
    process.looseMuCR +
    process.looseElCR +
    process.looseLepCR +
    process.metVeto +
    process.lepMinFilter +
    ~process.lepMaxFilter +
    process.zPlusLep + process.zllmtree + process.zlletree
)

process.zllPath = cms.Path(
    process.common +
    process.bestZ +
    process.selectedZ1 +
    process.looseMuCR +
    process.looseElCR +
    process.looseLepCR +
    process.diLepCRbare +
    process.diLepCR    +
    process.zx    +
    process.skimEventZX +  process.anyZxTree +
    process.skimEventZXcut1 +
    process.skimEventZXcut2 +
    process.skimEventZXcut3 +
    process.skimEventZXcut4 +
    process.skimEventZXsort1 +
    process.bestZX       +  process.zxTree
)

### Paths with reco classification
from WWAnalysis.AnalysisStep.zz4l.recoFinalStateClassifiers_cff import makeSplittedPaths4L
makeSplittedPaths4L(process, 'zzPath', TRIGGER_FILTER)

### Paths with MC matching sequence
from WWAnalysis.AnalysisStep.zz4l.ptEtaFilters import adaEtaFilter, adaPtMinFilter
process.gen3FilterEta254PtMin = process.gen3FilterEta254PtMin5.clone(cut = cms.string(adaEtaFilter(2.5,2.4)+" && "+adaPtMinFilter(EL_PT_MIN,MU_PT_MIN)))
process.genSkim      = cms.Sequence(process.gen3RecoSeq + process.gen3FilterAny)
process.genSkimPtEta = cms.Sequence(process.genSkim + process.gen3FilterEta254PtMin)
process.ZZ_Any   = cms.Path(  process.genSkim                      + process.zzPath._seq )
process.ZZ_4Mu   = cms.Path(  process.genSkim + process.gen3ZZ4M   + process.zzPath._seq )
process.ZZ_4E    = cms.Path(  process.genSkim + process.gen3ZZ4E   + process.zzPath._seq )
process.ZZ_2E2Mu = cms.Path(  process.genSkim + process.gen3ZZ2E2M + process.zzPath._seq )
process.ZZ_GenPtEta_Any   = cms.Path(  process.genSkimPtEta                      + process.zzPath._seq  )
process.ZZ_GenPtEta_4Mu   = cms.Path(  process.genSkimPtEta + process.gen3ZZ4M   + process.zzPath._seq  )
process.ZZ_GenPtEta_4E    = cms.Path(  process.genSkimPtEta + process.gen3ZZ4E   + process.zzPath._seq  )
process.ZZ_GenPtEta_2E2Mu = cms.Path(  process.genSkimPtEta + process.gen3ZZ2E2M + process.zzPath._seq  )
process.ZZ_LepMonitor = cms.Path( process.gen3RecoSeq + process.gen3FilterAny + process.leptonPath._seq )

## Schedule without MC matching
process.schedule = cms.Schedule(process.zzPath, process.leptonPath, process.count4lPath, process.zPath, process.zlPath, process.zllPath)

## Add also paths with RECO classification
process.schedule.extend([ process.zzPath_4E, process.zzPath_4M, process.zzPath_2E2M ])
process.schedule.extend([ process.zzPath_4E_3Path, process.zzPath_4M_3Path ]) # not commissioned yet

## Add to schedules paths with MC matching
if False and isMC:
    process.schedule.extend([ process.ZZ_Any, process.ZZ_4Mu, process.ZZ_4E, process.ZZ_2E2Mu ])
    process.schedule.extend([ process.ZZ_GenPtEta_Any, process.ZZ_GenPtEta_4Mu, process.ZZ_GenPtEta_4E, process.ZZ_GenPtEta_2E2Mu ])

process.TFileService = cms.Service("TFileService", fileName = cms.string("hzzTree.root"))
