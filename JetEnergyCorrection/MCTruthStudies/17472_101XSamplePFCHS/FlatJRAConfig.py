import FWCore.ParameterSet.Config as cms

process = cms.Process("JRA")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/RunIISummer18DR/QCD_Pt-15to7000_TuneCP5_Flat_13TeV_pythia8/AODSIM/FlatPU0to70_101X_upgrade2018_realistic_v7-v2/70000/FED6701D-586E-E811-B66E-0CC47A4D76A2.root')
)
process.HFRecalParameterBlock = cms.PSet(
    HFdepthOneParameterA = cms.vdouble(
        0.004123, 0.00602, 0.008201, 0.010489, 0.013379,
        0.016997, 0.021464, 0.027371, 0.034195, 0.044807,
        0.058939, 0.125497
    ),
    HFdepthOneParameterB = cms.vdouble(
        -4e-06, -2e-06, 0.0, 4e-06, 1.5e-05,
        2.6e-05, 6.3e-05, 8.4e-05, 0.00016, 0.000107,
        0.000425, 0.000209
    ),
    HFdepthTwoParameterA = cms.vdouble(
        0.002861, 0.004168, 0.0064, 0.008388, 0.011601,
        0.014425, 0.018633, 0.023232, 0.028274, 0.035447,
        0.051579, 0.086593
    ),
    HFdepthTwoParameterB = cms.vdouble(
        -2e-06, -0.0, -7e-06, -6e-06, -2e-06,
        1e-06, 1.9e-05, 3.1e-05, 6.7e-05, 1.2e-05,
        0.000157, -3e-06
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(True)
)

process.puppiCentral = cms.VPSet(cms.PSet(
    algoId = cms.int32(5),
    applyLowPUCorr = cms.bool(True),
    combOpt = cms.int32(0),
    cone = cms.double(0.4),
    rmsPtMin = cms.double(0.1),
    rmsScaleFactor = cms.double(1.0),
    useCharged = cms.bool(True)
))

process.puppiForward = cms.VPSet(cms.PSet(
    algoId = cms.int32(5),
    applyLowPUCorr = cms.bool(True),
    combOpt = cms.int32(0),
    cone = cms.double(0.4),
    rmsPtMin = cms.double(0.5),
    rmsScaleFactor = cms.double(1.0),
    useCharged = cms.bool(False)
))

process.ak4GenJetsNoNu = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('GenJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nSigmaPU = cms.double(1.0),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("genParticlesForJetsNoNu"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak4PFCHSJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.4),
    src = cms.InputTag("pfNoPileUpJME"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak4PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.4),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak4PUPPIJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.4),
    src = cms.InputTag("puppi"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak4pfGenToParton = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak4GenJetsNoNu"),
    partons = cms.InputTag("partons")
)


process.ak4pfJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfGenPtEta"),
    srcRec = cms.InputTag("ak4pfPtEta")
)


process.ak4pfJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfPtEtaUncor"),
    srcRec = cms.InputTag("ak4pfPtEta")
)


process.ak4pfchsGenToParton = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak4GenJetsNoNu"),
    partons = cms.InputTag("partons")
)
process.ak4pfchsAODGenToParton = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak4GenJetsNoNu"),
    partons = cms.InputTag("partons")
)

process.ak4pfchsJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfchsGenPtEta"),
    srcRec = cms.InputTag("ak4pfchsPtEta")
)
process.ak4pfchsAODJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfchsAODGenPtEta"),
    srcRec = cms.InputTag("ak4pfchsAODPtEta")
)


process.ak4pfchsJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfchsPtEtaUncor"),
    srcRec = cms.InputTag("ak4pfchsPtEta")
)
process.ak4pfchsAODJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfchsAODPtEtaUncor"),
    srcRec = cms.InputTag("ak4pfchsAODPtEta")
)


process.ak4puppiGenToParton = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak4GenJetsNoNu"),
    partons = cms.InputTag("partons")
)


process.ak4puppiJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4puppiGenPtEta"),
    srcRec = cms.InputTag("ak4puppiPtEta")
)


process.ak4puppiJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4puppiPtEtaUncor"),
    srcRec = cms.InputTag("ak4puppiPtEta")
)


process.ak8GenJetsNoNu = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('GenJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nSigmaPU = cms.double(1.0),
    rParam = cms.double(0.8),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("genParticlesForJetsNoNu"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak8PFCHSJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.8),
    src = cms.InputTag("pfNoPileUpJME"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak8PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.8),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak8PUPPIJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(3.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.8),
    src = cms.InputTag("puppi"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak8pfGenToParton = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak8GenJetsNoNu"),
    partons = cms.InputTag("partons")
)


process.ak8pfJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak8pfGenPtEta"),
    srcRec = cms.InputTag("ak8pfPtEta")
)


process.ak8pfJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak8pfPtEtaUncor"),
    srcRec = cms.InputTag("ak8pfPtEta")
)


process.ak8pfchsGenToParton = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak8GenJetsNoNu"),
    partons = cms.InputTag("partons")
)


process.ak8pfchsJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak8pfchsGenPtEta"),
    srcRec = cms.InputTag("ak8pfchsPtEta")
)


process.ak8pfchsJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak8pfchsPtEtaUncor"),
    srcRec = cms.InputTag("ak8pfchsPtEta")
)


process.ak8puppiGenToParton = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak8GenJetsNoNu"),
    partons = cms.InputTag("partons")
)


process.ak8puppiJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak8puppiGenPtEta"),
    srcRec = cms.InputTag("ak8puppiPtEta")
)


process.ak8puppiJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak8puppiPtEtaUncor"),
    srcRec = cms.InputTag("ak8puppiPtEta")
)


process.genParticlesForJetsNoNu = cms.EDProducer("InputGenJetsParticleSelector",
    excludeFromResonancePids = cms.vuint32(12, 13, 14, 16),
    excludeResonances = cms.bool(False),
    ignoreParticleIDs = cms.vuint32(
        1000022, 1000012, 1000014, 1000016, 2000012,
        2000014, 2000016, 1000039, 5100039, 4000012,
        4000014, 4000016, 9900012, 9900014, 9900016,
        39, 12, 14, 16
    ),
    partonicFinalState = cms.bool(False),
    src = cms.InputTag("genParticles"),
    tausAsJets = cms.bool(False)
)


