import FWCore.ParameterSet.Config as cms

process = cms.Process("JRA")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:InputFile.root')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

process.options = cms.untracked.PSet(
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(True)
)

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


process.ak4pfchsJetToRef = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfchsGenPtEta"),
    srcRec = cms.InputTag("ak4pfchsPtEta")
)


process.ak4pfchsJetToUncorJet = cms.EDProducer("MatchRecToGen",
    srcGen = cms.InputTag("ak4pfchsPtEtaUncor"),
    srcRec = cms.InputTag("ak4pfchsPtEta")
)


process.genParticlesForJetsNoNu = cms.EDProducer("InputGenJetsParticleSelector",
    excludeFromResonancePids = cms.vuint32(12, 13, 14, 16),
    excludeResonances = cms.bool(False),
    ignoreParticleIDs = cms.vuint32(1000022, 1000012, 1000014, 1000016, 2000012,
        2000014, 2000016, 1000039, 5100039, 4000012,
        4000014, 4000016, 9900012, 9900014, 9900016,
        39, 12, 14, 16),
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
    puCenters = cms.vdouble(-5, -4, -3, -2, -1,
        0, 1, 2, 3, 4,
        5),
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
    puCenters = cms.vdouble(-5, -4, -3, -2, -1,
        0, 1, 2, 3, 4,
        5),
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


process.ak4pfchsPtEta = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFCHSJets")
)


process.ak4pfchsPtEtaUncor = cms.EDFilter("EtaPtMinCandViewRefSelector",
    etaMax = cms.double(5.5),
    etaMin = cms.double(-5.5),
    ptMin = cms.double(1.0),
    src = cms.InputTag("ak4PFCHSJets")
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
    categories = cms.untracked.vstring('FwkJob',
        'FwkReport',
        'FwkSummary',
        'Root_NoDictionary'),
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
    destinations = cms.untracked.vstring('warnings',
        'errors',
        'infos',
        'debugs',
        'cout',
        'cerr'),
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
    fileName = cms.string('JRAnoPU.root')
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
    SelectedCalos = cms.vstring('HCAL',
        'ZDC',
        'CASTOR',
        'EcalBarrel',
        'EcalEndcap',
        'EcalPreshower',
        'TOWER')
)


process.CaloTopologyBuilder = cms.ESProducer("CaloTopologyBuilder")


process.CaloTowerHardcodeGeometryEP = cms.ESProducer("CaloTowerHardcodeGeometryEP")


process.CaloTowerTopologyEP = cms.ESProducer("CaloTowerTopologyEP")


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
    MergePosition = cms.untracked.bool(True),
    appendToDataLabel = cms.string('')
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


process.XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring( ('Geometry/CMSCommonData/data/materials.xml',
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
        'Geometry/CMSCommonData/data/FieldParameters.xml' ) ),
    rootNodeName = cms.string('cms:OCMS')
)


process.eegeom = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('EcalMappingRcd')
)


process.pfNoPileUpJMETask = cms.Task(process.goodOfflinePrimaryVertices, process.pfNoPileUpJME, process.pfPileUpJME)


process.ak4pfSequence = cms.Sequence(((process.kt6PFJetsRhos+((((process.genParticlesForJetsNoNu+(process.ak4PFJets+process.ak4GenJetsNoNu+process.ak4pfGenPtEta+process.ak4pfPtEta+process.ak4pfPtEtaUncor))+process.partons+process.ak4pfGenToParton)+process.ak4pfJetToRef)+process.ak4pfJetToUncorJet))+process.ak4pf))


process.pfNoPileUpJMESequence = cms.Sequence(process.pfNoPileUpJMETask)


process.ak4pfchsSequence = cms.Sequence((process.pfNoPileUpJMESequence+((process.kt6PFchsJetsRhos+((((process.genParticlesForJetsNoNu+(process.ak4PFCHSJets+process.ak4GenJetsNoNu+process.ak4pfchsGenPtEta+process.ak4pfchsPtEta+process.ak4pfchsPtEtaUncor))+process.partons+process.ak4pfchsGenToParton)+process.ak4pfchsJetToRef)+process.ak4pfchsJetToUncorJet))+process.ak4pfchs)))


process.ak4pfPath = cms.Path(process.ak4pfSequence)


process.ak4pfchsPath = cms.Path(process.ak4pfchsSequence)



