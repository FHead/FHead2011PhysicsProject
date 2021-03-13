
[31m~*~ USING CENTRALITY TABLE FOR Hydjet Drum5F ~*~[0m

import FWCore.ParameterSet.Config as cms

process = cms.Process("HiForest")

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring('file:HIN-HINPbPbAutumn18DR-00060.root')
)
process.CondDB = cms.PSet(
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    connect = cms.string('')
)

process.DA_vectParameters = cms.PSet(
    TkDAClusParameters = cms.PSet(
        Tmin = cms.double(2.0),
        Tpurge = cms.double(2.0),
        Tstop = cms.double(0.5),
        coolingFactor = cms.double(0.6),
        d0CutOff = cms.double(3.0),
        dzCutOff = cms.double(3.0),
        uniquetrkweight = cms.double(0.8),
        vertexSize = cms.double(0.006),
        zmerge = cms.double(0.01)
    ),
    algorithm = cms.string('DA_vect')
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

process.JetIDParams = cms.PSet(
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    useRecHits = cms.bool(True)
)

process.calibratedEgammaPatSettings = cms.PSet(
    correctionFile = cms.string('EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc'),
    minEtToCalibrate = cms.double(5.0),
    produceCalibratedObjs = cms.bool(True),
    recHitCollectionEB = cms.InputTag("reducedEgamma","reducedEBRecHits"),
    recHitCollectionEE = cms.InputTag("reducedEgamma","reducedEERecHits"),
    semiDeterministic = cms.bool(True)
)

process.calibratedEgammaSettings = cms.PSet(
    correctionFile = cms.string('EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc'),
    minEtToCalibrate = cms.double(5.0),
    produceCalibratedObjs = cms.bool(True),
    recHitCollectionEB = cms.InputTag("reducedEcalRecHitsEB"),
    recHitCollectionEE = cms.InputTag("reducedEcalRecHitsEE"),
    semiDeterministic = cms.bool(True)
)

process.combinedSecondaryVertexCommon = cms.PSet(
    SoftLeptonFlip = cms.bool(False),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)

process.disc = cms.PSet(
    denominator = cms.VInputTag(
        cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDb"), 
        cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDothers")
    ),
    name = cms.string('ccvsLight'),
    numerator = cms.VInputTag(cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"))
)

process.ecalTrkCombinationRegression = cms.PSet(
    ecalTrkRegressionConfig = cms.PSet(
        ebHighEtForestName = cms.string('electron_eb_ECALTRK'),
        ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt'),
        eeHighEtForestName = cms.string('electron_ee_ECALTRK'),
        eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt'),
        forceHighEnergyTrainingIfSaturated = cms.bool(False),
        lowEtHighEtBoundary = cms.double(50.0),
        rangeMaxHighEt = cms.double(3.0),
        rangeMaxLowEt = cms.double(3.0),
        rangeMinHighEt = cms.double(-1.0),
        rangeMinLowEt = cms.double(-1.0)
    ),
    ecalTrkRegressionUncertConfig = cms.PSet(
        ebHighEtForestName = cms.string('electron_eb_ECALTRK_var'),
        ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt_var'),
        eeHighEtForestName = cms.string('electron_ee_ECALTRK_var'),
        eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt_var'),
        forceHighEnergyTrainingIfSaturated = cms.bool(False),
        lowEtHighEtBoundary = cms.double(50.0),
        rangeMaxHighEt = cms.double(0.5),
        rangeMaxLowEt = cms.double(0.5),
        rangeMinHighEt = cms.double(0.0002),
        rangeMinLowEt = cms.double(0.0002)
    ),
    maxEPDiffInSigmaForComb = cms.double(15.0),
    maxEcalEnergyForComb = cms.double(200.0),
    maxRelTrkMomErrForComb = cms.double(10.0),
    minEOverPForComb = cms.double(0.025)
)

process.ghostTrackCommon = cms.PSet(
    charmCut = cms.double(1.5),
    minimumTrackWeight = cms.double(0.5),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig')
)

process.ghostTrackVertexRecoBlock = cms.PSet(
    vertexReco = cms.PSet(
        finder = cms.string('gtvr'),
        fitType = cms.string('RefitGhostTrackWithVertices'),
        maxFitChi2 = cms.double(10.0),
        mergeThreshold = cms.double(3.0),
        primcut = cms.double(2.0),
        seccut = cms.double(4.0)
    )
)

process.j2tParametersCALO = cms.PSet(
    coneSize = cms.double(0.4),
    extrapolations = cms.InputTag("trackExtrapolator"),
    trackQuality = cms.string('goodIterative'),
    tracks = cms.InputTag("generalTracks")
)

process.j2tParametersVX = cms.PSet(
    coneSize = cms.double(0.4),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    useAssigned = cms.bool(False)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.pfDeepBoostedJetPreprocessParams = cms.PSet(
    input_names = cms.vstring(
        'pfcand', 
        'sv'
    ),
    pfcand = cms.PSet(
        input_shape = cms.vuint32(1, 42, 100, 1),
        var_infos = cms.PSet(
            pfcand_VTX_ass = cms.PSet(
                median = cms.double(7.0),
                upper = cms.double(7.0)
            ),
            pfcand_abseta = cms.PSet(
                median = cms.double(0.599505603313),
                upper = cms.double(1.21494185925)
            ),
            pfcand_btagEtaRel = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(3.23048327446)
            ),
            pfcand_btagJetDistVal = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_btagPParRatio = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.997295975685)
            ),
            pfcand_btagPtRatio = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.174372568727)
            ),
            pfcand_btagSip2dSig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.565274050236)
            ),
            pfcand_btagSip2dVal = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00165283482056)
            ),
            pfcand_btagSip3dSig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.03450630188)
            ),
            pfcand_btagSip3dVal = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00417172765359)
            ),
            pfcand_charge = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.0)
            ),
            pfcand_deltaR = cms.PSet(
                median = cms.double(0.22575956583),
                upper = cms.double(0.488191870451)
            ),
            pfcand_detadeta = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(5.08303287461e-07)
            ),
            pfcand_dlambdadz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_dphidphi = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(7.63271316373e-07)
            ),
            pfcand_dphidxy = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_dptdpt = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(6.11870564171e-06)
            ),
            pfcand_drminsv = cms.PSet(
                median = cms.double(0.177426457405),
                upper = cms.double(0.555181086063)
            ),
            pfcand_drsubjet1 = cms.PSet(
                median = cms.double(0.231124095619),
                upper = cms.double(0.549522156715)
            ),
            pfcand_drsubjet2 = cms.PSet(
                median = cms.double(0.263272643089),
                upper = cms.double(0.605471189022)
            ),
            pfcand_dxy = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00254638679326)
            ),
            pfcand_dxydxy = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(2.14965821215e-05)
            ),
            pfcand_dxydz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.31130221348e-07)
            ),
            pfcand_dxysig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.496566288471)
            ),
            pfcand_dz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.00448730448261)
            ),
            pfcand_dzdz = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(3.40332044289e-05)
            ),
            pfcand_dzsig = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.596591930389)
            ),
            pfcand_erel_log = cms.PSet(
                median = cms.double(-5.38983869553),
                upper = cms.double(-3.53490426064)
            ),
            pfcand_etarel = cms.PSet(
                median = cms.double(-0.0054658302106),
                upper = cms.double(0.174858552814)
            ),
            pfcand_hcalFrac = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_isChargedHad = cms.PSet(
                median = cms.double(1.0),
                upper = cms.double(1.0)
            ),
            pfcand_isEl = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_isGamma = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(1.0)
            ),
            pfcand_isMu = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_isNeutralHad = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(0.0)
            ),
            pfcand_lostInnerHits = cms.PSet(
                median = cms.double(-1.0),
                upper = cms.double(-1.0)
            ),
            pfcand_normchi2 = cms.PSet(
                median = cms.double(999.0),
                upper = cms.double(999.0)
            ),
            pfcand_phirel = cms.PSet(
                median = cms.double(-5.10289683007e-05),
                upper = cms.double(0.215602903366)
            ),
            pfcand_pt_log = cms.PSet(
                median = cms.double(1.09469842911),
                upper = cms.double(3.02194809914)
            ),
            pfcand_ptrel_log = cms.PSet(
                median = cms.double(-5.38205528259),
                upper = cms.double(-3.52304198265)
            ),
            pfcand_puppiw = cms.PSet(
                median = cms.double(1.0),
                upper = cms.double(1.0)
            ),
            pfcand_quality = cms.PSet(
                median = cms.double(0.0),
                upper = cms.double(5.0)
            )
        ),
        var_length = cms.uint32(100),
        var_names = cms.vstring(
            'pfcand_pt_log', 
            'pfcand_ptrel_log', 
            'pfcand_erel_log', 
            'pfcand_phirel', 
            'pfcand_etarel', 
            'pfcand_deltaR', 
            'pfcand_abseta', 
            'pfcand_puppiw', 
            'pfcand_drminsv', 
            'pfcand_drsubjet1', 
            'pfcand_drsubjet2', 
            'pfcand_charge', 
            'pfcand_isMu', 
            'pfcand_isEl', 
            'pfcand_isChargedHad', 
            'pfcand_isGamma', 
            'pfcand_isNeutralHad', 
            'pfcand_hcalFrac', 
            'pfcand_VTX_ass', 
            'pfcand_lostInnerHits', 
            'pfcand_normchi2', 
            'pfcand_quality', 
            'pfcand_dz', 
            'pfcand_dzsig', 
            'pfcand_dxy', 
            'pfcand_dxysig', 
            'pfcand_dptdpt', 
            'pfcand_detadeta', 
            'pfcand_dphidphi', 
            'pfcand_dxydxy', 
            'pfcand_dzdz', 
            'pfcand_dxydz', 
            'pfcand_dphidxy', 
            'pfcand_dlambdadz', 
            'pfcand_btagEtaRel', 
            'pfcand_btagPtRatio', 
            'pfcand_btagPParRatio', 
            'pfcand_btagSip2dVal', 
            'pfcand_btagSip2dSig', 
            'pfcand_btagSip3dVal', 
            'pfcand_btagSip3dSig', 
            'pfcand_btagJetDistVal'
        )
    ),
    sv = cms.PSet(
        input_shape = cms.vuint32(1, 15, 7, 1),
        var_infos = cms.PSet(
            sv_abseta = cms.PSet(
                median = cms.double(0.579698801041),
                upper = cms.double(1.2257443285)
            ),
            sv_costhetasvpv = cms.PSet(
                median = cms.double(0.999744534492),
                upper = cms.double(0.999992311001)
            ),
            sv_d3d = cms.PSet(
                median = cms.double(0.496477723122),
                upper = cms.double(4.83165483475)
            ),
            sv_d3dsig = cms.PSet(
                median = cms.double(6.50515079498),
                upper = cms.double(36.9069334412)
            ),
            sv_deltaR = cms.PSet(
                median = cms.double(0.105607174337),
                upper = cms.double(0.323846782446)
            ),
            sv_dxy = cms.PSet(
                median = cms.double(0.369336694479),
                upper = cms.double(3.97735537529)
            ),
            sv_dxysig = cms.PSet(
                median = cms.double(6.49603271484),
                upper = cms.double(36.8943783569)
            ),
            sv_erel_log = cms.PSet(
                median = cms.double(-2.77275466919),
                upper = cms.double(-1.7486346817)
            ),
            sv_etarel = cms.PSet(
                median = cms.double(-0.00318800867535),
                upper = cms.double(0.0951088288426)
            ),
            sv_mass = cms.PSet(
                median = cms.double(1.36728298664),
                upper = cms.double(4.75960615158)
            ),
            sv_normchi2 = cms.PSet(
                median = cms.double(0.796081960201),
                upper = cms.double(2.15187430382)
            ),
            sv_ntracks = cms.PSet(
                median = cms.double(3.0),
                upper = cms.double(5.0)
            ),
            sv_phirel = cms.PSet(
                median = cms.double(0.000510219600983),
                upper = cms.double(0.110185634494)
            ),
            sv_pt_log = cms.PSet(
                median = cms.double(3.77797603607),
                upper = cms.double(4.90166530609)
            ),
            sv_ptrel_log = cms.PSet(
                median = cms.double(-2.7622461319),
                upper = cms.double(-1.73727185726)
            )
        ),
        var_length = cms.uint32(7),
        var_names = cms.vstring(
            'sv_pt_log', 
            'sv_ptrel_log', 
            'sv_erel_log', 
            'sv_phirel', 
            'sv_etarel', 
            'sv_deltaR', 
            'sv_abseta', 
            'sv_mass', 
            'sv_ntracks', 
            'sv_normchi2', 
            'sv_dxy', 
            'sv_dxysig', 
            'sv_d3d', 
            'sv_d3dsig', 
            'sv_costhetasvpv'
        )
    )
)

process.softPFElectronCommon = cms.PSet(
    gbrForestLabel = cms.string('btag_SoftPFElectron_BDT'),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFElectron_BDT.weights.xml.gz')
)

process.softPFMuonCommon = cms.PSet(
    gbrForestLabel = cms.string('btag_SoftPFMuon_BDT'),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFMuon_BDT.weights.xml.gz')
)

process.trackPseudoSelectionBlock = cms.PSet(
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    )
)

process.trackSelectionBlock = cms.PSet(
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    )
)

process.variableJTAPars = cms.PSet(
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5)
)

process.vertexCutsBlock = cms.PSet(
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    )
)

process.vertexRecoBlock = cms.PSet(
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    )
)

process.vertexSelectionBlock = cms.PSet(
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)

process.vertexTrackSelectionBlock = cms.PSet(
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    )
)

process.c_vs_b_vars_vpset = cms.VPSet(
    cms.PSet(
        default = cms.double(-1),
        name = cms.string('vertexLeptonCategory'),
        taggingVarName = cms.string('vertexLeptonCategory')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(0),
        name = cms.string('trackSip2dSig_0'),
        taggingVarName = cms.string('trackSip2dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(1),
        name = cms.string('trackSip2dSig_1'),
        taggingVarName = cms.string('trackSip2dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(0),
        name = cms.string('trackSip3dSig_0'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(1),
        name = cms.string('trackSip3dSig_1'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('trackPtRel_0'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('trackPtRel_1'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('trackPPar_0'),
        taggingVarName = cms.string('trackPPar')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('trackPPar_1'),
        taggingVarName = cms.string('trackPPar')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('trackEtaRel_0'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('trackEtaRel_1'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackDeltaR_0'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackDeltaR_1'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackPtRatio_0'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackPtRatio_1'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(1.1),
        idx = cms.int32(0),
        name = cms.string('trackPParRatio_0'),
        taggingVarName = cms.string('trackPParRatio')
    ), 
    cms.PSet(
        default = cms.double(1.1),
        idx = cms.int32(1),
        name = cms.string('trackPParRatio_1'),
        taggingVarName = cms.string('trackPParRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackJetDist_0'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackJetDist_1'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackDecayLenVal_0'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackDecayLenVal_1'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(0),
        name = cms.string('jetNSecondaryVertices'),
        taggingVarName = cms.string('jetNSecondaryVertices')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('jetNTracks'),
        taggingVarName = cms.string('jetNTracks')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('trackSumJetEtRatio'),
        taggingVarName = cms.string('trackSumJetEtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('trackSumJetDeltaR'),
        taggingVarName = cms.string('trackSumJetDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('vertexMass_0'),
        taggingVarName = cms.string('vertexMass')
    ), 
    cms.PSet(
        default = cms.double(-10),
        idx = cms.int32(0),
        name = cms.string('vertexEnergyRatio_0'),
        taggingVarName = cms.string('vertexEnergyRatio')
    ), 
    cms.PSet(
        default = cms.double(-999),
        idx = cms.int32(0),
        name = cms.string('trackSip2dSigAboveCharm_0'),
        taggingVarName = cms.string('trackSip2dSigAboveCharm')
    ), 
    cms.PSet(
        default = cms.double(-999),
        idx = cms.int32(0),
        name = cms.string('trackSip3dSigAboveCharm_0'),
        taggingVarName = cms.string('trackSip3dSigAboveCharm')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('flightDistance2dSig_0'),
        taggingVarName = cms.string('flightDistance2dSig')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('flightDistance3dSig_0'),
        taggingVarName = cms.string('flightDistance3dSig')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('vertexJetDeltaR_0'),
        taggingVarName = cms.string('vertexJetDeltaR')
    ), 
    cms.PSet(
        default = cms.double(0),
        idx = cms.int32(0),
        name = cms.string('vertexNTracks_0'),
        taggingVarName = cms.string('vertexNTracks')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('massVertexEnergyFraction_0'),
        taggingVarName = cms.string('massVertexEnergyFraction')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('vertexBoostOverSqrtJetPt_0'),
        taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonPtRel_0'),
        taggingVarName = cms.string('leptonPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonPtRel_1'),
        taggingVarName = cms.string('leptonPtRel')
    ), 
    cms.PSet(
        default = cms.double(-10000),
        idx = cms.int32(0),
        name = cms.string('leptonSip3d_0'),
        taggingVarName = cms.string('leptonSip3d')
    ), 
    cms.PSet(
        default = cms.double(-10000),
        idx = cms.int32(1),
        name = cms.string('leptonSip3d_1'),
        taggingVarName = cms.string('leptonSip3d')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonDeltaR_0'),
        taggingVarName = cms.string('leptonDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonDeltaR_1'),
        taggingVarName = cms.string('leptonDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonRatioRel_0'),
        taggingVarName = cms.string('leptonRatioRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonRatioRel_1'),
        taggingVarName = cms.string('leptonRatioRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonEtaRel_0'),
        taggingVarName = cms.string('leptonEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonEtaRel_1'),
        taggingVarName = cms.string('leptonEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonRatio_0'),
        taggingVarName = cms.string('leptonRatio')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonRatio_1'),
        taggingVarName = cms.string('leptonRatio')
    )
)

process.c_vs_l_vars_vpset = cms.VPSet(
    cms.PSet(
        default = cms.double(-1),
        name = cms.string('vertexLeptonCategory'),
        taggingVarName = cms.string('vertexLeptonCategory')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(0),
        name = cms.string('trackSip2dSig_0'),
        taggingVarName = cms.string('trackSip2dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(1),
        name = cms.string('trackSip2dSig_1'),
        taggingVarName = cms.string('trackSip2dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(0),
        name = cms.string('trackSip3dSig_0'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(1),
        name = cms.string('trackSip3dSig_1'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('trackPtRel_0'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('trackPtRel_1'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('trackPPar_0'),
        taggingVarName = cms.string('trackPPar')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('trackPPar_1'),
        taggingVarName = cms.string('trackPPar')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('trackEtaRel_0'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('trackEtaRel_1'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackDeltaR_0'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackDeltaR_1'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackPtRatio_0'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackPtRatio_1'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(1.1),
        idx = cms.int32(0),
        name = cms.string('trackPParRatio_0'),
        taggingVarName = cms.string('trackPParRatio')
    ), 
    cms.PSet(
        default = cms.double(1.1),
        idx = cms.int32(1),
        name = cms.string('trackPParRatio_1'),
        taggingVarName = cms.string('trackPParRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackJetDist_0'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackJetDist_1'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('trackDecayLenVal_0'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('trackDecayLenVal_1'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(0),
        name = cms.string('jetNSecondaryVertices'),
        taggingVarName = cms.string('jetNSecondaryVertices')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('jetNTracks'),
        taggingVarName = cms.string('jetNTracks')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('trackSumJetEtRatio'),
        taggingVarName = cms.string('trackSumJetEtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('trackSumJetDeltaR'),
        taggingVarName = cms.string('trackSumJetDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('vertexMass_0'),
        taggingVarName = cms.string('vertexMass')
    ), 
    cms.PSet(
        default = cms.double(-10),
        idx = cms.int32(0),
        name = cms.string('vertexEnergyRatio_0'),
        taggingVarName = cms.string('vertexEnergyRatio')
    ), 
    cms.PSet(
        default = cms.double(-999),
        idx = cms.int32(0),
        name = cms.string('trackSip2dSigAboveCharm_0'),
        taggingVarName = cms.string('trackSip2dSigAboveCharm')
    ), 
    cms.PSet(
        default = cms.double(-999),
        idx = cms.int32(0),
        name = cms.string('trackSip3dSigAboveCharm_0'),
        taggingVarName = cms.string('trackSip3dSigAboveCharm')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('flightDistance2dSig_0'),
        taggingVarName = cms.string('flightDistance2dSig')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('flightDistance3dSig_0'),
        taggingVarName = cms.string('flightDistance3dSig')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('vertexJetDeltaR_0'),
        taggingVarName = cms.string('vertexJetDeltaR')
    ), 
    cms.PSet(
        default = cms.double(0),
        idx = cms.int32(0),
        name = cms.string('vertexNTracks_0'),
        taggingVarName = cms.string('vertexNTracks')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('massVertexEnergyFraction_0'),
        taggingVarName = cms.string('massVertexEnergyFraction')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('vertexBoostOverSqrtJetPt_0'),
        taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonPtRel_0'),
        taggingVarName = cms.string('leptonPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonPtRel_1'),
        taggingVarName = cms.string('leptonPtRel')
    ), 
    cms.PSet(
        default = cms.double(-10000),
        idx = cms.int32(0),
        name = cms.string('leptonSip3d_0'),
        taggingVarName = cms.string('leptonSip3d')
    ), 
    cms.PSet(
        default = cms.double(-10000),
        idx = cms.int32(1),
        name = cms.string('leptonSip3d_1'),
        taggingVarName = cms.string('leptonSip3d')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonDeltaR_0'),
        taggingVarName = cms.string('leptonDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonDeltaR_1'),
        taggingVarName = cms.string('leptonDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonRatioRel_0'),
        taggingVarName = cms.string('leptonRatioRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonRatioRel_1'),
        taggingVarName = cms.string('leptonRatioRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonEtaRel_0'),
        taggingVarName = cms.string('leptonEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonEtaRel_1'),
        taggingVarName = cms.string('leptonEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('leptonRatio_0'),
        taggingVarName = cms.string('leptonRatio')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('leptonRatio_1'),
        taggingVarName = cms.string('leptonRatio')
    )
)

process.csvscikit_vpset = cms.VPSet(
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(0),
        name = cms.string('TagVarCSV_trackSip3dSig_0'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(1),
        name = cms.string('TagVarCSV_trackSip3dSig_1'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(2),
        name = cms.string('TagVarCSV_trackSip3dSig_2'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-100),
        idx = cms.int32(3),
        name = cms.string('TagVarCSV_trackSip3dSig_3'),
        taggingVarName = cms.string('trackSip3dSig')
    ), 
    cms.PSet(
        default = cms.double(-999),
        name = cms.string('TagVarCSV_trackSip3dSigAboveCharm'),
        taggingVarName = cms.string('trackSip3dSigAboveCharm')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('TagVarCSV_trackPtRel_0'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('TagVarCSV_trackPtRel_1'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(2),
        name = cms.string('TagVarCSV_trackPtRel_2'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(3),
        name = cms.string('TagVarCSV_trackPtRel_3'),
        taggingVarName = cms.string('trackPtRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(0),
        name = cms.string('TagVarCSV_trackEtaRel_0'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(1),
        name = cms.string('TagVarCSV_trackEtaRel_1'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(2),
        name = cms.string('TagVarCSV_trackEtaRel_2'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-1),
        idx = cms.int32(3),
        name = cms.string('TagVarCSV_trackEtaRel_3'),
        taggingVarName = cms.string('trackEtaRel')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('TagVarCSV_trackDeltaR_0'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('TagVarCSV_trackDeltaR_1'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(2),
        name = cms.string('TagVarCSV_trackDeltaR_2'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(3),
        name = cms.string('TagVarCSV_trackDeltaR_3'),
        taggingVarName = cms.string('trackDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('TagVarCSV_trackPtRatio_0'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('TagVarCSV_trackPtRatio_1'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(2),
        name = cms.string('TagVarCSV_trackPtRatio_2'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(3),
        name = cms.string('TagVarCSV_trackPtRatio_3'),
        taggingVarName = cms.string('trackPtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('TagVarCSV_trackJetDist_0'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('TagVarCSV_trackJetDist_1'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(2),
        name = cms.string('TagVarCSV_trackJetDist_2'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(3),
        name = cms.string('TagVarCSV_trackJetDist_3'),
        taggingVarName = cms.string('trackJetDist')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(0),
        name = cms.string('TagVarCSV_trackDecayLenVal_0'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(1),
        name = cms.string('TagVarCSV_trackDecayLenVal_1'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(2),
        name = cms.string('TagVarCSV_trackDecayLenVal_2'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        idx = cms.int32(3),
        name = cms.string('TagVarCSV_trackDecayLenVal_3'),
        taggingVarName = cms.string('trackDecayLenVal')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('TagVarCSV_trackSumJetEtRatio'),
        taggingVarName = cms.string('trackSumJetEtRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('TagVarCSV_trackSumJetDeltaR'),
        taggingVarName = cms.string('trackSumJetDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('TagVarCSV_vertexMass'),
        taggingVarName = cms.string('vertexMass')
    ), 
    cms.PSet(
        default = cms.double(0),
        name = cms.string('TagVarCSV_vertexNTracks'),
        taggingVarName = cms.string('vertexNTracks')
    ), 
    cms.PSet(
        default = cms.double(-10),
        name = cms.string('TagVarCSV_vertexEnergyRatio'),
        taggingVarName = cms.string('vertexEnergyRatio')
    ), 
    cms.PSet(
        default = cms.double(-0.1),
        name = cms.string('TagVarCSV_vertexJetDeltaR'),
        taggingVarName = cms.string('vertexJetDeltaR')
    ), 
    cms.PSet(
        default = cms.double(-1),
        name = cms.string('TagVarCSV_flightDistance2dSig'),
        taggingVarName = cms.string('flightDistance2dSig')
    ), 
    cms.PSet(
        default = cms.double(0),
        name = cms.string('TagVarCSV_jetNSecondaryVertices'),
        taggingVarName = cms.string('jetNSecondaryVertices')
    ), 
    cms.PSet(
        default = cms.double(0),
        name = cms.string('TagVarCSV_vertexCategory'),
        taggingVarName = cms.string('vertexCategory')
    )
)

process.HBHENoiseFilterResultProducer = cms.EDProducer("HBHENoiseFilterResultProducer",
    IgnoreTS4TS5ifJetInLowBVRegion = cms.bool(True),
    defaultDecision = cms.string('HBHENoiseFilterResultRun2Loose'),
    minHPDHits = cms.int32(17),
    minHPDNoOtherHits = cms.int32(10),
    minIsolatedNoiseSumE = cms.double(50.0),
    minIsolatedNoiseSumEt = cms.double(25.0),
    minNumIsolatedNoiseChannels = cms.int32(10),
    minZeros = cms.int32(9999),
    noiselabel = cms.InputTag("hcalnoise"),
    useBunchSpacingProducer = cms.bool(True)
)


process.Njettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.8),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak8PFJetsCHS")
)


process.PFTowers = cms.EDProducer("ParticleTowerProducer",
    src = cms.InputTag("particleFlow"),
    useHF = cms.bool(False)
)


process.ak10CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(1.0),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak10PFJets = cms.EDProducer("FastjetJetProducer",
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
    jetPtMin = cms.double(1.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(1.0),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak1CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.1),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak1GenJets = cms.EDProducer("FastjetJetProducer",
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
    rParam = cms.double(0.1),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak1GenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.1),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak1GenJets")
)


process.ak1HiCleanedGenJets = cms.EDProducer("HiGenJetCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("ak1HiGenJets")
)


process.ak1HiGenJets = cms.EDProducer("SubEventGenJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(True),
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
    rParam = cms.double(0.1),
    radiusPU = cms.double(0.5),
    signalOnly = cms.bool(False),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak1HiGenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.1),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak1HiSignalGenJets")
)


process.ak1HiSignalGenJets = cms.EDProducer("HiSignalGenJetProducer",
    src = cms.InputTag("ak1HiGenJets")
)


process.ak1PFJets = cms.EDProducer("FastjetJetProducer",
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
    jetPtMin = cms.double(1.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.1),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak2CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.2),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak2GenJets = cms.EDProducer("FastjetJetProducer",
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
    rParam = cms.double(0.2),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak2GenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.2),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak2GenJets")
)


process.ak2HiCleanedGenJets = cms.EDProducer("HiGenJetCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("ak2HiGenJets")
)


process.ak2HiGenJets = cms.EDProducer("SubEventGenJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(True),
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
    rParam = cms.double(0.2),
    radiusPU = cms.double(0.5),
    signalOnly = cms.bool(False),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak2HiGenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.2),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak2HiSignalGenJets")
)


process.ak2HiSignalGenJets = cms.EDProducer("HiSignalGenJetProducer",
    src = cms.InputTag("ak2HiGenJets")
)


process.ak2PFJets = cms.EDProducer("FastjetJetProducer",
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
    jetPtMin = cms.double(1.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.2),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak3CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.3),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak3GenJets = cms.EDProducer("FastjetJetProducer",
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
    rParam = cms.double(0.3),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak3GenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.3),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak3GenJets")
)


process.ak3HiCleanedGenJets = cms.EDProducer("HiGenJetCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("ak3HiGenJets")
)


process.ak3HiGenJets = cms.EDProducer("SubEventGenJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(True),
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
    rParam = cms.double(0.3),
    radiusPU = cms.double(0.5),
    signalOnly = cms.bool(False),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak3HiGenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.3),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak3HiSignalGenJets")
)


process.ak3HiSignalGenJets = cms.EDProducer("HiSignalGenJetProducer",
    src = cms.InputTag("ak3HiGenJets")
)


process.ak3PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"), cms.InputTag("ak3PFSecondaryVertexTagInfos"))
)


process.ak3PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"), cms.InputTag("ak3PFSecondaryVertexTagInfos"))
)


process.ak3PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("ak3PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.ak3PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"))
)


process.ak3PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("ak3CaloJets"),
    useRecHits = cms.bool(True)
)


process.ak3PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"))
)


process.ak3PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("ak3PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.ak3PFJets = cms.EDProducer("FastjetJetProducer",
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
    jetPtMin = cms.double(1.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.3),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak3PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"), cms.InputTag("ak3PFSecondaryVertexNegativeTagInfos"))
)


process.ak3PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"), cms.InputTag("ak3PFSecondaryVertexNegativeTagInfos"))
)


process.ak3PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSecondaryVertexNegativeTagInfos"))
)


process.ak3PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSecondaryVertexNegativeTagInfos"))
)


process.ak3PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSoftPFMuonsTagInfos"))
)


process.ak3PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.3),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak3PFJets")
)


process.ak3PFPatJetFlavourAssociation = cms.EDProducer("JetFlavourClustering",
    bHadrons = cms.InputTag("ak3PFPatJetPartons","bHadrons"),
    cHadrons = cms.InputTag("ak3PFPatJetPartons","cHadrons"),
    ghostRescaling = cms.double(1e-18),
    hadronFlavourHasPriority = cms.bool(False),
    jetAlgorithm = cms.string('AntiKt'),
    jets = cms.InputTag("ak3PFJets"),
    leptons = cms.InputTag("ak3PFPatJetPartons","leptons"),
    partons = cms.InputTag("ak3PFPatJetPartons","physicsPartons"),
    rParam = cms.double(0.3)
)


process.ak3PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.ak3PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"), cms.InputTag("ak3PFSecondaryVertexTagInfos"))
)


process.ak3PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"), cms.InputTag("ak3PFSecondaryVertexTagInfos"))
)


process.ak3PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSoftPFMuonsTagInfos"))
)


process.ak3PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("ak3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.ak3PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("ak3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.ak3PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSecondaryVertexTagInfos"))
)


process.ak3PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSecondaryVertexTagInfos"))
)


process.ak3PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSoftPFMuonsTagInfos"))
)


process.ak3PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSoftPFMuonsTagInfos"))
)


process.ak3PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFSoftPFMuonsTagInfos"))
)


process.ak3PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("ak3PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.ak3PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"))
)


process.ak3PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"))
)


process.ak3PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK3PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("ak3PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.ak3PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak3PFJets")
)


process.ak3PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak3HiSignalGenJets")
)


process.ak3PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak3PFJets")
)


process.ak3PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("ak3PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("ak3PFPatJetFlavourAssociation"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("ak3PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("ak3PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("ak3PFCombinedSecondaryVertexBJetTags"), cms.InputTag("ak3PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("ak3PFJetBProbabilityBJetTags"), 
        cms.InputTag("ak3PFJetProbabilityBJetTags"), cms.InputTag("ak3PFTrackCountingHighEffBJetTags"), cms.InputTag("ak3PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("ak3PFmatch"),
    genPartonMatch = cms.InputTag("ak3PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak3PFcorr")),
    jetIDMap = cms.InputTag("ak3PFJetID"),
    jetSource = cms.InputTag("ak3PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("ak3PFImpactParameterTagInfos"), cms.InputTag("ak3PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("ak3PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(False),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "ak3PFNjettiness:tau1", "ak3PFNjettiness:tau2", "ak3PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.ak4CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak4GenJets = cms.EDProducer("FastjetJetProducer",
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
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak4GenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.4),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak4GenJets")
)


process.ak4HiCleanedGenJets = cms.EDProducer("HiGenJetCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("ak4HiGenJets")
)


process.ak4HiGenJets = cms.EDProducer("SubEventGenJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(True),
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
    signalOnly = cms.bool(False),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak4HiGenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.4),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak4HiSignalGenJets")
)


process.ak4HiSignalGenJets = cms.EDProducer("HiSignalGenJetProducer",
    src = cms.InputTag("ak4HiGenJets")
)


process.ak4PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"), cms.InputTag("ak4PFSecondaryVertexTagInfos"))
)


process.ak4PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"), cms.InputTag("ak4PFSecondaryVertexTagInfos"))
)


process.ak4PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("ak4PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.ak4PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"))
)


process.ak4PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("ak4CaloJets"),
    useRecHits = cms.bool(True)
)


process.ak4PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"))
)


process.ak4PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("ak4PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
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
    jetPtMin = cms.double(1.0),
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


process.ak4PFJetsForFlow = cms.EDProducer("FastjetJetProducer",
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
    jetPtMin = cms.double(15.0),
    jetType = cms.string('PFJet'),
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
    src = cms.InputTag("pfcandCleanerPt4Eta2","particleFlowCleaned"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak4PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"), cms.InputTag("ak4PFSecondaryVertexNegativeTagInfos"))
)


process.ak4PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"), cms.InputTag("ak4PFSecondaryVertexNegativeTagInfos"))
)


process.ak4PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSecondaryVertexNegativeTagInfos"))
)


process.ak4PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSecondaryVertexNegativeTagInfos"))
)


process.ak4PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSoftPFMuonsTagInfos"))
)


process.ak4PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.4),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak4PFJets")
)


process.ak4PFPatJetFlavourAssociation = cms.EDProducer("JetFlavourClustering",
    bHadrons = cms.InputTag("ak4PFPatJetPartons","bHadrons"),
    cHadrons = cms.InputTag("ak4PFPatJetPartons","cHadrons"),
    ghostRescaling = cms.double(1e-18),
    hadronFlavourHasPriority = cms.bool(False),
    jetAlgorithm = cms.string('AntiKt'),
    jets = cms.InputTag("ak4PFJets"),
    leptons = cms.InputTag("ak4PFPatJetPartons","leptons"),
    partons = cms.InputTag("ak4PFPatJetPartons","physicsPartons"),
    rParam = cms.double(0.4)
)


process.ak4PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.ak4PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"), cms.InputTag("ak4PFSecondaryVertexTagInfos"))
)


process.ak4PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"), cms.InputTag("ak4PFSecondaryVertexTagInfos"))
)


process.ak4PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSoftPFMuonsTagInfos"))
)


process.ak4PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("ak4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.ak4PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("ak4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.ak4PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSecondaryVertexTagInfos"))
)


process.ak4PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSecondaryVertexTagInfos"))
)


process.ak4PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSoftPFMuonsTagInfos"))
)


process.ak4PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSoftPFMuonsTagInfos"))
)


process.ak4PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFSoftPFMuonsTagInfos"))
)


process.ak4PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("ak4PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.ak4PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"))
)


process.ak4PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"))
)


process.ak4PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK4PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("ak4PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.ak4PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak4PFJets")
)


process.ak4PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak4HiSignalGenJets")
)


process.ak4PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak4PFJets")
)


process.ak4PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("ak4PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("ak4PFPatJetFlavourAssociation"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("ak4PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("ak4PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("ak4PFCombinedSecondaryVertexBJetTags"), cms.InputTag("ak4PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("ak4PFJetBProbabilityBJetTags"), 
        cms.InputTag("ak4PFJetProbabilityBJetTags"), cms.InputTag("ak4PFTrackCountingHighEffBJetTags"), cms.InputTag("ak4PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("ak4PFmatch"),
    genPartonMatch = cms.InputTag("ak4PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak4PFcorr")),
    jetIDMap = cms.InputTag("ak4PFJetID"),
    jetSource = cms.InputTag("ak4PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("ak4PFImpactParameterTagInfos"), cms.InputTag("ak4PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("ak4PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(False),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "ak4PFNjettiness:tau1", "ak4PFNjettiness:tau2", "ak4PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.ak5CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.5),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak5GenJets = cms.EDProducer("FastjetJetProducer",
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
    rParam = cms.double(0.5),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak5GenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.5),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak5GenJets")
)


process.ak5HiCleanedGenJets = cms.EDProducer("HiGenJetCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("ak5HiGenJets")
)


process.ak5HiGenJets = cms.EDProducer("SubEventGenJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(True),
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
    rParam = cms.double(0.5),
    radiusPU = cms.double(0.5),
    signalOnly = cms.bool(False),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak5HiGenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.5),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak5HiSignalGenJets")
)


process.ak5HiSignalGenJets = cms.EDProducer("HiSignalGenJetProducer",
    src = cms.InputTag("ak5HiGenJets")
)


process.ak5JetExtender = cms.EDProducer("JetExtender",
    coneSize = cms.double(0.5),
    jet2TracksAtCALO = cms.InputTag("ak5JetTracksAssociatorAtCaloFace"),
    jet2TracksAtVX = cms.InputTag("ak5JetTracksAssociatorAtVertex"),
    jets = cms.InputTag("ak5CaloJets")
)


process.ak5JetTracksAssociatorAtCaloFace = cms.EDProducer("JetTracksAssociatorAtCaloFace",
    coneSize = cms.double(0.5),
    extrapolations = cms.InputTag("trackExtrapolator"),
    jets = cms.InputTag("ak5CaloJets"),
    trackQuality = cms.string('goodIterative'),
    tracks = cms.InputTag("generalTracks")
)


process.ak5JetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("ak5CaloJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    useAssigned = cms.bool(False)
)


process.ak5JetTracksAssociatorAtVertexPF = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("ak5PFJetsCHS"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    useAssigned = cms.bool(False)
)


process.ak5JetTracksAssociatorExplicit = cms.EDProducer("JetTracksAssociatorExplicit",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("ak5PFJetsCHS"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    useAssigned = cms.bool(False)
)


process.ak5PFJets = cms.EDProducer("FastjetJetProducer",
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
    jetPtMin = cms.double(1.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.5),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak6CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.6),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak6GenJets = cms.EDProducer("FastjetJetProducer",
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
    rParam = cms.double(0.6),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak6GenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.6),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak6GenJets")
)


process.ak6HiCleanedGenJets = cms.EDProducer("HiGenJetCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("ak6HiGenJets")
)


process.ak6HiGenJets = cms.EDProducer("SubEventGenJetProducer",
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    doAreaFastjet = cms.bool(True),
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
    rParam = cms.double(0.6),
    radiusPU = cms.double(0.5),
    signalOnly = cms.bool(False),
    src = cms.InputTag("genParticlesForJets"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True)
)


process.ak6HiGenNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.6),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("ak6HiSignalGenJets")
)


process.ak6HiSignalGenJets = cms.EDProducer("HiSignalGenJetProducer",
    src = cms.InputTag("ak6HiGenJets")
)


process.ak6PFJets = cms.EDProducer("FastjetJetProducer",
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
    jetPtMin = cms.double(1.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    rParam = cms.double(0.6),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak8CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.8),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
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
    jetPtMin = cms.double(1.0),
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


process.akCs10PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(1.0),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akCs1PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.1),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akCs2PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.2),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akCs3PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"), cms.InputTag("akCs3PFSecondaryVertexTagInfos"))
)


process.akCs3PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"), cms.InputTag("akCs3PFSecondaryVertexTagInfos"))
)


process.akCs3PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akCs3PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akCs3PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"))
)


process.akCs3PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akCs3CaloJets"),
    useRecHits = cms.bool(True)
)


process.akCs3PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"))
)


process.akCs3PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akCs3PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akCs3PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.3),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akCs3PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"), cms.InputTag("akCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akCs3PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"), cms.InputTag("akCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akCs3PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akCs3PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akCs3PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSoftPFMuonsTagInfos"))
)


process.akCs3PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.3),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akCs3PFJets")
)


process.akCs3PFPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akCs3PFPatJetPartonAssociationLegacy")
)


process.akCs3PFPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akCs3PFJets"),
    partons = cms.InputTag("signalPartons")
)


process.akCs3PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akCs3PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"), cms.InputTag("akCs3PFSecondaryVertexTagInfos"))
)


process.akCs3PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"), cms.InputTag("akCs3PFSecondaryVertexTagInfos"))
)


process.akCs3PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSoftPFMuonsTagInfos"))
)


process.akCs3PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akCs3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akCs3PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akCs3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akCs3PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSecondaryVertexTagInfos"))
)


process.akCs3PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSecondaryVertexTagInfos"))
)


process.akCs3PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSoftPFMuonsTagInfos"))
)


process.akCs3PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSoftPFMuonsTagInfos"))
)


process.akCs3PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFSoftPFMuonsTagInfos"))
)


process.akCs3PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akCs3PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akCs3PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"))
)


process.akCs3PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"))
)


process.akCs3PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK3PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akCs3PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akCs3PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("akCs3PFJets")
)


process.akCs3PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("ak3HiSignalGenJets")
)


process.akCs3PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akCs3PFJets")
)


process.akCs3PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akCs3PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akCs3PFPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akCs3PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akCs3PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akCs3PFCombinedSecondaryVertexBJetTags"), cms.InputTag("akCs3PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akCs3PFJetBProbabilityBJetTags"), 
        cms.InputTag("akCs3PFJetProbabilityBJetTags"), cms.InputTag("akCs3PFTrackCountingHighEffBJetTags"), cms.InputTag("akCs3PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akCs3PFmatch"),
    genPartonMatch = cms.InputTag("akCs3PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akCs3PFcorr")),
    jetIDMap = cms.InputTag("akCs3PFJetID"),
    jetSource = cms.InputTag("akCs3PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akCs3PFImpactParameterTagInfos"), cms.InputTag("akCs3PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akCs3PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akCs3PFNjettiness:tau1", "akCs3PFNjettiness:tau2", "akCs3PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akCs4PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"), cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
)


process.akCs4PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('CSVscikitTags'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"), cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
)


process.akCs4PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akCs4PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akCs4PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"))
)


process.akCs4PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akCs4CaloJets"),
    useRecHits = cms.bool(True)
)


process.akCs4PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"))
)


process.akCs4PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akCs4PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akCs4PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.4),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akCs4PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"), cms.InputTag("akCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akCs4PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"), cms.InputTag("akCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akCs4PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akCs4PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akCs4PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSoftPFMuonsTagInfos"))
)


process.akCs4PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.4),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akCs4PFJets")
)


process.akCs4PFPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akCs4PFPatJetPartonAssociationLegacy")
)


process.akCs4PFPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akCs4PFJets"),
    partons = cms.InputTag("signalPartons")
)


process.akCs4PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akCs4PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"), cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
)


process.akCs4PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"), cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
)


process.akCs4PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSoftPFMuonsTagInfos"))
)


process.akCs4PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akCs4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akCs4PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akCs4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akCs4PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
)


process.akCs4PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
)


process.akCs4PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSoftPFMuonsTagInfos"))
)


process.akCs4PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSoftPFMuonsTagInfos"))
)


process.akCs4PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFSoftPFMuonsTagInfos"))
)


process.akCs4PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akCs4PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akCs4PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"))
)


process.akCs4PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"))
)


process.akCs4PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK4PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akCs4PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akCs4PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("akCs4PFJets")
)


process.akCs4PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("ak4HiSignalGenJets")
)


process.akCs4PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akCs4PFJets")
)


process.akCs4PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akCs4PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akCs4PFPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akCs4PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akCs4PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akCs4PFCombinedSecondaryVertexBJetTags"), cms.InputTag("akCs4PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akCs4PFJetBProbabilityBJetTags"), 
        cms.InputTag("akCs4PFJetProbabilityBJetTags"), cms.InputTag("akCs4PFTrackCountingHighEffBJetTags"), cms.InputTag("akCs4PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akCs4PFmatch"),
    genPartonMatch = cms.InputTag("akCs4PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akCs4PFcorr")),
    jetIDMap = cms.InputTag("akCs4PFJetID"),
    jetSource = cms.InputTag("akCs4PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akCs4PFImpactParameterTagInfos"), cms.InputTag("akCs4PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akCs4PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akCs4PFNjettiness:tau1", "akCs4PFNjettiness:tau2", "akCs4PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akCs5PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.5),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akCs6PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akCs8PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.8),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(False),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs10PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(1.0),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs1PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.1),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs2PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.2),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs3PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs3PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs3PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs3PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs3PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akFlowPuCs3PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akFlowPuCs3PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"))
)


process.akFlowPuCs3PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akFlowPuCs3CaloJets"),
    useRecHits = cms.bool(True)
)


process.akFlowPuCs3PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"))
)


process.akFlowPuCs3PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akFlowPuCs3PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akFlowPuCs3PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.3),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs3PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs3PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs3PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs3PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs3PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs3PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.3),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akFlowPuCs3PFJets")
)


process.akFlowPuCs3PFPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akFlowPuCs3PFPatJetPartonAssociationLegacy")
)


process.akFlowPuCs3PFPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akFlowPuCs3PFJets"),
    partons = cms.InputTag("signalPartons")
)


process.akFlowPuCs3PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akFlowPuCs3PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs3PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs3PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs3PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs3PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs3PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akFlowPuCs3PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akFlowPuCs3PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs3PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs3PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs3PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs3PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs3PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akFlowPuCs3PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akFlowPuCs3PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"))
)


process.akFlowPuCs3PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"))
)


process.akFlowPuCs3PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK3PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akFlowPuCs3PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akFlowPuCs3PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("akFlowPuCs3PFJets")
)


process.akFlowPuCs3PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("ak3HiSignalGenJets")
)


process.akFlowPuCs3PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akFlowPuCs3PFJets")
)


process.akFlowPuCs3PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akFlowPuCs3PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akFlowPuCs3PFPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akFlowPuCs3PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akFlowPuCs3PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akFlowPuCs3PFCombinedSecondaryVertexBJetTags"), cms.InputTag("akFlowPuCs3PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akFlowPuCs3PFJetBProbabilityBJetTags"), 
        cms.InputTag("akFlowPuCs3PFJetProbabilityBJetTags"), cms.InputTag("akFlowPuCs3PFTrackCountingHighEffBJetTags"), cms.InputTag("akFlowPuCs3PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akFlowPuCs3PFmatch"),
    genPartonMatch = cms.InputTag("akFlowPuCs3PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFlowPuCs3PFcorr")),
    jetIDMap = cms.InputTag("akFlowPuCs3PFJetID"),
    jetSource = cms.InputTag("akFlowPuCs3PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akFlowPuCs3PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs3PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akFlowPuCs3PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akFlowPuCs3PFNjettiness:tau1", "akFlowPuCs3PFNjettiness:tau2", "akFlowPuCs3PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akFlowPuCs4PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs4PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs4PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs4PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs4PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akFlowPuCs4PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akFlowPuCs4PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"))
)


process.akFlowPuCs4PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akFlowPuCs4CaloJets"),
    useRecHits = cms.bool(True)
)


process.akFlowPuCs4PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"))
)


process.akFlowPuCs4PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akFlowPuCs4PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akFlowPuCs4PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.4),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs4PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs4PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs4PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs4PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSecondaryVertexNegativeTagInfos"))
)


process.akFlowPuCs4PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs4PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.4),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akFlowPuCs4PFJets")
)


process.akFlowPuCs4PFPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akFlowPuCs4PFPatJetPartonAssociationLegacy")
)


process.akFlowPuCs4PFPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akFlowPuCs4PFJets"),
    partons = cms.InputTag("signalPartons")
)


process.akFlowPuCs4PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akFlowPuCs4PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs4PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs4PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs4PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs4PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs4PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akFlowPuCs4PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akFlowPuCs4PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs4PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSecondaryVertexTagInfos"))
)


process.akFlowPuCs4PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs4PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs4PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFSoftPFMuonsTagInfos"))
)


process.akFlowPuCs4PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akFlowPuCs4PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akFlowPuCs4PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"))
)


process.akFlowPuCs4PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"))
)


process.akFlowPuCs4PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK4PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akFlowPuCs4PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akFlowPuCs4PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("akFlowPuCs4PFJets")
)


process.akFlowPuCs4PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
    src = cms.InputTag("ak4HiSignalGenJets")
)


process.akFlowPuCs4PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akFlowPuCs4PFJets")
)


process.akFlowPuCs4PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akFlowPuCs4PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akFlowPuCs4PFPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akFlowPuCs4PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akFlowPuCs4PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akFlowPuCs4PFCombinedSecondaryVertexBJetTags"), cms.InputTag("akFlowPuCs4PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akFlowPuCs4PFJetBProbabilityBJetTags"), 
        cms.InputTag("akFlowPuCs4PFJetProbabilityBJetTags"), cms.InputTag("akFlowPuCs4PFTrackCountingHighEffBJetTags"), cms.InputTag("akFlowPuCs4PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akFlowPuCs4PFmatch"),
    genPartonMatch = cms.InputTag("akFlowPuCs4PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akFlowPuCs4PFcorr")),
    jetIDMap = cms.InputTag("akFlowPuCs4PFJetID"),
    jetSource = cms.InputTag("akFlowPuCs4PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akFlowPuCs4PFImpactParameterTagInfos"), cms.InputTag("akFlowPuCs4PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akFlowPuCs4PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akFlowPuCs4PFNjettiness:tau1", "akFlowPuCs4PFNjettiness:tau2", "akFlowPuCs4PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akFlowPuCs5PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.5),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs6PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akFlowPuCs8PFJets = cms.EDProducer("CSJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    csAlpha = cms.double(2.0),
    csRParam = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges"),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.8),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    useExplicitGhosts = cms.bool(True),
    useModulatedRho = cms.bool(True),
    voronoiRfact = cms.double(-0.9),
    writeJetsWithConst = cms.bool(True)
)


process.akPu10CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(12.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(1.0),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu10PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(30.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(1.0),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu1CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(4.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.1),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu1PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.1),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu2CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(4.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.2),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu2PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.2),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu3CaloCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"), cms.InputTag("akPu3CaloSecondaryVertexTagInfos"))
)


process.akPu3CaloCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"), cms.InputTag("akPu3CaloSecondaryVertexTagInfos"))
)


process.akPu3CaloImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akPu3CaloJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akPu3CaloJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"))
)


process.akPu3CaloJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akPu3CaloJets"),
    useRecHits = cms.bool(True)
)


process.akPu3CaloJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"))
)


process.akPu3CaloJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akPu3CaloJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akPu3CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(6.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.3),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu3CaloNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"), cms.InputTag("akPu3CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu3CaloNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"), cms.InputTag("akPu3CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu3CaloNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu3CaloNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu3CaloNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSoftPFMuonsTagInfos"))
)


process.akPu3CaloNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.3),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akPu3CaloJets")
)


process.akPu3CaloPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akPu3CaloPatJetPartonAssociationLegacy")
)


process.akPu3CaloPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akPu3CaloJets"),
    partons = cms.InputTag("signalPartons")
)


process.akPu3CaloPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akPu3CaloPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"), cms.InputTag("akPu3CaloSecondaryVertexTagInfos"))
)


process.akPu3CaloPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"), cms.InputTag("akPu3CaloSecondaryVertexTagInfos"))
)


process.akPu3CaloPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSoftPFMuonsTagInfos"))
)


process.akPu3CaloSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu3CaloImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu3CaloSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu3CaloImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu3CaloSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSecondaryVertexTagInfos"))
)


process.akPu3CaloSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSecondaryVertexTagInfos"))
)


process.akPu3CaloSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSoftPFMuonsTagInfos"))
)


process.akPu3CaloSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSoftPFMuonsTagInfos"))
)


process.akPu3CaloSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloSoftPFMuonsTagInfos"))
)


process.akPu3CaloSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akPu3CaloJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akPu3CaloTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"))
)


process.akPu3CaloTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"))
)


process.akPu3Calocorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK4PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akPu3CaloJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akPu3Calomatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu3CaloJets")
)


process.akPu3CalomatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak3HiSignalGenJets")
)


process.akPu3Caloparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu3CaloJets")
)


process.akPu3CalopatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akPu3CaloPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akPu3CaloPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akPu3CaloSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akPu3CaloSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akPu3CaloCombinedSecondaryVertexBJetTags"), cms.InputTag("akPu3CaloCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akPu3CaloJetBProbabilityBJetTags"), 
        cms.InputTag("akPu3CaloJetProbabilityBJetTags"), cms.InputTag("akPu3CaloTrackCountingHighEffBJetTags"), cms.InputTag("akPu3CaloTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akPu3Calomatch"),
    genPartonMatch = cms.InputTag("akPu3Caloparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3Calocorr")),
    jetIDMap = cms.InputTag("akPu3CaloJetID"),
    jetSource = cms.InputTag("akPu3CaloJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akPu3CaloImpactParameterTagInfos"), cms.InputTag("akPu3CaloSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akPu3CaloJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akPu3CaloNjettiness:tau1", "akPu3CaloNjettiness:tau2", "akPu3CaloNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akPu3PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
)


process.akPu3PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
)


process.akPu3PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akPu3PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akPu3PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))
)


process.akPu3PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akPu3CaloJets"),
    useRecHits = cms.bool(True)
)


process.akPu3PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))
)


process.akPu3PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akPu3PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akPu3PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(15.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.3),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu3PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), cms.InputTag("akPu3PFSecondaryVertexNegativeTagInfos"))
)


process.akPu3PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), cms.InputTag("akPu3PFSecondaryVertexNegativeTagInfos"))
)


process.akPu3PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSecondaryVertexNegativeTagInfos"))
)


process.akPu3PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSecondaryVertexNegativeTagInfos"))
)


process.akPu3PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSoftPFMuonsTagInfos"))
)


process.akPu3PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.3),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akPu3PFJets")
)


process.akPu3PFPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akPu3PFPatJetPartonAssociationLegacy")
)


process.akPu3PFPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akPu3PFJets"),
    partons = cms.InputTag("signalPartons")
)


process.akPu3PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akPu3PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
)


process.akPu3PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
)


process.akPu3PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSoftPFMuonsTagInfos"))
)


process.akPu3PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu3PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu3PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu3PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
)


process.akPu3PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSecondaryVertexTagInfos"))
)


process.akPu3PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSoftPFMuonsTagInfos"))
)


process.akPu3PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSoftPFMuonsTagInfos"))
)


process.akPu3PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFSoftPFMuonsTagInfos"))
)


process.akPu3PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akPu3PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akPu3PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))
)


process.akPu3PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"))
)


process.akPu3PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK3PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akPu3PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akPu3PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu3PFJets")
)


process.akPu3PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak3HiSignalGenJets"),
    maxDeltaR = cms.double(0.3),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak3HiSignalGenJets")
)


process.akPu3PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu3PFJets")
)


process.akPu3PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akPu3PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akPu3PFPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akPu3PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akPu3PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akPu3PFCombinedSecondaryVertexBJetTags"), cms.InputTag("akPu3PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akPu3PFJetBProbabilityBJetTags"), 
        cms.InputTag("akPu3PFJetProbabilityBJetTags"), cms.InputTag("akPu3PFTrackCountingHighEffBJetTags"), cms.InputTag("akPu3PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akPu3PFmatch"),
    genPartonMatch = cms.InputTag("akPu3PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu3PFcorr")),
    jetIDMap = cms.InputTag("akPu3PFJetID"),
    jetSource = cms.InputTag("akPu3PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akPu3PFImpactParameterTagInfos"), cms.InputTag("akPu3PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akPu3PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akPu3PFNjettiness:tau1", "akPu3PFNjettiness:tau2", "akPu3PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akPu4CaloCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"), cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))
)


process.akPu4CaloCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('CSVscikitTags'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"), cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))
)


process.akPu4CaloImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akPu4CaloJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akPu4CaloJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"))
)


process.akPu4CaloJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akPu4CaloJets"),
    useRecHits = cms.bool(True)
)


process.akPu4CaloJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"))
)


process.akPu4CaloJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akPu4CaloJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akPu4CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(8.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu4CaloNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"), cms.InputTag("akPu4CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu4CaloNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"), cms.InputTag("akPu4CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu4CaloNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu4CaloNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSecondaryVertexNegativeTagInfos"))
)


process.akPu4CaloNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSoftPFMuonsTagInfos"))
)


process.akPu4CaloNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.4),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akPu4CaloJets")
)


process.akPu4CaloPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akPu4CaloPatJetPartonAssociationLegacy")
)


process.akPu4CaloPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akPu4CaloJets"),
    partons = cms.InputTag("signalPartons")
)


process.akPu4CaloPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akPu4CaloPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"), cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))
)


process.akPu4CaloPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"), cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))
)


process.akPu4CaloPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSoftPFMuonsTagInfos"))
)


process.akPu4CaloSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu4CaloImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu4CaloSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu4CaloImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu4CaloSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))
)


process.akPu4CaloSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))
)


process.akPu4CaloSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSoftPFMuonsTagInfos"))
)


process.akPu4CaloSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSoftPFMuonsTagInfos"))
)


process.akPu4CaloSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloSoftPFMuonsTagInfos"))
)


process.akPu4CaloSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akPu4CaloJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akPu4CaloTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"))
)


process.akPu4CaloTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"))
)


process.akPu4Calocorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK4PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akPu4CaloJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akPu4Calomatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu4CaloJets")
)


process.akPu4CalomatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak4HiSignalGenJets")
)


process.akPu4Caloparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu4CaloJets")
)


process.akPu4CalopatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akPu4CaloPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akPu4CaloPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akPu4CaloSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akPu4CaloSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akPu4CaloCombinedSecondaryVertexBJetTags"), cms.InputTag("akPu4CaloCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akPu4CaloJetBProbabilityBJetTags"), 
        cms.InputTag("akPu4CaloJetProbabilityBJetTags"), cms.InputTag("akPu4CaloTrackCountingHighEffBJetTags"), cms.InputTag("akPu4CaloTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akPu4Calomatch"),
    genPartonMatch = cms.InputTag("akPu4Caloparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu4Calocorr")),
    jetIDMap = cms.InputTag("akPu4CaloJetID"),
    jetSource = cms.InputTag("akPu4CaloJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akPu4CaloImpactParameterTagInfos"), cms.InputTag("akPu4CaloSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akPu4CaloJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akPu4CaloNjettiness:tau1", "akPu4CaloNjettiness:tau2", "akPu4CaloNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akPu4PFCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"), cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
)


process.akPu4PFCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('CSVscikitTags'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"), cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
)


process.akPu4PFImpactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("akPu4PFJetTracksAssociatorAtVertex"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.akPu4PFJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"))
)


process.akPu4PFJetID = cms.EDProducer("JetIDProducer",
    ebRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    eeRecHitsColl = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    hbheRecHitsColl = cms.InputTag("hbhereco"),
    hfRecHitsColl = cms.InputTag("hfreco"),
    hoRecHitsColl = cms.InputTag("horeco"),
    rpcRecHits = cms.InputTag("rpcRecHits"),
    src = cms.InputTag("akPu4CaloJets"),
    useRecHits = cms.bool(True)
)


process.akPu4PFJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"))
)


process.akPu4PFJetTracksAssociatorAtVertex = cms.EDProducer("JetTracksAssociatorAtVertex",
    coneSize = cms.double(0.5),
    jets = cms.InputTag("akPu4PFJets"),
    pvSrc = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("highPurityTracks"),
    useAssigned = cms.bool(False)
)


process.akPu4PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(20.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.4),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu4PFNegativeCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"), cms.InputTag("akPu4PFSecondaryVertexNegativeTagInfos"))
)


process.akPu4PFNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"), cms.InputTag("akPu4PFSecondaryVertexNegativeTagInfos"))
)


process.akPu4PFNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSecondaryVertexNegativeTagInfos"))
)


process.akPu4PFNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSecondaryVertexNegativeTagInfos"))
)


process.akPu4PFNegativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSoftPFMuonsTagInfos"))
)


process.akPu4PFNjettiness = cms.EDProducer("NjettinessAdder",
    Njets = cms.vuint32(1, 2, 3, 4),
    R0 = cms.double(0.4),
    Rcutoff = cms.double(999.0),
    akAxesR0 = cms.double(999.0),
    axesDefinition = cms.uint32(6),
    beta = cms.double(1.0),
    measureDefinition = cms.uint32(0),
    nPass = cms.int32(999),
    src = cms.InputTag("akPu4PFJets")
)


process.akPu4PFPatJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("akPu4PFPatJetPartonAssociationLegacy")
)


process.akPu4PFPatJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("akPu4PFJets"),
    partons = cms.InputTag("signalPartons")
)


process.akPu4PFPatJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("hiSignalGenParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.akPu4PFPositiveCombinedSecondaryVertexBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"), cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
)


process.akPu4PFPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"), cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
)


process.akPu4PFPositiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSoftPFMuonsTagInfos"))
)


process.akPu4PFSecondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu4PFSecondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("akPu4PFImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.akPu4PFSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
)


process.akPu4PFSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
)


process.akPu4PFSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSoftPFMuonsTagInfos"))
)


process.akPu4PFSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSoftPFMuonsTagInfos"))
)


process.akPu4PFSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFSoftPFMuonsTagInfos"))
)


process.akPu4PFSoftPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("akPu4PFJets"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.akPu4PFTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"))
)


process.akPu4PFTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"))
)


process.akPu4PFcorr = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring('L2Relative'),
    payload = cms.string('AK4PF'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("akPu4PFJets"),
    useNPV = cms.bool(False),
    useRho = cms.bool(False)
)


process.akPu4PFmatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu4PFJets")
)


process.akPu4PFmatchGroomed = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4HiSignalGenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak4HiSignalGenJets")
)


process.akPu4PFparton = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("hiSignalGenParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("akPu4PFJets")
)


process.akPu4PFpatJetsWithBtagging = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("akPu4PFPatJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("akPu4PFPatJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(False),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(True),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("akPu4PFSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("akPu4PFSimpleSecondaryVertexHighPurBJetTags"), cms.InputTag("akPu4PFCombinedSecondaryVertexBJetTags"), cms.InputTag("akPu4PFCombinedSecondaryVertexV2BJetTags"), cms.InputTag("akPu4PFJetBProbabilityBJetTags"), 
        cms.InputTag("akPu4PFJetProbabilityBJetTags"), cms.InputTag("akPu4PFTrackCountingHighEffBJetTags"), cms.InputTag("akPu4PFTrackCountingHighPurBJetTags")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("akPu4PFmatch"),
    genPartonMatch = cms.InputTag("akPu4PFparton"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("akPu4PFcorr")),
    jetIDMap = cms.InputTag("akPu4PFJetID"),
    jetSource = cms.InputTag("akPu4PFJets"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(cms.InputTag("akPu4PFImpactParameterTagInfos"), cms.InputTag("akPu4PFSecondaryVertexTagInfos")),
    trackAssociationSource = cms.InputTag("akPu4PFJetTracksAssociatorAtVertex"),
    useLegacyJetMCFlavour = cms.bool(True),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("", "akPu4PFNjettiness:tau1", "akPu4PFNjettiness:tau2", "akPu4PFNjettiness:tau3")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.akPu5CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.5),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu5PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(25.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.5),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu6CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(12.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.6),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu6PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(30.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.6),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu8CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nExclude = cms.uint32(2),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(12.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.8),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.akPu8PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(True),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('BasicJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.5),
    nExclude = cms.uint32(2),
    puCenters = cms.vdouble(
        -5, -4, -3, -2, -1, 
        0, 1, 2, 3, 4, 
        5
    ),
    puPtMin = cms.double(30.0),
    puWidth = cms.double(0.8),
    rParam = cms.double(0.8),
    src = cms.InputTag("PFTowers"),
    srcPVs = cms.InputTag(""),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.bToCharmDecayVertexMerged = cms.EDProducer("BtoCharmDecayVertexMerger",
    maxDRUnique = cms.double(0.4),
    maxPtreltomerge = cms.double(7777.0),
    maxvecSumIMifsmallDRUnique = cms.double(5.5),
    minCosPAtomerge = cms.double(0.99),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("inclusiveSecondaryVerticesFiltered")
)


process.calibratedElectrons = cms.EDProducer("CalibratedElectronProducer",
    correctionFile = cms.string('EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc'),
    epCombConfig = cms.PSet(
        ecalTrkRegressionConfig = cms.PSet(
            ebHighEtForestName = cms.string('electron_eb_ECALTRK'),
            ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt'),
            eeHighEtForestName = cms.string('electron_ee_ECALTRK'),
            eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt'),
            forceHighEnergyTrainingIfSaturated = cms.bool(False),
            lowEtHighEtBoundary = cms.double(50.0),
            rangeMaxHighEt = cms.double(3.0),
            rangeMaxLowEt = cms.double(3.0),
            rangeMinHighEt = cms.double(-1.0),
            rangeMinLowEt = cms.double(-1.0)
        ),
        ecalTrkRegressionUncertConfig = cms.PSet(
            ebHighEtForestName = cms.string('electron_eb_ECALTRK_var'),
            ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt_var'),
            eeHighEtForestName = cms.string('electron_ee_ECALTRK_var'),
            eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt_var'),
            forceHighEnergyTrainingIfSaturated = cms.bool(False),
            lowEtHighEtBoundary = cms.double(50.0),
            rangeMaxHighEt = cms.double(0.5),
            rangeMaxLowEt = cms.double(0.5),
            rangeMinHighEt = cms.double(0.0002),
            rangeMinLowEt = cms.double(0.0002)
        ),
        maxEPDiffInSigmaForComb = cms.double(15.0),
        maxEcalEnergyForComb = cms.double(200.0),
        maxRelTrkMomErrForComb = cms.double(10.0),
        minEOverPForComb = cms.double(0.025)
    ),
    minEtToCalibrate = cms.double(5.0),
    produceCalibratedObjs = cms.bool(True),
    recHitCollectionEB = cms.InputTag("reducedEcalRecHitsEB"),
    recHitCollectionEE = cms.InputTag("reducedEcalRecHitsEE"),
    semiDeterministic = cms.bool(True),
    src = cms.InputTag("gedGsfElectrons")
)


process.calibratedPatElectrons = cms.EDProducer("CalibratedPatElectronProducer",
    correctionFile = cms.string('EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc'),
    epCombConfig = cms.PSet(
        ecalTrkRegressionConfig = cms.PSet(
            ebHighEtForestName = cms.string('electron_eb_ECALTRK'),
            ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt'),
            eeHighEtForestName = cms.string('electron_ee_ECALTRK'),
            eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt'),
            forceHighEnergyTrainingIfSaturated = cms.bool(False),
            lowEtHighEtBoundary = cms.double(50.0),
            rangeMaxHighEt = cms.double(3.0),
            rangeMaxLowEt = cms.double(3.0),
            rangeMinHighEt = cms.double(-1.0),
            rangeMinLowEt = cms.double(-1.0)
        ),
        ecalTrkRegressionUncertConfig = cms.PSet(
            ebHighEtForestName = cms.string('electron_eb_ECALTRK_var'),
            ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt_var'),
            eeHighEtForestName = cms.string('electron_ee_ECALTRK_var'),
            eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt_var'),
            forceHighEnergyTrainingIfSaturated = cms.bool(False),
            lowEtHighEtBoundary = cms.double(50.0),
            rangeMaxHighEt = cms.double(0.5),
            rangeMaxLowEt = cms.double(0.5),
            rangeMinHighEt = cms.double(0.0002),
            rangeMinLowEt = cms.double(0.0002)
        ),
        maxEPDiffInSigmaForComb = cms.double(15.0),
        maxEcalEnergyForComb = cms.double(200.0),
        maxRelTrkMomErrForComb = cms.double(10.0),
        minEOverPForComb = cms.double(0.025)
    ),
    minEtToCalibrate = cms.double(5.0),
    produceCalibratedObjs = cms.bool(True),
    recHitCollectionEB = cms.InputTag("reducedEgamma","reducedEBRecHits"),
    recHitCollectionEE = cms.InputTag("reducedEgamma","reducedEERecHits"),
    semiDeterministic = cms.bool(True),
    src = cms.InputTag("slimmedElectrons")
)


process.calibratedPatPhotons = cms.EDProducer("CalibratedPatPhotonProducer",
    correctionFile = cms.string('EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc'),
    minEtToCalibrate = cms.double(5.0),
    produceCalibratedObjs = cms.bool(True),
    recHitCollectionEB = cms.InputTag("reducedEgamma","reducedEBRecHits"),
    recHitCollectionEE = cms.InputTag("reducedEgamma","reducedEERecHits"),
    semiDeterministic = cms.bool(True),
    src = cms.InputTag("slimmedPhotons")
)


process.calibratedPhotons = cms.EDProducer("CalibratedPhotonProducer",
    correctionFile = cms.string('EgammaAnalysis/ElectronTools/data/ScalesSmearings/Run2017_17Nov2017_v1_ele_unc'),
    minEtToCalibrate = cms.double(5.0),
    produceCalibratedObjs = cms.bool(True),
    recHitCollectionEB = cms.InputTag("reducedEcalRecHitsEB"),
    recHitCollectionEE = cms.InputTag("reducedEcalRecHitsEE"),
    semiDeterministic = cms.bool(True),
    src = cms.InputTag("gedPhotons")
)


process.candidateVertexArbitrator = cms.EDProducer("CandidateVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxTimeSignificance = cms.double(3.5),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("candidateVertexMerger"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("particleFlow")
)


process.candidateVertexArbitratorCvsL = cms.EDProducer("CandidateVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxTimeSignificance = cms.double(3.5),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("candidateVertexMergerCvsL"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("particleFlow")
)


process.candidateVertexArbitratorDefault = cms.EDProducer("CandidateVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxTimeSignificance = cms.double(3.5),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("candidateVertexMerger"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("particleFlow")
)


process.candidateVertexMerger = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.7),
    minSignificance = cms.double(2),
    secondaryVertices = cms.InputTag("inclusiveCandidateVertexFinder")
)


process.candidateVertexMergerCvsL = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.7),
    minSignificance = cms.double(2),
    secondaryVertices = cms.InputTag("inclusiveCandidateVertexFinderCvsL")
)


process.centralityBin = cms.EDProducer("CentralityBinProducer",
    Centrality = cms.InputTag("hiCentrality"),
    centralityVariable = cms.string('HFtowers'),
    nonDefaultGlauberModel = cms.string(''),
    pPbRunFlip = cms.uint32(99999999)
)


process.cleanedPartons = cms.EDProducer("HiPartonCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("myPartons")
)


process.combinedInclusiveSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("inclusiveSecondaryVertexFinderTagInfos"))
)


process.combinedMVAV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedMVAV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("secondaryVertexTagInfos"), cms.InputTag("inclusiveSecondaryVertexFinderTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.combinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('combinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("secondaryVertexTagInfos"))
)


process.correctedElectrons = cms.EDProducer("CorrectedElectronProducer",
    centrality = cms.InputTag("centralityBin","HFtowers"),
    correctionFile = cms.string('HeavyIonsAnalysis/PhotonAnalysis/data/SS2018PbPbMC.dat'),
    epCombConfig = cms.PSet(
        ecalTrkRegressionConfig = cms.PSet(
            ebHighEtForestName = cms.string('electron_eb_ECALTRK'),
            ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt'),
            eeHighEtForestName = cms.string('electron_ee_ECALTRK'),
            eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt'),
            forceHighEnergyTrainingIfSaturated = cms.bool(False),
            lowEtHighEtBoundary = cms.double(50.0),
            rangeMaxHighEt = cms.double(3.0),
            rangeMaxLowEt = cms.double(3.0),
            rangeMinHighEt = cms.double(-1.0),
            rangeMinLowEt = cms.double(-1.0)
        ),
        ecalTrkRegressionUncertConfig = cms.PSet(
            ebHighEtForestName = cms.string('electron_eb_ECALTRK_var'),
            ebLowEtForestName = cms.string('electron_eb_ECALTRK_lowpt_var'),
            eeHighEtForestName = cms.string('electron_ee_ECALTRK_var'),
            eeLowEtForestName = cms.string('electron_ee_ECALTRK_lowpt_var'),
            forceHighEnergyTrainingIfSaturated = cms.bool(False),
            lowEtHighEtBoundary = cms.double(50.0),
            rangeMaxHighEt = cms.double(0.5),
            rangeMaxLowEt = cms.double(0.5),
            rangeMinHighEt = cms.double(0.0002),
            rangeMinLowEt = cms.double(0.0002)
        ),
        maxEPDiffInSigmaForComb = cms.double(15.0),
        maxEcalEnergyForComb = cms.double(200.0),
        maxRelTrkMomErrForComb = cms.double(10.0),
        minEOverPForComb = cms.double(0.025)
    ),
    minPt = cms.double(20.0),
    semiDeterministic = cms.bool(True),
    src = cms.InputTag("gedGsfElectrons")
)


process.doubleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('doubleVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("inclusiveSecondaryVertexFinderFilteredTagInfos"))
)


process.genParticlesForJets = cms.EDProducer("InputGenJetsParticleSelector",
    excludeFromResonancePids = cms.vuint32(12, 13, 14, 16),
    excludeResonances = cms.bool(False),
    ignoreParticleIDs = cms.vuint32(
        1000022, 1000012, 1000014, 1000016, 2000012, 
        2000014, 2000016, 1000039, 5100039, 4000012, 
        4000014, 4000016, 9900012, 9900014, 9900016, 
        39
    ),
    partonicFinalState = cms.bool(False),
    src = cms.InputTag("genParticles"),
    tausAsJets = cms.bool(False)
)


process.genParticlesForJetsSignal = cms.EDProducer("InputGenJetsParticleSelector",
    excludeFromResonancePids = cms.vuint32(12, 13, 14, 16),
    excludeResonances = cms.bool(False),
    ignoreParticleIDs = cms.vuint32(
        1000022, 1000012, 1000014, 1000016, 2000012, 
        2000014, 2000016, 1000039, 5100039, 4000012, 
        4000014, 4000016, 9900012, 9900014, 9900016, 
        39
    ),
    partonicFinalState = cms.bool(False),
    src = cms.InputTag("hiSignalGenParticles"),
    tausAsJets = cms.bool(False)
)


process.ghostTrackBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('ghostTrackComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("ghostTrackVertexTagInfos"))
)


process.ghostTrackVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("impactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(1),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('gtvr'),
        fitType = cms.string('RefitGhostTrackWithVertices'),
        maxFitChi2 = cms.double(10.0),
        mergeThreshold = cms.double(3.0),
        primcut = cms.double(2.0),
        seccut = cms.double(4.0)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.heavyIonCleanedGenJets = cms.EDProducer("HiGenJetCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("iterativeCone5HiGenJets")
)


process.hiFJGridEmptyAreaCalculator = cms.EDProducer("HiFJGridEmptyAreaCalculator",
    CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    bandWidth = cms.double(0.2),
    doCentrality = cms.bool(True),
    gridWidth = cms.double(0.05),
    hiBinCut = cms.int32(100),
    jetSource = cms.InputTag("kt4PFJetsForRho"),
    keepGridInfo = cms.bool(False),
    mapEtaEdges = cms.InputTag("hiFJRhoProducer","mapEtaEdges"),
    mapToRho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    mapToRhoM = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    pfCandSource = cms.InputTag("particleFlow")
)


process.hiFJGridEmptyAreaCalculatorFinerBins = cms.EDProducer("HiFJGridEmptyAreaCalculator",
    CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    bandWidth = cms.double(0.2),
    doCentrality = cms.bool(True),
    gridWidth = cms.double(0.05),
    hiBinCut = cms.int32(100),
    jetSource = cms.InputTag("kt4PFJetsForRho"),
    keepGridInfo = cms.bool(False),
    mapEtaEdges = cms.InputTag("hiFJRhoProducerFinerBins","mapEtaEdges"),
    mapToRho = cms.InputTag("hiFJRhoProducerFinerBins","mapToRho"),
    mapToRhoM = cms.InputTag("hiFJRhoProducerFinerBins","mapToRhoM"),
    pfCandSource = cms.InputTag("particleFlow")
)


process.hiFJRhoFlowModulationProducer = cms.EDProducer("HiFJRhoFlowModulationProducer",
    EvtPlane = cms.InputTag("hiEvtPlane"),
    doEvtPlane = cms.bool(False),
    doFlatTest = cms.bool(True),
    doFreePlaneFit = cms.bool(False),
    doJettyExclusion = cms.bool(False),
    evtPlaneLevel = cms.int32(0),
    jetTag = cms.InputTag("ak4PFJetsForFlow"),
    pfCandSource = cms.InputTag("particleFlow")
)


process.hiFJRhoProducer = cms.EDProducer("HiFJRhoProducer",
    etaMaxExcl = cms.double(2.0),
    etaMaxExcl2 = cms.double(3.0),
    etaRanges = cms.vdouble(
        -5.0, -3.0, -2.1, -1.3, 1.3, 
        2.1, 3.0, 5.0
    ),
    jetSource = cms.InputTag("kt4PFJetsForRho"),
    nExcl = cms.int32(2),
    nExcl2 = cms.int32(1),
    ptMinExcl = cms.double(20.0),
    ptMinExcl2 = cms.double(20.0)
)


process.hiFJRhoProducerFinerBins = cms.EDProducer("HiFJRhoProducer",
    etaMaxExcl = cms.double(2.0),
    etaMaxExcl2 = cms.double(3.0),
    etaRanges = cms.vdouble(
        -5.0, -4.0, -3, -2.5, -2.0, 
        -0.8, 0.8, 2.0, 2.5, 3.0, 
        4.0, 5.0
    ),
    jetSource = cms.InputTag("kt4PFJetsForRho"),
    nExcl = cms.int32(2),
    nExcl2 = cms.int32(1),
    ptMinExcl = cms.double(20.0),
    ptMinExcl2 = cms.double(20.0)
)


process.hiPartons = cms.EDProducer("HiPartonCleaner",
    createNewCollection = cms.untracked.bool(True),
    deltaR = cms.double(0.25),
    fillDummyEntries = cms.untracked.bool(True),
    ptCut = cms.double(20),
    src = cms.InputTag("genPartons")
)


process.hiPuRhoR3Producer = cms.EDProducer("HiPuRhoProducer",
    medianWindowWidth = cms.int32(2),
    minimumTowersFraction = cms.double(0.7),
    nSigmaPU = cms.double(1.0),
    puPtMin = cms.double(15.0),
    rParam = cms.double(0.3),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("PFTowers"),
    towSigmaCut = cms.double(5.0)
)


process.hiSignalGenJets = cms.EDProducer("HiSignalGenJetProducer",
    src = cms.InputTag("ak4HiGenJets")
)


process.hiSignalGenParticles = cms.EDProducer("HiSignalParticleProducer",
    src = cms.InputTag("genParticles")
)


process.impactParameterMVABJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('impactParameterMVAComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.impactParameterTagInfos = cms.EDProducer("TrackIPProducer",
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jetTracks = cms.InputTag("ak4JetTracksAssociatorAtVertexPF"),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(8),
    minimumNumberOfPixelHits = cms.int32(2),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.inclusiveCandidateSecondaryVertices = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.2),
    minSignificance = cms.double(10.0),
    secondaryVertices = cms.InputTag("candidateVertexArbitrator")
)


process.inclusiveCandidateSecondaryVerticesCvsL = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.2),
    minSignificance = cms.double(10.0),
    secondaryVertices = cms.InputTag("candidateVertexArbitratorCvsL")
)


process.inclusiveCandidateVertexFinder = cms.EDProducer("InclusiveCandidateVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(20),
        maxTimeSignificance = cms.double(3.5),
        seedMax3DIPSignificance = cms.double(9999),
        seedMax3DIPValue = cms.double(9999),
        seedMin3DIPSignificance = cms.double(1.2),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    maximumTimeSignificance = cms.double(3),
    minHits = cms.uint32(0),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("particleFlow"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(2.5),
    vertexMinDLenSig = cms.double(0.5),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.inclusiveCandidateVertexFinderCvsL = cms.EDProducer("InclusiveCandidateVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(20),
        maxTimeSignificance = cms.double(3.5),
        seedMax3DIPSignificance = cms.double(9999),
        seedMax3DIPValue = cms.double(9999),
        seedMin3DIPSignificance = cms.double(1.2),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    maximumTimeSignificance = cms.double(3),
    minHits = cms.uint32(0),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("particleFlow"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(1.25),
    vertexMinDLenSig = cms.double(0.25),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.inclusiveCandidateVertexFinderDefault = cms.EDProducer("InclusiveCandidateVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(20),
        maxTimeSignificance = cms.double(3.5),
        seedMax3DIPSignificance = cms.double(9999),
        seedMax3DIPValue = cms.double(9999),
        seedMin3DIPSignificance = cms.double(1.2),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    maximumTimeSignificance = cms.double(3),
    minHits = cms.uint32(0),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("particleFlow"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(2.5),
    vertexMinDLenSig = cms.double(0.5),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.inclusiveSecondaryVertexFinderFilteredNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("bToCharmDecayVertexMerged"),
    extSVDeltaRToJet = cms.double(-0.4),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("impactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-2.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.inclusiveSecondaryVertexFinderFilteredTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("bToCharmDecayVertexMerged"),
    extSVDeltaRToJet = cms.double(0.4),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("impactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(2.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.inclusiveSecondaryVertexFinderNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveSecondaryVertices"),
    extSVDeltaRToJet = cms.double(-0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("impactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-2.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.inclusiveSecondaryVertexFinderTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveSecondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("impactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(2.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.inclusiveSecondaryVertices = cms.EDProducer("VertexMerger",
    maxFraction = cms.double(0.2),
    minSignificance = cms.double(10.0),
    secondaryVertices = cms.InputTag("trackVertexArbitrator")
)


process.inclusiveVertexFinder = cms.EDProducer("InclusiveVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(20),
        maxTimeSignificance = cms.double(3.5),
        seedMax3DIPSignificance = cms.double(9999),
        seedMax3DIPValue = cms.double(9999),
        seedMin3DIPSignificance = cms.double(1.2),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    maximumTimeSignificance = cms.double(3),
    minHits = cms.uint32(8),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(2.5),
    vertexMinDLenSig = cms.double(0.5),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.inclusiveVertexFinderDefault = cms.EDProducer("InclusiveVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(20),
        maxTimeSignificance = cms.double(3.5),
        seedMax3DIPSignificance = cms.double(9999),
        seedMax3DIPValue = cms.double(9999),
        seedMin3DIPSignificance = cms.double(1.2),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    maximumTimeSignificance = cms.double(3),
    minHits = cms.uint32(8),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(2.5),
    vertexMinDLenSig = cms.double(0.5),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.jetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.jetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('jetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.kt4PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('Kt'),
    jetPtMin = cms.double(0.0),
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


process.kt4PFJetsForRho = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    Rho_EtaMax = cms.double(4.5),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(True),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('Kt'),
    jetPtMin = cms.double(0.0),
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
    rParam = cms.double(0.4),
    src = cms.InputTag("particleFlow"),
    srcPVs = cms.InputTag(""),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.myPartons = cms.EDProducer("PartonSelector",
    src = cms.InputTag("genParticles"),
    withLeptons = cms.bool(False)
)


process.negativeCombinedInclusiveSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("inclusiveSecondaryVertexFinderNegativeTagInfos"))
)


process.negativeCombinedMVAV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedMVAV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("secondaryVertexNegativeTagInfos"), cms.InputTag("inclusiveSecondaryVertexFinderNegativeTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.negativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("secondaryVertexNegativeTagInfos"))
)


process.negativeOnlyJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeOnlyJetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.negativeOnlyJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeOnlyJetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.negativeSimpleInclusiveSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("inclusiveSecondaryVertexFinderFilteredNegativeTagInfos"))
)


process.negativeSimpleInclusiveSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("inclusiveSecondaryVertexFinderFilteredNegativeTagInfos"))
)


process.negativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("secondaryVertexNegativeTagInfos"))
)


process.negativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("secondaryVertexNegativeTagInfos"))
)


process.negativeSoftPFElectronBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFElectronComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.negativeSoftPFElectronByIP2dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFElectronByIP2dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.negativeSoftPFElectronByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFElectronByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.negativeSoftPFElectronByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFElectronByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.negativeSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.negativeSoftPFMuonByIP2dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByIP2dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.negativeSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.negativeSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.negativeTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeTrackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.negativeTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('negativeTrackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.offlinePrimaryVertices = cms.EDProducer("PrimaryVertexProducer",
    TkClusParameters = cms.PSet(
        TkDAClusParameters = cms.PSet(
            Tmin = cms.double(2.0),
            Tpurge = cms.double(2.0),
            Tstop = cms.double(0.5),
            coolingFactor = cms.double(0.6),
            d0CutOff = cms.double(3.0),
            dzCutOff = cms.double(3.0),
            uniquetrkweight = cms.double(0.8),
            vertexSize = cms.double(0.006),
            zmerge = cms.double(0.01)
        ),
        algorithm = cms.string('DA_vect')
    ),
    TkFilterParameters = cms.PSet(
        algorithm = cms.string('filter'),
        maxD0Significance = cms.double(4.0),
        maxEta = cms.double(2.4),
        maxNormalizedChi2 = cms.double(10.0),
        minPixelLayersWithHits = cms.int32(2),
        minPt = cms.double(0.0),
        minSiliconLayersWithHits = cms.int32(5),
        trackQuality = cms.string('any')
    ),
    TrackLabel = cms.InputTag("highPurityTracks"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    verbose = cms.untracked.bool(False),
    vertexCollections = cms.VPSet(
        cms.PSet(
            algorithm = cms.string('AdaptiveVertexFitter'),
            chi2cutoff = cms.double(2.5),
            label = cms.string(''),
            maxDistanceToBeam = cms.double(1.0),
            minNdof = cms.double(0.0),
            useBeamConstraint = cms.bool(False)
        ), 
        cms.PSet(
            algorithm = cms.string('AdaptiveVertexFitter'),
            chi2cutoff = cms.double(2.5),
            label = cms.string('WithBS'),
            maxDistanceToBeam = cms.double(1.0),
            minNdof = cms.double(2.0),
            useBeamConstraint = cms.bool(True)
        )
    )
)


process.offlinePrimaryVerticesRecovery = cms.EDProducer("PrimaryVertexRecoveryProducer",
    TkClusParameters = cms.PSet(
        TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(1.0)
        ),
        algorithm = cms.string('gap')
    ),
    TkFilterParameters = cms.PSet(
        algorithm = cms.string('filter'),
        maxD0Significance = cms.double(999.0),
        maxEta = cms.double(999.0),
        maxNormalizedChi2 = cms.double(999.0),
        minPixelLayersWithHits = cms.int32(0),
        minPt = cms.double(0.0),
        minSiliconLayersWithHits = cms.int32(0),
        trackQuality = cms.string('any')
    ),
    TrackLabel = cms.InputTag("generalTracks"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    oldVertexLabel = cms.InputTag("offlinePrimaryVertices"),
    redoAllVertices = cms.bool(False),
    verbose = cms.untracked.bool(False),
    vertexCollections = cms.VPSet(cms.PSet(
        algorithm = cms.string('AdaptiveVertexFitter'),
        chi2cutoff = cms.double(2.5),
        label = cms.string(''),
        maxDistanceToBeam = cms.double(1.0),
        minNdof = cms.double(0.0),
        useBeamConstraint = cms.bool(False)
    ))
)


process.patJetCorrFactors = cms.EDProducer("JetCorrFactorsProducer",
    emf = cms.bool(False),
    extraJPTOffset = cms.string('L1FastJet'),
    flavorType = cms.string('J'),
    levels = cms.vstring(
        'L1FastJet', 
        'L2Relative', 
        'L3Absolute'
    ),
    payload = cms.string('AK4PFchs'),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    src = cms.InputTag("ak4PFJetsCHS"),
    useNPV = cms.bool(True),
    useRho = cms.bool(True)
)


process.patJetFlavourAssociation = cms.EDProducer("JetFlavourClustering",
    bHadrons = cms.InputTag("patJetPartons","bHadrons"),
    cHadrons = cms.InputTag("patJetPartons","cHadrons"),
    ghostRescaling = cms.double(1e-18),
    hadronFlavourHasPriority = cms.bool(False),
    jetAlgorithm = cms.string('AntiKt'),
    jets = cms.InputTag("ak4PFJetsCHS"),
    leptons = cms.InputTag("patJetPartons","leptons"),
    partons = cms.InputTag("patJetPartons","physicsPartons"),
    rParam = cms.double(0.4)
)


process.patJetFlavourAssociationLegacy = cms.EDProducer("JetFlavourIdentifier",
    physicsDefinition = cms.bool(False),
    srcByReference = cms.InputTag("patJetPartonAssociationLegacy")
)


process.patJetGenJetMatch = cms.EDProducer("GenJetMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("ak4GenJets"),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(),
    mcStatus = cms.vint32(),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak4PFJetsCHS")
)


process.patJetPartonAssociationLegacy = cms.EDProducer("JetPartonMatcher",
    coneSizeToAssociate = cms.double(0.3),
    jets = cms.InputTag("ak4PFJetsCHS"),
    partons = cms.InputTag("patJetPartonsLegacy")
)


process.patJetPartonMatch = cms.EDProducer("MCMatcher",
    checkCharge = cms.bool(False),
    matched = cms.InputTag("genParticles"),
    maxDPtRel = cms.double(3.0),
    maxDeltaR = cms.double(0.4),
    mcPdgId = cms.vint32(
        1, 2, 3, 4, 5, 
        21
    ),
    mcStatus = cms.vint32(3, 23),
    resolveAmbiguities = cms.bool(True),
    resolveByMatchQuality = cms.bool(False),
    src = cms.InputTag("ak4PFJetsCHS")
)


process.patJetPartons = cms.EDProducer("HadronAndPartonSelector",
    fullChainPhysPartons = cms.bool(True),
    particles = cms.InputTag("genParticles"),
    partonMode = cms.string('Auto'),
    src = cms.InputTag("generator")
)


process.patJetPartonsLegacy = cms.EDProducer("PartonSelector",
    src = cms.InputTag("genParticles"),
    withLeptons = cms.bool(False)
)


process.patJets = cms.EDProducer("PATJetProducer",
    JetFlavourInfoSource = cms.InputTag("patJetFlavourAssociation"),
    JetPartonMapSource = cms.InputTag("patJetFlavourAssociationLegacy"),
    addAssociatedTracks = cms.bool(True),
    addBTagInfo = cms.bool(True),
    addDiscriminators = cms.bool(True),
    addEfficiencies = cms.bool(False),
    addGenJetMatch = cms.bool(True),
    addGenPartonMatch = cms.bool(True),
    addJetCharge = cms.bool(True),
    addJetCorrFactors = cms.bool(True),
    addJetFlavourInfo = cms.bool(True),
    addJetID = cms.bool(False),
    addPartonJetMatch = cms.bool(False),
    addResolutions = cms.bool(False),
    addTagInfos = cms.bool(False),
    discriminatorSources = cms.VInputTag(
        cms.InputTag("pfJetBProbabilityBJetTags"), cms.InputTag("pfJetProbabilityBJetTags"), cms.InputTag("pfTrackCountingHighEffBJetTags"), cms.InputTag("pfSimpleSecondaryVertexHighEffBJetTags"), cms.InputTag("pfSimpleInclusiveSecondaryVertexHighEffBJetTags"), 
        cms.InputTag("pfCombinedSecondaryVertexV2BJetTags"), cms.InputTag("pfCombinedInclusiveSecondaryVertexV2BJetTags"), cms.InputTag("softPFMuonBJetTags"), cms.InputTag("softPFElectronBJetTags"), cms.InputTag("pfCombinedMVAV2BJetTags"), 
        cms.InputTag("pfCombinedCvsLJetTags"), cms.InputTag("pfCombinedCvsBJetTags"), cms.InputTag("pfDeepCSVJetTags","probb"), cms.InputTag("pfDeepCSVJetTags","probc"), cms.InputTag("pfDeepCSVJetTags","probudsg"), 
        cms.InputTag("pfDeepCSVJetTags","probbb")
    ),
    efficiencies = cms.PSet(

    ),
    embedGenJetMatch = cms.bool(True),
    embedGenPartonMatch = cms.bool(True),
    embedPFCandidates = cms.bool(False),
    genJetMatch = cms.InputTag("patJetGenJetMatch"),
    genPartonMatch = cms.InputTag("patJetPartonMatch"),
    getJetMCFlavour = cms.bool(True),
    jetChargeSource = cms.InputTag("patJetCharge"),
    jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactors")),
    jetIDMap = cms.InputTag("ak4JetID"),
    jetSource = cms.InputTag("ak4PFJetsCHS"),
    partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
    resolutions = cms.PSet(

    ),
    tagInfoSources = cms.VInputTag(),
    trackAssociationSource = cms.InputTag("ak4JetTracksAssociatorAtVertexPF"),
    useLegacyJetMCFlavour = cms.bool(False),
    userData = cms.PSet(
        userCands = cms.PSet(
            src = cms.VInputTag("")
        ),
        userClasses = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFloats = cms.PSet(
            src = cms.VInputTag("")
        ),
        userFunctionLabels = cms.vstring(),
        userFunctions = cms.vstring(),
        userInts = cms.PSet(
            src = cms.VInputTag("")
        )
    )
)


process.pfBoostedDoubleSVAK8TagInfos = cms.EDProducer("BoostedDoubleSVProducer",
    R0 = cms.double(0.8),
    beta = cms.double(1.0),
    maxSVDeltaRToJet = cms.double(0.7),
    svTagInfos = cms.InputTag("pfInclusiveSecondaryVertexFinderAK8TagInfos"),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.8),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    )
)


process.pfBoostedDoubleSVCA15TagInfos = cms.EDProducer("BoostedDoubleSVProducer",
    R0 = cms.double(1.5),
    beta = cms.double(1.0),
    maxSVDeltaRToJet = cms.double(1.0),
    svTagInfos = cms.InputTag("pfInclusiveSecondaryVertexFinderCA15TagInfos"),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(1.5),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    )
)


process.pfBoostedDoubleSecondaryVertexAK8BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateBoostedDoubleSecondaryVertexAK8Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfBoostedDoubleSVAK8TagInfos"))
)


process.pfBoostedDoubleSecondaryVertexCA15BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateBoostedDoubleSecondaryVertexCA15Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfBoostedDoubleSVCA15TagInfos"))
)


process.pfCSVscikitJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('CSVscikitTags'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"))
)


process.pfChargeBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateChargeBTagComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfCombinedCvsBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('charmTagsComputerCvsB'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfCombinedCvsLJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('charmTagsComputerCvsL'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfCombinedInclusiveSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"))
)


process.pfCombinedMVAV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateCombinedMVAV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfSecondaryVertexTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfSecondaryVertexTagInfos"))
)


process.pfDeepBoostedDiscriminatorsJetTags = cms.EDProducer("BTagProbabilityToDiscriminator",
    discriminators = cms.VPSet(
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfDeepBoostedJetTags","probTbcq"), cms.InputTag("pfDeepBoostedJetTags","probTbqq"), cms.InputTag("pfDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfDeepBoostedJetTags","probQCDc"), cms.InputTag("pfDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('TvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepBoostedJetTags","probTbcq"), cms.InputTag("pfDeepBoostedJetTags","probTbqq"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfDeepBoostedJetTags","probWcq"), cms.InputTag("pfDeepBoostedJetTags","probWqq"), cms.InputTag("pfDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfDeepBoostedJetTags","probQCDc"), cms.InputTag("pfDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('WvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepBoostedJetTags","probWcq"), cms.InputTag("pfDeepBoostedJetTags","probWqq"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfDeepBoostedJetTags","probZbb"), cms.InputTag("pfDeepBoostedJetTags","probZcc"), cms.InputTag("pfDeepBoostedJetTags","probZqq"), cms.InputTag("pfDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDcc"), 
                cms.InputTag("pfDeepBoostedJetTags","probQCDb"), cms.InputTag("pfDeepBoostedJetTags","probQCDc"), cms.InputTag("pfDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('ZvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepBoostedJetTags","probZbb"), cms.InputTag("pfDeepBoostedJetTags","probZcc"), cms.InputTag("pfDeepBoostedJetTags","probZqq"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfDeepBoostedJetTags","probZbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfDeepBoostedJetTags","probQCDb"), cms.InputTag("pfDeepBoostedJetTags","probQCDc"), 
                cms.InputTag("pfDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('ZbbvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepBoostedJetTags","probZbb"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfDeepBoostedJetTags","probHbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfDeepBoostedJetTags","probQCDb"), cms.InputTag("pfDeepBoostedJetTags","probQCDc"), 
                cms.InputTag("pfDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('HbbvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepBoostedJetTags","probHbb"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfDeepBoostedJetTags","probHqqqq"), cms.InputTag("pfDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfDeepBoostedJetTags","probQCDb"), cms.InputTag("pfDeepBoostedJetTags","probQCDc"), 
                cms.InputTag("pfDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('H4qvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepBoostedJetTags","probHqqqq"))
        )
    )
)


process.pfDeepBoostedJetTagInfos = cms.EDProducer("DeepBoostedJetTagInfoProducer",
    has_puppi_weighted_daughters = cms.bool(True),
    jet_radius = cms.double(0.8),
    jets = cms.InputTag("ak8PFJetsPuppi"),
    min_jet_pt = cms.double(150),
    min_pt_for_track_properties = cms.double(-1),
    puppi_value_map = cms.InputTag("puppi"),
    secondary_vertices = cms.InputTag("inclusiveCandidateSecondaryVertices"),
    vertex_associator = cms.InputTag("primaryVertexAssociation","original"),
    vertices = cms.InputTag("offlinePrimaryVertices")
)


process.pfDeepBoostedJetTags = cms.EDProducer("DeepBoostedJetTagsProducer",
    debugMode = cms.untracked.bool(False),
    flav_names = cms.vstring(
        'probTbcq', 
        'probTbqq', 
        'probTbc', 
        'probTbq', 
        'probWcq', 
        'probWqq', 
        'probZbb', 
        'probZcc', 
        'probZqq', 
        'probHbb', 
        'probHcc', 
        'probHqqqq', 
        'probQCDbb', 
        'probQCDcc', 
        'probQCDb', 
        'probQCDc', 
        'probQCDothers'
    ),
    model_path = cms.FileInPath('RecoBTag/Combined/data/DeepBoostedJet/V01/full/resnet-symbol.json'),
    param_path = cms.FileInPath('RecoBTag/Combined/data/DeepBoostedJet/V01/full/resnet-0000.params'),
    preprocessParams = cms.PSet(
        input_names = cms.vstring(
            'pfcand', 
            'sv'
        ),
        pfcand = cms.PSet(
            input_shape = cms.vuint32(1, 42, 100, 1),
            var_infos = cms.PSet(
                pfcand_VTX_ass = cms.PSet(
                    median = cms.double(7.0),
                    upper = cms.double(7.0)
                ),
                pfcand_abseta = cms.PSet(
                    median = cms.double(0.599505603313),
                    upper = cms.double(1.21494185925)
                ),
                pfcand_btagEtaRel = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(3.23048327446)
                ),
                pfcand_btagJetDistVal = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_btagPParRatio = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.997295975685)
                ),
                pfcand_btagPtRatio = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.174372568727)
                ),
                pfcand_btagSip2dSig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.565274050236)
                ),
                pfcand_btagSip2dVal = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00165283482056)
                ),
                pfcand_btagSip3dSig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.03450630188)
                ),
                pfcand_btagSip3dVal = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00417172765359)
                ),
                pfcand_charge = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.0)
                ),
                pfcand_deltaR = cms.PSet(
                    median = cms.double(0.22575956583),
                    upper = cms.double(0.488191870451)
                ),
                pfcand_detadeta = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(5.08303287461e-07)
                ),
                pfcand_dlambdadz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_dphidphi = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(7.63271316373e-07)
                ),
                pfcand_dphidxy = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_dptdpt = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(6.11870564171e-06)
                ),
                pfcand_drminsv = cms.PSet(
                    median = cms.double(0.177426457405),
                    upper = cms.double(0.555181086063)
                ),
                pfcand_drsubjet1 = cms.PSet(
                    median = cms.double(0.231124095619),
                    upper = cms.double(0.549522156715)
                ),
                pfcand_drsubjet2 = cms.PSet(
                    median = cms.double(0.263272643089),
                    upper = cms.double(0.605471189022)
                ),
                pfcand_dxy = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00254638679326)
                ),
                pfcand_dxydxy = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(2.14965821215e-05)
                ),
                pfcand_dxydz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.31130221348e-07)
                ),
                pfcand_dxysig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.496566288471)
                ),
                pfcand_dz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00448730448261)
                ),
                pfcand_dzdz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(3.40332044289e-05)
                ),
                pfcand_dzsig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.596591930389)
                ),
                pfcand_erel_log = cms.PSet(
                    median = cms.double(-5.38983869553),
                    upper = cms.double(-3.53490426064)
                ),
                pfcand_etarel = cms.PSet(
                    median = cms.double(-0.0054658302106),
                    upper = cms.double(0.174858552814)
                ),
                pfcand_hcalFrac = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_isChargedHad = cms.PSet(
                    median = cms.double(1.0),
                    upper = cms.double(1.0)
                ),
                pfcand_isEl = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_isGamma = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.0)
                ),
                pfcand_isMu = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_isNeutralHad = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_lostInnerHits = cms.PSet(
                    median = cms.double(-1.0),
                    upper = cms.double(-1.0)
                ),
                pfcand_normchi2 = cms.PSet(
                    median = cms.double(999.0),
                    upper = cms.double(999.0)
                ),
                pfcand_phirel = cms.PSet(
                    median = cms.double(-5.10289683007e-05),
                    upper = cms.double(0.215602903366)
                ),
                pfcand_pt_log = cms.PSet(
                    median = cms.double(1.09469842911),
                    upper = cms.double(3.02194809914)
                ),
                pfcand_ptrel_log = cms.PSet(
                    median = cms.double(-5.38205528259),
                    upper = cms.double(-3.52304198265)
                ),
                pfcand_puppiw = cms.PSet(
                    median = cms.double(1.0),
                    upper = cms.double(1.0)
                ),
                pfcand_quality = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(5.0)
                )
            ),
            var_length = cms.uint32(100),
            var_names = cms.vstring(
                'pfcand_pt_log', 
                'pfcand_ptrel_log', 
                'pfcand_erel_log', 
                'pfcand_phirel', 
                'pfcand_etarel', 
                'pfcand_deltaR', 
                'pfcand_abseta', 
                'pfcand_puppiw', 
                'pfcand_drminsv', 
                'pfcand_drsubjet1', 
                'pfcand_drsubjet2', 
                'pfcand_charge', 
                'pfcand_isMu', 
                'pfcand_isEl', 
                'pfcand_isChargedHad', 
                'pfcand_isGamma', 
                'pfcand_isNeutralHad', 
                'pfcand_hcalFrac', 
                'pfcand_VTX_ass', 
                'pfcand_lostInnerHits', 
                'pfcand_normchi2', 
                'pfcand_quality', 
                'pfcand_dz', 
                'pfcand_dzsig', 
                'pfcand_dxy', 
                'pfcand_dxysig', 
                'pfcand_dptdpt', 
                'pfcand_detadeta', 
                'pfcand_dphidphi', 
                'pfcand_dxydxy', 
                'pfcand_dzdz', 
                'pfcand_dxydz', 
                'pfcand_dphidxy', 
                'pfcand_dlambdadz', 
                'pfcand_btagEtaRel', 
                'pfcand_btagPtRatio', 
                'pfcand_btagPParRatio', 
                'pfcand_btagSip2dVal', 
                'pfcand_btagSip2dSig', 
                'pfcand_btagSip3dVal', 
                'pfcand_btagSip3dSig', 
                'pfcand_btagJetDistVal'
            )
        ),
        sv = cms.PSet(
            input_shape = cms.vuint32(1, 15, 7, 1),
            var_infos = cms.PSet(
                sv_abseta = cms.PSet(
                    median = cms.double(0.579698801041),
                    upper = cms.double(1.2257443285)
                ),
                sv_costhetasvpv = cms.PSet(
                    median = cms.double(0.999744534492),
                    upper = cms.double(0.999992311001)
                ),
                sv_d3d = cms.PSet(
                    median = cms.double(0.496477723122),
                    upper = cms.double(4.83165483475)
                ),
                sv_d3dsig = cms.PSet(
                    median = cms.double(6.50515079498),
                    upper = cms.double(36.9069334412)
                ),
                sv_deltaR = cms.PSet(
                    median = cms.double(0.105607174337),
                    upper = cms.double(0.323846782446)
                ),
                sv_dxy = cms.PSet(
                    median = cms.double(0.369336694479),
                    upper = cms.double(3.97735537529)
                ),
                sv_dxysig = cms.PSet(
                    median = cms.double(6.49603271484),
                    upper = cms.double(36.8943783569)
                ),
                sv_erel_log = cms.PSet(
                    median = cms.double(-2.77275466919),
                    upper = cms.double(-1.7486346817)
                ),
                sv_etarel = cms.PSet(
                    median = cms.double(-0.00318800867535),
                    upper = cms.double(0.0951088288426)
                ),
                sv_mass = cms.PSet(
                    median = cms.double(1.36728298664),
                    upper = cms.double(4.75960615158)
                ),
                sv_normchi2 = cms.PSet(
                    median = cms.double(0.796081960201),
                    upper = cms.double(2.15187430382)
                ),
                sv_ntracks = cms.PSet(
                    median = cms.double(3.0),
                    upper = cms.double(5.0)
                ),
                sv_phirel = cms.PSet(
                    median = cms.double(0.000510219600983),
                    upper = cms.double(0.110185634494)
                ),
                sv_pt_log = cms.PSet(
                    median = cms.double(3.77797603607),
                    upper = cms.double(4.90166530609)
                ),
                sv_ptrel_log = cms.PSet(
                    median = cms.double(-2.7622461319),
                    upper = cms.double(-1.73727185726)
                )
            ),
            var_length = cms.uint32(7),
            var_names = cms.vstring(
                'sv_pt_log', 
                'sv_ptrel_log', 
                'sv_erel_log', 
                'sv_phirel', 
                'sv_etarel', 
                'sv_deltaR', 
                'sv_abseta', 
                'sv_mass', 
                'sv_ntracks', 
                'sv_normchi2', 
                'sv_dxy', 
                'sv_dxysig', 
                'sv_d3d', 
                'sv_d3dsig', 
                'sv_costhetasvpv'
            )
        )
    ),
    src = cms.InputTag("pfDeepBoostedJetTagInfos")
)


process.pfDeepCMVADiscriminatorsJetTags = cms.EDProducer("BTagProbabilityToDiscriminator",
    discriminators = cms.VPSet(
        cms.PSet(
            denominator = cms.VInputTag(),
            name = cms.string('BvsAll'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepCMVAJetTags","probb"), cms.InputTag("pfDeepCMVAJetTags","probbb"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(cms.InputTag("pfDeepCMVAJetTags","probc"), cms.InputTag("pfDeepCMVAJetTags","probb"), cms.InputTag("pfDeepCMVAJetTags","probbb")),
            name = cms.string('CvsB'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepCMVAJetTags","probc"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(cms.InputTag("pfDeepCMVAJetTags","probc"), cms.InputTag("pfDeepCMVAJetTags","probudsg")),
            name = cms.string('CvsL'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepCMVAJetTags","probc"))
        )
    )
)


process.pfDeepCMVAJetTags = cms.EDProducer("DeepFlavourJetTagsProducer",
    NNConfig = cms.FileInPath('RecoBTag/Combined/data/Model_DeepCMVA.json'),
    checkSVForDefaults = cms.bool(False),
    meanPadding = cms.bool(False),
    src = cms.InputTag("pfDeepCMVATagInfos"),
    toAdd = cms.PSet(

    )
)


process.pfDeepCMVANegativeTagInfos = cms.EDProducer("DeepCMVATagInfoProducer",
    cMVAPtThreshold = cms.double(200),
    deepNNTagInfos = cms.InputTag("pfDeepCSVNegativeTagInfos"),
    elInfoSrc = cms.InputTag("softPFElectronsTagInfos"),
    ipInfoSrc = cms.InputTag("pfImpactParameterTagInfos"),
    jpComputerSrc = cms.string('candidateJetProbabilityComputer'),
    jpbComputerSrc = cms.string('candidateJetBProbabilityComputer'),
    muInfoSrc = cms.InputTag("softPFMuonsTagInfos"),
    softelComputerSrc = cms.string('softPFElectronComputer'),
    softmuComputerSrc = cms.string('softPFMuonComputer')
)


process.pfDeepCMVAPositiveTagInfos = cms.EDProducer("DeepCMVATagInfoProducer",
    cMVAPtThreshold = cms.double(200),
    deepNNTagInfos = cms.InputTag("pfDeepCSVPositiveTagInfos"),
    elInfoSrc = cms.InputTag("softPFElectronsTagInfos"),
    ipInfoSrc = cms.InputTag("pfImpactParameterTagInfos"),
    jpComputerSrc = cms.string('candidateJetProbabilityComputer'),
    jpbComputerSrc = cms.string('candidateJetBProbabilityComputer'),
    muInfoSrc = cms.InputTag("softPFMuonsTagInfos"),
    softelComputerSrc = cms.string('softPFElectronComputer'),
    softmuComputerSrc = cms.string('softPFMuonComputer')
)


process.pfDeepCMVATagInfos = cms.EDProducer("DeepCMVATagInfoProducer",
    cMVAPtThreshold = cms.double(200),
    deepNNTagInfos = cms.InputTag("pfDeepCSVTagInfos"),
    elInfoSrc = cms.InputTag("softPFElectronsTagInfos"),
    ipInfoSrc = cms.InputTag("pfImpactParameterTagInfos"),
    jpComputerSrc = cms.string('candidateJetProbabilityComputer'),
    jpbComputerSrc = cms.string('candidateJetBProbabilityComputer'),
    muInfoSrc = cms.InputTag("softPFMuonsTagInfos"),
    softelComputerSrc = cms.string('softPFElectronComputer'),
    softmuComputerSrc = cms.string('softPFMuonComputer')
)


process.pfDeepCSVDiscriminatorsJetTags = cms.EDProducer("BTagProbabilityToDiscriminator",
    discriminators = cms.VPSet(
        cms.PSet(
            denominator = cms.VInputTag(),
            name = cms.string('BvsAll'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepCSVJetTags","probb"), cms.InputTag("pfDeepCSVJetTags","probbb"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(cms.InputTag("pfDeepCSVJetTags","probc"), cms.InputTag("pfDeepCSVJetTags","probb"), cms.InputTag("pfDeepCSVJetTags","probbb")),
            name = cms.string('CvsB'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepCSVJetTags","probc"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(cms.InputTag("pfDeepCSVJetTags","probudsg"), cms.InputTag("pfDeepCSVJetTags","probc")),
            name = cms.string('CvsL'),
            numerator = cms.VInputTag(cms.InputTag("pfDeepCSVJetTags","probc"))
        )
    )
)


process.pfDeepCSVJetTags = cms.EDProducer("DeepFlavourJetTagsProducer",
    NNConfig = cms.FileInPath('RecoBTag/Combined/data/DeepFlavourNoSL.json'),
    checkSVForDefaults = cms.bool(False),
    meanPadding = cms.bool(False),
    src = cms.InputTag("pfDeepCSVTagInfos"),
    toAdd = cms.PSet(
        probcc = cms.string('probc')
    )
)


process.pfDeepCSVNegativeTagInfos = cms.EDProducer("DeepNNTagInfoProducer",
    computer = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(True),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        trackFlip = cms.bool(True),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(-2.0),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(10.0),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(10.0),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(True)
    ),
    svTagInfos = cms.InputTag("pfInclusiveSecondaryVertexFinderNegativeTagInfos")
)


process.pfDeepCSVPositiveTagInfos = cms.EDProducer("DeepNNTagInfoProducer",
    computer = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(True),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        trackFlip = cms.bool(False),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(2.0),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(0),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(0),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(False)
    ),
    svTagInfos = cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos")
)


process.pfDeepCSVTagInfos = cms.EDProducer("DeepNNTagInfoProducer",
    computer = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(True),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        trackFlip = cms.bool(False),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(2.0),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(False)
    ),
    svTagInfos = cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos")
)


process.pfDeepDoubleBJetTags = cms.EDProducer("DeepDoubleBTFJetTagsProducer",
    batch_eval = cms.bool(False),
    flav_table = cms.PSet(
        probH = cms.vuint32(1),
        probQ = cms.vuint32(0)
    ),
    graph_path = cms.FileInPath('RecoBTag/Combined/data/DeepDoubleB/V01/constant_graph_PtCut_MassSculptPen.pb'),
    input_names = cms.vstring(
        'input_1', 
        'input_2', 
        'input_3'
    ),
    lp_names = cms.vstring('db_input_batchnorm/keras_learning_phase'),
    nThreads = cms.uint32(1),
    output_names = cms.vstring('ID_pred/Softmax'),
    singleThreadPool = cms.string('no_threads'),
    src = cms.InputTag("pfDeepDoubleBTagInfos")
)


process.pfDeepDoubleBTagInfos = cms.EDProducer("DeepDoubleBTagInfoProducer",
    jet_radius = cms.double(0.8),
    jets = cms.InputTag("ak8PFJetsCHS"),
    min_candidate_pt = cms.double(0.95),
    secondary_vertices = cms.InputTag("inclusiveCandidateSecondaryVertices"),
    shallow_tag_infos = cms.InputTag("pfBoostedDoubleSVAK8TagInfos"),
    vertices = cms.InputTag("offlinePrimaryVertices")
)


process.pfDeepFlavourJetTags = cms.EDProducer("DeepFlavourTFJetTagsProducer",
    batch_eval = cms.bool(False),
    flav_table = cms.PSet(
        probb = cms.vuint32(0),
        probbb = cms.vuint32(1),
        probc = cms.vuint32(3),
        probg = cms.vuint32(5),
        problepb = cms.vuint32(2),
        probuds = cms.vuint32(4)
    ),
    graph_path = cms.FileInPath('RecoBTag/Combined/data/DeepFlavourV03_10X_training/constant_graph.pb'),
    input_names = cms.vstring(
        'input_1', 
        'input_2', 
        'input_3', 
        'input_4', 
        'input_5'
    ),
    lp_names = cms.vstring('cpf_input_batchnorm/keras_learning_phase'),
    nThreads = cms.uint32(1),
    output_names = cms.vstring(
        'ID_pred/Softmax', 
        'regression_pred/BiasAdd'
    ),
    singleThreadPool = cms.string('no_threads'),
    src = cms.InputTag("pfDeepFlavourTagInfos")
)


process.pfDeepFlavourTagInfos = cms.EDProducer("DeepFlavourTagInfoProducer",
    fallback_puppi_weight = cms.bool(False),
    fallback_vertex_association = cms.bool(False),
    flip = cms.bool(False),
    jet_radius = cms.double(0.4),
    jets = cms.InputTag("ak4PFJetsCHS"),
    min_candidate_pt = cms.double(0.95),
    puppi_value_map = cms.InputTag("puppi"),
    secondary_vertices = cms.InputTag("inclusiveCandidateSecondaryVertices"),
    shallow_tag_infos = cms.InputTag("pfDeepCSVTagInfos"),
    vertex_associator = cms.InputTag("primaryVertexAssociation","original"),
    vertices = cms.InputTag("offlinePrimaryVertices")
)


process.pfGhostTrackBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateGhostTrackComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfGhostTrackVertexTagInfos"))
)


process.pfGhostTrackVertexTagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(1),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('gtvr'),
        fitType = cms.string('RefitGhostTrackWithVertices'),
        maxFitChi2 = cms.double(10.0),
        mergeThreshold = cms.double(3.0),
        primcut = cms.double(2.0),
        seccut = cms.double(4.0)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfImpactParameterAK8TagInfos = cms.EDProducer("CandIPProducer",
    candidates = cms.InputTag("particleFlow"),
    computeGhostTrack = cms.bool(False),
    computeProbabilities = cms.bool(False),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jets = cms.InputTag("ak8PFJetsCHS"),
    maxDeltaR = cms.double(0.8),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(0),
    minimumNumberOfPixelHits = cms.int32(1),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.pfImpactParameterCA15TagInfos = cms.EDProducer("CandIPProducer",
    candidates = cms.InputTag("particleFlow"),
    computeGhostTrack = cms.bool(False),
    computeProbabilities = cms.bool(False),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jets = cms.InputTag("ca15PFJetsCHS"),
    maxDeltaR = cms.double(1.5),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(0),
    minimumNumberOfPixelHits = cms.int32(1),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.pfImpactParameterTagInfos = cms.EDProducer("CandIPProducer",
    candidates = cms.InputTag("particleFlow"),
    computeGhostTrack = cms.bool(True),
    computeProbabilities = cms.bool(True),
    ghostTrackPriorDeltaR = cms.double(0.03),
    jetDirectionUsingGhostTrack = cms.bool(False),
    jetDirectionUsingTracks = cms.bool(False),
    jets = cms.InputTag("ak4PFJetsCHS"),
    maxDeltaR = cms.double(0.4),
    maximumChiSquared = cms.double(5.0),
    maximumLongitudinalImpactParameter = cms.double(17.0),
    maximumTransverseImpactParameter = cms.double(0.2),
    minimumNumberOfHits = cms.int32(0),
    minimumNumberOfPixelHits = cms.int32(1),
    minimumTransverseMomentum = cms.double(1.0),
    primaryVertex = cms.InputTag("offlinePrimaryVertices"),
    useTrackQuality = cms.bool(False)
)


process.pfInclusiveSecondaryVertexFinderAK8TagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveCandidateSecondaryVertices"),
    extSVDeltaRToJet = cms.double(0.8),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterAK8TagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.8),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(2.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.8),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfInclusiveSecondaryVertexFinderCA15TagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveCandidateSecondaryVertices"),
    extSVDeltaRToJet = cms.double(1.5),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterCA15TagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(1.5),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(2.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(1.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfInclusiveSecondaryVertexFinderCvsLTagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveCandidateSecondaryVerticesCvsL"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(1.5),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfInclusiveSecondaryVertexFinderNegativeCvsLTagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveCandidateSecondaryVerticesCvsL"),
    extSVDeltaRToJet = cms.double(-0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-1.5),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfInclusiveSecondaryVertexFinderNegativeTagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveCandidateNegativeSecondaryVertices"),
    extSVDeltaRToJet = cms.double(-0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-2.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfInclusiveSecondaryVertexFinderTagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("inclusiveCandidateSecondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(True),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(2.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.79),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateJetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateJetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags = cms.EDProducer("BTagProbabilityToDiscriminator",
    discriminators = cms.VPSet(
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probTbcq"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probTbqq"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('TvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probTbcq"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probTbqq"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probWcq"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probWqq"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('WvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probWcq"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probWqq"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('ZHbbvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHbb"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('ZHccvsQCD'),
            numerator = cms.VInputTag(cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHcc"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('bbvsLight'),
            numerator = cms.VInputTag(cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"))
        ), 
        cms.PSet(
            denominator = cms.VInputTag(
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDbb"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDb"), 
                cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDothers")
            ),
            name = cms.string('ccvsLight'),
            numerator = cms.VInputTag(cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probZcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probHcc"), cms.InputTag("pfMassDecorrelatedDeepBoostedJetTags","probQCDcc"))
        )
    )
)


process.pfMassDecorrelatedDeepBoostedJetTags = cms.EDProducer("DeepBoostedJetTagsProducer",
    debugMode = cms.untracked.bool(False),
    flav_names = cms.vstring(
        'probTbcq', 
        'probTbqq', 
        'probTbc', 
        'probTbq', 
        'probWcq', 
        'probWqq', 
        'probZbb', 
        'probZcc', 
        'probZqq', 
        'probHbb', 
        'probHcc', 
        'probHqqqq', 
        'probQCDbb', 
        'probQCDcc', 
        'probQCDb', 
        'probQCDc', 
        'probQCDothers'
    ),
    model_path = cms.FileInPath('RecoBTag/Combined/data/DeepBoostedJet/V01/decorrelated/resnet-symbol.json'),
    param_path = cms.FileInPath('RecoBTag/Combined/data/DeepBoostedJet/V01/decorrelated/resnet-0000.params'),
    preprocessParams = cms.PSet(
        input_names = cms.vstring(
            'pfcand', 
            'sv'
        ),
        pfcand = cms.PSet(
            input_shape = cms.vuint32(1, 42, 100, 1),
            var_infos = cms.PSet(
                pfcand_VTX_ass = cms.PSet(
                    median = cms.double(7.0),
                    upper = cms.double(7.0)
                ),
                pfcand_abseta = cms.PSet(
                    median = cms.double(0.599505603313),
                    upper = cms.double(1.21494185925)
                ),
                pfcand_btagEtaRel = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(3.23048327446)
                ),
                pfcand_btagJetDistVal = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_btagPParRatio = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.997295975685)
                ),
                pfcand_btagPtRatio = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.174372568727)
                ),
                pfcand_btagSip2dSig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.565274050236)
                ),
                pfcand_btagSip2dVal = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00165283482056)
                ),
                pfcand_btagSip3dSig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.03450630188)
                ),
                pfcand_btagSip3dVal = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00417172765359)
                ),
                pfcand_charge = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.0)
                ),
                pfcand_deltaR = cms.PSet(
                    median = cms.double(0.22575956583),
                    upper = cms.double(0.488191870451)
                ),
                pfcand_detadeta = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(5.08303287461e-07)
                ),
                pfcand_dlambdadz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_dphidphi = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(7.63271316373e-07)
                ),
                pfcand_dphidxy = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_dptdpt = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(6.11870564171e-06)
                ),
                pfcand_drminsv = cms.PSet(
                    median = cms.double(0.177426457405),
                    upper = cms.double(0.555181086063)
                ),
                pfcand_drsubjet1 = cms.PSet(
                    median = cms.double(0.231124095619),
                    upper = cms.double(0.549522156715)
                ),
                pfcand_drsubjet2 = cms.PSet(
                    median = cms.double(0.263272643089),
                    upper = cms.double(0.605471189022)
                ),
                pfcand_dxy = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00254638679326)
                ),
                pfcand_dxydxy = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(2.14965821215e-05)
                ),
                pfcand_dxydz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.31130221348e-07)
                ),
                pfcand_dxysig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.496566288471)
                ),
                pfcand_dz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.00448730448261)
                ),
                pfcand_dzdz = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(3.40332044289e-05)
                ),
                pfcand_dzsig = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.596591930389)
                ),
                pfcand_erel_log = cms.PSet(
                    median = cms.double(-5.38983869553),
                    upper = cms.double(-3.53490426064)
                ),
                pfcand_etarel = cms.PSet(
                    median = cms.double(-0.0054658302106),
                    upper = cms.double(0.174858552814)
                ),
                pfcand_hcalFrac = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_isChargedHad = cms.PSet(
                    median = cms.double(1.0),
                    upper = cms.double(1.0)
                ),
                pfcand_isEl = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_isGamma = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(1.0)
                ),
                pfcand_isMu = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_isNeutralHad = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(0.0)
                ),
                pfcand_lostInnerHits = cms.PSet(
                    median = cms.double(-1.0),
                    upper = cms.double(-1.0)
                ),
                pfcand_normchi2 = cms.PSet(
                    median = cms.double(999.0),
                    upper = cms.double(999.0)
                ),
                pfcand_phirel = cms.PSet(
                    median = cms.double(-5.10289683007e-05),
                    upper = cms.double(0.215602903366)
                ),
                pfcand_pt_log = cms.PSet(
                    median = cms.double(1.09469842911),
                    upper = cms.double(3.02194809914)
                ),
                pfcand_ptrel_log = cms.PSet(
                    median = cms.double(-5.38205528259),
                    upper = cms.double(-3.52304198265)
                ),
                pfcand_puppiw = cms.PSet(
                    median = cms.double(1.0),
                    upper = cms.double(1.0)
                ),
                pfcand_quality = cms.PSet(
                    median = cms.double(0.0),
                    upper = cms.double(5.0)
                )
            ),
            var_length = cms.uint32(100),
            var_names = cms.vstring(
                'pfcand_pt_log', 
                'pfcand_ptrel_log', 
                'pfcand_erel_log', 
                'pfcand_phirel', 
                'pfcand_etarel', 
                'pfcand_deltaR', 
                'pfcand_abseta', 
                'pfcand_puppiw', 
                'pfcand_drminsv', 
                'pfcand_drsubjet1', 
                'pfcand_drsubjet2', 
                'pfcand_charge', 
                'pfcand_isMu', 
                'pfcand_isEl', 
                'pfcand_isChargedHad', 
                'pfcand_isGamma', 
                'pfcand_isNeutralHad', 
                'pfcand_hcalFrac', 
                'pfcand_VTX_ass', 
                'pfcand_lostInnerHits', 
                'pfcand_normchi2', 
                'pfcand_quality', 
                'pfcand_dz', 
                'pfcand_dzsig', 
                'pfcand_dxy', 
                'pfcand_dxysig', 
                'pfcand_dptdpt', 
                'pfcand_detadeta', 
                'pfcand_dphidphi', 
                'pfcand_dxydxy', 
                'pfcand_dzdz', 
                'pfcand_dxydz', 
                'pfcand_dphidxy', 
                'pfcand_dlambdadz', 
                'pfcand_btagEtaRel', 
                'pfcand_btagPtRatio', 
                'pfcand_btagPParRatio', 
                'pfcand_btagSip2dVal', 
                'pfcand_btagSip2dSig', 
                'pfcand_btagSip3dVal', 
                'pfcand_btagSip3dSig', 
                'pfcand_btagJetDistVal'
            )
        ),
        sv = cms.PSet(
            input_shape = cms.vuint32(1, 15, 7, 1),
            var_infos = cms.PSet(
                sv_abseta = cms.PSet(
                    median = cms.double(0.579698801041),
                    upper = cms.double(1.2257443285)
                ),
                sv_costhetasvpv = cms.PSet(
                    median = cms.double(0.999744534492),
                    upper = cms.double(0.999992311001)
                ),
                sv_d3d = cms.PSet(
                    median = cms.double(0.496477723122),
                    upper = cms.double(4.83165483475)
                ),
                sv_d3dsig = cms.PSet(
                    median = cms.double(6.50515079498),
                    upper = cms.double(36.9069334412)
                ),
                sv_deltaR = cms.PSet(
                    median = cms.double(0.105607174337),
                    upper = cms.double(0.323846782446)
                ),
                sv_dxy = cms.PSet(
                    median = cms.double(0.369336694479),
                    upper = cms.double(3.97735537529)
                ),
                sv_dxysig = cms.PSet(
                    median = cms.double(6.49603271484),
                    upper = cms.double(36.8943783569)
                ),
                sv_erel_log = cms.PSet(
                    median = cms.double(-2.77275466919),
                    upper = cms.double(-1.7486346817)
                ),
                sv_etarel = cms.PSet(
                    median = cms.double(-0.00318800867535),
                    upper = cms.double(0.0951088288426)
                ),
                sv_mass = cms.PSet(
                    median = cms.double(1.36728298664),
                    upper = cms.double(4.75960615158)
                ),
                sv_normchi2 = cms.PSet(
                    median = cms.double(0.796081960201),
                    upper = cms.double(2.15187430382)
                ),
                sv_ntracks = cms.PSet(
                    median = cms.double(3.0),
                    upper = cms.double(5.0)
                ),
                sv_phirel = cms.PSet(
                    median = cms.double(0.000510219600983),
                    upper = cms.double(0.110185634494)
                ),
                sv_pt_log = cms.PSet(
                    median = cms.double(3.77797603607),
                    upper = cms.double(4.90166530609)
                ),
                sv_ptrel_log = cms.PSet(
                    median = cms.double(-2.7622461319),
                    upper = cms.double(-1.73727185726)
                )
            ),
            var_length = cms.uint32(7),
            var_names = cms.vstring(
                'sv_pt_log', 
                'sv_ptrel_log', 
                'sv_erel_log', 
                'sv_phirel', 
                'sv_etarel', 
                'sv_deltaR', 
                'sv_abseta', 
                'sv_mass', 
                'sv_ntracks', 
                'sv_normchi2', 
                'sv_dxy', 
                'sv_dxysig', 
                'sv_d3d', 
                'sv_d3dsig', 
                'sv_costhetasvpv'
            )
        )
    ),
    src = cms.InputTag("pfDeepBoostedJetTagInfos")
)


process.pfNegativeCombinedCvsBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('charmTagsNegativeComputerCvsB'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderNegativeCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfNegativeCombinedCvsLJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('charmTagsNegativeComputerCvsL'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderNegativeCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfNegativeCombinedInclusiveSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateNegativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderNegativeTagInfos"))
)


process.pfNegativeCombinedMVAV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateNegativeCombinedMVAV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfSecondaryVertexNegativeTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderNegativeTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfNegativeCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateNegativeCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfSecondaryVertexNegativeTagInfos"))
)


process.pfNegativeDeepCMVAJetTags = cms.EDProducer("DeepFlavourJetTagsProducer",
    NNConfig = cms.FileInPath('RecoBTag/Combined/data/Model_DeepCMVA.json'),
    checkSVForDefaults = cms.bool(False),
    meanPadding = cms.bool(False),
    src = cms.InputTag("pfDeepCMVANegativeTagInfos"),
    toAdd = cms.PSet(

    )
)


process.pfNegativeDeepCSVJetTags = cms.EDProducer("DeepFlavourJetTagsProducer",
    NNConfig = cms.FileInPath('RecoBTag/Combined/data/DeepFlavourNoSL.json'),
    checkSVForDefaults = cms.bool(False),
    meanPadding = cms.bool(False),
    src = cms.InputTag("pfDeepCSVNegativeTagInfos"),
    toAdd = cms.PSet(
        probcc = cms.string('probc')
    )
)


process.pfNegativeDeepFlavourJetTags = cms.EDProducer("DeepFlavourTFJetTagsProducer",
    batch_eval = cms.bool(False),
    flav_table = cms.PSet(
        probb = cms.vuint32(0),
        probbb = cms.vuint32(1),
        probc = cms.vuint32(3),
        probg = cms.vuint32(5),
        problepb = cms.vuint32(2),
        probuds = cms.vuint32(4)
    ),
    graph_path = cms.FileInPath('RecoBTag/Combined/data/DeepFlavourV03_10X_training/constant_graph.pb'),
    input_names = cms.vstring(
        'input_1', 
        'input_2', 
        'input_3', 
        'input_4', 
        'input_5'
    ),
    lp_names = cms.vstring('cpf_input_batchnorm/keras_learning_phase'),
    nThreads = cms.uint32(1),
    output_names = cms.vstring(
        'ID_pred/Softmax', 
        'regression_pred/BiasAdd'
    ),
    singleThreadPool = cms.string('no_threads'),
    src = cms.InputTag("pfNegativeDeepFlavourTagInfos")
)


process.pfNegativeDeepFlavourTagInfos = cms.EDProducer("DeepFlavourTagInfoProducer",
    fallback_puppi_weight = cms.bool(False),
    fallback_vertex_association = cms.bool(False),
    flip = cms.bool(True),
    jet_radius = cms.double(0.4),
    jets = cms.InputTag("ak4PFJetsCHS"),
    min_candidate_pt = cms.double(0.95),
    puppi_value_map = cms.InputTag("puppi"),
    secondary_vertices = cms.InputTag("inclusiveCandidateNegativeSecondaryVertices"),
    shallow_tag_infos = cms.InputTag("pfDeepCSVNegativeTagInfos"),
    vertex_associator = cms.InputTag("primaryVertexAssociation","original"),
    vertices = cms.InputTag("offlinePrimaryVertices")
)


process.pfNegativeOnlyJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateNegativeOnlyJetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfNegativeOnlyJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateNegativeOnlyJetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfNegativeSimpleInclusiveSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfInclusiveSecondaryVertexFinderNegativeTagInfos"))
)


process.pfNegativeSimpleInclusiveSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfInclusiveSecondaryVertexFinderNegativeTagInfos"))
)


process.pfNegativeSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfSecondaryVertexNegativeTagInfos"))
)


process.pfNegativeSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfSecondaryVertexNegativeTagInfos"))
)


process.pfNegativeTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateNegativeTrackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfNegativeTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateNegativeTrackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfPositiveCombinedCvsBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('charmTagsPositiveComputerCvsB'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfPositiveCombinedCvsLJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('charmTagsPositiveComputerCvsL'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfPositiveCombinedInclusiveSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidatePositiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"))
)


process.pfPositiveCombinedMVAV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidatePositiveCombinedMVAV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfSecondaryVertexTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.pfPositiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidatePositiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfSecondaryVertexTagInfos"))
)


process.pfPositiveDeepCMVAJetTags = cms.EDProducer("DeepFlavourJetTagsProducer",
    NNConfig = cms.FileInPath('RecoBTag/Combined/data/Model_DeepCMVA.json'),
    checkSVForDefaults = cms.bool(False),
    meanPadding = cms.bool(False),
    src = cms.InputTag("pfDeepCMVAPositiveTagInfos"),
    toAdd = cms.PSet(

    )
)


process.pfPositiveDeepCSVJetTags = cms.EDProducer("DeepFlavourJetTagsProducer",
    NNConfig = cms.FileInPath('RecoBTag/Combined/data/DeepFlavourNoSL.json'),
    checkSVForDefaults = cms.bool(False),
    meanPadding = cms.bool(False),
    src = cms.InputTag("pfDeepCSVPositiveTagInfos"),
    toAdd = cms.PSet(
        probcc = cms.string('probc')
    )
)


process.pfPositiveOnlyJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidatePositiveOnlyJetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfPositiveOnlyJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidatePositiveOnlyJetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfSecondaryVertexNegativeTagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfSecondaryVertexTagInfos = cms.EDProducer("CandSecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("pfImpactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(1),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.pfSimpleInclusiveSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"))
)


process.pfSimpleInclusiveSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos"))
)


process.pfSimpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfSecondaryVertexTagInfos"))
)


process.pfSimpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateSimpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfSecondaryVertexTagInfos"))
)


process.pfTrackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateTrackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfTrackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('candidateTrackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"))
)


process.pfcandCleanerPt4Eta2 = cms.EDProducer("HiPFCandCleaner",
    pfAbsEtaMax = cms.double(2.0),
    pfCandidateLabel = cms.InputTag("particleFlow"),
    pfPtMin = cms.double(4.0)
)


process.positiveCombinedInclusiveSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("inclusiveSecondaryVertexFinderTagInfos"))
)


process.positiveCombinedMVAV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedMVAV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("secondaryVertexPositiveTagInfos"), cms.InputTag("inclusiveSecondaryVertexFinderPositiveTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos"))
)


process.positiveCombinedSecondaryVertexV2BJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveCombinedSecondaryVertexV2Computer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"), cms.InputTag("secondaryVertexTagInfos"))
)


process.positiveOnlyJetBProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveOnlyJetBProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.positiveOnlyJetProbabilityBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveOnlyJetProbabilityComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.positiveSoftPFElectronBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFElectronComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.positiveSoftPFElectronByIP2dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFElectronByIP2dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.positiveSoftPFElectronByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFElectronByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.positiveSoftPFElectronByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFElectronByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.positiveSoftPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.positiveSoftPFMuonByIP2dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByIP2dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.positiveSoftPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.positiveSoftPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('positiveSoftPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.primaryVertexAssociation = cms.EDProducer("PFCandidatePrimaryVertexSorter",
    assignment = cms.PSet(
        maxDistanceToJetAxis = cms.double(0.07),
        maxDtSigForPrimaryAssignment = cms.double(3.0),
        maxDxyForJetAxisAssigment = cms.double(0.1),
        maxDxyForNotReconstructedPrimary = cms.double(0.01),
        maxDxySigForNotReconstructedPrimary = cms.double(2),
        maxDzErrorForPrimaryAssignment = cms.double(0.05),
        maxDzForJetAxisAssigment = cms.double(0.1),
        maxDzForPrimaryAssignment = cms.double(0.1),
        maxDzSigForPrimaryAssignment = cms.double(5.0),
        maxJetDeltaR = cms.double(0.5),
        minJetPt = cms.double(25),
        preferHighRanked = cms.bool(False),
        useTiming = cms.bool(False)
    ),
    jets = cms.InputTag("ak4PFJets"),
    particles = cms.InputTag("particleFlow"),
    produceAssociationToOriginalVertices = cms.bool(True),
    produceNoPileUpCollection = cms.bool(False),
    producePileUpCollection = cms.bool(False),
    produceSortedVertices = cms.bool(False),
    qualityForPrimary = cms.int32(2),
    sorting = cms.PSet(

    ),
    usePVMET = cms.bool(True),
    vertices = cms.InputTag("offlinePrimaryVertices")
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


process.randomEngineStateProducer = cms.EDProducer("RandomEngineStateProducer")


process.secondaryVertexNegativeTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("impactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(-3.0),
        distSig2dMin = cms.double(-99999.9),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(-0.01),
        distVal2dMin = cms.double(-2.5),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(-0.5),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.secondaryVertexTagInfos = cms.EDProducer("SecondaryVertexProducer",
    beamSpotTag = cms.InputTag("offlineBeamSpot"),
    constraint = cms.string('BeamSpot'),
    extSVCollection = cms.InputTag("secondaryVertices"),
    extSVDeltaRToJet = cms.double(0.3),
    minimumTrackWeight = cms.double(0.5),
    trackIPTagInfos = cms.InputTag("impactParameterTagInfos"),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(99999.9),
        maxDistToAxis = cms.double(0.2),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(2),
        ptMin = cms.double(1.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(8),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip3dSig'),
    useExternalSV = cms.bool(False),
    usePVError = cms.bool(True),
    vertexCuts = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.4),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    ),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        minweight = cms.double(0.5),
        primcut = cms.double(1.8),
        seccut = cms.double(6.0),
        smoothing = cms.bool(False),
        weightthreshold = cms.double(0.001)
    ),
    vertexSelection = cms.PSet(
        sortCriterium = cms.string('dist3dError')
    )
)


process.siPixelRecHits = cms.EDProducer("SiPixelRecHitConverter",
    CPE = cms.string('PixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),
    src = cms.InputTag("siPixelClusters")
)


process.siPixelRecHitsPreSplitting = cms.EDProducer("SiPixelRecHitConverter",
    CPE = cms.string('PixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),
    src = cms.InputTag("siPixelClustersPreSplitting")
)


process.signalPartons = cms.EDProducer("PartonSelector",
    src = cms.InputTag("hiSignalGenParticles"),
    withLeptons = cms.bool(False)
)


process.simpleInclusiveSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("inclusiveSecondaryVertexFinderFilteredTagInfos"))
)


process.simpleInclusiveSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("inclusiveSecondaryVertexFinderFilteredTagInfos"))
)


process.simpleSecondaryVertexHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex2TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("secondaryVertexTagInfos"))
)


process.simpleSecondaryVertexHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('simpleSecondaryVertex3TrkComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("secondaryVertexTagInfos"))
)


process.softPFElectronBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFElectronComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.softPFElectronByIP2dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFElectronByIP2dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.softPFElectronByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFElectronByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.softPFElectronByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFElectronByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFElectronsTagInfos"))
)


process.softPFElectronsTagInfos = cms.EDProducer("SoftPFElectronTagInfoProducer",
    DeltaRElectronJet = cms.double(0.4),
    MaxSip3Dsig = cms.double(200),
    electrons = cms.InputTag("gedGsfElectrons"),
    jets = cms.InputTag("ak4PFJetsCHS"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.softPFMuonBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.softPFMuonByIP2dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP2dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.softPFMuonByIP3dBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByIP3dComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.softPFMuonByPtBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('softPFMuonByPtComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("softPFMuonsTagInfos"))
)


process.softPFMuonsTagInfos = cms.EDProducer("SoftPFMuonTagInfoProducer",
    filterIpsig = cms.double(4.0),
    filterPromptMuons = cms.bool(False),
    filterRatio1 = cms.double(0.4),
    filterRatio2 = cms.double(0.7),
    jets = cms.InputTag("ak4PFJetsCHS"),
    muonPt = cms.double(2.0),
    muonSIPsig = cms.double(200.0),
    muons = cms.InputTag("muons"),
    primaryVertex = cms.InputTag("offlinePrimaryVertices")
)


process.towersAboveThreshold = cms.EDProducer("CaloTowerCandidateCreator",
    minimumE = cms.double(3.0),
    minimumEt = cms.double(0.0),
    src = cms.InputTag("towerMaker"),
    verbose = cms.untracked.int32(0)
)


process.towersAboveThresholdTh2 = cms.EDProducer("CaloTowerCandidateCreator",
    minimumE = cms.double(2.0),
    minimumEt = cms.double(0.0),
    src = cms.InputTag("towerMaker"),
    verbose = cms.untracked.int32(0)
)


process.towersAboveThresholdTh4 = cms.EDProducer("CaloTowerCandidateCreator",
    minimumE = cms.double(4.0),
    minimumEt = cms.double(0.0),
    src = cms.InputTag("towerMaker"),
    verbose = cms.untracked.int32(0)
)


process.towersAboveThresholdTh5 = cms.EDProducer("CaloTowerCandidateCreator",
    minimumE = cms.double(5.0),
    minimumEt = cms.double(0.0),
    src = cms.InputTag("towerMaker"),
    verbose = cms.untracked.int32(0)
)


process.trackCountingHighEffBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D2ndComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.trackCountingHighPurBJetTags = cms.EDProducer("JetTagProducer",
    jetTagComputer = cms.string('trackCounting3D3rdComputer'),
    tagInfos = cms.VInputTag(cms.InputTag("impactParameterTagInfos"))
)


process.trackVertexArbitrator = cms.EDProducer("TrackVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxTimeSignificance = cms.double(3.5),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("vertexMerger"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("generalTracks")
)


process.trackVertexArbitratorDefault = cms.EDProducer("TrackVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxTimeSignificance = cms.double(3.5),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("vertexMerger"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("generalTracks")
)


process.vertexMerger = cms.EDProducer("VertexMerger",
    maxFraction = cms.double(0.7),
    minSignificance = cms.double(2),
    secondaryVertices = cms.InputTag("inclusiveVertexFinder")
)


process.bVertexFilter = cms.EDFilter("BVertexFilter",
    minVertices = cms.int32(0),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("secondaryVertices"),
    useVertexKinematicAsJetAxis = cms.bool(True),
    vertexFilter = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.1),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    )
)


process.beamScrapingFilter = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)


process.clusterCompatibilityFilter = cms.EDFilter("HIClusterCompatibilityFilter",
    cluscomSrc = cms.InputTag("hiClusterCompatibility"),
    clusterPars = cms.vdouble(0.0, 0.0045),
    clusterTrunc = cms.double(2.0),
    maxZ = cms.double(20.05),
    minZ = cms.double(-20.0),
    nhitsTrunc = cms.int32(150)
)


process.fHBHEIsoNoiseFilterResult = cms.EDFilter("BooleanFlagFilter",
    inputLabel = cms.InputTag("HBHENoiseFilterResultProducer","HBHEIsoNoiseFilterResult"),
    reverseDecision = cms.bool(False)
)


process.fHBHENoiseFilterResult = cms.EDFilter("BooleanFlagFilter",
    inputLabel = cms.InputTag("HBHENoiseFilterResultProducer","HBHENoiseFilterResult"),
    reverseDecision = cms.bool(False)
)


process.fHBHENoiseFilterResultRun1 = cms.EDFilter("BooleanFlagFilter",
    inputLabel = cms.InputTag("HBHENoiseFilterResultProducer","HBHENoiseFilterResultRun1"),
    reverseDecision = cms.bool(False)
)


process.fHBHENoiseFilterResultRun2Loose = cms.EDFilter("BooleanFlagFilter",
    inputLabel = cms.InputTag("HBHENoiseFilterResultProducer","HBHENoiseFilterResultRun2Loose"),
    reverseDecision = cms.bool(False)
)


process.fHBHENoiseFilterResultRun2Tight = cms.EDFilter("BooleanFlagFilter",
    inputLabel = cms.InputTag("HBHENoiseFilterResultProducer","HBHENoiseFilterResultRun2Tight"),
    reverseDecision = cms.bool(False)
)


process.hfNegFilter = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfNegTowers")
)


process.hfNegFilter2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfNegTowers")
)


process.hfNegFilter2Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfNegTowersTh2")
)


process.hfNegFilter2Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfNegTowersTh4")
)


process.hfNegFilter2Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfNegTowersTh5")
)


process.hfNegFilter3 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfNegTowers")
)


process.hfNegFilter3Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfNegTowersTh2")
)


process.hfNegFilter3Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfNegTowersTh4")
)


process.hfNegFilter3Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfNegTowersTh5")
)


process.hfNegFilter4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfNegTowers")
)


process.hfNegFilter4Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfNegTowersTh2")
)


process.hfNegFilter4Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfNegTowersTh4")
)


process.hfNegFilter4Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfNegTowersTh5")
)


process.hfNegFilter5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfNegTowers")
)


process.hfNegFilter5Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfNegTowersTh2")
)


process.hfNegFilter5Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfNegTowersTh4")
)


process.hfNegFilter5Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfNegTowersTh5")
)


process.hfNegFilterTh2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfNegTowersTh2")
)


process.hfNegFilterTh4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfNegTowersTh4")
)


process.hfNegFilterTh5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfNegTowersTh5")
)


process.hfNegTowers = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(-3.0),
    etaMin = cms.double(-6.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThreshold")
)


process.hfNegTowersTh2 = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(-3.0),
    etaMin = cms.double(-6.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThresholdTh2")
)


process.hfNegTowersTh4 = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(-3.0),
    etaMin = cms.double(-6.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThresholdTh4")
)


process.hfNegTowersTh5 = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(-3.0),
    etaMin = cms.double(-6.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThresholdTh5")
)


process.hfPosFilter = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfPosTowers")
)


process.hfPosFilter2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfPosTowers")
)


process.hfPosFilter2Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfPosTowersTh2")
)


process.hfPosFilter2Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfPosTowersTh4")
)


process.hfPosFilter2Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(2),
    src = cms.InputTag("hfPosTowersTh5")
)


process.hfPosFilter3 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfPosTowers")
)


process.hfPosFilter3Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfPosTowersTh2")
)


process.hfPosFilter3Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfPosTowersTh4")
)


process.hfPosFilter3Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfPosTowersTh5")
)


process.hfPosFilter4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfPosTowers")
)


process.hfPosFilter4Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfPosTowersTh2")
)


process.hfPosFilter4Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfPosTowersTh4")
)


process.hfPosFilter4Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(4),
    src = cms.InputTag("hfPosTowersTh5")
)


process.hfPosFilter5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfPosTowers")
)


process.hfPosFilter5Th2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfPosTowersTh2")
)


process.hfPosFilter5Th4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfPosTowersTh4")
)


process.hfPosFilter5Th5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(5),
    src = cms.InputTag("hfPosTowersTh5")
)


process.hfPosFilterTh2 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfPosTowersTh2")
)


process.hfPosFilterTh4 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfPosTowersTh4")
)


process.hfPosFilterTh5 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfPosTowersTh5")
)


process.hfPosTowers = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(6.0),
    etaMin = cms.double(3.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThreshold")
)


process.hfPosTowersTh2 = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(6.0),
    etaMin = cms.double(3.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThresholdTh2")
)


process.hfPosTowersTh4 = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(6.0),
    etaMin = cms.double(3.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThresholdTh4")
)


process.hfPosTowersTh5 = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(6.0),
    etaMin = cms.double(3.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThresholdTh5")
)


process.hiTracks = cms.EDFilter("TrackSelector",
    cut = cms.string('quality("highPurity")'),
    src = cms.InputTag("hiGeneralTracks")
)


process.highPurityTracks = cms.EDFilter("TrackSelector",
    cut = cms.string('quality("highPurity")'),
    src = cms.InputTag("generalTracks")
)


process.hltPixelClusterShapeFilter = cms.EDFilter("HLTPixelClusterShapeFilter",
    clusterPars = cms.vdouble(0, 0.0045),
    clusterTrunc = cms.double(2),
    inputTag = cms.InputTag("siPixelRecHits"),
    maxZ = cms.double(20.05),
    minZ = cms.double(-20),
    nhitsTrunc = cms.int32(150),
    saveTags = cms.bool(True),
    zStep = cms.double(0.2)
)


process.inclusiveSecondaryVerticesFiltered = cms.EDFilter("BVertexFilter",
    minVertices = cms.int32(0),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("inclusiveSecondaryVertices"),
    useVertexKinematicAsJetAxis = cms.bool(True),
    vertexFilter = cms.PSet(
        distSig2dMax = cms.double(99999.9),
        distSig2dMin = cms.double(3.0),
        distSig3dMax = cms.double(99999.9),
        distSig3dMin = cms.double(-99999.9),
        distVal2dMax = cms.double(2.5),
        distVal2dMin = cms.double(0.01),
        distVal3dMax = cms.double(99999.9),
        distVal3dMin = cms.double(-99999.9),
        fracPV = cms.double(0.65),
        massMax = cms.double(6.5),
        maxDeltaRToJetAxis = cms.double(0.1),
        minimumTrackWeight = cms.double(0.5),
        multiplicityMin = cms.uint32(2),
        useTrackWeights = cms.bool(True),
        v0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        )
    )
)


process.pileupVertexFilterCutE = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(True),
    doDzNtrkCut = cms.bool(False),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 3.0, 2.4, 2.0, 1.2, 
        1.2, 0.9, 0.6
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesRecovery")
)


process.pileupVertexFilterCutEandG = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(True),
    doDzNtrkCut = cms.bool(True),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 3.0, 2.4, 2.0, 1.2, 
        1.2, 0.9, 0.6
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesRecovery")
)


process.pileupVertexFilterCutG = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(True),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 3.0, 2.4, 2.0, 1.2, 
        1.2, 0.9, 0.6
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesRecovery")
)


process.pileupVertexFilterCutGloose = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(True),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 4.5, 3.2, 3.0, 1.8, 
        1.8, 1.35, 0.9
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesRecovery")
)


process.pileupVertexFilterCutGplus = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(True),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(0.05),
    dzCutByNtrk = cms.vdouble(
        999.0, 999.0, 999.0, 3.0, 2.0, 
        1.6, 1.4, 1.2, 1.1, 1.0, 
        0.9, 0.8, 0.7, 0.7, 0.6, 
        0.6, 0.5, 0.5, 0.4, 0.4, 
        0.4, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.2, 0.2, 0.2, 0.2, 
        0.0
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesRecovery")
)


process.pileupVertexFilterCutGplusNV = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(True),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 999.0, 999.0, 3.0, 2.0, 
        1.6, 1.4, 1.2, 1.1, 1.0, 
        0.9, 0.8, 0.7, 0.7, 0.6, 
        0.6, 0.5, 0.5, 0.4, 0.4, 
        0.4, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.2, 0.2, 0.2, 0.2, 
        0.0
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVertices")
)


process.pileupVertexFilterCutGplusUpsPP = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(True),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 999.0, 1.5, 1.0, 0.8, 
        0.6, 0.5, 0.4, 0.3, 0.2, 
        0.2, 0.2, 0.2, 0.2, 0.2, 
        0.2, 0.0
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVertices")
)


process.pileupVertexFilterCutGplusplus = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(False),
    doSurfaceCut = cms.bool(True),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(0.05),
    dzCutByNtrk = cms.vdouble(
        999.0, 3.0, 2.4, 2.0, 1.2, 
        1.2, 0.9, 0.6
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        28.593, -1.525, 2.636788, -1.5e-05, 200.0, 
        0.0
    ),
    surfaceFunctionString = cms.string('[0]*exp([1]*(x-([3]*(y-[4])**2+[5])))+[2]'),
    surfaceMinDzEval = cms.double(0.0),
    vtxSrc = cms.InputTag("offlinePrimaryVertices")
)


process.pileupVertexFilterCutGtight = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(True),
    doSurfaceCut = cms.bool(False),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 2.0, 1.6, 1.333, 0.8, 
        0.8, 0.6, 0.4
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesRecovery")
)


process.pileupVertexFilterCutW = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(False),
    doSurfaceCut = cms.bool(True),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(999.0),
    dzCutByNtrk = cms.vdouble(
        999.0, 3.0, 2.4, 2.0, 1.2, 
        1.2, 0.9, 0.6
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVertices")
)


process.pileupVertexFilterCutWplus = cms.EDFilter("PAPileUpVertexFilter",
    doDxyDzCut = cms.bool(False),
    doDzNtrkCut = cms.bool(False),
    doSurfaceCut = cms.bool(True),
    dxyDzCutPar0 = cms.double(0.6),
    dxyDzCutPar1 = cms.double(13.333),
    dxyVeto = cms.double(0.05),
    dzCutByNtrk = cms.vdouble(
        999.0, 3.0, 2.4, 2.0, 1.2, 
        1.2, 0.9, 0.6
    ),
    dzVeto = cms.double(-999.0),
    surfaceCutParameters = cms.vdouble(
        0.92473, 7.484908, 8.84978, -0.587169, 0.478601, 
        -0.000106, -0.000385, -0.09479, 0.250266, 198.662432, 
        728.42475, 2.958134
    ),
    surfaceFunctionString = cms.string('[2]*exp(-x**2/[0])*x**[3]+[1]+([6]*exp(-x/[4])*x**[7]+[5])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])*(y-[10]*exp(-x**2/[8])*x**[11]-[9])'),
    surfaceMinDzEval = cms.double(0.2),
    vtxSrc = cms.InputTag("offlinePrimaryVertices")
)


process.primaryVertexFilter = cms.EDFilter("VertexSelector",
    cut = cms.string('!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2'),
    filter = cms.bool(True),
    src = cms.InputTag("offlinePrimaryVerticesRecovery")
)


process.HiForest = cms.EDAnalyzer("HiForestInfo",
    GlobalTagLabel = cms.string('103X_upgrade2018_realistic_HI_v11'),
    HiForestVersion = cms.string('CMSSW_10_3_5-556-g6db37c42bce\n'),
    inputLines = cms.vstring(
        'HiForest 103X', 
        "\'JetCorrectorParametersCollection_Autumn18_HI_V6_MC_AK4PF\'"
    )
)


process.HiGenParticleAna = cms.EDAnalyzer("HiGenAnalyzer",
    chargedOnly = cms.untracked.bool(False),
    doHI = cms.untracked.bool(True),
    doParticles = cms.untracked.bool(True),
    doVertex = cms.untracked.bool(False),
    etaMax = cms.untracked.double(7.0),
    genHIsrc = cms.untracked.InputTag("heavyIon"),
    genParticleSrc = cms.untracked.InputTag("genParticles"),
    ptMin = cms.untracked.double(0),
    src = cms.untracked.InputTag("generator"),
    stableOnly = cms.untracked.bool(True)
)


process.ak3PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('ak3PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(False),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak3GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak3GenJets","sym"),
    genTau1 = cms.InputTag("ak3HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak3HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak3HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak3HiSignalGenJets"),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('ak3PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("ak3PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(False),
    matchTag = cms.untracked.InputTag("patJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.3),
    subjetGenTag = cms.untracked.InputTag("ak3GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.ak4PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('ak4PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(False),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak4GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak4GenJets","sym"),
    genTau1 = cms.InputTag("ak4HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak4HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak4HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak4HiSignalGenJets"),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('ak4PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("ak4PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(False),
    matchTag = cms.untracked.InputTag("patJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.4),
    subjetGenTag = cms.untracked.InputTag("ak4GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akCs3PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akCs3PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(True),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak3GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak3GenJets","sym"),
    genTau1 = cms.InputTag("ak3HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak3HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak3HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak3HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akCs3PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akCs3PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(True),
    matchTag = cms.untracked.InputTag("ak3PFpatJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.3),
    subjetGenTag = cms.untracked.InputTag("ak3GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akCs4PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akCs4PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(True),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak4GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak4GenJets","sym"),
    genTau1 = cms.InputTag("ak4HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak4HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak4HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak4HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akCs4PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akCs4PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(True),
    matchTag = cms.untracked.InputTag("ak4PFpatJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.4),
    subjetGenTag = cms.untracked.InputTag("ak4GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akFlowPuCs3PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akFlowPuCs3PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(True),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak3GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak3GenJets","sym"),
    genTau1 = cms.InputTag("ak3HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak3HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak3HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak3HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akFlowPuCs3PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akFlowPuCs3PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(True),
    matchTag = cms.untracked.InputTag("ak3PFpatJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.3),
    subjetGenTag = cms.untracked.InputTag("ak3GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akFlowPuCs4PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akFlowPuCs4PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(True),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak4GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak4GenJets","sym"),
    genTau1 = cms.InputTag("ak4HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak4HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak4HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak4HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akFlowPuCs4PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akFlowPuCs4PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(True),
    matchTag = cms.untracked.InputTag("ak4PFpatJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.4),
    subjetGenTag = cms.untracked.InputTag("ak4GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akPu3CaloJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akPu3Calo'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(False),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak3GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak3GenJets","sym"),
    genTau1 = cms.InputTag("ak3HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak3HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak3HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak3HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akPu3Calo'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akPu3CalopatJetsWithBtagging"),
    matchJets = cms.untracked.bool(False),
    matchTag = cms.untracked.InputTag("patJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.3),
    subjetGenTag = cms.untracked.InputTag("ak3GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akPu3PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akPu3PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(False),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak3GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak3GenJets","sym"),
    genTau1 = cms.InputTag("ak3HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak3HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak3HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak3HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akPu3PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akPu3PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(False),
    matchTag = cms.untracked.InputTag("patJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.3),
    subjetGenTag = cms.untracked.InputTag("ak3GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akPu4CaloJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akPu4Calo'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(False),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak4GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak4GenJets","sym"),
    genTau1 = cms.InputTag("ak4HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak4HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak4HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak4HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akPu4Calo'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akPu4CalopatJetsWithBtagging"),
    matchJets = cms.untracked.bool(False),
    matchTag = cms.untracked.InputTag("patJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.4),
    subjetGenTag = cms.untracked.InputTag("ak4GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.akPu4PFJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    bTagJetName = cms.untracked.string('akPu4PF'),
    doGenSubJets = cms.untracked.bool(False),
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(False),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(True),
    doLifeTimeTaggingExtras = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(True),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(True),
    genDroppedBranches = cms.InputTag("ak4GenJets","droppedBranches"),
    genParticles = cms.untracked.InputTag("genParticles"),
    genPtMin = cms.untracked.double(5),
    genSym = cms.InputTag("ak4GenJets","sym"),
    genTau1 = cms.InputTag("ak4HiGenNjettiness","tau1"),
    genTau2 = cms.InputTag("ak4HiGenNjettiness","tau2"),
    genTau3 = cms.InputTag("ak4HiGenNjettiness","tau3"),
    genjetTag = cms.InputTag("ak4HiSignalGenJets"),
    hltTrgResults = cms.untracked.string('TriggerResults::HISIGNAL'),
    isMC = cms.untracked.bool(True),
    jetName = cms.untracked.string('akPu4PF'),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("akPu4PFpatJetsWithBtagging"),
    matchJets = cms.untracked.bool(False),
    matchTag = cms.untracked.InputTag("patJetsWithBtagging"),
    pfCandidateLabel = cms.untracked.InputTag("particleFlow"),
    rParam = cms.double(0.4),
    subjetGenTag = cms.untracked.InputTag("ak4GenJets"),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("generalTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.anaTrack = cms.EDAnalyzer("TrackAnalyzer",
    associatorMap = cms.InputTag("tpRecoAssocHiGeneralTracks"),
    beamSpotSrc = cms.untracked.InputTag("offlineBeamSpot"),
    doMVA = cms.untracked.bool(False),
    doPFMatching = cms.untracked.bool(True),
    doSimTrack = cms.untracked.bool(False),
    doSimVertex = cms.untracked.bool(False),
    fillSimTrack = cms.untracked.bool(False),
    mvaSrc = cms.InputTag("hiGeneralTracks","MVAVals"),
    particleSrc = cms.InputTag("genParticles"),
    pfCandSrc = cms.InputTag("particleFlowTmp"),
    qualityString = cms.untracked.string('highPurity'),
    qualityStrings = cms.untracked.vstring(
        'highPurity', 
        'tight', 
        'loose'
    ),
    simTrackPtMin = cms.untracked.double(0.1),
    tpEffSrc = cms.untracked.InputTag("mix","MergedTrackTruth"),
    trackPtMin = cms.untracked.double(0.49),
    trackSrc = cms.InputTag("hiGeneralTracks"),
    useQuality = cms.untracked.bool(False),
    vertexSrc = cms.VInputTag("hiSelectedVertex")
)


process.dump = cms.EDAnalyzer("EventContentAnalyzer")


process.ggHiNtuplizer = cms.EDAnalyzer("ggHiNtuplizer",
    VtxLabel = cms.InputTag("offlinePrimaryVerticesRecovery"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    conversions = cms.InputTag("allConversions"),
    doEffectiveAreas = cms.bool(False),
    doEleERegression = cms.bool(False),
    doElectronVID = cms.bool(False),
    doElectrons = cms.bool(False),
    doGenParticles = cms.bool(True),
    doMuons = cms.bool(False),
    doPfIso = cms.bool(False),
    doPhoERegression = cms.bool(False),
    doPhotons = cms.bool(True),
    doRecHitsEB = cms.bool(False),
    doRecHitsEE = cms.bool(False),
    doSuperClusters = cms.bool(False),
    effAreasConfigFile = cms.FileInPath('HeavyIonsAnalysis/PhotonAnalysis/data/EffectiveAreas_94X_v0'),
    electronLooseID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-loose"),
    electronMediumID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-medium"),
    electronTightID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-tight"),
    electronVetoID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-veto"),
    genParticleSrc = cms.InputTag("genParticles"),
    gsfElectronLabel = cms.InputTag("gedGsfElectrons"),
    particleBasedIsolationPhoton = cms.InputTag("DUMMY"),
    particleFlowCollection = cms.InputTag("particleFlow"),
    pileupCollection = cms.InputTag("addPileupInfo"),
    recHitsEB = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEB"),
    recHitsEE = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEE"),
    recoMuonSrc = cms.InputTag("muons"),
    recoPhotonHiIsolationMap = cms.InputTag("photonIsolationHIProducerppIsland"),
    recoPhotonSrc = cms.InputTag("islandPhotons"),
    removePhotonPfIsoFootprint = cms.bool(False),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    runOnParticleGun = cms.bool(False),
    superClustersEB = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALBarrel"),
    superClustersEE = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALEndcapWithPreshower"),
    useValMapIso = cms.bool(True)
)


process.ggHiNtuplizerGED = cms.EDAnalyzer("ggHiNtuplizer",
    VtxLabel = cms.InputTag("offlinePrimaryVerticesRecovery"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    conversions = cms.InputTag("allConversions"),
    doEffectiveAreas = cms.bool(False),
    doEleERegression = cms.bool(False),
    doElectronVID = cms.bool(False),
    doElectrons = cms.bool(True),
    doGenParticles = cms.bool(True),
    doMuons = cms.bool(True),
    doPfIso = cms.bool(True),
    doPhoERegression = cms.bool(False),
    doPhotons = cms.bool(True),
    doRecHitsEB = cms.bool(False),
    doRecHitsEE = cms.bool(False),
    doSuperClusters = cms.bool(False),
    effAreasConfigFile = cms.FileInPath('HeavyIonsAnalysis/PhotonAnalysis/data/EffectiveAreas_94X_v0'),
    electronLooseID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-loose"),
    electronMediumID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-medium"),
    electronTightID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-tight"),
    electronVetoID = cms.InputTag("egmGsfElectronIDs","cutBasedElectronID-Spring15-25ns-V1-standalone-veto"),
    genParticleSrc = cms.InputTag("genParticles"),
    gsfElectronLabel = cms.InputTag("correctedElectrons"),
    particleBasedIsolationPhoton = cms.InputTag("particleBasedIsolation","gedPhotons"),
    particleFlowCollection = cms.InputTag("particleFlow"),
    pileupCollection = cms.InputTag("addPileupInfo"),
    recHitsEB = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEB"),
    recHitsEE = cms.untracked.InputTag("ecalRecHit","EcalRecHitsEE"),
    recoMuonSrc = cms.InputTag("muons"),
    recoPhotonHiIsolationMap = cms.InputTag("photonIsolationHIProducerppGED"),
    recoPhotonSrc = cms.InputTag("gedPhotons"),
    removePhotonPfIsoFootprint = cms.bool(True),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    runOnParticleGun = cms.bool(False),
    superClustersEB = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALBarrel"),
    superClustersEE = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALEndcapWithPreshower"),
    useValMapIso = cms.bool(True)
)


process.hiEvtAnalyzer = cms.EDAnalyzer("HiEvtAnalyzer",
    CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    CentralitySrc = cms.InputTag("hiCentrality"),
    EvtPlane = cms.InputTag("hiEvtPlane"),
    EvtPlaneFlat = cms.InputTag("hiEvtPlaneFlat"),
    HiMC = cms.InputTag("heavyIon"),
    Vertex = cms.InputTag("offlinePrimaryVerticesRecovery"),
    doCentrality = cms.bool(True),
    doEvtPlane = cms.bool(True),
    doEvtPlaneFlat = cms.bool(False),
    doHiMC = cms.bool(True),
    doMC = cms.bool(True),
    doVertex = cms.bool(True),
    evtPlaneLevel = cms.int32(0),
    useHepMC = cms.bool(False)
)


process.hiFJRhoAnalyzer = cms.EDAnalyzer("HiFJRhoAnalyzer",
    areaJets = cms.InputTag("hiFJRhoProducer","areaJets"),
    etaJets = cms.InputTag("hiFJRhoProducer","etaJets"),
    etaMap = cms.InputTag("hiFJRhoProducer","mapEtaEdges","HiForest"),
    etaMaxRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapEtaMaxGrid"),
    etaMinRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapEtaMinGrid"),
    meanRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapMeanRhoVsEtaGrid"),
    ptJets = cms.InputTag("hiFJRhoProducer","ptJets"),
    rho = cms.InputTag("hiFJRhoProducer","mapToRho"),
    rhoCorr = cms.InputTag("hiFJGridEmptyAreaCalculator","mapToRhoCorr"),
    rhoCorr1Bin = cms.InputTag("hiFJGridEmptyAreaCalculator","mapToRhoCorr1Bin"),
    rhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapRhoVsEtaGrid"),
    rhom = cms.InputTag("hiFJRhoProducer","mapToRhoM"),
    rhomCorr = cms.InputTag("hiFJGridEmptyAreaCalculator","mapToRhoMCorr"),
    rhomCorr1Bin = cms.InputTag("hiFJGridEmptyAreaCalculator","mapToRhoMCorr1Bin"),
    useModulatedRho = cms.bool(False)
)


process.hiFJRhoAnalyzerFinerBins = cms.EDAnalyzer("HiFJRhoAnalyzer",
    areaJets = cms.InputTag("hiFJRhoProducerFinerBins","areaJets"),
    etaJets = cms.InputTag("hiFJRhoProducerFinerBins","etaJets"),
    etaMap = cms.InputTag("hiFJRhoProducerFinerBins","mapEtaEdges","HiForest"),
    etaMaxRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapEtaMaxGrid"),
    etaMinRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapEtaMinGrid"),
    meanRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapMeanRhoVsEtaGrid"),
    ptJets = cms.InputTag("hiFJRhoProducerFinerBins","ptJets"),
    rho = cms.InputTag("hiFJRhoProducerFinerBins","mapToRho"),
    rhoCorr = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapToRhoCorr"),
    rhoCorr1Bin = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapToRhoCorr1Bin"),
    rhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapRhoVsEtaGrid"),
    rhom = cms.InputTag("hiFJRhoProducerFinerBins","mapToRhoM"),
    rhomCorr = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapToRhoMCorr"),
    rhomCorr1Bin = cms.InputTag("hiFJGridEmptyAreaCalculatorFinerBins","mapToRhoMCorr1Bin"),
    useModulatedRho = cms.bool(False)
)


process.hiPuRhoR3Analyzer = cms.EDAnalyzer("HiFJRhoAnalyzer",
    areaJets = cms.InputTag("hiPuRhoR3Producer","areaJets"),
    etaJets = cms.InputTag("hiPuRhoR3Producer","etaJets"),
    etaMap = cms.InputTag("hiPuRhoR3Producer","mapEtaEdges","HiForest"),
    etaMaxRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapEtaMaxGrid"),
    etaMinRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapEtaMinGrid"),
    meanRhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapMeanRhoVsEtaGrid"),
    nTow = cms.InputTag("hiPuRhoR3Producer","mapToNTow"),
    ptJets = cms.InputTag("hiPuRhoR3Producer","ptJets"),
    rho = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoCorr = cms.InputTag("hiPuRhoR3Producer","mapToRhoMedian"),
    rhoCorr1Bin = cms.InputTag("hiPuRhoR3Producer","mapToRho"),
    rhoExtra = cms.InputTag("hiPuRhoR3Producer","mapToRhoExtra"),
    rhoFlowFitParams = cms.InputTag("hiFJRhoFlowModulationProducer","rhoFlowFitParams"),
    rhoGrid = cms.InputTag("hiFJGridEmptyAreaCalculator","mapRhoVsEtaGrid"),
    rhom = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    rhomCorr = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    rhomCorr1Bin = cms.InputTag("hiPuRhoR3Producer","mapToRhoM"),
    towExcludeEta = cms.InputTag("hiPuRhoR3Producer","mapToTowExcludeEta"),
    towExcludePhi = cms.InputTag("hiPuRhoR3Producer","mapToTowExcludePhi"),
    towExcludePt = cms.InputTag("hiPuRhoR3Producer","mapToTowExcludePt"),
    useModulatedRho = cms.bool(True)
)


process.hltanalysis = cms.EDAnalyzer("HLTBitAnalyzer",
    HLTProcessName = cms.string('HLT'),
    OfflinePrimaryVertices0 = cms.InputTag(""),
    RunParameters = cms.PSet(
        isData = cms.untracked.bool(True)
    ),
    UseTFileService = cms.untracked.bool(True),
    dummyBranches = cms.untracked.vstring( (
        'DST_Physics_v7', 
        'AlCa_EcalEtaEBonlyForHI_v1', 
        'AlCa_EcalEtaEEonlyForHI_v1', 
        'AlCa_EcalPhiSymForHI_v1', 
        'AlCa_EcalPi0EBonlyForHI_v1', 
        'AlCa_EcalPi0EEonlyForHI_v1', 
        'AlCa_RPCMuonNormalisationForHI_v1', 
        'HLT_EcalCalibration_v4', 
        'HLT_HICastorMinimumBias_part0_v1', 
        'HLT_HICastorMinimumBias_part10_v1', 
        'HLT_HICastorMinimumBias_part11_v1', 
        'HLT_HICastorMinimumBias_part12_v1', 
        'HLT_HICastorMinimumBias_part13_v1', 
        'HLT_HICastorMinimumBias_part14_v1', 
        'HLT_HICastorMinimumBias_part15_v1', 
        'HLT_HICastorMinimumBias_part16_v1', 
        'HLT_HICastorMinimumBias_part17_v1', 
        'HLT_HICastorMinimumBias_part18_v1', 
        'HLT_HICastorMinimumBias_part19_v1', 
        'HLT_HICastorMinimumBias_part1_v1', 
        'HLT_HICastorMinimumBias_part2_v1', 
        'HLT_HICastorMinimumBias_part3_v1', 
        'HLT_HICastorMinimumBias_part4_v1', 
        'HLT_HICastorMinimumBias_part5_v1', 
        'HLT_HICastorMinimumBias_part6_v1', 
        'HLT_HICastorMinimumBias_part7_v1', 
        'HLT_HICastorMinimumBias_part8_v1', 
        'HLT_HICastorMinimumBias_part9_v1', 
        'HLT_HICastor_HighJet_BptxAND_v1', 
        'HLT_HICastor_HighJet_MBHF1AND_BptxAND_v1', 
        'HLT_HICastor_HighJet_MBHF1OR_BptxAND_v1', 
        'HLT_HICastor_HighJet_MBHF1OR_v1', 
        'HLT_HICastor_HighJet_MBHF2AND_BptxAND_v1', 
        'HLT_HICastor_HighJet_NotMBHF2AND_v1', 
        'HLT_HICastor_HighJet_NotMBHF2OR_v1', 
        'HLT_HICastor_HighJet_v1', 
        'HLT_HICastor_MediumJet_BptxAND_v1', 
        'HLT_HICastor_MediumJet_MBHF1OR_BptxAND_v1', 
        'HLT_HICastor_MediumJet_MBHF1OR_v1', 
        'HLT_HICastor_MediumJet_NotMBHF2AND_v1', 
        'HLT_HICastor_MediumJet_NotMBHF2OR_v1', 
        'HLT_HICastor_MediumJet_SingleEG5_MBHF1OR_BptxAND_v1', 
        'HLT_HICastor_MediumJet_SingleEG5_MBHF1OR_v1', 
        'HLT_HICastor_MediumJet_SingleMu0_MBHF1OR_BptxAND_v1', 
        'HLT_HICastor_MediumJet_SingleMu0_MBHF1OR_v1', 
        'HLT_HICastor_MediumJet_v1', 
        'HLT_HICastor_Muon_BptxAND_v1', 
        'HLT_HICastor_Muon_v1', 
        'HLT_HICentrality30100_FirstCollisionAfterAbortGap_v1', 
        'HLT_HICentralityTag20100_v1', 
        'HLT_HICentralityTag30100_v1', 
        'HLT_HICentralityTag50100_v1', 
        'HLT_HICentralityVeto_Beamspot_v1', 
        'HLT_HICentralityVeto_v1', 
        'HLT_HICsAK4PFJet100Eta1p5_Beamspot_v1', 
        'HLT_HICsAK4PFJet100Eta1p5_Centrality_30_100_v1', 
        'HLT_HICsAK4PFJet100Eta1p5_Centrality_50_100_v1', 
        'HLT_HICsAK4PFJet100Eta1p5_v1', 
        'HLT_HICsAK4PFJet120Eta1p5_v1', 
        'HLT_HICsAK4PFJet60Eta1p5_Centrality_30_100_v1', 
        'HLT_HICsAK4PFJet60Eta1p5_Centrality_50_100_v1', 
        'HLT_HICsAK4PFJet60Eta1p5_v1', 
        'HLT_HICsAK4PFJet80Eta1p5_Centrality_30_100_v1', 
        'HLT_HICsAK4PFJet80Eta1p5_Centrality_50_100_v1', 
        'HLT_HICsAK4PFJet80Eta1p5_v1', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt15_v1', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt20_v1', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt30_v1', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt40_v1', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt50_v1', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt60_v1', 
        'HLT_HIDoubleEle10GsfMass50_v1', 
        'HLT_HIDoubleEle10Gsf_v1', 
        'HLT_HIDoubleEle15GsfMass50_v1', 
        'HLT_HIDoubleEle15Gsf_v1', 
        'HLT_HIDsPPTrackingGlobal_Dpt20_v1', 
        'HLT_HIDsPPTrackingGlobal_Dpt30_v1', 
        'HLT_HIDsPPTrackingGlobal_Dpt40_v1', 
        'HLT_HIDsPPTrackingGlobal_Dpt50_v1', 
        'HLT_HIDsPPTrackingGlobal_Dpt60_v1', 
        'HLT_HIEle10Gsf_PuAK4CaloJet100Eta2p1_v1', 
        'HLT_HIEle10Gsf_PuAK4CaloJet40Eta2p1_v1', 
        'HLT_HIEle10Gsf_PuAK4CaloJet60Eta2p1_v1', 
        'HLT_HIEle10Gsf_PuAK4CaloJet80Eta2p1_v1', 
        'HLT_HIEle10Gsf_v1', 
        'HLT_HIEle15Ele10GsfMass50_v1', 
        'HLT_HIEle15Ele10Gsf_v1', 
        'HLT_HIEle15Gsf_PuAK4CaloJet100Eta2p1_v1', 
        'HLT_HIEle15Gsf_PuAK4CaloJet40Eta2p1_v1', 
        'HLT_HIEle15Gsf_PuAK4CaloJet60Eta2p1_v1', 
        'HLT_HIEle15Gsf_PuAK4CaloJet80Eta2p1_v1', 
        'HLT_HIEle15Gsf_v1', 
        'HLT_HIEle20Gsf_PuAK4CaloJet100Eta2p1_v1', 
        'HLT_HIEle20Gsf_PuAK4CaloJet40Eta2p1_v1', 
        'HLT_HIEle20Gsf_PuAK4CaloJet60Eta2p1_v1', 
        'HLT_HIEle20Gsf_PuAK4CaloJet80Eta2p1_v1', 
        'HLT_HIEle20Gsf_v1', 
        'HLT_HIEle30Gsf_v1', 
        'HLT_HIEle40Gsf_v1', 
        'HLT_HIEle50Gsf_v1', 
        'HLT_HIFullTracks2018_HighPt18_v1', 
        'HLT_HIFullTracks2018_HighPt24_v1', 
        'HLT_HIFullTracks2018_HighPt34_v1', 
        'HLT_HIFullTracks2018_HighPt45_v1', 
        'HLT_HIFullTracks2018_HighPt56_v1', 
        'HLT_HIFullTracks2018_HighPt60_v1', 
        'HLT_HIFullTracks_Multiplicity020_HF1AND_v1', 
        'HLT_HIFullTracks_Multiplicity020_HF1OR_v1', 
        'HLT_HIFullTracks_Multiplicity020_HF2OR_v1', 
        'HLT_HIFullTracks_Multiplicity020_v1', 
        'HLT_HIFullTracks_Multiplicity2040_HF1AND_v1', 
        'HLT_HIFullTracks_Multiplicity2040_HF1OR_v1', 
        'HLT_HIFullTracks_Multiplicity2040_HF2OR_v1', 
        'HLT_HIFullTracks_Multiplicity2040_v1', 
        'HLT_HIFullTracks_Multiplicity335_HF1OR_v1', 
        'HLT_HIFullTracks_Multiplicity4060_v1', 
        'HLT_HIFullTracks_Multiplicity6080_v1', 
        'HLT_HIFullTracks_Multiplicity80100_v1', 
        'HLT_HIGEDPhoton10_Cent30_100_v1', 
        'HLT_HIGEDPhoton10_Cent50_100_v1', 
        'HLT_HIGEDPhoton10_EB_HECut_v1', 
        'HLT_HIGEDPhoton10_EB_v1', 
        'HLT_HIGEDPhoton10_HECut_v1', 
        'HLT_HIGEDPhoton10_v1', 
        'HLT_HIGEDPhoton20_Cent30_100_v1', 
        'HLT_HIGEDPhoton20_Cent50_100_v1', 
        'HLT_HIGEDPhoton20_EB_HECut_v1', 
        'HLT_HIGEDPhoton20_EB_v1', 
        'HLT_HIGEDPhoton20_HECut_v1', 
        'HLT_HIGEDPhoton20_v1', 
        'HLT_HIGEDPhoton30_Cent30_100_v1', 
        'HLT_HIGEDPhoton30_Cent50_100_v1', 
        'HLT_HIGEDPhoton30_EB_HECut_v1', 
        'HLT_HIGEDPhoton30_EB_v1', 
        'HLT_HIGEDPhoton30_HECut_v1', 
        'HLT_HIGEDPhoton30_v1', 
        'HLT_HIGEDPhoton40_Cent30_100_v1', 
        'HLT_HIGEDPhoton40_Cent50_100_v1', 
        'HLT_HIGEDPhoton40_EB_HECut_v1', 
        'HLT_HIGEDPhoton40_EB_v1', 
        'HLT_HIGEDPhoton40_HECut_v1', 
        'HLT_HIGEDPhoton40_v1', 
        'HLT_HIGEDPhoton50_EB_HECut_v1', 
        'HLT_HIGEDPhoton50_EB_v1', 
        'HLT_HIGEDPhoton50_HECut_v1', 
        'HLT_HIGEDPhoton50_v1', 
        'HLT_HIGEDPhoton60_EB_HECut_v1', 
        'HLT_HIGEDPhoton60_EB_v1', 
        'HLT_HIGEDPhoton60_HECut_v1', 
        'HLT_HIGEDPhoton60_v1', 
        'HLT_HIHcalNZS_v1', 
        'HLT_HIHcalPhiSym_v1', 
        'HLT_HIIslandPhoton10_Eta1p5_v1', 
        'HLT_HIIslandPhoton10_Eta2p4_Cent30_100_v1', 
        'HLT_HIIslandPhoton10_Eta2p4_Cent50_100_v1', 
        'HLT_HIIslandPhoton10_Eta2p4_v1', 
        'HLT_HIIslandPhoton10_Eta3p1_Cent30_100_v1', 
        'HLT_HIIslandPhoton10_Eta3p1_Cent50_100_v1', 
        'HLT_HIIslandPhoton10_Eta3p1_v1', 
        'HLT_HIIslandPhoton20_Eta1p5_v1', 
        'HLT_HIIslandPhoton20_Eta2p4_Cent30_100_v1', 
        'HLT_HIIslandPhoton20_Eta2p4_Cent50_100_v1', 
        'HLT_HIIslandPhoton20_Eta2p4_v1', 
        'HLT_HIIslandPhoton20_Eta3p1_Cent30_100_v1', 
        'HLT_HIIslandPhoton20_Eta3p1_Cent50_100_v1', 
        'HLT_HIIslandPhoton20_Eta3p1_v1', 
        'HLT_HIIslandPhoton30_Eta1p5_v1', 
        'HLT_HIIslandPhoton30_Eta2p4_Cent30_100_v1', 
        'HLT_HIIslandPhoton30_Eta2p4_Cent50_100_v1', 
        'HLT_HIIslandPhoton30_Eta2p4_v1', 
        'HLT_HIIslandPhoton30_Eta3p1_Cent30_100_v1', 
        'HLT_HIIslandPhoton30_Eta3p1_Cent50_100_v1', 
        'HLT_HIIslandPhoton30_Eta3p1_v1', 
        'HLT_HIIslandPhoton40_Eta1p5_v1', 
        'HLT_HIIslandPhoton40_Eta2p4_Cent30_100_v1', 
        'HLT_HIIslandPhoton40_Eta2p4_Cent50_100_v1', 
        'HLT_HIIslandPhoton40_Eta2p4_v1', 
        'HLT_HIIslandPhoton40_Eta3p1_Cent30_100_v1', 
        'HLT_HIIslandPhoton40_Eta3p1_Cent50_100_v1', 
        'HLT_HIIslandPhoton40_Eta3p1_v1', 
        'HLT_HIIslandPhoton50_Eta1p5_v1', 
        'HLT_HIIslandPhoton50_Eta2p4_v1', 
        'HLT_HIIslandPhoton50_Eta3p1_v1', 
        'HLT_HIIslandPhoton60_Eta1p5_v1', 
        'HLT_HIIslandPhoton60_Eta2p4_v1', 
        'HLT_HIIslandPhoton60_Eta3p1_v1', 
        'HLT_HIL1DoubleMu0_v1', 
        'HLT_HIL1DoubleMu10_v1', 
        'HLT_HIL1DoubleMuOpen_Centrality_30_100_v1', 
        'HLT_HIL1DoubleMuOpen_Centrality_40_100_v1', 
        'HLT_HIL1DoubleMuOpen_Centrality_50_100_v1', 
        'HLT_HIL1DoubleMuOpen_MAXdR2p0_v1', 
        'HLT_HIL1DoubleMuOpen_MAXdR3p5_v1', 
        'HLT_HIL1DoubleMuOpen_OS_Centrality_30_100_v1', 
        'HLT_HIL1DoubleMuOpen_OS_Centrality_40_100_v1', 
        'HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1', 
        'HLT_HIL1DoubleMuOpen_OS_er1p6_v1', 
        'HLT_HIL1DoubleMuOpen_OS_v1', 
        'HLT_HIL1DoubleMuOpen_SS_v1', 
        'HLT_HIL1DoubleMuOpen_er1p6_v1', 
        'HLT_HIL1DoubleMuOpen_v1', 
        'HLT_HIL1Mu3Eta2p5_Ele10Gsf_v1', 
        'HLT_HIL1Mu3Eta2p5_Ele15Gsf_v1', 
        'HLT_HIL1Mu3Eta2p5_Ele20Gsf_v1', 
        'HLT_HIL1Mu3_Centrality_70_100_v1', 
        'HLT_HIL1Mu3_Centrality_80_100_v1', 
        'HLT_HIL1Mu3_v1', 
        'HLT_HIL1Mu5Eta2p5_Ele10Gsf_v1', 
        'HLT_HIL1Mu5Eta2p5_Ele15Gsf_v1', 
        'HLT_HIL1Mu5Eta2p5_Ele20Gsf_v1', 
        'HLT_HIL1Mu5_v1', 
        'HLT_HIL1Mu7Eta2p5_Ele10Gsf_v1', 
        'HLT_HIL1Mu7Eta2p5_Ele15Gsf_v1', 
        'HLT_HIL1Mu7Eta2p5_Ele20Gsf_v1', 
        'HLT_HIL1Mu7_v1', 
        'HLT_HIL1MuOpen_Centrality_70_100_v1', 
        'HLT_HIL1MuOpen_Centrality_80_100_v1', 
        'HLT_HIL1NotBptxOR_v1', 
        'HLT_HIL1UnpairedBunchBptxMinus_v1', 
        'HLT_HIL1UnpairedBunchBptxPlus_v1', 
        'HLT_HIL1_ETT10_ETTAsym50_MinimumBiasHF1_OR_BptxAND_v1', 
        'HLT_HIL1_ETT60_ETTAsym65_MinimumBiasHF2_OR_PixelTracks10_v1', 
        'HLT_HIL1_ETT65_ETTAsym80_MinimumBiasHF2_OR_PixelTracks10_v1', 
        'HLT_HIL1_ETT8_ETTAsym50_MinimumBiasHF1_OR_BptxAND_v1', 
        'HLT_HIL1_ZDC_AND_OR_MinimumBiasHF1_AND_BptxAND_v1', 
        'HLT_HIL1_ZDC_AND_OR_MinimumBiasHF2_AND_BptxAND_v1', 
        'HLT_HIL2DoubleMuOpen_v1', 
        'HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1', 
        'HLT_HIL2Mu12_v1', 
        'HLT_HIL2Mu15_v1', 
        'HLT_HIL2Mu20_v1', 
        'HLT_HIL2Mu3_NHitQ10_v1', 
        'HLT_HIL2Mu3_NHitQ15_tagging_v1', 
        'HLT_HIL2Mu3_NHitQ15_v1', 
        'HLT_HIL2Mu3_v1', 
        'HLT_HIL2Mu5_NHitQ10_v1', 
        'HLT_HIL2Mu5_NHitQ15_tagging_v1', 
        'HLT_HIL2Mu5_NHitQ15_v1', 
        'HLT_HIL2Mu5_v1', 
        'HLT_HIL2Mu7_NHitQ10_v1', 
        'HLT_HIL2Mu7_NHitQ15_tagging_v1', 
        'HLT_HIL2Mu7_NHitQ15_v1', 
        'HLT_HIL2Mu7_v1', 
        'HLT_HIL2_L1DoubleMu10_v1', 
        'HLT_HIL3DoubleMuOpen_JpsiPsi_v1', 
        'HLT_HIL3DoubleMuOpen_M60120_v1', 
        'HLT_HIL3DoubleMuOpen_Upsi_v1', 
        'HLT_HIL3DoubleMuOpen_v1', 
        'HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1', 
        'HLT_HIL3Mu0_L2Mu0_v1', 
        'HLT_HIL3Mu12_v1', 
        'HLT_HIL3Mu15_v1', 
        'HLT_HIL3Mu20_v1', 
        'HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v1', 
        'HLT_HIL3Mu2p5NHitQ10_L2Mu2_v1', 
        'HLT_HIL3Mu2p5_L1DoubleMu0_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v1', 
        'HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1', 
        'HLT_HIL3Mu3_EG10HECut_v1', 
        'HLT_HIL3Mu3_EG15HECut_v1', 
        'HLT_HIL3Mu3_EG20HECut_v1', 
        'HLT_HIL3Mu3_EG30HECut_v1', 
        'HLT_HIL3Mu3_L1DoubleMu0_v1', 
        'HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1', 
        'HLT_HIL3Mu3_L1DoubleMuOpen_v1', 
        'HLT_HIL3Mu3_L1TripleMuOpen_v1', 
        'HLT_HIL3Mu3_NHitQ10_tagging_v1', 
        'HLT_HIL3Mu3_NHitQ10_v1', 
        'HLT_HIL3Mu3_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet100Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet100Eta2p1_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet40Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet40Eta2p1_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet60Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet60Eta2p1_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet80Eta2p1_FilterDr_v1', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet80Eta2p1_v1', 
        'HLT_HIL3Mu5_EG10HECut_v1', 
        'HLT_HIL3Mu5_EG15HECut_v1', 
        'HLT_HIL3Mu5_EG20HECut_v1', 
        'HLT_HIL3Mu5_EG30HECut_v1', 
        'HLT_HIL3Mu5_NHitQ10_tagging_v1', 
        'HLT_HIL3Mu5_NHitQ10_v1', 
        'HLT_HIL3Mu5_v1', 
        'HLT_HIL3Mu7_EG10HECut_v1', 
        'HLT_HIL3Mu7_EG15HECut_v1', 
        'HLT_HIL3Mu7_EG20HECut_v1', 
        'HLT_HIL3Mu7_EG30HECut_v1', 
        'HLT_HIL3Mu7_NHitQ10_tagging_v1', 
        'HLT_HIL3Mu7_NHitQ10_v1', 
        'HLT_HIL3Mu7_v1', 
        'HLT_HIL3_L1DoubleMu10_v1', 
        'HLT_HILcPPTrackingGlobal_Dpt20_v1', 
        'HLT_HILcPPTrackingGlobal_Dpt30_v1', 
        'HLT_HILcPPTrackingGlobal_Dpt40_v1', 
        'HLT_HILcPPTrackingGlobal_Dpt50_v1', 
        'HLT_HILcPPTrackingGlobal_Dpt60_v1', 
        'HLT_HIMinimumBiasHFOR_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part0_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part10_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part11_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part12_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part13_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part14_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part15_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part16_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part17_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part18_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part19_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part1_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part20_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part21_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part22_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part23_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part2_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part3_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part4_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part5_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part6_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part7_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part8_v1', 
        'HLT_HIMinimumBiasRF_SinglePixelTrack_part9_v1', 
        'HLT_HIMinimumBiasRF_part0_v1', 
        'HLT_HIMinimumBiasRF_part10_v1', 
        'HLT_HIMinimumBiasRF_part11_v1', 
        'HLT_HIMinimumBiasRF_part12_v1', 
        'HLT_HIMinimumBiasRF_part13_v1', 
        'HLT_HIMinimumBiasRF_part14_v1', 
        'HLT_HIMinimumBiasRF_part15_v1', 
        'HLT_HIMinimumBiasRF_part16_v1', 
        'HLT_HIMinimumBiasRF_part17_v1', 
        'HLT_HIMinimumBiasRF_part18_v1', 
        'HLT_HIMinimumBiasRF_part19_v1', 
        'HLT_HIMinimumBiasRF_part1_v1', 
        'HLT_HIMinimumBiasRF_part20_v1', 
        'HLT_HIMinimumBiasRF_part21_v1', 
        'HLT_HIMinimumBiasRF_part22_v1', 
        'HLT_HIMinimumBiasRF_part23_v1', 
        'HLT_HIMinimumBiasRF_part2_v1', 
        'HLT_HIMinimumBiasRF_part3_v1', 
        'HLT_HIMinimumBiasRF_part4_v1', 
        'HLT_HIMinimumBiasRF_part5_v1', 
        'HLT_HIMinimumBiasRF_part6_v1', 
        'HLT_HIMinimumBiasRF_part7_v1', 
        'HLT_HIMinimumBiasRF_part8_v1', 
        'HLT_HIMinimumBiasRF_part9_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part0_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part10_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part11_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part12_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part13_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part14_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part15_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part16_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part17_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part18_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part19_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part1_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part2_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part3_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part4_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part5_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part6_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part7_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part8_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part9_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part0_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part10_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part11_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part12_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part13_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part14_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part15_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part16_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part17_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part18_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part19_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part1_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part2_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part3_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part4_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part5_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part6_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part7_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part8_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part9_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part0_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part10_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part11_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part12_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part13_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part14_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part15_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part16_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part17_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part18_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part19_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part1_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part2_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part3_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part4_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part5_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part6_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part7_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part8_v1', 
        'HLT_HIMinimumBias_SinglePixelTrack_part9_v1', 
        'HLT_HIMinimumBias_part0_v1', 
        'HLT_HIMinimumBias_part10_v1', 
        'HLT_HIMinimumBias_part10_v6', 
        'HLT_HIMinimumBias_part11_v1', 
        'HLT_HIMinimumBias_part11_v6', 
        'HLT_HIMinimumBias_part12_v1', 
        'HLT_HIMinimumBias_part12_v7', 
        'HLT_HIMinimumBias_part13_v1', 
        'HLT_HIMinimumBias_part13_v7', 
        'HLT_HIMinimumBias_part14_v1', 
        'HLT_HIMinimumBias_part14_v8', 
        'HLT_HIMinimumBias_part15_v1', 
        'HLT_HIMinimumBias_part15_v8', 
        'HLT_HIMinimumBias_part16_v1', 
        'HLT_HIMinimumBias_part16_v9', 
        'HLT_HIMinimumBias_part17_v1', 
        'HLT_HIMinimumBias_part17_v9', 
        'HLT_HIMinimumBias_part18_v1', 
        'HLT_HIMinimumBias_part18_v10', 
        'HLT_HIMinimumBias_part18_v11', 
        'HLT_HIMinimumBias_part19_v1', 
        'HLT_HIMinimumBias_part19_v10', 
        'HLT_HIMinimumBias_part19_v11', 
        'HLT_HIMinimumBias_part1_v1', 
        'HLT_HIMinimumBias_part20_v1', 
        'HLT_HIMinimumBias_part21_v1', 
        'HLT_HIMinimumBias_part22_v1', 
        'HLT_HIMinimumBias_part23_v1', 
        'HLT_HIMinimumBias_part24_v1', 
        'HLT_HIMinimumBias_part25_v1', 
        'HLT_HIMinimumBias_part2_v1', 
        'HLT_HIMinimumBias_part2_v2', 
        'HLT_HIMinimumBias_part3_v1', 
        'HLT_HIMinimumBias_part3_v2', 
        'HLT_HIMinimumBias_part4_v1', 
        'HLT_HIMinimumBias_part4_v3', 
        'HLT_HIMinimumBias_part5_v1', 
        'HLT_HIMinimumBias_part5_v3', 
        'HLT_HIMinimumBias_part6_v1', 
        'HLT_HIMinimumBias_part6_v4', 
        'HLT_HIMinimumBias_part7_v1', 
        'HLT_HIMinimumBias_part7_v4', 
        'HLT_HIMinimumBias_part8_v1', 
        'HLT_HIMinimumBias_part8_v5', 
        'HLT_HIMinimumBias_part9_v1', 
        'HLT_HIMinimumBias_part9_v5', 
        'HLT_HIPhysicsForZS_v1', 
        'HLT_HIPhysics_v1', 
        'HLT_HIPuAK4CaloJet100Eta2p4_CSVv2WP0p75_v1', 
        'HLT_HIPuAK4CaloJet100Eta2p4_CSVv2WP0p8_v1', 
        'HLT_HIPuAK4CaloJet100Eta2p4_DeepCSV0p4_v1', 
        'HLT_HIPuAK4CaloJet100Eta2p4_DeepCSV0p71_v1', 
        'HLT_HIPuAK4CaloJet100Eta5p1_Centrality_30_100_v1', 
        'HLT_HIPuAK4CaloJet100Eta5p1_Centrality_50_100_v1', 
        'HLT_HIPuAK4CaloJet100Eta5p1_v1', 
        'HLT_HIPuAK4CaloJet100Fwd_v1', 
        'HLT_HIPuAK4CaloJet100_35_Eta0p7_v1', 
        'HLT_HIPuAK4CaloJet100_35_Eta1p1_v1', 
        'HLT_HIPuAK4CaloJet120Eta5p1_v1', 
        'HLT_HIPuAK4CaloJet120Fwd_v1', 
        'HLT_HIPuAK4CaloJet40Eta5p1_Centrality_30_100_v1', 
        'HLT_HIPuAK4CaloJet40Eta5p1_Centrality_50_100_v1', 
        'HLT_HIPuAK4CaloJet40Eta5p1_v1', 
        'HLT_HIPuAK4CaloJet40Fwd_v1', 
        'HLT_HIPuAK4CaloJet60Eta2p4_CSVv2WP0p75_v1', 
        'HLT_HIPuAK4CaloJet60Eta2p4_CSVv2WP0p8_v1', 
        'HLT_HIPuAK4CaloJet60Eta2p4_DeepCSV0p4_v1', 
        'HLT_HIPuAK4CaloJet60Eta2p4_DeepCSV0p71_v1', 
        'HLT_HIPuAK4CaloJet60Eta5p1_Centrality_30_100_v1', 
        'HLT_HIPuAK4CaloJet60Eta5p1_Centrality_50_100_v1', 
        'HLT_HIPuAK4CaloJet60Eta5p1_v1', 
        'HLT_HIPuAK4CaloJet60Fwd_v1', 
        'HLT_HIPuAK4CaloJet80Eta2p4_CSVv2WP0p75_v1', 
        'HLT_HIPuAK4CaloJet80Eta2p4_CSVv2WP0p8_v1', 
        'HLT_HIPuAK4CaloJet80Eta2p4_DeepCSV0p4_v1', 
        'HLT_HIPuAK4CaloJet80Eta2p4_DeepCSV0p71_v1', 
        'HLT_HIPuAK4CaloJet80Eta5p1_Centrality_30_100_v1', 
        'HLT_HIPuAK4CaloJet80Eta5p1_Centrality_50_100_v1', 
        'HLT_HIPuAK4CaloJet80Eta5p1_v1', 
        'HLT_HIPuAK4CaloJet80Fwd_v1', 
        'HLT_HIPuAK4CaloJet80_35_Eta0p7_v1', 
        'HLT_HIPuAK4CaloJet80_35_Eta1p1_v1', 
        'HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v1', 
        'HLT_HIRandom_v1', 
        'HLT_HIUPC_DoubleEG2_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG2_BptxAND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG2_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG2_NotMBHF2AND_SinglePixelTrack_v1', 
        'HLT_HIUPC_DoubleEG2_NotMBHF2AND_v1', 
        'HLT_HIUPC_DoubleEG2_NotMBHF2OR_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG2_NotMBHF2OR_SinglePixelTrack_v1', 
        'HLT_HIUPC_DoubleEG2_NotMBHF2OR_v1', 
        'HLT_HIUPC_DoubleEG5_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG5_BptxAND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG5_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG5_NotMBHF2AND_SinglePixelTrack_v1', 
        'HLT_HIUPC_DoubleEG5_NotMBHF2AND_v1', 
        'HLT_HIUPC_DoubleEG5_NotMBHF2OR_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleEG5_NotMBHF2OR_SinglePixelTrack_v1', 
        'HLT_HIUPC_DoubleEG5_NotMBHF2OR_v1', 
        'HLT_HIUPC_DoubleMu0_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleMu0_NotMBHF2AND_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleMu0_NotMBHF2AND_v1', 
        'HLT_HIUPC_DoubleMu0_NotMBHF2OR_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleMu0_NotMBHF2OR_v1', 
        'HLT_HIUPC_DoubleMuOpen_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleMuOpen_NotMBHF2OR_MaxPixelTrack_v1', 
        'HLT_HIUPC_DoubleMuOpen_NotMBHF2OR_v1', 
        'HLT_HIUPC_ETT5_Asym50_NotMBHF2OR_SinglePixelTrack_v1', 
        'HLT_HIUPC_ETT5_Asym50_NotMBHF2OR_v1', 
        'HLT_HIUPC_Mu8_Mu13_MaxPixelTrack_v1', 
        'HLT_HIUPC_Mu8_Mu13_v1', 
        'HLT_HIUPC_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_NotMBHF2AND_SinglePixelTrack_v1', 
        'HLT_HIUPC_NotMBHF2AND_v1', 
        'HLT_HIUPC_NotMBHF2OR_BptxAND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_NotMBHF2OR_BptxAND_SinglePixelTrack_v1', 
        'HLT_HIUPC_SingleEG3_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG3_BptxAND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG3_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG3_NotMBHF2AND_SinglePixelTrack_v1', 
        'HLT_HIUPC_SingleEG3_NotMBHF2AND_v1', 
        'HLT_HIUPC_SingleEG3_NotMBHF2OR_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG3_NotMBHF2OR_SinglePixelTrack_v1', 
        'HLT_HIUPC_SingleEG3_NotMBHF2OR_v1', 
        'HLT_HIUPC_SingleEG5_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG5_BptxAND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG5_NotMBHF2AND_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG5_NotMBHF2AND_SinglePixelTrack_v1', 
        'HLT_HIUPC_SingleEG5_NotMBHF2AND_v1', 
        'HLT_HIUPC_SingleEG5_NotMBHF2OR_SinglePixelTrack_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleEG5_NotMBHF2OR_SinglePixelTrack_v1', 
        'HLT_HIUPC_SingleEG5_NotMBHF2OR_v1', 
        'HLT_HIUPC_SingleMu0_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMu0_NotMBHF2AND_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMu0_NotMBHF2AND_v1', 
        'HLT_HIUPC_SingleMu0_NotMBHF2OR_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMu0_NotMBHF2OR_v1', 
        'HLT_HIUPC_SingleMu3_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMu3_NotMBHF2OR_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMu3_NotMBHF2OR_v1', 
        'HLT_HIUPC_SingleMuOpen_BptxAND_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMuOpen_NotMBHF2AND_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v1', 
        'HLT_HIUPC_SingleMuOpen_NotMBHF2OR_MaxPixelTrack_v1', 
        'HLT_HIUPC_SingleMuOpen_NotMBHF2OR_v1', 
        'HLT_HIUPC_ZeroBias_MaxPixelCluster_v1', 
        'HLT_HIUPC_ZeroBias_SinglePixelTrack_v1', 
        'HLT_HIZeroBias_FirstCollisionAfterAbortGap_v1', 
        'HLT_HIZeroBias_v1', 
        'HLT_HI_CastorMuon_v1', 
        'HLT_HMinimumBias_part12_v1', 
        'HLT_HMinimumBias_part18_v1', 
        'HLT_HcalCalibration_v5', 
        'HLT_Mu8_Mu13_MaxPixelTrack_v1', 
        'HLT_Mu8_Mu13_v1', 
        'HLT_ZDCAND_MBHF1AND_BptxAND_v1', 
        'HLT_ZDCAND_MBHF1OR_BptxAND_v1', 
        'HLT_ZDCAND_MBHF2AND_BptxAND_v1', 
        'HLT_ZDCAND_MBHF2OR_BptxAND_v1', 
        'HLT_ZDCM_BptxAND_v1', 
        'HLT_ZDCM_ZDCP_BptxAND_v1', 
        'HLT_ZDCM_ZDCP_MBHF1AND_BptxAND_v1', 
        'HLT_ZDCM_v1', 
        'HLT_ZDCOR_MBHF1OR_BptxAND_v1', 
        'HLT_ZDCOR_MBHF2OR_BptxAND_v1', 
        'HLT_ZDCP_BptxAND_v1', 
        'HLT_ZDCP_v1'
     ) ),
    genEventInfo = cms.InputTag(""),
    hltresults = cms.InputTag("TriggerResults","","HLT"),
    l1dummyBranches = cms.untracked.vstring( (
        'L1_AlwaysTrue', 
        'L1_BPTX_AND_Ref1_VME', 
        'L1_BPTX_AND_Ref3_VME', 
        'L1_BPTX_AND_Ref4_VME', 
        'L1_BPTX_BeamGas_B1_VME', 
        'L1_BPTX_BeamGas_B2_VME', 
        'L1_BPTX_BeamGas_Ref1_VME', 
        'L1_BPTX_BeamGas_Ref2_VME', 
        'L1_BPTX_NotOR_VME', 
        'L1_BPTX_OR_Ref3_VME', 
        'L1_BPTX_OR_Ref4_VME', 
        'L1_BPTX_RefAND_VME', 
        'L1_BptxMinus', 
        'L1_BptxMinus_NotBptxPlus', 
        'L1_BptxOR', 
        'L1_BptxPlus', 
        'L1_BptxPlus_NotBptxMinus', 
        'L1_BptxXOR', 
        'L1_Castor1', 
        'L1_CastorHighJet', 
        'L1_CastorHighJet_BptxAND', 
        'L1_CastorHighJet_MinimumBiasHF1_OR_BptxAND', 
        'L1_CastorHighJet_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_CastorHighJet_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_CastorHighJet_OR_MinimumBiasHF1_AND_BptxAND', 
        'L1_CastorHighJet_OR_MinimumBiasHF2_AND_BptxAND', 
        'L1_CastorMediumJet', 
        'L1_CastorMediumJet_BptxAND', 
        'L1_CastorMediumJet_MinimumBiasHF1_OR_BptxAND', 
        'L1_CastorMediumJet_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_CastorMediumJet_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_CastorMediumJet_SingleEG5_MinimumBiasHF1_OR_BptxAND', 
        'L1_CastorMediumJet_SingleMu0_MinimumBiasHF1_OR_BptxAND', 
        'L1_CastorMuon', 
        'L1_CastorMuon_BptxAND', 
        'L1_Centrality_20_100_MinimumBiasHF1_AND_BptxAND', 
        'L1_Centrality_30_100', 
        'L1_Centrality_30_100_MinimumBiasHF1_AND_BptxAND', 
        'L1_Centrality_50_100', 
        'L1_Centrality_Saturation', 
        'L1_DoubleEG10_BptxAND', 
        'L1_DoubleEG2', 
        'L1_DoubleEG2_BptxAND', 
        'L1_DoubleEG2_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_DoubleEG2_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_DoubleEG5', 
        'L1_DoubleEG5_BptxAND', 
        'L1_DoubleEG5_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_DoubleEG5_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_DoubleEG8_BptxAND', 
        'L1_DoubleJet16And12_MidEta2p7_BptxAND', 
        'L1_DoubleJet16And12_MidEta2p7_Centrality_30_100_BptxAND', 
        'L1_DoubleJet16And12_MidEta2p7_Centrality_50_100_BptxAND', 
        'L1_DoubleJet16And8_MidEta2p7_BptxAND', 
        'L1_DoubleJet16And8_MidEta2p7_Centrality_30_100_BptxAND', 
        'L1_DoubleJet16And8_MidEta2p7_Centrality_50_100_BptxAND', 
        'L1_DoubleJet20And12_MidEta2p7_BptxAND', 
        'L1_DoubleJet20And12_MidEta2p7_Centrality_30_100_BptxAND', 
        'L1_DoubleJet20And12_MidEta2p7_Centrality_50_100_BptxAND', 
        'L1_DoubleJet20And8_MidEta2p7_BptxAND', 
        'L1_DoubleJet20And8_MidEta2p7_Centrality_30_100_BptxAND', 
        'L1_DoubleJet20And8_MidEta2p7_Centrality_50_100_BptxAND', 
        'L1_DoubleJet28And16_MidEta2p7_BptxAND', 
        'L1_DoubleJet28And16_MidEta2p7_Centrality_30_100_BptxAND', 
        'L1_DoubleJet28And16_MidEta2p7_Centrality_50_100_BptxAND', 
        'L1_DoubleMu0', 
        'L1_DoubleMu0_BptxAND', 
        'L1_DoubleMu0_Centrality_10_100_MinimumBiasHF1_AND_BptxAND', 
        'L1_DoubleMu0_Centrality_30_100_MinimumBiasHF1_AND_BptxAND', 
        'L1_DoubleMu0_Centrality_50_100_MinimumBiasHF1_AND_BptxAND', 
        'L1_DoubleMu0_Mass_Min1', 
        'L1_DoubleMu0_MinimumBiasHF1_AND_BptxAND', 
        'L1_DoubleMu0_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_DoubleMu0_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_DoubleMu0_SQ', 
        'L1_DoubleMu0_SQ_OS', 
        'L1_DoubleMu10_BptxAND', 
        'L1_DoubleMuOpen', 
        'L1_DoubleMuOpen_BptxAND', 
        'L1_DoubleMuOpen_Centrality_10_100_BptxAND', 
        'L1_DoubleMuOpen_Centrality_30_100_BptxAND', 
        'L1_DoubleMuOpen_Centrality_40_100_BptxAND', 
        'L1_DoubleMuOpen_Centrality_50_100_BptxAND', 
        'L1_DoubleMuOpen_MaxDr2p0_BptxAND', 
        'L1_DoubleMuOpen_MaxDr2p0_OS_BptxAND', 
        'L1_DoubleMuOpen_MaxDr3p5', 
        'L1_DoubleMuOpen_MaxDr3p5_BptxAND', 
        'L1_DoubleMuOpen_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_DoubleMuOpen_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_DoubleMuOpen_OS', 
        'L1_DoubleMuOpen_OS_BptxAND', 
        'L1_DoubleMuOpen_SS', 
        'L1_DoubleMuOpen_SS_BptxAND', 
        'L1_ETMHF100', 
        'L1_ETMHF100_HTT60er', 
        'L1_ETMHF120', 
        'L1_ETMHF120_HTT60er', 
        'L1_ETT10_ETTAsym50_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT10_ETTAsym55_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT10_ETTAsym60_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT10_ETTAsym65_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT10_ETTAsym70_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT10_ETTAsym80_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT1200', 
        'L1_ETT1600', 
        'L1_ETT2000', 
        'L1_ETT35_NotETT80_BptxAND', 
        'L1_ETT40_NotETT95_BptxAND', 
        'L1_ETT45_NotETT110_BptxAND', 
        'L1_ETT5', 
        'L1_ETT50_ETTAsym40_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym40_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym50_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym50_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym55_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym60_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym60_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym65_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym70_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym70_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym80_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_ETTAsym80_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT50_NotETT120_BptxAND', 
        'L1_ETT55_NotETT130_BptxAND', 
        'L1_ETT5_BptxAND', 
        'L1_ETT5_ETTAsym40_BptxAND', 
        'L1_ETT5_ETTAsym40_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_ETTAsym40_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT5_ETTAsym50_BptxAND', 
        'L1_ETT5_ETTAsym50_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_ETTAsym50_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT5_ETTAsym55_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_ETTAsym60_BptxAND', 
        'L1_ETT5_ETTAsym60_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_ETTAsym60_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT5_ETTAsym65_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_ETTAsym70_BptxAND', 
        'L1_ETT5_ETTAsym70_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_ETTAsym70_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT5_ETTAsym80_BptxAND', 
        'L1_ETT5_ETTAsym80_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_ETTAsym80_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETT5_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT5_NotETT30_BptxAND', 
        'L1_ETT5_NotMinimumBiasHF2_OR', 
        'L1_ETT60_ETTAsym60_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT60_ETTAsym65_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT65_ETTAsym70_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT65_ETTAsym80_MinimumBiasHF2_OR_BptxAND', 
        'L1_ETT8_ETTAsym50_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT8_ETTAsym55_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT8_ETTAsym60_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT8_ETTAsym65_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT8_ETTAsym70_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETT8_ETTAsym80_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETTAsym40', 
        'L1_ETTAsym40_BptxAND', 
        'L1_ETTAsym40_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETTAsym40_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETTAsym50', 
        'L1_ETTAsym50_BptxAND', 
        'L1_ETTAsym50_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETTAsym50_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETTAsym60', 
        'L1_ETTAsym60_BptxAND', 
        'L1_ETTAsym60_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETTAsym60_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETTAsym70', 
        'L1_ETTAsym70_BptxAND', 
        'L1_ETTAsym70_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETTAsym70_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_ETTAsym80', 
        'L1_ETTAsym80_BptxAND', 
        'L1_ETTAsym80_MinimumBiasHF1_OR_BptxAND', 
        'L1_ETTAsym80_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_FirstBunchAfterTrain', 
        'L1_FirstBunchBeforeTrain', 
        'L1_FirstBunchInTrain', 
        'L1_FirstCollisionInOrbit', 
        'L1_FirstCollisionInOrbit_Centrality30_100_BptxAND', 
        'L1_FirstCollisionInTrain', 
        'L1_HCAL_LaserMon_Trig', 
        'L1_HCAL_LaserMon_Veto', 
        'L1_HTT120er', 
        'L1_HTT200er', 
        'L1_HTT280er', 
        'L1_HTT360er', 
        'L1_HTT450er', 
        'L1_IsolatedBunch', 
        'L1_LastBunchInTrain', 
        'L1_LastCollisionInTrain', 
        'L1_MinimumBiasHF0_AND_BptxAND', 
        'L1_MinimumBiasHF0_OR_BptxAND', 
        'L1_MinimumBiasHF1_AND', 
        'L1_MinimumBiasHF1_AND_BptxAND', 
        'L1_MinimumBiasHF1_AND_OR_ETT10_BptxAND', 
        'L1_MinimumBiasHF1_OR', 
        'L1_MinimumBiasHF1_OR_BptxAND', 
        'L1_MinimumBiasHF1_XOR_BptxAND', 
        'L1_MinimumBiasHF2_AND', 
        'L1_MinimumBiasHF2_AND_BptxAND', 
        'L1_MinimumBiasHF2_OR', 
        'L1_MinimumBiasHF2_OR_BptxAND', 
        'L1_NotBptxOR', 
        'L1_NotETT100_MinimumBiasHF1_AND_BptxAND', 
        'L1_NotETT110_MinimumBiasHF1_OR_BptxAND', 
        'L1_NotETT110_MinimumBiasHF2_OR_BptxAND', 
        'L1_NotETT150_MinimumBiasHF1_AND_BptxAND', 
        'L1_NotETT150_MinimumBiasHF1_OR_BptxAND', 
        'L1_NotETT150_MinimumBiasHF2_OR_BptxAND', 
        'L1_NotETT200_MinimumBiasHF1_AND_BptxAND', 
        'L1_NotETT20_MinimumBiasHF1_AND_BptxAND', 
        'L1_NotETT20_MinimumBiasHF1_OR_BptxAND', 
        'L1_NotETT20_MinimumBiasHF2_OR_BptxAND', 
        'L1_NotETT80_MinimumBiasHF1_AND_BptxAND', 
        'L1_NotETT80_MinimumBiasHF1_OR_BptxAND', 
        'L1_NotETT80_MinimumBiasHF2_OR_BptxAND', 
        'L1_NotETT95_MinimumBiasHF1_AND_BptxAND', 
        'L1_NotETT95_MinimumBiasHF1_OR_BptxAND', 
        'L1_NotETT95_MinimumBiasHF2_OR_BptxAND', 
        'L1_NotMinimumBiasHF0_AND_BptxAND', 
        'L1_NotMinimumBiasHF0_AND_BptxAND_TOTEM_1', 
        'L1_NotMinimumBiasHF0_AND_BptxAND_TOTEM_2', 
        'L1_NotMinimumBiasHF0_AND_BptxAND_TOTEM_4', 
        'L1_NotMinimumBiasHF0_OR_BptxAND', 
        'L1_NotMinimumBiasHF0_OR_BptxAND_TOTEM_1', 
        'L1_NotMinimumBiasHF0_OR_BptxAND_TOTEM_2', 
        'L1_NotMinimumBiasHF0_OR_BptxAND_TOTEM_4', 
        'L1_NotMinimumBiasHF1_AND', 
        'L1_NotMinimumBiasHF1_OR', 
        'L1_NotMinimumBiasHF1_OR_BptxAND', 
        'L1_NotMinimumBiasHF2_AND', 
        'L1_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_NotMinimumBiasHF2_OR', 
        'L1_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_SecondBunchInTrain', 
        'L1_SecondLastBunchInTrain', 
        'L1_SingleEG10er2p5', 
        'L1_SingleEG12_BptxAND', 
        'L1_SingleEG12_SingleJet28_MidEta2p7_BptxAND', 
        'L1_SingleEG12_SingleJet28_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG12_SingleJet32_MidEta2p7_BptxAND', 
        'L1_SingleEG12_SingleJet40_MidEta2p7_BptxAND', 
        'L1_SingleEG12_SingleJet44_MidEta2p7_BptxAND', 
        'L1_SingleEG12_SingleJet44_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG12_SingleJet56_MidEta2p7_BptxAND', 
        'L1_SingleEG12_SingleJet56_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG12_SingleJet60_MidEta2p7_BptxAND', 
        'L1_SingleEG12_SingleJet60_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG15_BptxAND', 
        'L1_SingleEG15_Centrality_30_100_BptxAND', 
        'L1_SingleEG15_Centrality_50_100_BptxAND', 
        'L1_SingleEG15_SingleJet28_MidEta2p7_BptxAND', 
        'L1_SingleEG15_SingleJet28_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG15_SingleJet44_MidEta2p7_BptxAND', 
        'L1_SingleEG15_SingleJet44_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG15_SingleJet56_MidEta2p7_BptxAND', 
        'L1_SingleEG15_SingleJet56_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG15_SingleJet60_MidEta2p7_BptxAND', 
        'L1_SingleEG15_SingleJet60_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG15er2p5', 
        'L1_SingleEG21_BptxAND', 
        'L1_SingleEG21_Centrality_30_100_BptxAND', 
        'L1_SingleEG21_Centrality_50_100_BptxAND', 
        'L1_SingleEG26er2p5', 
        'L1_SingleEG3', 
        'L1_SingleEG30_BptxAND', 
        'L1_SingleEG3_BptxAND', 
        'L1_SingleEG3_Centrality_30_100_BptxAND', 
        'L1_SingleEG3_Centrality_50_100_BptxAND', 
        'L1_SingleEG3_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_SingleEG3_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_SingleEG5', 
        'L1_SingleEG50', 
        'L1_SingleEG5_BptxAND', 
        'L1_SingleEG5_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_SingleEG5_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_SingleEG5_SingleJet28_MidEta2p7_BptxAND', 
        'L1_SingleEG5_SingleJet32_MidEta2p7_BptxAND', 
        'L1_SingleEG5_SingleJet40_MidEta2p7_BptxAND', 
        'L1_SingleEG7_BptxAND', 
        'L1_SingleEG7_Centrality_30_100_BptxAND', 
        'L1_SingleEG7_Centrality_50_100_BptxAND', 
        'L1_SingleEG7_SingleJet28_MidEta2p7_BptxAND', 
        'L1_SingleEG7_SingleJet28_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG7_SingleJet32_MidEta2p7_BptxAND', 
        'L1_SingleEG7_SingleJet40_MidEta2p7_BptxAND', 
        'L1_SingleEG7_SingleJet44_MidEta2p7_BptxAND', 
        'L1_SingleEG7_SingleJet44_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG7_SingleJet56_MidEta2p7_BptxAND', 
        'L1_SingleEG7_SingleJet56_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG7_SingleJet60_MidEta2p7_BptxAND', 
        'L1_SingleEG7_SingleJet60_MidEta2p7_MinDr0p4_BptxAND', 
        'L1_SingleEG8er2p5', 
        'L1_SingleIsoEG12_BptxAND', 
        'L1_SingleIsoEG15_BptxAND', 
        'L1_SingleIsoEG21_BptxAND', 
        'L1_SingleIsoEG3_BptxAND', 
        'L1_SingleIsoEG7_BptxAND', 
        'L1_SingleJet120', 
        'L1_SingleJet120_FWD3p0', 
        'L1_SingleJet120er2p5', 
        'L1_SingleJet16_BptxAND', 
        'L1_SingleJet16_Centrality_30_100_BptxAND', 
        'L1_SingleJet16_Centrality_50_100_BptxAND', 
        'L1_SingleJet16_FWD_BptxAND', 
        'L1_SingleJet16_FWD_Centrality_30_100_BptxAND', 
        'L1_SingleJet16_FWD_Centrality_50_100_BptxAND', 
        'L1_SingleJet180er2p5', 
        'L1_SingleJet200', 
        'L1_SingleJet24_BptxAND', 
        'L1_SingleJet24_Centrality_30_100_BptxAND', 
        'L1_SingleJet24_Centrality_50_100_BptxAND', 
        'L1_SingleJet28_BptxAND', 
        'L1_SingleJet28_Centrality_30_100_BptxAND', 
        'L1_SingleJet28_Centrality_50_100_BptxAND', 
        'L1_SingleJet28_FWD_BptxAND', 
        'L1_SingleJet28_FWD_Centrality_30_100_BptxAND', 
        'L1_SingleJet28_FWD_Centrality_50_100_BptxAND', 
        'L1_SingleJet32_BptxAND', 
        'L1_SingleJet32_Centrality_30_100_BptxAND', 
        'L1_SingleJet32_Centrality_50_100_BptxAND', 
        'L1_SingleJet35', 
        'L1_SingleJet35_FWD3p0', 
        'L1_SingleJet35er2p5', 
        'L1_SingleJet36_BptxAND', 
        'L1_SingleJet36_Centrality_30_100_BptxAND', 
        'L1_SingleJet36_Centrality_50_100_BptxAND', 
        'L1_SingleJet36_FWD_BptxAND', 
        'L1_SingleJet36_FWD_Centrality_30_100_BptxAND', 
        'L1_SingleJet36_FWD_Centrality_50_100_BptxAND', 
        'L1_SingleJet40_BptxAND', 
        'L1_SingleJet40_Centrality_30_100_BptxAND', 
        'L1_SingleJet40_Centrality_50_100_BptxAND', 
        'L1_SingleJet44_BptxAND', 
        'L1_SingleJet44_Centrality_30_100_BptxAND', 
        'L1_SingleJet44_Centrality_50_100_BptxAND', 
        'L1_SingleJet44_FWD_BptxAND', 
        'L1_SingleJet44_FWD_Centrality_30_100_BptxAND', 
        'L1_SingleJet44_FWD_Centrality_50_100_BptxAND', 
        'L1_SingleJet48_BptxAND', 
        'L1_SingleJet48_Centrality_30_100_BptxAND', 
        'L1_SingleJet48_Centrality_50_100_BptxAND', 
        'L1_SingleJet56_BptxAND', 
        'L1_SingleJet56_Centrality_30_100_BptxAND', 
        'L1_SingleJet56_Centrality_50_100_BptxAND', 
        'L1_SingleJet56_FWD_BptxAND', 
        'L1_SingleJet56_FWD_Centrality_30_100_BptxAND', 
        'L1_SingleJet56_FWD_Centrality_50_100_BptxAND', 
        'L1_SingleJet60', 
        'L1_SingleJet60_BptxAND', 
        'L1_SingleJet60_Centrality_30_100_BptxAND', 
        'L1_SingleJet60_Centrality_50_100_BptxAND', 
        'L1_SingleJet60_FWD3p0', 
        'L1_SingleJet60er2p5', 
        'L1_SingleJet64_BptxAND', 
        'L1_SingleJet64_Centrality_30_100_BptxAND', 
        'L1_SingleJet64_Centrality_50_100_BptxAND', 
        'L1_SingleJet64_FWD_BptxAND', 
        'L1_SingleJet64_FWD_Centrality_30_100_BptxAND', 
        'L1_SingleJet64_FWD_Centrality_50_100_BptxAND', 
        'L1_SingleJet72_BptxAND', 
        'L1_SingleJet8', 
        'L1_SingleJet80_BptxAND', 
        'L1_SingleJet8_BptxAND', 
        'L1_SingleJet8_Centrality_30_100_BptxAND', 
        'L1_SingleJet8_Centrality_50_100_BptxAND', 
        'L1_SingleJet8_FWD_BptxAND', 
        'L1_SingleJet8_FWD_Centrality_30_100_BptxAND', 
        'L1_SingleJet8_FWD_Centrality_50_100_BptxAND', 
        'L1_SingleJet90', 
        'L1_SingleJet90_FWD3p0', 
        'L1_SingleJet90er2p5', 
        'L1_SingleMu0', 
        'L1_SingleMu0_BMTF', 
        'L1_SingleMu0_BptxAND', 
        'L1_SingleMu0_DQ', 
        'L1_SingleMu0_EMTF', 
        'L1_SingleMu0_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_SingleMu0_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_SingleMu0_OMTF', 
        'L1_SingleMu12', 
        'L1_SingleMu12_BptxAND', 
        'L1_SingleMu12_DQ_BMTF', 
        'L1_SingleMu12_DQ_EMTF', 
        'L1_SingleMu12_DQ_OMTF', 
        'L1_SingleMu12_MinimumBiasHF1_AND_BptxAND', 
        'L1_SingleMu12_SingleEG7_BptxAND', 
        'L1_SingleMu16', 
        'L1_SingleMu16_BptxAND', 
        'L1_SingleMu16_MinimumBiasHF1_AND_BptxAND', 
        'L1_SingleMu22', 
        'L1_SingleMu22_BMTF', 
        'L1_SingleMu22_EMTF', 
        'L1_SingleMu22_OMTF', 
        'L1_SingleMu3', 
        'L1_SingleMu3Open_BptxAND', 
        'L1_SingleMu3_BptxAND', 
        'L1_SingleMu3_Centrality_70_100_BptxAND', 
        'L1_SingleMu3_Centrality_80_100_BptxAND', 
        'L1_SingleMu3_MinimumBiasHF1_AND_BptxAND', 
        'L1_SingleMu3_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_SingleMu3_SingleEG12_BptxAND', 
        'L1_SingleMu3_SingleEG15_BptxAND', 
        'L1_SingleMu3_SingleEG20_BptxAND', 
        'L1_SingleMu3_SingleEG30_BptxAND', 
        'L1_SingleMu3_SingleJet28_MidEta2p7_BptxAND', 
        'L1_SingleMu3_SingleJet32_MidEta2p7_BptxAND', 
        'L1_SingleMu3_SingleJet40_MidEta2p7_BptxAND', 
        'L1_SingleMu5', 
        'L1_SingleMu5_BptxAND', 
        'L1_SingleMu5_MinimumBiasHF1_AND_BptxAND', 
        'L1_SingleMu5_SingleEG10_BptxAND', 
        'L1_SingleMu5_SingleEG12_BptxAND', 
        'L1_SingleMu5_SingleEG15_BptxAND', 
        'L1_SingleMu5_SingleEG20_BptxAND', 
        'L1_SingleMu7', 
        'L1_SingleMu7_BptxAND', 
        'L1_SingleMu7_DQ', 
        'L1_SingleMu7_MinimumBiasHF1_AND_BptxAND', 
        'L1_SingleMu7_SingleEG10_BptxAND', 
        'L1_SingleMu7_SingleEG12_BptxAND', 
        'L1_SingleMu7_SingleEG15_BptxAND', 
        'L1_SingleMu7_SingleEG7_BptxAND', 
        'L1_SingleMuCosmics', 
        'L1_SingleMuCosmics_BMTF', 
        'L1_SingleMuCosmics_EMTF', 
        'L1_SingleMuCosmics_OMTF', 
        'L1_SingleMuOpen', 
        'L1_SingleMuOpen_BptxAND', 
        'L1_SingleMuOpen_Centrality_70_100_BptxAND', 
        'L1_SingleMuOpen_Centrality_70_100_MinimumBiasHF1_AND_BptxAND', 
        'L1_SingleMuOpen_Centrality_80_100_BptxAND', 
        'L1_SingleMuOpen_Centrality_80_100_MinimumBiasHF1_AND_BptxAND', 
        'L1_SingleMuOpen_NotMinimumBiasHF2_AND_BptxAND', 
        'L1_SingleMuOpen_NotMinimumBiasHF2_OR_BptxAND', 
        'L1_SingleMuOpen_SingleEG15_BptxAND', 
        'L1_SingleMuOpen_SingleJet28_MidEta2p7_BptxAND', 
        'L1_SingleMuOpen_SingleJet44_MidEta2p7_BptxAND', 
        'L1_SingleMuOpen_SingleJet56_MidEta2p7_BptxAND', 
        'L1_SingleMuOpen_SingleJet64_MidEta2p7_BptxAND', 
        'L1_TOTEM_1', 
        'L1_TOTEM_2', 
        'L1_TOTEM_3', 
        'L1_TOTEM_4', 
        'L1_UnpairedBunchBptxMinus', 
        'L1_UnpairedBunchBptxPlus', 
        'L1_ZDCM', 
        'L1_ZDCM_BptxAND', 
        'L1_ZDCM_ZDCP_BptxAND', 
        'L1_ZDCP', 
        'L1_ZDCP_BptxAND', 
        'L1_ZDC_AND_OR_MinimumBiasHF1_AND_BptxAND', 
        'L1_ZDC_AND_OR_MinimumBiasHF1_OR_BptxAND', 
        'L1_ZDC_AND_OR_MinimumBiasHF2_AND_BptxAND', 
        'L1_ZDC_AND_OR_MinimumBiasHF2_OR_BptxAND', 
        'L1_ZDC_OR_OR_MinimumBiasHF1_OR_BptxAND', 
        'L1_ZDC_OR_OR_MinimumBiasHF2_OR_BptxAND', 
        'L1_ZeroBias', 
        'L1_ZeroBias_copy'
     ) ),
    l1results = cms.InputTag("gtStage2Digis"),
    mctruth = cms.InputTag(""),
    simhits = cms.InputTag("")
)


process.hltobject = cms.EDAnalyzer("TriggerObjectAnalyzer",
    processName = cms.string('HLT'),
    treeName = cms.string('JetTriggers'),
    triggerEvent = cms.InputTag("hltTriggerSummaryAOD","","HLT"),
    triggerNames = cms.vstring(
        'HLT_HIL1DoubleMuOpen_v', 
        'HLT_HIL1DoubleMuOpen_OS_Centrality_40_100_v', 
        'HLT_HIL1DoubleMuOpen_Centrality_50_100_v', 
        'HLT_HIL1DoubleMu10_v', 
        'HLT_HIL2_L1DoubleMu10_v', 
        'HLT_HIL3_L1DoubleMu10_v', 
        'HLT_HIL2DoubleMuOpen_v', 
        'HLT_HIL3DoubleMuOpen_v', 
        'HLT_HIL3DoubleMuOpen_M60120_v', 
        'HLT_HIL3DoubleMuOpen_JpsiPsi_v', 
        'HLT_HIL3DoubleMuOpen_Upsi_v', 
        'HLT_HIL3Mu0_L2Mu0_v', 
        'HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v', 
        'HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v', 
        'HLT_HIL3Mu3_L1TripleMuOpen_v', 
        'HLT_HIL1MuOpen_Centrality_70_100_v', 
        'HLT_HIL1MuOpen_Centrality_80_100_v', 
        'HLT_HIL2Mu3_NHitQ15_v', 
        'HLT_HIL2Mu5_NHitQ15_v', 
        'HLT_HIL2Mu7_NHitQ15_v', 
        'HLT_HIL3Mu12_v', 
        'HLT_HIL3Mu15_v', 
        'HLT_HIL3Mu20_v', 
        'HLT_HIL3Mu3_NHitQ10_v', 
        'HLT_HIL3Mu5_NHitQ10_v', 
        'HLT_HIL3Mu7_NHitQ10_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet40Eta2p1_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet60Eta2p1_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet80Eta2p1_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet100Eta2p1_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet40Eta2p1_FilterDr_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet60Eta2p1_FilterDr_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet80Eta2p1_FilterDr_v', 
        'HLT_HIL3Mu3Eta2p5_PuAK4CaloJet100Eta2p1_FilterDr_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet40Eta2p1_FilterDr_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet60Eta2p1_FilterDr_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet80Eta2p1_FilterDr_v', 
        'HLT_HIL3Mu5Eta2p5_PuAK4CaloJet100Eta2p1_FilterDr_v', 
        'HLT_HIPuAK4CaloJet40Eta5p1_v', 
        'HLT_HIPuAK4CaloJet60Eta5p1_v', 
        'HLT_HIPuAK4CaloJet80Eta5p1_v', 
        'HLT_HIPuAK4CaloJet100Eta5p1_v', 
        'HLT_HIPuAK4CaloJet120Eta5p1_v', 
        'HLT_HIPuAK4CaloJet40Fwd_v', 
        'HLT_HIPuAK4CaloJet60Fwd_v', 
        'HLT_HIPuAK4CaloJet80Fwd_v', 
        'HLT_HIPuAK4CaloJet100Fwd_v', 
        'HLT_HIPuAK4CaloJet120Fwd_v', 
        'HLT_HIPuAK4CaloJet80_35_Eta1p1_v', 
        'HLT_HIPuAK4CaloJet100_35_Eta1p1_v', 
        'HLT_HIPuAK4CaloJet80_35_Eta0p7_v', 
        'HLT_HIPuAK4CaloJet100_35_Eta0p7_v', 
        'HLT_HIPuAK4CaloJet80_45_45_Eta2p1_v', 
        'HLT_HIPuAK4CaloJet60Eta2p4_DeepCSV0p4_v', 
        'HLT_HIPuAK4CaloJet80Eta2p4_DeepCSV0p4_v', 
        'HLT_HIPuAK4CaloJet100Eta2p4_DeepCSV0p4_v', 
        'HLT_HIPuAK4CaloJet60Eta2p4_CSVv2WP0p75_v', 
        'HLT_HIPuAK4CaloJet80Eta2p4_CSVv2WP0p75_v', 
        'HLT_HIPuAK4CaloJet100Eta2p4_CSVv2WP0p75_v', 
        'HLT_HICsAK4PFJet60Eta1p5_v', 
        'HLT_HICsAK4PFJet80Eta1p5_v', 
        'HLT_HICsAK4PFJet100Eta1p5_v', 
        'HLT_HICsAK4PFJet120Eta1p5_v', 
        'HLT_HIEle10Gsf_v', 
        'HLT_HIEle15Gsf_v', 
        'HLT_HIEle20Gsf_v', 
        'HLT_HIEle30Gsf_v', 
        'HLT_HIEle40Gsf_v', 
        'HLT_HIEle50Gsf_v', 
        'HLT_HIDoubleEle15Gsf_v', 
        'HLT_HIDoubleEle15GsfMass50_v', 
        'HLT_HIEle15Ele10Gsf_v', 
        'HLT_HIEle15Ele10GsfMass50_v', 
        'HLT_HIDoubleEle10Gsf_v', 
        'HLT_HIDoubleEle10GsfMass50_v', 
        'HLT_HIEle10Gsf_PuAK4CaloJet40Eta2p1_v', 
        'HLT_HIEle10Gsf_PuAK4CaloJet60Eta2p1_v', 
        'HLT_HIEle10Gsf_PuAK4CaloJet80Eta2p1_v', 
        'HLT_HIEle10Gsf_PuAK4CaloJet100Eta2p1_v', 
        'HLT_HIEle15Gsf_PuAK4CaloJet40Eta2p1_v', 
        'HLT_HIEle15Gsf_PuAK4CaloJet60Eta2p1_v', 
        'HLT_HIEle15Gsf_PuAK4CaloJet80Eta2p1_v', 
        'HLT_HIEle15Gsf_PuAK4CaloJet100Eta2p1_v', 
        'HLT_HIEle20Gsf_PuAK4CaloJet40Eta2p1_v', 
        'HLT_HIEle20Gsf_PuAK4CaloJet60Eta2p1_v', 
        'HLT_HIEle20Gsf_PuAK4CaloJet80Eta2p1_v', 
        'HLT_HIEle20Gsf_PuAK4CaloJet100Eta2p1_v', 
        'HLT_HIL1Mu5Eta2p5_Ele20Gsf_v', 
        'HLT_HIL1Mu7Eta2p5_Ele20Gsf_v', 
        'HLT_HIGEDPhoton10_v', 
        'HLT_HIGEDPhoton20_v', 
        'HLT_HIGEDPhoton30_v', 
        'HLT_HIGEDPhoton40_v', 
        'HLT_HIGEDPhoton50_v', 
        'HLT_HIGEDPhoton60_v', 
        'HLT_HIGEDPhoton10_EB_v', 
        'HLT_HIGEDPhoton20_EB_v', 
        'HLT_HIGEDPhoton30_EB_v', 
        'HLT_HIGEDPhoton40_EB_v', 
        'HLT_HIGEDPhoton50_EB_v', 
        'HLT_HIGEDPhoton60_EB_v', 
        'HLT_HIIslandPhoton10_Eta2p4_v', 
        'HLT_HIIslandPhoton20_Eta2p4_v', 
        'HLT_HIIslandPhoton30_Eta2p4_v', 
        'HLT_HIIslandPhoton40_Eta2p4_v', 
        'HLT_HIIslandPhoton50_Eta2p4_v', 
        'HLT_HIIslandPhoton60_Eta2p4_v', 
        'HLT_HIIslandPhoton10_Eta1p5_v', 
        'HLT_HIIslandPhoton20_Eta1p5_v', 
        'HLT_HIIslandPhoton30_Eta1p5_v', 
        'HLT_HIIslandPhoton40_Eta1p5_v', 
        'HLT_HIIslandPhoton50_Eta1p5_v', 
        'HLT_HIIslandPhoton60_Eta1p5_v', 
        'HLT_HIPuAK4CaloJet40Eta5p1_Centrality_30_100_v', 
        'HLT_HIPuAK4CaloJet60Eta5p1_Centrality_30_100_v', 
        'HLT_HIPuAK4CaloJet80Eta5p1_Centrality_30_100_v', 
        'HLT_HIPuAK4CaloJet100Eta5p1_Centrality_30_100_v', 
        'HLT_HIPuAK4CaloJet40Eta5p1_Centrality_50_100_v', 
        'HLT_HIPuAK4CaloJet60Eta5p1_Centrality_50_100_v', 
        'HLT_HIPuAK4CaloJet80Eta5p1_Centrality_50_100_v', 
        'HLT_HIPuAK4CaloJet100Eta5p1_Centrality_50_100_v', 
        'HLT_HICsAK4PFJet60Eta1p5_Centrality_30_100_v', 
        'HLT_HICsAK4PFJet80Eta1p5_Centrality_30_100_v', 
        'HLT_HICsAK4PFJet100Eta1p5_Centrality_30_100_v', 
        'HLT_HICsAK4PFJet60Eta1p5_Centrality_50_100_v', 
        'HLT_HICsAK4PFJet80Eta1p5_Centrality_50_100_v', 
        'HLT_HICsAK4PFJet100Eta1p5_Centrality_50_100_v', 
        'HLT_HIGEDPhoton10_Cent30_100_v', 
        'HLT_HIGEDPhoton20_Cent30_100_v', 
        'HLT_HIGEDPhoton30_Cent30_100_v', 
        'HLT_HIGEDPhoton40_Cent30_100_v', 
        'HLT_HIIslandPhoton10_Eta2p4_Cent30_100_v', 
        'HLT_HIIslandPhoton20_Eta2p4_Cent30_100_v', 
        'HLT_HIIslandPhoton30_Eta2p4_Cent30_100_v', 
        'HLT_HIIslandPhoton40_Eta2p4_Cent30_100_v', 
        'HLT_HIGEDPhoton10_Cent50_100_v', 
        'HLT_HIGEDPhoton20_Cent50_100_v', 
        'HLT_HIGEDPhoton30_Cent50_100_v', 
        'HLT_HIGEDPhoton40_Cent50_100_v', 
        'HLT_HIIslandPhoton10_Eta2p4_Cent50_100_v', 
        'HLT_HIIslandPhoton20_Eta2p4_Cent50_100_v', 
        'HLT_HIIslandPhoton30_Eta2p4_Cent50_100_v', 
        'HLT_HIIslandPhoton40_Eta2p4_Cent50_100_v', 
        'HLT_HIFullTracks_Multiplicity2040_HF1OR_v', 
        'HLT_HIFullTracks_Multiplicity4060_v', 
        'HLT_HIFullTracks_Multiplicity6080_v', 
        'HLT_HIFullTracks_Multiplicity80100_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt15_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt20_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt40_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt50_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt60_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt20_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt40_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt50_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt60_v', 
        'HLT_HILcPPTrackingGlobal_Dpt20_v', 
        'HLT_HILcPPTrackingGlobal_Dpt40_v', 
        'HLT_HILcPPTrackingGlobal_Dpt50_v', 
        'HLT_HILcPPTrackingGlobal_Dpt60_v', 
        'HLT_HIFullTracks2018_HighPt18_v', 
        'HLT_HIFullTracks2018_HighPt24_v', 
        'HLT_HIFullTracks2018_HighPt34_v', 
        'HLT_HIFullTracks2018_HighPt45_v', 
        'HLT_HIFullTracks2018_HighPt56_v', 
        'HLT_HIFullTracks2018_HighPt60_v', 
        'HLT_HIUPC_ZeroBias_SinglePixelTrack_v', 
        'HLT_HIUPC_SingleEG5_NotMBHF2AND_SinglePixelTrack_v', 
        'HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v', 
        'HLT_HICastor_MediumJet_NotMBHF2AND_v', 
        'HLT_HIL2Mu3_NHitQ15_tagging_v', 
        'HLT_HIL2Mu5_NHitQ15_tagging_v', 
        'HLT_HIL2Mu7_NHitQ15_tagging_v', 
        'HLT_HIL3Mu3_NHitQ10_tagging_v', 
        'HLT_HIL3Mu5_NHitQ10_tagging_v', 
        'HLT_HIL3Mu7_NHitQ10_tagging_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt15_NoIter10_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt20_NoIter10_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt40_NoIter10_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt50_NoIter10_v', 
        'HLT_HIDmesonPPTrackingGlobal_Dpt60_NoIter10_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt20_NoIter10_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt40_NoIter10_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt50_NoIter10_v', 
        'HLT_HIDsPPTrackingGlobal_Dpt60_NoIter10_v', 
        'HLT_HILcPPTrackingGlobal_Dpt20_NoIter10_v', 
        'HLT_HILcPPTrackingGlobal_Dpt40_NoIter10_v', 
        'HLT_HILcPPTrackingGlobal_Dpt50_NoIter10_v', 
        'HLT_HILcPPTrackingGlobal_Dpt60_NoIter10_v', 
        'HLT_HIFullTracks2018_HighPt18_NoIter10_v', 
        'HLT_HIFullTracks2018_HighPt24_NoIter10_v', 
        'HLT_HIFullTracks2018_HighPt34_NoIter10_v', 
        'HLT_HIFullTracks2018_HighPt45_NoIter10_v', 
        'HLT_HIFullTracks2018_HighPt56_NoIter10_v', 
        'HLT_HIFullTracks2018_HighPt60_NoIter10_v'
    ),
    triggerResults = cms.InputTag("TriggerResults","","HLT")
)


process.inclusiveJetAnalyzer = cms.EDAnalyzer("HiInclusiveJetAnalyzer",
    doGenSym = cms.untracked.bool(False),
    doGenTaus = cms.untracked.bool(False),
    doHiJetID = cms.untracked.bool(True),
    doJetConstituents = cms.untracked.bool(False),
    doLifeTimeTagging = cms.untracked.bool(False),
    doStandardJetID = cms.untracked.bool(False),
    doSubEvent = cms.untracked.bool(False),
    doSubJets = cms.untracked.bool(False),
    doTower = cms.untracked.bool(False),
    doWTARecluster = cms.untracked.bool(False),
    eventInfoTag = cms.InputTag("generator"),
    fillGenJets = cms.untracked.bool(False),
    genjetTag = cms.InputTag("ak4HiGenJets"),
    isMC = cms.untracked.bool(False),
    jetPtMin = cms.double(5.0),
    jetTag = cms.InputTag("ak4PFJets"),
    matchTag = cms.untracked.InputTag("akPu4PFpatJets"),
    rParam = cms.double(0.4),
    towersSrc = cms.InputTag("towerMaker"),
    trackQuality = cms.untracked.string('highPurity'),
    trackTag = cms.InputTag("hiTracks"),
    useHepMC = cms.untracked.bool(False),
    useQuality = cms.untracked.bool(True),
    useRawPt = cms.untracked.bool(False),
    vtxTag = cms.InputTag("hiSelectedVertex")
)


process.l1object = cms.EDAnalyzer("L1UpgradeFlatTreeProducer",
    doEg = cms.bool(True),
    doJet = cms.bool(True),
    doMuon = cms.bool(True),
    doSum = cms.bool(True),
    doTau = cms.bool(True),
    egToken = cms.untracked.InputTag("caloStage2Digis","EGamma"),
    jetToken = cms.untracked.InputTag("caloStage2Digis","Jet"),
    maxL1Upgrade = cms.uint32(60),
    muonToken = cms.untracked.InputTag("gmtStage2Digis","Muon"),
    sumToken = cms.untracked.InputTag("caloStage2Digis","EtSum"),
    tauTokens = cms.untracked.VInputTag(cms.InputTag("caloStage2Digis","Tau"))
)


process.pfTowers = cms.EDAnalyzer("RecHitTreeProducer",
    BasicClusterSrc = cms.InputTag("islandBasicClusters","islandBarrelBasicClusters"),
    EBRecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    EBTreePtMin = cms.untracked.double(15),
    EERecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    EETreePtMin = cms.untracked.double(15),
    FastJetRhoTag = cms.InputTag("kt4CaloJets"),
    FastJetSigmaTag = cms.InputTag("kt4CaloJets"),
    HBHETreePtMin = cms.untracked.double(15),
    HFTreePtMin = cms.untracked.double(15),
    HFlongMin = cms.untracked.double(0.5),
    HFshortMin = cms.untracked.double(0.85),
    HFtowerMin = cms.untracked.double(3),
    JetSrc = cms.InputTag("iterativeConePu5CaloJets"),
    TowerTreePtMin = cms.untracked.double(-99),
    calZDCDigi = cms.bool(True),
    castorRecHitSrc = cms.InputTag("castorreco"),
    doBasicClusters = cms.bool(False),
    doCASTOR = cms.bool(True),
    doEbyEonly = cms.bool(False),
    doEcal = cms.bool(False),
    doFastJet = cms.bool(False),
    doHBHE = cms.bool(False),
    doHF = cms.bool(False),
    doTowers = cms.bool(True),
    doZDCDigi = cms.bool(False),
    doZDCRecHit = cms.bool(False),
    hasVtx = cms.bool(False),
    hcalHBHERecHitSrc = cms.InputTag("hbhereco"),
    hcalHFRecHitSrc = cms.InputTag("hfreco"),
    nZdcTs = cms.int32(10),
    saveBothVtx = cms.bool(False),
    towersSrc = cms.InputTag("PFTowers"),
    useJets = cms.bool(False),
    vtxSrc = cms.InputTag("hiSelectedVertex"),
    zdcDigiSrc = cms.InputTag("hcalDigis"),
    zdcRecHitSrc = cms.InputTag("zdcreco")
)


process.pfTowerspp = cms.EDAnalyzer("RecHitTreeProducer",
    BasicClusterSrc = cms.InputTag("islandBasicClusters","islandBarrelBasicClusters"),
    EBRecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    EBTreePtMin = cms.untracked.double(15),
    EERecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    EETreePtMin = cms.untracked.double(15),
    FastJetRhoTag = cms.InputTag("kt4CaloJets"),
    FastJetSigmaTag = cms.InputTag("kt4CaloJets"),
    HBHETreePtMin = cms.untracked.double(15),
    HFTreePtMin = cms.untracked.double(15),
    HFlongMin = cms.untracked.double(0.5),
    HFshortMin = cms.untracked.double(0.85),
    HFtowerMin = cms.untracked.double(3),
    JetSrc = cms.InputTag("ak4CaloJets"),
    TowerTreePtMin = cms.untracked.double(-99),
    calZDCDigi = cms.bool(True),
    castorRecHitSrc = cms.InputTag("castorreco"),
    doBasicClusters = cms.bool(False),
    doCASTOR = cms.bool(True),
    doEbyEonly = cms.bool(False),
    doEcal = cms.bool(False),
    doFastJet = cms.bool(False),
    doHBHE = cms.bool(False),
    doHF = cms.bool(False),
    doTowers = cms.bool(True),
    doZDCDigi = cms.bool(False),
    doZDCRecHit = cms.bool(False),
    hasVtx = cms.bool(False),
    hcalHBHERecHitSrc = cms.InputTag("hbhereco"),
    hcalHFRecHitSrc = cms.InputTag("hfreco"),
    nZdcTs = cms.int32(10),
    saveBothVtx = cms.bool(False),
    towersSrc = cms.InputTag("PFTowers"),
    useJets = cms.bool(False),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesWithBS"),
    zdcDigiSrc = cms.InputTag("hcalDigis"),
    zdcRecHitSrc = cms.InputTag("zdcreco")
)


process.pfcandAnalyzer = cms.EDAnalyzer("HiPFCandAnalyzer",
    doCaloEnergy = cms.bool(True),
    doJets = cms.bool(False),
    doMC = cms.bool(False),
    doTrackMatching = cms.bool(True),
    genLabel = cms.InputTag("genParticles"),
    genPtMin = cms.double(0.5),
    jetLabel = cms.InputTag("ak5patJets"),
    jetPtMin = cms.double(20.0),
    pfAbsEtaMax = cms.double(5.0),
    pfCandidateLabel = cms.InputTag("particleFlow"),
    pfPtMin = cms.double(0.0),
    skipCharged = cms.bool(False),
    trackLabel = cms.InputTag("generalTracks")
)


process.pfcandAnalyzerCS = cms.EDAnalyzer("HiPFCandAnalyzer",
    doCaloEnergy = cms.bool(False),
    doJets = cms.bool(False),
    doMC = cms.bool(False),
    doTrackMatching = cms.bool(False),
    genLabel = cms.InputTag("genParticles"),
    genPtMin = cms.double(0.5),
    jetLabel = cms.InputTag("ak5patJets"),
    jetPtMin = cms.double(20.0),
    pfAbsEtaMax = cms.double(5.0),
    pfCandidateLabel = cms.InputTag("akCs4PFJets","pfParticlesCs"),
    pfPtMin = cms.double(0.0),
    skipCharged = cms.bool(False),
    trackLabel = cms.InputTag("generalTracks")
)


process.pixelTrack = cms.EDAnalyzer("TrackAnalyzer",
    associatorMap = cms.InputTag("tpRecoAssocHiGeneralTracks"),
    beamSpotSrc = cms.untracked.InputTag("offlineBeamSpot"),
    doMVA = cms.untracked.bool(False),
    doPFMatching = cms.untracked.bool(True),
    doSimTrack = cms.untracked.bool(False),
    doSimVertex = cms.untracked.bool(False),
    fillSimTrack = cms.untracked.bool(False),
    mvaSrc = cms.InputTag("hiGeneralTracks","MVAVals"),
    particleSrc = cms.InputTag("genParticles"),
    pfCandSrc = cms.InputTag("particleFlowTmp"),
    qualityString = cms.untracked.string('highPurity'),
    qualityStrings = cms.untracked.vstring('highPurity'),
    simTrackPtMin = cms.untracked.double(0.1),
    tpEffSrc = cms.untracked.InputTag("mix","MergedTrackTruth"),
    trackPtMin = cms.untracked.double(0.4),
    trackSrc = cms.InputTag("hiConformalPixelTracks"),
    useQuality = cms.untracked.bool(False),
    vertexSrc = cms.VInputTag("hiSelectedVertex")
)


process.ppTrack = cms.EDAnalyzer("TrackAnalyzer",
    associatorMap = cms.InputTag("tpRecoAssocHiGeneralTracks"),
    beamSpotSrc = cms.untracked.InputTag("offlineBeamSpot"),
    doMVA = cms.untracked.bool(True),
    doPFMatching = cms.untracked.bool(True),
    doSimTrack = cms.untracked.bool(False),
    doSimVertex = cms.untracked.bool(False),
    fillSimTrack = cms.untracked.bool(False),
    mvaSrc = cms.InputTag("generalTracks","MVAValues"),
    particleSrc = cms.InputTag("genParticles"),
    pfCandSrc = cms.InputTag("particleFlow"),
    qualityString = cms.untracked.string('highPurity'),
    qualityStrings = cms.untracked.vstring(
        'highPurity', 
        'tight', 
        'loose'
    ),
    simTrackPtMin = cms.untracked.double(0.1),
    tpEffSrc = cms.untracked.InputTag("mix","MergedTrackTruth"),
    trackPtMin = cms.untracked.double(0.01),
    trackSrc = cms.InputTag("generalTracks"),
    useQuality = cms.untracked.bool(False),
    vertexSrc = cms.VInputTag(cms.InputTag("offlinePrimaryVerticesRecovery"))
)


process.rechitanalyzer = cms.EDAnalyzer("RecHitTreeProducer",
    BasicClusterSrc = cms.InputTag("islandBasicClusters","islandBarrelBasicClusters"),
    EBRecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    EBTreePtMin = cms.untracked.double(15),
    EERecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    EETreePtMin = cms.untracked.double(15),
    FastJetRhoTag = cms.InputTag("kt4CaloJets"),
    FastJetSigmaTag = cms.InputTag("kt4CaloJets"),
    HBHETreePtMin = cms.untracked.double(15),
    HFTreePtMin = cms.untracked.double(15),
    HFlongMin = cms.untracked.double(0.5),
    HFshortMin = cms.untracked.double(0.85),
    HFtowerMin = cms.untracked.double(3),
    JetSrc = cms.InputTag("iterativeConePu5CaloJets"),
    TowerTreePtMin = cms.untracked.double(-9999),
    calZDCDigi = cms.bool(True),
    castorRecHitSrc = cms.InputTag("castorreco"),
    doBasicClusters = cms.bool(False),
    doCASTOR = cms.bool(True),
    doEbyEonly = cms.bool(False),
    doEcal = cms.bool(False),
    doFastJet = cms.bool(False),
    doHBHE = cms.bool(False),
    doHF = cms.bool(True),
    doTowers = cms.bool(True),
    doZDCDigi = cms.bool(False),
    doZDCRecHit = cms.bool(False),
    hasVtx = cms.bool(True),
    hcalHBHERecHitSrc = cms.InputTag("hbhereco"),
    hcalHFRecHitSrc = cms.InputTag("hfreco"),
    nZdcTs = cms.int32(10),
    saveBothVtx = cms.bool(False),
    towersSrc = cms.InputTag("towerMaker"),
    useJets = cms.bool(False),
    vtxSrc = cms.InputTag("hiSelectedVertex"),
    zdcDigiSrc = cms.InputTag("hcalDigis"),
    zdcRecHitSrc = cms.InputTag("zdcreco")
)


process.rechitanalyzerpp = cms.EDAnalyzer("RecHitTreeProducer",
    BasicClusterSrc = cms.InputTag("islandBasicClusters","islandBarrelBasicClusters"),
    EBRecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    EBTreePtMin = cms.untracked.double(15),
    EERecHitSrc = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    EETreePtMin = cms.untracked.double(15),
    FastJetRhoTag = cms.InputTag("kt4CaloJets"),
    FastJetSigmaTag = cms.InputTag("kt4CaloJets"),
    HBHETreePtMin = cms.untracked.double(15),
    HFTreePtMin = cms.untracked.double(15),
    HFlongMin = cms.untracked.double(0.5),
    HFshortMin = cms.untracked.double(0.85),
    HFtowerMin = cms.untracked.double(3),
    JetSrc = cms.InputTag("ak4CaloJets"),
    TowerTreePtMin = cms.untracked.double(-9999),
    calZDCDigi = cms.bool(True),
    castorRecHitSrc = cms.InputTag("castorreco"),
    doBasicClusters = cms.bool(False),
    doCASTOR = cms.bool(True),
    doEbyEonly = cms.bool(False),
    doEcal = cms.bool(False),
    doFastJet = cms.bool(False),
    doHBHE = cms.bool(False),
    doHF = cms.bool(False),
    doTowers = cms.bool(True),
    doZDCDigi = cms.bool(False),
    doZDCRecHit = cms.bool(False),
    hasVtx = cms.bool(True),
    hcalHBHERecHitSrc = cms.InputTag("hbhereco"),
    hcalHFRecHitSrc = cms.InputTag("hfreco"),
    nZdcTs = cms.int32(10),
    saveBothVtx = cms.bool(False),
    towersSrc = cms.InputTag("towerMaker"),
    useJets = cms.bool(False),
    vtxSrc = cms.InputTag("offlinePrimaryVerticesWithBS"),
    zdcDigiSrc = cms.InputTag("hcalDigis"),
    zdcRecHitSrc = cms.InputTag("zdcreco")
)


process.runAnalyzer = cms.EDAnalyzer("RunAnalyzer")


process.skimanalysis = cms.EDAnalyzer("FilterAnalyzer",
    hltresults = cms.InputTag("TriggerResults","","HiForest"),
    superFilters = cms.vstring('')
)


process.DQMStore = cms.Service("DQMStore",
    LSbasedMode = cms.untracked.bool(False),
    collateHistograms = cms.untracked.bool(False),
    enableMultiThread = cms.untracked.bool(False),
    forceResetOnBeginLumi = cms.untracked.bool(False),
    referenceFileName = cms.untracked.string(''),
    verbose = cms.untracked.int32(0),
    verboseQT = cms.untracked.int32(0)
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
            reportEvery = cms.untracked.int32(1)
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


process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    CTPPSFastRecHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1357987)
    ),
    LHCTransport = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(87654321)
    ),
    MuonSimHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(987346)
    ),
    VtxSmeared = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(98765432)
    ),
    ecalPreshowerRecHit = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(6541321)
    ),
    ecalRecHit = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(654321)
    ),
    externalLHEProducer = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(234567)
    ),
    famosPileUp = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    fastSimProducer = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(13579)
    ),
    fastTrackerRecHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(24680)
    ),
    g4SimHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(11)
    ),
    generator = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(123456789)
    ),
    hbhereco = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(541321)
    ),
    hfreco = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(541321)
    ),
    hiSignal = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(123456789)
    ),
    hiSignalG4SimHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(11)
    ),
    hiSignalLHCTransport = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(88776655)
    ),
    horeco = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(541321)
    ),
    l1ParamMuons = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(6453209)
    ),
    mix = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(12345)
    ),
    mixData = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(12345)
    ),
    mixGenPU = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    mixRecoTracks = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    mixSimCaloHits = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(918273)
    ),
    paramMuons = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(54525)
    ),
    saveFileName = cms.untracked.string(''),
    simBeamSpotFilter = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(87654321)
    ),
    simMuonCSCDigis = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(11223344)
    ),
    simMuonDTDigis = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1234567)
    ),
    simMuonRPCDigis = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1234567)
    ),
    simSiStripDigiSimLink = cms.PSet(
        engineName = cms.untracked.string('MixMaxRng'),
        initialSeed = cms.untracked.uint32(1234567)
    )
)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('HiForestAOD.root')
)


process.CSCGeometryESModule = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    debugV = cms.untracked.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useDDD = cms.bool(False),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.CSVscikitTags = cms.ESProducer("CSVscikitESProducer",
    computer = cms.ESInputTag("justastupiddummyname"),
    gbrForestLabel = cms.string(''),
    mvaName = cms.string('BDT'),
    slComputerCfg = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        calibrationRecords = cms.vstring(
            'CombinedSVIVFV2RecoVertex', 
            'CombinedSVIVFV2PseudoVertex', 
            'CombinedSVIVFV2NoVertex'
        ),
        categoryVariableName = cms.string('vertexCategory'),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(True),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        recordLabel = cms.string(''),
        trackFlip = cms.bool(False),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(2.0),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useCategories = cms.bool(True),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(False)
    ),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderTagInfos")),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.VPSet(
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('TagVarCSV_trackSip3dSig_0'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('TagVarCSV_trackSip3dSig_1'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(2),
            name = cms.string('TagVarCSV_trackSip3dSig_2'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(3),
            name = cms.string('TagVarCSV_trackSip3dSig_3'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-999),
            name = cms.string('TagVarCSV_trackSip3dSigAboveCharm'),
            taggingVarName = cms.string('trackSip3dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('TagVarCSV_trackPtRel_0'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('TagVarCSV_trackPtRel_1'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(2),
            name = cms.string('TagVarCSV_trackPtRel_2'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(3),
            name = cms.string('TagVarCSV_trackPtRel_3'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('TagVarCSV_trackEtaRel_0'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('TagVarCSV_trackEtaRel_1'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(2),
            name = cms.string('TagVarCSV_trackEtaRel_2'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(3),
            name = cms.string('TagVarCSV_trackEtaRel_3'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('TagVarCSV_trackDeltaR_0'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('TagVarCSV_trackDeltaR_1'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(2),
            name = cms.string('TagVarCSV_trackDeltaR_2'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(3),
            name = cms.string('TagVarCSV_trackDeltaR_3'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('TagVarCSV_trackPtRatio_0'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('TagVarCSV_trackPtRatio_1'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(2),
            name = cms.string('TagVarCSV_trackPtRatio_2'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(3),
            name = cms.string('TagVarCSV_trackPtRatio_3'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('TagVarCSV_trackJetDist_0'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('TagVarCSV_trackJetDist_1'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(2),
            name = cms.string('TagVarCSV_trackJetDist_2'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(3),
            name = cms.string('TagVarCSV_trackJetDist_3'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('TagVarCSV_trackDecayLenVal_0'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('TagVarCSV_trackDecayLenVal_1'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(2),
            name = cms.string('TagVarCSV_trackDecayLenVal_2'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(3),
            name = cms.string('TagVarCSV_trackDecayLenVal_3'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('TagVarCSV_trackSumJetEtRatio'),
            taggingVarName = cms.string('trackSumJetEtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('TagVarCSV_trackSumJetDeltaR'),
            taggingVarName = cms.string('trackSumJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('TagVarCSV_vertexMass'),
            taggingVarName = cms.string('vertexMass')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('TagVarCSV_vertexNTracks'),
            taggingVarName = cms.string('vertexNTracks')
        ), 
        cms.PSet(
            default = cms.double(-10),
            name = cms.string('TagVarCSV_vertexEnergyRatio'),
            taggingVarName = cms.string('vertexEnergyRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('TagVarCSV_vertexJetDeltaR'),
            taggingVarName = cms.string('vertexJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            name = cms.string('TagVarCSV_flightDistance2dSig'),
            taggingVarName = cms.string('flightDistance2dSig')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('TagVarCSV_jetNSecondaryVertices'),
            taggingVarName = cms.string('jetNSecondaryVertices')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('TagVarCSV_vertexCategory'),
            taggingVarName = cms.string('vertexCategory')
        )
    ),
    weightFile = cms.FileInPath('HeavyIonsAnalysis/JetAnalysis/data/TMVA_Btag_CsJets_PbPb2018_BDTG.weights.xml')
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


process.CaloTowerGeometryFromDBEP = cms.ESProducer("CaloTowerGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.CaloTowerTopologyEP = cms.ESProducer("CaloTowerTopologyEP")


process.CastorDbProducer = cms.ESProducer("CastorDbProducer",
    appendToDataLabel = cms.string('')
)


process.CastorGeometryFromDBEP = cms.ESProducer("CastorGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.DTGeometryESModule = cms.ESProducer("DTGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(False)
)


process.EcalBarrelGeometryFromDBEP = cms.ESProducer("EcalBarrelGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalElectronicsMappingBuilder = cms.ESProducer("EcalElectronicsMappingBuilder")


process.EcalEndcapGeometryFromDBEP = cms.ESProducer("EcalEndcapGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalLaserCorrectionService = cms.ESProducer("EcalLaserCorrectionService")


process.EcalPreshowerGeometryFromDBEP = cms.ESProducer("EcalPreshowerGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalTrigTowerConstituentsMapBuilder = cms.ESProducer("EcalTrigTowerConstituentsMapBuilder",
    MapFile = cms.untracked.string('Geometry/EcalMapping/data/EndCap_TTMap.txt')
)


process.GlobalTrackingGeometryESProducer = cms.ESProducer("GlobalTrackingGeometryESProducer")


process.HcalAlignmentEP = cms.ESProducer("HcalAlignmentEP")


process.HcalGeometryFromDBEP = cms.ESProducer("HcalGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.MuonDetLayerGeometryESProducer = cms.ESProducer("MuonDetLayerGeometryESProducer")


process.MuonNumberingInitialization = cms.ESProducer("MuonNumberingInitialization")


process.ParabolicParametrizedMagneticFieldProducer = cms.ESProducer("AutoParametrizedMagneticFieldProducer",
    label = cms.untracked.string('ParabolicMf'),
    valueOverride = cms.int32(18268),
    version = cms.string('Parabolic')
)


process.RPCGeometryESModule = cms.ESProducer("RPCGeometryESModule",
    compatibiltyWith11 = cms.untracked.bool(True),
    useDDD = cms.untracked.bool(False)
)


process.SiStripRecHitMatcherESProducer = cms.ESProducer("SiStripRecHitMatcherESProducer",
    ComponentName = cms.string('StandardMatcher'),
    NSigmaInside = cms.double(3.0),
    PreFilter = cms.bool(False)
)


process.SteppingHelixPropagatorAlong = cms.ESProducer("SteppingHelixPropagatorESProducer",
    ApplyRadX0Correction = cms.bool(True),
    AssumeNoMaterial = cms.bool(False),
    ComponentName = cms.string('SteppingHelixPropagatorAlong'),
    NoErrorPropagation = cms.bool(False),
    PropagationDirection = cms.string('alongMomentum'),
    SetVBFPointer = cms.bool(False),
    VBFName = cms.string('VolumeBasedMagneticField'),
    debug = cms.bool(False),
    endcapShiftInZNeg = cms.double(0.0),
    endcapShiftInZPos = cms.double(0.0),
    returnTangentPlane = cms.bool(True),
    sendLogWarning = cms.bool(False),
    useEndcapShiftsInZ = cms.bool(False),
    useInTeslaFromMagField = cms.bool(False),
    useIsYokeFlag = cms.bool(True),
    useMagVolumes = cms.bool(True),
    useMatVolumes = cms.bool(True),
    useTuningForL2Speed = cms.bool(False)
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


process.TransientTrackBuilderESProducer = cms.ESProducer("TransientTrackBuilderESProducer",
    ComponentName = cms.string('TransientTrackBuilder')
)


process.VolumeBasedMagneticFieldESProducer = cms.ESProducer("VolumeBasedMagneticFieldESProducerFromDB",
    debugBuilder = cms.untracked.bool(False),
    label = cms.untracked.string(''),
    valueOverride = cms.int32(18268)
)


process.XMLFromDBSource = cms.ESProducer("XMLIdealGeometryESProducer",
    label = cms.string('Extended'),
    rootDDName = cms.string('cms:OCMS')
)


process.ZdcGeometryFromDBEP = cms.ESProducer("ZdcGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.candidateBoostedDoubleSecondaryVertexAK8Computer = cms.ESProducer("CandidateBoostedDoubleSecondaryVertexESProducer",
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SecondaryVertex/data/BoostedDoubleSV_AK8_BDT_v4.weights.xml.gz')
)


process.candidateBoostedDoubleSecondaryVertexCA15Computer = cms.ESProducer("CandidateBoostedDoubleSecondaryVertexESProducer",
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SecondaryVertex/data/BoostedDoubleSV_CA15_BDT_v3.weights.xml.gz')
)


process.candidateChargeBTagComputer = cms.ESProducer("CandidateChargeBTagESProducer",
    gbrForestLabel = cms.string(''),
    jetChargeExp = cms.double(0.8),
    svChargeExp = cms.double(0.5),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(False),
    weightFile = cms.FileInPath('RecoBTag/Combined/data/ChargeBTag_4sep_2016.weights.xml.gz')
)


process.candidateCombinedMVAV2Computer = cms.ESProducer("CombinedMVAV2JetTagESProducer",
    gbrForestLabel = cms.string('btag_CombinedMVAv2_BDT'),
    jetTagComputers = cms.vstring(
        'candidateJetProbabilityComputer', 
        'candidateJetBProbabilityComputer', 
        'candidateCombinedSecondaryVertexV2Computer', 
        'softPFMuonComputer', 
        'softPFElectronComputer'
    ),
    mvaName = cms.string('bdt'),
    spectators = cms.vstring(),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    variables = cms.vstring(
        'Jet_CSV', 
        'Jet_CSVIVF', 
        'Jet_JP', 
        'Jet_JBP', 
        'Jet_SoftMu', 
        'Jet_SoftEl'
    ),
    weightFile = cms.FileInPath('RecoBTag/Combined/data/CombinedMVAV2_13_07_2015.weights.xml.gz')
)


process.candidateCombinedSecondaryVertexSoftLeptonComputer = cms.ESProducer("CandidateCombinedSecondaryVertexSoftLeptonESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVRecoVertexNoSoftLepton', 
        'CombinedSVPseudoVertexNoSoftLepton', 
        'CombinedSVNoVertexNoSoftLepton', 
        'CombinedSVRecoVertexSoftMuon', 
        'CombinedSVPseudoVertexSoftMuon', 
        'CombinedSVNoVertexSoftMuon', 
        'CombinedSVRecoVertexSoftElectron', 
        'CombinedSVPseudoVertexSoftElectron', 
        'CombinedSVNoVertexSoftElectron'
    ),
    categoryVariableName = cms.string('vertexLeptonCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)


process.candidateCombinedSecondaryVertexSoftLeptonCvsLComputer = cms.ESProducer("CandidateCombinedSecondaryVertexSoftLeptonCvsLESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVRecoVertexNoSoftLeptonCvsL', 
        'CombinedSVPseudoVertexNoSoftLeptonCvsL', 
        'CombinedSVNoVertexNoSoftLeptonCvsL', 
        'CombinedSVRecoVertexSoftMuonCvsL', 
        'CombinedSVPseudoVertexSoftMuonCvsL', 
        'CombinedSVNoVertexSoftMuonCvsL', 
        'CombinedSVRecoVertexSoftElectronCvsL', 
        'CombinedSVPseudoVertexSoftElectronCvsL', 
        'CombinedSVNoVertexSoftElectronCvsL'
    ),
    categoryVariableName = cms.string('vertexLeptonCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)


process.candidateCombinedSecondaryVertexV2Computer = cms.ESProducer("CandidateCombinedSecondaryVertexESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVIVFV2RecoVertex', 
        'CombinedSVIVFV2PseudoVertex', 
        'CombinedSVIVFV2NoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)


process.candidateGhostTrackComputer = cms.ESProducer("CandidateGhostTrackESProducer",
    calibrationRecords = cms.vstring(
        'GhostTrackRecoVertex', 
        'GhostTrackPseudoVertex', 
        'GhostTrackNoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    minimumTrackWeight = cms.double(0.5),
    recordLabel = cms.string(''),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True)
)


process.candidateJetBProbabilityComputer = cms.ESProducer("CandidateJetBProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    numberOfBTracks = cms.uint32(4),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.candidateJetProbabilityComputer = cms.ESProducer("CandidateJetProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(0.3),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.candidateNegativeCombinedMVAV2Computer = cms.ESProducer("CombinedMVAV2JetTagESProducer",
    gbrForestLabel = cms.string('btag_CombinedMVAv2_BDT'),
    jetTagComputers = cms.vstring(
        'candidateNegativeOnlyJetProbabilityComputer', 
        'candidateNegativeOnlyJetBProbabilityComputer', 
        'candidateNegativeCombinedSecondaryVertexV2Computer', 
        'negativeSoftPFMuonComputer', 
        'negativeSoftPFElectronComputer'
    ),
    mvaName = cms.string('bdt'),
    spectators = cms.vstring(),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    variables = cms.vstring(
        'Jet_CSV', 
        'Jet_CSVIVF', 
        'Jet_JP', 
        'Jet_JBP', 
        'Jet_SoftMu', 
        'Jet_SoftEl'
    ),
    weightFile = cms.FileInPath('RecoBTag/Combined/data/CombinedMVAV2_13_07_2015.weights.xml.gz')
)


process.candidateNegativeCombinedSecondaryVertexV2Computer = cms.ESProducer("CandidateCombinedSecondaryVertexESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVIVFV2RecoVertex', 
        'CombinedSVIVFV2PseudoVertex', 
        'CombinedSVIVFV2NoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(True),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(-2.0),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(0),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(0),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(True)
)


process.candidateNegativeOnlyJetBProbabilityComputer = cms.ESProducer("CandidateJetBProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    numberOfBTracks = cms.uint32(4),
    trackIpSign = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.candidateNegativeOnlyJetProbabilityComputer = cms.ESProducer("CandidateJetProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(0.3),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    trackIpSign = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.candidateNegativeTrackCounting3D2ndComputer = cms.ESProducer("CandidateNegativeTrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(2),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.candidateNegativeTrackCounting3D3rdComputer = cms.ESProducer("CandidateNegativeTrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(3),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.candidatePositiveCombinedMVAV2Computer = cms.ESProducer("CombinedMVAV2JetTagESProducer",
    gbrForestLabel = cms.string('btag_CombinedMVAv2_BDT'),
    jetTagComputers = cms.vstring(
        'candidatePositiveOnlyJetProbabilityComputer', 
        'candidatePositiveOnlyJetBProbabilityComputer', 
        'candidatePositiveCombinedSecondaryVertexV2Computer', 
        'negativeSoftPFMuonComputer', 
        'negativeSoftPFElectronComputer'
    ),
    mvaName = cms.string('bdt'),
    spectators = cms.vstring(),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    variables = cms.vstring(
        'Jet_CSV', 
        'Jet_CSVIVF', 
        'Jet_JP', 
        'Jet_JBP', 
        'Jet_SoftMu', 
        'Jet_SoftEl'
    ),
    weightFile = cms.FileInPath('RecoBTag/Combined/data/CombinedMVAV2_13_07_2015.weights.xml.gz')
)


process.candidatePositiveCombinedSecondaryVertexV2Computer = cms.ESProducer("CandidateCombinedSecondaryVertexESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVIVFV2RecoVertex', 
        'CombinedSVIVFV2PseudoVertex', 
        'CombinedSVIVFV2NoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(0),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(0),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)


process.candidatePositiveOnlyJetBProbabilityComputer = cms.ESProducer("CandidateJetBProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    numberOfBTracks = cms.uint32(4),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.candidatePositiveOnlyJetProbabilityComputer = cms.ESProducer("CandidateJetProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(0.3),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.candidateSimpleSecondaryVertex2TrkComputer = cms.ESProducer("CandidateSimpleSecondaryVertexESProducer",
    minTracks = cms.uint32(2),
    unBoost = cms.bool(False),
    use3d = cms.bool(True),
    useSignificance = cms.bool(True)
)


process.candidateSimpleSecondaryVertex3TrkComputer = cms.ESProducer("CandidateSimpleSecondaryVertexESProducer",
    minTracks = cms.uint32(3),
    unBoost = cms.bool(False),
    use3d = cms.bool(True),
    useSignificance = cms.bool(True)
)


process.candidateTrackCounting3D2ndComputer = cms.ESProducer("CandidateTrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(2),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.candidateTrackCounting3D3rdComputer = cms.ESProducer("CandidateTrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(3),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.charmTagsComputerCvsB = cms.ESProducer("CharmTaggerESProducer",
    computer = cms.ESInputTag("combinedSecondaryVertexSoftLeptonComputer"),
    defaultValueNoTracks = cms.bool(False),
    gbrForestLabel = cms.string(''),
    mvaName = cms.string('BDT'),
    slComputerCfg = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        calibrationRecords = cms.vstring(
            'CombinedSVRecoVertexNoSoftLepton', 
            'CombinedSVPseudoVertexNoSoftLepton', 
            'CombinedSVNoVertexNoSoftLepton', 
            'CombinedSVRecoVertexSoftMuon', 
            'CombinedSVPseudoVertexSoftMuon', 
            'CombinedSVNoVertexSoftMuon', 
            'CombinedSVRecoVertexSoftElectron', 
            'CombinedSVPseudoVertexSoftElectron', 
            'CombinedSVNoVertexSoftElectron'
        ),
        categoryVariableName = cms.string('vertexLeptonCategory'),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(False),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        recordLabel = cms.string(''),
        trackFlip = cms.bool(False),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(2.0),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useCategories = cms.bool(True),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(False)
    ),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos")),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.VPSet(
        cms.PSet(
            default = cms.double(-1),
            name = cms.string('vertexLeptonCategory'),
            taggingVarName = cms.string('vertexLeptonCategory')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSig_0'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip2dSig_1'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSig_0'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip3dSig_1'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPtRel_0'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPtRel_1'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPPar_0'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPPar_1'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackEtaRel_0'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackEtaRel_1'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDeltaR_0'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDeltaR_1'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackPtRatio_0'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackPtRatio_1'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(0),
            name = cms.string('trackPParRatio_0'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(1),
            name = cms.string('trackPParRatio_1'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackJetDist_0'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackJetDist_1'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDecayLenVal_0'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDecayLenVal_1'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('jetNSecondaryVertices'),
            taggingVarName = cms.string('jetNSecondaryVertices')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('jetNTracks'),
            taggingVarName = cms.string('jetNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetEtRatio'),
            taggingVarName = cms.string('trackSumJetEtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetDeltaR'),
            taggingVarName = cms.string('trackSumJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexMass_0'),
            taggingVarName = cms.string('vertexMass')
        ), 
        cms.PSet(
            default = cms.double(-10),
            idx = cms.int32(0),
            name = cms.string('vertexEnergyRatio_0'),
            taggingVarName = cms.string('vertexEnergyRatio')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip2dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip3dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance2dSig_0'),
            taggingVarName = cms.string('flightDistance2dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance3dSig_0'),
            taggingVarName = cms.string('flightDistance3dSig')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexJetDeltaR_0'),
            taggingVarName = cms.string('vertexJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(0),
            idx = cms.int32(0),
            name = cms.string('vertexNTracks_0'),
            taggingVarName = cms.string('vertexNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('massVertexEnergyFraction_0'),
            taggingVarName = cms.string('massVertexEnergyFraction')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexBoostOverSqrtJetPt_0'),
            taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonPtRel_0'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonPtRel_1'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(0),
            name = cms.string('leptonSip3d_0'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(1),
            name = cms.string('leptonSip3d_1'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonDeltaR_0'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonDeltaR_1'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatioRel_0'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatioRel_1'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonEtaRel_0'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonEtaRel_1'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatio_0'),
            taggingVarName = cms.string('leptonRatio')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatio_1'),
            taggingVarName = cms.string('leptonRatio')
        )
    ),
    weightFile = cms.FileInPath('RecoBTag/CTagging/data/c_vs_b_sklearn.weight.xml')
)


process.charmTagsComputerCvsL = cms.ESProducer("CharmTaggerESProducer",
    computer = cms.ESInputTag("combinedSecondaryVertexSoftLeptonComputer"),
    defaultValueNoTracks = cms.bool(False),
    gbrForestLabel = cms.string(''),
    mvaName = cms.string('BDT'),
    slComputerCfg = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        calibrationRecords = cms.vstring(
            'CombinedSVRecoVertexNoSoftLepton', 
            'CombinedSVPseudoVertexNoSoftLepton', 
            'CombinedSVNoVertexNoSoftLepton', 
            'CombinedSVRecoVertexSoftMuon', 
            'CombinedSVPseudoVertexSoftMuon', 
            'CombinedSVNoVertexSoftMuon', 
            'CombinedSVRecoVertexSoftElectron', 
            'CombinedSVPseudoVertexSoftElectron', 
            'CombinedSVNoVertexSoftElectron'
        ),
        categoryVariableName = cms.string('vertexLeptonCategory'),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(False),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        recordLabel = cms.string(''),
        trackFlip = cms.bool(False),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(2.0),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useCategories = cms.bool(True),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(False)
    ),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos")),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.VPSet(
        cms.PSet(
            default = cms.double(-1),
            name = cms.string('vertexLeptonCategory'),
            taggingVarName = cms.string('vertexLeptonCategory')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSig_0'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip2dSig_1'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSig_0'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip3dSig_1'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPtRel_0'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPtRel_1'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPPar_0'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPPar_1'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackEtaRel_0'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackEtaRel_1'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDeltaR_0'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDeltaR_1'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackPtRatio_0'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackPtRatio_1'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(0),
            name = cms.string('trackPParRatio_0'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(1),
            name = cms.string('trackPParRatio_1'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackJetDist_0'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackJetDist_1'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDecayLenVal_0'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDecayLenVal_1'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('jetNSecondaryVertices'),
            taggingVarName = cms.string('jetNSecondaryVertices')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('jetNTracks'),
            taggingVarName = cms.string('jetNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetEtRatio'),
            taggingVarName = cms.string('trackSumJetEtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetDeltaR'),
            taggingVarName = cms.string('trackSumJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexMass_0'),
            taggingVarName = cms.string('vertexMass')
        ), 
        cms.PSet(
            default = cms.double(-10),
            idx = cms.int32(0),
            name = cms.string('vertexEnergyRatio_0'),
            taggingVarName = cms.string('vertexEnergyRatio')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip2dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip3dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance2dSig_0'),
            taggingVarName = cms.string('flightDistance2dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance3dSig_0'),
            taggingVarName = cms.string('flightDistance3dSig')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexJetDeltaR_0'),
            taggingVarName = cms.string('vertexJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(0),
            idx = cms.int32(0),
            name = cms.string('vertexNTracks_0'),
            taggingVarName = cms.string('vertexNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('massVertexEnergyFraction_0'),
            taggingVarName = cms.string('massVertexEnergyFraction')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexBoostOverSqrtJetPt_0'),
            taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonPtRel_0'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonPtRel_1'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(0),
            name = cms.string('leptonSip3d_0'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(1),
            name = cms.string('leptonSip3d_1'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonDeltaR_0'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonDeltaR_1'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatioRel_0'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatioRel_1'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonEtaRel_0'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonEtaRel_1'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatio_0'),
            taggingVarName = cms.string('leptonRatio')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatio_1'),
            taggingVarName = cms.string('leptonRatio')
        )
    ),
    weightFile = cms.FileInPath('RecoBTag/CTagging/data/c_vs_udsg_sklearn.weight.xml')
)


process.charmTagsNegativeComputerCvsB = cms.ESProducer("CharmTaggerESProducer",
    computer = cms.ESInputTag("combinedSecondaryVertexSoftLeptonComputer"),
    defaultValueNoTracks = cms.bool(False),
    gbrForestLabel = cms.string(''),
    mvaName = cms.string('BDT'),
    slComputerCfg = cms.PSet(
        SoftLeptonFlip = cms.bool(True),
        calibrationRecords = cms.vstring(
            'CombinedSVRecoVertexNoSoftLepton', 
            'CombinedSVPseudoVertexNoSoftLepton', 
            'CombinedSVNoVertexNoSoftLepton', 
            'CombinedSVRecoVertexSoftMuon', 
            'CombinedSVPseudoVertexSoftMuon', 
            'CombinedSVNoVertexSoftMuon', 
            'CombinedSVRecoVertexSoftElectron', 
            'CombinedSVPseudoVertexSoftElectron', 
            'CombinedSVNoVertexSoftElectron'
        ),
        categoryVariableName = cms.string('vertexLeptonCategory'),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(False),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        recordLabel = cms.string(''),
        trackFlip = cms.bool(True),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(-2.0),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(0),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(0),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useCategories = cms.bool(True),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(True)
    ),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos")),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.VPSet(
        cms.PSet(
            default = cms.double(-1),
            name = cms.string('vertexLeptonCategory'),
            taggingVarName = cms.string('vertexLeptonCategory')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSig_0'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip2dSig_1'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSig_0'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip3dSig_1'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPtRel_0'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPtRel_1'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPPar_0'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPPar_1'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackEtaRel_0'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackEtaRel_1'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDeltaR_0'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDeltaR_1'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackPtRatio_0'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackPtRatio_1'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(0),
            name = cms.string('trackPParRatio_0'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(1),
            name = cms.string('trackPParRatio_1'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackJetDist_0'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackJetDist_1'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDecayLenVal_0'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDecayLenVal_1'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('jetNSecondaryVertices'),
            taggingVarName = cms.string('jetNSecondaryVertices')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('jetNTracks'),
            taggingVarName = cms.string('jetNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetEtRatio'),
            taggingVarName = cms.string('trackSumJetEtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetDeltaR'),
            taggingVarName = cms.string('trackSumJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexMass_0'),
            taggingVarName = cms.string('vertexMass')
        ), 
        cms.PSet(
            default = cms.double(-10),
            idx = cms.int32(0),
            name = cms.string('vertexEnergyRatio_0'),
            taggingVarName = cms.string('vertexEnergyRatio')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip2dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip3dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance2dSig_0'),
            taggingVarName = cms.string('flightDistance2dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance3dSig_0'),
            taggingVarName = cms.string('flightDistance3dSig')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexJetDeltaR_0'),
            taggingVarName = cms.string('vertexJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(0),
            idx = cms.int32(0),
            name = cms.string('vertexNTracks_0'),
            taggingVarName = cms.string('vertexNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('massVertexEnergyFraction_0'),
            taggingVarName = cms.string('massVertexEnergyFraction')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexBoostOverSqrtJetPt_0'),
            taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonPtRel_0'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonPtRel_1'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(0),
            name = cms.string('leptonSip3d_0'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(1),
            name = cms.string('leptonSip3d_1'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonDeltaR_0'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonDeltaR_1'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatioRel_0'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatioRel_1'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonEtaRel_0'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonEtaRel_1'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatio_0'),
            taggingVarName = cms.string('leptonRatio')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatio_1'),
            taggingVarName = cms.string('leptonRatio')
        )
    ),
    weightFile = cms.FileInPath('RecoBTag/CTagging/data/c_vs_b_sklearn.weight.xml')
)


process.charmTagsNegativeComputerCvsL = cms.ESProducer("CharmTaggerESProducer",
    computer = cms.ESInputTag("combinedSecondaryVertexSoftLeptonComputer"),
    defaultValueNoTracks = cms.bool(False),
    gbrForestLabel = cms.string(''),
    mvaName = cms.string('BDT'),
    slComputerCfg = cms.PSet(
        SoftLeptonFlip = cms.bool(True),
        calibrationRecords = cms.vstring(
            'CombinedSVRecoVertexNoSoftLepton', 
            'CombinedSVPseudoVertexNoSoftLepton', 
            'CombinedSVNoVertexNoSoftLepton', 
            'CombinedSVRecoVertexSoftMuon', 
            'CombinedSVPseudoVertexSoftMuon', 
            'CombinedSVNoVertexSoftMuon', 
            'CombinedSVRecoVertexSoftElectron', 
            'CombinedSVPseudoVertexSoftElectron', 
            'CombinedSVNoVertexSoftElectron'
        ),
        categoryVariableName = cms.string('vertexLeptonCategory'),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(False),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        recordLabel = cms.string(''),
        trackFlip = cms.bool(True),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(-2.0),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(0),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(0),
            sip3dSigMin = cms.double(-99999.9),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useCategories = cms.bool(True),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(True)
    ),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos")),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.VPSet(
        cms.PSet(
            default = cms.double(-1),
            name = cms.string('vertexLeptonCategory'),
            taggingVarName = cms.string('vertexLeptonCategory')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSig_0'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip2dSig_1'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSig_0'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip3dSig_1'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPtRel_0'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPtRel_1'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPPar_0'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPPar_1'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackEtaRel_0'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackEtaRel_1'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDeltaR_0'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDeltaR_1'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackPtRatio_0'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackPtRatio_1'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(0),
            name = cms.string('trackPParRatio_0'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(1),
            name = cms.string('trackPParRatio_1'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackJetDist_0'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackJetDist_1'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDecayLenVal_0'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDecayLenVal_1'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('jetNSecondaryVertices'),
            taggingVarName = cms.string('jetNSecondaryVertices')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('jetNTracks'),
            taggingVarName = cms.string('jetNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetEtRatio'),
            taggingVarName = cms.string('trackSumJetEtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetDeltaR'),
            taggingVarName = cms.string('trackSumJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexMass_0'),
            taggingVarName = cms.string('vertexMass')
        ), 
        cms.PSet(
            default = cms.double(-10),
            idx = cms.int32(0),
            name = cms.string('vertexEnergyRatio_0'),
            taggingVarName = cms.string('vertexEnergyRatio')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip2dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip3dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance2dSig_0'),
            taggingVarName = cms.string('flightDistance2dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance3dSig_0'),
            taggingVarName = cms.string('flightDistance3dSig')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexJetDeltaR_0'),
            taggingVarName = cms.string('vertexJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(0),
            idx = cms.int32(0),
            name = cms.string('vertexNTracks_0'),
            taggingVarName = cms.string('vertexNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('massVertexEnergyFraction_0'),
            taggingVarName = cms.string('massVertexEnergyFraction')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexBoostOverSqrtJetPt_0'),
            taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonPtRel_0'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonPtRel_1'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(0),
            name = cms.string('leptonSip3d_0'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(1),
            name = cms.string('leptonSip3d_1'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonDeltaR_0'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonDeltaR_1'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatioRel_0'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatioRel_1'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonEtaRel_0'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonEtaRel_1'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatio_0'),
            taggingVarName = cms.string('leptonRatio')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatio_1'),
            taggingVarName = cms.string('leptonRatio')
        )
    ),
    weightFile = cms.FileInPath('RecoBTag/CTagging/data/c_vs_udsg_sklearn.weight.xml')
)


process.charmTagsPositiveComputerCvsB = cms.ESProducer("CharmTaggerESProducer",
    computer = cms.ESInputTag("combinedSecondaryVertexSoftLeptonComputer"),
    defaultValueNoTracks = cms.bool(False),
    gbrForestLabel = cms.string(''),
    mvaName = cms.string('BDT'),
    slComputerCfg = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        calibrationRecords = cms.vstring(
            'CombinedSVRecoVertexNoSoftLepton', 
            'CombinedSVPseudoVertexNoSoftLepton', 
            'CombinedSVNoVertexNoSoftLepton', 
            'CombinedSVRecoVertexSoftMuon', 
            'CombinedSVPseudoVertexSoftMuon', 
            'CombinedSVNoVertexSoftMuon', 
            'CombinedSVRecoVertexSoftElectron', 
            'CombinedSVPseudoVertexSoftElectron', 
            'CombinedSVNoVertexSoftElectron'
        ),
        categoryVariableName = cms.string('vertexLeptonCategory'),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(False),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        recordLabel = cms.string(''),
        trackFlip = cms.bool(False),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(2.0),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(0),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(0),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useCategories = cms.bool(True),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(False)
    ),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos")),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.VPSet(
        cms.PSet(
            default = cms.double(-1),
            name = cms.string('vertexLeptonCategory'),
            taggingVarName = cms.string('vertexLeptonCategory')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSig_0'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip2dSig_1'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSig_0'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip3dSig_1'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPtRel_0'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPtRel_1'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPPar_0'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPPar_1'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackEtaRel_0'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackEtaRel_1'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDeltaR_0'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDeltaR_1'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackPtRatio_0'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackPtRatio_1'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(0),
            name = cms.string('trackPParRatio_0'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(1),
            name = cms.string('trackPParRatio_1'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackJetDist_0'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackJetDist_1'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDecayLenVal_0'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDecayLenVal_1'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('jetNSecondaryVertices'),
            taggingVarName = cms.string('jetNSecondaryVertices')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('jetNTracks'),
            taggingVarName = cms.string('jetNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetEtRatio'),
            taggingVarName = cms.string('trackSumJetEtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetDeltaR'),
            taggingVarName = cms.string('trackSumJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexMass_0'),
            taggingVarName = cms.string('vertexMass')
        ), 
        cms.PSet(
            default = cms.double(-10),
            idx = cms.int32(0),
            name = cms.string('vertexEnergyRatio_0'),
            taggingVarName = cms.string('vertexEnergyRatio')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip2dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip3dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance2dSig_0'),
            taggingVarName = cms.string('flightDistance2dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance3dSig_0'),
            taggingVarName = cms.string('flightDistance3dSig')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexJetDeltaR_0'),
            taggingVarName = cms.string('vertexJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(0),
            idx = cms.int32(0),
            name = cms.string('vertexNTracks_0'),
            taggingVarName = cms.string('vertexNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('massVertexEnergyFraction_0'),
            taggingVarName = cms.string('massVertexEnergyFraction')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexBoostOverSqrtJetPt_0'),
            taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonPtRel_0'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonPtRel_1'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(0),
            name = cms.string('leptonSip3d_0'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(1),
            name = cms.string('leptonSip3d_1'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonDeltaR_0'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonDeltaR_1'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatioRel_0'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatioRel_1'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonEtaRel_0'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonEtaRel_1'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatio_0'),
            taggingVarName = cms.string('leptonRatio')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatio_1'),
            taggingVarName = cms.string('leptonRatio')
        )
    ),
    weightFile = cms.FileInPath('RecoBTag/CTagging/data/c_vs_b_sklearn.weight.xml')
)


process.charmTagsPositiveComputerCvsL = cms.ESProducer("CharmTaggerESProducer",
    computer = cms.ESInputTag("combinedSecondaryVertexSoftLeptonComputer"),
    defaultValueNoTracks = cms.bool(False),
    gbrForestLabel = cms.string(''),
    mvaName = cms.string('BDT'),
    slComputerCfg = cms.PSet(
        SoftLeptonFlip = cms.bool(False),
        calibrationRecords = cms.vstring(
            'CombinedSVRecoVertexNoSoftLepton', 
            'CombinedSVPseudoVertexNoSoftLepton', 
            'CombinedSVNoVertexNoSoftLepton', 
            'CombinedSVRecoVertexSoftMuon', 
            'CombinedSVPseudoVertexSoftMuon', 
            'CombinedSVNoVertexSoftMuon', 
            'CombinedSVRecoVertexSoftElectron', 
            'CombinedSVPseudoVertexSoftElectron', 
            'CombinedSVNoVertexSoftElectron'
        ),
        categoryVariableName = cms.string('vertexLeptonCategory'),
        charmCut = cms.double(1.5),
        correctVertexMass = cms.bool(False),
        minimumTrackWeight = cms.double(0.5),
        pseudoMultiplicityMin = cms.uint32(2),
        pseudoVertexV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.05)
        ),
        recordLabel = cms.string(''),
        trackFlip = cms.bool(False),
        trackMultiplicityMin = cms.uint32(2),
        trackPairV0Filter = cms.PSet(
            k0sMassWindow = cms.double(0.03)
        ),
        trackPseudoSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(2.0),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(0),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSelection = cms.PSet(
            a_dR = cms.double(-0.001053),
            a_pT = cms.double(0.005263),
            b_dR = cms.double(0.6263),
            b_pT = cms.double(0.3684),
            jetDeltaRMax = cms.double(0.3),
            maxDecayLen = cms.double(5),
            maxDistToAxis = cms.double(0.07),
            max_pT = cms.double(500),
            max_pT_dRcut = cms.double(0.1),
            max_pT_trackPTcut = cms.double(3),
            min_pT = cms.double(120),
            min_pT_dRcut = cms.double(0.5),
            normChi2Max = cms.double(99999.9),
            pixelHitsMin = cms.uint32(0),
            ptMin = cms.double(0.0),
            qualityClass = cms.string('any'),
            sip2dSigMax = cms.double(99999.9),
            sip2dSigMin = cms.double(-99999.9),
            sip2dValMax = cms.double(99999.9),
            sip2dValMin = cms.double(-99999.9),
            sip3dSigMax = cms.double(99999.9),
            sip3dSigMin = cms.double(0),
            sip3dValMax = cms.double(99999.9),
            sip3dValMin = cms.double(-99999.9),
            totalHitsMin = cms.uint32(0),
            useVariableJTA = cms.bool(False)
        ),
        trackSort = cms.string('sip2dSig'),
        useCategories = cms.bool(True),
        useTrackWeights = cms.bool(True),
        vertexFlip = cms.bool(False)
    ),
    tagInfos = cms.VInputTag(cms.InputTag("pfImpactParameterTagInfos"), cms.InputTag("pfInclusiveSecondaryVertexFinderCvsLTagInfos"), cms.InputTag("softPFMuonsTagInfos"), cms.InputTag("softPFElectronsTagInfos")),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.VPSet(
        cms.PSet(
            default = cms.double(-1),
            name = cms.string('vertexLeptonCategory'),
            taggingVarName = cms.string('vertexLeptonCategory')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSig_0'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip2dSig_1'),
            taggingVarName = cms.string('trackSip2dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSig_0'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-100),
            idx = cms.int32(1),
            name = cms.string('trackSip3dSig_1'),
            taggingVarName = cms.string('trackSip3dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPtRel_0'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPtRel_1'),
            taggingVarName = cms.string('trackPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackPPar_0'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackPPar_1'),
            taggingVarName = cms.string('trackPPar')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('trackEtaRel_0'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('trackEtaRel_1'),
            taggingVarName = cms.string('trackEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDeltaR_0'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDeltaR_1'),
            taggingVarName = cms.string('trackDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackPtRatio_0'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackPtRatio_1'),
            taggingVarName = cms.string('trackPtRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(0),
            name = cms.string('trackPParRatio_0'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(1.1),
            idx = cms.int32(1),
            name = cms.string('trackPParRatio_1'),
            taggingVarName = cms.string('trackPParRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackJetDist_0'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackJetDist_1'),
            taggingVarName = cms.string('trackJetDist')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('trackDecayLenVal_0'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(1),
            name = cms.string('trackDecayLenVal_1'),
            taggingVarName = cms.string('trackDecayLenVal')
        ), 
        cms.PSet(
            default = cms.double(0),
            name = cms.string('jetNSecondaryVertices'),
            taggingVarName = cms.string('jetNSecondaryVertices')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('jetNTracks'),
            taggingVarName = cms.string('jetNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetEtRatio'),
            taggingVarName = cms.string('trackSumJetEtRatio')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            name = cms.string('trackSumJetDeltaR'),
            taggingVarName = cms.string('trackSumJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexMass_0'),
            taggingVarName = cms.string('vertexMass')
        ), 
        cms.PSet(
            default = cms.double(-10),
            idx = cms.int32(0),
            name = cms.string('vertexEnergyRatio_0'),
            taggingVarName = cms.string('vertexEnergyRatio')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip2dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip2dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-999),
            idx = cms.int32(0),
            name = cms.string('trackSip3dSigAboveCharm_0'),
            taggingVarName = cms.string('trackSip3dSigAboveCharm')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance2dSig_0'),
            taggingVarName = cms.string('flightDistance2dSig')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('flightDistance3dSig_0'),
            taggingVarName = cms.string('flightDistance3dSig')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexJetDeltaR_0'),
            taggingVarName = cms.string('vertexJetDeltaR')
        ), 
        cms.PSet(
            default = cms.double(0),
            idx = cms.int32(0),
            name = cms.string('vertexNTracks_0'),
            taggingVarName = cms.string('vertexNTracks')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('massVertexEnergyFraction_0'),
            taggingVarName = cms.string('massVertexEnergyFraction')
        ), 
        cms.PSet(
            default = cms.double(-0.1),
            idx = cms.int32(0),
            name = cms.string('vertexBoostOverSqrtJetPt_0'),
            taggingVarName = cms.string('vertexBoostOverSqrtJetPt')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonPtRel_0'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonPtRel_1'),
            taggingVarName = cms.string('leptonPtRel')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(0),
            name = cms.string('leptonSip3d_0'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-10000),
            idx = cms.int32(1),
            name = cms.string('leptonSip3d_1'),
            taggingVarName = cms.string('leptonSip3d')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonDeltaR_0'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonDeltaR_1'),
            taggingVarName = cms.string('leptonDeltaR')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatioRel_0'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatioRel_1'),
            taggingVarName = cms.string('leptonRatioRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonEtaRel_0'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonEtaRel_1'),
            taggingVarName = cms.string('leptonEtaRel')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(0),
            name = cms.string('leptonRatio_0'),
            taggingVarName = cms.string('leptonRatio')
        ), 
        cms.PSet(
            default = cms.double(-1),
            idx = cms.int32(1),
            name = cms.string('leptonRatio_1'),
            taggingVarName = cms.string('leptonRatio')
        )
    ),
    weightFile = cms.FileInPath('RecoBTag/CTagging/data/c_vs_udsg_sklearn.weight.xml')
)


process.combinedMVAV2Computer = cms.ESProducer("CombinedMVAV2JetTagESProducer",
    jetTagComputers = cms.vstring(
        'jetProbabilityComputer', 
        'jetBProbabilityComputer', 
        'combinedSecondaryVertexV2Computer', 
        'softPFMuonComputer', 
        'softPFElectronComputer'
    ),
    mvaName = cms.string('bdt'),
    spectators = cms.vstring(),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.vstring(
        'Jet_CSV', 
        'Jet_CSVIVF', 
        'Jet_JP', 
        'Jet_JBP', 
        'Jet_SoftMu', 
        'Jet_SoftEl'
    ),
    weightFile = cms.FileInPath('RecoBTag/Combined/data/CombinedMVAV2_13_07_2015.weights.xml.gz')
)


process.combinedSecondaryVertexV2Computer = cms.ESProducer("CombinedSecondaryVertexESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVIVFV2RecoVertex', 
        'CombinedSVIVFV2PseudoVertex', 
        'CombinedSVIVFV2NoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)


process.doubleVertex2TrkComputer = cms.ESProducer("SimpleSecondaryVertexESProducer",
    minTracks = cms.uint32(2),
    minVertices = cms.uint32(2),
    unBoost = cms.bool(False),
    use3d = cms.bool(True),
    useSignificance = cms.bool(True)
)


process.fakeForIdealAlignment = cms.ESProducer("FakeAlignmentProducer",
    appendToDataLabel = cms.string('fakeForIdeal')
)


process.ghostTrackComputer = cms.ESProducer("GhostTrackESProducer",
    calibrationRecords = cms.vstring(
        'GhostTrackRecoVertex', 
        'GhostTrackPseudoVertex', 
        'GhostTrackNoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    minimumTrackWeight = cms.double(0.5),
    recordLabel = cms.string(''),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True)
)


process.hcalDDDRecConstants = cms.ESProducer("HcalDDDRecConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalDDDSimConstants = cms.ESProducer("HcalDDDSimConstantsESModule",
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
    useDDD = cms.bool(False),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.idealForDigiDTGeometry = cms.ESProducer("DTGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    fromDDD = cms.bool(False)
)


process.idealForDigiTrackerGeometry = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    fromDDD = cms.bool(False)
)


process.impactParameterMVAComputer = cms.ESProducer("GenericMVAJetTagESProducer",
    calibrationRecord = cms.string('ImpactParameterMVA'),
    recordLabel = cms.string(''),
    useCategories = cms.bool(False)
)


process.jetBProbabilityComputer = cms.ESProducer("JetBProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    numberOfBTracks = cms.uint32(4),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.jetProbabilityComputer = cms.ESProducer("JetProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(0.3),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.negativeCombinedMVAV2Computer = cms.ESProducer("CombinedMVAV2JetTagESProducer",
    jetTagComputers = cms.vstring(
        'negativeOnlyJetProbabilityComputer', 
        'negativeOnlyJetBProbabilityComputer', 
        'negativeCombinedSecondaryVertexV2Computer', 
        'negativeSoftPFMuonComputer', 
        'negativeSoftPFElectronComputer'
    ),
    mvaName = cms.string('bdt'),
    spectators = cms.vstring(),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.vstring(
        'Jet_CSV', 
        'Jet_CSVIVF', 
        'Jet_JP', 
        'Jet_JBP', 
        'Jet_SoftMu', 
        'Jet_SoftEl'
    ),
    weightFile = cms.FileInPath('RecoBTag/Combined/data/CombinedMVAV2_13_07_2015.weights.xml.gz')
)


process.negativeCombinedSecondaryVertexV2Computer = cms.ESProducer("CombinedSecondaryVertexESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVIVFV2RecoVertex', 
        'CombinedSVIVFV2PseudoVertex', 
        'CombinedSVIVFV2NoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(True),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(-2.0),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(0),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(0),
        sip3dSigMin = cms.double(-99999.9),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(True)
)


process.negativeOnlyJetBProbabilityComputer = cms.ESProducer("JetBProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    numberOfBTracks = cms.uint32(4),
    trackIpSign = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.negativeOnlyJetProbabilityComputer = cms.ESProducer("JetProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(0.3),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    trackIpSign = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.negativeSoftPFElectronByIP2dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('negative'),
    use3d = cms.bool(False)
)


process.negativeSoftPFElectronByIP3dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('negative'),
    use3d = cms.bool(True)
)


process.negativeSoftPFElectronByPtComputer = cms.ESProducer("LeptonTaggerByPtESProducer",
    ipSign = cms.string('negative')
)


process.negativeSoftPFElectronComputer = cms.ESProducer("ElectronTaggerESProducer",
    gbrForestLabel = cms.string('btag_SoftPFElectron_BDT'),
    ipSign = cms.string('negative'),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFElectron_BDT.weights.xml.gz')
)


process.negativeSoftPFMuonByIP2dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('negative'),
    use3d = cms.bool(False)
)


process.negativeSoftPFMuonByIP3dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('negative'),
    use3d = cms.bool(True)
)


process.negativeSoftPFMuonByPtComputer = cms.ESProducer("LeptonTaggerByPtESProducer",
    ipSign = cms.string('negative')
)


process.negativeSoftPFMuonComputer = cms.ESProducer("MuonTaggerESProducer",
    gbrForestLabel = cms.string('btag_SoftPFMuon_BDT'),
    ipSign = cms.string('negative'),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFMuon_BDT.weights.xml.gz')
)


process.negativeTrackCounting3D2ndComputer = cms.ESProducer("NegativeTrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(2),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.negativeTrackCounting3D3rdComputer = cms.ESProducer("NegativeTrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(3),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.positiveCombinedMVAV2Computer = cms.ESProducer("CombinedMVAV2JetTagESProducer",
    jetTagComputers = cms.vstring(
        'positiveOnlyJetProbabilityComputer', 
        'positiveOnlyJetBProbabilityComputer', 
        'positiveCombinedSecondaryVertexV2Computer', 
        'positiveSoftPFMuonComputer', 
        'positiveSoftPFElectronComputer'
    ),
    mvaName = cms.string('bdt'),
    spectators = cms.vstring(),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    variables = cms.vstring(
        'Jet_CSV', 
        'Jet_CSVIVF', 
        'Jet_JP', 
        'Jet_JBP', 
        'Jet_SoftMu', 
        'Jet_SoftEl'
    ),
    weightFile = cms.FileInPath('RecoBTag/Combined/data/CombinedMVAV2_13_07_2015.weights.xml.gz')
)


process.positiveCombinedSecondaryVertexV2Computer = cms.ESProducer("CombinedSecondaryVertexESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVIVFV2RecoVertex', 
        'CombinedSVIVFV2PseudoVertex', 
        'CombinedSVIVFV2NoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string(''),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(2),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(2.0),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(0),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3),
        min_pT = cms.double(120),
        min_pT_dRcut = cms.double(0.5),
        normChi2Max = cms.double(99999.9),
        pixelHitsMin = cms.uint32(0),
        ptMin = cms.double(0.0),
        qualityClass = cms.string('any'),
        sip2dSigMax = cms.double(99999.9),
        sip2dSigMin = cms.double(-99999.9),
        sip2dValMax = cms.double(99999.9),
        sip2dValMin = cms.double(-99999.9),
        sip3dSigMax = cms.double(99999.9),
        sip3dSigMin = cms.double(0),
        sip3dValMax = cms.double(99999.9),
        sip3dValMin = cms.double(-99999.9),
        totalHitsMin = cms.uint32(0),
        useVariableJTA = cms.bool(False)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)


process.positiveOnlyJetBProbabilityComputer = cms.ESProducer("JetBProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    numberOfBTracks = cms.uint32(4),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.positiveOnlyJetProbabilityComputer = cms.ESProducer("JetProbabilityESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(0.3),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumProbability = cms.double(0.005),
    trackIpSign = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useVariableJTA = cms.bool(False)
)


process.positiveSoftPFElectronByIP2dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('positive'),
    use3d = cms.bool(False)
)


process.positiveSoftPFElectronByIP3dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('positive'),
    use3d = cms.bool(True)
)


process.positiveSoftPFElectronByPtComputer = cms.ESProducer("LeptonTaggerByPtESProducer",
    ipSign = cms.string('positive')
)


process.positiveSoftPFElectronComputer = cms.ESProducer("ElectronTaggerESProducer",
    gbrForestLabel = cms.string('btag_SoftPFElectron_BDT'),
    ipSign = cms.string('positive'),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFElectron_BDT.weights.xml.gz')
)


process.positiveSoftPFMuonByIP2dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('positive'),
    use3d = cms.bool(False)
)


process.positiveSoftPFMuonByIP3dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('positive'),
    use3d = cms.bool(True)
)


process.positiveSoftPFMuonByPtComputer = cms.ESProducer("LeptonTaggerByPtESProducer",
    ipSign = cms.string('positive')
)


process.positiveSoftPFMuonComputer = cms.ESProducer("MuonTaggerESProducer",
    gbrForestLabel = cms.string('btag_SoftPFMuon_BDT'),
    ipSign = cms.string('positive'),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFMuon_BDT.weights.xml.gz')
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


process.simpleSecondaryVertex2TrkComputer = cms.ESProducer("SimpleSecondaryVertexESProducer",
    minTracks = cms.uint32(2),
    unBoost = cms.bool(False),
    use3d = cms.bool(True),
    useSignificance = cms.bool(True)
)


process.simpleSecondaryVertex3TrkComputer = cms.ESProducer("SimpleSecondaryVertexESProducer",
    minTracks = cms.uint32(3),
    unBoost = cms.bool(False),
    use3d = cms.bool(True),
    useSignificance = cms.bool(True)
)


process.sistripconn = cms.ESProducer("SiStripConnectivity")


process.softPFElectronByIP2dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('any'),
    use3d = cms.bool(False)
)


process.softPFElectronByIP3dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('any'),
    use3d = cms.bool(True)
)


process.softPFElectronByPtComputer = cms.ESProducer("LeptonTaggerByPtESProducer",
    ipSign = cms.string('any')
)


process.softPFElectronComputer = cms.ESProducer("ElectronTaggerESProducer",
    gbrForestLabel = cms.string('btag_SoftPFElectron_BDT'),
    ipSign = cms.string('any'),
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFElectron_BDT.weights.xml.gz')
)


process.softPFMuonByIP2dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('any'),
    use3d = cms.bool(False)
)


process.softPFMuonByIP3dComputer = cms.ESProducer("LeptonTaggerByIPESProducer",
    ipSign = cms.string('any'),
    use3d = cms.bool(True)
)


process.softPFMuonByPtComputer = cms.ESProducer("LeptonTaggerByPtESProducer",
    ipSign = cms.string('any')
)


process.softPFMuonComputer = cms.ESProducer("MuonTaggerESProducer",
    gbrForestLabel = cms.string('btag_SoftPFMuon_BDT'),
    ipSign = cms.string('any'),
    useAdaBoost = cms.bool(True),
    useCondDB = cms.bool(True),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SoftLepton/data/SoftPFMuon_BDT.weights.xml.gz')
)


process.stripCPEESProducer = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('stripCPE'),
    ComponentType = cms.string('SimpleStripCPE'),
    parameters = cms.PSet(

    )
)


process.trackCounting3D2ndComputer = cms.ESProducer("TrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(2),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.trackCounting3D3rdComputer = cms.ESProducer("TrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(0),
    max_pT = cms.double(500),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3),
    maximumDecayLength = cms.double(5.0),
    maximumDistanceToJetAxis = cms.double(0.07),
    min_pT = cms.double(120),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(-1),
    nthTrack = cms.int32(3),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.trackerGeometryDB = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(False)
)


process.trackerNumberingGeometryDB = cms.ESProducer("TrackerGeometricDetESModule",
    appendToDataLabel = cms.string(''),
    fromDDD = cms.bool(False)
)


process.trackerTopology = cms.ESProducer("TrackerTopologyEP",
    appendToDataLabel = cms.string('')
)


process.BTagRecord = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('JetTagComputerRecord')
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
    globaltag = cms.string('103X_upgrade2018_realistic_HI_v11'),
    pfnPostfix = cms.untracked.string(''),
    pfnPrefix = cms.untracked.string(''),
    snapshotTime = cms.string('9999-12-31 23:59:59.000'),
    toGet = cms.VPSet(
        cms.PSet(
            connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
            label = cms.untracked.string('HFtowers'),
            record = cms.string('HeavyIonRcd'),
            tag = cms.string('CentralityTable_HFtowers200_HydjetDrum5F_v1032x01_mc')
        ), 
        cms.PSet(
            connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
            record = cms.string('BTagTrackProbability3DRcd'),
            tag = cms.string('JPcalib_MC103X_2018PbPb_v4')
        )
    )
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


process.HepPDTESSource = cms.ESSource("HepPDTESSource",
    pdtFileName = cms.FileInPath('SimGeneral/HepPDTESSource/data/pythiaparticle.tbl')
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
            depVsNeutrons = cms.vdouble(5.543e-10, 8.012e-10),
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
            depVsNeutrons = cms.vdouble(5.543e-10, 8.012e-10),
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


process.jec = cms.ESSource("PoolDBESSource",
    DBParameters = cms.PSet(
        messageLevel = cms.untracked.int32(0)
    ),
    timetype = cms.string('runnumber'),
    toGet = cms.VPSet(
        cms.PSet(
            connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
            label = cms.untracked.string('AK2PF'),
            record = cms.string('JetCorrectionsRecord'),
            tag = cms.string('JetCorrectorParametersCollection_Autumn18_HI_V6_MC_AK2PF')
        ), 
        cms.PSet(
            connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
            label = cms.untracked.string('AK3PF'),
            record = cms.string('JetCorrectionsRecord'),
            tag = cms.string('JetCorrectorParametersCollection_Autumn18_HI_V6_MC_AK3PF')
        ), 
        cms.PSet(
            connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
            label = cms.untracked.string('AK4PF'),
            record = cms.string('JetCorrectionsRecord'),
            tag = cms.string('JetCorrectorParametersCollection_Autumn18_HI_V6_MC_AK4PF')
        ), 
        cms.PSet(
            connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
            label = cms.untracked.string('AK5PF'),
            record = cms.string('JetCorrectionsRecord'),
            tag = cms.string('JetCorrectorParametersCollection_Autumn18_HI_V6_MC_AK5PF')
        ), 
        cms.PSet(
            connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
            label = cms.untracked.string('AK6PF'),
            record = cms.string('JetCorrectionsRecord'),
            tag = cms.string('JetCorrectorParametersCollection_Autumn18_HI_V6_MC_AK6PF')
        )
    )
)


process.prefer("es_hardcode")

process.prefer("jec")

process.combinedMVATask = cms.Task(process.combinedMVAV2BJetTags, process.negativeCombinedMVAV2BJetTags, process.pfCombinedMVAV2BJetTags, process.pfNegativeCombinedMVAV2BJetTags, process.pfPositiveCombinedMVAV2BJetTags, process.positiveCombinedMVAV2BJetTags)


process.secondaryVertexTask = cms.Task(process.bToCharmDecayVertexMerged, process.combinedInclusiveSecondaryVertexV2BJetTags, process.combinedSecondaryVertexV2BJetTags, process.doubleSecondaryVertexHighEffBJetTags, process.ghostTrackBJetTags, process.ghostTrackVertexTagInfos, process.inclusiveSecondaryVertexFinderFilteredNegativeTagInfos, process.inclusiveSecondaryVertexFinderFilteredTagInfos, process.inclusiveSecondaryVertexFinderNegativeTagInfos, process.inclusiveSecondaryVertexFinderTagInfos, process.inclusiveSecondaryVerticesFiltered, process.negativeCombinedInclusiveSecondaryVertexV2BJetTags, process.negativeCombinedSecondaryVertexV2BJetTags, process.negativeSimpleInclusiveSecondaryVertexHighEffBJetTags, process.negativeSimpleInclusiveSecondaryVertexHighPurBJetTags, process.negativeSimpleSecondaryVertexHighEffBJetTags, process.negativeSimpleSecondaryVertexHighPurBJetTags, process.pfBoostedDoubleSVAK8TagInfos, process.pfBoostedDoubleSVCA15TagInfos, process.pfBoostedDoubleSecondaryVertexAK8BJetTags, process.pfBoostedDoubleSecondaryVertexCA15BJetTags, process.pfCombinedInclusiveSecondaryVertexV2BJetTags, process.pfCombinedSecondaryVertexV2BJetTags, process.pfGhostTrackBJetTags, process.pfGhostTrackVertexTagInfos, process.pfInclusiveSecondaryVertexFinderAK8TagInfos, process.pfInclusiveSecondaryVertexFinderCA15TagInfos, process.pfInclusiveSecondaryVertexFinderNegativeTagInfos, process.pfInclusiveSecondaryVertexFinderTagInfos, process.pfNegativeCombinedInclusiveSecondaryVertexV2BJetTags, process.pfNegativeCombinedSecondaryVertexV2BJetTags, process.pfNegativeSimpleInclusiveSecondaryVertexHighEffBJetTags, process.pfNegativeSimpleInclusiveSecondaryVertexHighPurBJetTags, process.pfNegativeSimpleSecondaryVertexHighEffBJetTags, process.pfNegativeSimpleSecondaryVertexHighPurBJetTags, process.pfPositiveCombinedInclusiveSecondaryVertexV2BJetTags, process.pfPositiveCombinedSecondaryVertexV2BJetTags, process.pfSecondaryVertexNegativeTagInfos, process.pfSecondaryVertexTagInfos, process.pfSimpleInclusiveSecondaryVertexHighEffBJetTags, process.pfSimpleInclusiveSecondaryVertexHighPurBJetTags, process.pfSimpleSecondaryVertexHighEffBJetTags, process.pfSimpleSecondaryVertexHighPurBJetTags, process.positiveCombinedInclusiveSecondaryVertexV2BJetTags, process.positiveCombinedSecondaryVertexV2BJetTags, process.secondaryVertexNegativeTagInfos, process.secondaryVertexTagInfos, process.simpleInclusiveSecondaryVertexHighEffBJetTags, process.simpleInclusiveSecondaryVertexHighPurBJetTags, process.simpleSecondaryVertexHighEffBJetTags, process.simpleSecondaryVertexHighPurBJetTags)


process.legacyBTaggingTask = cms.Task(process.combinedInclusiveSecondaryVertexV2BJetTags, process.combinedMVAV2BJetTags, process.combinedSecondaryVertexV2BJetTags, process.ghostTrackBJetTags, process.ghostTrackVertexTagInfos, process.impactParameterTagInfos, process.inclusiveSecondaryVertexFinderTagInfos, process.jetBProbabilityBJetTags, process.jetProbabilityBJetTags, process.secondaryVertexTagInfos, process.simpleSecondaryVertexHighEffBJetTags, process.softPFElectronBJetTags, process.softPFElectronsTagInfos, process.softPFMuonBJetTags, process.softPFMuonsTagInfos, process.trackCountingHighEffBJetTags)


process.pfDeepCSVTask = cms.Task(process.pfDeepCMVAJetTags, process.pfDeepCMVATagInfos, process.pfDeepCSVJetTags, process.pfDeepCSVTagInfos)


process.pfDeepFlavourTask = cms.Task(process.pfDeepFlavourJetTags, process.pfDeepFlavourTagInfos, process.primaryVertexAssociation, process.puppi)


process.CombinedCharmTagJetTagsTask = cms.Task(process.pfNegativeCombinedCvsBJetTags, process.pfNegativeCombinedCvsLJetTags, process.pfPositiveCombinedCvsBJetTags, process.pfPositiveCombinedCvsLJetTags)


process.patJetFlavourIdLegacyTask = cms.Task(process.patJetFlavourAssociationLegacy, process.patJetPartonAssociationLegacy, process.patJetPartonsLegacy)


process.pfDeepBoostedJetTask = cms.Task(process.pfDeepBoostedDiscriminatorsJetTags, process.pfDeepBoostedJetTagInfos, process.pfDeepBoostedJetTags, process.pfMassDecorrelatedDeepBoostedDiscriminatorsJetTags, process.pfMassDecorrelatedDeepBoostedJetTags, process.primaryVertexAssociation, process.puppi)


process.impactParameterTask = cms.Task(process.impactParameterMVABJetTags, process.impactParameterTagInfos, process.jetBProbabilityBJetTags, process.jetProbabilityBJetTags, process.negativeOnlyJetBProbabilityBJetTags, process.negativeOnlyJetProbabilityBJetTags, process.negativeTrackCountingHighEffBJetTags, process.negativeTrackCountingHighPurBJetTags, process.pfImpactParameterAK8TagInfos, process.pfImpactParameterCA15TagInfos, process.pfImpactParameterTagInfos, process.pfJetBProbabilityBJetTags, process.pfJetProbabilityBJetTags, process.pfNegativeOnlyJetBProbabilityBJetTags, process.pfNegativeOnlyJetProbabilityBJetTags, process.pfNegativeTrackCountingHighEffBJetTags, process.pfNegativeTrackCountingHighPurBJetTags, process.pfPositiveOnlyJetBProbabilityBJetTags, process.pfPositiveOnlyJetProbabilityBJetTags, process.pfTrackCountingHighEffBJetTags, process.pfTrackCountingHighPurBJetTags, process.positiveOnlyJetBProbabilityBJetTags, process.positiveOnlyJetProbabilityBJetTags, process.trackCountingHighEffBJetTags, process.trackCountingHighPurBJetTags)


process.inclusiveCandidateVertexingCvsLTask = cms.Task(process.candidateVertexArbitratorCvsL, process.candidateVertexMergerCvsL, process.inclusiveCandidateSecondaryVerticesCvsL, process.inclusiveCandidateVertexFinderCvsL)


process.inclusiveVertexingTask = cms.Task(process.inclusiveSecondaryVertices, process.inclusiveVertexFinder, process.trackVertexArbitrator, process.vertexMerger)


process.softLeptonTask = cms.Task(process.negativeSoftPFElectronBJetTags, process.negativeSoftPFElectronByIP2dBJetTags, process.negativeSoftPFElectronByIP3dBJetTags, process.negativeSoftPFElectronByPtBJetTags, process.negativeSoftPFMuonBJetTags, process.negativeSoftPFMuonByIP2dBJetTags, process.negativeSoftPFMuonByIP3dBJetTags, process.negativeSoftPFMuonByPtBJetTags, process.positiveSoftPFElectronBJetTags, process.positiveSoftPFElectronByIP2dBJetTags, process.positiveSoftPFElectronByIP3dBJetTags, process.positiveSoftPFElectronByPtBJetTags, process.positiveSoftPFMuonBJetTags, process.positiveSoftPFMuonByIP2dBJetTags, process.positiveSoftPFMuonByIP3dBJetTags, process.positiveSoftPFMuonByPtBJetTags, process.softPFElectronBJetTags, process.softPFElectronByIP2dBJetTags, process.softPFElectronByIP3dBJetTags, process.softPFElectronByPtBJetTags, process.softPFElectronsTagInfos, process.softPFMuonBJetTags, process.softPFMuonByIP2dBJetTags, process.softPFMuonByIP3dBJetTags, process.softPFMuonByPtBJetTags, process.softPFMuonsTagInfos)


process.inclusiveCandidateVertexingTask = cms.Task(process.candidateVertexArbitrator, process.candidateVertexMerger, process.inclusiveCandidateSecondaryVertices, process.inclusiveCandidateVertexFinder)


process.patJetFlavourIdTask = cms.Task(process.patJetFlavourAssociation, process.patJetPartons)


process.pfBTaggingTask = cms.Task(process.inclusiveCandidateVertexingTask, process.pfChargeBJetTags, process.pfCombinedInclusiveSecondaryVertexV2BJetTags, process.pfCombinedMVAV2BJetTags, process.pfCombinedSecondaryVertexV2BJetTags, process.pfDeepCSVTask, process.pfGhostTrackBJetTags, process.pfGhostTrackVertexTagInfos, process.pfImpactParameterTagInfos, process.pfInclusiveSecondaryVertexFinderTagInfos, process.pfJetBProbabilityBJetTags, process.pfJetProbabilityBJetTags, process.pfSecondaryVertexTagInfos, process.pfSimpleInclusiveSecondaryVertexHighEffBJetTags, process.pfSimpleSecondaryVertexHighEffBJetTags, process.pfTrackCountingHighEffBJetTags, process.softPFElectronBJetTags, process.softPFElectronsTagInfos, process.softPFMuonBJetTags, process.softPFMuonsTagInfos)


process.cTaggingTask = cms.Task(process.CombinedCharmTagJetTagsTask, process.pfCombinedCvsBJetTags, process.pfCombinedCvsLJetTags, process.pfInclusiveSecondaryVertexFinderCvsLTagInfos, process.pfInclusiveSecondaryVertexFinderNegativeCvsLTagInfos, process.pfSecondaryVertexTagInfos)


process.pfCTaggingTask = cms.Task(process.inclusiveCandidateVertexingCvsLTask, process.pfCombinedCvsBJetTags, process.pfCombinedCvsLJetTags, process.pfInclusiveSecondaryVertexFinderCvsLTagInfos)


process.btaggingTask = cms.Task(process.pfBTaggingTask, process.pfCTaggingTask)


process.pfDeepCSV = cms.Sequence(process.pfDeepCSVTask)


process.akFlowPuCs4PFJetBtaggingSV = cms.Sequence(process.akFlowPuCs4PFImpactParameterTagInfos+process.akFlowPuCs4PFSecondaryVertexTagInfos+process.akFlowPuCs4PFSimpleSecondaryVertexHighEffBJetTags+process.akFlowPuCs4PFSimpleSecondaryVertexHighPurBJetTags+process.akFlowPuCs4PFCombinedSecondaryVertexBJetTags+process.akFlowPuCs4PFCombinedSecondaryVertexV2BJetTags)


process.trackSequencesPbPb = cms.Sequence(process.anaTrack)


process.pfCTagging = cms.Sequence(process.pfCTaggingTask)


process.patJetFlavourId = cms.Sequence(process.patJetFlavourIdTask)


process.hfCoincFilterTh4 = cms.Sequence(process.towersAboveThresholdTh4+process.hfPosTowersTh4+process.hfNegTowersTh4+process.hfPosFilterTh4+process.hfNegFilterTh4)


process.btagging = cms.Sequence(process.btaggingTask)


process.ak4PFJetBtaggingNegSV = cms.Sequence(process.ak4PFImpactParameterTagInfos+process.ak4PFSecondaryVertexNegativeTagInfos+process.ak4PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.ak4PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.ak4PFNegativeCombinedSecondaryVertexBJetTags+process.ak4PFPositiveCombinedSecondaryVertexBJetTags+process.ak4PFNegativeCombinedSecondaryVertexV2BJetTags+process.ak4PFPositiveCombinedSecondaryVertexV2BJetTags)


process.akCs4PFPatJetFlavourIdLegacy = cms.Sequence(process.akCs4PFPatJetPartonAssociationLegacy+process.akCs4PFPatJetFlavourAssociationLegacy)


process.inclusiveCandidateVertexing = cms.Sequence(process.inclusiveCandidateVertexingTask)


process.ak4PFJetBtaggingMu = cms.Sequence(process.ak4PFSoftPFMuonsTagInfos+process.ak4PFSoftPFMuonBJetTags+process.ak4PFSoftPFMuonByIP3dBJetTags+process.ak4PFSoftPFMuonByPtBJetTags+process.ak4PFNegativeSoftPFMuonByPtBJetTags+process.ak4PFPositiveSoftPFMuonByPtBJetTags)


process.inclusiveVertexing = cms.Sequence(process.inclusiveVertexingTask)


process.akPu3CaloJetBtaggingSV = cms.Sequence(process.akPu3CaloImpactParameterTagInfos+process.akPu3CaloSecondaryVertexTagInfos+process.akPu3CaloSimpleSecondaryVertexHighEffBJetTags+process.akPu3CaloSimpleSecondaryVertexHighPurBJetTags+process.akPu3CaloCombinedSecondaryVertexBJetTags+process.akPu3CaloCombinedSecondaryVertexV2BJetTags)


process.akFlowPuCs4PFPatJetFlavourIdLegacy = cms.Sequence(process.akFlowPuCs4PFPatJetPartonAssociationLegacy+process.akFlowPuCs4PFPatJetFlavourAssociationLegacy)


process.pfBTagging = cms.Sequence(process.pfBTaggingTask)


process.akPu3CaloPatJetFlavourIdLegacy = cms.Sequence(process.akPu3CaloPatJetPartonAssociationLegacy+process.akPu3CaloPatJetFlavourAssociationLegacy)


process.hfCoincFilterTh5 = cms.Sequence(process.towersAboveThresholdTh5+process.hfPosTowersTh5+process.hfNegTowersTh5+process.hfPosFilterTh5+process.hfNegFilterTh5)


process.hfCoincFilterTh2 = cms.Sequence(process.towersAboveThresholdTh2+process.hfPosTowersTh2+process.hfNegTowersTh2+process.hfPosFilterTh2+process.hfNegFilterTh2)


process.hfCoincFilterTh3 = cms.Sequence(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter+process.hfNegFilter)


process.akCs3PFJetBtaggingNegSV = cms.Sequence(process.akCs3PFImpactParameterTagInfos+process.akCs3PFSecondaryVertexNegativeTagInfos+process.akCs3PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.akCs3PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.akCs3PFNegativeCombinedSecondaryVertexBJetTags+process.akCs3PFPositiveCombinedSecondaryVertexBJetTags+process.akCs3PFNegativeCombinedSecondaryVertexV2BJetTags+process.akCs3PFPositiveCombinedSecondaryVertexV2BJetTags)


process.inclusiveCandidateVertexingCvsL = cms.Sequence(process.inclusiveCandidateVertexingCvsLTask)


process.ak3PFJetBtaggingMu = cms.Sequence(process.ak3PFSoftPFMuonsTagInfos+process.ak3PFSoftPFMuonBJetTags+process.ak3PFSoftPFMuonByIP3dBJetTags+process.ak3PFSoftPFMuonByPtBJetTags+process.ak3PFNegativeSoftPFMuonByPtBJetTags+process.ak3PFPositiveSoftPFMuonByPtBJetTags)


process.akPu4PFJetBtaggingNegSV = cms.Sequence(process.akPu4PFImpactParameterTagInfos+process.akPu4PFSecondaryVertexNegativeTagInfos+process.akPu4PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.akPu4PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.akPu4PFNegativeCombinedSecondaryVertexBJetTags+process.akPu4PFPositiveCombinedSecondaryVertexBJetTags+process.akPu4PFNegativeCombinedSecondaryVertexV2BJetTags+process.akPu4PFPositiveCombinedSecondaryVertexV2BJetTags)


process.akPu3PFJetBtaggingMu = cms.Sequence(process.akPu3PFSoftPFMuonsTagInfos+process.akPu3PFSoftPFMuonBJetTags+process.akPu3PFSoftPFMuonByIP3dBJetTags+process.akPu3PFSoftPFMuonByPtBJetTags+process.akPu3PFNegativeSoftPFMuonByPtBJetTags+process.akPu3PFPositiveSoftPFMuonByPtBJetTags)


process.akPu3CaloJetBtaggingMu = cms.Sequence(process.akPu3CaloSoftPFMuonsTagInfos+process.akPu3CaloSoftPFMuonBJetTags+process.akPu3CaloSoftPFMuonByIP3dBJetTags+process.akPu3CaloSoftPFMuonByPtBJetTags+process.akPu3CaloNegativeSoftPFMuonByPtBJetTags+process.akPu3CaloPositiveSoftPFMuonByPtBJetTags)


process.akCs4PFJetBtaggingIP = cms.Sequence(process.akCs4PFImpactParameterTagInfos+process.akCs4PFTrackCountingHighEffBJetTags+process.akCs4PFTrackCountingHighPurBJetTags+process.akCs4PFJetProbabilityBJetTags+process.akCs4PFJetBProbabilityBJetTags)


process.hfCoincFilter3Th4 = cms.Sequence(process.towersAboveThresholdTh4+process.hfPosTowersTh4+process.hfNegTowersTh4+process.hfPosFilter3Th4+process.hfNegFilter3Th4)


process.hfCoincFilter3Th2 = cms.Sequence(process.towersAboveThresholdTh2+process.hfPosTowersTh2+process.hfNegTowersTh2+process.hfPosFilter3Th2+process.hfNegFilter3Th2)


process.hfCoincFilter3Th3 = cms.Sequence(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter3+process.hfNegFilter3)


process.akCs3PFJetBtaggingIP = cms.Sequence(process.akCs3PFImpactParameterTagInfos+process.akCs3PFTrackCountingHighEffBJetTags+process.akCs3PFTrackCountingHighPurBJetTags+process.akCs3PFJetProbabilityBJetTags+process.akCs3PFJetBProbabilityBJetTags)


process.akPu4CaloJetBtaggingMu = cms.Sequence(process.akPu4CaloSoftPFMuonsTagInfos+process.akPu4CaloSoftPFMuonBJetTags+process.akPu4CaloSoftPFMuonByIP3dBJetTags+process.akPu4CaloSoftPFMuonByPtBJetTags+process.akPu4CaloNegativeSoftPFMuonByPtBJetTags+process.akPu4CaloPositiveSoftPFMuonByPtBJetTags)


process.legacyBTagging = cms.Sequence(process.legacyBTaggingTask)


process.akCs3PFPatJetFlavourIdLegacy = cms.Sequence(process.akCs3PFPatJetPartonAssociationLegacy+process.akCs3PFPatJetFlavourAssociationLegacy)


process.ak3PFJetBtaggingSV = cms.Sequence(process.ak3PFImpactParameterTagInfos+process.ak3PFSecondaryVertexTagInfos+process.ak3PFSimpleSecondaryVertexHighEffBJetTags+process.ak3PFSimpleSecondaryVertexHighPurBJetTags+process.ak3PFCombinedSecondaryVertexBJetTags+process.ak3PFCombinedSecondaryVertexV2BJetTags)


process.akCs4PFJetSequence_data = cms.Sequence(process.akCs4PFcorr+process.akCs4PFJetTracksAssociatorAtVertex+process.akCs4PFJetBtaggingIP+process.akCs4PFImpactParameterTagInfos+process.akCs4PFSecondaryVertexTagInfos+process.akCs4PFSimpleSecondaryVertexHighEffBJetTags+process.akCs4PFSimpleSecondaryVertexHighPurBJetTags+process.akCs4PFCombinedSecondaryVertexBJetTags+process.akCs4PFCombinedSecondaryVertexV2BJetTags+process.akCs4PFNjettiness+process.akCs4PFpatJetsWithBtagging+process.akCs4PFJetAnalyzer)


process.akPu3PFJetBtaggingNegSV = cms.Sequence(process.akPu3PFImpactParameterTagInfos+process.akPu3PFSecondaryVertexNegativeTagInfos+process.akPu3PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.akPu3PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.akPu3PFNegativeCombinedSecondaryVertexBJetTags+process.akPu3PFPositiveCombinedSecondaryVertexBJetTags+process.akPu3PFNegativeCombinedSecondaryVertexV2BJetTags+process.akPu3PFPositiveCombinedSecondaryVertexV2BJetTags)


process.akPu4PFJetBtaggingSV = cms.Sequence(process.akPu4PFImpactParameterTagInfos+process.akPu4PFSecondaryVertexTagInfos+process.akPu4PFSimpleSecondaryVertexHighEffBJetTags+process.akPu4PFSimpleSecondaryVertexHighPurBJetTags+process.akPu4PFCombinedSecondaryVertexBJetTags+process.akPu4PFCombinedSecondaryVertexV2BJetTags)


process.ak5JTAExplicit = cms.Sequence(process.ak5JetTracksAssociatorExplicit)


process.akCs4PFJetBtaggingSV = cms.Sequence(process.akCs4PFImpactParameterTagInfos+process.akCs4PFSecondaryVertexTagInfos+process.akCs4PFSimpleSecondaryVertexHighEffBJetTags+process.akCs4PFSimpleSecondaryVertexHighPurBJetTags+process.akCs4PFCombinedSecondaryVertexBJetTags+process.akCs4PFCombinedSecondaryVertexV2BJetTags)


process.ak3PFJetBtaggingNegSV = cms.Sequence(process.ak3PFImpactParameterTagInfos+process.ak3PFSecondaryVertexNegativeTagInfos+process.ak3PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.ak3PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.ak3PFNegativeCombinedSecondaryVertexBJetTags+process.ak3PFPositiveCombinedSecondaryVertexBJetTags+process.ak3PFNegativeCombinedSecondaryVertexV2BJetTags+process.ak3PFPositiveCombinedSecondaryVertexV2BJetTags)


process.akFlowPuCs3PFJetBtaggingIP = cms.Sequence(process.akFlowPuCs3PFImpactParameterTagInfos+process.akFlowPuCs3PFTrackCountingHighEffBJetTags+process.akFlowPuCs3PFTrackCountingHighPurBJetTags+process.akFlowPuCs3PFJetProbabilityBJetTags+process.akFlowPuCs3PFJetBProbabilityBJetTags)


process.akCs4PFJetBtaggingNegSV = cms.Sequence(process.akCs4PFImpactParameterTagInfos+process.akCs4PFSecondaryVertexNegativeTagInfos+process.akCs4PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.akCs4PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.akCs4PFNegativeCombinedSecondaryVertexBJetTags+process.akCs4PFPositiveCombinedSecondaryVertexBJetTags+process.akCs4PFNegativeCombinedSecondaryVertexV2BJetTags+process.akCs4PFPositiveCombinedSecondaryVertexV2BJetTags)


process.akFlowPuCs4PFJetBtaggingMu = cms.Sequence(process.akFlowPuCs4PFSoftPFMuonsTagInfos+process.akFlowPuCs4PFSoftPFMuonBJetTags+process.akFlowPuCs4PFSoftPFMuonByIP3dBJetTags+process.akFlowPuCs4PFSoftPFMuonByPtBJetTags+process.akFlowPuCs4PFNegativeSoftPFMuonByPtBJetTags+process.akFlowPuCs4PFPositiveSoftPFMuonByPtBJetTags)


process.hfCoincFilter4Th5 = cms.Sequence(process.towersAboveThresholdTh5+process.hfPosTowersTh5+process.hfNegTowersTh5+process.hfPosFilter4Th5+process.hfNegFilter4Th5)


process.hfCoincFilter4Th4 = cms.Sequence(process.towersAboveThresholdTh4+process.hfPosTowersTh4+process.hfNegTowersTh4+process.hfPosFilter4Th4+process.hfNegFilter4Th4)


process.hfCoincFilter4Th3 = cms.Sequence(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter4+process.hfNegFilter4)


process.akPu3PFJetBtaggingSV = cms.Sequence(process.akPu3PFImpactParameterTagInfos+process.akPu3PFSecondaryVertexTagInfos+process.akPu3PFSimpleSecondaryVertexHighEffBJetTags+process.akPu3PFSimpleSecondaryVertexHighPurBJetTags+process.akPu3PFCombinedSecondaryVertexBJetTags+process.akPu3PFCombinedSecondaryVertexV2BJetTags)


process.akPu4PFPatJetFlavourIdLegacy = cms.Sequence(process.akPu4PFPatJetPartonAssociationLegacy+process.akPu4PFPatJetFlavourAssociationLegacy)


process.hfCoincFilter2Th5 = cms.Sequence(process.towersAboveThresholdTh5+process.hfPosTowersTh5+process.hfNegTowersTh5+process.hfPosFilter2Th5+process.hfNegFilter2Th5)


process.hfCoincFilter2Th4 = cms.Sequence(process.towersAboveThresholdTh4+process.hfPosTowersTh4+process.hfNegTowersTh4+process.hfPosFilter2Th4+process.hfNegFilter2Th4)


process.hfCoincFilter2Th3 = cms.Sequence(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter2+process.hfNegFilter2)


process.hfCoincFilter2Th2 = cms.Sequence(process.towersAboveThresholdTh2+process.hfPosTowersTh2+process.hfNegTowersTh2+process.hfPosFilter2Th2+process.hfNegFilter2Th2)


process.ak4PFJetBtaggingIP = cms.Sequence(process.ak4PFImpactParameterTagInfos+process.ak4PFTrackCountingHighEffBJetTags+process.ak4PFTrackCountingHighPurBJetTags+process.ak4PFJetProbabilityBJetTags+process.ak4PFJetBProbabilityBJetTags)


process.akPu4PFJetBtaggingMu = cms.Sequence(process.akPu4PFSoftPFMuonsTagInfos+process.akPu4PFSoftPFMuonBJetTags+process.akPu4PFSoftPFMuonByIP3dBJetTags+process.akPu4PFSoftPFMuonByPtBJetTags+process.akPu4PFNegativeSoftPFMuonByPtBJetTags+process.akPu4PFPositiveSoftPFMuonByPtBJetTags)


process.ak5JTA = cms.Sequence(process.ak5JetTracksAssociatorAtVertexPF+process.ak5JetTracksAssociatorAtVertex+process.ak5JetTracksAssociatorAtCaloFace+process.ak5JetExtender)


process.akFlowPuCs4PFJetBtaggingNegSV = cms.Sequence(process.akFlowPuCs4PFImpactParameterTagInfos+process.akFlowPuCs4PFSecondaryVertexNegativeTagInfos+process.akFlowPuCs4PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.akFlowPuCs4PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.akFlowPuCs4PFNegativeCombinedSecondaryVertexBJetTags+process.akFlowPuCs4PFPositiveCombinedSecondaryVertexBJetTags+process.akFlowPuCs4PFNegativeCombinedSecondaryVertexV2BJetTags+process.akFlowPuCs4PFPositiveCombinedSecondaryVertexV2BJetTags)


process.akPu3CaloJetBtaggingNegSV = cms.Sequence(process.akPu3CaloImpactParameterTagInfos+process.akPu3CaloSecondaryVertexNegativeTagInfos+process.akPu3CaloNegativeSimpleSecondaryVertexHighEffBJetTags+process.akPu3CaloNegativeSimpleSecondaryVertexHighPurBJetTags+process.akPu3CaloNegativeCombinedSecondaryVertexBJetTags+process.akPu3CaloPositiveCombinedSecondaryVertexBJetTags+process.akPu3CaloNegativeCombinedSecondaryVertexV2BJetTags+process.akPu3CaloPositiveCombinedSecondaryVertexV2BJetTags)


process.akPu4CaloJetBtaggingSV = cms.Sequence(process.akPu4CaloImpactParameterTagInfos+process.akPu4CaloSecondaryVertexTagInfos+process.akPu4CaloSimpleSecondaryVertexHighEffBJetTags+process.akPu4CaloSimpleSecondaryVertexHighPurBJetTags+process.akPu4CaloCombinedSecondaryVertexBJetTags+process.akPu4CaloCombinedSecondaryVertexV2BJetTags)


process.patJetFlavourIdLegacy = cms.Sequence(process.patJetFlavourIdLegacyTask)


process.ak3PFJetBtaggingIP = cms.Sequence(process.ak3PFImpactParameterTagInfos+process.ak3PFTrackCountingHighEffBJetTags+process.ak3PFTrackCountingHighPurBJetTags+process.ak3PFJetProbabilityBJetTags+process.ak3PFJetBProbabilityBJetTags)


process.akFlowPuCs3PFJetBtaggingNegSV = cms.Sequence(process.akFlowPuCs3PFImpactParameterTagInfos+process.akFlowPuCs3PFSecondaryVertexNegativeTagInfos+process.akFlowPuCs3PFNegativeSimpleSecondaryVertexHighEffBJetTags+process.akFlowPuCs3PFNegativeSimpleSecondaryVertexHighPurBJetTags+process.akFlowPuCs3PFNegativeCombinedSecondaryVertexBJetTags+process.akFlowPuCs3PFPositiveCombinedSecondaryVertexBJetTags+process.akFlowPuCs3PFNegativeCombinedSecondaryVertexV2BJetTags+process.akFlowPuCs3PFPositiveCombinedSecondaryVertexV2BJetTags)


process.hfCoincFilter5Th2 = cms.Sequence(process.towersAboveThresholdTh2+process.hfPosTowersTh2+process.hfNegTowersTh2+process.hfPosFilter5Th2+process.hfNegFilter5Th2)


process.akFlowPuCs3PFPatJetFlavourIdLegacy = cms.Sequence(process.akFlowPuCs3PFPatJetPartonAssociationLegacy+process.akFlowPuCs3PFPatJetFlavourAssociationLegacy)


process.hfCoincFilter5Th3 = cms.Sequence(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter5+process.hfNegFilter5)


process.hfCoincFilter5Th4 = cms.Sequence(process.towersAboveThresholdTh4+process.hfPosTowersTh4+process.hfNegTowersTh4+process.hfPosFilter5Th4+process.hfNegFilter5Th4)


process.hfCoincFilter5Th5 = cms.Sequence(process.towersAboveThresholdTh5+process.hfPosTowersTh5+process.hfNegTowersTh5+process.hfPosFilter5Th5+process.hfNegFilter5Th5)


process.akCs3PFJetBtaggingMu = cms.Sequence(process.akCs3PFSoftPFMuonsTagInfos+process.akCs3PFSoftPFMuonBJetTags+process.akCs3PFSoftPFMuonByIP3dBJetTags+process.akCs3PFSoftPFMuonByPtBJetTags+process.akCs3PFNegativeSoftPFMuonByPtBJetTags+process.akCs3PFPositiveSoftPFMuonByPtBJetTags)


process.akCs4PFJetBtagging = cms.Sequence(process.akCs4PFJetBtaggingIP+process.akCs4PFJetBtaggingSV)


process.ak3PFPatJetFlavourId = cms.Sequence(process.ak3PFPatJetPartons+process.ak3PFPatJetFlavourAssociation)


process.akFlowPuCs3PFJetBtaggingSV = cms.Sequence(process.akFlowPuCs3PFImpactParameterTagInfos+process.akFlowPuCs3PFSecondaryVertexTagInfos+process.akFlowPuCs3PFSimpleSecondaryVertexHighEffBJetTags+process.akFlowPuCs3PFSimpleSecondaryVertexHighPurBJetTags+process.akFlowPuCs3PFCombinedSecondaryVertexBJetTags+process.akFlowPuCs3PFCombinedSecondaryVertexV2BJetTags)


process.akPu4CaloJetBtaggingIP = cms.Sequence(process.akPu4CaloImpactParameterTagInfos+process.akPu4CaloTrackCountingHighEffBJetTags+process.akPu4CaloTrackCountingHighPurBJetTags+process.akPu4CaloJetProbabilityBJetTags+process.akPu4CaloJetBProbabilityBJetTags)


process.akPu3CaloJetBtaggingIP = cms.Sequence(process.akPu3CaloImpactParameterTagInfos+process.akPu3CaloTrackCountingHighEffBJetTags+process.akPu3CaloTrackCountingHighPurBJetTags+process.akPu3CaloJetProbabilityBJetTags+process.akPu3CaloJetBProbabilityBJetTags)


process.hfCoincFilter3Th5 = cms.Sequence(process.towersAboveThresholdTh5+process.hfPosTowersTh5+process.hfNegTowersTh5+process.hfPosFilter3Th5+process.hfNegFilter3Th5)


process.akCs4PFJetBtaggingMu = cms.Sequence(process.akCs4PFSoftPFMuonsTagInfos+process.akCs4PFSoftPFMuonBJetTags+process.akCs4PFSoftPFMuonByIP3dBJetTags+process.akCs4PFSoftPFMuonByPtBJetTags+process.akCs4PFNegativeSoftPFMuonByPtBJetTags+process.akCs4PFPositiveSoftPFMuonByPtBJetTags)


process.akPu3PFJetBtaggingIP = cms.Sequence(process.akPu3PFImpactParameterTagInfos+process.akPu3PFTrackCountingHighEffBJetTags+process.akPu3PFTrackCountingHighPurBJetTags+process.akPu3PFJetProbabilityBJetTags+process.akPu3PFJetBProbabilityBJetTags)


process.akPu4PFJetBtaggingIP = cms.Sequence(process.akPu4PFImpactParameterTagInfos+process.akPu4PFTrackCountingHighEffBJetTags+process.akPu4PFTrackCountingHighPurBJetTags+process.akPu4PFJetProbabilityBJetTags+process.akPu4PFJetBProbabilityBJetTags)


process.akPu3CaloJetBtagging = cms.Sequence(process.akPu3CaloJetBtaggingIP+process.akPu3CaloJetBtaggingSV)


process.rhoSequence = cms.Sequence(process.PFTowers+process.kt4PFJets+process.kt4PFJetsForRho+process.hiFJRhoProducer+process.hiFJRhoProducerFinerBins+process.hiFJGridEmptyAreaCalculator+process.hiFJGridEmptyAreaCalculatorFinerBins+process.hiPuRhoR3Producer+process.pfcandCleanerPt4Eta2+process.ak4PFJetsForFlow+process.hiFJRhoFlowModulationProducer)


process.genCleanedSequence = cms.Sequence(process.genParticlesForJets+process.ak3HiGenJets+process.ak4HiGenJets+process.myPartons+process.cleanedPartons+process.ak3HiCleanedGenJets+process.ak4HiCleanedGenJets)


process.akFlowPuCs4PFJetBtaggingIP = cms.Sequence(process.akFlowPuCs4PFImpactParameterTagInfos+process.akFlowPuCs4PFTrackCountingHighEffBJetTags+process.akFlowPuCs4PFTrackCountingHighPurBJetTags+process.akFlowPuCs4PFJetProbabilityBJetTags+process.akFlowPuCs4PFJetBProbabilityBJetTags)


process.akPu4CaloPatJetFlavourIdLegacy = cms.Sequence(process.akPu4CaloPatJetPartonAssociationLegacy+process.akPu4CaloPatJetFlavourAssociationLegacy)


process.ak4PFJetBtaggingSV = cms.Sequence(process.ak4PFImpactParameterTagInfos+process.ak4PFSecondaryVertexTagInfos+process.ak4PFSimpleSecondaryVertexHighEffBJetTags+process.ak4PFSimpleSecondaryVertexHighPurBJetTags+process.ak4PFCombinedSecondaryVertexBJetTags+process.ak4PFCombinedSecondaryVertexV2BJetTags)


process.akPu4CaloJetBtaggingNegSV = cms.Sequence(process.akPu4CaloImpactParameterTagInfos+process.akPu4CaloSecondaryVertexNegativeTagInfos+process.akPu4CaloNegativeSimpleSecondaryVertexHighEffBJetTags+process.akPu4CaloNegativeSimpleSecondaryVertexHighPurBJetTags+process.akPu4CaloNegativeCombinedSecondaryVertexBJetTags+process.akPu4CaloPositiveCombinedSecondaryVertexBJetTags+process.akPu4CaloNegativeCombinedSecondaryVertexV2BJetTags+process.akPu4CaloPositiveCombinedSecondaryVertexV2BJetTags)


process.akFlowPuCs3PFJetBtagging = cms.Sequence(process.akFlowPuCs3PFJetBtaggingIP+process.akFlowPuCs3PFJetBtaggingSV)


process.genSignalSequence = cms.Sequence(process.genParticlesForJets+process.hiSignalGenParticles+process.genParticlesForJetsSignal+process.ak3HiGenJets+process.ak4HiGenJets+process.signalPartons+process.ak3HiSignalGenJets+process.ak4HiSignalGenJets+process.ak3HiGenNjettiness+process.ak4HiGenNjettiness)


process.akPu3CaloJetSequence_mc = cms.Sequence(process.akPu3Calomatch+process.akPu3Caloparton+process.akPu3Calocorr+process.akPu3CaloPatJetFlavourIdLegacy+process.akPu3CaloJetTracksAssociatorAtVertex+process.akPu3CaloJetBtagging+process.akPu3CaloNjettiness+process.akPu3CalopatJetsWithBtagging+process.akPu3CaloJetAnalyzer)


process.akFlowPuCs3PFJetSequence_mc = cms.Sequence(process.akFlowPuCs3PFmatch+process.akFlowPuCs3PFparton+process.akFlowPuCs3PFcorr+process.akFlowPuCs3PFPatJetFlavourIdLegacy+process.akFlowPuCs3PFJetTracksAssociatorAtVertex+process.akFlowPuCs3PFJetBtagging+process.akFlowPuCs3PFNjettiness+process.akFlowPuCs3PFpatJetsWithBtagging+process.akFlowPuCs3PFJetAnalyzer)


process.akFlowPuCs3PFJetSequence_mb = cms.Sequence(process.akFlowPuCs3PFJetSequence_mc)


process.hfCoincFilter4Th2 = cms.Sequence(process.towersAboveThresholdTh2+process.hfPosTowersTh2+process.hfNegTowersTh2+process.hfPosFilter4Th2+process.hfNegFilter4Th2)


process.akFlowPuCs3PFJetBtaggingMu = cms.Sequence(process.akFlowPuCs3PFSoftPFMuonsTagInfos+process.akFlowPuCs3PFSoftPFMuonBJetTags+process.akFlowPuCs3PFSoftPFMuonByIP3dBJetTags+process.akFlowPuCs3PFSoftPFMuonByPtBJetTags+process.akFlowPuCs3PFNegativeSoftPFMuonByPtBJetTags+process.akFlowPuCs3PFPositiveSoftPFMuonByPtBJetTags)


process.trackSequencesPP = cms.Sequence(process.ppTrack)


process.akPu3PFJetBtagging = cms.Sequence(process.akPu3PFJetBtaggingIP+process.akPu3PFJetBtaggingSV)


process.akCs3PFJetBtaggingSV = cms.Sequence(process.akCs3PFImpactParameterTagInfos+process.akCs3PFSecondaryVertexTagInfos+process.akCs3PFSimpleSecondaryVertexHighEffBJetTags+process.akCs3PFSimpleSecondaryVertexHighPurBJetTags+process.akCs3PFCombinedSecondaryVertexBJetTags+process.akCs3PFCombinedSecondaryVertexV2BJetTags)


process.akPu3PFPatJetFlavourIdLegacy = cms.Sequence(process.akPu3PFPatJetPartonAssociationLegacy+process.akPu3PFPatJetFlavourAssociationLegacy)


process.ak4PFPatJetFlavourId = cms.Sequence(process.ak4PFPatJetPartons+process.ak4PFPatJetFlavourAssociation)


process.collisionEventSelectionV2 = cms.Sequence(process.hfCoincFilter2Th4+process.primaryVertexFilter+process.siPixelRecHits+process.hltPixelClusterShapeFilter)


process.ak3PFJetBtagging = cms.Sequence(process.ak3PFJetBtaggingIP+process.ak3PFJetBtaggingSV)


process.ak3PFJetSequence_mc = cms.Sequence(process.ak3PFmatch+process.ak3PFparton+process.ak3PFcorr+process.ak3PFPatJetFlavourId+process.ak3PFJetTracksAssociatorAtVertex+process.ak3PFJetBtagging+process.ak3PFNjettiness+process.ak3PFpatJetsWithBtagging+process.ak3PFJetAnalyzer)


process.akPu4PFJetSequence_mb = cms.Sequence(process.akPu4PFmatch+process.akPu4PFparton+process.akPu4PFcorr+process.akPu4PFPatJetFlavourIdLegacy+process.akPu4PFJetTracksAssociatorAtVertex+process.akPu4PFJetBtaggingIP+process.akPu4PFImpactParameterTagInfos+process.akPu4PFSecondaryVertexTagInfos+process.akPu4PFSimpleSecondaryVertexHighEffBJetTags+process.akPu4PFSimpleSecondaryVertexHighPurBJetTags+process.akPu4PFCombinedSecondaryVertexBJetTags+process.akPu4PFCombinedSecondaryVertexV2BJetTags+process.akPu4PFNjettiness+process.akPu4PFpatJetsWithBtagging+process.akPu4PFJetAnalyzer)


process.akPu4PFJetSequence_mc = cms.Sequence(process.akPu4PFmatch+process.akPu4PFparton+process.akPu4PFcorr+process.akPu4PFPatJetFlavourIdLegacy+process.akPu4PFJetTracksAssociatorAtVertex+process.akPu4PFJetBtaggingIP+process.akPu4PFImpactParameterTagInfos+process.akPu4PFSecondaryVertexTagInfos+process.akPu4PFSimpleSecondaryVertexHighEffBJetTags+process.akPu4PFSimpleSecondaryVertexHighPurBJetTags+process.akPu4PFCombinedSecondaryVertexBJetTags+process.akPu4PFCombinedSecondaryVertexV2BJetTags+process.akPu4PFNjettiness+process.akPu4PFpatJetsWithBtagging+process.akPu4PFJetAnalyzer)


process.akFlowPuCs4PFJetBtagging = cms.Sequence(process.akFlowPuCs4PFJetBtaggingIP+process.akFlowPuCs4PFJetBtaggingSV)


process.akCs3PFJetBtagging = cms.Sequence(process.akCs3PFJetBtaggingIP+process.akCs3PFJetBtaggingSV)


process.akPu4CaloJetBtagging = cms.Sequence(process.akPu4CaloJetBtaggingIP+process.akPu4CaloImpactParameterTagInfos+process.akPu4CaloSecondaryVertexTagInfos+process.akPu4CaloSimpleSecondaryVertexHighEffBJetTags+process.akPu4CaloSimpleSecondaryVertexHighPurBJetTags+process.akPu4CaloCombinedSecondaryVertexBJetTags+process.akPu4CaloCombinedSecondaryVertexV2BJetTags)


process.ak4PFJetBtagging = cms.Sequence(process.ak4PFJetBtaggingIP+process.ak4PFJetBtaggingSV)


process.akPu3CaloJetSequence = cms.Sequence(process.akPu3CaloJetSequence_mc)


process.akPu3CaloJetSequence_data = cms.Sequence(process.akPu3Calocorr+process.akPu3CaloJetTracksAssociatorAtVertex+process.akPu3CaloJetBtagging+process.akPu3CaloNjettiness+process.akPu3CalopatJetsWithBtagging+process.akPu3CaloJetAnalyzer)


process.ak3PFJetSequence = cms.Sequence(process.ak3PFJetSequence_mc)


process.akCs4PFJetSequence_mc = cms.Sequence(process.akCs4PFmatch+process.akCs4PFparton+process.akCs4PFcorr+process.akCs4PFPatJetFlavourIdLegacy+process.akCs4PFJetTracksAssociatorAtVertex+process.akCs4PFJetBtagging+process.akCs4PFNjettiness+process.akCs4PFpatJetsWithBtagging+process.akCs4PFJetAnalyzer)


process.akCs4PFJetSequence_mb = cms.Sequence(process.akCs4PFJetSequence_mc)


process.akFlowPuCs3PFJetSequence = cms.Sequence(process.akFlowPuCs3PFJetSequence_mc)


process.akPu3CaloJetSequence_jec = cms.Sequence(process.akPu3CaloJetSequence_mc)


process.akCs3PFJetSequence_mc = cms.Sequence(process.akCs3PFmatch+process.akCs3PFparton+process.akCs3PFcorr+process.akCs3PFPatJetFlavourIdLegacy+process.akCs3PFJetTracksAssociatorAtVertex+process.akCs3PFJetBtagging+process.akCs3PFNjettiness+process.akCs3PFpatJetsWithBtagging+process.akCs3PFJetAnalyzer)


process.akCs4PFJetSequence_jec = cms.Sequence(process.akCs4PFJetSequence_mc)


process.akPu4CaloJetSequence_data = cms.Sequence(process.akPu4Calocorr+process.akPu4CaloJetTracksAssociatorAtVertex+process.akPu4CaloJetBtagging+process.akPu4CaloNjettiness+process.akPu4CalopatJetsWithBtagging+process.akPu4CaloJetAnalyzer)


process.akFlowPuCs3PFJetSequence_data = cms.Sequence(process.akFlowPuCs3PFcorr+process.akFlowPuCs3PFJetTracksAssociatorAtVertex+process.akFlowPuCs3PFJetBtagging+process.akFlowPuCs3PFNjettiness+process.akFlowPuCs3PFpatJetsWithBtagging+process.akFlowPuCs3PFJetAnalyzer)


process.akPu4PFJetSequence_jec = cms.Sequence(process.akPu4PFJetSequence_mc)


process.akFlowPuCs3PFJetSequence_jec = cms.Sequence(process.akFlowPuCs3PFJetSequence_mc)


process.ak4PFJetSequence_mc = cms.Sequence(process.ak4PFmatch+process.ak4PFparton+process.ak4PFcorr+process.ak4PFPatJetFlavourId+process.ak4PFJetTracksAssociatorAtVertex+process.ak4PFJetBtagging+process.ak4PFNjettiness+process.ak4PFpatJetsWithBtagging+process.ak4PFJetAnalyzer)


process.ak4PFJetSequence_mb = cms.Sequence(process.ak4PFJetSequence_mc)


process.akFlowPuCs4PFJetSequence_data = cms.Sequence(process.akFlowPuCs4PFcorr+process.akFlowPuCs4PFJetTracksAssociatorAtVertex+process.akFlowPuCs4PFJetBtagging+process.akFlowPuCs4PFNjettiness+process.akFlowPuCs4PFpatJetsWithBtagging+process.akFlowPuCs4PFJetAnalyzer)


process.ak3PFJetSequence_jec = cms.Sequence(process.ak3PFJetSequence_mc)


process.ak4PFJetSequence_data = cms.Sequence(process.ak4PFcorr+process.ak4PFJetTracksAssociatorAtVertex+process.ak4PFJetBtagging+process.ak4PFNjettiness+process.ak4PFpatJetsWithBtagging+process.ak4PFJetAnalyzer)


process.akPu4PFJetBtagging = cms.Sequence(process.akPu4PFJetBtaggingIP+process.akPu4PFImpactParameterTagInfos+process.akPu4PFSecondaryVertexTagInfos+process.akPu4PFSimpleSecondaryVertexHighEffBJetTags+process.akPu4PFSimpleSecondaryVertexHighPurBJetTags+process.akPu4PFCombinedSecondaryVertexBJetTags+process.akPu4PFCombinedSecondaryVertexV2BJetTags)


process.akCs4PFJetSequence = cms.Sequence(process.akCs4PFJetSequence_mc)


process.akCs3PFJetSequence = cms.Sequence(process.akCs3PFJetSequence_mc)


process.akPu3CaloJetSequence_mb = cms.Sequence(process.akPu3CaloJetSequence_mc)


process.collisionEventSelection = cms.Sequence(process.hfCoincFilter3Th3+process.primaryVertexFilter+process.siPixelRecHits+process.hltPixelClusterShapeFilter)


process.ak3PFJetSequence_data = cms.Sequence(process.ak3PFcorr+process.ak3PFJetTracksAssociatorAtVertex+process.ak3PFJetBtagging+process.ak3PFNjettiness+process.ak3PFpatJetsWithBtagging+process.ak3PFJetAnalyzer)


process.akPu3PFJetSequence_data = cms.Sequence(process.akPu3PFcorr+process.akPu3PFJetTracksAssociatorAtVertex+process.akPu3PFJetBtagging+process.akPu3PFNjettiness+process.akPu3PFpatJetsWithBtagging+process.akPu3PFJetAnalyzer)


process.akPu4PFJetSequence = cms.Sequence(process.akPu4PFJetSequence_mc)


process.akPu3PFJetSequence_mc = cms.Sequence(process.akPu3PFmatch+process.akPu3PFparton+process.akPu3PFcorr+process.akPu3PFPatJetFlavourIdLegacy+process.akPu3PFJetTracksAssociatorAtVertex+process.akPu3PFJetBtagging+process.akPu3PFNjettiness+process.akPu3PFpatJetsWithBtagging+process.akPu3PFJetAnalyzer)


process.akPu3PFJetSequence_mb = cms.Sequence(process.akPu3PFJetSequence_mc)


process.ak4PFJetSequence = cms.Sequence(process.ak4PFJetSequence_mc)


process.ak3PFJetSequence_mb = cms.Sequence(process.ak3PFJetSequence_mc)


process.ak4PFJetSequence_jec = cms.Sequence(process.ak4PFJetSequence_mc)


process.akFlowPuCs4PFJetSequence_mc = cms.Sequence(process.akFlowPuCs4PFmatch+process.akFlowPuCs4PFparton+process.akFlowPuCs4PFcorr+process.akFlowPuCs4PFPatJetFlavourIdLegacy+process.akFlowPuCs4PFJetTracksAssociatorAtVertex+process.akFlowPuCs4PFJetBtagging+process.akFlowPuCs4PFNjettiness+process.akFlowPuCs4PFpatJetsWithBtagging+process.akFlowPuCs4PFJetAnalyzer)


process.akCs3PFJetSequence_jec = cms.Sequence(process.akCs3PFJetSequence_mc)


process.akPu4CaloJetSequence_mc = cms.Sequence(process.akPu4Calomatch+process.akPu4Caloparton+process.akPu4Calocorr+process.akPu4CaloPatJetFlavourIdLegacy+process.akPu4CaloJetTracksAssociatorAtVertex+process.akPu4CaloJetBtagging+process.akPu4CaloNjettiness+process.akPu4CalopatJetsWithBtagging+process.akPu4CaloJetAnalyzer)


process.akPu4CaloJetSequence_mb = cms.Sequence(process.akPu4CaloJetSequence_mc)


process.akPu3PFJetSequence_jec = cms.Sequence(process.akPu3PFJetSequence_mc)


process.akFlowPuCs4PFJetSequence = cms.Sequence(process.akFlowPuCs4PFJetSequence_mc)


process.akPu4CaloJetSequence_jec = cms.Sequence(process.akPu4CaloJetSequence_mc)


process.akCs3PFJetSequence_data = cms.Sequence(process.akCs3PFcorr+process.akCs3PFJetTracksAssociatorAtVertex+process.akCs3PFJetBtagging+process.akCs3PFNjettiness+process.akCs3PFpatJetsWithBtagging+process.akCs3PFJetAnalyzer)


process.akFlowPuCs4PFJetSequence_jec = cms.Sequence(process.akFlowPuCs4PFJetSequence_mc)


process.akPu4PFJetSequence_data = cms.Sequence(process.akPu4PFcorr+process.akPu4PFJetTracksAssociatorAtVertex+process.akPu4PFJetBtagging+process.akPu4PFNjettiness+process.akPu4PFpatJetsWithBtagging+process.akPu4PFJetAnalyzer)


process.akPu3PFJetSequence = cms.Sequence(process.akPu3PFJetSequence_mc)


process.akCs3PFJetSequence_mb = cms.Sequence(process.akCs3PFJetSequence_mc)


process.akPu4CaloJetSequence = cms.Sequence(process.akPu4CaloJetSequence_mc)


process.akFlowPuCs4PFJetSequence_mb = cms.Sequence(process.akFlowPuCs4PFJetSequence_mc)


process.jetSequence = cms.Sequence(process.rhoSequence+process.highPurityTracks+process.akPu3CaloJets+process.ak3PFJets+process.akPu3PFJets+process.akCs3PFJets+process.akFlowPuCs3PFJets+process.akPu4CaloJets+process.ak4PFJets+process.akPu4PFJets+process.akCs4PFJets+process.akFlowPuCs4PFJets+process.akPu3CaloJetSequence+process.ak3PFJetSequence+process.akPu3PFJetSequence+process.akCs3PFJetSequence+process.akFlowPuCs3PFJetSequence+process.akPu4CaloJetSequence+process.ak4PFJetSequence+process.akPu4PFJetSequence+process.akCs4PFJetSequence+process.akFlowPuCs4PFJetSequence)


process.ana_step = cms.Path(process.offlinePrimaryVerticesRecovery+process.HiForest+process.runAnalyzer+process.hltanalysis+process.hltobject+process.centralityBin+process.hiEvtAnalyzer+process.HiGenParticleAna+process.genSignalSequence+process.correctedElectrons+process.ggHiNtuplizer+process.ggHiNtuplizerGED+process.pfcandAnalyzer+process.trackSequencesPP+process.rechitanalyzerpp)


process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)


process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)


process.pBeamScrapingFilter = cms.Path(process.beamScrapingFilter)


process.collisionEventSelectionAOD = cms.Path((process.hfCoincFilter3Th3+process.primaryVertexFilter+process.clusterCompatibilityFilter))


process.collisionEventSelectionAODv2 = cms.Path((process.hfCoincFilter2Th4+process.primaryVertexFilter+process.clusterCompatibilityFilter))


process.phfCoincFilter1Th3 = cms.Path(process.hfCoincFilterTh3)


process.phfCoincFilter2Th3 = cms.Path(process.hfCoincFilter2Th3)


process.phfCoincFilter3Th3 = cms.Path(process.hfCoincFilter3Th3)


process.phfCoincFilter4Th3 = cms.Path(process.hfCoincFilter4Th3)


process.phfCoincFilter5Th3 = cms.Path(process.hfCoincFilter5Th3)


process.phfCoincFilter1Th4 = cms.Path(process.hfCoincFilterTh4)


process.phfCoincFilter2Th4 = cms.Path(process.hfCoincFilter2Th4)


process.phfCoincFilter3Th4 = cms.Path(process.hfCoincFilter3Th4)


process.phfCoincFilter4Th4 = cms.Path(process.hfCoincFilter4Th4)


process.phfCoincFilter5Th4 = cms.Path(process.hfCoincFilter5Th4)


process.phfCoincFilter1Th5 = cms.Path(process.hfCoincFilterTh5)


process.phfCoincFilter4Th2 = cms.Path(process.hfCoincFilter4Th2)


process.pVertexFilterCutG = cms.Path(process.pileupVertexFilterCutG)


process.pVertexFilterCutGloose = cms.Path(process.pileupVertexFilterCutGloose)


process.pVertexFilterCutGtight = cms.Path(process.pileupVertexFilterCutGtight)


process.pVertexFilterCutGplus = cms.Path(process.pileupVertexFilterCutGplus)


process.pVertexFilterCutE = cms.Path(process.pileupVertexFilterCutE)


process.pVertexFilterCutEandG = cms.Path(process.pileupVertexFilterCutEandG)


process.pHBHENoiseFilterResultProducer = cms.Path(process.HBHENoiseFilterResultProducer)


process.HBHENoiseFilterResult = cms.Path(process.fHBHENoiseFilterResult)


process.HBHENoiseFilterResultRun1 = cms.Path(process.fHBHENoiseFilterResultRun1)


process.HBHENoiseFilterResultRun2Loose = cms.Path(process.fHBHENoiseFilterResultRun2Loose)


process.HBHENoiseFilterResultRun2Tight = cms.Path(process.fHBHENoiseFilterResultRun2Tight)


process.HBHEIsoNoiseFilterResult = cms.Path(process.fHBHEIsoNoiseFilterResult)


process.pAna = cms.EndPath(process.skimanalysis)