process.kt6PFJetsRhos = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('Kt'),
    jetPtMin = cms.double(5.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1,
        0, 1, 2, 3, 4,
        5
    ),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.6),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.kt6PFchsJetsRhos = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('Kt'),
    jetPtMin = cms.double(5.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1,
        0, 1, 2, 3, 4,
        5
    ),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.6),
    src = cms.InputTag("pfNoPileUpJME"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.partons = cms.EDProducer("PartonSelector",
    skipFirstN = cms.uint32(0),
    src = cms.InputTag("genParticles"),
    withLeptons = cms.bool(False)
)


process.pfNoPileUpJME = cms.EDProducer("TPPFCandidatesOnPFCandidates",
    bottomCollection = cms.InputTag("particleFlowPtrs"),
    enable = cms.bool(True),
    name = cms.untracked.string('pileUpOnPFCandidates'),
    topCollection = cms.InputTag("pfPileUpJME"),
    verbose = cms.untracked.bool(False)
)


process.pfPileUpJME = cms.EDProducer("PFPileUp",
    Enable = cms.bool(True),
    PFCandidates = cms.InputTag("particleFlowPtrs"),
    Vertices = cms.InputTag("goodOfflinePrimaryVertices"),
    checkClosestZVertex = cms.bool(False),
    verbose = cms.untracked.bool(False)
)


process.puppi = cms.EDProducer("PuppiProducer",
    DeltaZCut = cms.double(0.3),
    MinPuppiWeight = cms.double(0.01),
    PtMaxNeutrals = cms.double(200.0),
    UseDeltaZCut = cms.bool(True),
    algos = cms.VPSet(
        cms.PSet(
            EtaMaxExtrap = cms.double(2.0),
            MedEtaSF = cms.vdouble(1.0),
            MinNeutralPt = cms.vdouble(0.2),
            MinNeutralPtSlope = cms.vdouble(0.015),
            RMSEtaSF = cms.vdouble(1.0),
            etaMax = cms.vdouble(2.5),
            etaMin = cms.vdouble(0.0),
            ptMin = cms.vdouble(0.0),
            puppiAlgos = cms.VPSet(cms.PSet(
                algoId = cms.int32(5),
                applyLowPUCorr = cms.bool(True),
                combOpt = cms.int32(0),
                cone = cms.double(0.4),
                rmsPtMin = cms.double(0.1),
                rmsScaleFactor = cms.double(1.0),
                useCharged = cms.bool(True)
            ))
        ),
        cms.PSet(
            EtaMaxExtrap = cms.double(2.0),
            MedEtaSF = cms.vdouble(0.9, 0.75),
            MinNeutralPt = cms.vdouble(1.7, 2.0),
            MinNeutralPtSlope = cms.vdouble(0.08, 0.08),
            RMSEtaSF = cms.vdouble(1.2, 0.95),
            etaMax = cms.vdouble(3.0, 10.0),
            etaMin = cms.vdouble(2.5, 3.0),
            ptMin = cms.vdouble(0.0, 0.0),
            puppiAlgos = cms.VPSet(cms.PSet(
                algoId = cms.int32(5),
                applyLowPUCorr = cms.bool(True),
                combOpt = cms.int32(0),
                cone = cms.double(0.4),
                rmsPtMin = cms.double(0.5),
                rmsScaleFactor = cms.double(1.0),
                useCharged = cms.bool(False)
            ))
        )
    ),
    applyCHS = cms.bool(True),
    candName = cms.InputTag("particleFlow"),
    clonePackedCands = cms.bool(False),
    invertPuppi = cms.bool(False),
    puppiDiagnostics = cms.bool(False),
    puppiForLeptons = cms.bool(False),
    useExistingWeights = cms.bool(False),
    useExp = cms.bool(False),
    useWeightsNoLep = cms.bool(False),
    vertexName = cms.InputTag("offlinePrimaryVertices"),
    vtxNdofCut = cms.int32(4),
    vtxZCut = cms.double(24)
)


process.ak4pfGenPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4GenJetsNoNu")
)


process.ak4pfPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFJets")
)


process.ak4pfPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFJets")
)


process.ak4pfchsGenPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4GenJetsNoNu")
)
process.ak4pfchsAODGenPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4GenJetsNoNu")
)


process.ak4pfchsPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFCHSJets")
)
process.ak4pfchsAODPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFJetsCHS")
)


process.ak4pfchsPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFCHSJets")
)
process.ak4pfchsAODPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFJetsCHS")
)


process.ak4puppiGenPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4GenJetsNoNu")
)


process.ak4puppiPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PUPPIJets")
)


process.ak4puppiPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PUPPIJets")
)


process.ak8pfGenPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8GenJetsNoNu")
)


process.ak8pfPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8PFJets")
)


process.ak8pfPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8PFJets")
)


process.ak8pfchsGenPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8GenJetsNoNu")
)


process.ak8pfchsPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8PFCHSJets")
)


process.ak8pfchsPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8PFCHSJets")
)


process.ak8puppiGenPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8GenJetsNoNu")
)


process.ak8puppiPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8PUPPIJets")
)


process.ak8puppiPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak8PUPPIJets")
)


process.goodOfflinePrimaryVertices = cms.EDFilter("VertexSelector",
    cut = cms.string('!isFake && ndof >= 4.0 && abs(z) <= 24.0 && abs(position.Rho) <= 2.0'),
    filter = cms.bool(False),
    src = cms.InputTag("offlinePrimaryVertices")
)


process.ak4pf = cms.EDAnalyzer("JetResponseAnalyzer",
    deltaRMax = cms.double(0.25),
    deltaRPartonMax = cms.double(0.25),
    doComposition = cms.bool(True),
    doFlavor = cms.bool(True),
    doHLT = cms.bool(False),
    doJetPt = cms.bool(True),
    doRefPt = cms.bool(True),
    jecLabel = cms.string(''),
    nRefMax = cms.uint32(0),
    saveCandidates = cms.bool(False),
    srcGenParticles = cms.InputTag("genParticles"),
    srcJetToUncorJetMap = cms.InputTag("ak4pfJetToUncorJet","rec2gen"),
    srcPFCandidates = cms.InputTag("particleFlow"),
    srcRef = cms.InputTag("ak4pfGenPtEta"),
    srcRefToJetMap = cms.InputTag("ak4pfJetToRef","gen2rec"),
    srcRefToPartonMap = cms.InputTag("ak4pfGenToParton"),
    srcRho = cms.InputTag("fixedGridRhoFastjetAll"),
    srcRhoHLT = cms.InputTag(""),
    srcRhos = cms.InputTag("kt6PFJetsRhos","rhos"),
    srcVtx = cms.InputTag("offlinePrimaryVertices")
)


process.ak4pfchs = cms.EDAnalyzer("JetResponseAnalyzer",
    deltaRMax = cms.double(0.25),
    deltaRPartonMax = cms.double(0.25),
    doComposition = cms.bool(True),
    doFlavor = cms.bool(True),
    doHLT = cms.bool(False),
    doJetPt = cms.bool(True),
    doRefPt = cms.bool(True),
    jecLabel = cms.string(''),
    nRefMax = cms.uint32(0),
    saveCandidates = cms.bool(False),
    srcGenParticles = cms.InputTag("genParticles"),
    srcJetToUncorJetMap = cms.InputTag("ak4pfchsJetToUncorJet","rec2gen"),
    srcPFCandidates = cms.InputTag("pfNoPileUpJME"),
    srcRef = cms.InputTag("ak4pfchsGenPtEta"),
    srcRefToJetMap = cms.InputTag("ak4pfchsJetToRef","gen2rec"),
    srcRefToPartonMap = cms.InputTag("ak4pfchsGenToParton"),
    srcRho = cms.InputTag("fixedGridRhoFastjetAll"),
    srcRhoHLT = cms.InputTag(""),
    srcRhos = cms.InputTag("kt6PFchsJetsRhos","rhos"),
    srcVtx = cms.InputTag("offlinePrimaryVertices")
)
process.ak4pfchsAOD = cms.EDAnalyzer("JetResponseAnalyzer",
    deltaRMax = cms.double(0.25),
    deltaRPartonMax = cms.double(0.25),
    doComposition = cms.bool(True),
    doFlavor = cms.bool(True),
    doHLT = cms.bool(False),
    doJetPt = cms.bool(True),
    doRefPt = cms.bool(True),
    jecLabel = cms.string(''),
    nRefMax = cms.uint32(0),
    saveCandidates = cms.bool(False),
    srcGenParticles = cms.InputTag("genParticles"),
    srcJetToUncorJetMap = cms.InputTag("ak4pfchsAODJetToUncorJet","rec2gen"),
    srcPFCandidates = cms.InputTag("pfNoPileUpJME"),
    srcRef = cms.InputTag("ak4pfchsAODGenPtEta"),
    srcRefToJetMap = cms.InputTag("ak4pfchsAODJetToRef","gen2rec"),
    srcRefToPartonMap = cms.InputTag("ak4pfchsAODGenToParton"),
    srcRho = cms.InputTag("fixedGridRhoFastjetAll"),
    srcRhoHLT = cms.InputTag(""),
    srcRhos = cms.InputTag("kt6PFchsJetsRhos","rhos"),
    srcVtx = cms.InputTag("offlinePrimaryVertices")
)


process.ak4puppi = cms.EDAnalyzer("JetResponseAnalyzer",
    deltaRMax = cms.double(0.25),
    deltaRPartonMax = cms.double(0.25),
    doComposition = cms.bool(True),
    doFlavor = cms.bool(True),
    doHLT = cms.bool(False),
    doJetPt = cms.bool(True),
    doRefPt = cms.bool(True),
    jecLabel = cms.string(''),
    nRefMax = cms.uint32(0),
    saveCandidates = cms.bool(False),
    srcGenParticles = cms.InputTag("genParticles"),
    srcJetToUncorJetMap = cms.InputTag("ak4puppiJetToUncorJet","rec2gen"),
    srcPFCandidates = cms.InputTag("puppi"),
    srcRef = cms.InputTag("ak4puppiGenPtEta"),
    srcRefToJetMap = cms.InputTag("ak4puppiJetToRef","gen2rec"),
    srcRefToPartonMap = cms.InputTag("ak4puppiGenToParton"),
    srcRho = cms.InputTag("fixedGridRhoFastjetAll"),
    srcRhoHLT = cms.InputTag(""),
    srcRhos = cms.InputTag("kt6PFJetsRhos","rhos"),
    srcVtx = cms.InputTag("offlinePrimaryVertices")
)


process.ak8pf = cms.EDAnalyzer("JetResponseAnalyzer",
    deltaRMax = cms.double(0.25),
    deltaRPartonMax = cms.double(0.25),
    doComposition = cms.bool(True),
    doFlavor = cms.bool(True),
    doHLT = cms.bool(False),
    doJetPt = cms.bool(True),
    doRefPt = cms.bool(True),
    jecLabel = cms.string(''),
    nRefMax = cms.uint32(0),
    saveCandidates = cms.bool(False),
    srcGenParticles = cms.InputTag("genParticles"),
    srcJetToUncorJetMap = cms.InputTag("ak8pfJetToUncorJet","rec2gen"),
    srcPFCandidates = cms.InputTag("particleFlow"),
    srcRef = cms.InputTag("ak8pfGenPtEta"),
    srcRefToJetMap = cms.InputTag("ak8pfJetToRef","gen2rec"),
    srcRefToPartonMap = cms.InputTag("ak8pfGenToParton"),
    srcRho = cms.InputTag("fixedGridRhoFastjetAll"),
    srcRhoHLT = cms.InputTag(""),
    srcRhos = cms.InputTag("kt6PFJetsRhos","rhos"),
    srcVtx = cms.InputTag("offlinePrimaryVertices")
)


process.ak8pfchs = cms.EDAnalyzer("JetResponseAnalyzer",
    deltaRMax = cms.double(0.25),
    deltaRPartonMax = cms.double(0.25),
    doComposition = cms.bool(True),
    doFlavor = cms.bool(True),
    doHLT = cms.bool(False),
    doJetPt = cms.bool(True),
    doRefPt = cms.bool(True),
    jecLabel = cms.string(''),
    nRefMax = cms.uint32(0),
    saveCandidates = cms.bool(False),
    srcGenParticles = cms.InputTag("genParticles"),
    srcJetToUncorJetMap = cms.InputTag("ak8pfchsJetToUncorJet","rec2gen"),
    srcPFCandidates = cms.InputTag("pfNoPileUpJME"),
    srcRef = cms.InputTag("ak8pfchsGenPtEta"),
    srcRefToJetMap = cms.InputTag("ak8pfchsJetToRef","gen2rec"),
    srcRefToPartonMap = cms.InputTag("ak8pfchsGenToParton"),
    srcRho = cms.InputTag("fixedGridRhoFastjetAll"),
    srcRhoHLT = cms.InputTag(""),
    srcRhos = cms.InputTag("kt6PFchsJetsRhos","rhos"),
    srcVtx = cms.InputTag("offlinePrimaryVertices")
)


process.ak8puppi = cms.EDAnalyzer("JetResponseAnalyzer",
    deltaRMax = cms.double(0.25),
    deltaRPartonMax = cms.double(0.25),
    doComposition = cms.bool(True),
    doFlavor = cms.bool(True),
    doHLT = cms.bool(False),
    doJetPt = cms.bool(True),
    doRefPt = cms.bool(True),
    jecLabel = cms.string(''),
    nRefMax = cms.uint32(0),
    saveCandidates = cms.bool(False),
    srcGenParticles = cms.InputTag("genParticles"),
    srcJetToUncorJetMap = cms.InputTag("ak8puppiJetToUncorJet","rec2gen"),
    srcPFCandidates = cms.InputTag("puppi"),
    srcRef = cms.InputTag("ak8puppiGenPtEta"),
    srcRefToJetMap = cms.InputTag("ak8puppiJetToRef","gen2rec"),
    srcRefToPartonMap = cms.InputTag("ak8puppiGenToParton"),
    srcRho = cms.InputTag("fixedGridRhoFastjetAll"),
    srcRhoHLT = cms.InputTag(""),
    srcRhos = cms.InputTag("kt6PFJetsRhos","rhos"),
    srcVtx = cms.InputTag("offlinePrimaryVertices")
)


process.MessageLogger = cms.Service("MessageLogger",
    FrameworkJobReport = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        optionalPSet = cms.untracked.bool(True)
    ),
    categories = cms.untracked.vstring(
        'FwkJob',
        'FwkReport',
        'FwkSummary',
        'Root_NoDictionary'
    ),
    cerr = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        FwkReport = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(100)
        ),
        FwkSummary = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(1)
        ),
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        noTimeStamps = cms.untracked.bool(False),
        optionalPSet = cms.untracked.bool(True),
        threshold = cms.untracked.string('INFO')
    ),
    cerr_stats = cms.untracked.PSet(
        optionalPSet = cms.untracked.bool(True),
        output = cms.untracked.string('cerr'),
        threshold = cms.untracked.string('WARNING')
    ),
    cout = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    debugModules = cms.untracked.vstring(),
    debugs = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    default = cms.untracked.PSet(

    ),
    destinations = cms.untracked.vstring(
        'warnings',
        'errors',
        'infos',
        'debugs',
        'cout',
        'cerr'
    ),
    errors = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    fwkJobReports = cms.untracked.vstring('FrameworkJobReport'),
    infos = cms.untracked.PSet(
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        optionalPSet = cms.untracked.bool(True),
        placeholder = cms.untracked.bool(True)
    ),
    statistics = cms.untracked.vstring('cerr_stats'),
    suppressDebug = cms.untracked.vstring(),
    suppressInfo = cms.untracked.vstring(),
    suppressWarning = cms.untracked.vstring(),
    warnings = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    )
)


process.TFileService = cms.Service("TFileService",
    closeFileFast = cms.untracked.bool(False),
    fileName = cms.string('/tmp/chenyi/JRA.root')
)


process.CSCGeometryESModule = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    debugV = cms.untracked.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useDDD = cms.bool(True),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.CaloGeometryBuilder = cms.ESProducer("CaloGeometryBuilder",
    SelectedCalos = cms.vstring(
        'HCAL',
        'ZDC',
        'CASTOR',
        'EcalBarrel',
        'EcalEndcap',
        'EcalPreshower',
        'TOWER'
    )
)


process.CaloTopologyBuilder = cms.ESProducer("CaloTopologyBuilder")


process.CaloTowerHardcodeGeometryEP = cms.ESProducer("CaloTowerHardcodeGeometryEP")


process.CaloTowerTopologyEP = cms.ESProducer("CaloTowerTopologyEP")


process.CastorDbProducer = cms.ESProducer("CastorDbProducer",
    appendToDataLabel = cms.string('')
)


process.CastorHardcodeGeometryEP = cms.ESProducer("CastorHardcodeGeometryEP")


process.DTGeometryESModule = cms.ESProducer("DTGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(True)
)


process.EcalBarrelGeometryEP = cms.ESProducer("EcalBarrelGeometryEP",
    applyAlignment = cms.bool(False)
)


process.EcalElectronicsMappingBuilder = cms.ESProducer("EcalElectronicsMappingBuilder")


process.EcalEndcapGeometryEP = cms.ESProducer("EcalEndcapGeometryEP",
    applyAlignment = cms.bool(False)
)


process.EcalLaserCorrectionService = cms.ESProducer("EcalLaserCorrectionService")


process.EcalPreshowerGeometryEP = cms.ESProducer("EcalPreshowerGeometryEP",
    applyAlignment = cms.bool(False)
)


process.EcalTrigTowerConstituentsMapBuilder = cms.ESProducer("EcalTrigTowerConstituentsMapBuilder",
    MapFile = cms.untracked.string('Geometry/EcalMapping/data/EndCap_TTMap.txt')
)


process.GlobalTrackingGeometryESProducer = cms.ESProducer("GlobalTrackingGeometryESProducer")


process.HcalHardcodeGeometryEP = cms.ESProducer("HcalHardcodeGeometryEP",
    UseOldLoader = cms.bool(False)
)


process.MuonDetLayerGeometryESProducer = cms.ESProducer("MuonDetLayerGeometryESProducer")


process.MuonNumberingInitialization = cms.ESProducer("MuonNumberingInitialization")


process.ParabolicParametrizedMagneticFieldProducer = cms.ESProducer("AutoParametrizedMagneticFieldProducer",
    label = cms.untracked.string('ParabolicMf'),
    valueOverride = cms.int32(-1),
    version = cms.string('Parabolic')
)


process.RPCGeometryESModule = cms.ESProducer("RPCGeometryESModule",
    compatibiltyWith11 = cms.untracked.bool(True),
    useDDD = cms.untracked.bool(True)
)


process.SiStripRecHitMatcherESProducer = cms.ESProducer("SiStripRecHitMatcherESProducer",
    ComponentName = cms.string('StandardMatcher'),
    NSigmaInside = cms.double(3.0),
    PreFilter = cms.bool(False)
)


process.StripCPEfromTrackAngleESProducer = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('StripCPEfromTrackAngle'),
    ComponentType = cms.string('StripCPEfromTrackAngle'),
    parameters = cms.PSet(
        mLC_P0 = cms.double(-0.326),
        mLC_P1 = cms.double(0.618),
        mLC_P2 = cms.double(0.3),
        mTEC_P0 = cms.double(-1.885),
        mTEC_P1 = cms.double(0.471),
        mTIB_P0 = cms.double(-0.742),
        mTIB_P1 = cms.double(0.202),
        mTID_P0 = cms.double(-1.427),
        mTID_P1 = cms.double(0.433),
        mTOB_P0 = cms.double(-1.026),
        mTOB_P1 = cms.double(0.253),
        maxChgOneMIP = cms.double(6000.0),
        useLegacyError = cms.bool(False)
    )
)


process.TrackerRecoGeometryESProducer = cms.ESProducer("TrackerRecoGeometryESProducer")


process.VolumeBasedMagneticFieldESProducer = cms.ESProducer("VolumeBasedMagneticFieldESProducerFromDB",
    debugBuilder = cms.untracked.bool(False),
    label = cms.untracked.string(''),
    valueOverride = cms.int32(-1)
)


process.ZdcHardcodeGeometryEP = cms.ESProducer("ZdcHardcodeGeometryEP")


process.fakeForIdealAlignment = cms.ESProducer("FakeAlignmentProducer",
    appendToDataLabel = cms.string('fakeForIdeal')
)


process.hcalDDDRecConstants = cms.ESProducer("HcalDDDRecConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalDDDSimConstants = cms.ESProducer("HcalDDDSimConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalParameters = cms.ESProducer("HcalParametersESModule",
    appendToDataLabel = cms.string('')
)


process.hcalTopologyIdeal = cms.ESProducer("HcalTopologyIdealEP",
    Exclude = cms.untracked.string(''),
    MergePosition = cms.untracked.bool(False),
    appendToDataLabel = cms.string('')
)


process.hcal_db_producer = cms.ESProducer("HcalDbProducer",
    dump = cms.untracked.vstring(''),
    file = cms.untracked.string('')
)


process.idealForDigiCSCGeometry = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    debugV = cms.untracked.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useDDD = cms.bool(True),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.idealForDigiDTGeometry = cms.ESProducer("DTGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    fromDDD = cms.bool(True)
)


process.idealForDigiTrackerGeometry = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    fromDDD = cms.bool(True)
)


process.siPixelQualityESProducer = cms.ESProducer("SiPixelQualityESProducer",
    ListOfRecordToMerge = cms.VPSet(
        cms.PSet(
            record = cms.string('SiPixelQualityFromDbRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiPixelDetVOffRcd'),
            tag = cms.string('')
        )
    )
)


process.siStripBackPlaneCorrectionDepESProducer = cms.ESProducer("SiStripBackPlaneCorrectionDepESProducer",
    BackPlaneCorrectionDeconvMode = cms.PSet(
        label = cms.untracked.string('deconvolution'),
        record = cms.string('SiStripBackPlaneCorrectionRcd')
    ),
    BackPlaneCorrectionPeakMode = cms.PSet(
        label = cms.untracked.string('peak'),
        record = cms.string('SiStripBackPlaneCorrectionRcd')
    ),
    LatencyRecord = cms.PSet(
        label = cms.untracked.string(''),
        record = cms.string('SiStripLatencyRcd')
    )
)


process.siStripGainESProducer = cms.ESProducer("SiStripGainESProducer",
    APVGain = cms.VPSet(
        cms.PSet(
            Label = cms.untracked.string(''),
            NormalizationFactor = cms.untracked.double(1.0),
            Record = cms.string('SiStripApvGainRcd')
        ),
        cms.PSet(
            Label = cms.untracked.string(''),
            NormalizationFactor = cms.untracked.double(1.0),
            Record = cms.string('SiStripApvGain2Rcd')
        )
    ),
    AutomaticNormalization = cms.bool(False),
    appendToDataLabel = cms.string(''),
    printDebug = cms.untracked.bool(False)
)


process.siStripLorentzAngleDepESProducer = cms.ESProducer("SiStripLorentzAngleDepESProducer",
    LatencyRecord = cms.PSet(
        label = cms.untracked.string(''),
        record = cms.string('SiStripLatencyRcd')
    ),
    LorentzAngleDeconvMode = cms.PSet(
        label = cms.untracked.string('deconvolution'),
        record = cms.string('SiStripLorentzAngleRcd')
    ),
    LorentzAnglePeakMode = cms.PSet(
        label = cms.untracked.string('peak'),
        record = cms.string('SiStripLorentzAngleRcd')
    )
)


process.siStripQualityESProducer = cms.ESProducer("SiStripQualityESProducer",
    ListOfRecordToMerge = cms.VPSet(
        cms.PSet(
            record = cms.string('SiStripDetVOffRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripDetCablingRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('RunInfoRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadChannelRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadFiberRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadModuleRcd'),
            tag = cms.string('')
        ),
        cms.PSet(
            record = cms.string('SiStripBadStripRcd'),
            tag = cms.string('')
        )
    ),
    PrintDebugOutput = cms.bool(False),
    ReduceGranularity = cms.bool(False),
    ThresholdForReducedGranularity = cms.double(0.3),
    UseEmptyRunInfo = cms.bool(False),
    appendToDataLabel = cms.string('')
)


process.sistripconn = cms.ESProducer("SiStripConnectivity")


process.stripCPEESProducer = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('stripCPE'),
    ComponentType = cms.string('SimpleStripCPE'),
    parameters = cms.PSet(

    )
)


process.trackerGeometry = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(True)
)


process.trackerNumberingGeometry = cms.ESProducer("TrackerGeometricDetESModule",
    appendToDataLabel = cms.string(''),
    fromDDD = cms.bool(True)
)


process.trackerParameters = cms.ESProducer("TrackerParametersESModule",
    appendToDataLabel = cms.string('')
)


process.trackerTopology = cms.ESProducer("TrackerTopologyEP",
    appendToDataLabel = cms.string('')
)


process.GlobalTag = cms.ESSource("PoolDBESSource",
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    DumpStat = cms.untracked.bool(False),
    ReconnectEachRun = cms.untracked.bool(False),
    RefreshAlways = cms.untracked.bool(False),
    RefreshEachRun = cms.untracked.bool(False),
    RefreshOpenIOVs = cms.untracked.bool(False),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
    globaltag = cms.string('101X_dataRun2_v7'),
    pfnPostfix = cms.untracked.string(''),
    pfnPrefix = cms.untracked.string(''),
    snapshotTime = cms.string(''),
    toGet = cms.VPSet()
)


process.HcalTimeSlewEP = cms.ESSource("HcalTimeSlewEP",
    appendToDataLabel = cms.string('HBHE'),
    timeSlewParametersM2 = cms.VPSet(
        cms.PSet(
            slope = cms.double(-3.178648),
            tmax = cms.double(16.0),
            tzero = cms.double(23.960177)
        ),
        cms.PSet(
            slope = cms.double(-1.556668),
            tmax = cms.double(10.0),
            tzero = cms.double(13.307784)
        ),
        cms.PSet(
            slope = cms.double(-1.075824),
            tmax = cms.double(6.25),
            tzero = cms.double(9.109694)
        )
    ),
    timeSlewParametersM3 = cms.VPSet(
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(12.2999),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-2.19142),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(0.0),
            tspar2_siPM = cms.double(0.0)
        ),
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(15.5),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-3.2),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(32.0),
            tspar2_siPM = cms.double(0.0)
        ),
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(12.2999),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-2.19142),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(0.0),
            tspar2_siPM = cms.double(0.0)
        ),
        cms.PSet(
            cap = cms.double(6.0),
            tspar0 = cms.double(12.2999),
            tspar0_siPM = cms.double(0.0),
            tspar1 = cms.double(-2.19142),
            tspar1_siPM = cms.double(0.0),
            tspar2 = cms.double(0.0),
            tspar2_siPM = cms.double(0.0)
        )
    )
)


process.XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring( (
        'Geometry/CMSCommonData/data/materials.xml',
        'Geometry/CMSCommonData/data/rotations.xml',
        'Geometry/CMSCommonData/data/normal/cmsextent.xml',
        'Geometry/CMSCommonData/data/cms.xml',
        'Geometry/CMSCommonData/data/cmsMother.xml',
        'Geometry/CMSCommonData/data/cmsTracker.xml',
        'Geometry/CMSCommonData/data/caloBase.xml',
        'Geometry/CMSCommonData/data/cmsCalo.xml',
        'Geometry/CMSCommonData/data/muonBase.xml',
        'Geometry/CMSCommonData/data/cmsMuon.xml',
        'Geometry/CMSCommonData/data/mgnt.xml',
        'Geometry/CMSCommonData/data/beampipe.xml',
        'Geometry/CMSCommonData/data/cmsBeam.xml',
        'Geometry/CMSCommonData/data/muonMB.xml',
        'Geometry/CMSCommonData/data/muonMagnet.xml',
        'Geometry/TrackerCommonData/data/trackerParameters.xml',
        'Geometry/TrackerCommonData/data/pixfwdMaterials.xml',
        'Geometry/TrackerCommonData/data/pixfwdCommon.xml',
        'Geometry/TrackerCommonData/data/pixfwdPlaq.xml',
        'Geometry/TrackerCommonData/data/pixfwdPlaq1x2.xml',
        'Geometry/TrackerCommonData/data/pixfwdPlaq1x5.xml',
        'Geometry/TrackerCommonData/data/pixfwdPlaq2x3.xml',
        'Geometry/TrackerCommonData/data/pixfwdPlaq2x4.xml',
        'Geometry/TrackerCommonData/data/pixfwdPlaq2x5.xml',
        'Geometry/TrackerCommonData/data/pixfwdPanelBase.xml',
        'Geometry/TrackerCommonData/data/pixfwdPanel.xml',
        'Geometry/TrackerCommonData/data/pixfwdBlade.xml',
        'Geometry/TrackerCommonData/data/pixfwdNipple.xml',
        'Geometry/TrackerCommonData/data/pixfwdDisk.xml',
        'Geometry/TrackerCommonData/data/pixfwdCylinder.xml',
        'Geometry/TrackerCommonData/data/pixfwd.xml',
        'Geometry/TrackerCommonData/data/pixbarmaterial.xml',
        'Geometry/TrackerCommonData/data/pixbarladder.xml',
        'Geometry/TrackerCommonData/data/pixbarladderfull.xml',
        'Geometry/TrackerCommonData/data/pixbarladderhalf.xml',
        'Geometry/TrackerCommonData/data/pixbarlayer.xml',
        'Geometry/TrackerCommonData/data/pixbarlayer0.xml',
        'Geometry/TrackerCommonData/data/pixbarlayer1.xml',
        'Geometry/TrackerCommonData/data/pixbarlayer2.xml',
        'Geometry/TrackerCommonData/data/pixbar.xml',
        'Geometry/TrackerCommonData/data/tibtidcommonmaterial.xml',
        'Geometry/TrackerCommonData/data/tibmaterial.xml',
        'Geometry/TrackerCommonData/data/tibmodpar.xml',
        'Geometry/TrackerCommonData/data/tibmodule0.xml',
        'Geometry/TrackerCommonData/data/tibmodule0a.xml',
        'Geometry/TrackerCommonData/data/tibmodule0b.xml',
        'Geometry/TrackerCommonData/data/tibmodule2.xml',
        'Geometry/TrackerCommonData/data/tibstringpar.xml',
        'Geometry/TrackerCommonData/data/tibstring0ll.xml',
        'Geometry/TrackerCommonData/data/tibstring0lr.xml',
        'Geometry/TrackerCommonData/data/tibstring0ul.xml',
        'Geometry/TrackerCommonData/data/tibstring0ur.xml',
        'Geometry/TrackerCommonData/data/tibstring0.xml',
        'Geometry/TrackerCommonData/data/tibstring1ll.xml',
        'Geometry/TrackerCommonData/data/tibstring1lr.xml',
        'Geometry/TrackerCommonData/data/tibstring1ul.xml',
        'Geometry/TrackerCommonData/data/tibstring1ur.xml',
        'Geometry/TrackerCommonData/data/tibstring1.xml',
        'Geometry/TrackerCommonData/data/tibstring2ll.xml',
        'Geometry/TrackerCommonData/data/tibstring2lr.xml',
        'Geometry/TrackerCommonData/data/tibstring2ul.xml',
        'Geometry/TrackerCommonData/data/tibstring2ur.xml',
        'Geometry/TrackerCommonData/data/tibstring2.xml',
        'Geometry/TrackerCommonData/data/tibstring3ll.xml',
        'Geometry/TrackerCommonData/data/tibstring3lr.xml',
        'Geometry/TrackerCommonData/data/tibstring3ul.xml',
        'Geometry/TrackerCommonData/data/tibstring3ur.xml',
        'Geometry/TrackerCommonData/data/tibstring3.xml',
        'Geometry/TrackerCommonData/data/tiblayerpar.xml',
        'Geometry/TrackerCommonData/data/tiblayer0.xml',
        'Geometry/TrackerCommonData/data/tiblayer1.xml',
        'Geometry/TrackerCommonData/data/tiblayer2.xml',
        'Geometry/TrackerCommonData/data/tiblayer3.xml',
        'Geometry/TrackerCommonData/data/tib.xml',
        'Geometry/TrackerCommonData/data/tidmaterial.xml',
        'Geometry/TrackerCommonData/data/tidmodpar.xml',
        'Geometry/TrackerCommonData/data/tidmodule0.xml',
        'Geometry/TrackerCommonData/data/tidmodule0r.xml',
        'Geometry/TrackerCommonData/data/tidmodule0l.xml',
        'Geometry/TrackerCommonData/data/tidmodule1.xml',
        'Geometry/TrackerCommonData/data/tidmodule1r.xml',
        'Geometry/TrackerCommonData/data/tidmodule1l.xml',
        'Geometry/TrackerCommonData/data/tidmodule2.xml',
        'Geometry/TrackerCommonData/data/tidringpar.xml',
        'Geometry/TrackerCommonData/data/tidring0.xml',
        'Geometry/TrackerCommonData/data/tidring0f.xml',
        'Geometry/TrackerCommonData/data/tidring0b.xml',
        'Geometry/TrackerCommonData/data/tidring1.xml',
        'Geometry/TrackerCommonData/data/tidring1f.xml',
        'Geometry/TrackerCommonData/data/tidring1b.xml',
        'Geometry/TrackerCommonData/data/tidring2.xml',
        'Geometry/TrackerCommonData/data/tid.xml',
        'Geometry/TrackerCommonData/data/tidf.xml',
        'Geometry/TrackerCommonData/data/tidb.xml',
        'Geometry/TrackerCommonData/data/tibtidservices.xml',
        'Geometry/TrackerCommonData/data/tibtidservicesf.xml',
        'Geometry/TrackerCommonData/data/tibtidservicesb.xml',
        'Geometry/TrackerCommonData/data/tobmaterial.xml',
        'Geometry/TrackerCommonData/data/tobmodpar.xml',
        'Geometry/TrackerCommonData/data/tobmodule0.xml',
        'Geometry/TrackerCommonData/data/tobmodule2.xml',
        'Geometry/TrackerCommonData/data/tobmodule4.xml',
        'Geometry/TrackerCommonData/data/tobrodpar.xml',
        'Geometry/TrackerCommonData/data/tobrod0c.xml',
        'Geometry/TrackerCommonData/data/tobrod0l.xml',
        'Geometry/TrackerCommonData/data/tobrod0h.xml',
        'Geometry/TrackerCommonData/data/tobrod0.xml',
        'Geometry/TrackerCommonData/data/tobrod1l.xml',
        'Geometry/TrackerCommonData/data/tobrod1h.xml',
        'Geometry/TrackerCommonData/data/tobrod1.xml',
        'Geometry/TrackerCommonData/data/tobrod2c.xml',
        'Geometry/TrackerCommonData/data/tobrod2l.xml',
        'Geometry/TrackerCommonData/data/tobrod2h.xml',
        'Geometry/TrackerCommonData/data/tobrod2.xml',
        'Geometry/TrackerCommonData/data/tobrod3l.xml',
        'Geometry/TrackerCommonData/data/tobrod3h.xml',
        'Geometry/TrackerCommonData/data/tobrod3.xml',
        'Geometry/TrackerCommonData/data/tobrod4c.xml',
        'Geometry/TrackerCommonData/data/tobrod4l.xml',
        'Geometry/TrackerCommonData/data/tobrod4h.xml',
        'Geometry/TrackerCommonData/data/tobrod4.xml',
        'Geometry/TrackerCommonData/data/tobrod5l.xml',
        'Geometry/TrackerCommonData/data/tobrod5h.xml',
        'Geometry/TrackerCommonData/data/tobrod5.xml',
        'Geometry/TrackerCommonData/data/tob.xml',
        'Geometry/TrackerCommonData/data/tecmaterial.xml',
        'Geometry/TrackerCommonData/data/tecmodpar.xml',
        'Geometry/TrackerCommonData/data/tecmodule0.xml',
        'Geometry/TrackerCommonData/data/tecmodule0r.xml',
        'Geometry/TrackerCommonData/data/tecmodule0s.xml',
        'Geometry/TrackerCommonData/data/tecmodule1.xml',
        'Geometry/TrackerCommonData/data/tecmodule1r.xml',
        'Geometry/TrackerCommonData/data/tecmodule1s.xml',
        'Geometry/TrackerCommonData/data/tecmodule2.xml',
        'Geometry/TrackerCommonData/data/tecmodule3.xml',
        'Geometry/TrackerCommonData/data/tecmodule4.xml',
        'Geometry/TrackerCommonData/data/tecmodule4r.xml',
        'Geometry/TrackerCommonData/data/tecmodule4s.xml',
        'Geometry/TrackerCommonData/data/tecmodule5.xml',
        'Geometry/TrackerCommonData/data/tecmodule6.xml',
        'Geometry/TrackerCommonData/data/tecpetpar.xml',
        'Geometry/TrackerCommonData/data/tecring0.xml',
        'Geometry/TrackerCommonData/data/tecring1.xml',
        'Geometry/TrackerCommonData/data/tecring2.xml',
        'Geometry/TrackerCommonData/data/tecring3.xml',
        'Geometry/TrackerCommonData/data/tecring4.xml',
        'Geometry/TrackerCommonData/data/tecring5.xml',
        'Geometry/TrackerCommonData/data/tecring6.xml',
        'Geometry/TrackerCommonData/data/tecring0f.xml',
        'Geometry/TrackerCommonData/data/tecring1f.xml',
        'Geometry/TrackerCommonData/data/tecring2f.xml',
        'Geometry/TrackerCommonData/data/tecring3f.xml',
        'Geometry/TrackerCommonData/data/tecring4f.xml',
        'Geometry/TrackerCommonData/data/tecring5f.xml',
        'Geometry/TrackerCommonData/data/tecring6f.xml',
        'Geometry/TrackerCommonData/data/tecring0b.xml',
        'Geometry/TrackerCommonData/data/tecring1b.xml',
        'Geometry/TrackerCommonData/data/tecring2b.xml',
        'Geometry/TrackerCommonData/data/tecring3b.xml',
        'Geometry/TrackerCommonData/data/tecring4b.xml',
        'Geometry/TrackerCommonData/data/tecring5b.xml',
        'Geometry/TrackerCommonData/data/tecring6b.xml',
        'Geometry/TrackerCommonData/data/tecpetalf.xml',
        'Geometry/TrackerCommonData/data/tecpetalb.xml',
        'Geometry/TrackerCommonData/data/tecpetal0.xml',
        'Geometry/TrackerCommonData/data/tecpetal0f.xml',
        'Geometry/TrackerCommonData/data/tecpetal0b.xml',
        'Geometry/TrackerCommonData/data/tecpetal3.xml',
        'Geometry/TrackerCommonData/data/tecpetal3f.xml',
        'Geometry/TrackerCommonData/data/tecpetal3b.xml',
        'Geometry/TrackerCommonData/data/tecpetal6f.xml',
        'Geometry/TrackerCommonData/data/tecpetal6b.xml',
        'Geometry/TrackerCommonData/data/tecpetal8f.xml',
        'Geometry/TrackerCommonData/data/tecpetal8b.xml',
        'Geometry/TrackerCommonData/data/tecwheel.xml',
        'Geometry/TrackerCommonData/data/tecwheela.xml',
        'Geometry/TrackerCommonData/data/tecwheelb.xml',
        'Geometry/TrackerCommonData/data/tecwheelc.xml',
        'Geometry/TrackerCommonData/data/tecwheeld.xml',
        'Geometry/TrackerCommonData/data/tecwheel6.xml',
        'Geometry/TrackerCommonData/data/tecservices.xml',
        'Geometry/TrackerCommonData/data/tecbackplate.xml',
        'Geometry/TrackerCommonData/data/tec.xml',
        'Geometry/TrackerCommonData/data/trackermaterial.xml',
        'Geometry/TrackerCommonData/data/tracker.xml',
        'Geometry/TrackerCommonData/data/trackerpixbar.xml',
        'Geometry/TrackerCommonData/data/trackerpixfwd.xml',
        'Geometry/TrackerCommonData/data/trackertibtidservices.xml',
        'Geometry/TrackerCommonData/data/trackertib.xml',
        'Geometry/TrackerCommonData/data/trackertid.xml',
        'Geometry/TrackerCommonData/data/trackertob.xml',
        'Geometry/TrackerCommonData/data/trackertec.xml',
        'Geometry/TrackerCommonData/data/trackerbulkhead.xml',
        'Geometry/TrackerCommonData/data/trackerother.xml',
        'Geometry/EcalCommonData/data/eregalgo.xml',
        'Geometry/EcalCommonData/data/ebalgo.xml',
        'Geometry/EcalCommonData/data/ebcon.xml',
        'Geometry/EcalCommonData/data/ebrot.xml',
        'Geometry/EcalCommonData/data/eecon.xml',
        'Geometry/EcalCommonData/data/eefixed.xml',
        'Geometry/EcalCommonData/data/eehier.xml',
        'Geometry/EcalCommonData/data/eealgo.xml',
        'Geometry/EcalCommonData/data/escon.xml',
        'Geometry/EcalCommonData/data/esalgo.xml',
        'Geometry/EcalCommonData/data/eeF.xml',
        'Geometry/EcalCommonData/data/eeB.xml',
        'Geometry/EcalCommonData/data/ectkcable.xml',
        'Geometry/HcalCommonData/data/hcalrotations.xml',
        'Geometry/HcalCommonData/data/hcalalgo.xml',
        'Geometry/HcalCommonData/data/hcalbarrelalgo.xml',
        'Geometry/HcalCommonData/data/hcalendcapalgo.xml',
        'Geometry/HcalCommonData/data/hcalouteralgo.xml',
        'Geometry/HcalCommonData/data/hcalforwardalgo.xml',
        'Geometry/HcalCommonData/data/average/hcalforwardmaterial.xml',
        'Geometry/HcalCommonData/data/hcalSimNumbering.xml',
        'Geometry/HcalCommonData/data/hcalRecNumbering.xml',
        'Geometry/MuonCommonData/data/mbCommon.xml',
        'Geometry/MuonCommonData/data/mb1.xml',
        'Geometry/MuonCommonData/data/mb2.xml',
        'Geometry/MuonCommonData/data/mb3.xml',
        'Geometry/MuonCommonData/data/mb4.xml',
        'Geometry/MuonCommonData/data/muonYoke.xml',
        'Geometry/MuonCommonData/data/mf.xml',
        'Geometry/ForwardCommonData/data/forward.xml',
        'Geometry/ForwardCommonData/data/bundle/forwardshield.xml',
        'Geometry/ForwardCommonData/data/brmrotations.xml',
        'Geometry/ForwardCommonData/data/brm.xml',
        'Geometry/ForwardCommonData/data/totemMaterials.xml',
        'Geometry/ForwardCommonData/data/totemRotations.xml',
        'Geometry/ForwardCommonData/data/totemt1.xml',
        'Geometry/ForwardCommonData/data/totemt2.xml',
        'Geometry/ForwardCommonData/data/ionpump.xml',
        'Geometry/MuonCommonData/data/muonNumbering.xml',
        'Geometry/TrackerCommonData/data/trackerStructureTopology.xml',
        'Geometry/TrackerSimData/data/trackersens.xml',
        'Geometry/TrackerRecoData/data/trackerRecoMaterial.xml',
        'Geometry/EcalSimData/data/ecalsens.xml',
        'Geometry/HcalCommonData/data/hcalsenspmf.xml',
        'Geometry/HcalSimData/data/hf.xml',
        'Geometry/HcalSimData/data/hfpmt.xml',
        'Geometry/HcalSimData/data/hffibrebundle.xml',
        'Geometry/HcalSimData/data/CaloUtil.xml',
        'Geometry/MuonSimData/data/muonSens.xml',
        'Geometry/DTGeometryBuilder/data/dtSpecsFilter.xml',
        'Geometry/CSCGeometryBuilder/data/cscSpecsFilter.xml',
        'Geometry/CSCGeometryBuilder/data/cscSpecs.xml',
        'Geometry/RPCGeometryBuilder/data/RPCSpecs.xml',
        'Geometry/ForwardCommonData/data/brmsens.xml',
        'Geometry/HcalSimData/data/HcalProdCuts.xml',
        'Geometry/EcalSimData/data/EcalProdCuts.xml',
        'Geometry/EcalSimData/data/ESProdCuts.xml',
        'Geometry/TrackerSimData/data/trackerProdCuts.xml',
        'Geometry/TrackerSimData/data/trackerProdCutsBEAM.xml',
        'Geometry/MuonSimData/data/muonProdCuts.xml',
        'Geometry/ForwardSimData/data/ForwardShieldProdCuts.xml',
        'Geometry/CMSCommonData/data/FieldParameters.xml'
     ) ),
    rootNodeName = cms.string('cms:OCMS')
)


process.eegeom = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('EcalMappingRcd')
)


process.es_hardcode = cms.ESSource("HcalHardcodeCalibrations",
    GainWidthsForTrigPrims = cms.bool(False),
    HBRecalibration = cms.bool(False),
    HBmeanenergies = cms.FileInPath('CalibCalorimetry/HcalPlugins/data/meanenergiesHB.txt'),
    HBreCalibCutoff = cms.double(20.0),
    HERecalibration = cms.bool(False),
    HEmeanenergies = cms.FileInPath('CalibCalorimetry/HcalPlugins/data/meanenergiesHE.txt'),
    HEreCalibCutoff = cms.double(20.0),
    HFRecalParameterBlock = cms.PSet(
        HFdepthOneParameterA = cms.vdouble(
            0.004123, 0.00602, 0.008201, 0.010489, 0.013379,
            0.016997, 0.021464, 0.027371, 0.034195, 0.044807,
            0.058939, 0.125497
        ),
        HFdepthOneParameterB = cms.vdouble(
            -4e-06, -2e-06, 0.0, 4e-06, 1.5e-05,
            2.6e-05, 6.3e-05, 8.4e-05, 0.00016, 0.000107,
            0.000425, 0.000209
        ),
        HFdepthTwoParameterA = cms.vdouble(
            0.002861, 0.004168, 0.0064, 0.008388, 0.011601,
            0.014425, 0.018633, 0.023232, 0.028274, 0.035447,
            0.051579, 0.086593
        ),
        HFdepthTwoParameterB = cms.vdouble(
            -2e-06, -0.0, -7e-06, -6e-06, -2e-06,
            1e-06, 1.9e-05, 3.1e-05, 6.7e-05, 1.2e-05,
            0.000157, -3e-06
        )
    ),
    HFRecalibration = cms.bool(False),
    SiPMCharacteristics = cms.VPSet(
        cms.PSet(
            crosstalk = cms.double(0.0),
            nonlin1 = cms.double(1.0),
            nonlin2 = cms.double(0.0),
            nonlin3 = cms.double(0.0),
            pixels = cms.int32(36000)
        ),
        cms.PSet(
            crosstalk = cms.double(0.0),
            nonlin1 = cms.double(1.0),
            nonlin2 = cms.double(0.0),
            nonlin3 = cms.double(0.0),
            pixels = cms.int32(2500)
        ),
        cms.PSet(
            crosstalk = cms.double(0.17),
            nonlin1 = cms.double(1.00985),
            nonlin2 = cms.double(7.84089e-06),
            nonlin3 = cms.double(2.86282e-10),
            pixels = cms.int32(27370)
        ),
        cms.PSet(
            crosstalk = cms.double(0.196),
            nonlin1 = cms.double(1.00546),
            nonlin2 = cms.double(6.40239e-06),
            nonlin3 = cms.double(1.27011e-10),
            pixels = cms.int32(38018)
        ),
        cms.PSet(
            crosstalk = cms.double(0.17),
            nonlin1 = cms.double(1.00985),
            nonlin2 = cms.double(7.84089e-06),
            nonlin3 = cms.double(2.86282e-10),
            pixels = cms.int32(27370)
        ),
        cms.PSet(
            crosstalk = cms.double(0.196),
            nonlin1 = cms.double(1.00546),
            nonlin2 = cms.double(6.40239e-06),
            nonlin3 = cms.double(1.27011e-10),
            pixels = cms.int32(38018)
        ),
        cms.PSet(
            crosstalk = cms.double(0.0),
            nonlin1 = cms.double(1.0),
            nonlin2 = cms.double(0.0),
            nonlin3 = cms.double(0.0),
            pixels = cms.int32(0)
        )
    ),
    hb = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.19),
        gainWidth = cms.vdouble(0.0),
        mcShape = cms.int32(125),
        pedestal = cms.double(3.285),
        pedestalWidth = cms.double(0.809),
        photoelectronsToAnalog = cms.double(0.3305),
        qieOffset = cms.vdouble(-0.49, 1.8, 7.2, 37.9),
        qieSlope = cms.vdouble(0.912, 0.917, 0.922, 0.923),
        qieType = cms.int32(0),
        recoShape = cms.int32(105),
        zsThreshold = cms.int32(8)
    ),
    hbUpgrade = cms.PSet(
        darkCurrent = cms.vdouble(0.01, 0.015),
        doRadiationDamage = cms.bool(True),
        gain = cms.vdouble(0.0006252),
        gainWidth = cms.vdouble(0),
        mcShape = cms.int32(206),
        pedestal = cms.double(17.3),
        pedestalWidth = cms.double(1.5),
        photoelectronsToAnalog = cms.double(40.0),
        qieOffset = cms.vdouble(0.0, 0.0, 0.0, 0.0),
        qieSlope = cms.vdouble(0.05376, 0.05376, 0.05376, 0.05376),
        qieType = cms.int32(2),
        radiationDamage = cms.PSet(
            depVsNeutrons = cms.vdouble(5.69e-11, 7.9e-11),
            depVsTemp = cms.double(0.0631),
            intlumiOffset = cms.double(150),
            intlumiToNeutrons = cms.double(367000000.0),
            temperatureBase = cms.double(20),
            temperatureNew = cms.double(-5)
        ),
        recoShape = cms.int32(206),
        zsThreshold = cms.int32(16)
    ),
    he = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.23),
        gainWidth = cms.vdouble(0),
        mcShape = cms.int32(125),
        pedestal = cms.double(3.163),
        pedestalWidth = cms.double(0.9698),
        photoelectronsToAnalog = cms.double(0.3305),
        qieOffset = cms.vdouble(-0.38, 2.0, 7.6, 39.6),
        qieSlope = cms.vdouble(0.912, 0.916, 0.92, 0.922),
        qieType = cms.int32(0),
        recoShape = cms.int32(105),
        zsThreshold = cms.int32(9)
    ),
    heUpgrade = cms.PSet(
        darkCurrent = cms.vdouble(0.01, 0.015),
        doRadiationDamage = cms.bool(True),
        gain = cms.vdouble(0.0006252),
        gainWidth = cms.vdouble(0),
        mcShape = cms.int32(206),
        pedestal = cms.double(17.3),
        pedestalWidth = cms.double(1.5),
        photoelectronsToAnalog = cms.double(40.0),
        qieOffset = cms.vdouble(0.0, 0.0, 0.0, 0.0),
        qieSlope = cms.vdouble(0.05376, 0.05376, 0.05376, 0.05376),
        qieType = cms.int32(2),
        radiationDamage = cms.PSet(
            depVsNeutrons = cms.vdouble(5.69e-11, 7.9e-11),
            depVsTemp = cms.double(0.0631),
            intlumiOffset = cms.double(75),
            intlumiToNeutrons = cms.double(29200000.0),
            temperatureBase = cms.double(20),
            temperatureNew = cms.double(5)
        ),
        recoShape = cms.int32(206),
        zsThreshold = cms.int32(16)
    ),
    hf = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.14, 0.135),
        gainWidth = cms.vdouble(0.0, 0.0),
        mcShape = cms.int32(301),
        pedestal = cms.double(9.354),
        pedestalWidth = cms.double(2.516),
        photoelectronsToAnalog = cms.double(0.0),
        qieOffset = cms.vdouble(-0.87, 1.4, 7.8, -29.6),
        qieSlope = cms.vdouble(0.359, 0.358, 0.36, 0.367),
        qieType = cms.int32(0),
        recoShape = cms.int32(301),
        zsThreshold = cms.int32(-9999)
    ),
    hfUpgrade = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.14, 0.135),
        gainWidth = cms.vdouble(0.0, 0.0),
        mcShape = cms.int32(301),
        pedestal = cms.double(13.33),
        pedestalWidth = cms.double(3.33),
        photoelectronsToAnalog = cms.double(0.0),
        qieOffset = cms.vdouble(0.0697, -0.7405, 12.38, -671.9),
        qieSlope = cms.vdouble(0.297, 0.298, 0.298, 0.313),
        qieType = cms.int32(1),
        recoShape = cms.int32(301),
        zsThreshold = cms.int32(-9999)
    ),
    ho = cms.PSet(
        darkCurrent = cms.vdouble(0.0),
        doRadiationDamage = cms.bool(False),
        gain = cms.vdouble(0.006, 0.0087),
        gainWidth = cms.vdouble(0.0, 0.0),
        mcShape = cms.int32(201),
        pedestal = cms.double(12.06),
        pedestalWidth = cms.double(0.6285),
        photoelectronsToAnalog = cms.double(4.0),
        qieOffset = cms.vdouble(-0.44, 1.4, 7.1, 38.5),
        qieSlope = cms.vdouble(0.907, 0.915, 0.92, 0.921),
        qieType = cms.int32(0),
        recoShape = cms.int32(201),
        zsThreshold = cms.int32(24)
    ),
    iLumi = cms.double(-1.0),
    killHE = cms.bool(False),
    testHEPlan1 = cms.bool(False),
    testHFQIE10 = cms.bool(False),
    toGet = cms.untracked.vstring('GainWidths'),
    useHBUpgrade = cms.bool(False),
    useHEUpgrade = cms.bool(False),
    useHFUpgrade = cms.bool(False),
    useHOUpgrade = cms.bool(True),
    useIeta18depth1 = cms.bool(True),
    useLayer0Weight = cms.bool(False)
)


process.prefer("es_hardcode")

process.pfNoPileUpJMETask = cms.Task(process.goodOfflinePrimaryVertices, process.pfNoPileUpJME, process.pfPileUpJME)


process.ak8puppiSequence = cms.Sequence(((process.kt6PFJetsRhos+((((process.genParticlesForJetsNoNu+(process.puppi+process.ak8PUPPIJets+process.ak8GenJetsNoNu+process.ak8puppiGenPtEta+process.ak8puppiPtEta+process.ak8puppiPtEtaUncor))+process.partons+process.ak8puppiGenToParton)+process.ak8puppiJetToRef)+process.ak8puppiJetToUncorJet))+process.ak8puppi))


process.pfNoPileUpJMESequence = cms.Sequence(process.pfNoPileUpJMETask)


process.ak8pfSequence = cms.Sequence(process.kt6PFJetsRhos+((((process.genParticlesForJetsNoNu+(process.ak8PFJets+process.ak8GenJetsNoNu+process.ak8pfGenPtEta+process.ak8pfPtEta+process.ak8pfPtEtaUncor))+process.partons+process.ak8pfGenToParton)+process.ak8pfJetToRef)+process.ak8pfJetToUncorJet)+process.ak8pf)


process.ak4puppiSequence = cms.Sequence(process.kt6PFJetsRhos+((((process.genParticlesForJetsNoNu+(process.puppi+process.ak4PUPPIJets+process.ak4GenJetsNoNu+process.ak4puppiGenPtEta+process.ak4puppiPtEta+process.ak4puppiPtEtaUncor))+process.partons+process.ak4puppiGenToParton)+process.ak4puppiJetToRef)+process.ak4puppiJetToUncorJet)+process.ak4puppi)


process.ak4pfchsSequence = cms.Sequence(process.pfNoPileUpJMESequence+process.kt6PFchsJetsRhos+((((process.genParticlesForJetsNoNu+(process.ak4PFCHSJets+process.ak4GenJetsNoNu+process.ak4pfchsGenPtEta+process.ak4pfchsPtEta+process.ak4pfchsPtEtaUncor))+process.partons+process.ak4pfchsGenToParton)+process.ak4pfchsJetToRef)+process.ak4pfchsJetToUncorJet)+process.ak4pfchs)
process.ak4pfchsAODSequence = cms.Sequence(process.pfNoPileUpJMESequence+process.kt6PFchsJetsRhos+((((process.genParticlesForJetsNoNu+(process.ak4GenJetsNoNu+process.ak4pfchsAODGenPtEta+process.ak4pfchsAODPtEta+process.ak4pfchsAODPtEtaUncor))+process.partons+process.ak4pfchsAODGenToParton)+process.ak4pfchsAODJetToRef)+process.ak4pfchsAODJetToUncorJet)+process.ak4pfchsAOD)

process.ak4pfSequence = cms.Sequence(process.kt6PFJetsRhos+((((process.genParticlesForJetsNoNu+(process.ak4PFJets+process.ak4GenJetsNoNu+process.ak4pfGenPtEta+process.ak4pfPtEta+process.ak4pfPtEtaUncor))+process.partons+process.ak4pfGenToParton)+process.ak4pfJetToRef)+process.ak4pfJetToUncorJet)+process.ak4pf)


process.ak8pfchsSequence = cms.Sequence((process.pfNoPileUpJMESequence+((process.kt6PFchsJetsRhos+((((process.genParticlesForJetsNoNu+(process.ak8PFCHSJets+process.ak8GenJetsNoNu+process.ak8pfchsGenPtEta+process.ak8pfchsPtEta+process.ak8pfchsPtEtaUncor))+process.partons+process.ak8pfchsGenToParton)+process.ak8pfchsJetToRef)+process.ak8pfchsJetToUncorJet))+process.ak8pfchs)))


process.ak4pfPath = cms.Path(process.ak4pfSequence)


process.ak4pfchsPath = cms.Path(process.ak4pfchsSequence)
process.ak4pfchsAODPath = cms.Path(process.ak4pfchsAODSequence)


process.ak4puppiPath = cms.Path(process.ak4puppiSequence)


process.ak8pfPath = cms.Path(process.ak8pfSequence)


process.ak8pfchsPath = cms.Path(process.ak8pfchsSequence)


process.ak8puppiPath = cms.Path(process.ak8puppiSequence)



