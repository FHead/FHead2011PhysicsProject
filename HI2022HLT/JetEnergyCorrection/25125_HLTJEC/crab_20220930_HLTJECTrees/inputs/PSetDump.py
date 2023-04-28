import FWCore.ParameterSet.Config as cms
from HeterogeneousCore.CUDACore.ProcessAcceleratorCUDA import ProcessAcceleratorCUDA
from HeterogeneousCore.CUDACore.SwitchProducerCUDA import SwitchProducerCUDA

process = cms.Process("MyHLT")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/tmp/chenyi/step2_DIGI_15.root'),
    inputCommands = cms.untracked.vstring('keep *')
)
process.HLTConfigVersion = cms.PSet(
    tableName = cms.string('/users/chenyi/PbPb2022/Jet/HLTJEC/V9')
)

process.HLTIter0GroupedCkfTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(5.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0PSetTrajectoryFilterIT')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0PSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTIter0HighPtTkMuPSetTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('CkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    intermediateCleaning = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(4),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0HighPtTkMuPSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator')
)

process.HLTIter0HighPtTkMuPSetTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.3),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter0IterL3FromL1MuonGroupedCkfTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(10.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.9),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter0IterL3FromL1MuonPSetGroupedCkfTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(1000.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0IterL3FromL1MuonGroupedCkfTrajectoryFilterIT')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(True),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(1.0),
    maxCand = cms.int32(5),
    minNrOfHitsForRebuild = cms.int32(2),
    propagatorAlong = cms.string('PropagatorWithMaterial'),
    propagatorOpposite = cms.string('PropagatorWithMaterialOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0IterL3FromL1MuonGroupedCkfTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTIter0IterL3MuonGroupedCkfTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(10.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.9),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter0IterL3MuonPSetGroupedCkfTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(1000.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0IterL3MuonGroupedCkfTrajectoryFilterIT')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(True),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(1.0),
    maxCand = cms.int32(5),
    minNrOfHitsForRebuild = cms.int32(2),
    propagatorAlong = cms.string('PropagatorWithMaterial'),
    propagatorOpposite = cms.string('PropagatorWithMaterialOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0IterL3MuonGroupedCkfTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTIter0PSetTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('CkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator9'),
    intermediateCleaning = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter0PSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator')
)

process.HLTIter0PSetTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.3),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter1GroupedCkfTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(5.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter1PSetTrajectoryFilterIT')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter1PSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTIter1PSetTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('CkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator16'),
    intermediateCleaning = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter1PSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator')
)

process.HLTIter1PSetTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.2),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter2GroupedCkfTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(5.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter2PSetTrajectoryFilterIT')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter2PSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTIter2IterL3FromL1MuonPSetGroupedCkfTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(1000.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3FromL1MuonPSetTrajectoryFilterIT')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(False),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3FromL1MuonPSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTIter2IterL3FromL1MuonPSetTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(3),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.3),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter2IterL3MuonPSetGroupedCkfTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(1000.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3MuonPSetTrajectoryFilterIT')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(False),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3MuonPSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTIter2IterL3MuonPSetTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(3),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.3),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter2PSetTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('CkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator16'),
    intermediateCleaning = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter2PSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator')
)

process.HLTIter2PSetTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.3),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(1),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTIter4PSetTrajectoryBuilderIT = cms.PSet(
    ComponentType = cms.string('CkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator16'),
    intermediateCleaning = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(1),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTIter4PSetTrajectoryFilterIT')
    ),
    updator = cms.string('hltESPKFUpdator')
)

process.HLTIter4PSetTrajectoryFilterIT = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.3),
    minimumNumberOfHits = cms.int32(6),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetCkfBaseTrajectoryFilter_block = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.9),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetDetachedQuadStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPDetachedQuadStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetDetachedQuadStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetDetachedQuadStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPDetachedQuadStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetDetachedQuadStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetDetachedQuadStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetDetachedQuadStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.9),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetDetachedStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(5.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetDetachedStepTrajectoryFilter')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetDetachedStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetDetachedStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CompositeTrajectoryFilter'),
    filters = cms.VPSet(cms.PSet(
        refToPSet_ = cms.string('HLTPSetDetachedStepTrajectoryFilterBase')
    ))
)

process.HLTPSetDetachedStepTrajectoryFilterBase = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(2),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.075),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetDetachedTripletStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPDetachedTripletStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetDetachedTripletStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetDetachedTripletStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPDetachedTripletStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetDetachedTripletStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetDetachedTripletStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetDetachedTripletStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.9),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetHighPtTripletStepTrajectoryBuilderForDmesonPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPHighPtTripletStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetHighPtTripletStepTrajectoryFilterForDmesonPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetHighPtTripletStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPHighPtTripletStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetHighPtTripletStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetHighPtTripletStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPHighPtTripletStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetHighPtTripletStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetHighPtTripletStepTrajectoryFilterForDmesonPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(3.5),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetHighPtTripletStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(1.0),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetHighPtTripletStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.7),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetInitialStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPInitialStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilter')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(True),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(1),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetInitialStepTrajectoryBuilderForDmesonPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPInitialStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(True),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(1),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterForDmesonPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetInitialStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPInitialStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(True),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(1),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetInitialStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPInitialStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(True),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(1),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetInitialStepTrajectoryBuilderPreSplittingForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPInitialStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterPreSplittingForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetInitialStepTrajectoryBuilderPreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPInitialStepChi2ChargeMeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterPreSplittingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetInitialStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.2),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetInitialStepTrajectoryFilterBasePreSplittingForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(1.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetInitialStepTrajectoryFilterBasePreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.2),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetInitialStepTrajectoryFilterForDmesonPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(3.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetInitialStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(1.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetInitialStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.6),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetInitialStepTrajectoryFilterPreSplittingForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CompositeTrajectoryFilter'),
    filters = cms.VPSet(
        cms.PSet(
            refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterBasePreSplittingForFullTrackingPPOnAA')
        ),
        cms.PSet(
            refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterShapePreSplittingPPOnAA')
        )
    )
)

process.HLTPSetInitialStepTrajectoryFilterPreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('CompositeTrajectoryFilter'),
    filters = cms.VPSet(
        cms.PSet(
            refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterBasePreSplittingPPOnAA')
        ),
        cms.PSet(
            refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryFilterShapePreSplittingPPOnAA')
        )
    )
)

process.HLTPSetInitialStepTrajectoryFilterShapePreSplittingPPOnAA = cms.PSet(
    ComponentType = cms.string('StripSubClusterShapeTrajectoryFilter'),
    layerMask = cms.PSet(
        TEC = cms.bool(False),
        TIB = cms.vuint32(1, 2),
        TID = cms.vuint32(1, 2),
        TOB = cms.bool(False)
    ),
    maxNSat = cms.uint32(3),
    maxTrimmedSizeDiffNeg = cms.double(1.0),
    maxTrimmedSizeDiffPos = cms.double(0.7),
    seedCutMIPs = cms.double(0.35),
    seedCutSN = cms.double(7.0),
    subclusterCutMIPs = cms.double(0.45),
    subclusterCutSN = cms.double(12.0),
    subclusterWindow = cms.double(0.7),
    trimMaxADC = cms.double(30.0),
    trimMaxFracNeigh = cms.double(0.25),
    trimMaxFracTotal = cms.double(0.15)
)

process.HLTPSetJetCoreStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    foundHitBonus = cms.double(5.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetJetCoreStepTrajectoryFilter')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(50),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetJetCoreStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetJetCoreStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(50),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetJetCoreStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetJetCoreStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetJetCoreStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetLowPtQuadStepTrajectoryBuilderForDmesonPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPLowPtQuadStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(4),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtQuadStepTrajectoryFilterForDmesonPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetLowPtQuadStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPLowPtQuadStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(4),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtQuadStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetLowPtQuadStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPLowPtQuadStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(4),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtQuadStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetLowPtQuadStepTrajectoryFilterForDmesonPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(2.8),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetLowPtQuadStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(1.0),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetLowPtQuadStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.49),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetLowPtStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(5.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtStepTrajectoryFilter')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(4),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetLowPtStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(1),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.075),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetLowPtTripletStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPLowPtTripletStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(4),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtTripletStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetLowPtTripletStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPLowPtTripletStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(4),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtTripletStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetLowPtTripletStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(2.8),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetLowPtTripletStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.49),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetMixedStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeTightMeasurementEstimator16'),
    foundHitBonus = cms.double(5.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetMixedStepTrajectoryFilter')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialForMixedStep'),
    propagatorOpposite = cms.string('PropagatorWithMaterialForMixedStepOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetMixedStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetMixedStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.4),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetMixedTripletStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPMixedTripletStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialForMixedStep'),
    propagatorOpposite = cms.string('PropagatorWithMaterialForMixedStepOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetMixedTripletStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetMixedTripletStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPMixedTripletStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialForMixedStep'),
    propagatorOpposite = cms.string('PropagatorWithMaterialForMixedStepOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetMixedTripletStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetMixedTripletStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.4),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetMixedTripletStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.4),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.4),
    minimumNumberOfHits = cms.int32(3),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetMuTrackJpsiTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('CkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    intermediateCleaning = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(1),
    propagatorAlong = cms.string('PropagatorWithMaterial'),
    propagatorOpposite = cms.string('PropagatorWithMaterialOpposite'),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetMuTrackJpsiTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator')
)

process.HLTPSetMuTrackJpsiTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(8),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(10.0),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetMuonCkfTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('MuonCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    deltaEta = cms.double(-1.0),
    deltaPhi = cms.double(-1.0),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    intermediateCleaning = cms.bool(False),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterial'),
    propagatorOpposite = cms.string('PropagatorWithMaterialOpposite'),
    propagatorProximity = cms.string('SteppingHelixPropagatorAny'),
    rescaleErrorIfFail = cms.double(1.0),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetMuonCkfTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSeedLayer = cms.bool(False)
)

process.HLTPSetMuonCkfTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(-1),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.9),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetMuonTrackingRegionBuilder8356 = cms.PSet(
    DeltaEta = cms.double(0.2),
    DeltaPhi = cms.double(0.2),
    DeltaR = cms.double(0.2),
    DeltaZ = cms.double(15.9),
    EtaR_UpperLimit_Par1 = cms.double(0.25),
    EtaR_UpperLimit_Par2 = cms.double(0.15),
    Eta_fixed = cms.bool(False),
    Eta_min = cms.double(0.1),
    MeasurementTrackerName = cms.InputTag("hltESPMeasurementTracker"),
    OnDemand = cms.int32(-1),
    PhiR_UpperLimit_Par1 = cms.double(0.6),
    PhiR_UpperLimit_Par2 = cms.double(0.2),
    Phi_fixed = cms.bool(False),
    Phi_min = cms.double(0.1),
    Pt_fixed = cms.bool(False),
    Pt_min = cms.double(1.5),
    Rescale_Dz = cms.double(3.0),
    Rescale_eta = cms.double(3.0),
    Rescale_phi = cms.double(3.0),
    UseVertex = cms.bool(False),
    Z_fixed = cms.bool(True),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    input = cms.InputTag("hltL2Muons","UpdatedAtVtx"),
    maxRegions = cms.int32(2),
    precise = cms.bool(True),
    vertexCollection = cms.InputTag("pixelVertices")
)

process.HLTPSetPixelLessStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPPixelLessStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelLessStepTrajectoryFilter')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(4),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelLessStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetPixelLessStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPPixelLessStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(4),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelLessStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetPixelLessStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPPixelLessStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetCkfBaseTrajectoryFilter_block')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(4),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelLessStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(True)
)

process.HLTPSetPixelLessStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelLessStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelLessStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(2.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPPixelPairStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelPairStepTrajectoryFilterInOut')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelPairStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPPixelPairStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelPairStepTrajectoryFilterInOutForFullTrackingPPOnAA')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelPairStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPPixelPairStepChi2ChargeMeasurementEstimator9'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelPairStepTrajectoryFilterInOutPPOnAA')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(3),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(5),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPixelPairStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryFilterInOut = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(1),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryFilterInOutForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(1),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryFilterInOutPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(1),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPixelPairStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(0),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(999),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetPvClusterComparer = cms.PSet(
    track_chi2_max = cms.double(9999999.0),
    track_prob_min = cms.double(-1.0),
    track_pt_max = cms.double(10.0),
    track_pt_min = cms.double(2.5)
)

process.HLTPSetPvClusterComparerForBTag = cms.PSet(
    track_chi2_max = cms.double(20.0),
    track_prob_min = cms.double(-1.0),
    track_pt_max = cms.double(20.0),
    track_pt_min = cms.double(0.1)
)

process.HLTPSetPvClusterComparerForIT = cms.PSet(
    track_chi2_max = cms.double(20.0),
    track_prob_min = cms.double(-1.0),
    track_pt_max = cms.double(20.0),
    track_pt_min = cms.double(1.0)
)

process.HLTPSetTobTecStepInOutTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetTobTecStepInOutTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetTobTecStepInOutTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(2.0),
    minimumNumberOfHits = cms.int32(4),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetTobTecStepTrajectoryBuilder = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPTobTecStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetTobTecStepInOutTrajectoryFilter')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(4),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetTobTecStepTrajectoryFilter')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(False)
)

process.HLTPSetTobTecStepTrajectoryBuilderForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPTobTecStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetTobTecStepInOutTrajectoryFilterForFullTrackingPPOnAA')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(4),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetTobTecStepTrajectoryFilterForFullTrackingPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(False)
)

process.HLTPSetTobTecStepTrajectoryBuilderPPOnAA = cms.PSet(
    ComponentType = cms.string('GroupedCkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(False),
    bestHitOnly = cms.bool(True),
    estimator = cms.string('hltESPTobTecStepChi2ChargeMeasurementEstimator16'),
    foundHitBonus = cms.double(10.0),
    inOutTrajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetTobTecStepInOutTrajectoryFilterPPOnAA')
    ),
    intermediateCleaning = cms.bool(True),
    keepOriginalIfRebuildFails = cms.bool(False),
    lockHits = cms.bool(True),
    lostHitPenalty = cms.double(30.0),
    maxCand = cms.int32(2),
    maxDPhiForLooperReconstruction = cms.double(2.0),
    maxPtForLooperReconstruction = cms.double(0.7),
    minNrOfHitsForRebuild = cms.int32(4),
    propagatorAlong = cms.string('PropagatorWithMaterialParabolicMf'),
    propagatorOpposite = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    requireSeedHitsInRebuild = cms.bool(True),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetTobTecStepTrajectoryFilterPPOnAA')
    ),
    updator = cms.string('hltESPKFUpdator'),
    useSameTrajFilter = cms.bool(False)
)

process.HLTPSetTobTecStepTrajectoryFilter = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(0.1),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetTobTecStepTrajectoryFilterForFullTrackingPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(5.0),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetTobTecStepTrajectoryFilterPPOnAA = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(2.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(0),
    maxLostHitsFraction = cms.double(0.1),
    maxNumberOfHits = cms.int32(100),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(3),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(2.0),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(1),
    strictSeedExtension = cms.bool(False)
)

process.HLTPSetTrajectoryBuilderForGsfElectrons = cms.PSet(
    ComponentType = cms.string('CkfTrajectoryBuilder'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    alwaysUseInvalidHits = cms.bool(True),
    estimator = cms.string('hltESPChi2ChargeMeasurementEstimator2000'),
    intermediateCleaning = cms.bool(False),
    lostHitPenalty = cms.double(90.0),
    maxCand = cms.int32(5),
    propagatorAlong = cms.string('hltESPFwdElectronPropagator'),
    propagatorOpposite = cms.string('hltESPBwdElectronPropagator'),
    seedAs5DHit = cms.bool(False),
    trajectoryFilter = cms.PSet(
        refToPSet_ = cms.string('HLTPSetTrajectoryFilterForElectrons')
    ),
    updator = cms.string('hltESPKFUpdator')
)

process.HLTPSetTrajectoryFilterForElectrons = cms.PSet(
    ComponentType = cms.string('CkfBaseTrajectoryFilter'),
    chargeSignificance = cms.double(-1.0),
    constantValueForLostHitsFractionFilter = cms.double(1.0),
    extraNumberOfHitsBeforeTheFirstLoop = cms.int32(4),
    highEtaSwitch = cms.double(5.0),
    maxCCCLostHits = cms.int32(9999),
    maxConsecLostHits = cms.int32(1),
    maxLostHits = cms.int32(1),
    maxLostHitsFraction = cms.double(999.0),
    maxNumberOfHits = cms.int32(-1),
    minGoodStripCharge = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    minHitsAtHighEta = cms.int32(5),
    minHitsMinPt = cms.int32(-1),
    minNumberOfHitsForLoopers = cms.int32(13),
    minNumberOfHitsPerLoop = cms.int32(4),
    minPt = cms.double(2.0),
    minimumNumberOfHits = cms.int32(5),
    nSigmaMinPt = cms.double(5.0),
    pixelSeedExtension = cms.bool(False),
    seedExtension = cms.int32(0),
    seedPairPenalty = cms.int32(0),
    strictSeedExtension = cms.bool(False)
)

process.HLTSeedFromConsecutiveHitsCreator = cms.PSet(
    ComponentName = cms.string('SeedFromConsecutiveHitsCreator'),
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string(''),
    propagator = cms.string('PropagatorWithMaterial')
)

process.HLTSeedFromProtoTracks = cms.PSet(
    ComponentName = cms.string('SeedFromConsecutiveHitsCreator'),
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf')
)

process.HLTSiStripClusterChargeCutForHI = cms.PSet(
    value = cms.double(2069.0)
)

process.HLTSiStripClusterChargeCutLoose = cms.PSet(
    value = cms.double(1620.0)
)

process.HLTSiStripClusterChargeCutNone = cms.PSet(
    value = cms.double(-1.0)
)

process.HLTSiStripClusterChargeCutTight = cms.PSet(
    value = cms.double(1945.0)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

process.maxLuminosityBlocks = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    FailPath = cms.untracked.vstring(),
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    SkipEvent = cms.untracked.vstring(),
    accelerators = cms.untracked.vstring('*'),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(0)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    makeTriggerResults = cms.obsolete.untracked.bool,
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(0),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(True)
)

process.transferSystem = cms.PSet(
    default = cms.PSet(
        default = cms.vstring('Tier0'),
        emulator = cms.vstring('Lustre'),
        streamLookArea = cms.PSet(

        ),
        test = cms.vstring('Lustre')
    ),
    destinations = cms.vstring(
        'Tier0',
        'DQM',
        'ECAL',
        'EventDisplay',
        'Lustre',
        'None'
    ),
    streamA = cms.PSet(
        default = cms.vstring('Tier0'),
        emulator = cms.vstring('Lustre'),
        test = cms.vstring('Lustre')
    ),
    streamCalibration = cms.PSet(
        default = cms.vstring('Tier0'),
        emulator = cms.vstring('None'),
        test = cms.vstring('Lustre')
    ),
    streamDQM = cms.PSet(
        default = cms.vstring('DQM'),
        emulator = cms.vstring('None'),
        test = cms.vstring(
            'DQM',
            'Lustre'
        )
    ),
    streamDQMCalibration = cms.PSet(
        default = cms.vstring('DQM'),
        emulator = cms.vstring('None'),
        test = cms.vstring(
            'DQM',
            'Lustre'
        )
    ),
    streamEcalCalibration = cms.PSet(
        default = cms.vstring('ECAL'),
        emulator = cms.vstring('None'),
        test = cms.vstring('ECAL')
    ),
    streamEventDisplay = cms.PSet(
        default = cms.vstring(
            'EventDisplay',
            'Tier0'
        ),
        emulator = cms.vstring('None'),
        test = cms.vstring(
            'EventDisplay',
            'Lustre'
        )
    ),
    streamExpressCosmics = cms.PSet(
        default = cms.vstring('Tier0'),
        emulator = cms.vstring('Lustre'),
        test = cms.vstring('Lustre')
    ),
    streamLookArea = cms.PSet(
        default = cms.vstring('DQM'),
        emulator = cms.vstring('None'),
        test = cms.vstring(
            'DQM',
            'Lustre'
        )
    ),
    streamNanoDST = cms.PSet(
        default = cms.vstring('Tier0'),
        emulator = cms.vstring('None'),
        test = cms.vstring('Lustre')
    ),
    streamRPCMON = cms.PSet(
        default = cms.vstring('Tier0'),
        emulator = cms.vstring('None'),
        test = cms.vstring('Lustre')
    ),
    streamTrackerCalibration = cms.PSet(
        default = cms.vstring('Tier0'),
        emulator = cms.vstring('None'),
        test = cms.vstring('Lustre')
    ),
    transferModes = cms.vstring(
        'default',
        'test',
        'emulator'
    )
)

process.hltAK4CaloAbsoluteCorrector = cms.EDProducer("LXXXCorrectorProducer",
    algorithm = cms.string('AK4CaloHLT'),
    level = cms.string('L3Absolute')
)


process.hltAK4CaloFastJetCorrector = cms.EDProducer("L1FastjetCorrectorProducer",
    algorithm = cms.string('AK4CaloHLT'),
    level = cms.string('L1FastJet'),
    srcRho = cms.InputTag("hltFixedGridRhoFastjetAllCalo")
)


process.hltAK4CaloJetsPF = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(5),
    DxyTrVtxMax = cms.double(0.0),
    DzTrVtxMax = cms.double(0.0),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    MaxVtxZ = cms.double(15.0),
    MinVtxNdof = cms.int32(5),
    R0 = cms.double(-1.0),
    Rho_EtaMax = cms.double(4.4),
    UseOnlyOnePV = cms.bool(False),
    UseOnlyVertexTracks = cms.bool(False),
    applyWeight = cms.bool(False),
    beta = cms.double(-1.0),
    correctShape = cms.bool(False),
    csRParam = cms.double(-1.0),
    csRho_EtaMax = cms.double(-1.0),
    dRMax = cms.double(-1.0),
    dRMin = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    gridMaxRapidity = cms.double(-1.0),
    gridSpacing = cms.double(-1.0),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string(''),
    jetPtMin = cms.double(1.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxDepth = cms.int32(-1),
    maxInputs = cms.uint32(1),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(0),
    minimumTowersFraction = cms.double(0.0),
    muCut = cms.double(-1.0),
    muMax = cms.double(-1.0),
    muMin = cms.double(-1.0),
    nExclude = cms.uint32(0),
    nFilt = cms.int32(-1),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.0),
    rFilt = cms.double(-1.0),
    rFiltFactor = cms.double(-1.0),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.4),
    rcut_factor = cms.double(-1.0),
    restrictInputs = cms.bool(False),
    src = cms.InputTag("hltTowerMakerForAll"),
    srcPVs = cms.InputTag("NotUsed"),
    srcWeights = cms.InputTag(""),
    subjetPtMin = cms.double(-1.0),
    subtractorName = cms.string(''),
    sumRecHits = cms.bool(False),
    trimPtFracMin = cms.double(-1.0),
    useCMSBoostedTauSeedingAlgorithm = cms.bool(False),
    useConstituentSubtraction = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    useDynamicFiltering = cms.bool(False),
    useExplicitGhosts = cms.bool(False),
    useFiltering = cms.bool(False),
    useKtPruning = cms.bool(False),
    useMassDropTagger = cms.bool(False),
    usePruning = cms.bool(False),
    useSoftDrop = cms.bool(False),
    useTrimming = cms.bool(False),
    verbosity = cms.int32(0),
    voronoiRfact = cms.double(-9.0),
    writeCompound = cms.bool(False),
    writeJetsWithConst = cms.bool(False),
    yCut = cms.double(-1.0),
    yMax = cms.double(-1.0),
    yMin = cms.double(-1.0),
    zcut = cms.double(-1.0)
)


process.hltAK4CaloRelativeCorrector = cms.EDProducer("LXXXCorrectorProducer",
    algorithm = cms.string('AK4CaloHLT'),
    level = cms.string('L2Relative')
)


process.hltAK4Iter1TrackJets4Iter2PPOnAA = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(5),
    DxyTrVtxMax = cms.double(0.2),
    DzTrVtxMax = cms.double(0.5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    MaxVtxZ = cms.double(30.0),
    MinVtxNdof = cms.int32(0),
    R0 = cms.double(-1.0),
    Rho_EtaMax = cms.double(4.4),
    UseOnlyOnePV = cms.bool(True),
    UseOnlyVertexTracks = cms.bool(False),
    applyWeight = cms.bool(False),
    beta = cms.double(-1.0),
    correctShape = cms.bool(False),
    csRParam = cms.double(-1.0),
    csRho_EtaMax = cms.double(-1.0),
    dRMax = cms.double(-1.0),
    dRMin = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    gridMaxRapidity = cms.double(-1.0),
    gridSpacing = cms.double(-1.0),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.1),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string(''),
    jetPtMin = cms.double(7.5),
    jetType = cms.string('TrackJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxDepth = cms.int32(-1),
    maxInputs = cms.uint32(1),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.0),
    muCut = cms.double(-1.0),
    muMax = cms.double(-1.0),
    muMin = cms.double(-1.0),
    nExclude = cms.uint32(0),
    nFilt = cms.int32(-1),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(),
    puPtMin = cms.double(0.0),
    puWidth = cms.double(0.0),
    rFilt = cms.double(-1.0),
    rFiltFactor = cms.double(-1.0),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.4),
    rcut_factor = cms.double(-1.0),
    restrictInputs = cms.bool(False),
    src = cms.InputTag("hltIter1TrackRefsForJets4Iter2PPOnAA"),
    srcPVs = cms.InputTag("hltTrimmedPixelVerticesPPOnAA"),
    srcWeights = cms.InputTag(""),
    subjetPtMin = cms.double(-1.0),
    subtractorName = cms.string(''),
    sumRecHits = cms.bool(False),
    trimPtFracMin = cms.double(-1.0),
    useCMSBoostedTauSeedingAlgorithm = cms.bool(False),
    useConstituentSubtraction = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    useDynamicFiltering = cms.bool(False),
    useExplicitGhosts = cms.bool(False),
    useFiltering = cms.bool(False),
    useKtPruning = cms.bool(False),
    useMassDropTagger = cms.bool(False),
    usePruning = cms.bool(False),
    useSoftDrop = cms.bool(False),
    useTrimming = cms.bool(False),
    verbosity = cms.int32(0),
    voronoiRfact = cms.double(0.9),
    writeCompound = cms.bool(False),
    writeJetsWithConst = cms.bool(False),
    yCut = cms.double(-1.0),
    yMax = cms.double(-1.0),
    yMin = cms.double(-1.0),
    zcut = cms.double(-1.0)
)


process.hltAK4PFJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(5),
    DxyTrVtxMax = cms.double(0.0),
    DzTrVtxMax = cms.double(0.0),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    MaxVtxZ = cms.double(15.0),
    MinVtxNdof = cms.int32(0),
    R0 = cms.double(-1.0),
    Rho_EtaMax = cms.double(4.4),
    UseOnlyOnePV = cms.bool(False),
    UseOnlyVertexTracks = cms.bool(False),
    applyWeight = cms.bool(False),
    beta = cms.double(-1.0),
    correctShape = cms.bool(False),
    csRParam = cms.double(-1.0),
    csRho_EtaMax = cms.double(-1.0),
    dRMax = cms.double(-1.0),
    dRMin = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    gridMaxRapidity = cms.double(-1.0),
    gridSpacing = cms.double(-1.0),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string(''),
    jetPtMin = cms.double(0.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxDepth = cms.int32(-1),
    maxInputs = cms.uint32(1),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(0),
    minimumTowersFraction = cms.double(0.0),
    muCut = cms.double(-1.0),
    muMax = cms.double(-1.0),
    muMin = cms.double(-1.0),
    nExclude = cms.uint32(0),
    nFilt = cms.int32(-1),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.0),
    rFilt = cms.double(-1.0),
    rFiltFactor = cms.double(-1.0),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    rcut_factor = cms.double(-1.0),
    restrictInputs = cms.bool(False),
    src = cms.InputTag("hltParticleFlowPPOnAA"),
    srcPVs = cms.InputTag("hltPixelVerticesPPOnAA"),
    srcWeights = cms.InputTag(""),
    subjetPtMin = cms.double(-1.0),
    subtractorName = cms.string(''),
    sumRecHits = cms.bool(False),
    trimPtFracMin = cms.double(-1.0),
    useCMSBoostedTauSeedingAlgorithm = cms.bool(False),
    useConstituentSubtraction = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    useDynamicFiltering = cms.bool(False),
    useExplicitGhosts = cms.bool(False),
    useFiltering = cms.bool(False),
    useKtPruning = cms.bool(False),
    useMassDropTagger = cms.bool(False),
    usePruning = cms.bool(False),
    useSoftDrop = cms.bool(False),
    useTrimming = cms.bool(False),
    verbosity = cms.int32(0),
    voronoiRfact = cms.double(-9.0),
    writeCompound = cms.bool(False),
    writeJetsWithConst = cms.bool(False),
    yCut = cms.double(-1.0),
    yMax = cms.double(-1.0),
    yMin = cms.double(-1.0),
    zcut = cms.double(-1.0)
)


process.hltCsAK4PFJetsPPOnAA = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(5),
    DxyTrVtxMax = cms.double(0.0),
    DzTrVtxMax = cms.double(0.0),
    GhostArea = cms.double(0.005),
    Ghost_EtaMax = cms.double(6.5),
    MaxVtxZ = cms.double(15.0),
    MinVtxNdof = cms.int32(0),
    R0 = cms.double(-1.0),
    Rho_EtaMax = cms.double(4.5),
    UseOnlyOnePV = cms.bool(False),
    UseOnlyVertexTracks = cms.bool(False),
    applyWeight = cms.bool(False),
    beta = cms.double(-1.0),
    correctShape = cms.bool(False),
    csRParam = cms.double(-1.0),
    csRho_EtaMax = cms.double(-1.0),
    dRMax = cms.double(-1.0),
    dRMin = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    gridMaxRapidity = cms.double(-1.0),
    gridSpacing = cms.double(-1.0),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string('pfParticlesCs'),
    jetPtMin = cms.double(5.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxDepth = cms.int32(-1),
    maxInputs = cms.uint32(1),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.0),
    muCut = cms.double(-1.0),
    muMax = cms.double(-1.0),
    muMin = cms.double(-1.0),
    nExclude = cms.uint32(0),
    nFilt = cms.int32(-1),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.0),
    rFilt = cms.double(-1.0),
    rFiltFactor = cms.double(-1.0),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    rcut_factor = cms.double(-1.0),
    restrictInputs = cms.bool(False),
    src = cms.InputTag("hltParticleFlowPPOnAA"),
    srcPVs = cms.InputTag("hltPixelVerticesPPOnAA"),
    srcWeights = cms.InputTag(""),
    subjetPtMin = cms.double(-1.0),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    trimPtFracMin = cms.double(-1.0),
    useCMSBoostedTauSeedingAlgorithm = cms.bool(False),
    useConstituentSubtraction = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    useDynamicFiltering = cms.bool(False),
    useExplicitGhosts = cms.bool(False),
    useFiltering = cms.bool(False),
    useKtPruning = cms.bool(False),
    useMassDropTagger = cms.bool(False),
    usePruning = cms.bool(False),
    useSoftDrop = cms.bool(False),
    useTrimming = cms.bool(False),
    verbosity = cms.int32(0),
    voronoiRfact = cms.double(-0.9),
    writeCompound = cms.bool(False),
    writeJetsWithConst = cms.bool(False),
    yCut = cms.double(-1.0),
    yMax = cms.double(-1.0),
    yMin = cms.double(-1.0),
    zcut = cms.double(-1.0)
)


process.hltCsc2DRecHits = cms.EDProducer("CSCRecHitDProducer",
    CSCDebug = cms.untracked.bool(False),
    CSCNoOfTimeBinsForDynamicPedestal = cms.int32(2),
    CSCStripClusterChargeCut = cms.double(25.0),
    CSCStripPeakThreshold = cms.double(10.0),
    CSCStripxtalksOffset = cms.double(0.03),
    CSCUseCalibrations = cms.bool(True),
    CSCUseGasGainCorrections = cms.bool(False),
    CSCUseReducedWireTimeWindow = cms.bool(False),
    CSCUseStaticPedestals = cms.bool(False),
    CSCUseTimingCorrections = cms.bool(True),
    CSCWireClusterDeltaT = cms.int32(1),
    CSCWireTimeWindowHigh = cms.int32(15),
    CSCWireTimeWindowLow = cms.int32(0),
    CSCstripWireDeltaTime = cms.int32(8),
    ConstSyst_ME12 = cms.double(0.0),
    ConstSyst_ME13 = cms.double(0.0),
    ConstSyst_ME1a = cms.double(0.022),
    ConstSyst_ME1b = cms.double(0.007),
    ConstSyst_ME21 = cms.double(0.0),
    ConstSyst_ME22 = cms.double(0.0),
    ConstSyst_ME31 = cms.double(0.0),
    ConstSyst_ME32 = cms.double(0.0),
    ConstSyst_ME41 = cms.double(0.0),
    NoiseLevel_ME12 = cms.double(9.0),
    NoiseLevel_ME13 = cms.double(8.0),
    NoiseLevel_ME1a = cms.double(7.0),
    NoiseLevel_ME1b = cms.double(8.0),
    NoiseLevel_ME21 = cms.double(9.0),
    NoiseLevel_ME22 = cms.double(9.0),
    NoiseLevel_ME31 = cms.double(9.0),
    NoiseLevel_ME32 = cms.double(9.0),
    NoiseLevel_ME41 = cms.double(9.0),
    UseAverageTime = cms.bool(False),
    UseFivePoleFit = cms.bool(True),
    UseParabolaFit = cms.bool(False),
    XTasymmetry_ME12 = cms.double(0.0),
    XTasymmetry_ME13 = cms.double(0.0),
    XTasymmetry_ME1a = cms.double(0.0),
    XTasymmetry_ME1b = cms.double(0.0),
    XTasymmetry_ME21 = cms.double(0.0),
    XTasymmetry_ME22 = cms.double(0.0),
    XTasymmetry_ME31 = cms.double(0.0),
    XTasymmetry_ME32 = cms.double(0.0),
    XTasymmetry_ME41 = cms.double(0.0),
    readBadChambers = cms.bool(True),
    readBadChannels = cms.bool(False),
    stripDigiTag = cms.InputTag("hltMuonCSCDigis","MuonCSCStripDigi"),
    wireDigiTag = cms.InputTag("hltMuonCSCDigis","MuonCSCWireDigi")
)


process.hltCscSegments = cms.EDProducer("CSCSegmentProducer",
    algo_psets = cms.VPSet(cms.PSet(
        algo_name = cms.string('CSCSegAlgoRU'),
        algo_psets = cms.VPSet(
            cms.PSet(
                chi2Max = cms.double(100.0),
                chi2Norm_2D_ = cms.double(35.0),
                chi2_str = cms.double(50.0),
                dPhiIntMax = cms.double(0.005),
                dPhiMax = cms.double(0.006),
                dRIntMax = cms.double(2.0),
                dRMax = cms.double(1.5),
                doCollisions = cms.bool(True),
                enlarge = cms.bool(False),
                minLayersApart = cms.int32(1),
                wideSeg = cms.double(3.0)
            ),
            cms.PSet(
                chi2Max = cms.double(100.0),
                chi2Norm_2D_ = cms.double(35.0),
                chi2_str = cms.double(50.0),
                dPhiIntMax = cms.double(0.004),
                dPhiMax = cms.double(0.005),
                dRIntMax = cms.double(2.0),
                dRMax = cms.double(1.5),
                doCollisions = cms.bool(True),
                enlarge = cms.bool(False),
                minLayersApart = cms.int32(1),
                wideSeg = cms.double(3.0)
            ),
            cms.PSet(
                chi2Max = cms.double(100.0),
                chi2Norm_2D_ = cms.double(35.0),
                chi2_str = cms.double(50.0),
                dPhiIntMax = cms.double(0.003),
                dPhiMax = cms.double(0.004),
                dRIntMax = cms.double(2.0),
                dRMax = cms.double(1.5),
                doCollisions = cms.bool(True),
                enlarge = cms.bool(False),
                minLayersApart = cms.int32(1),
                wideSeg = cms.double(3.0)
            ),
            cms.PSet(
                chi2Max = cms.double(60.0),
                chi2Norm_2D_ = cms.double(20.0),
                chi2_str = cms.double(30.0),
                dPhiIntMax = cms.double(0.002),
                dPhiMax = cms.double(0.003),
                dRIntMax = cms.double(2.0),
                dRMax = cms.double(1.5),
                doCollisions = cms.bool(True),
                enlarge = cms.bool(False),
                minLayersApart = cms.int32(1),
                wideSeg = cms.double(3.0)
            ),
            cms.PSet(
                chi2Max = cms.double(180.0),
                chi2Norm_2D_ = cms.double(60.0),
                chi2_str = cms.double(80.0),
                dPhiIntMax = cms.double(0.005),
                dPhiMax = cms.double(0.007),
                dRIntMax = cms.double(2.0),
                dRMax = cms.double(1.5),
                doCollisions = cms.bool(True),
                enlarge = cms.bool(False),
                minLayersApart = cms.int32(1),
                wideSeg = cms.double(3.0)
            ),
            cms.PSet(
                chi2Max = cms.double(100.0),
                chi2Norm_2D_ = cms.double(35.0),
                chi2_str = cms.double(50.0),
                dPhiIntMax = cms.double(0.004),
                dPhiMax = cms.double(0.006),
                dRIntMax = cms.double(2.0),
                dRMax = cms.double(1.5),
                doCollisions = cms.bool(True),
                enlarge = cms.bool(False),
                minLayersApart = cms.int32(1),
                wideSeg = cms.double(3.0)
            )
        ),
        chamber_types = cms.vstring(
            'ME1/a',
            'ME1/b',
            'ME1/2',
            'ME1/3',
            'ME2/1',
            'ME2/2',
            'ME3/1',
            'ME3/2',
            'ME4/1',
            'ME4/2'
        ),
        parameters_per_chamber_type = cms.vint32(
            1, 2, 3, 4, 5,
            6, 5, 6, 5, 6
        )
    )),
    algo_type = cms.int32(1),
    inputObjects = cms.InputTag("hltCsc2DRecHits")
)


process.hltDoubletRecoveryClustersRefRemovalPPOnAA = cms.EDProducer("TrackClusterRemover",
    TrackQuality = cms.string('highPurity'),
    maxChi2 = cms.double(16.0),
    minNumberOfLayersWithMeasBeforeFiltering = cms.int32(0),
    oldClusterRemovalInfo = cms.InputTag("hltFullIter2ClustersRefRemovalPPOnAA"),
    overrideTrkQuals = cms.InputTag(""),
    pixelClusters = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA"),
    stripClusters = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression"),
    trackClassifier = cms.InputTag("","QualityMasks"),
    trajectories = cms.InputTag("hltFullIter2HighPurityTracksPPOnAA")
)


process.hltDoubletRecoveryMaskedMeasurementTrackerEventPPOnAA = cms.EDProducer("MaskedMeasurementTrackerEventProducer",
    OnDemand = cms.bool(False),
    clustersToSkip = cms.InputTag("hltDoubletRecoveryClustersRefRemovalPPOnAA"),
    src = cms.InputTag("hltSiStripClustersFullPPOnAA")
)


process.hltDoubletRecoveryPFlowCkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltDoubletRecoveryMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTIter2GroupedCkfTrajectoryBuilderIT')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(False),
    maxNSeeds = cms.uint32(100000),
    maxSeedsBeforeCleaning = cms.uint32(1000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltDoubletRecoveryPFlowPixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(False)
)


process.hltDoubletRecoveryPFlowCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('hltDoubletRecovery'),
    Fitter = cms.string('hltESPFittingSmootherIT'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltDoubletRecoveryMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltDoubletRecoveryPFlowCkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltDoubletRecoveryPFlowPixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltSiStripClustersFullPPOnAA"),
    MaxNumberOfCosmicClusters = cms.uint32(50000),
    MaxNumberOfPixelClusters = cms.uint32(40000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA"),
    cut = cms.string(''),
    doClusterCheck = cms.bool(False),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltDoubletRecoveryPFlowPixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltDoubletRecoveryPFlowPixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(False),
    produceSeedingHitSets = cms.bool(True),
    seedingLayers = cms.InputTag(""),
    trackingRegions = cms.InputTag(""),
    trackingRegionsSeedingLayers = cms.InputTag("hltDoubletRecoveryPixelLayersAndRegionsPPOnAA")
)


process.hltDoubletRecoveryPFlowPixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltDoubletRecoveryPFlowPixelHitDoubletsPPOnAA")
)


process.hltDoubletRecoveryPFlowTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 0.003),
            d0err_par = cms.vdouble(0.001, 0.001, 0.001),
            dr_exp = cms.vint32(4, 4, 4),
            dr_par1 = cms.vdouble(3.40282346639e+38, 0.4, 0.4),
            dr_par2 = cms.vdouble(3.40282346639e+38, 0.3, 0.3)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 4),
            dz_par1 = cms.vdouble(3.40282346639e+38, 0.4, 0.4),
            dz_par2 = cms.vdouble(3.40282346639e+38, 0.35, 0.35)
        ),
        maxChi2 = cms.vdouble(9999.0, 25.0, 16.0),
        maxChi2n = cms.vdouble(1.2, 1.0, 0.7),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 15.0),
        maxLostLayers = cms.vint32(1, 1, 1),
        min3DLayers = cms.vint32(0, 0, 0),
        minLayers = cms.vint32(3, 3, 3),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 0, 0)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltDoubletRecoveryPFlowCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltTrimmedPixelVerticesPPOnAA")
)


process.hltDoubletRecoveryPFlowTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltDoubletRecoveryPFlowTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltDoubletRecoveryPFlowTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltDoubletRecoveryPFlowCtfWithMaterialTracksPPOnAA")
)


process.hltDoubletRecoveryPixelLayersAndRegionsPPOnAA = cms.EDProducer("PixelInactiveAreaTrackingRegionsSeedingLayersProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        skipClusters = cms.InputTag("hltDoubletRecoveryClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        skipClusters = cms.InputTag("hltDoubletRecoveryClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    RegionPSet = cms.PSet(
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        extraEta = cms.double(0.0),
        extraPhi = cms.double(0.0),
        maxNVertices = cms.int32(3),
        measurementTrackerName = cms.InputTag("hltDoubletRecoveryMaskedMeasurementTrackerEventPPOnAA"),
        nSigmaZBeamSpot = cms.double(4.0),
        nSigmaZVertex = cms.double(3.0),
        operationMode = cms.string('VerticesFixed'),
        originRadius = cms.double(0.015),
        precise = cms.bool(True),
        ptMin = cms.double(1.2),
        searchOpt = cms.bool(False),
        vertexCollection = cms.InputTag("hltTrimmedPixelVerticesPPOnAA"),
        whereToUseMeasurementTracker = cms.string('ForSiStrips'),
        zErrorBeamSpot = cms.double(15.0),
        zErrorVertex = cms.double(0.03)
    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    badPixelFEDChannelCollectionLabels = cms.VInputTag("hltSiPixelDigisPPOnAA"),
    createPlottingFiles = cms.untracked.bool(False),
    debug = cms.untracked.bool(False),
    ignoreSingleFPixPanelModules = cms.bool(True),
    inactivePixelDetectorLabels = cms.VInputTag("hltSiPixelDigisPPOnAA"),
    layerList = cms.vstring(
        'BPix1+BPix2',
        'BPix1+BPix3',
        'BPix1+BPix4',
        'BPix2+BPix3',
        'BPix2+BPix4',
        'BPix3+BPix4',
        'BPix1+FPix1_pos',
        'BPix1+FPix1_neg',
        'BPix1+FPix2_pos',
        'BPix1+FPix2_neg',
        'BPix1+FPix3_pos',
        'BPix1+FPix3_neg',
        'BPix2+FPix1_pos',
        'BPix2+FPix1_neg',
        'BPix2+FPix2_pos',
        'BPix2+FPix2_neg',
        'BPix3+FPix1_pos',
        'BPix3+FPix1_neg',
        'FPix1_pos+FPix2_pos',
        'FPix1_neg+FPix2_neg',
        'FPix1_pos+FPix3_pos',
        'FPix1_neg+FPix3_neg',
        'FPix2_pos+FPix3_pos',
        'FPix2_neg+FPix3_neg'
    )
)


process.hltDt1DRecHits = cms.EDProducer("DTRecHitProducer",
    debug = cms.untracked.bool(False),
    dtDigiLabel = cms.InputTag("hltMuonDTDigis"),
    recAlgo = cms.string('DTLinearDriftFromDBAlgo'),
    recAlgoConfig = cms.PSet(
        debug = cms.untracked.bool(False),
        doVdriftCorr = cms.bool(True),
        maxTime = cms.double(420.0),
        minTime = cms.double(-3.0),
        readLegacyTTrigDB = cms.bool(True),
        readLegacyVDriftDB = cms.bool(True),
        stepTwoFromDigi = cms.bool(False),
        tTrigMode = cms.string('DTTTrigSyncFromDB'),
        tTrigModeConfig = cms.PSet(
            debug = cms.untracked.bool(False),
            doT0Correction = cms.bool(True),
            doTOFCorrection = cms.bool(True),
            doWirePropCorrection = cms.bool(True),
            t0Label = cms.string(''),
            tTrigLabel = cms.string(''),
            tofCorrType = cms.int32(0),
            vPropWire = cms.double(24.4),
            wirePropCorrType = cms.int32(0)
        ),
        useUncertDB = cms.bool(True)
    )
)


process.hltDt4DSegments = cms.EDProducer("DTRecSegment4DProducer",
    Reco4DAlgoConfig = cms.PSet(
        AllDTRecHits = cms.bool(True),
        Reco2DAlgoConfig = cms.PSet(
            AlphaMaxPhi = cms.double(1.0),
            AlphaMaxTheta = cms.double(0.9),
            MaxAllowedHits = cms.uint32(50),
            debug = cms.untracked.bool(False),
            hit_afterT0_resolution = cms.double(0.03),
            nSharedHitsMax = cms.int32(2),
            nUnSharedHitsMin = cms.int32(2),
            performT0SegCorrection = cms.bool(False),
            performT0_vdriftSegCorrection = cms.bool(False),
            perform_delta_rejecting = cms.bool(False),
            recAlgo = cms.string('DTLinearDriftFromDBAlgo'),
            recAlgoConfig = cms.PSet(
                debug = cms.untracked.bool(False),
                doVdriftCorr = cms.bool(True),
                maxTime = cms.double(420.0),
                minTime = cms.double(-3.0),
                readLegacyTTrigDB = cms.bool(True),
                readLegacyVDriftDB = cms.bool(True),
                stepTwoFromDigi = cms.bool(False),
                tTrigMode = cms.string('DTTTrigSyncFromDB'),
                tTrigModeConfig = cms.PSet(
                    debug = cms.untracked.bool(False),
                    doT0Correction = cms.bool(True),
                    doTOFCorrection = cms.bool(True),
                    doWirePropCorrection = cms.bool(True),
                    t0Label = cms.string(''),
                    tTrigLabel = cms.string(''),
                    tofCorrType = cms.int32(0),
                    vPropWire = cms.double(24.4),
                    wirePropCorrType = cms.int32(0)
                ),
                useUncertDB = cms.bool(True)
            ),
            segmCleanerMode = cms.int32(2)
        ),
        Reco2DAlgoName = cms.string('DTCombinatorialPatternReco'),
        debug = cms.untracked.bool(False),
        hit_afterT0_resolution = cms.double(0.03),
        nSharedHitsMax = cms.int32(2),
        nUnSharedHitsMin = cms.int32(2),
        performT0SegCorrection = cms.bool(False),
        performT0_vdriftSegCorrection = cms.bool(False),
        perform_delta_rejecting = cms.bool(False),
        recAlgo = cms.string('DTLinearDriftFromDBAlgo'),
        recAlgoConfig = cms.PSet(
            debug = cms.untracked.bool(False),
            doVdriftCorr = cms.bool(True),
            maxTime = cms.double(420.0),
            minTime = cms.double(-3.0),
            readLegacyTTrigDB = cms.bool(True),
            readLegacyVDriftDB = cms.bool(True),
            stepTwoFromDigi = cms.bool(False),
            tTrigMode = cms.string('DTTTrigSyncFromDB'),
            tTrigModeConfig = cms.PSet(
                debug = cms.untracked.bool(False),
                doT0Correction = cms.bool(True),
                doTOFCorrection = cms.bool(True),
                doWirePropCorrection = cms.bool(True),
                t0Label = cms.string(''),
                tTrigLabel = cms.string(''),
                tofCorrType = cms.int32(0),
                vPropWire = cms.double(24.4),
                wirePropCorrType = cms.int32(0)
            ),
            useUncertDB = cms.bool(True)
        ),
        segmCleanerMode = cms.int32(2)
    ),
    Reco4DAlgoName = cms.string('DTCombinatorialPatternReco4D'),
    debug = cms.untracked.bool(False),
    recHits1DLabel = cms.InputTag("hltDt1DRecHits"),
    recHits2DLabel = cms.InputTag("dt2DSegments")
)


process.hltEcalDetIdToBeRecovered = cms.EDProducer("EcalDetIdToBeRecoveredProducer",
    ebDetIdToBeRecovered = cms.string('ebDetId'),
    ebFEToBeRecovered = cms.string('ebFE'),
    ebIntegrityChIdErrors = cms.InputTag("hltEcalDigis","EcalIntegrityChIdErrors"),
    ebIntegrityGainErrors = cms.InputTag("hltEcalDigis","EcalIntegrityGainErrors"),
    ebIntegrityGainSwitchErrors = cms.InputTag("hltEcalDigis","EcalIntegrityGainSwitchErrors"),
    ebSrFlagCollection = cms.InputTag("hltEcalDigis"),
    eeDetIdToBeRecovered = cms.string('eeDetId'),
    eeFEToBeRecovered = cms.string('eeFE'),
    eeIntegrityChIdErrors = cms.InputTag("hltEcalDigis","EcalIntegrityChIdErrors"),
    eeIntegrityGainErrors = cms.InputTag("hltEcalDigis","EcalIntegrityGainErrors"),
    eeIntegrityGainSwitchErrors = cms.InputTag("hltEcalDigis","EcalIntegrityGainSwitchErrors"),
    eeSrFlagCollection = cms.InputTag("hltEcalDigis"),
    integrityBlockSizeErrors = cms.InputTag("hltEcalDigis","EcalIntegrityBlockSizeErrors"),
    integrityTTIdErrors = cms.InputTag("hltEcalDigis","EcalIntegrityTTIdErrors")
)


process.hltEcalDigisFromGPU = cms.EDProducer("EcalCPUDigisProducer",
    digisInLabelEB = cms.InputTag("hltEcalDigisGPU","ebDigis"),
    digisInLabelEE = cms.InputTag("hltEcalDigisGPU","eeDigis"),
    digisOutLabelEB = cms.string('ebDigis'),
    digisOutLabelEE = cms.string('eeDigis'),
    produceDummyIntegrityCollections = cms.bool(True)
)


process.hltEcalDigisGPU = cms.EDProducer("EcalRawToDigiGPU",
    FEDs = cms.vint32(
        601, 602, 603, 604, 605,
        606, 607, 608, 609, 610,
        611, 612, 613, 614, 615,
        616, 617, 618, 619, 620,
        621, 622, 623, 624, 625,
        626, 627, 628, 629, 630,
        631, 632, 633, 634, 635,
        636, 637, 638, 639, 640,
        641, 642, 643, 644, 645,
        646, 647, 648, 649, 650,
        651, 652, 653, 654
    ),
    InputLabel = cms.InputTag("rawDataCollector"),
    digisLabelEB = cms.string('ebDigis'),
    digisLabelEE = cms.string('eeDigis'),
    maxChannelsEB = cms.uint32(61200),
    maxChannelsEE = cms.uint32(14648)
)


process.hltEcalDigisLegacy = cms.EDProducer("EcalRawToDigi",
    DoRegional = cms.bool(False),
    FEDs = cms.vint32(
        601, 602, 603, 604, 605,
        606, 607, 608, 609, 610,
        611, 612, 613, 614, 615,
        616, 617, 618, 619, 620,
        621, 622, 623, 624, 625,
        626, 627, 628, 629, 630,
        631, 632, 633, 634, 635,
        636, 637, 638, 639, 640,
        641, 642, 643, 644, 645,
        646, 647, 648, 649, 650,
        651, 652, 653, 654
    ),
    FedLabel = cms.InputTag("listfeds"),
    InputLabel = cms.InputTag("rawDataCollector"),
    eventPut = cms.bool(True),
    feIdCheck = cms.bool(True),
    feUnpacking = cms.bool(True),
    forceToKeepFRData = cms.bool(False),
    headerUnpacking = cms.bool(True),
    memUnpacking = cms.bool(True),
    numbTriggerTSamples = cms.int32(1),
    numbXtalTSamples = cms.int32(10),
    orderedDCCIdList = cms.vint32(
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25,
        26, 27, 28, 29, 30,
        31, 32, 33, 34, 35,
        36, 37, 38, 39, 40,
        41, 42, 43, 44, 45,
        46, 47, 48, 49, 50,
        51, 52, 53, 54
    ),
    orderedFedList = cms.vint32(
        601, 602, 603, 604, 605,
        606, 607, 608, 609, 610,
        611, 612, 613, 614, 615,
        616, 617, 618, 619, 620,
        621, 622, 623, 624, 625,
        626, 627, 628, 629, 630,
        631, 632, 633, 634, 635,
        636, 637, 638, 639, 640,
        641, 642, 643, 644, 645,
        646, 647, 648, 649, 650,
        651, 652, 653, 654
    ),
    silentMode = cms.untracked.bool(True),
    srpUnpacking = cms.bool(True),
    syncCheck = cms.bool(True),
    tccUnpacking = cms.bool(True)
)


process.hltEcalPreshowerDigis = cms.EDProducer("ESRawToDigi",
    ESdigiCollection = cms.string(''),
    InstanceES = cms.string(''),
    LookupTable = cms.FileInPath('EventFilter/ESDigiToRaw/data/ES_lookup_table.dat'),
    debugMode = cms.untracked.bool(False),
    sourceTag = cms.InputTag("rawDataCollector")
)


process.hltEcalPreshowerRecHit = cms.EDProducer("ESRecHitProducer",
    ESRecoAlgo = cms.int32(0),
    ESdigiCollection = cms.InputTag("hltEcalPreshowerDigis"),
    ESrechitCollection = cms.string('EcalRecHitsES'),
    algo = cms.string('ESRecHitWorker')
)


process.hltEcalRecHitWithTPs = cms.EDProducer("EcalRecHitProducer",
    ChannelStatusToBeExcluded = cms.vstring(),
    EBLaserMAX = cms.double(3.0),
    EBLaserMIN = cms.double(0.5),
    EBrechitCollection = cms.string('EcalRecHitsEB'),
    EBuncalibRecHitCollection = cms.InputTag("hltEcalUncalibRecHit","EcalUncalibRecHitsEB"),
    EELaserMAX = cms.double(8.0),
    EELaserMIN = cms.double(0.5),
    EErechitCollection = cms.string('EcalRecHitsEE'),
    EEuncalibRecHitCollection = cms.InputTag("hltEcalUncalibRecHit","EcalUncalibRecHitsEE"),
    algo = cms.string('EcalRecHitWorkerSimple'),
    algoRecover = cms.string('EcalRecHitWorkerRecover'),
    bdtWeightFileCracks = cms.FileInPath('RecoLocalCalo/EcalDeadChannelRecoveryAlgos/data/BDTWeights/bdtgAllRH_8GT700MeV_onlyCracks_ZskimData2017_v1.xml'),
    bdtWeightFileNoCracks = cms.FileInPath('RecoLocalCalo/EcalDeadChannelRecoveryAlgos/data/BDTWeights/bdtgAllRH_8GT700MeV_noCracks_ZskimData2017_v1.xml'),
    cleaningConfig = cms.PSet(
        cThreshold_barrel = cms.double(4.0),
        cThreshold_double = cms.double(10.0),
        cThreshold_endcap = cms.double(15.0),
        e4e1Threshold_barrel = cms.double(0.08),
        e4e1Threshold_endcap = cms.double(0.3),
        e4e1_a_barrel = cms.double(0.04),
        e4e1_a_endcap = cms.double(0.02),
        e4e1_b_barrel = cms.double(-0.024),
        e4e1_b_endcap = cms.double(-0.0125),
        e6e2thresh = cms.double(0.04),
        ignoreOutOfTimeThresh = cms.double(1000000000.0),
        tightenCrack_e1_double = cms.double(2.0),
        tightenCrack_e1_single = cms.double(2.0),
        tightenCrack_e4e1_single = cms.double(3.0),
        tightenCrack_e6e2_double = cms.double(3.0)
    ),
    dbStatusToBeExcludedEB = cms.vint32(14, 78, 142),
    dbStatusToBeExcludedEE = cms.vint32(14, 78, 142),
    ebDetIdToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","ebDetId"),
    ebFEToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","ebFE"),
    eeDetIdToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","eeDetId"),
    eeFEToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","eeFE"),
    flagsMapDBReco = cms.PSet(
        kDead = cms.vstring('kNoDataNoTP'),
        kGood = cms.vstring(
            'kOk',
            'kDAC',
            'kNoLaser',
            'kNoisy'
        ),
        kNeighboursRecovered = cms.vstring(
            'kFixedG0',
            'kNonRespondingIsolated',
            'kDeadVFE'
        ),
        kNoisy = cms.vstring(
            'kNNoisy',
            'kFixedG6',
            'kFixedG1'
        ),
        kTowerRecovered = cms.vstring('kDeadFE')
    ),
    killDeadChannels = cms.bool(True),
    laserCorrection = cms.bool(True),
    logWarningEtThreshold_EB_FE = cms.double(50.0),
    logWarningEtThreshold_EE_FE = cms.double(50.0),
    recoverEBFE = cms.bool(True),
    recoverEBIsolatedChannels = cms.bool(False),
    recoverEBVFE = cms.bool(False),
    recoverEEFE = cms.bool(True),
    recoverEEIsolatedChannels = cms.bool(False),
    recoverEEVFE = cms.bool(False),
    singleChannelRecoveryMethod = cms.string('NeuralNetworks'),
    singleChannelRecoveryThreshold = cms.double(8.0),
    skipTimeCalib = cms.bool(False),
    sum8ChannelRecoveryThreshold = cms.double(0.0),
    triggerPrimitiveDigiCollection = cms.InputTag("hltEcalDigisLegacy","EcalTriggerPrimitives")
)


process.hltEcalRecHitWithoutTPs = cms.EDProducer("EcalRecHitProducer",
    ChannelStatusToBeExcluded = cms.vstring(),
    EBLaserMAX = cms.double(3.0),
    EBLaserMIN = cms.double(0.5),
    EBrechitCollection = cms.string('EcalRecHitsEB'),
    EBuncalibRecHitCollection = cms.InputTag("hltEcalUncalibRecHit","EcalUncalibRecHitsEB"),
    EELaserMAX = cms.double(8.0),
    EELaserMIN = cms.double(0.5),
    EErechitCollection = cms.string('EcalRecHitsEE'),
    EEuncalibRecHitCollection = cms.InputTag("hltEcalUncalibRecHit","EcalUncalibRecHitsEE"),
    algo = cms.string('EcalRecHitWorkerSimple'),
    algoRecover = cms.string('EcalRecHitWorkerRecover'),
    bdtWeightFileCracks = cms.FileInPath('RecoLocalCalo/EcalDeadChannelRecoveryAlgos/data/BDTWeights/bdtgAllRH_8GT700MeV_onlyCracks_ZskimData2017_v1.xml'),
    bdtWeightFileNoCracks = cms.FileInPath('RecoLocalCalo/EcalDeadChannelRecoveryAlgos/data/BDTWeights/bdtgAllRH_8GT700MeV_noCracks_ZskimData2017_v1.xml'),
    cleaningConfig = cms.PSet(
        cThreshold_barrel = cms.double(4.0),
        cThreshold_double = cms.double(10.0),
        cThreshold_endcap = cms.double(15.0),
        e4e1Threshold_barrel = cms.double(0.08),
        e4e1Threshold_endcap = cms.double(0.3),
        e4e1_a_barrel = cms.double(0.04),
        e4e1_a_endcap = cms.double(0.02),
        e4e1_b_barrel = cms.double(-0.024),
        e4e1_b_endcap = cms.double(-0.0125),
        e6e2thresh = cms.double(0.04),
        ignoreOutOfTimeThresh = cms.double(1000000000.0),
        tightenCrack_e1_double = cms.double(2.0),
        tightenCrack_e1_single = cms.double(2.0),
        tightenCrack_e4e1_single = cms.double(3.0),
        tightenCrack_e6e2_double = cms.double(3.0)
    ),
    dbStatusToBeExcludedEB = cms.vint32(14, 78, 142),
    dbStatusToBeExcludedEE = cms.vint32(14, 78, 142),
    ebDetIdToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","ebDetId"),
    ebFEToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","ebFE"),
    eeDetIdToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","eeDetId"),
    eeFEToBeRecovered = cms.InputTag("hltEcalDetIdToBeRecovered","eeFE"),
    flagsMapDBReco = cms.PSet(
        kDead = cms.vstring('kNoDataNoTP'),
        kGood = cms.vstring(
            'kOk',
            'kDAC',
            'kNoLaser',
            'kNoisy'
        ),
        kNeighboursRecovered = cms.vstring(
            'kFixedG0',
            'kNonRespondingIsolated',
            'kDeadVFE'
        ),
        kNoisy = cms.vstring(
            'kNNoisy',
            'kFixedG6',
            'kFixedG1'
        ),
        kTowerRecovered = cms.vstring('kDeadFE')
    ),
    killDeadChannels = cms.bool(True),
    laserCorrection = cms.bool(True),
    logWarningEtThreshold_EB_FE = cms.double(50.0),
    logWarningEtThreshold_EE_FE = cms.double(50.0),
    recoverEBFE = cms.bool(True),
    recoverEBIsolatedChannels = cms.bool(False),
    recoverEBVFE = cms.bool(False),
    recoverEEFE = cms.bool(True),
    recoverEEIsolatedChannels = cms.bool(False),
    recoverEEVFE = cms.bool(False),
    singleChannelRecoveryMethod = cms.string('NeuralNetworks'),
    singleChannelRecoveryThreshold = cms.double(8.0),
    skipTimeCalib = cms.bool(False),
    sum8ChannelRecoveryThreshold = cms.double(0.0),
    triggerPrimitiveDigiCollection = cms.InputTag("unused")
)


process.hltEcalUncalibRecHitFromSoA = cms.EDProducer("EcalUncalibRecHitConvertGPU2CPUFormat",
    recHitsLabelCPUEB = cms.string('EcalUncalibRecHitsEB'),
    recHitsLabelCPUEE = cms.string('EcalUncalibRecHitsEE'),
    recHitsLabelGPUEB = cms.InputTag("hltEcalUncalibRecHitSoA","EcalUncalibRecHitsEB"),
    recHitsLabelGPUEE = cms.InputTag("hltEcalUncalibRecHitSoA","EcalUncalibRecHitsEE")
)


process.hltEcalUncalibRecHitGPU = cms.EDProducer("EcalUncalibRecHitProducerGPU",
    EBtimeConstantTerm = cms.double(0.6),
    EBtimeFitLimits_Lower = cms.double(0.2),
    EBtimeFitLimits_Upper = cms.double(1.4),
    EBtimeNconst = cms.double(28.5),
    EEtimeConstantTerm = cms.double(1.0),
    EEtimeFitLimits_Lower = cms.double(0.2),
    EEtimeFitLimits_Upper = cms.double(1.4),
    EEtimeNconst = cms.double(31.8),
    amplitudeThresholdEB = cms.double(10.0),
    amplitudeThresholdEE = cms.double(10.0),
    digisLabelEB = cms.InputTag("hltEcalDigisGPU","ebDigis"),
    digisLabelEE = cms.InputTag("hltEcalDigisGPU","eeDigis"),
    kernelMinimizeThreads = cms.untracked.vuint32(32, 1, 1),
    maxNumberHitsEB = cms.uint32(61200),
    maxNumberHitsEE = cms.uint32(14648),
    outOfTimeThresholdGain12mEB = cms.double(1000.0),
    outOfTimeThresholdGain12mEE = cms.double(1000.0),
    outOfTimeThresholdGain12pEB = cms.double(1000.0),
    outOfTimeThresholdGain12pEE = cms.double(1000.0),
    outOfTimeThresholdGain61mEB = cms.double(1000.0),
    outOfTimeThresholdGain61mEE = cms.double(1000.0),
    outOfTimeThresholdGain61pEB = cms.double(1000.0),
    outOfTimeThresholdGain61pEE = cms.double(1000.0),
    recHitsLabelEB = cms.string('EcalUncalibRecHitsEB'),
    recHitsLabelEE = cms.string('EcalUncalibRecHitsEE'),
    shouldRunTimingComputation = cms.bool(True)
)


process.hltEcalUncalibRecHitLegacy = cms.EDProducer("EcalUncalibRecHitProducer",
    EBdigiCollection = cms.InputTag("hltEcalDigis","ebDigis"),
    EBhitCollection = cms.string('EcalUncalibRecHitsEB'),
    EEdigiCollection = cms.InputTag("hltEcalDigis","eeDigis"),
    EEhitCollection = cms.string('EcalUncalibRecHitsEE'),
    algo = cms.string('EcalUncalibRecHitWorkerMultiFit'),
    algoPSet = cms.PSet(
        EBamplitudeFitParameters = cms.vdouble(1.138, 1.652),
        EBtimeConstantTerm = cms.double(0.6),
        EBtimeFitLimits_Lower = cms.double(0.2),
        EBtimeFitLimits_Upper = cms.double(1.4),
        EBtimeFitParameters = cms.vdouble(
            -2.015452, 3.130702, -12.3473, 41.88921, -82.83944,
            91.01147, -50.35761, 11.05621
        ),
        EBtimeNconst = cms.double(28.5),
        EEamplitudeFitParameters = cms.vdouble(1.89, 1.4),
        EEtimeConstantTerm = cms.double(1.0),
        EEtimeFitLimits_Lower = cms.double(0.2),
        EEtimeFitLimits_Upper = cms.double(1.4),
        EEtimeFitParameters = cms.vdouble(
            -2.390548, 3.553628, -17.62341, 67.67538, -133.213,
            140.7432, -75.41106, 16.20277
        ),
        EEtimeNconst = cms.double(31.8),
        activeBXs = cms.vint32(
            -5, -4, -3, -2, -1,
            0, 1, 2, 3, 4
        ),
        addPedestalUncertaintyEB = cms.double(0.0),
        addPedestalUncertaintyEE = cms.double(0.0),
        ampErrorCalculation = cms.bool(False),
        amplitudeThresholdEB = cms.double(10.0),
        amplitudeThresholdEE = cms.double(10.0),
        doPrefitEB = cms.bool(False),
        doPrefitEE = cms.bool(False),
        dynamicPedestalsEB = cms.bool(False),
        dynamicPedestalsEE = cms.bool(False),
        gainSwitchUseMaxSampleEB = cms.bool(True),
        gainSwitchUseMaxSampleEE = cms.bool(False),
        mitigateBadSamplesEB = cms.bool(False),
        mitigateBadSamplesEE = cms.bool(False),
        outOfTimeThresholdGain12mEB = cms.double(1000.0),
        outOfTimeThresholdGain12mEE = cms.double(1000.0),
        outOfTimeThresholdGain12pEB = cms.double(1000.0),
        outOfTimeThresholdGain12pEE = cms.double(1000.0),
        outOfTimeThresholdGain61mEB = cms.double(1000.0),
        outOfTimeThresholdGain61mEE = cms.double(1000.0),
        outOfTimeThresholdGain61pEB = cms.double(1000.0),
        outOfTimeThresholdGain61pEE = cms.double(1000.0),
        prefitMaxChiSqEB = cms.double(25.0),
        prefitMaxChiSqEE = cms.double(10.0),
        selectiveBadSampleCriteriaEB = cms.bool(False),
        selectiveBadSampleCriteriaEE = cms.bool(False),
        simplifiedNoiseModelForGainSwitch = cms.bool(True),
        timealgo = cms.string('RatioMethod'),
        useLumiInfoRunHeader = cms.bool(False)
    )
)


process.hltEcalUncalibRecHitSoA = cms.EDProducer("EcalCPUUncalibRecHitProducer",
    containsTimingInformation = cms.bool(True),
    recHitsInLabelEB = cms.InputTag("hltEcalUncalibRecHitGPU","EcalUncalibRecHitsEB"),
    recHitsInLabelEE = cms.InputTag("hltEcalUncalibRecHitGPU","EcalUncalibRecHitsEE"),
    recHitsOutLabelEB = cms.string('EcalUncalibRecHitsEB'),
    recHitsOutLabelEE = cms.string('EcalUncalibRecHitsEE')
)


process.hltFEDSelector = cms.EDProducer("EvFFEDSelector",
    fedList = cms.vuint32(1023, 1024),
    inputTag = cms.InputTag("rawDataCollector")
)


process.hltFixedGridRhoFastjetAllCalo = cms.EDProducer("FixedGridRhoProducerFastjet",
    gridSpacing = cms.double(0.55),
    maxRapidity = cms.double(5.0),
    pfCandidatesTag = cms.InputTag("hltTowerMakerForAll")
)


process.hltFullIter0CkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersFullPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryBuilderForFullTrackingPPOnAA')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(True),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(True),
    maxNSeeds = cms.uint32(500000),
    maxSeedsBeforeCleaning = cms.uint32(5000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltFullIter0PixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(True)
)


process.hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTPSetInitialStepTrajectoryBuilderPreSplittingForFullTrackingPPOnAA')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(True),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(True),
    maxNSeeds = cms.uint32(500000),
    maxSeedsBeforeCleaning = cms.uint32(5000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltFullIter0PixelSeedsPreSplittingPPOnAA"),
    useHitsSplitting = cms.bool(True)
)


process.hltFullIter0CtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('initialStep'),
    Fitter = cms.string('hltESPFlexibleKFFittingSmoother'),
    GeometricInnerState = cms.bool(False),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag(""),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBuilderAngleAndTemplate'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltFullIter0CkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltFullIter0CtfWithMaterialTracksPreSplittingPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('initialStep'),
    Fitter = cms.string('hltESPFlexibleKFFittingSmoother'),
    GeometricInnerState = cms.bool(False),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag(""),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBuilderAngleAndTemplate'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(False)
)


process.hltFullIter0HighPurityTracksPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltFullIter0TrackMVAClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltFullIter0TrackMVAClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltFullIter0CtfWithMaterialTracksPPOnAA")
)


process.hltFullIter0PixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression"),
    MaxNumberOfCosmicClusters = cms.uint32(500000),
    MaxNumberOfPixelClusters = cms.uint32(150000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(True),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltFullIter0PixelClusterCheckPreSplittingPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityZeroSuppression"),
    MaxNumberOfCosmicClusters = cms.uint32(500000),
    MaxNumberOfPixelClusters = cms.uint32(150000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(True),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltFullIter0PixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltFullIter0PixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0, 1, 2),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltFullIter0PixelQuadrupletsPPOnAA"),
    trackingRegions = cms.InputTag("hltFullIter0PixelTrackingRegions"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltFullIter0PixelHitDoubletsPreSplittingPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltFullIter0PixelClusterCheckPreSplittingPPOnAA"),
    layerPairs = cms.vuint32(0, 1, 2),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltFullIter0PixelQuadrupletsPreSplittingPPOnAA"),
    trackingRegions = cms.InputTag("hltFullIter0PixelTrackingRegionsPreSplitting"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltFullIter0PixelHitQuadrupletsPPOnAA = cms.EDProducer("CAHitQuadrupletEDProducer",
    CAHardPtCut = cms.double(0.0),
    CAPhiCut = cms.double(0.2),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.0012),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('LowPtClusterShapeSeedComparitor'),
        clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCacheAfterSplittingPPOnAA"),
        clusterShapeHitFilter = cms.string('ClusterShapeHitFilter')
    ),
    doublets = cms.InputTag("hltFullIter0PixelHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    fitFastCircle = cms.bool(True),
    fitFastCircleChi2Cut = cms.bool(True),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.7),
        pt2 = cms.double(2.0),
        value1 = cms.double(200.0),
        value2 = cms.double(50.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltFullIter0PixelHitQuadrupletsPreSplittingPPOnAA = cms.EDProducer("CAHitQuadrupletEDProducer",
    CAHardPtCut = cms.double(0.0),
    CAPhiCut = cms.double(0.2),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.0012),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('LowPtClusterShapeSeedComparitor'),
        clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCachePPOnAA"),
        clusterShapeHitFilter = cms.string('ClusterShapeHitFilter')
    ),
    doublets = cms.InputTag("hltFullIter0PixelHitDoubletsPreSplittingPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    fitFastCircle = cms.bool(True),
    fitFastCircleChi2Cut = cms.bool(True),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.7),
        pt2 = cms.double(2.0),
        value1 = cms.double(200.0),
        value2 = cms.double(50.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltFullIter0PixelQuadrupletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0027),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3+BPix4',
        'BPix1+BPix2+BPix3+FPix1_pos',
        'BPix1+BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos+FPix2_pos',
        'BPix1+BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_neg+FPix2_neg+FPix3_neg'
    )
)


process.hltFullIter0PixelQuadrupletsPreSplittingPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3+BPix4',
        'BPix1+BPix2+BPix3+FPix1_pos',
        'BPix1+BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos+FPix2_pos',
        'BPix1+BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_neg+FPix2_neg+FPix3_neg'
    )
)


process.hltFullIter0PixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsTripletOnlyEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ClusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCacheAfterSplittingPPOnAA"),
        ClusterShapeHitFilterName = cms.string('ClusterShapeHitFilter'),
        ComponentName = cms.string('PixelClusterShapeSeedComparitor'),
        FilterAtHelixStage = cms.bool(False),
        FilterPixelHits = cms.bool(True),
        FilterStripHits = cms.bool(False)
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltFullIter0PixelHitQuadrupletsPPOnAA")
)


process.hltFullIter0PixelSeedsPreSplittingPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsTripletOnlyEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ClusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCachePPOnAA"),
        ClusterShapeHitFilterName = cms.string('ClusterShapeHitFilter'),
        ComponentName = cms.string('PixelClusterShapeSeedComparitor'),
        FilterAtHelixStage = cms.bool(False),
        FilterPixelHits = cms.bool(True),
        FilterStripHits = cms.bool(False)
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltFullIter0PixelHitQuadrupletsPreSplittingPPOnAA")
)


process.hltFullIter0PixelTrackingRegions = cms.EDProducer("GlobalTrackingRegionFromBeamSpotEDProducer",
    RegionPSet = cms.PSet(
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        nSigmaZ = cms.double(4.0),
        originHalfLength = cms.double(0.0),
        originRadius = cms.double(0.02),
        precise = cms.bool(True),
        ptMin = cms.double(1.0),
        useMultipleScattering = cms.bool(False)
    )
)


process.hltFullIter0PixelTrackingRegionsPreSplitting = cms.EDProducer("GlobalTrackingRegionFromBeamSpotEDProducer",
    RegionPSet = cms.PSet(
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        nSigmaZ = cms.double(4.0),
        originHalfLength = cms.double(0.0),
        originRadius = cms.double(0.02),
        precise = cms.bool(True),
        ptMin = cms.double(1.0),
        useMultipleScattering = cms.bool(False)
    )
)


process.hltFullIter0PrimaryVerticesPPOnAA = cms.EDProducer("PrimaryVertexProducer",
    TkClusParameters = cms.PSet(
        TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(1.0)
        ),
        algorithm = cms.string('gap')
    ),
    TkFilterParameters = cms.PSet(
        algorithm = cms.string('filter'),
        maxD0Significance = cms.double(2.0),
        maxEta = cms.double(2.4),
        maxNormalizedChi2 = cms.double(10.0),
        minPixelLayersWithHits = cms.int32(3),
        minPt = cms.double(0.7),
        minSiliconLayersWithHits = cms.int32(5),
        trackQuality = cms.string('any')
    ),
    TrackLabel = cms.InputTag("hltFullIter0CtfWithMaterialTracksPPOnAA"),
    TrackTimeResosLabel = cms.InputTag("dummy_default"),
    TrackTimesLabel = cms.InputTag("dummy_default"),
    beamSpotLabel = cms.InputTag("hltOnlineBeamSpot"),
    isRecoveryIteration = cms.bool(False),
    recoveryVtxCollection = cms.InputTag(""),
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


process.hltFullIter0PrimaryVerticesPreSplittingPPOnAA = cms.EDProducer("PrimaryVertexProducer",
    TkClusParameters = cms.PSet(
        TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(1.0)
        ),
        algorithm = cms.string('gap')
    ),
    TkFilterParameters = cms.PSet(
        algorithm = cms.string('filter'),
        maxD0Significance = cms.double(2.0),
        maxEta = cms.double(2.4),
        maxNormalizedChi2 = cms.double(10.0),
        minPixelLayersWithHits = cms.int32(3),
        minPt = cms.double(0.7),
        minSiliconLayersWithHits = cms.int32(5),
        trackQuality = cms.string('any')
    ),
    TrackLabel = cms.InputTag("hltFullIter0CtfWithMaterialTracksPreSplittingPPOnAA"),
    TrackTimeResosLabel = cms.InputTag("dummy_default"),
    TrackTimesLabel = cms.InputTag("dummy_default"),
    beamSpotLabel = cms.InputTag("hltOnlineBeamSpot"),
    isRecoveryIteration = cms.bool(False),
    recoveryVtxCollection = cms.InputTag(""),
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


process.hltFullIter0TrackMVAClassifierPPOnAA = cms.EDProducer("TrackMVAClassifierPrompt",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        GBRForestFileName = cms.string(''),
        GBRForestLabel = cms.string('HIMVASelectorInitialStep_Phase1')
    ),
    qualityCuts = cms.vdouble(-0.9, -0.5, 0.2),
    src = cms.InputTag("hltFullIter0CtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltFullIter0PrimaryVerticesPPOnAA")
)


process.hltFullIter1CkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltFullIter1MaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTPSetLowPtQuadStepTrajectoryBuilderForFullTrackingPPOnAA')
    ),
    TrajectoryCleaner = cms.string('hltESPLowPtQuadStepTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(True),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(True),
    maxNSeeds = cms.uint32(500000),
    maxSeedsBeforeCleaning = cms.uint32(5000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltFullIter1PixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(True)
)


process.hltFullIter1ClustersRefRemovalPPOnAA = cms.EDProducer("TrackClusterRemover",
    TrackQuality = cms.string('highPurity'),
    maxChi2 = cms.double(9.0),
    minNumberOfLayersWithMeasBeforeFiltering = cms.int32(0),
    oldClusterRemovalInfo = cms.InputTag(""),
    overrideTrkQuals = cms.InputTag(""),
    pixelClusters = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA"),
    stripClusters = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression"),
    trackClassifier = cms.InputTag("","QualityMasks"),
    trajectories = cms.InputTag("hltFullIter0HighPurityTracksPPOnAA")
)


process.hltFullIter1CtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('lowPtQuadStep'),
    Fitter = cms.string('hltESPFlexibleKFFittingSmoother'),
    GeometricInnerState = cms.bool(False),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltFullIter1MaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBuilderAngleAndTemplate'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltFullIter1CkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltFullIter1HighPurityTracksPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltFullIter1TrackMVAClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltFullIter1TrackMVAClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltFullIter1CtfWithMaterialTracksPPOnAA")
)


process.hltFullIter1MaskedMeasurementTrackerEventPPOnAA = cms.EDProducer("MaskedMeasurementTrackerEventProducer",
    OnDemand = cms.bool(False),
    clustersToSkip = cms.InputTag("hltFullIter1ClustersRefRemovalPPOnAA"),
    src = cms.InputTag("hltSiStripClustersFullPPOnAA")
)


process.hltFullIter1PixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression"),
    MaxNumberOfCosmicClusters = cms.uint32(500000),
    MaxNumberOfPixelClusters = cms.uint32(150000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(True),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltFullIter1PixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltFullIter1PixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0, 1, 2),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltFullIter1PixelQuadrupletsPPOnAA"),
    trackingRegions = cms.InputTag("hltFullIter1PixelTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltFullIter1PixelHitQuadrupletsPPOnAA = cms.EDProducer("CAHitQuadrupletEDProducer",
    CAHardPtCut = cms.double(0.0),
    CAPhiCut = cms.double(0.3),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.0017),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('LowPtClusterShapeSeedComparitor'),
        clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCacheAfterSplittingPPOnAA"),
        clusterShapeHitFilter = cms.string('ClusterShapeHitFilter')
    ),
    doublets = cms.InputTag("hltFullIter1PixelHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    fitFastCircle = cms.bool(True),
    fitFastCircleChi2Cut = cms.bool(True),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.7),
        pt2 = cms.double(2.0),
        value1 = cms.double(1000.0),
        value2 = cms.double(150.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltFullIter1PixelQuadrupletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0027),
        skipClusters = cms.InputTag("hltFullIter1ClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        skipClusters = cms.InputTag("hltFullIter1ClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3+BPix4',
        'BPix1+BPix2+BPix3+FPix1_pos',
        'BPix1+BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos+FPix2_pos',
        'BPix1+BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_neg+FPix2_neg+FPix3_neg'
    )
)


process.hltFullIter1PixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltFullIter1PixelHitQuadrupletsPPOnAA")
)


process.hltFullIter1PixelTrackingRegionsPPOnAA = cms.EDProducer("GlobalTrackingRegionWithVerticesEDProducer",
    RegionPSet = cms.PSet(
        VertexCollection = cms.InputTag("hltFullIter0PrimaryVerticesPPOnAA"),
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        fixedError = cms.double(0.5),
        maxNVertices = cms.int32(-1),
        nSigmaZ = cms.double(4.0),
        originRadius = cms.double(0.02),
        precise = cms.bool(True),
        ptMin = cms.double(1.0),
        sigmaZVertex = cms.double(4.0),
        useFakeVertices = cms.bool(False),
        useFixedError = cms.bool(True),
        useFoundVertices = cms.bool(True),
        useMultipleScattering = cms.bool(False)
    )
)


process.hltFullIter1TrackMVAClassifierPPOnAA = cms.EDProducer("TrackMVAClassifierPrompt",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        GBRForestFileName = cms.string(''),
        GBRForestLabel = cms.string('HIMVASelectorLowPtQuadStep_Phase1')
    ),
    qualityCuts = cms.vdouble(-0.9, -0.4, 0.3),
    src = cms.InputTag("hltFullIter1CtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltFullIter0PrimaryVerticesPPOnAA")
)


process.hltFullIter2CkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltFullIter2MaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTPSetHighPtTripletStepTrajectoryBuilderForFullTrackingPPOnAA')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(True),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(True),
    maxNSeeds = cms.uint32(500000),
    maxSeedsBeforeCleaning = cms.uint32(5000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltFullIter2PixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(True)
)


process.hltFullIter2ClustersRefRemovalPPOnAA = cms.EDProducer("TrackClusterRemover",
    TrackQuality = cms.string('highPurity'),
    maxChi2 = cms.double(9.0),
    minNumberOfLayersWithMeasBeforeFiltering = cms.int32(0),
    oldClusterRemovalInfo = cms.InputTag("hltFullIter1ClustersRefRemovalPPOnAA"),
    overrideTrkQuals = cms.InputTag(""),
    pixelClusters = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA"),
    stripClusters = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression"),
    trackClassifier = cms.InputTag("","QualityMasks"),
    trajectories = cms.InputTag("hltFullIter1HighPurityTracksPPOnAA")
)


process.hltFullIter2CtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('highPtTripletStep'),
    Fitter = cms.string('hltESPFlexibleKFFittingSmoother'),
    GeometricInnerState = cms.bool(False),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltFullIter2MaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBuilderAngleAndTemplate'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltFullIter2CkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltFullIter2HighPurityTracksPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltFullIter2TrackMVAClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltFullIter2TrackMVAClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltFullIter2CtfWithMaterialTracksPPOnAA")
)


process.hltFullIter2MaskedMeasurementTrackerEventPPOnAA = cms.EDProducer("MaskedMeasurementTrackerEventProducer",
    OnDemand = cms.bool(False),
    clustersToSkip = cms.InputTag("hltFullIter2ClustersRefRemovalPPOnAA"),
    src = cms.InputTag("hltSiStripClustersFullPPOnAA")
)


process.hltFullIter2PixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression"),
    MaxNumberOfCosmicClusters = cms.uint32(500000),
    MaxNumberOfPixelClusters = cms.uint32(150000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(True),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltFullIter2PixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltFullIter2PixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0, 1),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltFullIter2PixelTripletsPPOnAA"),
    trackingRegions = cms.InputTag("hltFullIter2PixelTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltFullIter2PixelHitTripletsPPOnAA = cms.EDProducer("CAHitTripletEDProducer",
    CAHardPtCut = cms.double(0.3),
    CAPhiCut = cms.double(0.07),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.004),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('LowPtClusterShapeSeedComparitor'),
        clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCacheAfterSplittingPPOnAA"),
        clusterShapeHitFilter = cms.string('ClusterShapeHitFilter')
    ),
    doublets = cms.InputTag("hltFullIter2PixelHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.8),
        pt2 = cms.double(8.0),
        value1 = cms.double(100.0),
        value2 = cms.double(6.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltFullIter2PixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltFullIter2PixelHitTripletsPPOnAA")
)


process.hltFullIter2PixelTrackingRegionsPPOnAA = cms.EDProducer("GlobalTrackingRegionWithVerticesEDProducer",
    RegionPSet = cms.PSet(
        VertexCollection = cms.InputTag("hltFullIter0PrimaryVerticesPPOnAA"),
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        fixedError = cms.double(0.2),
        maxNVertices = cms.int32(-1),
        nSigmaZ = cms.double(4.0),
        originRadius = cms.double(0.02),
        precise = cms.bool(True),
        ptMin = cms.double(1.0),
        sigmaZVertex = cms.double(4.0),
        useFakeVertices = cms.bool(False),
        useFixedError = cms.bool(True),
        useFoundVertices = cms.bool(True),
        useMultipleScattering = cms.bool(False)
    )
)


process.hltFullIter2PixelTripletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0027),
        skipClusters = cms.InputTag("hltFullIter2ClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsAfterSplittingPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        skipClusters = cms.InputTag("hltFullIter2ClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3',
        'BPix2+BPix3+BPix4',
        'BPix1+BPix3+BPix4',
        'BPix1+BPix2+BPix4',
        'BPix2+BPix3+FPix1_pos',
        'BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos',
        'BPix1+BPix2+FPix1_neg',
        'BPix1+BPix3+FPix1_pos',
        'BPix1+BPix3+FPix1_neg',
        'BPix2+FPix1_pos+FPix2_pos',
        'BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos',
        'BPix1+FPix1_neg+FPix2_neg',
        'BPix1+BPix2+FPix2_pos',
        'BPix1+BPix2+FPix2_neg',
        'FPix1_pos+FPix2_pos+FPix3_pos',
        'FPix1_neg+FPix2_neg+FPix3_neg',
        'BPix1+FPix2_pos+FPix3_pos',
        'BPix1+FPix2_neg+FPix3_neg',
        'BPix1+FPix1_pos+FPix3_pos',
        'BPix1+FPix1_neg+FPix3_neg'
    )
)


process.hltFullIter2TrackMVAClassifierPPOnAA = cms.EDProducer("TrackMVAClassifierPrompt",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        GBRForestFileName = cms.string(''),
        GBRForestLabel = cms.string('HIMVASelectorHighPtTripletStep_Phase1')
    ),
    qualityCuts = cms.vdouble(-0.9, -0.3, 0.85),
    src = cms.InputTag("hltFullIter2CtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltFullIter0PrimaryVerticesPPOnAA")
)


process.hltGemRecHits = cms.EDProducer("GEMRecHitProducer",
    applyMasking = cms.bool(False),
    ge21Off = cms.bool(False),
    gemDigiLabel = cms.InputTag("hltMuonGEMDigis"),
    recAlgo = cms.string('GEMRecHitStandardAlgo'),
    recAlgoConfig = cms.PSet(

    )
)


process.hltGemSegments = cms.EDProducer("GEMSegmentProducer",
    algo_name = cms.string('GEMSegmentAlgorithm'),
    algo_pset = cms.PSet(
        clusterOnlySameBXRecHits = cms.bool(True),
        dEtaChainBoxMax = cms.double(0.05),
        dPhiChainBoxMax = cms.double(0.02),
        dXclusBoxMax = cms.double(1.0),
        dYclusBoxMax = cms.double(5.0),
        maxRecHitsInCluster = cms.int32(4),
        minHitsPerSegment = cms.uint32(2),
        preClustering = cms.bool(True),
        preClusteringUseChaining = cms.bool(True)
    ),
    ge0_name = cms.string('GE0SegAlgoRU'),
    ge0_pset = cms.PSet(
        allowWideSegments = cms.bool(True),
        doCollisions = cms.bool(True),
        maxChi2Additional = cms.double(100.0),
        maxChi2GoodSeg = cms.double(50.0),
        maxChi2Prune = cms.double(50.0),
        maxETASeeds = cms.double(0.1),
        maxNumberOfHits = cms.uint32(300),
        maxNumberOfHitsPerLayer = cms.uint32(100),
        maxPhiAdditional = cms.double(0.001096605744),
        maxPhiSeeds = cms.double(0.001096605744),
        maxTOFDiff = cms.double(25.0),
        minNumberOfHits = cms.uint32(4),
        requireCentralBX = cms.bool(True)
    ),
    gemRecHitLabel = cms.InputTag("hltGemRecHits")
)


process.hltGtStage2Digis = cms.EDProducer("L1TRawToDigi",
    CTP7 = cms.untracked.bool(False),
    DmxFWId = cms.uint32(0),
    FWId = cms.uint32(0),
    FWOverride = cms.bool(False),
    FedIds = cms.vint32(1404),
    InputLabel = cms.InputTag("rawDataCollector"),
    MTF7 = cms.untracked.bool(False),
    MinFeds = cms.uint32(0),
    Setup = cms.string('stage2::GTSetup'),
    TMTCheck = cms.bool(True),
    debug = cms.untracked.bool(False),
    lenAMC13Header = cms.untracked.int32(8),
    lenAMC13Trailer = cms.untracked.int32(8),
    lenAMCHeader = cms.untracked.int32(8),
    lenAMCTrailer = cms.untracked.int32(0),
    lenSlinkHeader = cms.untracked.int32(8),
    lenSlinkTrailer = cms.untracked.int32(8)
)


process.hltGtStage2ObjectMap = cms.EDProducer("L1TGlobalProducer",
    AlgoBlkInputTag = cms.InputTag("hltGtStage2Digis"),
    AlgorithmTriggersUnmasked = cms.bool(True),
    AlgorithmTriggersUnprescaled = cms.bool(True),
    AlternativeNrBxBoardDaq = cms.uint32(0),
    BstLengthBytes = cms.int32(-1),
    EGammaInputTag = cms.InputTag("hltGtStage2Digis","EGamma"),
    EmulateBxInEvent = cms.int32(1),
    EtSumInputTag = cms.InputTag("hltGtStage2Digis","EtSum"),
    ExtInputTag = cms.InputTag("hltGtStage2Digis"),
    GetPrescaleColumnFromData = cms.bool(False),
    JetInputTag = cms.InputTag("hltGtStage2Digis","Jet"),
    L1DataBxInEvent = cms.int32(5),
    MuonInputTag = cms.InputTag("hltGtStage2Digis","Muon"),
    MuonShowerInputTag = cms.InputTag("hltGtStage2Digis","MuonShower"),
    PrescaleSet = cms.uint32(1),
    PrintL1Menu = cms.untracked.bool(False),
    ProduceL1GtDaqRecord = cms.bool(True),
    ProduceL1GtObjectMapRecord = cms.bool(True),
    RequireMenuToMatchAlgoBlkInput = cms.bool(True),
    TauInputTag = cms.InputTag("hltGtStage2Digis","Tau"),
    TriggerMenuLuminosity = cms.string('startup'),
    Verbosity = cms.untracked.int32(0),
    resetPSCountersEachLumiSec = cms.bool(True),
    semiRandomInitialPSCounters = cms.bool(False),
    useMuonShowers = cms.bool(True)
)


process.hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression = cms.EDProducer("SiStripClusterizer",
    Clusterizer = cms.PSet(
        Algorithm = cms.string('ThreeThresholdAlgorithm'),
        ChannelThreshold = cms.double(2.0),
        ClusterThreshold = cms.double(5.0),
        ConditionsLabel = cms.string(''),
        MaxAdjacentBad = cms.uint32(0),
        MaxSequentialBad = cms.uint32(1),
        MaxSequentialHoles = cms.uint32(0),
        RemoveApvShots = cms.bool(True),
        SeedThreshold = cms.double(3.0),
        clusterChargeCut = cms.PSet(
            refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
        )
    ),
    DigiProducersList = cms.VInputTag("hltSiStripZeroSuppression:VirginRaw", "hltSiStripZeroSuppression:ProcessedRaw", "hltSiStripZeroSuppression:ScopeMode", "hltSiStripZeroSuppression:ZeroSuppressed")
)


process.hltHITrackingSiStripRawToClustersFacilityZeroSuppression = cms.EDProducer("SiStripClusterizer",
    Clusterizer = cms.PSet(
        Algorithm = cms.string('ThreeThresholdAlgorithm'),
        ChannelThreshold = cms.double(2.0),
        ClusterThreshold = cms.double(5.0),
        ConditionsLabel = cms.string(''),
        MaxAdjacentBad = cms.uint32(0),
        MaxSequentialBad = cms.uint32(1),
        MaxSequentialHoles = cms.uint32(0),
        RemoveApvShots = cms.bool(True),
        SeedThreshold = cms.double(3.0),
        clusterChargeCut = cms.PSet(
            refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
        )
    ),
    DigiProducersList = cms.VInputTag("hltSiStripZeroSuppression:VirginRaw", "hltSiStripZeroSuppression:ProcessedRaw", "hltSiStripZeroSuppression:ScopeMode", "hltSiStripZeroSuppression:ZeroSuppressed")
)


process.hltHbherecoFromGPU = cms.EDProducer("HcalCPURecHitsProducer",
    produceLegacy = cms.bool(True),
    produceSoA = cms.bool(True),
    recHitsLegacyLabelOut = cms.string(''),
    recHitsM0LabelIn = cms.InputTag("hltHbherecoGPU"),
    recHitsM0LabelOut = cms.string('')
)


process.hltHbherecoGPU = cms.EDProducer("HBHERecHitProducerGPU",
    applyTimeSlew = cms.bool(True),
    digisLabelF01HE = cms.InputTag("hltHcalDigisGPU"),
    digisLabelF3HB = cms.InputTag("hltHcalDigisGPU"),
    digisLabelF5HB = cms.InputTag("hltHcalDigisGPU"),
    firstSampleShift = cms.int32(0),
    kernelMinimizeThreads = cms.vuint32(16, 1, 1),
    kprep1dChannelsPerBlock = cms.uint32(32),
    maxChannels = cms.uint32(10000),
    maxTimeSamples = cms.uint32(10),
    meanTime = cms.double(0.0),
    recHitsLabelM0HBHE = cms.string(''),
    sipmQNTStoSum = cms.int32(3),
    sipmQTSShift = cms.int32(0),
    slopeTimeSlewParameters = cms.vdouble(-3.178648, -1.5610227, -1.075824),
    timeSigmaHPD = cms.double(5.0),
    timeSigmaSiPM = cms.double(2.5),
    tmaxTimeSlewParameters = cms.vdouble(16.0, 10.0, 6.25),
    ts4Thresh = cms.double(0.0),
    tzeroTimeSlewParameters = cms.vdouble(23.960177, 11.977461, 9.109694),
    useEffectivePedestals = cms.bool(True)
)


process.hltHbherecoLegacy = cms.EDProducer("HBHEPhase1Reconstructor",
    algoConfigClass = cms.string(''),
    algorithm = cms.PSet(
        Class = cms.string('SimpleHBHEPhase1Algo'),
        activeBXs = cms.vint32(
            -3, -2, -1, 0, 1,
            2, 3, 4
        ),
        applyLegacyHBMCorrection = cms.bool(False),
        applyPedConstraint = cms.bool(False),
        applyPulseJitter = cms.bool(False),
        applyTimeConstraint = cms.bool(False),
        applyTimeSlew = cms.bool(True),
        applyTimeSlewM3 = cms.bool(True),
        calculateArrivalTime = cms.bool(False),
        chiSqSwitch = cms.double(-1.0),
        correctForPhaseContainment = cms.bool(True),
        correctionPhaseNS = cms.double(6.0),
        deltaChiSqThresh = cms.double(0.001),
        dynamicPed = cms.bool(False),
        firstSampleShift = cms.int32(0),
        fitTimes = cms.int32(1),
        meanPed = cms.double(0.0),
        meanTime = cms.double(0.0),
        nMaxItersMin = cms.int32(50),
        nMaxItersNNLS = cms.int32(500),
        nnlsThresh = cms.double(1e-11),
        pulseJitter = cms.double(1.0),
        respCorrM3 = cms.double(1.0),
        samplesToAdd = cms.int32(2),
        tdcTimeShift = cms.double(0.0),
        timeMax = cms.double(12.5),
        timeMin = cms.double(-12.5),
        timeSigmaHPD = cms.double(5.0),
        timeSigmaSiPM = cms.double(2.5),
        timeSlewParsType = cms.int32(3),
        ts4Max = cms.vdouble(100.0, 20000.0, 30000.0),
        ts4Min = cms.double(0.0),
        ts4Thresh = cms.double(0.0),
        ts4chi2 = cms.vdouble(15.0, 15.0),
        useM2 = cms.bool(False),
        useM3 = cms.bool(False),
        useMahi = cms.bool(True)
    ),
    digiLabelQIE11 = cms.InputTag("hltHcalDigis"),
    digiLabelQIE8 = cms.InputTag("hltHcalDigis"),
    dropZSmarkedPassed = cms.bool(True),
    flagParametersQIE11 = cms.PSet(

    ),
    flagParametersQIE8 = cms.PSet(
        hitEnergyMinimum = cms.double(1.0),
        hitMultiplicityThreshold = cms.int32(17),
        nominalPedestal = cms.double(3.0),
        pulseShapeParameterSets = cms.VPSet(
            cms.PSet(
                pulseShapeParameters = cms.vdouble(
                    0.0, 100.0, -50.0, 0.0, -15.0,
                    0.15
                )
            ),
            cms.PSet(
                pulseShapeParameters = cms.vdouble(
                    100.0, 2000.0, -50.0, 0.0, -5.0,
                    0.05
                )
            ),
            cms.PSet(
                pulseShapeParameters = cms.vdouble(
                    2000.0, 1000000.0, -50.0, 0.0, 95.0,
                    0.0
                )
            ),
            cms.PSet(
                pulseShapeParameters = cms.vdouble(
                    -1000000.0, 1000000.0, 45.0, 0.1, 1000000.0,
                    0.0
                )
            )
        )
    ),
    makeRecHits = cms.bool(True),
    processQIE11 = cms.bool(True),
    processQIE8 = cms.bool(False),
    pulseShapeParametersQIE11 = cms.PSet(

    ),
    pulseShapeParametersQIE8 = cms.PSet(
        LeftSlopeCut = cms.vdouble(5.0, 2.55, 2.55),
        LeftSlopeThreshold = cms.vdouble(250.0, 500.0, 100000.0),
        LinearCut = cms.vdouble(-3.0, -0.054, -0.054),
        LinearThreshold = cms.vdouble(20.0, 100.0, 100000.0),
        MinimumChargeThreshold = cms.double(20.0),
        MinimumTS4TS5Threshold = cms.double(100.0),
        R45MinusOneRange = cms.double(0.2),
        R45PlusOneRange = cms.double(0.2),
        RMS8MaxCut = cms.vdouble(-13.5, -11.5, -11.5),
        RMS8MaxThreshold = cms.vdouble(20.0, 100.0, 100000.0),
        RightSlopeCut = cms.vdouble(5.0, 4.15, 4.15),
        RightSlopeSmallCut = cms.vdouble(1.08, 1.16, 1.16),
        RightSlopeSmallThreshold = cms.vdouble(150.0, 200.0, 100000.0),
        RightSlopeThreshold = cms.vdouble(250.0, 400.0, 100000.0),
        TS3TS4ChargeThreshold = cms.double(70.0),
        TS3TS4UpperChargeThreshold = cms.double(20.0),
        TS4TS5ChargeThreshold = cms.double(70.0),
        TS4TS5LowerCut = cms.vdouble(
            -1.0, -0.7, -0.5, -0.4, -0.3,
            0.1
        ),
        TS4TS5LowerThreshold = cms.vdouble(
            100.0, 120.0, 160.0, 200.0, 300.0,
            500.0
        ),
        TS4TS5UpperCut = cms.vdouble(1.0, 0.8, 0.75, 0.72),
        TS4TS5UpperThreshold = cms.vdouble(70.0, 90.0, 100.0, 400.0),
        TS5TS6ChargeThreshold = cms.double(70.0),
        TS5TS6UpperChargeThreshold = cms.double(20.0),
        TriangleIgnoreSlow = cms.bool(False),
        TrianglePeakTS = cms.uint32(10000),
        UseDualFit = cms.bool(True)
    ),
    recoParamsFromDB = cms.bool(True),
    saveDroppedInfos = cms.bool(False),
    saveEffectivePedestal = cms.bool(True),
    saveInfos = cms.bool(False),
    setLegacyFlagsQIE11 = cms.bool(False),
    setLegacyFlagsQIE8 = cms.bool(False),
    setNegativeFlagsQIE11 = cms.bool(False),
    setNegativeFlagsQIE8 = cms.bool(False),
    setNoiseFlagsQIE11 = cms.bool(False),
    setNoiseFlagsQIE8 = cms.bool(False),
    setPulseShapeFlagsQIE11 = cms.bool(False),
    setPulseShapeFlagsQIE8 = cms.bool(False),
    sipmQNTStoSum = cms.int32(3),
    sipmQTSShift = cms.int32(0),
    tsFromDB = cms.bool(False),
    use8ts = cms.bool(True)
)


process.hltHcalDigis = cms.EDProducer("HcalRawToDigi",
    ComplainEmptyData = cms.untracked.bool(False),
    ElectronicsMap = cms.string(''),
    ExpectedOrbitMessageTime = cms.untracked.int32(-1),
    FEDs = cms.untracked.vint32(),
    FilterDataQuality = cms.bool(True),
    HcalFirstFED = cms.untracked.int32(700),
    InputLabel = cms.InputTag("rawDataCollector"),
    UnpackCalib = cms.untracked.bool(True),
    UnpackTTP = cms.untracked.bool(False),
    UnpackUMNio = cms.untracked.bool(True),
    UnpackZDC = cms.untracked.bool(True),
    UnpackerMode = cms.untracked.int32(0),
    firstSample = cms.int32(0),
    lastSample = cms.int32(9),
    saveQIE10DataNSamples = cms.untracked.vint32(),
    saveQIE10DataTags = cms.untracked.vstring(),
    saveQIE11DataNSamples = cms.untracked.vint32(),
    saveQIE11DataTags = cms.untracked.vstring(),
    silent = cms.untracked.bool(True)
)


process.hltHcalDigisGPU = cms.EDProducer("HcalDigisProducerGPU",
    digisLabelF01HE = cms.string(''),
    digisLabelF3HB = cms.string(''),
    digisLabelF5HB = cms.string(''),
    hbheDigisLabel = cms.InputTag("hltHcalDigis"),
    maxChannelsF01HE = cms.uint32(10000),
    maxChannelsF3HB = cms.uint32(10000),
    maxChannelsF5HB = cms.uint32(10000),
    qie11DigiLabel = cms.InputTag("hltHcalDigis")
)


process.hltHfprereco = cms.EDProducer("HFPreReconstructor",
    digiLabel = cms.InputTag("hltHcalDigis"),
    dropZSmarkedPassed = cms.bool(True),
    forceSOI = cms.int32(-1),
    soiShift = cms.int32(0),
    sumAllTimeSlices = cms.bool(False),
    tsFromDB = cms.bool(False)
)


process.hltHfreco = cms.EDProducer("HFPhase1Reconstructor",
    HFStripFilter = cms.PSet(
        gap = cms.int32(2),
        lstrips = cms.int32(2),
        maxStripTime = cms.double(10.0),
        maxThreshold = cms.double(100.0),
        seedHitIetaMax = cms.int32(35),
        stripThreshold = cms.double(40.0),
        timeMax = cms.double(6.0),
        verboseLevel = cms.untracked.int32(10),
        wedgeCut = cms.double(0.05)
    ),
    PETstat = cms.PSet(
        HcalAcceptSeverityLevel = cms.int32(9),
        longETParams = cms.vdouble(
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        ),
        longEnergyParams = cms.vdouble(
            43.5, 45.7, 48.32, 51.36, 54.82,
            58.7, 63.0, 67.72, 72.86, 78.42,
            84.4, 90.8, 97.62
        ),
        long_R = cms.vdouble(0.98),
        long_R_29 = cms.vdouble(0.8),
        shortETParams = cms.vdouble(
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        ),
        shortEnergyParams = cms.vdouble(
            35.1773, 35.37, 35.7933, 36.4472, 37.3317,
            38.4468, 39.7925, 41.3688, 43.1757, 45.2132,
            47.4813, 49.98, 52.7093
        ),
        short_R = cms.vdouble(0.8),
        short_R_29 = cms.vdouble(0.8)
    ),
    S8S1stat = cms.PSet(
        HcalAcceptSeverityLevel = cms.int32(9),
        isS8S1 = cms.bool(True),
        longETParams = cms.vdouble(
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        ),
        longEnergyParams = cms.vdouble(
            40.0, 100.0, 100.0, 100.0, 100.0,
            100.0, 100.0, 100.0, 100.0, 100.0,
            100.0, 100.0, 100.0
        ),
        long_optimumSlope = cms.vdouble(
            0.3, 0.1, 0.1, 0.1, 0.1,
            0.1, 0.1, 0.1, 0.1, 0.1,
            0.1, 0.1, 0.1
        ),
        shortETParams = cms.vdouble(
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        ),
        shortEnergyParams = cms.vdouble(
            40.0, 100.0, 100.0, 100.0, 100.0,
            100.0, 100.0, 100.0, 100.0, 100.0,
            100.0, 100.0, 100.0
        ),
        short_optimumSlope = cms.vdouble(
            0.3, 0.1, 0.1, 0.1, 0.1,
            0.1, 0.1, 0.1, 0.1, 0.1,
            0.1, 0.1, 0.1
        )
    ),
    S9S1stat = cms.PSet(
        HcalAcceptSeverityLevel = cms.int32(9),
        isS8S1 = cms.bool(False),
        longETParams = cms.vdouble(
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        ),
        longEnergyParams = cms.vdouble(
            43.5, 45.7, 48.32, 51.36, 54.82,
            58.7, 63.0, 67.72, 72.86, 78.42,
            84.4, 90.8, 97.62
        ),
        long_optimumSlope = cms.vdouble(
            -99999.0, 0.0164905, 0.0238698, 0.0321383, 0.041296,
            0.0513428, 0.0622789, 0.0741041, 0.0868186, 0.100422,
            0.135313, 0.136289, 0.0589927
        ),
        shortETParams = cms.vdouble(
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        ),
        shortEnergyParams = cms.vdouble(
            35.1773, 35.37, 35.7933, 36.4472, 37.3317,
            38.4468, 39.7925, 41.3688, 43.1757, 45.2132,
            47.4813, 49.98, 52.7093
        ),
        short_optimumSlope = cms.vdouble(
            -99999.0, 0.0164905, 0.0238698, 0.0321383, 0.041296,
            0.0513428, 0.0622789, 0.0741041, 0.0868186, 0.100422,
            0.135313, 0.136289, 0.0589927
        )
    ),
    algoConfigClass = cms.string('HFPhase1PMTParams'),
    algorithm = cms.PSet(
        Class = cms.string('HFFlexibleTimeCheck'),
        energyWeights = cms.vdouble(
            1.0, 1.0, 1.0, 0.0, 1.0,
            0.0, 2.0, 0.0, 2.0, 0.0,
            2.0, 0.0, 1.0, 0.0, 0.0,
            1.0, 0.0, 1.0, 0.0, 2.0,
            0.0, 2.0, 0.0, 2.0, 0.0,
            1.0
        ),
        rejectAllFailures = cms.bool(True),
        soiPhase = cms.uint32(1),
        tfallIfNoTDC = cms.double(-101.0),
        timeShift = cms.double(0.0),
        tlimits = cms.vdouble(-1000.0, 1000.0, -1000.0, 1000.0),
        triseIfNoTDC = cms.double(-100.0)
    ),
    checkChannelQualityForDepth3and4 = cms.bool(False),
    inputLabel = cms.InputTag("hltHfprereco"),
    runHFStripFilter = cms.bool(False),
    setNoiseFlags = cms.bool(True),
    useChannelQualityFromDB = cms.bool(False)
)


process.hltHiFJRhoProducer = cms.EDProducer("HiFJRhoProducer",
    etaMaxExcl = cms.double(2.0),
    etaMaxExcl2 = cms.double(3.0),
    etaRanges = cms.vdouble(
        -5.0, -3.0, -2.1, -1.3, 1.3,
        2.1, 3.0, 5.0
    ),
    jetSource = cms.InputTag("hltKT4PFJetsForRho"),
    nExcl = cms.int32(2),
    nExcl2 = cms.int32(1),
    ptMinExcl = cms.double(20.0),
    ptMinExcl2 = cms.double(20.0)
)


process.hltHoreco = cms.EDProducer("HcalHitReconstructor",
    HFInWindowStat = cms.PSet(

    ),
    PETstat = cms.PSet(

    ),
    S8S1stat = cms.PSet(

    ),
    S9S1stat = cms.PSet(

    ),
    Subdetector = cms.string('HO'),
    correctForPhaseContainment = cms.bool(True),
    correctForTimeslew = cms.bool(True),
    correctTiming = cms.bool(False),
    correctionPhaseNS = cms.double(13.0),
    dataOOTCorrectionCategory = cms.string('Data'),
    dataOOTCorrectionName = cms.string(''),
    digiLabel = cms.InputTag("hltHcalDigis"),
    digiTimeFromDB = cms.bool(True),
    digistat = cms.PSet(

    ),
    dropZSmarkedPassed = cms.bool(True),
    firstAuxTS = cms.int32(4),
    firstSample = cms.int32(4),
    hfTimingTrustParameters = cms.PSet(

    ),
    mcOOTCorrectionCategory = cms.string('MC'),
    mcOOTCorrectionName = cms.string(''),
    recoParamsFromDB = cms.bool(True),
    samplesToAdd = cms.int32(4),
    saturationParameters = cms.PSet(
        maxADCvalue = cms.int32(127)
    ),
    setHSCPFlags = cms.bool(False),
    setNegativeFlags = cms.bool(False),
    setNoiseFlags = cms.bool(False),
    setPulseShapeFlags = cms.bool(False),
    setSaturationFlags = cms.bool(False),
    setTimingTrustFlags = cms.bool(False),
    tsFromDB = cms.bool(True),
    useLeakCorrection = cms.bool(False)
)


process.hltIter0IterL3FromL1MuonCkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('none'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTIter0IterL3FromL1MuonPSetGroupedCkfTrajectoryBuilderIT')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(True),
    maxNSeeds = cms.uint32(100000),
    maxSeedsBeforeCleaning = cms.uint32(1000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltIter0IterL3FromL1MuonPixelSeedsFromPixelTracksPPOnAA"),
    useHitsSplitting = cms.bool(True)
)


process.hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('hltIter0'),
    Fitter = cms.string('hltESPFittingSmootherIT'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltIter0IterL3FromL1MuonCkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltIter0IterL3FromL1MuonPixelSeedsFromPixelTracksPPOnAA = cms.EDProducer("SeedGeneratorFromProtoTracksEDProducer",
    InputCollection = cms.InputTag("hltIterL3FromL1MuonPixelTracksPPOnAA"),
    InputVertexCollection = cms.InputTag("hltIterL3FromL1MuonTrimmedPixelVerticesPPOnAA"),
    SeedCreatorPSet = cms.PSet(
        refToPSet_ = cms.string('HLTSeedFromProtoTracks')
    ),
    TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
    includeFourthHit = cms.bool(False),
    originHalfLength = cms.double(0.3),
    originRadius = cms.double(0.1),
    useEventsWithNoVertex = cms.bool(True),
    usePV = cms.bool(False),
    useProtoTrackKinematics = cms.bool(False)
)


process.hltIter0IterL3FromL1MuonTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 3.40282346639e+38),
            d0err_par = cms.vdouble(0.001, 0.001, 3.40282346639e+38),
            dr_exp = cms.vint32(4, 4, 2147483647),
            dr_par1 = cms.vdouble(0.4, 0.4, 3.40282346639e+38),
            dr_par2 = cms.vdouble(0.3, 0.3, 3.40282346639e+38)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 2147483647),
            dz_par1 = cms.vdouble(0.4, 0.4, 3.40282346639e+38),
            dz_par2 = cms.vdouble(0.35, 0.35, 3.40282346639e+38)
        ),
        maxChi2 = cms.vdouble(3.40282346639e+38, 3.40282346639e+38, 3.40282346639e+38),
        maxChi2n = cms.vdouble(1.2, 1.0, 0.7),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 100.0),
        maxLostLayers = cms.vint32(1, 1, 1),
        min3DLayers = cms.vint32(0, 3, 4),
        minLayers = cms.vint32(3, 3, 4),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 3, 4)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltIterL3FromL1MuonTrimmedPixelVerticesPPOnAA")
)


process.hltIter0IterL3FromL1MuonTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltIter0IterL3FromL1MuonTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltIter0IterL3FromL1MuonTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA")
)


process.hltIter0IterL3MuonCkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('none'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTIter0IterL3MuonPSetGroupedCkfTrajectoryBuilderIT')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(True),
    maxNSeeds = cms.uint32(100000),
    maxSeedsBeforeCleaning = cms.uint32(1000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltIter0IterL3MuonPixelSeedsFromPixelTracksPPOnAA"),
    useHitsSplitting = cms.bool(True)
)


process.hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('hltIter0'),
    Fitter = cms.string('hltESPFittingSmootherIT'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClusters"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltIter0IterL3MuonCkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltIter0IterL3MuonPixelSeedsFromPixelTracksPPOnAA = cms.EDProducer("SeedGeneratorFromProtoTracksEDProducer",
    InputCollection = cms.InputTag("hltIterL3MuonPixelTracksPPOnAA"),
    InputVertexCollection = cms.InputTag("hltIterL3MuonTrimmedPixelVerticesPPOnAA"),
    SeedCreatorPSet = cms.PSet(
        refToPSet_ = cms.string('HLTSeedFromProtoTracks')
    ),
    TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
    includeFourthHit = cms.bool(False),
    originHalfLength = cms.double(0.3),
    originRadius = cms.double(0.1),
    useEventsWithNoVertex = cms.bool(True),
    usePV = cms.bool(False),
    useProtoTrackKinematics = cms.bool(False)
)


process.hltIter0IterL3MuonTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 3.40282346639e+38),
            d0err_par = cms.vdouble(0.001, 0.001, 3.40282346639e+38),
            dr_exp = cms.vint32(4, 4, 2147483647),
            dr_par1 = cms.vdouble(0.4, 0.4, 3.40282346639e+38),
            dr_par2 = cms.vdouble(0.3, 0.3, 3.40282346639e+38)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 2147483647),
            dz_par1 = cms.vdouble(0.4, 0.4, 3.40282346639e+38),
            dz_par2 = cms.vdouble(0.35, 0.35, 3.40282346639e+38)
        ),
        maxChi2 = cms.vdouble(3.40282346639e+38, 3.40282346639e+38, 3.40282346639e+38),
        maxChi2n = cms.vdouble(1.2, 1.0, 0.7),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 100.0),
        maxLostLayers = cms.vint32(1, 1, 1),
        min3DLayers = cms.vint32(0, 3, 4),
        minLayers = cms.vint32(3, 3, 4),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 3, 4)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltIterL3MuonTrimmedPixelVerticesPPOnAA")
)


process.hltIter0IterL3MuonTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltIter0IterL3MuonTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltIter0IterL3MuonTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA")
)


process.hltIter1MergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltFullIter0HighPurityTracksPPOnAA", "hltFullIter1HighPurityTracksPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltFullIter0HighPurityTracksPPOnAA", "hltFullIter1HighPurityTracksPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIter1TrackAndTauJets4Iter2PPOnAA = cms.EDProducer("TauJetSelectorForHLTTrackSeeding",
    etaMaxCaloJet = cms.double(2.7),
    etaMinCaloJet = cms.double(-2.7),
    fractionMaxChargedPUInCaloCone = cms.double(0.3),
    fractionMinCaloInTauCone = cms.double(0.7),
    inputCaloJetTag = cms.InputTag("hltAK4CaloJetsPFEt5"),
    inputTrackJetTag = cms.InputTag("hltAK4Iter1TrackJets4Iter2PPOnAA"),
    inputTrackTag = cms.InputTag("hltIter1MergedPPOnAA"),
    isolationConeSize = cms.double(0.5),
    nTrkMaxInCaloCone = cms.int32(0),
    ptMinCaloJet = cms.double(10.0),
    ptTrkMaxInCaloCone = cms.double(1.4),
    tauConeSize = cms.double(0.2)
)


process.hltIter1TrackRefsForJets4Iter2PPOnAA = cms.EDProducer("ChargedRefCandidateProducer",
    particleType = cms.string('pi+'),
    src = cms.InputTag("hltIter1MergedPPOnAA")
)


process.hltIter2IterL3FromL1MuonCkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltIter2IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3FromL1MuonPSetGroupedCkfTrajectoryBuilderIT')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(False),
    maxNSeeds = cms.uint32(100000),
    maxSeedsBeforeCleaning = cms.uint32(1000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltIter2IterL3FromL1MuonPixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(False)
)


process.hltIter2IterL3FromL1MuonClustersRefRemovalPPOnAA = cms.EDProducer("TrackClusterRemover",
    TrackQuality = cms.string('highPurity'),
    maxChi2 = cms.double(16.0),
    minNumberOfLayersWithMeasBeforeFiltering = cms.int32(0),
    oldClusterRemovalInfo = cms.InputTag(""),
    overrideTrkQuals = cms.InputTag(""),
    pixelClusters = cms.InputTag("hltSiPixelClustersPPOnAA"),
    stripClusters = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityZeroSuppression"),
    trackClassifier = cms.InputTag("","QualityMasks"),
    trajectories = cms.InputTag("hltIter0IterL3FromL1MuonTrackSelectionHighPurityPPOnAA")
)


process.hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('hltIter2'),
    Fitter = cms.string('hltESPFittingSmootherIT'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltIter2IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltIter2IterL3FromL1MuonCkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltIter2IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA = cms.EDProducer("MaskedMeasurementTrackerEventProducer",
    OnDemand = cms.bool(False),
    clustersToSkip = cms.InputTag("hltIter2IterL3FromL1MuonClustersRefRemovalPPOnAA"),
    src = cms.InputTag("hltSiStripClustersPPOnAA")
)


process.hltIter2IterL3FromL1MuonMergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIter0IterL3FromL1MuonTrackSelectionHighPurityPPOnAA", "hltIter2IterL3FromL1MuonTrackSelectionHighPurityPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIter0IterL3FromL1MuonTrackSelectionHighPurityPPOnAA", "hltIter2IterL3FromL1MuonTrackSelectionHighPurityPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIter2IterL3FromL1MuonPixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltSiStripClustersPPOnAA"),
    MaxNumberOfCosmicClusters = cms.uint32(50000),
    MaxNumberOfPixelClusters = cms.uint32(10000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(False),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltIter2IterL3FromL1MuonPixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltIter2IterL3FromL1MuonPixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0, 1),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltIter2IterL3FromL1MuonPixelLayerTripletsPPOnAA"),
    trackingRegions = cms.InputTag("hltIterL3FromL1MuonPixelTracksTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltIter2IterL3FromL1MuonPixelHitTripletsPPOnAA = cms.EDProducer("CAHitTripletEDProducer",
    CAHardPtCut = cms.double(0.3),
    CAPhiCut = cms.double(0.1),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.015),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    doublets = cms.InputTag("hltIter2IterL3FromL1MuonPixelHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.8),
        pt2 = cms.double(8.0),
        value1 = cms.double(100.0),
        value2 = cms.double(6.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltIter2IterL3FromL1MuonPixelLayerTripletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        skipClusters = cms.InputTag("hltIter2IterL3FromL1MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        skipClusters = cms.InputTag("hltIter2IterL3FromL1MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3',
        'BPix2+BPix3+BPix4',
        'BPix1+BPix3+BPix4',
        'BPix1+BPix2+BPix4',
        'BPix2+BPix3+FPix1_pos',
        'BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos',
        'BPix1+BPix2+FPix1_neg',
        'BPix2+FPix1_pos+FPix2_pos',
        'BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos',
        'BPix1+FPix1_neg+FPix2_neg',
        'FPix1_pos+FPix2_pos+FPix3_pos',
        'FPix1_neg+FPix2_neg+FPix3_neg',
        'BPix1+BPix3+FPix1_pos',
        'BPix1+BPix2+FPix2_pos',
        'BPix1+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix2_neg',
        'BPix1+FPix2_neg+FPix3_neg',
        'BPix1+FPix1_neg+FPix3_neg',
        'BPix1+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_pos+FPix3_pos'
    )
)


process.hltIter2IterL3FromL1MuonPixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsTripletOnlyEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltIter2IterL3FromL1MuonPixelHitTripletsPPOnAA")
)


process.hltIter2IterL3FromL1MuonTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 3.40282346639e+38),
            d0err_par = cms.vdouble(0.001, 0.001, 3.40282346639e+38),
            dr_exp = cms.vint32(4, 4, 2147483647),
            dr_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dr_par2 = cms.vdouble(3.40282346639e+38, 0.3, 3.40282346639e+38)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 2147483647),
            dz_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dz_par2 = cms.vdouble(3.40282346639e+38, 0.35, 3.40282346639e+38)
        ),
        maxChi2 = cms.vdouble(9999.0, 25.0, 3.40282346639e+38),
        maxChi2n = cms.vdouble(1.2, 1.0, 0.7),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 100.0),
        maxLostLayers = cms.vint32(1, 1, 1),
        min3DLayers = cms.vint32(0, 0, 0),
        minLayers = cms.vint32(3, 3, 3),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 0, 0)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltIterL3FromL1MuonTrimmedPixelVerticesPPOnAA")
)


process.hltIter2IterL3FromL1MuonTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltIter2IterL3FromL1MuonTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltIter2IterL3FromL1MuonTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA")
)


process.hltIter2IterL3MuonCkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltIter2IterL3MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3MuonPSetGroupedCkfTrajectoryBuilderIT')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(False),
    maxNSeeds = cms.uint32(100000),
    maxSeedsBeforeCleaning = cms.uint32(1000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltIter2IterL3MuonPixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(False)
)


process.hltIter2IterL3MuonClustersRefRemovalPPOnAA = cms.EDProducer("TrackClusterRemover",
    TrackQuality = cms.string('highPurity'),
    maxChi2 = cms.double(16.0),
    minNumberOfLayersWithMeasBeforeFiltering = cms.int32(0),
    oldClusterRemovalInfo = cms.InputTag(""),
    overrideTrkQuals = cms.InputTag(""),
    pixelClusters = cms.InputTag("hltSiPixelClustersPPOnAA"),
    stripClusters = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityZeroSuppression"),
    trackClassifier = cms.InputTag("","QualityMasks"),
    trajectories = cms.InputTag("hltIter0IterL3MuonTrackSelectionHighPurityPPOnAA")
)


process.hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('hltIter2'),
    Fitter = cms.string('hltESPFittingSmootherIT'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltIter2IterL3MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltIter2IterL3MuonCkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltIter2IterL3MuonMaskedMeasurementTrackerEventPPOnAA = cms.EDProducer("MaskedMeasurementTrackerEventProducer",
    OnDemand = cms.bool(False),
    clustersToSkip = cms.InputTag("hltIter2IterL3MuonClustersRefRemovalPPOnAA"),
    src = cms.InputTag("hltSiStripClustersPPOnAA")
)


process.hltIter2IterL3MuonMergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIter0IterL3MuonTrackSelectionHighPurityPPOnAA", "hltIter2IterL3MuonTrackSelectionHighPurityPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIter0IterL3MuonTrackSelectionHighPurityPPOnAA", "hltIter2IterL3MuonTrackSelectionHighPurityPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIter2IterL3MuonPixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltSiStripClustersPPOnAA"),
    MaxNumberOfCosmicClusters = cms.uint32(50000),
    MaxNumberOfPixelClusters = cms.uint32(10000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(False),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltIter2IterL3MuonPixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltIter2IterL3MuonPixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0, 1),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltIter2IterL3MuonPixelLayerTripletsPPOnAA"),
    trackingRegions = cms.InputTag("hltIterL3MuonPixelTracksTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltIter2IterL3MuonPixelHitTripletsPPOnAA = cms.EDProducer("CAHitTripletEDProducer",
    CAHardPtCut = cms.double(0.3),
    CAPhiCut = cms.double(0.1),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.015),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    doublets = cms.InputTag("hltIter2IterL3MuonPixelHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.8),
        pt2 = cms.double(8.0),
        value1 = cms.double(100.0),
        value2 = cms.double(6.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltIter2IterL3MuonPixelLayerTripletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        skipClusters = cms.InputTag("hltIter2IterL3MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        skipClusters = cms.InputTag("hltIter2IterL3MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3',
        'BPix2+BPix3+BPix4',
        'BPix1+BPix3+BPix4',
        'BPix1+BPix2+BPix4',
        'BPix2+BPix3+FPix1_pos',
        'BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos',
        'BPix1+BPix2+FPix1_neg',
        'BPix2+FPix1_pos+FPix2_pos',
        'BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos',
        'BPix1+FPix1_neg+FPix2_neg',
        'FPix1_pos+FPix2_pos+FPix3_pos',
        'FPix1_neg+FPix2_neg+FPix3_neg',
        'BPix1+BPix3+FPix1_pos',
        'BPix1+BPix2+FPix2_pos',
        'BPix1+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix2_neg',
        'BPix1+FPix2_neg+FPix3_neg',
        'BPix1+FPix1_neg+FPix3_neg',
        'BPix1+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_pos+FPix3_pos'
    )
)


process.hltIter2IterL3MuonPixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsTripletOnlyEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltIter2IterL3MuonPixelHitTripletsPPOnAA")
)


process.hltIter2IterL3MuonTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 3.40282346639e+38),
            d0err_par = cms.vdouble(0.001, 0.001, 3.40282346639e+38),
            dr_exp = cms.vint32(4, 4, 2147483647),
            dr_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dr_par2 = cms.vdouble(3.40282346639e+38, 0.3, 3.40282346639e+38)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 2147483647),
            dz_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dz_par2 = cms.vdouble(3.40282346639e+38, 0.35, 3.40282346639e+38)
        ),
        maxChi2 = cms.vdouble(9999.0, 25.0, 3.40282346639e+38),
        maxChi2n = cms.vdouble(1.2, 1.0, 0.7),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 100.0),
        maxLostLayers = cms.vint32(1, 1, 1),
        min3DLayers = cms.vint32(0, 0, 0),
        minLayers = cms.vint32(3, 3, 3),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 0, 0)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltIterL3MuonTrimmedPixelVerticesPPOnAA")
)


process.hltIter2IterL3MuonTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltIter2IterL3MuonTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltIter2IterL3MuonTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA")
)


process.hltIter2MergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIter1MergedPPOnAA", "hltFullIter2HighPurityTracksPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIter1MergedPPOnAA", "hltFullIter2HighPurityTracksPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIter3IterL3FromL1MuonCkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltIter3IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3MuonPSetGroupedCkfTrajectoryBuilderIT')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(False),
    maxNSeeds = cms.uint32(100000),
    maxSeedsBeforeCleaning = cms.uint32(1000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltIter3IterL3FromL1MuonPixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(False)
)


process.hltIter3IterL3FromL1MuonClustersRefRemovalPPOnAA = cms.EDProducer("TrackClusterRemover",
    TrackQuality = cms.string('highPurity'),
    maxChi2 = cms.double(16.0),
    minNumberOfLayersWithMeasBeforeFiltering = cms.int32(0),
    oldClusterRemovalInfo = cms.InputTag("hltIter2IterL3FromL1MuonClustersRefRemovalPPOnAA"),
    overrideTrkQuals = cms.InputTag(""),
    pixelClusters = cms.InputTag("hltSiPixelClustersPPOnAA"),
    stripClusters = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityZeroSuppression"),
    trackClassifier = cms.InputTag("","QualityMasks"),
    trajectories = cms.InputTag("hltIter2IterL3FromL1MuonTrackSelectionHighPurityPPOnAA")
)


process.hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('hltIter3'),
    Fitter = cms.string('hltESPFittingSmootherIT'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltIter3IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltIter3IterL3FromL1MuonCkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltIter3IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA = cms.EDProducer("MaskedMeasurementTrackerEventProducer",
    OnDemand = cms.bool(False),
    clustersToSkip = cms.InputTag("hltIter3IterL3FromL1MuonClustersRefRemovalPPOnAA"),
    src = cms.InputTag("hltSiStripClustersPPOnAA")
)


process.hltIter3IterL3FromL1MuonMergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIter2IterL3FromL1MuonMergedPPOnAA", "hltIter3IterL3FromL1MuonTrackSelectionHighPurityPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIter2IterL3FromL1MuonMergedPPOnAA", "hltIter3IterL3FromL1MuonTrackSelectionHighPurityPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIter3IterL3FromL1MuonPixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltSiStripClustersPPOnAA"),
    MaxNumberOfCosmicClusters = cms.uint32(50000),
    MaxNumberOfPixelClusters = cms.uint32(10000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(False),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltIter3IterL3FromL1MuonPixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltIter3IterL3FromL1MuonPixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(False),
    produceSeedingHitSets = cms.bool(True),
    seedingLayers = cms.InputTag("hltIter3IterL3FromL1MuonPixelLayerPairsPPOnAA"),
    trackingRegions = cms.InputTag("hltIter3IterL3FromL1MuonTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltIter3IterL3FromL1MuonPixelLayerPairsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        skipClusters = cms.InputTag("hltIter3IterL3FromL1MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        skipClusters = cms.InputTag("hltIter3IterL3FromL1MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2',
        'BPix1+BPix3',
        'BPix1+BPix4',
        'BPix2+BPix3',
        'BPix2+BPix4',
        'BPix3+BPix4',
        'BPix1+FPix1_pos',
        'BPix1+FPix1_neg',
        'BPix1+FPix2_pos',
        'BPix1+FPix2_neg',
        'BPix1+FPix3_pos',
        'BPix1+FPix3_neg',
        'BPix2+FPix1_pos',
        'BPix2+FPix1_neg',
        'BPix2+FPix2_pos',
        'BPix2+FPix2_neg',
        'BPix3+FPix1_pos',
        'BPix3+FPix1_neg',
        'FPix1_pos+FPix2_pos',
        'FPix1_neg+FPix2_neg',
        'FPix1_pos+FPix3_pos',
        'FPix1_neg+FPix3_neg',
        'FPix2_pos+FPix3_pos',
        'FPix2_neg+FPix3_neg'
    )
)


process.hltIter3IterL3FromL1MuonPixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltIter3IterL3FromL1MuonPixelHitDoubletsPPOnAA")
)


process.hltIter3IterL3FromL1MuonTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 3.40282346639e+38),
            d0err_par = cms.vdouble(0.001, 0.001, 3.40282346639e+38),
            dr_exp = cms.vint32(4, 4, 2147483647),
            dr_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dr_par2 = cms.vdouble(3.40282346639e+38, 0.3, 3.40282346639e+38)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 2147483647),
            dz_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dz_par2 = cms.vdouble(3.40282346639e+38, 0.35, 3.40282346639e+38)
        ),
        maxChi2 = cms.vdouble(9999.0, 25.0, 3.40282346639e+38),
        maxChi2n = cms.vdouble(1.2, 1.0, 0.7),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 100.0),
        maxLostLayers = cms.vint32(1, 1, 1),
        min3DLayers = cms.vint32(0, 0, 0),
        minLayers = cms.vint32(3, 3, 3),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 0, 0)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltIterL3FromL1MuonTrimmedPixelVerticesPPOnAA")
)


process.hltIter3IterL3FromL1MuonTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltIter3IterL3FromL1MuonTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltIter3IterL3FromL1MuonTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA")
)


process.hltIter3IterL3FromL1MuonTrackingRegionsPPOnAA = cms.EDProducer("CandidateSeededTrackingRegionsEDProducer",
    RegionPSet = cms.PSet(
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        deltaEta = cms.double(0.2),
        deltaPhi = cms.double(0.1),
        input = cms.InputTag("hltL1MuonsPt0PPOnAA"),
        maxNRegions = cms.int32(5),
        maxNVertices = cms.int32(1),
        measurementTrackerName = cms.InputTag(""),
        mode = cms.string('BeamSpotSigma'),
        nSigmaZBeamSpot = cms.double(4.0),
        nSigmaZVertex = cms.double(3.0),
        originRadius = cms.double(0.015),
        precise = cms.bool(True),
        ptMin = cms.double(1.0),
        searchOpt = cms.bool(False),
        vertexCollection = cms.InputTag("notUsed"),
        whereToUseMeasurementTracker = cms.string('Never'),
        zErrorBeamSpot = cms.double(24.2),
        zErrorVetex = cms.double(0.2)
    )
)


process.hltIter3IterL3MuonCkfTrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltIter3IterL3MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTIter2IterL3MuonPSetGroupedCkfTrajectoryBuilderIT')
    ),
    TrajectoryCleaner = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterialParabolicMf'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialParabolicMfOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(False),
    maxNSeeds = cms.uint32(100000),
    maxSeedsBeforeCleaning = cms.uint32(1000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(False),
    src = cms.InputTag("hltIter3IterL3MuonPixelSeedsPPOnAA"),
    useHitsSplitting = cms.bool(False)
)


process.hltIter3IterL3MuonClustersRefRemovalPPOnAA = cms.EDProducer("TrackClusterRemover",
    TrackQuality = cms.string('highPurity'),
    maxChi2 = cms.double(16.0),
    minNumberOfLayersWithMeasBeforeFiltering = cms.int32(0),
    oldClusterRemovalInfo = cms.InputTag("hltIter2IterL3MuonClustersRefRemovalPPOnAA"),
    overrideTrkQuals = cms.InputTag(""),
    pixelClusters = cms.InputTag("hltSiPixelClustersPPOnAA"),
    stripClusters = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityZeroSuppression"),
    trackClassifier = cms.InputTag("","QualityMasks"),
    trajectories = cms.InputTag("hltIter2IterL3MuonTrackSelectionHighPurityPPOnAA")
)


process.hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('hltIter3'),
    Fitter = cms.string('hltESPFittingSmootherIT'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string(''),
    MeasurementTrackerEvent = cms.InputTag("hltIter3IterL3MuonMaskedMeasurementTrackerEventPPOnAA"),
    NavigationSchool = cms.string(''),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltIter3IterL3MuonCkfTrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(True)
)


process.hltIter3IterL3MuonL2CandidatesPPOnAA = cms.EDProducer("ConcreteChargedCandidateProducer",
    particleType = cms.string('mu+'),
    src = cms.InputTag("hltL2SelectorForL3IOPPOnAA")
)


process.hltIter3IterL3MuonMaskedMeasurementTrackerEventPPOnAA = cms.EDProducer("MaskedMeasurementTrackerEventProducer",
    OnDemand = cms.bool(False),
    clustersToSkip = cms.InputTag("hltIter3IterL3MuonClustersRefRemovalPPOnAA"),
    src = cms.InputTag("hltSiStripClustersPPOnAA")
)


process.hltIter3IterL3MuonMergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIter2IterL3MuonMergedPPOnAA", "hltIter3IterL3MuonTrackSelectionHighPurityPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIter2IterL3MuonMergedPPOnAA", "hltIter3IterL3MuonTrackSelectionHighPurityPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIter3IterL3MuonPixelClusterCheckPPOnAA = cms.EDProducer("ClusterCheckerEDProducer",
    ClusterCollectionLabel = cms.InputTag("hltSiStripClustersPPOnAA"),
    MaxNumberOfCosmicClusters = cms.uint32(50000),
    MaxNumberOfPixelClusters = cms.uint32(10000),
    PixelClusterCollectionLabel = cms.InputTag("hltSiPixelClustersPPOnAA"),
    cut = cms.string('strip < 1000000 && pixel < 150000 && (strip < 50000 + 10*pixel) && (pixel < 5000 + strip/2.)'),
    doClusterCheck = cms.bool(False),
    silentClusterCheck = cms.untracked.bool(False)
)


process.hltIter3IterL3MuonPixelHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag("hltIter3IterL3MuonPixelClusterCheckPPOnAA"),
    layerPairs = cms.vuint32(0),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(False),
    produceSeedingHitSets = cms.bool(True),
    seedingLayers = cms.InputTag("hltIter3IterL3MuonPixelLayerPairsPPOnAA"),
    trackingRegions = cms.InputTag("hltIter3IterL3MuonTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltIter3IterL3MuonPixelLayerPairsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        skipClusters = cms.InputTag("hltIter3IterL3MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        skipClusters = cms.InputTag("hltIter3IterL3MuonClustersRefRemovalPPOnAA"),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2',
        'BPix1+BPix3',
        'BPix1+BPix4',
        'BPix2+BPix3',
        'BPix2+BPix4',
        'BPix3+BPix4',
        'BPix1+FPix1_pos',
        'BPix1+FPix1_neg',
        'BPix1+FPix2_pos',
        'BPix1+FPix2_neg',
        'BPix1+FPix3_pos',
        'BPix1+FPix3_neg',
        'BPix2+FPix1_pos',
        'BPix2+FPix1_neg',
        'BPix2+FPix2_pos',
        'BPix2+FPix2_neg',
        'BPix3+FPix1_pos',
        'BPix3+FPix1_neg',
        'FPix1_pos+FPix2_pos',
        'FPix1_neg+FPix2_neg',
        'FPix1_pos+FPix3_pos',
        'FPix1_neg+FPix3_neg',
        'FPix2_pos+FPix3_pos',
        'FPix2_neg+FPix3_neg'
    )
)


process.hltIter3IterL3MuonPixelSeedsPPOnAA = cms.EDProducer("SeedCreatorFromRegionConsecutiveHitsEDProducer",
    MinOneOverPtError = cms.double(1.0),
    OriginTransverseErrorMultiplier = cms.double(1.0),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('none')
    ),
    SeedMomentumForBOFF = cms.double(5.0),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    forceKinematicWithRegionDirection = cms.bool(False),
    magneticField = cms.string('ParabolicMf'),
    propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    seedingHitSets = cms.InputTag("hltIter3IterL3MuonPixelHitDoubletsPPOnAA")
)


process.hltIter3IterL3MuonTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(False),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 3.40282346639e+38),
            d0err_par = cms.vdouble(0.001, 0.001, 3.40282346639e+38),
            dr_exp = cms.vint32(4, 4, 2147483647),
            dr_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dr_par2 = cms.vdouble(3.40282346639e+38, 0.3, 3.40282346639e+38)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 2147483647),
            dz_par1 = cms.vdouble(3.40282346639e+38, 0.4, 3.40282346639e+38),
            dz_par2 = cms.vdouble(3.40282346639e+38, 0.35, 3.40282346639e+38)
        ),
        maxChi2 = cms.vdouble(9999.0, 25.0, 3.40282346639e+38),
        maxChi2n = cms.vdouble(1.2, 1.0, 0.7),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 100.0),
        maxLostLayers = cms.vint32(1, 1, 1),
        min3DLayers = cms.vint32(0, 0, 0),
        minLayers = cms.vint32(3, 3, 3),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 0, 0)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("hltIterL3MuonTrimmedPixelVerticesPPOnAA")
)


process.hltIter3IterL3MuonTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltIter3IterL3MuonTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltIter3IterL3MuonTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA")
)


process.hltIter3IterL3MuonTrackingRegionsPPOnAA = cms.EDProducer("CandidateSeededTrackingRegionsEDProducer",
    RegionPSet = cms.PSet(
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        deltaEta = cms.double(0.1),
        deltaPhi = cms.double(0.1),
        input = cms.InputTag("hltIter3IterL3MuonL2CandidatesPPOnAA"),
        maxNRegions = cms.int32(2),
        maxNVertices = cms.int32(1),
        measurementTrackerName = cms.InputTag(""),
        mode = cms.string('BeamSpotSigma'),
        nSigmaZBeamSpot = cms.double(4.0),
        nSigmaZVertex = cms.double(3.0),
        originRadius = cms.double(0.015),
        precise = cms.bool(True),
        ptMin = cms.double(2.0),
        searchOpt = cms.bool(False),
        vertexCollection = cms.InputTag("notUsed"),
        whereToUseMeasurementTracker = cms.string('Never'),
        zErrorBeamSpot = cms.double(24.2),
        zErrorVetex = cms.double(0.2)
    )
)


process.hltIterL3FromL1MuonPixelLayerQuadrupletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3+BPix4',
        'BPix1+BPix2+BPix3+FPix1_pos',
        'BPix1+BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos+FPix2_pos',
        'BPix1+BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_neg+FPix2_neg+FPix3_neg'
    )
)


process.hltIterL3FromL1MuonPixelTracksHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag(""),
    layerPairs = cms.vuint32(0, 1, 2),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltIterL3FromL1MuonPixelLayerQuadrupletsPPOnAA"),
    trackingRegions = cms.InputTag("hltIterL3FromL1MuonPixelTracksTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltIterL3FromL1MuonPixelTracksHitQuadrupletsPPOnAA = cms.EDProducer("CAHitQuadrupletEDProducer",
    CAHardPtCut = cms.double(0.0),
    CAPhiCut = cms.double(0.2),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.005),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('LowPtClusterShapeSeedComparitor'),
        clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCachePPOnAA"),
        clusterShapeHitFilter = cms.string('ClusterShapeHitFilter')
    ),
    doublets = cms.InputTag("hltIterL3FromL1MuonPixelTracksHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    fitFastCircle = cms.bool(True),
    fitFastCircleChi2Cut = cms.bool(True),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.7),
        pt2 = cms.double(2.0),
        value1 = cms.double(200.0),
        value2 = cms.double(50.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltIterL3FromL1MuonPixelTracksPPOnAA = cms.EDProducer("PixelTrackProducer",
    Cleaner = cms.string('hltPixelTracksCleanerBySharedHits'),
    Filter = cms.InputTag("hltIterL3MuonPixelTracksFilter"),
    Fitter = cms.InputTag("hltIterL3MuonPixelTracksFitter"),
    SeedingHitSets = cms.InputTag("hltIterL3FromL1MuonPixelTracksHitQuadrupletsPPOnAA"),
    passLabel = cms.string('')
)


process.hltIterL3FromL1MuonPixelTracksTrackingRegionsPPOnAA = cms.EDProducer("CandidateSeededTrackingRegionsEDProducer",
    RegionPSet = cms.PSet(
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        deltaEta = cms.double(0.35),
        deltaPhi = cms.double(0.2),
        input = cms.InputTag("hltL1MuonsPt0PPOnAA"),
        maxNRegions = cms.int32(5),
        maxNVertices = cms.int32(1),
        measurementTrackerName = cms.InputTag(""),
        mode = cms.string('BeamSpotSigma'),
        nSigmaZBeamSpot = cms.double(4.0),
        nSigmaZVertex = cms.double(3.0),
        originRadius = cms.double(0.2),
        precise = cms.bool(True),
        ptMin = cms.double(1.5),
        searchOpt = cms.bool(False),
        vertexCollection = cms.InputTag("notUsed"),
        whereToUseMeasurementTracker = cms.string('Never'),
        zErrorBeamSpot = cms.double(24.2),
        zErrorVetex = cms.double(0.2)
    )
)


process.hltIterL3FromL1MuonPixelVerticesPPOnAA = cms.EDProducer("PixelVertexProducer",
    Finder = cms.string('DivisiveVertexFinder'),
    Method2 = cms.bool(True),
    NTrkMin = cms.int32(2),
    PVcomparer = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPvClusterComparerForIT')
    ),
    PtMin = cms.double(1.0),
    TrackCollection = cms.InputTag("hltIterL3MuonPixelTracksPPOnAA"),
    UseError = cms.bool(True),
    Verbosity = cms.int32(0),
    WtAverage = cms.bool(True),
    ZOffset = cms.double(5.0),
    ZSeparation = cms.double(0.05),
    beamSpot = cms.InputTag("hltOnlineBeamSpot")
)


process.hltIterL3FromL1MuonTrimmedPixelVerticesPPOnAA = cms.EDProducer("PixelVertexCollectionTrimmer",
    PVcomparer = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPvClusterComparerForIT')
    ),
    fractionSumPt2 = cms.double(0.3),
    maxVtx = cms.uint32(100),
    minSumPt2 = cms.double(0.0),
    src = cms.InputTag("hltIterL3FromL1MuonPixelVerticesPPOnAA")
)


process.hltIterL3GlbMuonPPOnAA = cms.EDProducer("L3MuonProducer",
    L3TrajBuilderParameters = cms.PSet(
        GlbRefitterParameters = cms.PSet(
            CSCRecSegmentLabel = cms.InputTag("hltCscSegments"),
            Chi2CutCSC = cms.double(150.0),
            Chi2CutDT = cms.double(10.0),
            Chi2CutRPC = cms.double(1.0),
            DTRecSegmentLabel = cms.InputTag("hltDt4DSegments"),
            DYTthrs = cms.vint32(30, 15),
            DoPredictionsOnly = cms.bool(False),
            Fitter = cms.string('hltESPL3MuKFTrajectoryFitter'),
            HitThreshold = cms.int32(1),
            MuonHitsOption = cms.int32(1),
            MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
            PropDirForCosmics = cms.bool(False),
            Propagator = cms.string('hltESPSmartPropagatorAny'),
            RefitDirection = cms.string('insideOut'),
            RefitFlag = cms.bool(True),
            RefitRPCHits = cms.bool(True),
            SkipStation = cms.int32(-1),
            TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
            TrackerSkipSection = cms.int32(-1),
            TrackerSkipSystem = cms.int32(-1)
        ),
        GlobalMuonTrackMatcher = cms.PSet(
            Chi2Cut_1 = cms.double(50.0),
            Chi2Cut_2 = cms.double(50.0),
            Chi2Cut_3 = cms.double(200.0),
            DeltaDCut_1 = cms.double(40.0),
            DeltaDCut_2 = cms.double(10.0),
            DeltaDCut_3 = cms.double(15.0),
            DeltaRCut_1 = cms.double(0.1),
            DeltaRCut_2 = cms.double(0.2),
            DeltaRCut_3 = cms.double(1.0),
            Eta_threshold = cms.double(1.2),
            LocChi2Cut = cms.double(0.001),
            MinP = cms.double(2.5),
            MinPt = cms.double(1.5),
            Propagator = cms.string('hltESPSmartPropagator'),
            Pt_threshold1 = cms.double(0.0),
            Pt_threshold2 = cms.double(999999999.0),
            Quality_1 = cms.double(20.0),
            Quality_2 = cms.double(15.0),
            Quality_3 = cms.double(7.0)
        ),
        MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
        MuonTrackingRegionBuilder = cms.PSet(
            DeltaEta = cms.double(0.2),
            DeltaPhi = cms.double(0.15),
            DeltaR = cms.double(0.025),
            DeltaZ = cms.double(24.2),
            EtaR_UpperLimit_Par1 = cms.double(0.25),
            EtaR_UpperLimit_Par2 = cms.double(0.15),
            Eta_fixed = cms.bool(True),
            Eta_min = cms.double(0.1),
            MeasurementTrackerName = cms.InputTag("hltESPMeasurementTracker"),
            OnDemand = cms.int32(-1),
            PhiR_UpperLimit_Par1 = cms.double(0.6),
            PhiR_UpperLimit_Par2 = cms.double(0.2),
            Phi_fixed = cms.bool(True),
            Phi_min = cms.double(0.1),
            Pt_fixed = cms.bool(False),
            Pt_min = cms.double(1.4),
            Rescale_Dz = cms.double(4.0),
            Rescale_eta = cms.double(3.0),
            Rescale_phi = cms.double(3.0),
            UseVertex = cms.bool(False),
            Z_fixed = cms.bool(False),
            beamSpot = cms.InputTag("hltOnlineBeamSpot"),
            input = cms.InputTag("hltL2MuonsPPOnAA","UpdatedAtVtx"),
            maxRegions = cms.int32(20),
            precise = cms.bool(True),
            vertexCollection = cms.InputTag("pixelVertices")
        ),
        PCut = cms.double(2.5),
        PtCut = cms.double(1.5),
        RefitRPCHits = cms.bool(True),
        ScaleTECxFactor = cms.double(-1.0),
        ScaleTECyFactor = cms.double(-1.0),
        TrackTransformer = cms.PSet(
            DoPredictionsOnly = cms.bool(False),
            Fitter = cms.string('hltESPL3MuKFTrajectoryFitter'),
            MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
            Propagator = cms.string('hltESPSmartPropagatorAny'),
            RefitDirection = cms.string('insideOut'),
            RefitRPCHits = cms.bool(True),
            Smoother = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
            TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle')
        ),
        TrackerPropagator = cms.string('SteppingHelixPropagatorAny'),
        TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        tkTrajBeamSpot = cms.InputTag("hltOnlineBeamSpot"),
        tkTrajLabel = cms.InputTag("hltIterL3MuonAndMuonFromL1MergedPPOnAA"),
        tkTrajMaxChi2 = cms.double(9999.0),
        tkTrajMaxDXYBeamSpot = cms.double(9999.0),
        tkTrajUseVertex = cms.bool(False),
        tkTrajVertex = cms.InputTag("Notused")
    ),
    MuonCollectionLabel = cms.InputTag("hltL2MuonsPPOnAA","UpdatedAtVtx"),
    ServiceParameters = cms.PSet(
        Propagators = cms.untracked.vstring(
            'hltESPSmartPropagatorAny',
            'SteppingHelixPropagatorAny',
            'hltESPSmartPropagator',
            'hltESPSteppingHelixPropagatorOpposite'
        ),
        RPCLayers = cms.bool(True),
        UseMuonNavigation = cms.untracked.bool(True)
    ),
    TrackLoaderParameters = cms.PSet(
        DoSmoothing = cms.bool(True),
        MuonSeededTracksInstance = cms.untracked.string('L2Seeded'),
        MuonUpdatorAtVertexParameters = cms.PSet(
            BeamSpotPositionErrors = cms.vdouble(0.1, 0.1, 5.3),
            MaxChi2 = cms.double(1000000.0),
            Propagator = cms.string('hltESPSteppingHelixPropagatorOpposite')
        ),
        PutTkTrackIntoEvent = cms.untracked.bool(False),
        SmoothTkTrack = cms.untracked.bool(False),
        Smoother = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        VertexConstraint = cms.bool(False),
        beamSpot = cms.InputTag("hltOnlineBeamSpot")
    )
)


process.hltIterL3MuonAndMuonFromL1MergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIterL3MuonMergedPPOnAA", "hltIter3IterL3FromL1MuonMergedPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIterL3MuonMergedPPOnAA", "hltIter3IterL3FromL1MuonMergedPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIterL3MuonCandidatesPPOnAA = cms.EDProducer("L3MuonCandidateProducerFromMuons",
    DisplacedReconstruction = cms.bool(False),
    InputObjects = cms.InputTag("hltIterL3MuonsPPOnAA")
)


process.hltIterL3MuonMergedPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIterL3OIMuonTrackSelectionHighPurityPPOnAA", "hltIter3IterL3MuonMergedPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIterL3OIMuonTrackSelectionHighPurityPPOnAA", "hltIter3IterL3MuonMergedPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltIterL3MuonPixelLayerQuadrupletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3+BPix4',
        'BPix1+BPix2+BPix3+FPix1_pos',
        'BPix1+BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos+FPix2_pos',
        'BPix1+BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_neg+FPix2_neg+FPix3_neg'
    )
)


process.hltIterL3MuonPixelTracksFilter = cms.EDProducer("PixelTrackFilterByKinematicsProducer",
    chi2 = cms.double(1000.0),
    nSigmaInvPtTolerance = cms.double(0.0),
    nSigmaTipMaxTolerance = cms.double(0.0),
    ptMin = cms.double(0.1),
    tipMax = cms.double(1.0)
)


process.hltIterL3MuonPixelTracksFitter = cms.EDProducer("PixelFitterByHelixProjectionsProducer",
    scaleErrorsForBPix1 = cms.bool(False),
    scaleFactor = cms.double(0.65)
)


process.hltIterL3MuonPixelTracksHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag(""),
    layerPairs = cms.vuint32(0, 1, 2),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltIterL3MuonPixelLayerQuadrupletsPPOnAA"),
    trackingRegions = cms.InputTag("hltIterL3MuonPixelTracksTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltIterL3MuonPixelTracksHitQuadrupletsPPOnAA = cms.EDProducer("CAHitQuadrupletEDProducer",
    CAHardPtCut = cms.double(0.0),
    CAPhiCut = cms.double(0.2),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.005),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('LowPtClusterShapeSeedComparitor'),
        clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCachePPOnAA"),
        clusterShapeHitFilter = cms.string('ClusterShapeHitFilter')
    ),
    doublets = cms.InputTag("hltIterL3MuonPixelTracksHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    fitFastCircle = cms.bool(True),
    fitFastCircleChi2Cut = cms.bool(True),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.7),
        pt2 = cms.double(2.0),
        value1 = cms.double(200.0),
        value2 = cms.double(50.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltIterL3MuonPixelTracksPPOnAA = cms.EDProducer("PixelTrackProducer",
    Cleaner = cms.string('hltPixelTracksCleanerBySharedHits'),
    Filter = cms.InputTag("hltIterL3MuonPixelTracksFilter"),
    Fitter = cms.InputTag("hltIterL3MuonPixelTracksFitter"),
    SeedingHitSets = cms.InputTag("hltIterL3MuonPixelTracksHitQuadrupletsPPOnAA"),
    passLabel = cms.string('')
)


process.hltIterL3MuonPixelTracksTrackingRegionsPPOnAA = cms.EDProducer("MuonTrackingRegionEDProducer",
    DeltaEta = cms.double(0.2),
    DeltaPhi = cms.double(0.15),
    DeltaR = cms.double(0.025),
    DeltaZ = cms.double(24.2),
    EtaR_UpperLimit_Par1 = cms.double(0.25),
    EtaR_UpperLimit_Par2 = cms.double(0.15),
    Eta_fixed = cms.bool(True),
    Eta_min = cms.double(0.0),
    MeasurementTrackerName = cms.InputTag(""),
    OnDemand = cms.int32(-1),
    PhiR_UpperLimit_Par1 = cms.double(0.6),
    PhiR_UpperLimit_Par2 = cms.double(0.2),
    Phi_fixed = cms.bool(True),
    Phi_min = cms.double(0.0),
    Pt_fixed = cms.bool(True),
    Pt_min = cms.double(1.4),
    Rescale_Dz = cms.double(4.0),
    Rescale_eta = cms.double(3.0),
    Rescale_phi = cms.double(3.0),
    UseVertex = cms.bool(False),
    Z_fixed = cms.bool(True),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    input = cms.InputTag("hltL2SelectorForL3IOPPOnAA"),
    maxRegions = cms.int32(5),
    precise = cms.bool(True),
    vertexCollection = cms.InputTag("notUsed")
)


process.hltIterL3MuonPixelVerticesPPOnAA = cms.EDProducer("PixelVertexProducer",
    Finder = cms.string('DivisiveVertexFinder'),
    Method2 = cms.bool(True),
    NTrkMin = cms.int32(2),
    PVcomparer = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPvClusterComparerForIT')
    ),
    PtMin = cms.double(1.0),
    TrackCollection = cms.InputTag("hltIterL3MuonPixelTracksPPOnAA"),
    UseError = cms.bool(True),
    Verbosity = cms.int32(0),
    WtAverage = cms.bool(True),
    ZOffset = cms.double(5.0),
    ZSeparation = cms.double(0.05),
    beamSpot = cms.InputTag("hltOnlineBeamSpot")
)


process.hltIterL3MuonTracksPPOnAA = cms.EDProducer("HLTMuonTrackSelector",
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    copyTrajectories = cms.untracked.bool(False),
    muon = cms.InputTag("hltIterL3MuonsPPOnAA"),
    originalMVAVals = cms.InputTag("none"),
    track = cms.InputTag("hltIterL3MuonAndMuonFromL1MergedPPOnAA")
)


process.hltIterL3MuonTrimmedPixelVerticesPPOnAA = cms.EDProducer("PixelVertexCollectionTrimmer",
    PVcomparer = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPvClusterComparerForIT')
    ),
    fractionSumPt2 = cms.double(0.3),
    maxVtx = cms.uint32(100),
    minSumPt2 = cms.double(0.0),
    src = cms.InputTag("hltIterL3MuonPixelVerticesPPOnAA")
)


process.hltIterL3MuonsFromL2LinksCombinationPPOnAA = cms.EDProducer("L3TrackLinksCombiner",
    labels = cms.VInputTag("hltL3MuonsIterL3OIPPOnAA", "hltL3MuonsIterL3IOPPOnAA")
)


process.hltIterL3MuonsNoIDPPOnAA = cms.EDProducer("MuonIdProducer",
    CaloExtractorPSet = cms.PSet(
        CenterConeOnCalIntersection = cms.bool(False),
        ComponentName = cms.string('CaloExtractorByAssociator'),
        DR_Max = cms.double(1.0),
        DR_Veto_E = cms.double(0.07),
        DR_Veto_H = cms.double(0.1),
        DR_Veto_HO = cms.double(0.1),
        DepositInstanceLabels = cms.vstring(
            'ecal',
            'hcal',
            'ho'
        ),
        DepositLabel = cms.untracked.string('Cal'),
        NoiseTow_EB = cms.double(0.04),
        NoiseTow_EE = cms.double(0.15),
        Noise_EB = cms.double(0.025),
        Noise_EE = cms.double(0.1),
        Noise_HB = cms.double(0.2),
        Noise_HE = cms.double(0.2),
        Noise_HO = cms.double(0.2),
        PrintTimeReport = cms.untracked.bool(False),
        PropagatorName = cms.string('hltESPFastSteppingHelixPropagatorAny'),
        ServiceParameters = cms.PSet(
            Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
            RPCLayers = cms.bool(False),
            UseMuonNavigation = cms.untracked.bool(False)
        ),
        Threshold_E = cms.double(0.2),
        Threshold_H = cms.double(0.5),
        Threshold_HO = cms.double(0.5),
        TrackAssociatorParameters = cms.PSet(
            CSCSegmentCollectionLabel = cms.InputTag("hltCscSegments"),
            CaloTowerCollectionLabel = cms.InputTag("Notused"),
            DTRecSegment4DCollectionLabel = cms.InputTag("hltDt4DSegments"),
            EBRecHitCollectionLabel = cms.InputTag("Notused"),
            EERecHitCollectionLabel = cms.InputTag("Notused"),
            HBHERecHitCollectionLabel = cms.InputTag("Notused"),
            HORecHitCollectionLabel = cms.InputTag("Notused"),
            accountForTrajectoryChangeCalo = cms.bool(False),
            dREcal = cms.double(1.0),
            dREcalPreselection = cms.double(1.0),
            dRHcal = cms.double(1.0),
            dRHcalPreselection = cms.double(1.0),
            dRMuon = cms.double(9999.0),
            dRMuonPreselection = cms.double(0.2),
            dRPreshowerPreselection = cms.double(0.2),
            muonMaxDistanceSigmaX = cms.double(0.0),
            muonMaxDistanceSigmaY = cms.double(0.0),
            muonMaxDistanceX = cms.double(5.0),
            muonMaxDistanceY = cms.double(5.0),
            propagateAllDirections = cms.bool(True),
            trajectoryUncertaintyTolerance = cms.double(-1.0),
            truthMatch = cms.bool(False),
            useCalo = cms.bool(True),
            useEcal = cms.bool(False),
            useHO = cms.bool(False),
            useHcal = cms.bool(False),
            useMuon = cms.bool(False),
            usePreshower = cms.bool(False)
        ),
        UseRecHitsFlag = cms.bool(False)
    ),
    JetExtractorPSet = cms.PSet(
        ComponentName = cms.string('JetExtractor'),
        DR_Max = cms.double(1.0),
        DR_Veto = cms.double(0.1),
        ExcludeMuonVeto = cms.bool(True),
        JetCollectionLabel = cms.InputTag("Notused"),
        PrintTimeReport = cms.untracked.bool(False),
        PropagatorName = cms.string('hltESPFastSteppingHelixPropagatorAny'),
        ServiceParameters = cms.PSet(
            Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
            RPCLayers = cms.bool(False),
            UseMuonNavigation = cms.untracked.bool(False)
        ),
        Threshold = cms.double(5.0),
        TrackAssociatorParameters = cms.PSet(
            CSCSegmentCollectionLabel = cms.InputTag("hltCscSegments"),
            CaloTowerCollectionLabel = cms.InputTag("Notused"),
            DTRecSegment4DCollectionLabel = cms.InputTag("hltDt4DSegments"),
            EBRecHitCollectionLabel = cms.InputTag("Notused"),
            EERecHitCollectionLabel = cms.InputTag("Notused"),
            HBHERecHitCollectionLabel = cms.InputTag("Notused"),
            HORecHitCollectionLabel = cms.InputTag("Notused"),
            accountForTrajectoryChangeCalo = cms.bool(False),
            dREcal = cms.double(0.5),
            dREcalPreselection = cms.double(0.5),
            dRHcal = cms.double(0.5),
            dRHcalPreselection = cms.double(0.5),
            dRMuon = cms.double(9999.0),
            dRMuonPreselection = cms.double(0.2),
            dRPreshowerPreselection = cms.double(0.2),
            muonMaxDistanceSigmaX = cms.double(0.0),
            muonMaxDistanceSigmaY = cms.double(0.0),
            muonMaxDistanceX = cms.double(5.0),
            muonMaxDistanceY = cms.double(5.0),
            propagateAllDirections = cms.bool(True),
            trajectoryUncertaintyTolerance = cms.double(-1.0),
            truthMatch = cms.bool(False),
            useCalo = cms.bool(True),
            useEcal = cms.bool(False),
            useHO = cms.bool(False),
            useHcal = cms.bool(False),
            useMuon = cms.bool(False),
            usePreshower = cms.bool(False)
        )
    ),
    MuonCaloCompatibility = cms.PSet(
        MuonTemplateFileName = cms.FileInPath('RecoMuon/MuonIdentification/data/MuID_templates_muons_lowPt_3_1_norm.root'),
        PionTemplateFileName = cms.FileInPath('RecoMuon/MuonIdentification/data/MuID_templates_pions_lowPt_3_1_norm.root'),
        allSiPMHO = cms.bool(False),
        delta_eta = cms.double(0.02),
        delta_phi = cms.double(0.02)
    ),
    ShowerDigiFillerParameters = cms.PSet(
        cscDigiCollectionLabel = cms.InputTag("muonCSCDigis","MuonCSCStripDigi"),
        digiMaxDistanceX = cms.double(25.0),
        dtDigiCollectionLabel = cms.InputTag("muonDTDigis")
    ),
    TimingFillerParameters = cms.PSet(
        CSCTimingParameters = cms.PSet(
            CSCStripError = cms.double(7.0),
            CSCStripTimeOffset = cms.double(0.0),
            CSCTimeOffset = cms.double(0.0),
            CSCWireError = cms.double(8.6),
            CSCWireTimeOffset = cms.double(0.0),
            CSCsegments = cms.InputTag("hltCscSegments"),
            MatchParameters = cms.PSet(
                CSCsegments = cms.InputTag("hltCscSegments"),
                DTradius = cms.double(0.01),
                DTsegments = cms.InputTag("hltDt4DSegments"),
                TightMatchCSC = cms.bool(True),
                TightMatchDT = cms.bool(False)
            ),
            PruneCut = cms.double(100.0),
            ServiceParameters = cms.PSet(
                Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
                RPCLayers = cms.bool(True)
            ),
            UseStripTime = cms.bool(True),
            UseWireTime = cms.bool(True),
            debug = cms.bool(False)
        ),
        DTTimingParameters = cms.PSet(
            DTTimeOffset = cms.double(2.7),
            DTsegments = cms.InputTag("hltDt4DSegments"),
            DoWireCorr = cms.bool(False),
            DropTheta = cms.bool(True),
            HitError = cms.double(6.0),
            HitsMin = cms.int32(5),
            MatchParameters = cms.PSet(
                CSCsegments = cms.InputTag("hltCscSegments"),
                DTradius = cms.double(0.01),
                DTsegments = cms.InputTag("hltDt4DSegments"),
                TightMatchCSC = cms.bool(True),
                TightMatchDT = cms.bool(False)
            ),
            PruneCut = cms.double(10000.0),
            RequireBothProjections = cms.bool(False),
            ServiceParameters = cms.PSet(
                Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
                RPCLayers = cms.bool(True)
            ),
            UseSegmentT0 = cms.bool(False),
            debug = cms.bool(False)
        ),
        EcalEnergyCut = cms.double(0.4),
        ErrorCSC = cms.double(7.4),
        ErrorDT = cms.double(6.0),
        ErrorEB = cms.double(2.085),
        ErrorEE = cms.double(6.95),
        UseCSC = cms.bool(True),
        UseDT = cms.bool(True),
        UseECAL = cms.bool(True)
    ),
    TrackAssociatorParameters = cms.PSet(
        CSCSegmentCollectionLabel = cms.InputTag("hltCscSegments"),
        CaloTowerCollectionLabel = cms.InputTag("Notused"),
        DTRecSegment4DCollectionLabel = cms.InputTag("hltDt4DSegments"),
        EBRecHitCollectionLabel = cms.InputTag("Notused"),
        EERecHitCollectionLabel = cms.InputTag("Notused"),
        HBHERecHitCollectionLabel = cms.InputTag("Notused"),
        HORecHitCollectionLabel = cms.InputTag("Notused"),
        accountForTrajectoryChangeCalo = cms.bool(False),
        dREcal = cms.double(9999.0),
        dREcalPreselection = cms.double(0.05),
        dRHcal = cms.double(9999.0),
        dRHcalPreselection = cms.double(0.2),
        dRMuon = cms.double(9999.0),
        dRMuonPreselection = cms.double(0.2),
        dRPreshowerPreselection = cms.double(0.2),
        muonMaxDistanceSigmaX = cms.double(0.0),
        muonMaxDistanceSigmaY = cms.double(0.0),
        muonMaxDistanceX = cms.double(5.0),
        muonMaxDistanceY = cms.double(5.0),
        propagateAllDirections = cms.bool(True),
        trajectoryUncertaintyTolerance = cms.double(-1.0),
        truthMatch = cms.bool(False),
        useCalo = cms.bool(False),
        useEcal = cms.bool(False),
        useHO = cms.bool(False),
        useHcal = cms.bool(False),
        useMuon = cms.bool(True),
        usePreshower = cms.bool(False)
    ),
    TrackExtractorPSet = cms.PSet(
        BeamSpotLabel = cms.InputTag("hltOnlineBeamSpot"),
        BeamlineOption = cms.string('BeamSpotFromEvent'),
        Chi2Ndof_Max = cms.double(1e+64),
        Chi2Prob_Min = cms.double(-1.0),
        ComponentName = cms.string('TrackExtractor'),
        DR_Max = cms.double(1.0),
        DR_Veto = cms.double(0.01),
        Diff_r = cms.double(0.1),
        Diff_z = cms.double(0.2),
        NHits_Min = cms.uint32(0),
        Pt_Min = cms.double(-1.0),
        inputTrackCollection = cms.InputTag("hltIter3IterL3FromL1MuonMergedPPOnAA")
    ),
    TrackerKinkFinderParameters = cms.PSet(
        diagonalOnly = cms.bool(False),
        usePosition = cms.bool(False)
    ),
    addExtraSoftMuons = cms.bool(False),
    arbitrateTrackerMuons = cms.bool(True),
    arbitrationCleanerOptions = cms.PSet(
        ClusterDPhi = cms.double(0.6),
        ClusterDTheta = cms.double(0.02),
        Clustering = cms.bool(True),
        ME1a = cms.bool(True),
        Overlap = cms.bool(True),
        OverlapDPhi = cms.double(0.0786),
        OverlapDTheta = cms.double(0.02)
    ),
    debugWithTruthMatching = cms.bool(False),
    ecalDepositName = cms.string('ecal'),
    fillCaloCompatibility = cms.bool(False),
    fillEnergy = cms.bool(False),
    fillGlobalTrackQuality = cms.bool(False),
    fillGlobalTrackRefits = cms.bool(False),
    fillIsolation = cms.bool(False),
    fillMatching = cms.bool(True),
    fillShowerDigis = cms.bool(False),
    fillTrackerKink = cms.bool(False),
    globalTrackQualityInputTag = cms.InputTag("glbTrackQual"),
    hcalDepositName = cms.string('hcal'),
    hoDepositName = cms.string('ho'),
    inputCollectionLabels = cms.VInputTag("hltIterL3MuonAndMuonFromL1MergedPPOnAA", "hltIterL3GlbMuonPPOnAA", "hltL2MuonsPPOnAA:UpdatedAtVtx"),
    inputCollectionTypes = cms.vstring(
        'inner tracks',
        'links',
        'outer tracks'
    ),
    jetDepositName = cms.string('jets'),
    maxAbsDx = cms.double(9999.0),
    maxAbsDy = cms.double(9999.0),
    maxAbsEta = cms.double(3.0),
    maxAbsPullX = cms.double(9999.0),
    maxAbsPullY = cms.double(9999.0),
    minCaloCompatibility = cms.double(0.6),
    minNumberOfMatches = cms.int32(1),
    minP = cms.double(2.5),
    minPCaloMuon = cms.double(1000000000.0),
    minPt = cms.double(1.5),
    ptThresholdToFillCandidateP4WithGlobalFit = cms.double(200.0),
    pvInputTag = cms.InputTag("offlinePrimaryVertices"),
    runArbitrationCleaner = cms.bool(False),
    selectHighPurity = cms.bool(False),
    sigmaThresholdToFillCandidateP4WithGlobalFit = cms.double(2.0),
    storeCrossedHcalRecHits = cms.bool(False),
    trackDepositName = cms.string('tracker'),
    writeIsoDeposits = cms.bool(False)
)


process.hltIterL3MuonsPPOnAA = cms.EDProducer("MuonIDFilterProducerForHLT",
    allowedTypeMask = cms.uint32(0),
    applyTriggerIdLoose = cms.bool(True),
    inputMuonCollection = cms.InputTag("hltIterL3MuonsNoIDPPOnAA"),
    maxNormalizedChi2 = cms.double(9999.0),
    minNMuonHits = cms.int32(0),
    minNMuonStations = cms.int32(0),
    minNTrkLayers = cms.int32(0),
    minPixHits = cms.int32(0),
    minPixLayer = cms.int32(0),
    minPt = cms.double(0.0),
    minTrkHits = cms.int32(0),
    requiredTypeMask = cms.uint32(0),
    typeMuon = cms.uint32(0)
)


process.hltIterL3OIL3MuonCandidatesPPOnAA = cms.EDProducer("L3MuonCandidateProducer",
    InputLinksObjects = cms.InputTag("hltIterL3OIL3MuonsLinksCombinationPPOnAA"),
    InputObjects = cms.InputTag("hltIterL3OIL3MuonsPPOnAA"),
    MuonPtOption = cms.string('Tracker')
)


process.hltIterL3OIL3MuonsLinksCombinationPPOnAA = cms.EDProducer("L3TrackLinksCombiner",
    labels = cms.VInputTag("hltL3MuonsIterL3OIPPOnAA")
)


process.hltIterL3OIL3MuonsPPOnAA = cms.EDProducer("L3TrackCombiner",
    labels = cms.VInputTag("hltL3MuonsIterL3OIPPOnAA")
)


process.hltIterL3OIMuCtfWithMaterialTracksPPOnAA = cms.EDProducer("TrackProducer",
    AlgorithmName = cms.string('iter10'),
    Fitter = cms.string('hltESPKFFittingSmootherWithOutliersRejectionAndRK'),
    GeometricInnerState = cms.bool(True),
    MeasurementTracker = cms.string('hltESPMeasurementTracker'),
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    Propagator = cms.string('PropagatorWithMaterial'),
    SimpleMagneticField = cms.string(''),
    TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
    TrajectoryInEvent = cms.bool(False),
    alias = cms.untracked.string('ctfWithMaterialTracks'),
    beamSpot = cms.InputTag("hltOnlineBeamSpot"),
    clusterRemovalInfo = cms.InputTag(""),
    src = cms.InputTag("hltIterL3OITrackCandidatesPPOnAA"),
    useHitsSplitting = cms.bool(False),
    useSimpleMF = cms.bool(False)
)


process.hltIterL3OIMuonTrackCutClassifierPPOnAA = cms.EDProducer("TrackCutClassifier",
    beamspot = cms.InputTag("hltOnlineBeamSpot"),
    ignoreVertices = cms.bool(True),
    mva = cms.PSet(
        dr_par = cms.PSet(
            d0err = cms.vdouble(0.003, 0.003, 3.40282346639e+38),
            d0err_par = cms.vdouble(0.001, 0.001, 3.40282346639e+38),
            dr_exp = cms.vint32(4, 4, 2147483647),
            dr_par1 = cms.vdouble(0.4, 0.4, 3.40282346639e+38),
            dr_par2 = cms.vdouble(0.3, 0.3, 3.40282346639e+38)
        ),
        dz_par = cms.PSet(
            dz_exp = cms.vint32(4, 4, 2147483647),
            dz_par1 = cms.vdouble(0.4, 0.4, 3.40282346639e+38),
            dz_par2 = cms.vdouble(0.35, 0.35, 3.40282346639e+38)
        ),
        maxChi2 = cms.vdouble(3.40282346639e+38, 3.40282346639e+38, 3.40282346639e+38),
        maxChi2n = cms.vdouble(10.0, 1.0, 0.4),
        maxDr = cms.vdouble(0.5, 0.03, 3.40282346639e+38),
        maxDz = cms.vdouble(0.5, 0.2, 3.40282346639e+38),
        maxDzWrtBS = cms.vdouble(3.40282346639e+38, 24.0, 100.0),
        maxLostLayers = cms.vint32(4, 3, 2),
        min3DLayers = cms.vint32(1, 2, 1),
        minLayers = cms.vint32(3, 5, 5),
        minNVtxTrk = cms.int32(3),
        minNdof = cms.vdouble(1e-05, 1e-05, 1e-05),
        minPixelHits = cms.vint32(0, 0, 1)
    ),
    qualityCuts = cms.vdouble(-0.7, 0.1, 0.7),
    src = cms.InputTag("hltIterL3OIMuCtfWithMaterialTracksPPOnAA"),
    vertices = cms.InputTag("Notused")
)


process.hltIterL3OIMuonTrackSelectionHighPurityPPOnAA = cms.EDProducer("TrackCollectionFilterCloner",
    copyExtras = cms.untracked.bool(True),
    copyTrajectories = cms.untracked.bool(False),
    minQuality = cms.string('highPurity'),
    originalMVAVals = cms.InputTag("hltIterL3OIMuonTrackCutClassifierPPOnAA","MVAValues"),
    originalQualVals = cms.InputTag("hltIterL3OIMuonTrackCutClassifierPPOnAA","QualityMasks"),
    originalSource = cms.InputTag("hltIterL3OIMuCtfWithMaterialTracksPPOnAA")
)


process.hltIterL3OISeedsFromL2MuonsPPOnAA = cms.EDProducer("TSGForOIFromL2",
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersPPOnAA"),
    SF1 = cms.double(3.0),
    SF2 = cms.double(4.0),
    SF3 = cms.double(5.0),
    SF4 = cms.double(7.0),
    SF5 = cms.double(10.0),
    SF6 = cms.double(2.0),
    SFHd = cms.double(4.0),
    SFHld = cms.double(2.0),
    UseHitLessSeeds = cms.bool(True),
    adjustErrorsDynamicallyForHitless = cms.bool(True),
    adjustErrorsDynamicallyForHits = cms.bool(False),
    debug = cms.untracked.bool(False),
    displacedReco = cms.bool(False),
    estimator = cms.string('hltESPChi2MeasurementEstimator100'),
    eta1 = cms.double(0.2),
    eta2 = cms.double(0.3),
    eta3 = cms.double(1.0),
    eta4 = cms.double(1.2),
    eta5 = cms.double(1.6),
    eta6 = cms.double(1.4),
    eta7 = cms.double(2.1),
    fixedErrorRescaleFactorForHitless = cms.double(2.0),
    fixedErrorRescaleFactorForHits = cms.double(1.0),
    hitsToTry = cms.int32(1),
    layersToTry = cms.int32(2),
    maxEtaForTOB = cms.double(1.8),
    maxHitSeeds = cms.uint32(1),
    maxHitlessSeeds = cms.uint32(5),
    maxSeeds = cms.uint32(20),
    minEtaForTEC = cms.double(0.7),
    numL2ValidHitsCutAllEndcap = cms.uint32(30),
    numL2ValidHitsCutAllEta = cms.uint32(20),
    pT1 = cms.double(13.0),
    pT2 = cms.double(30.0),
    pT3 = cms.double(70.0),
    propagatorName = cms.string('PropagatorWithMaterialParabolicMf'),
    src = cms.InputTag("hltL2MuonsPPOnAA","UpdatedAtVtx"),
    tsosDiff1 = cms.double(0.2),
    tsosDiff2 = cms.double(0.02)
)


process.hltIterL3OITrackCandidatesPPOnAA = cms.EDProducer("CkfTrackCandidateMaker",
    MeasurementTrackerEvent = cms.InputTag("hltSiStripClustersPPOnAA"),
    NavigationSchool = cms.string('SimpleNavigationSchool'),
    RedundantSeedCleaner = cms.string('CachingSeedCleanerBySharedInput'),
    TrajectoryBuilderPSet = cms.PSet(
        refToPSet_ = cms.string('HLTPSetMuonCkfTrajectoryBuilder')
    ),
    TrajectoryCleaner = cms.string('muonSeededTrajectoryCleanerBySharedHits'),
    TransientInitialStateEstimatorParameters = cms.PSet(
        numberMeasurementsForFit = cms.int32(4),
        propagatorAlongTISE = cms.string('PropagatorWithMaterial'),
        propagatorOppositeTISE = cms.string('PropagatorWithMaterialOpposite')
    ),
    cleanTrajectoryAfterInOut = cms.bool(False),
    clustersToSkip = cms.InputTag(""),
    doSeedingRegionRebuilding = cms.bool(False),
    maxNSeeds = cms.uint32(500000),
    maxSeedsBeforeCleaning = cms.uint32(5000),
    numHitsForSeedCleaner = cms.int32(4),
    onlyPixelHitsForSeedCleaner = cms.bool(False),
    phase2clustersToSkip = cms.InputTag(""),
    reverseTrajectories = cms.bool(True),
    src = cms.InputTag("hltIterL3OISeedsFromL2MuonsPPOnAA"),
    useHitsSplitting = cms.bool(False)
)


process.hltKT4PFJetsForRho = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(5),
    DxyTrVtxMax = cms.double(0.0),
    DzTrVtxMax = cms.double(0.0),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    MaxVtxZ = cms.double(15.0),
    MinVtxNdof = cms.int32(0),
    R0 = cms.double(-1.0),
    Rho_EtaMax = cms.double(4.4),
    UseOnlyOnePV = cms.bool(False),
    UseOnlyVertexTracks = cms.bool(False),
    applyWeight = cms.bool(False),
    beta = cms.double(-1.0),
    correctShape = cms.bool(False),
    csRParam = cms.double(-1.0),
    csRho_EtaMax = cms.double(-1.0),
    dRMax = cms.double(-1.0),
    dRMin = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(True),
    doFastJetNonUniform = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    gridMaxRapidity = cms.double(-1.0),
    gridSpacing = cms.double(-1.0),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.0),
    jetAlgorithm = cms.string('Kt'),
    jetCollInstanceName = cms.string(''),
    jetPtMin = cms.double(0.0),
    jetType = cms.string('PFJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxDepth = cms.int32(-1),
    maxInputs = cms.uint32(1),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(0),
    minimumTowersFraction = cms.double(0.0),
    muCut = cms.double(-1.0),
    muMax = cms.double(-1.0),
    muMin = cms.double(-1.0),
    nExclude = cms.uint32(0),
    nFilt = cms.int32(-1),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.0),
    rFilt = cms.double(-1.0),
    rFiltFactor = cms.double(-1.0),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    rcut_factor = cms.double(-1.0),
    restrictInputs = cms.bool(False),
    src = cms.InputTag("hltParticleFlowPPOnAA"),
    srcPVs = cms.InputTag("hltPixelVerticesPPOnAA"),
    srcWeights = cms.InputTag(""),
    subjetPtMin = cms.double(-1.0),
    subtractorName = cms.string(''),
    sumRecHits = cms.bool(False),
    trimPtFracMin = cms.double(-1.0),
    useCMSBoostedTauSeedingAlgorithm = cms.bool(False),
    useConstituentSubtraction = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    useDynamicFiltering = cms.bool(False),
    useExplicitGhosts = cms.bool(False),
    useFiltering = cms.bool(False),
    useKtPruning = cms.bool(False),
    useMassDropTagger = cms.bool(False),
    usePruning = cms.bool(False),
    useSoftDrop = cms.bool(False),
    useTrimming = cms.bool(False),
    verbosity = cms.int32(0),
    voronoiRfact = cms.double(-9.0),
    writeCompound = cms.bool(False),
    writeJetsWithConst = cms.bool(False),
    yCut = cms.double(-1.0),
    yMax = cms.double(-1.0),
    yMin = cms.double(-1.0),
    zcut = cms.double(-1.0)
)


process.hltL1MuonsPt0PPOnAA = cms.EDProducer("HLTL1TMuonSelector",
    CentralBxOnly = cms.bool(True),
    InputObjects = cms.InputTag("hltGtStage2Digis","Muon"),
    L1MaxEta = cms.double(5.0),
    L1MinPt = cms.double(9999.0),
    L1MinQuality = cms.uint32(7)
)


process.hltL2MuonCandidatesPPOnAA = cms.EDProducer("L2MuonCandidateProducer",
    InputObjects = cms.InputTag("hltL2MuonsPPOnAA","UpdatedAtVtx")
)


process.hltL2MuonSeedsPPOnAA = cms.EDProducer("L2MuonSeedGeneratorFromL1T",
    CentralBxOnly = cms.bool(True),
    EtaMatchingBins = cms.vdouble(0.0, 2.5),
    GMTReadoutCollection = cms.InputTag(""),
    InputObjects = cms.InputTag("hltGtStage2Digis","Muon"),
    L1MaxEta = cms.double(2.5),
    L1MinPt = cms.double(0.0),
    L1MinQuality = cms.uint32(0),
    MatchDR = cms.vdouble(1.0),
    MatchType = cms.uint32(0),
    OfflineSeedLabel = cms.untracked.InputTag("hltL2OfflineMuonSeeds"),
    Propagator = cms.string('SteppingHelixPropagatorAny'),
    ServiceParameters = cms.PSet(
        Propagators = cms.untracked.vstring('SteppingHelixPropagatorAny'),
        RPCLayers = cms.bool(True),
        UseMuonNavigation = cms.untracked.bool(True)
    ),
    SetMinPtBarrelTo = cms.double(3.0),
    SetMinPtEndcapTo = cms.double(0.5),
    SortType = cms.uint32(0),
    UseOfflineSeed = cms.untracked.bool(True),
    UseUnassociatedL1 = cms.bool(False)
)


process.hltL2MuonsPPOnAA = cms.EDProducer("L2MuonProducer",
    DoSeedRefit = cms.bool(False),
    InputObjects = cms.InputTag("hltL2MuonSeedsPPOnAA"),
    L2TrajBuilderParameters = cms.PSet(
        BWFilterParameters = cms.PSet(
            BWSeedType = cms.string('fromGenerator'),
            CSCRecSegmentLabel = cms.InputTag("hltCscSegments"),
            DTRecSegmentLabel = cms.InputTag("hltDt4DSegments"),
            EnableCSCMeasurement = cms.bool(True),
            EnableDTMeasurement = cms.bool(True),
            EnableGEMMeasurement = cms.bool(True),
            EnableRPCMeasurement = cms.bool(True),
            FitDirection = cms.string('outsideIn'),
            GEMRecSegmentLabel = cms.InputTag("hltGemRecHits"),
            MaxChi2 = cms.double(100.0),
            MuonTrajectoryUpdatorParameters = cms.PSet(
                ExcludeRPCFromFit = cms.bool(False),
                Granularity = cms.int32(0),
                MaxChi2 = cms.double(25.0),
                RescaleError = cms.bool(False),
                RescaleErrorFactor = cms.double(100.0),
                UseInvalidHits = cms.bool(True)
            ),
            NumberOfSigma = cms.double(3.0),
            Propagator = cms.string('hltESPFastSteppingHelixPropagatorAny'),
            RPCRecSegmentLabel = cms.InputTag("hltRpcRecHits")
        ),
        DoBackwardFilter = cms.bool(True),
        DoRefit = cms.bool(False),
        DoSeedRefit = cms.bool(False),
        FilterParameters = cms.PSet(
            CSCRecSegmentLabel = cms.InputTag("hltCscSegments"),
            DTRecSegmentLabel = cms.InputTag("hltDt4DSegments"),
            EnableCSCMeasurement = cms.bool(True),
            EnableDTMeasurement = cms.bool(True),
            EnableGEMMeasurement = cms.bool(True),
            EnableRPCMeasurement = cms.bool(True),
            FitDirection = cms.string('insideOut'),
            GEMRecSegmentLabel = cms.InputTag("hltGemRecHits"),
            MaxChi2 = cms.double(1000.0),
            MuonTrajectoryUpdatorParameters = cms.PSet(
                ExcludeRPCFromFit = cms.bool(False),
                Granularity = cms.int32(0),
                MaxChi2 = cms.double(25.0),
                RescaleError = cms.bool(False),
                RescaleErrorFactor = cms.double(100.0),
                UseInvalidHits = cms.bool(True)
            ),
            NumberOfSigma = cms.double(3.0),
            Propagator = cms.string('hltESPFastSteppingHelixPropagatorAny'),
            RPCRecSegmentLabel = cms.InputTag("hltRpcRecHits")
        ),
        NavigationType = cms.string('Standard'),
        SeedPosition = cms.string('in'),
        SeedPropagator = cms.string('hltESPFastSteppingHelixPropagatorAny'),
        SeedTransformerParameters = cms.PSet(
            Fitter = cms.string('hltESPKFFittingSmootherForL2Muon'),
            MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
            NMinRecHits = cms.uint32(2),
            Propagator = cms.string('hltESPFastSteppingHelixPropagatorAny'),
            RescaleError = cms.double(100.0),
            UseSubRecHits = cms.bool(False)
        )
    ),
    MuonTrajectoryBuilder = cms.string('Exhaustive'),
    SeedTransformerParameters = cms.PSet(
        Fitter = cms.string('hltESPKFFittingSmootherForL2Muon'),
        MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
        NMinRecHits = cms.uint32(2),
        Propagator = cms.string('hltESPFastSteppingHelixPropagatorAny'),
        RescaleError = cms.double(100.0),
        UseSubRecHits = cms.bool(False)
    ),
    ServiceParameters = cms.PSet(
        Propagators = cms.untracked.vstring(
            'hltESPFastSteppingHelixPropagatorAny',
            'hltESPFastSteppingHelixPropagatorOpposite'
        ),
        RPCLayers = cms.bool(True),
        UseMuonNavigation = cms.untracked.bool(True)
    ),
    TrackLoaderParameters = cms.PSet(
        DoSmoothing = cms.bool(False),
        MuonUpdatorAtVertexParameters = cms.PSet(
            BeamSpotPosition = cms.vdouble(0.0, 0.0, 0.0),
            BeamSpotPositionErrors = cms.vdouble(0.1, 0.1, 5.3),
            MaxChi2 = cms.double(1000000.0),
            Propagator = cms.string('hltESPFastSteppingHelixPropagatorOpposite')
        ),
        Smoother = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        VertexConstraint = cms.bool(True),
        beamSpot = cms.InputTag("hltOnlineBeamSpot")
    )
)


process.hltL2OfflineMuonSeeds = cms.EDProducer("MuonSeedGenerator",
    CSCRecSegmentLabel = cms.InputTag("hltCscSegments"),
    CSC_01 = cms.vdouble(
        0.166, 0.0, 0.0, 0.031, 0.0,
        0.0
    ),
    CSC_01_1_scale = cms.vdouble(-1.915329, 0.0),
    CSC_02 = cms.vdouble(
        0.612, -0.207, 0.0, 0.067, -0.001,
        0.0
    ),
    CSC_03 = cms.vdouble(
        0.787, -0.338, 0.029, 0.101, -0.008,
        0.0
    ),
    CSC_12 = cms.vdouble(
        -0.161, 0.254, -0.047, 0.042, -0.007,
        0.0
    ),
    CSC_12_1_scale = cms.vdouble(-6.434242, 0.0),
    CSC_12_2_scale = cms.vdouble(-1.63622, 0.0),
    CSC_12_3_scale = cms.vdouble(-1.63622, 0.0),
    CSC_13 = cms.vdouble(
        0.901, -1.302, 0.533, 0.045, 0.005,
        0.0
    ),
    CSC_13_2_scale = cms.vdouble(-6.077936, 0.0),
    CSC_13_3_scale = cms.vdouble(-1.701268, 0.0),
    CSC_14 = cms.vdouble(
        0.606, -0.181, -0.002, 0.111, -0.003,
        0.0
    ),
    CSC_14_3_scale = cms.vdouble(-1.969563, 0.0),
    CSC_23 = cms.vdouble(
        -0.081, 0.113, -0.029, 0.015, 0.008,
        0.0
    ),
    CSC_23_1_scale = cms.vdouble(-19.084285, 0.0),
    CSC_23_2_scale = cms.vdouble(-6.079917, 0.0),
    CSC_24 = cms.vdouble(
        0.004, 0.021, -0.002, 0.053, 0.0,
        0.0
    ),
    CSC_24_1_scale = cms.vdouble(-6.055701, 0.0),
    CSC_34 = cms.vdouble(
        0.062, -0.067, 0.019, 0.021, 0.003,
        0.0
    ),
    CSC_34_1_scale = cms.vdouble(-11.520507, 0.0),
    DTRecSegmentLabel = cms.InputTag("hltDt4DSegments"),
    DT_12 = cms.vdouble(
        0.183, 0.054, -0.087, 0.028, 0.002,
        0.0
    ),
    DT_12_1_scale = cms.vdouble(-3.692398, 0.0),
    DT_12_2_scale = cms.vdouble(-3.518165, 0.0),
    DT_13 = cms.vdouble(
        0.315, 0.068, -0.127, 0.051, -0.002,
        0.0
    ),
    DT_13_1_scale = cms.vdouble(-4.520923, 0.0),
    DT_13_2_scale = cms.vdouble(-4.257687, 0.0),
    DT_14 = cms.vdouble(
        0.359, 0.052, -0.107, 0.072, -0.004,
        0.0
    ),
    DT_14_1_scale = cms.vdouble(-5.644816, 0.0),
    DT_14_2_scale = cms.vdouble(-4.808546, 0.0),
    DT_23 = cms.vdouble(
        0.13, 0.023, -0.057, 0.028, 0.004,
        0.0
    ),
    DT_23_1_scale = cms.vdouble(-5.320346, 0.0),
    DT_23_2_scale = cms.vdouble(-5.117625, 0.0),
    DT_24 = cms.vdouble(
        0.176, 0.014, -0.051, 0.051, 0.003,
        0.0
    ),
    DT_24_1_scale = cms.vdouble(-7.490909, 0.0),
    DT_24_2_scale = cms.vdouble(-6.63094, 0.0),
    DT_34 = cms.vdouble(
        0.044, 0.004, -0.013, 0.029, 0.003,
        0.0
    ),
    DT_34_1_scale = cms.vdouble(-13.783765, 0.0),
    DT_34_2_scale = cms.vdouble(-11.901897, 0.0),
    EnableCSCMeasurement = cms.bool(True),
    EnableDTMeasurement = cms.bool(True),
    EnableME0Measurement = cms.bool(False),
    ME0RecSegmentLabel = cms.InputTag("me0Segments"),
    OL_1213 = cms.vdouble(
        0.96, -0.737, 0.0, 0.052, 0.0,
        0.0
    ),
    OL_1213_0_scale = cms.vdouble(-4.488158, 0.0),
    OL_1222 = cms.vdouble(
        0.848, -0.591, 0.0, 0.062, 0.0,
        0.0
    ),
    OL_1222_0_scale = cms.vdouble(-5.810449, 0.0),
    OL_1232 = cms.vdouble(
        0.184, 0.0, 0.0, 0.066, 0.0,
        0.0
    ),
    OL_1232_0_scale = cms.vdouble(-5.964634, 0.0),
    OL_2213 = cms.vdouble(
        0.117, 0.0, 0.0, 0.044, 0.0,
        0.0
    ),
    OL_2213_0_scale = cms.vdouble(-7.239789, 0.0),
    OL_2222 = cms.vdouble(
        0.107, 0.0, 0.0, 0.04, 0.0,
        0.0
    ),
    OL_2222_0_scale = cms.vdouble(-7.667231, 0.0),
    SMB_10 = cms.vdouble(
        1.387, -0.038, 0.0, 0.19, 0.0,
        0.0
    ),
    SMB_10_0_scale = cms.vdouble(2.448566, 0.0),
    SMB_11 = cms.vdouble(
        1.247, 0.72, -0.802, 0.229, -0.075,
        0.0
    ),
    SMB_11_0_scale = cms.vdouble(2.56363, 0.0),
    SMB_12 = cms.vdouble(
        2.128, -0.956, 0.0, 0.199, 0.0,
        0.0
    ),
    SMB_12_0_scale = cms.vdouble(2.283221, 0.0),
    SMB_20 = cms.vdouble(
        1.011, -0.052, 0.0, 0.188, 0.0,
        0.0
    ),
    SMB_20_0_scale = cms.vdouble(1.486168, 0.0),
    SMB_21 = cms.vdouble(
        1.043, -0.124, 0.0, 0.183, 0.0,
        0.0
    ),
    SMB_21_0_scale = cms.vdouble(1.58384, 0.0),
    SMB_22 = cms.vdouble(
        1.474, -0.758, 0.0, 0.185, 0.0,
        0.0
    ),
    SMB_22_0_scale = cms.vdouble(1.346681, 0.0),
    SMB_30 = cms.vdouble(
        0.505, -0.022, 0.0, 0.215, 0.0,
        0.0
    ),
    SMB_30_0_scale = cms.vdouble(-3.629838, 0.0),
    SMB_31 = cms.vdouble(
        0.549, -0.145, 0.0, 0.207, 0.0,
        0.0
    ),
    SMB_31_0_scale = cms.vdouble(-3.323768, 0.0),
    SMB_32 = cms.vdouble(
        0.67, -0.327, 0.0, 0.22, 0.0,
        0.0
    ),
    SMB_32_0_scale = cms.vdouble(-3.054156, 0.0),
    SME_11 = cms.vdouble(
        3.295, -1.527, 0.112, 0.378, 0.02,
        0.0
    ),
    SME_11_0_scale = cms.vdouble(1.325085, 0.0),
    SME_12 = cms.vdouble(
        0.102, 0.599, 0.0, 0.38, 0.0,
        0.0
    ),
    SME_12_0_scale = cms.vdouble(2.279181, 0.0),
    SME_13 = cms.vdouble(
        -1.286, 1.711, 0.0, 0.356, 0.0,
        0.0
    ),
    SME_13_0_scale = cms.vdouble(0.104905, 0.0),
    SME_21 = cms.vdouble(
        -0.529, 1.194, -0.358, 0.472, 0.086,
        0.0
    ),
    SME_21_0_scale = cms.vdouble(-0.040862, 0.0),
    SME_22 = cms.vdouble(
        -1.207, 1.491, -0.251, 0.189, 0.243,
        0.0
    ),
    SME_22_0_scale = cms.vdouble(-3.457901, 0.0),
    SME_31 = cms.vdouble(
        -1.594, 1.482, -0.317, 0.487, 0.097,
        0.0
    ),
    SME_32 = cms.vdouble(
        -0.901, 1.333, -0.47, 0.41, 0.073,
        0.0
    ),
    SME_41 = cms.vdouble(
        -0.003, 0.005, 0.005, 0.608, 0.076,
        0.0
    ),
    SME_42 = cms.vdouble(
        -0.003, 0.005, 0.005, 0.608, 0.076,
        0.0
    ),
    beamSpotTag = cms.InputTag("hltOnlineBeamSpot"),
    crackEtas = cms.vdouble(0.2, 1.6, 1.7),
    crackWindow = cms.double(0.04),
    deltaEtaCrackSearchWindow = cms.double(0.25),
    deltaEtaSearchWindow = cms.double(0.2),
    deltaPhiSearchWindow = cms.double(0.25),
    scaleDT = cms.bool(True)
)


process.hltL2SelectorForL3IOPPOnAA = cms.EDProducer("HLTMuonL2SelectorForL3IO",
    InputLinks = cms.InputTag("hltIterL3OIL3MuonsLinksCombinationPPOnAA"),
    MaxNormalizedChi2 = cms.double(200.0),
    MaxPtDifference = cms.double(0.3),
    MinNhits = cms.int32(1),
    MinNmuonHits = cms.int32(1),
    applyL3Filters = cms.bool(False),
    l2Src = cms.InputTag("hltL2MuonsPPOnAA","UpdatedAtVtx"),
    l3OISrc = cms.InputTag("hltIterL3OIL3MuonCandidatesPPOnAA")
)


process.hltL3MuonsIterL3IOPPOnAA = cms.EDProducer("L3MuonProducer",
    L3TrajBuilderParameters = cms.PSet(
        GlbRefitterParameters = cms.PSet(
            CSCRecSegmentLabel = cms.InputTag("hltCscSegments"),
            Chi2CutCSC = cms.double(150.0),
            Chi2CutDT = cms.double(10.0),
            Chi2CutRPC = cms.double(1.0),
            DTRecSegmentLabel = cms.InputTag("hltDt4DSegments"),
            DYTthrs = cms.vint32(30, 15),
            DoPredictionsOnly = cms.bool(False),
            Fitter = cms.string('hltESPL3MuKFTrajectoryFitter'),
            HitThreshold = cms.int32(1),
            MuonHitsOption = cms.int32(1),
            MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
            PropDirForCosmics = cms.bool(False),
            Propagator = cms.string('hltESPSmartPropagatorAny'),
            RefitDirection = cms.string('insideOut'),
            RefitFlag = cms.bool(True),
            RefitRPCHits = cms.bool(True),
            SkipStation = cms.int32(-1),
            TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
            TrackerSkipSection = cms.int32(-1),
            TrackerSkipSystem = cms.int32(-1)
        ),
        GlobalMuonTrackMatcher = cms.PSet(
            Chi2Cut_1 = cms.double(50.0),
            Chi2Cut_2 = cms.double(50.0),
            Chi2Cut_3 = cms.double(200.0),
            DeltaDCut_1 = cms.double(40.0),
            DeltaDCut_2 = cms.double(10.0),
            DeltaDCut_3 = cms.double(15.0),
            DeltaRCut_1 = cms.double(0.1),
            DeltaRCut_2 = cms.double(0.2),
            DeltaRCut_3 = cms.double(1.0),
            Eta_threshold = cms.double(1.2),
            LocChi2Cut = cms.double(0.001),
            MinP = cms.double(2.5),
            MinPt = cms.double(0.5),
            Propagator = cms.string('hltESPSmartPropagator'),
            Pt_threshold1 = cms.double(0.0),
            Pt_threshold2 = cms.double(999999999.0),
            Quality_1 = cms.double(20.0),
            Quality_2 = cms.double(15.0),
            Quality_3 = cms.double(7.0)
        ),
        MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
        MuonTrackingRegionBuilder = cms.PSet(
            DeltaEta = cms.double(0.04),
            DeltaPhi = cms.double(0.15),
            DeltaR = cms.double(0.025),
            DeltaZ = cms.double(24.2),
            EtaR_UpperLimit_Par1 = cms.double(0.25),
            EtaR_UpperLimit_Par2 = cms.double(0.15),
            Eta_fixed = cms.bool(True),
            Eta_min = cms.double(0.1),
            MeasurementTrackerName = cms.InputTag("hltESPMeasurementTracker"),
            OnDemand = cms.int32(-1),
            PhiR_UpperLimit_Par1 = cms.double(0.6),
            PhiR_UpperLimit_Par2 = cms.double(0.2),
            Phi_fixed = cms.bool(True),
            Phi_min = cms.double(0.1),
            Pt_fixed = cms.bool(True),
            Pt_min = cms.double(0.1),
            Rescale_Dz = cms.double(4.0),
            Rescale_eta = cms.double(3.0),
            Rescale_phi = cms.double(3.0),
            UseVertex = cms.bool(False),
            Z_fixed = cms.bool(True),
            beamSpot = cms.InputTag("hltOnlineBeamSpot"),
            input = cms.InputTag("hltL2SelectorForL3IOPPOnAA"),
            maxRegions = cms.int32(2),
            precise = cms.bool(True),
            vertexCollection = cms.InputTag("pixelVertices")
        ),
        PCut = cms.double(2.5),
        PtCut = cms.double(0.5),
        RefitRPCHits = cms.bool(True),
        ScaleTECxFactor = cms.double(-1.0),
        ScaleTECyFactor = cms.double(-1.0),
        TrackTransformer = cms.PSet(
            DoPredictionsOnly = cms.bool(False),
            Fitter = cms.string('hltESPL3MuKFTrajectoryFitter'),
            MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
            Propagator = cms.string('hltESPSmartPropagatorAny'),
            RefitDirection = cms.string('insideOut'),
            RefitRPCHits = cms.bool(True),
            Smoother = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
            TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle')
        ),
        TrackerPropagator = cms.string('SteppingHelixPropagatorAny'),
        TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        matchToSeeds = cms.bool(True),
        tkTrajBeamSpot = cms.InputTag("hltOnlineBeamSpot"),
        tkTrajLabel = cms.InputTag("hltIter3IterL3MuonMergedPPOnAA"),
        tkTrajMaxChi2 = cms.double(9999.0),
        tkTrajMaxDXYBeamSpot = cms.double(9999.0),
        tkTrajUseVertex = cms.bool(False),
        tkTrajVertex = cms.InputTag("hltIterL3MuonPixelVerticesPPOnAA")
    ),
    MuonCollectionLabel = cms.InputTag("hltL2MuonsPPOnAA","UpdatedAtVtx"),
    ServiceParameters = cms.PSet(
        Propagators = cms.untracked.vstring(
            'hltESPSmartPropagatorAny',
            'SteppingHelixPropagatorAny',
            'hltESPSmartPropagator',
            'hltESPSteppingHelixPropagatorOpposite'
        ),
        RPCLayers = cms.bool(True),
        UseMuonNavigation = cms.untracked.bool(True)
    ),
    TrackLoaderParameters = cms.PSet(
        DoSmoothing = cms.bool(False),
        MuonSeededTracksInstance = cms.untracked.string('L2Seeded'),
        MuonUpdatorAtVertexParameters = cms.PSet(
            BeamSpotPositionErrors = cms.vdouble(0.1, 0.1, 5.3),
            MaxChi2 = cms.double(1000000.0),
            Propagator = cms.string('hltESPSteppingHelixPropagatorOpposite')
        ),
        PutTkTrackIntoEvent = cms.untracked.bool(False),
        SmoothTkTrack = cms.untracked.bool(False),
        Smoother = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
        VertexConstraint = cms.bool(False),
        beamSpot = cms.InputTag("hltOnlineBeamSpot")
    )
)


process.hltL3MuonsIterL3LinksPPOnAA = cms.EDProducer("MuonLinksProducer",
    inputCollection = cms.InputTag("hltIterL3MuonsPPOnAA")
)


process.hltL3MuonsIterL3OIPPOnAA = cms.EDProducer("L3MuonProducer",
    L3TrajBuilderParameters = cms.PSet(
        GlbRefitterParameters = cms.PSet(
            CSCRecSegmentLabel = cms.InputTag("hltCscSegments"),
            Chi2CutCSC = cms.double(150.0),
            Chi2CutDT = cms.double(10.0),
            Chi2CutRPC = cms.double(1.0),
            DTRecSegmentLabel = cms.InputTag("hltDt4DSegments"),
            DYTthrs = cms.vint32(30, 15),
            DoPredictionsOnly = cms.bool(False),
            Fitter = cms.string('hltESPL3MuKFTrajectoryFitter'),
            HitThreshold = cms.int32(1),
            MuonHitsOption = cms.int32(1),
            MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
            PropDirForCosmics = cms.bool(False),
            Propagator = cms.string('hltESPSmartPropagatorAny'),
            RefitDirection = cms.string('insideOut'),
            RefitFlag = cms.bool(True),
            RefitRPCHits = cms.bool(True),
            SkipStation = cms.int32(-1),
            TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
            TrackerSkipSection = cms.int32(-1),
            TrackerSkipSystem = cms.int32(-1)
        ),
        GlobalMuonTrackMatcher = cms.PSet(
            Chi2Cut_1 = cms.double(50.0),
            Chi2Cut_2 = cms.double(50.0),
            Chi2Cut_3 = cms.double(200.0),
            DeltaDCut_1 = cms.double(40.0),
            DeltaDCut_2 = cms.double(10.0),
            DeltaDCut_3 = cms.double(15.0),
            DeltaRCut_1 = cms.double(0.1),
            DeltaRCut_2 = cms.double(0.2),
            DeltaRCut_3 = cms.double(1.0),
            Eta_threshold = cms.double(1.2),
            LocChi2Cut = cms.double(0.001),
            MinP = cms.double(2.5),
            MinPt = cms.double(0.5),
            Propagator = cms.string('hltESPSmartPropagator'),
            Pt_threshold1 = cms.double(0.0),
            Pt_threshold2 = cms.double(999999999.0),
            Quality_1 = cms.double(20.0),
            Quality_2 = cms.double(15.0),
            Quality_3 = cms.double(7.0)
        ),
        MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
        MuonTrackingRegionBuilder = cms.PSet(
            DeltaEta = cms.double(0.2),
            DeltaPhi = cms.double(0.15),
            DeltaR = cms.double(0.025),
            DeltaZ = cms.double(24.2),
            EtaR_UpperLimit_Par1 = cms.double(0.25),
            EtaR_UpperLimit_Par2 = cms.double(0.15),
            Eta_fixed = cms.bool(True),
            Eta_min = cms.double(0.1),
            MeasurementTrackerName = cms.InputTag("hltESPMeasurementTracker"),
            OnDemand = cms.int32(-1),
            PhiR_UpperLimit_Par1 = cms.double(0.6),
            PhiR_UpperLimit_Par2 = cms.double(0.2),
            Phi_fixed = cms.bool(True),
            Phi_min = cms.double(0.1),
            Pt_fixed = cms.bool(False),
            Pt_min = cms.double(0.1),
            Rescale_Dz = cms.double(4.0),
            Rescale_eta = cms.double(3.0),
            Rescale_phi = cms.double(3.0),
            UseVertex = cms.bool(False),
            Z_fixed = cms.bool(False),
            beamSpot = cms.InputTag("hltOnlineBeamSpot"),
            input = cms.InputTag("hltL2Muons","UpdatedAtVtx"),
            maxRegions = cms.int32(2),
            precise = cms.bool(True),
            vertexCollection = cms.InputTag("pixelVertices")
        ),
        PCut = cms.double(2.5),
        PtCut = cms.double(0.5),
        RefitRPCHits = cms.bool(True),
        ScaleTECxFactor = cms.double(-1.0),
        ScaleTECyFactor = cms.double(-1.0),
        TrackTransformer = cms.PSet(
            DoPredictionsOnly = cms.bool(False),
            Fitter = cms.string('hltESPL3MuKFTrajectoryFitter'),
            MuonRecHitBuilder = cms.string('hltESPMuonTransientTrackingRecHitBuilder'),
            Propagator = cms.string('hltESPSmartPropagatorAny'),
            RefitDirection = cms.string('insideOut'),
            RefitRPCHits = cms.bool(True),
            Smoother = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
            TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle')
        ),
        TrackerPropagator = cms.string('SteppingHelixPropagatorAny'),
        TrackerRecHitBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        tkTrajBeamSpot = cms.InputTag("hltOnlineBeamSpot"),
        tkTrajLabel = cms.InputTag("hltIterL3OIMuonTrackSelectionHighPurityPPOnAA"),
        tkTrajMaxChi2 = cms.double(9999.0),
        tkTrajMaxDXYBeamSpot = cms.double(9999.0),
        tkTrajUseVertex = cms.bool(False),
        tkTrajVertex = cms.InputTag("Notused")
    ),
    MuonCollectionLabel = cms.InputTag("hltL2MuonsPPOnAA","UpdatedAtVtx"),
    ServiceParameters = cms.PSet(
        Propagators = cms.untracked.vstring(
            'hltESPSmartPropagatorAny',
            'SteppingHelixPropagatorAny',
            'hltESPSmartPropagator',
            'hltESPSteppingHelixPropagatorOpposite'
        ),
        RPCLayers = cms.bool(True),
        UseMuonNavigation = cms.untracked.bool(True)
    ),
    TrackLoaderParameters = cms.PSet(
        DoSmoothing = cms.bool(True),
        MuonSeededTracksInstance = cms.untracked.string('L2Seeded'),
        MuonUpdatorAtVertexParameters = cms.PSet(
            BeamSpotPositionErrors = cms.vdouble(0.1, 0.1, 5.3),
            MaxChi2 = cms.double(1000000.0),
            Propagator = cms.string('hltESPSteppingHelixPropagatorOpposite')
        ),
        PutTkTrackIntoEvent = cms.untracked.bool(False),
        SmoothTkTrack = cms.untracked.bool(False),
        Smoother = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
        TTRHBuilder = cms.string('hltESPTTRHBWithTrackAngle'),
        VertexConstraint = cms.bool(False),
        beamSpot = cms.InputTag("hltOnlineBeamSpot")
    )
)


process.hltLightPFTracksPPOnAA = cms.EDProducer("LightPFTrackProducer",
    TkColList = cms.VInputTag("hltPFMuonMergingPPOnAA"),
    TrackQuality = cms.string('none'),
    UseQuality = cms.bool(False)
)


process.hltMergedTracksPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIter2MergedPPOnAA", "hltDoubletRecoveryPFlowTrackSelectionHighPurityPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIter2MergedPPOnAA", "hltDoubletRecoveryPFlowTrackSelectionHighPurityPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltMuonCSCDigis = cms.EDProducer("CSCDCCUnpacker",
    B904Setup = cms.untracked.bool(False),
    Debug = cms.untracked.bool(False),
    DisableMappingCheck = cms.untracked.bool(False),
    ErrorMask = cms.uint32(0),
    ExaminerMask = cms.uint32(535558134),
    FormatedEventDump = cms.untracked.bool(False),
    InputObjects = cms.InputTag("rawDataCollector"),
    PrintEventNumber = cms.untracked.bool(False),
    SuppressZeroLCT = cms.untracked.bool(True),
    UnpackStatusDigis = cms.bool(False),
    UseExaminer = cms.bool(True),
    UseFormatStatus = cms.bool(True),
    UseSelectiveUnpacking = cms.bool(True),
    VisualFEDInspect = cms.untracked.bool(False),
    VisualFEDShort = cms.untracked.bool(False),
    runDQM = cms.untracked.bool(False),
    useCSCShowers = cms.bool(False),
    useGEMs = cms.bool(False),
    useRPCs = cms.bool(False)
)


process.hltMuonDTDigis = cms.EDProducer("DTuROSRawToDigi",
    debug = cms.untracked.bool(False),
    inputLabel = cms.InputTag("rawDataCollector")
)


process.hltMuonGEMDigis = cms.EDProducer("GEMRawToDigiModule",
    InputLabel = cms.InputTag("rawDataCollector"),
    fedIdEnd = cms.uint32(1478),
    fedIdStart = cms.uint32(1467),
    ge21Off = cms.bool(True),
    keepDAQStatus = cms.bool(False),
    readMultiBX = cms.bool(False),
    useDBEMap = cms.bool(True)
)


process.hltMuonLinksPPOnAA = cms.EDProducer("MuonLinksProducerForHLT",
    InclusiveTrackerTrackCollection = cms.InputTag("hltPFMuonMergingPPOnAA"),
    LinkCollection = cms.InputTag("hltL3MuonsIterL3LinksPPOnAA"),
    pMin = cms.double(2.5),
    ptMin = cms.double(2.5),
    shareHitFraction = cms.double(0.8)
)


process.hltMuonRPCDigis = cms.EDProducer("RPCUnpackingModule",
    InputLabel = cms.InputTag("rawDataCollector"),
    doSynchro = cms.bool(False)
)


process.hltMuonsPPOnAA = cms.EDProducer("MuonIdProducer",
    CaloExtractorPSet = cms.PSet(
        CenterConeOnCalIntersection = cms.bool(False),
        ComponentName = cms.string('CaloExtractorByAssociator'),
        DR_Max = cms.double(1.0),
        DR_Veto_E = cms.double(0.07),
        DR_Veto_H = cms.double(0.1),
        DR_Veto_HO = cms.double(0.1),
        DepositInstanceLabels = cms.vstring(
            'ecal',
            'hcal',
            'ho'
        ),
        DepositLabel = cms.untracked.string('Cal'),
        NoiseTow_EB = cms.double(0.04),
        NoiseTow_EE = cms.double(0.15),
        Noise_EB = cms.double(0.025),
        Noise_EE = cms.double(0.1),
        Noise_HB = cms.double(0.2),
        Noise_HE = cms.double(0.2),
        Noise_HO = cms.double(0.2),
        PrintTimeReport = cms.untracked.bool(False),
        PropagatorName = cms.string('hltESPFastSteppingHelixPropagatorAny'),
        ServiceParameters = cms.PSet(
            Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
            RPCLayers = cms.bool(False),
            UseMuonNavigation = cms.untracked.bool(False)
        ),
        Threshold_E = cms.double(0.2),
        Threshold_H = cms.double(0.5),
        Threshold_HO = cms.double(0.5),
        TrackAssociatorParameters = cms.PSet(
            CSCSegmentCollectionLabel = cms.InputTag("hltCscSegments"),
            CaloTowerCollectionLabel = cms.InputTag("hltTowerMakerForAll"),
            DTRecSegment4DCollectionLabel = cms.InputTag("hltDt4DSegments"),
            EBRecHitCollectionLabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEB"),
            EERecHitCollectionLabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEE"),
            HBHERecHitCollectionLabel = cms.InputTag("hltHbhereco"),
            HORecHitCollectionLabel = cms.InputTag("hltHoreco"),
            accountForTrajectoryChangeCalo = cms.bool(False),
            dREcal = cms.double(1.0),
            dREcalPreselection = cms.double(1.0),
            dRHcal = cms.double(1.0),
            dRHcalPreselection = cms.double(1.0),
            dRMuon = cms.double(9999.0),
            dRMuonPreselection = cms.double(0.2),
            dRPreshowerPreselection = cms.double(0.2),
            muonMaxDistanceSigmaX = cms.double(0.0),
            muonMaxDistanceSigmaY = cms.double(0.0),
            muonMaxDistanceX = cms.double(5.0),
            muonMaxDistanceY = cms.double(5.0),
            propagateAllDirections = cms.bool(True),
            trajectoryUncertaintyTolerance = cms.double(-1.0),
            truthMatch = cms.bool(False),
            useCalo = cms.bool(True),
            useEcal = cms.bool(False),
            useHO = cms.bool(False),
            useHcal = cms.bool(False),
            useMuon = cms.bool(False),
            usePreshower = cms.bool(False)
        ),
        UseRecHitsFlag = cms.bool(False)
    ),
    JetExtractorPSet = cms.PSet(
        ComponentName = cms.string('JetExtractor'),
        DR_Max = cms.double(1.0),
        DR_Veto = cms.double(0.1),
        ExcludeMuonVeto = cms.bool(True),
        JetCollectionLabel = cms.InputTag("hltAK4CaloJetsPFEt5"),
        PrintTimeReport = cms.untracked.bool(False),
        PropagatorName = cms.string('hltESPFastSteppingHelixPropagatorAny'),
        ServiceParameters = cms.PSet(
            Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
            RPCLayers = cms.bool(False),
            UseMuonNavigation = cms.untracked.bool(False)
        ),
        Threshold = cms.double(5.0),
        TrackAssociatorParameters = cms.PSet(
            CSCSegmentCollectionLabel = cms.InputTag("hltCscSegments"),
            CaloTowerCollectionLabel = cms.InputTag("hltTowerMakerForAll"),
            DTRecSegment4DCollectionLabel = cms.InputTag("hltDt4DSegments"),
            EBRecHitCollectionLabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEB"),
            EERecHitCollectionLabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEE"),
            HBHERecHitCollectionLabel = cms.InputTag("hltHbhereco"),
            HORecHitCollectionLabel = cms.InputTag("hltHoreco"),
            accountForTrajectoryChangeCalo = cms.bool(False),
            dREcal = cms.double(0.5),
            dREcalPreselection = cms.double(0.5),
            dRHcal = cms.double(0.5),
            dRHcalPreselection = cms.double(0.5),
            dRMuon = cms.double(9999.0),
            dRMuonPreselection = cms.double(0.2),
            dRPreshowerPreselection = cms.double(0.2),
            muonMaxDistanceSigmaX = cms.double(0.0),
            muonMaxDistanceSigmaY = cms.double(0.0),
            muonMaxDistanceX = cms.double(5.0),
            muonMaxDistanceY = cms.double(5.0),
            propagateAllDirections = cms.bool(True),
            trajectoryUncertaintyTolerance = cms.double(-1.0),
            truthMatch = cms.bool(False),
            useCalo = cms.bool(True),
            useEcal = cms.bool(False),
            useHO = cms.bool(False),
            useHcal = cms.bool(False),
            useMuon = cms.bool(False),
            usePreshower = cms.bool(False)
        )
    ),
    MuonCaloCompatibility = cms.PSet(
        MuonTemplateFileName = cms.FileInPath('RecoMuon/MuonIdentification/data/MuID_templates_muons_lowPt_3_1_norm.root'),
        PionTemplateFileName = cms.FileInPath('RecoMuon/MuonIdentification/data/MuID_templates_pions_lowPt_3_1_norm.root'),
        allSiPMHO = cms.bool(False),
        delta_eta = cms.double(0.02),
        delta_phi = cms.double(0.02)
    ),
    ShowerDigiFillerParameters = cms.PSet(
        cscDigiCollectionLabel = cms.InputTag("muonCSCDigis","MuonCSCStripDigi"),
        digiMaxDistanceX = cms.double(25.0),
        dtDigiCollectionLabel = cms.InputTag("muonDTDigis")
    ),
    TimingFillerParameters = cms.PSet(
        CSCTimingParameters = cms.PSet(
            CSCStripError = cms.double(7.0),
            CSCStripTimeOffset = cms.double(0.0),
            CSCTimeOffset = cms.double(0.0),
            CSCWireError = cms.double(8.6),
            CSCWireTimeOffset = cms.double(0.0),
            CSCsegments = cms.InputTag("hltCscSegments"),
            MatchParameters = cms.PSet(
                CSCsegments = cms.InputTag("hltCscSegments"),
                DTradius = cms.double(0.01),
                DTsegments = cms.InputTag("hltDt4DSegments"),
                TightMatchCSC = cms.bool(True),
                TightMatchDT = cms.bool(False)
            ),
            PruneCut = cms.double(100.0),
            ServiceParameters = cms.PSet(
                Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
                RPCLayers = cms.bool(True)
            ),
            UseStripTime = cms.bool(True),
            UseWireTime = cms.bool(True),
            debug = cms.bool(False)
        ),
        DTTimingParameters = cms.PSet(
            DTTimeOffset = cms.double(2.7),
            DTsegments = cms.InputTag("hltDt4DSegments"),
            DoWireCorr = cms.bool(False),
            DropTheta = cms.bool(True),
            HitError = cms.double(6.0),
            HitsMin = cms.int32(5),
            MatchParameters = cms.PSet(
                CSCsegments = cms.InputTag("hltCscSegments"),
                DTradius = cms.double(0.01),
                DTsegments = cms.InputTag("hltDt4DSegments"),
                TightMatchCSC = cms.bool(True),
                TightMatchDT = cms.bool(False)
            ),
            PruneCut = cms.double(10000.0),
            RequireBothProjections = cms.bool(False),
            ServiceParameters = cms.PSet(
                Propagators = cms.untracked.vstring('hltESPFastSteppingHelixPropagatorAny'),
                RPCLayers = cms.bool(True)
            ),
            UseSegmentT0 = cms.bool(False),
            debug = cms.bool(False)
        ),
        EcalEnergyCut = cms.double(0.4),
        ErrorCSC = cms.double(7.4),
        ErrorDT = cms.double(6.0),
        ErrorEB = cms.double(2.085),
        ErrorEE = cms.double(6.95),
        UseCSC = cms.bool(True),
        UseDT = cms.bool(True),
        UseECAL = cms.bool(True)
    ),
    TrackAssociatorParameters = cms.PSet(
        CSCSegmentCollectionLabel = cms.InputTag("hltCscSegments"),
        CaloTowerCollectionLabel = cms.InputTag("hltTowerMakerForAll"),
        DTRecSegment4DCollectionLabel = cms.InputTag("hltDt4DSegments"),
        EBRecHitCollectionLabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEB"),
        EERecHitCollectionLabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEE"),
        HBHERecHitCollectionLabel = cms.InputTag("hltHbhereco"),
        HORecHitCollectionLabel = cms.InputTag("hltHoreco"),
        accountForTrajectoryChangeCalo = cms.bool(False),
        dREcal = cms.double(9999.0),
        dREcalPreselection = cms.double(0.05),
        dRHcal = cms.double(9999.0),
        dRHcalPreselection = cms.double(0.2),
        dRMuon = cms.double(9999.0),
        dRMuonPreselection = cms.double(0.2),
        dRPreshowerPreselection = cms.double(0.2),
        muonMaxDistanceSigmaX = cms.double(0.0),
        muonMaxDistanceSigmaY = cms.double(0.0),
        muonMaxDistanceX = cms.double(5.0),
        muonMaxDistanceY = cms.double(5.0),
        propagateAllDirections = cms.bool(True),
        trajectoryUncertaintyTolerance = cms.double(-1.0),
        truthMatch = cms.bool(False),
        useCalo = cms.bool(False),
        useEcal = cms.bool(True),
        useHO = cms.bool(True),
        useHcal = cms.bool(True),
        useMuon = cms.bool(True),
        usePreshower = cms.bool(False)
    ),
    TrackExtractorPSet = cms.PSet(
        BeamSpotLabel = cms.InputTag("hltOnlineBeamSpot"),
        BeamlineOption = cms.string('BeamSpotFromEvent'),
        Chi2Ndof_Max = cms.double(1e+64),
        Chi2Prob_Min = cms.double(-1.0),
        ComponentName = cms.string('TrackExtractor'),
        DR_Max = cms.double(1.0),
        DR_Veto = cms.double(0.01),
        DepositLabel = cms.untracked.string(''),
        Diff_r = cms.double(0.1),
        Diff_z = cms.double(0.2),
        NHits_Min = cms.uint32(0),
        Pt_Min = cms.double(-1.0),
        inputTrackCollection = cms.InputTag("hltPFMuonMergingPPOnAA")
    ),
    TrackerKinkFinderParameters = cms.PSet(
        diagonalOnly = cms.bool(False),
        usePosition = cms.bool(False)
    ),
    addExtraSoftMuons = cms.bool(False),
    arbitrateTrackerMuons = cms.bool(False),
    arbitrationCleanerOptions = cms.PSet(
        ClusterDPhi = cms.double(0.6),
        ClusterDTheta = cms.double(0.02),
        Clustering = cms.bool(True),
        ME1a = cms.bool(True),
        Overlap = cms.bool(True),
        OverlapDPhi = cms.double(0.0786),
        OverlapDTheta = cms.double(0.02)
    ),
    debugWithTruthMatching = cms.bool(False),
    ecalDepositName = cms.string('ecal'),
    fillCaloCompatibility = cms.bool(True),
    fillEnergy = cms.bool(True),
    fillGlobalTrackQuality = cms.bool(False),
    fillGlobalTrackRefits = cms.bool(False),
    fillIsolation = cms.bool(True),
    fillMatching = cms.bool(True),
    fillShowerDigis = cms.bool(False),
    fillTrackerKink = cms.bool(False),
    globalTrackQualityInputTag = cms.InputTag("glbTrackQual"),
    hcalDepositName = cms.string('hcal'),
    hoDepositName = cms.string('ho'),
    inputCollectionLabels = cms.VInputTag("hltPFMuonMergingPPOnAA", "hltMuonLinksPPOnAA", "hltL2MuonsPPOnAA"),
    inputCollectionTypes = cms.vstring(
        'inner tracks',
        'links',
        'outer tracks'
    ),
    jetDepositName = cms.string('jets'),
    maxAbsDx = cms.double(3.0),
    maxAbsDy = cms.double(9999.0),
    maxAbsEta = cms.double(3.0),
    maxAbsPullX = cms.double(4.0),
    maxAbsPullY = cms.double(9999.0),
    minCaloCompatibility = cms.double(0.6),
    minNumberOfMatches = cms.int32(1),
    minP = cms.double(10.0),
    minPCaloMuon = cms.double(1000000000.0),
    minPt = cms.double(10.0),
    ptThresholdToFillCandidateP4WithGlobalFit = cms.double(200.0),
    pvInputTag = cms.InputTag("offlinePrimaryVertices"),
    runArbitrationCleaner = cms.bool(False),
    selectHighPurity = cms.bool(False),
    sigmaThresholdToFillCandidateP4WithGlobalFit = cms.double(2.0),
    storeCrossedHcalRecHits = cms.bool(False),
    trackDepositName = cms.string('tracker'),
    writeIsoDeposits = cms.bool(False)
)


process.hltOnlineBeamSpot = cms.EDProducer("BeamSpotOnlineProducer",
    beamMode = cms.untracked.uint32(11),
    changeToCMSCoordinates = cms.bool(False),
    gtEvmLabel = cms.InputTag(""),
    maxRadius = cms.double(2.0),
    maxZ = cms.double(40.0),
    setSigmaZ = cms.double(0.0),
    src = cms.InputTag("hltScalersRawToDigi"),
    useTransientRecord = cms.bool(True)
)


process.hltOnlineMetaDataDigis = cms.EDProducer("OnlineMetaDataRawToDigi",
    onlineMetaDataInputLabel = cms.InputTag("rawDataCollector")
)


process.hltPFMuonMergingPPOnAA = cms.EDProducer("TrackListMerger",
    Epsilon = cms.double(-0.001),
    FoundHitBonus = cms.double(5.0),
    LostHitPenalty = cms.double(20.0),
    MaxNormalizedChisq = cms.double(1000.0),
    MinFound = cms.int32(3),
    MinPT = cms.double(0.05),
    ShareFrac = cms.double(0.19),
    TrackProducers = cms.VInputTag("hltIterL3MuonTracksPPOnAA", "hltMergedTracksPPOnAA"),
    allowFirstHitShare = cms.bool(True),
    copyExtras = cms.untracked.bool(True),
    copyMVA = cms.bool(False),
    hasSelector = cms.vint32(0, 0),
    indivShareFrac = cms.vdouble(1.0, 1.0),
    newQuality = cms.string('confirmed'),
    selectedTrackQuals = cms.VInputTag("hltIterL3MuonTracksPPOnAA", "hltMergedTracksPPOnAA"),
    setsToMerge = cms.VPSet(cms.PSet(
        pQual = cms.bool(False),
        tLists = cms.vint32(0, 1)
    )),
    trackAlgoPriorityOrder = cms.string('hltESPTrackAlgoPriorityOrder'),
    writeOnlyTrkQuals = cms.bool(False)
)


process.hltPSetMap = cms.EDProducer("ParameterSetBlobProducer")


process.hltParticleFlowBlockPPOnAA = cms.EDProducer("PFBlockProducer",
    debug = cms.untracked.bool(False),
    elementImporters = cms.VPSet(
        cms.PSet(
            DPtOverPtCuts_byTrackAlgo = cms.vdouble(
                0.5, 0.5, 0.5, 0.5, 0.5,
                0.5
            ),
            NHitCuts_byTrackAlgo = cms.vuint32(
                3, 3, 3, 3, 3,
                3
            ),
            cleanBadConvertedBrems = cms.bool(False),
            importerName = cms.string('GeneralTracksImporter'),
            muonMaxDPtOPt = cms.double(1.0),
            muonSrc = cms.InputTag("hltMuonsPPOnAA"),
            source = cms.InputTag("hltLightPFTracksPPOnAA"),
            trackQuality = cms.string('highPurity'),
            useIterativeTracking = cms.bool(False),
            vetoEndcap = cms.bool(False)
        ),
        cms.PSet(
            BCtoPFCMap = cms.InputTag(""),
            importerName = cms.string('ECALClusterImporter'),
            source = cms.InputTag("hltParticleFlowClusterECALUnseeded")
        ),
        cms.PSet(
            importerName = cms.string('GenericClusterImporter'),
            source = cms.InputTag("hltParticleFlowClusterHCAL")
        ),
        cms.PSet(
            importerName = cms.string('GenericClusterImporter'),
            source = cms.InputTag("hltParticleFlowClusterHF")
        )
    ),
    linkDefinitions = cms.VPSet(
        cms.PSet(
            linkType = cms.string('TRACK:ECAL'),
            linkerName = cms.string('TrackAndECALLinker'),
            useKDTree = cms.bool(True)
        ),
        cms.PSet(
            linkType = cms.string('TRACK:HCAL'),
            linkerName = cms.string('TrackAndHCALLinker'),
            nMaxHcalLinksPerTrack = cms.int32(1),
            trajectoryLayerEntrance = cms.string('HCALEntrance'),
            trajectoryLayerExit = cms.string('HCALExit'),
            useKDTree = cms.bool(True)
        ),
        cms.PSet(
            linkType = cms.string('ECAL:HCAL'),
            linkerName = cms.string('ECALAndHCALLinker'),
            minAbsEtaEcal = cms.double(2.5),
            useKDTree = cms.bool(False)
        ),
        cms.PSet(
            linkType = cms.string('HFEM:HFHAD'),
            linkerName = cms.string('HFEMAndHFHADLinker'),
            useKDTree = cms.bool(False)
        )
    ),
    verbose = cms.untracked.bool(False)
)


process.hltParticleFlowClusterECALUncorrectedUnseeded = cms.EDProducer("PFClusterProducer",
    energyCorrector = cms.PSet(

    ),
    initialClusteringStep = cms.PSet(
        algoName = cms.string('Basic2DGenericTopoClusterizer'),
        thresholdsByDetector = cms.VPSet(
            cms.PSet(
                detector = cms.string('ECAL_BARREL'),
                gatheringThreshold = cms.double(0.08),
                gatheringThresholdPt = cms.double(0.0)
            ),
            cms.PSet(
                detector = cms.string('ECAL_ENDCAP'),
                gatheringThreshold = cms.double(0.3),
                gatheringThresholdPt = cms.double(0.0)
            )
        ),
        useCornerCells = cms.bool(True)
    ),
    pfClusterBuilder = cms.PSet(
        algoName = cms.string('Basic2DGenericPFlowClusterizer'),
        allCellsPositionCalc = cms.PSet(
            algoName = cms.string('Basic2DGenericPFlowPositionCalc'),
            logWeightDenominator = cms.double(0.08),
            minAllowedNormalization = cms.double(1e-09),
            minFractionInCalc = cms.double(1e-09),
            posCalcNCrystals = cms.int32(-1),
            timeResolutionCalcBarrel = cms.PSet(
                constantTerm = cms.double(0.428192),
                constantTermLowE = cms.double(0.0),
                corrTermLowE = cms.double(0.0510871),
                noiseTerm = cms.double(1.10889),
                noiseTermLowE = cms.double(1.31883),
                threshHighE = cms.double(5.0),
                threshLowE = cms.double(0.5)
            ),
            timeResolutionCalcEndcap = cms.PSet(
                constantTerm = cms.double(0.0),
                constantTermLowE = cms.double(0.0),
                corrTermLowE = cms.double(0.0),
                noiseTerm = cms.double(5.72489999999),
                noiseTermLowE = cms.double(6.92683000001),
                threshHighE = cms.double(10.0),
                threshLowE = cms.double(1.0)
            )
        ),
        excludeOtherSeeds = cms.bool(True),
        maxIterations = cms.uint32(50),
        minFracTot = cms.double(1e-20),
        minFractionToKeep = cms.double(1e-07),
        positionCalc = cms.PSet(
            algoName = cms.string('Basic2DGenericPFlowPositionCalc'),
            logWeightDenominator = cms.double(0.08),
            minAllowedNormalization = cms.double(1e-09),
            minFractionInCalc = cms.double(1e-09),
            posCalcNCrystals = cms.int32(9),
            timeResolutionCalcBarrel = cms.PSet(
                constantTerm = cms.double(0.428192),
                constantTermLowE = cms.double(0.0),
                corrTermLowE = cms.double(0.0510871),
                noiseTerm = cms.double(1.10889),
                noiseTermLowE = cms.double(1.31883),
                threshHighE = cms.double(5.0),
                threshLowE = cms.double(0.5)
            ),
            timeResolutionCalcEndcap = cms.PSet(
                constantTerm = cms.double(0.0),
                constantTermLowE = cms.double(0.0),
                corrTermLowE = cms.double(0.0),
                noiseTerm = cms.double(5.72489999999),
                noiseTermLowE = cms.double(6.92683000001),
                threshHighE = cms.double(10.0),
                threshLowE = cms.double(1.0)
            )
        ),
        positionCalcForConvergence = cms.PSet(
            T0_EB = cms.double(7.4),
            T0_EE = cms.double(3.1),
            T0_ES = cms.double(1.2),
            W0 = cms.double(4.2),
            X0 = cms.double(0.89),
            algoName = cms.string('ECAL2DPositionCalcWithDepthCorr'),
            minAllowedNormalization = cms.double(0.0),
            minFractionInCalc = cms.double(0.0)
        ),
        recHitEnergyNorms = cms.VPSet(
            cms.PSet(
                detector = cms.string('ECAL_BARREL'),
                recHitEnergyNorm = cms.double(0.08)
            ),
            cms.PSet(
                detector = cms.string('ECAL_ENDCAP'),
                recHitEnergyNorm = cms.double(0.3)
            )
        ),
        showerSigma = cms.double(1.5),
        stoppingTolerance = cms.double(1e-08)
    ),
    positionReCalc = cms.PSet(
        T0_EB = cms.double(7.4),
        T0_EE = cms.double(3.1),
        T0_ES = cms.double(1.2),
        W0 = cms.double(4.2),
        X0 = cms.double(0.89),
        algoName = cms.string('ECAL2DPositionCalcWithDepthCorr'),
        minAllowedNormalization = cms.double(0.0),
        minFractionInCalc = cms.double(0.0)
    ),
    recHitCleaners = cms.VPSet(),
    recHitsSource = cms.InputTag("hltParticleFlowRecHitECALUnseeded"),
    seedCleaners = cms.VPSet(),
    seedFinder = cms.PSet(
        algoName = cms.string('LocalMaximumSeedFinder'),
        nNeighbours = cms.int32(8),
        thresholdsByDetector = cms.VPSet(
            cms.PSet(
                detector = cms.string('ECAL_ENDCAP'),
                seedingThreshold = cms.double(0.6),
                seedingThresholdPt = cms.double(0.15)
            ),
            cms.PSet(
                detector = cms.string('ECAL_BARREL'),
                seedingThreshold = cms.double(0.23),
                seedingThresholdPt = cms.double(0.0)
            )
        )
    )
)


process.hltParticleFlowClusterECALUnseeded = cms.EDProducer("CorrectedECALPFClusterProducer",
    energyCorrector = cms.PSet(
        applyCrackCorrections = cms.bool(False),
        applyMVACorrections = cms.bool(True),
        ebSrFlagLabel = cms.InputTag("hltEcalDigis"),
        eeSrFlagLabel = cms.InputTag("hltEcalDigis"),
        maxPtForMVAEvaluation = cms.double(300.0),
        recHitsEBLabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEB"),
        recHitsEELabel = cms.InputTag("hltEcalRecHit","EcalRecHitsEE"),
        srfAwareCorrection = cms.bool(True)
    ),
    inputECAL = cms.InputTag("hltParticleFlowClusterECALUncorrectedUnseeded"),
    inputPS = cms.InputTag("hltParticleFlowClusterPSUnseeded"),
    minimumPSEnergy = cms.double(0.0),
    skipPS = cms.bool(False)
)


process.hltParticleFlowClusterHBHE = cms.EDProducer("PFClusterProducer",
    energyCorrector = cms.PSet(

    ),
    initialClusteringStep = cms.PSet(
        algoName = cms.string('Basic2DGenericTopoClusterizer'),
        thresholdsByDetector = cms.VPSet(
            cms.PSet(
                depths = cms.vint32(1, 2, 3, 4),
                detector = cms.string('HCAL_BARREL1'),
                gatheringThreshold = cms.vdouble(0.1, 0.2, 0.3, 0.3),
                gatheringThresholdPt = cms.vdouble(0.0, 0.0, 0.0, 0.0)
            ),
            cms.PSet(
                depths = cms.vint32(
                    1, 2, 3, 4, 5,
                    6, 7
                ),
                detector = cms.string('HCAL_ENDCAP'),
                gatheringThreshold = cms.vdouble(
                    0.1, 0.2, 0.2, 0.2, 0.2,
                    0.2, 0.2
                ),
                gatheringThresholdPt = cms.vdouble(
                    0.0, 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0
                )
            )
        ),
        useCornerCells = cms.bool(True)
    ),
    pfClusterBuilder = cms.PSet(
        algoName = cms.string('Basic2DGenericPFlowClusterizer'),
        allCellsPositionCalc = cms.PSet(
            algoName = cms.string('Basic2DGenericPFlowPositionCalc'),
            logWeightDenominatorByDetector = cms.VPSet(
                cms.PSet(
                    depths = cms.vint32(1, 2, 3, 4),
                    detector = cms.string('HCAL_BARREL1'),
                    logWeightDenominator = cms.vdouble(0.1, 0.2, 0.3, 0.3)
                ),
                cms.PSet(
                    depths = cms.vint32(
                        1, 2, 3, 4, 5,
                        6, 7
                    ),
                    detector = cms.string('HCAL_ENDCAP'),
                    logWeightDenominator = cms.vdouble(
                        0.1, 0.2, 0.2, 0.2, 0.2,
                        0.2, 0.2
                    )
                )
            ),
            minAllowedNormalization = cms.double(1e-09),
            minFractionInCalc = cms.double(1e-09),
            posCalcNCrystals = cms.int32(-1)
        ),
        clusterTimeResFromSeed = cms.bool(False),
        excludeOtherSeeds = cms.bool(True),
        maxIterations = cms.uint32(50),
        maxNSigmaTime = cms.double(10.0),
        minChi2Prob = cms.double(0.0),
        minFracTot = cms.double(1e-20),
        minFractionToKeep = cms.double(1e-07),
        positionCalc = cms.PSet(
            algoName = cms.string('Basic2DGenericPFlowPositionCalc'),
            logWeightDenominatorByDetector = cms.VPSet(
                cms.PSet(
                    depths = cms.vint32(1, 2, 3, 4),
                    detector = cms.string('HCAL_BARREL1'),
                    logWeightDenominator = cms.vdouble(0.1, 0.2, 0.3, 0.3)
                ),
                cms.PSet(
                    depths = cms.vint32(
                        1, 2, 3, 4, 5,
                        6, 7
                    ),
                    detector = cms.string('HCAL_ENDCAP'),
                    logWeightDenominator = cms.vdouble(
                        0.1, 0.2, 0.2, 0.2, 0.2,
                        0.2, 0.2
                    )
                )
            ),
            minAllowedNormalization = cms.double(1e-09),
            minFractionInCalc = cms.double(1e-09),
            posCalcNCrystals = cms.int32(5)
        ),
        recHitEnergyNorms = cms.VPSet(
            cms.PSet(
                depths = cms.vint32(1, 2, 3, 4),
                detector = cms.string('HCAL_BARREL1'),
                recHitEnergyNorm = cms.vdouble(0.1, 0.2, 0.3, 0.3)
            ),
            cms.PSet(
                depths = cms.vint32(
                    1, 2, 3, 4, 5,
                    6, 7
                ),
                detector = cms.string('HCAL_ENDCAP'),
                recHitEnergyNorm = cms.vdouble(
                    0.1, 0.2, 0.2, 0.2, 0.2,
                    0.2, 0.2
                )
            )
        ),
        showerSigma = cms.double(10.0),
        stoppingTolerance = cms.double(1e-08),
        timeResolutionCalcBarrel = cms.PSet(
            constantTerm = cms.double(2.82),
            constantTermLowE = cms.double(4.24),
            corrTermLowE = cms.double(0.0),
            noiseTerm = cms.double(21.86),
            noiseTermLowE = cms.double(8.0),
            threshHighE = cms.double(15.0),
            threshLowE = cms.double(6.0)
        ),
        timeResolutionCalcEndcap = cms.PSet(
            constantTerm = cms.double(2.82),
            constantTermLowE = cms.double(4.24),
            corrTermLowE = cms.double(0.0),
            noiseTerm = cms.double(21.86),
            noiseTermLowE = cms.double(8.0),
            threshHighE = cms.double(15.0),
            threshLowE = cms.double(6.0)
        ),
        timeSigmaEB = cms.double(10.0),
        timeSigmaEE = cms.double(10.0)
    ),
    positionReCalc = cms.PSet(

    ),
    recHitCleaners = cms.VPSet(),
    recHitsSource = cms.InputTag("hltParticleFlowRecHitHBHE"),
    seedCleaners = cms.VPSet(),
    seedFinder = cms.PSet(
        algoName = cms.string('LocalMaximumSeedFinder'),
        nNeighbours = cms.int32(4),
        thresholdsByDetector = cms.VPSet(
            cms.PSet(
                depths = cms.vint32(1, 2, 3, 4),
                detector = cms.string('HCAL_BARREL1'),
                seedingThreshold = cms.vdouble(0.125, 0.25, 0.35, 0.35),
                seedingThresholdPt = cms.vdouble(0.0, 0.0, 0.0, 0.0)
            ),
            cms.PSet(
                depths = cms.vint32(
                    1, 2, 3, 4, 5,
                    6, 7
                ),
                detector = cms.string('HCAL_ENDCAP'),
                seedingThreshold = cms.vdouble(
                    0.1375, 0.275, 0.275, 0.275, 0.275,
                    0.275, 0.275
                ),
                seedingThresholdPt = cms.vdouble(
                    0.0, 0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0
                )
            )
        )
    )
)


process.hltParticleFlowClusterHCAL = cms.EDProducer("PFMultiDepthClusterProducer",
    clustersSource = cms.InputTag("hltParticleFlowClusterHBHE"),
    energyCorrector = cms.PSet(

    ),
    pfClusterBuilder = cms.PSet(
        algoName = cms.string('PFMultiDepthClusterizer'),
        allCellsPositionCalc = cms.PSet(
            algoName = cms.string('Basic2DGenericPFlowPositionCalc'),
            logWeightDenominatorByDetector = cms.VPSet(
                cms.PSet(
                    depths = cms.vint32(1, 2, 3, 4),
                    detector = cms.string('HCAL_BARREL1'),
                    logWeightDenominator = cms.vdouble(0.1, 0.2, 0.3, 0.3)
                ),
                cms.PSet(
                    depths = cms.vint32(
                        1, 2, 3, 4, 5,
                        6, 7
                    ),
                    detector = cms.string('HCAL_ENDCAP'),
                    logWeightDenominator = cms.vdouble(
                        0.1, 0.2, 0.2, 0.2, 0.2,
                        0.2, 0.2
                    )
                )
            ),
            minAllowedNormalization = cms.double(1e-09),
            minFractionInCalc = cms.double(1e-09),
            posCalcNCrystals = cms.int32(-1)
        ),
        minFractionToKeep = cms.double(1e-07),
        nSigmaEta = cms.double(2.0),
        nSigmaPhi = cms.double(2.0)
    ),
    positionReCalc = cms.PSet(

    )
)


process.hltParticleFlowClusterHF = cms.EDProducer("PFClusterProducer",
    energyCorrector = cms.PSet(

    ),
    initialClusteringStep = cms.PSet(
        algoName = cms.string('Basic2DClusterForEachSeed'),
        thresholdsByDetector = cms.VPSet()
    ),
    pfClusterBuilder = cms.PSet(

    ),
    positionReCalc = cms.PSet(

    ),
    recHitCleaners = cms.VPSet(),
    recHitsSource = cms.InputTag("hltParticleFlowRecHitHF"),
    seedCleaners = cms.VPSet(),
    seedFinder = cms.PSet(
        algoName = cms.string('LocalMaximumSeedFinder'),
        nNeighbours = cms.int32(0),
        thresholdsByDetector = cms.VPSet(
            cms.PSet(
                detector = cms.string('HF_EM'),
                seedingThreshold = cms.double(1.4),
                seedingThresholdPt = cms.double(0.0)
            ),
            cms.PSet(
                detector = cms.string('HF_HAD'),
                seedingThreshold = cms.double(1.4),
                seedingThresholdPt = cms.double(0.0)
            )
        )
    )
)


process.hltParticleFlowClusterPSUnseeded = cms.EDProducer("PFClusterProducer",
    energyCorrector = cms.PSet(

    ),
    initialClusteringStep = cms.PSet(
        algoName = cms.string('Basic2DGenericTopoClusterizer'),
        thresholdsByDetector = cms.VPSet(
            cms.PSet(
                detector = cms.string('PS1'),
                gatheringThreshold = cms.double(6e-05),
                gatheringThresholdPt = cms.double(0.0)
            ),
            cms.PSet(
                detector = cms.string('PS2'),
                gatheringThreshold = cms.double(6e-05),
                gatheringThresholdPt = cms.double(0.0)
            )
        ),
        useCornerCells = cms.bool(False)
    ),
    pfClusterBuilder = cms.PSet(
        algoName = cms.string('Basic2DGenericPFlowClusterizer'),
        excludeOtherSeeds = cms.bool(True),
        maxIterations = cms.uint32(50),
        minFracTot = cms.double(1e-20),
        minFractionToKeep = cms.double(1e-07),
        positionCalc = cms.PSet(
            algoName = cms.string('Basic2DGenericPFlowPositionCalc'),
            logWeightDenominator = cms.double(6e-05),
            minAllowedNormalization = cms.double(1e-09),
            minFractionInCalc = cms.double(1e-09),
            posCalcNCrystals = cms.int32(-1)
        ),
        recHitEnergyNorms = cms.VPSet(
            cms.PSet(
                detector = cms.string('PS1'),
                recHitEnergyNorm = cms.double(6e-05)
            ),
            cms.PSet(
                detector = cms.string('PS2'),
                recHitEnergyNorm = cms.double(6e-05)
            )
        ),
        showerSigma = cms.double(0.3),
        stoppingTolerance = cms.double(1e-08)
    ),
    positionReCalc = cms.PSet(

    ),
    recHitCleaners = cms.VPSet(),
    recHitsSource = cms.InputTag("hltParticleFlowRecHitPSUnseeded"),
    seedCleaners = cms.VPSet(),
    seedFinder = cms.PSet(
        algoName = cms.string('LocalMaximumSeedFinder'),
        nNeighbours = cms.int32(4),
        thresholdsByDetector = cms.VPSet(
            cms.PSet(
                detector = cms.string('PS1'),
                seedingThreshold = cms.double(0.00012),
                seedingThresholdPt = cms.double(0.0)
            ),
            cms.PSet(
                detector = cms.string('PS2'),
                seedingThreshold = cms.double(0.00012),
                seedingThresholdPt = cms.double(0.0)
            )
        )
    )
)


process.hltParticleFlowPPOnAA = cms.EDProducer("PFProducer",
    GedElectronValueMap = cms.InputTag("gedGsfElectronsTmp"),
    GedPhotonValueMap = cms.InputTag("tmpGedPhotons","valMapPFEgammaCandToPhoton"),
    PFEGammaCandidates = cms.InputTag("particleFlowEGamma"),
    PFEGammaFiltersParameters = cms.PSet(
        electron_ecalDrivenHademPreselCut = cms.double(0.15),
        electron_iso_combIso_barrel = cms.double(10.0),
        electron_iso_combIso_endcap = cms.double(10.0),
        electron_iso_mva_barrel = cms.double(-0.1875),
        electron_iso_mva_endcap = cms.double(-0.1075),
        electron_iso_pt = cms.double(10.0),
        electron_maxElePtForOnlyMVAPresel = cms.double(50.0),
        electron_missinghits = cms.uint32(1),
        electron_noniso_mvaCut = cms.double(-0.1),
        electron_protectionsForBadHcal = cms.PSet(
            dEta = cms.vdouble(0.0064, 0.01264),
            dPhi = cms.vdouble(0.0547, 0.0394),
            eInvPInv = cms.vdouble(0.184, 0.0721),
            enableProtections = cms.bool(False),
            full5x5_sigmaIetaIeta = cms.vdouble(0.0106, 0.0387)
        ),
        electron_protectionsForJetMET = cms.PSet(
            maxDPhiIN = cms.double(0.1),
            maxE = cms.double(50.0),
            maxEcalEOverPRes = cms.double(0.2),
            maxEcalEOverP_1 = cms.double(0.5),
            maxEcalEOverP_2 = cms.double(0.2),
            maxEeleOverPout = cms.double(0.2),
            maxEeleOverPoutRes = cms.double(0.5),
            maxEleHcalEOverEcalE = cms.double(0.1),
            maxHcalE = cms.double(10.0),
            maxHcalEOverEcalE = cms.double(0.1),
            maxHcalEOverP = cms.double(1.0),
            maxNtracks = cms.double(3.0),
            maxTrackPOverEele = cms.double(1.0)
        ),
        photon_HoE = cms.double(0.05),
        photon_MinEt = cms.double(10.0),
        photon_SigmaiEtaiEta_barrel = cms.double(0.0125),
        photon_SigmaiEtaiEta_endcap = cms.double(0.034),
        photon_combIso = cms.double(10.0),
        photon_protectionsForBadHcal = cms.PSet(
            enableProtections = cms.bool(False),
            solidConeTrkIsoOffset = cms.double(10.0),
            solidConeTrkIsoSlope = cms.double(0.3)
        ),
        photon_protectionsForJetMET = cms.PSet(
            sumPtTrackIso = cms.double(4.0),
            sumPtTrackIsoSlope = cms.double(0.001)
        )
    ),
    PFHFCleaningParameters = cms.PSet(
        maxDeltaPhiPt = cms.double(7.0),
        maxSignificance = cms.double(2.5),
        minDeltaMet = cms.double(0.4),
        minHFCleaningPt = cms.double(5.0),
        minSignificance = cms.double(2.5),
        minSignificanceReduction = cms.double(1.4)
    ),
    PFMuonAlgoParameters = cms.PSet(

    ),
    blocks = cms.InputTag("hltParticleFlowBlockPPOnAA"),
    calibHF_a_EMHAD = cms.vdouble(
        1.42215, 1.00496, 0.68961, 0.81656, 0.98504,
        0.98504, 1.00802, 1.0593, 1.4576, 1.4576
    ),
    calibHF_a_EMonly = cms.vdouble(
        0.96945, 0.96701, 0.76309, 0.82268, 0.87583,
        0.89718, 0.98674, 1.4681, 1.458, 1.458
    ),
    calibHF_b_EMHAD = cms.vdouble(
        1.27541, 0.85361, 0.86333, 0.89091, 0.94348,
        0.94348, 0.9437, 1.0034, 1.0444, 1.0444
    ),
    calibHF_b_HADonly = cms.vdouble(
        1.27541, 0.85361, 0.86333, 0.89091, 0.94348,
        0.94348, 0.9437, 1.0034, 1.0444, 1.0444
    ),
    calibHF_eta_step = cms.vdouble(
        0.0, 2.9, 3.0, 3.2, 4.2,
        4.4, 4.6, 4.8, 5.2, 5.4
    ),
    calibHF_use = cms.bool(False),
    calibrationsLabel = cms.string('HLT'),
    cleanedHF = cms.VInputTag("hltParticleFlowRecHitHF:Cleaned", "hltParticleFlowClusterHF:Cleaned"),
    debug = cms.untracked.bool(False),
    dptRel_DispVtx = cms.double(10.0),
    egammaElectrons = cms.InputTag(""),
    factors_45 = cms.vdouble(10.0, 100.0),
    goodPixelTrackDeadHcal_chi2n = cms.double(2.0),
    goodPixelTrackDeadHcal_dxy = cms.double(0.02),
    goodPixelTrackDeadHcal_dz = cms.double(0.05),
    goodPixelTrackDeadHcal_maxLost3Hit = cms.int32(0),
    goodPixelTrackDeadHcal_maxLost4Hit = cms.int32(1),
    goodPixelTrackDeadHcal_maxPt = cms.double(50.0),
    goodPixelTrackDeadHcal_minEta = cms.double(2.3),
    goodPixelTrackDeadHcal_ptErrRel = cms.double(1.0),
    goodTrackDeadHcal_chi2n = cms.double(5.0),
    goodTrackDeadHcal_dxy = cms.double(0.5),
    goodTrackDeadHcal_layers = cms.uint32(4),
    goodTrackDeadHcal_ptErrRel = cms.double(0.2),
    goodTrackDeadHcal_validFr = cms.double(0.5),
    iCfgCandConnector = cms.PSet(
        bCalibPrimary = cms.bool(False),
        bCorrect = cms.bool(False),
        nuclCalibFactors = cms.vdouble(0.8, 0.15, 0.5, 0.5, 0.05)
    ),
    muon_ECAL = cms.vdouble(0.5, 0.5),
    muon_HCAL = cms.vdouble(3.0, 3.0),
    muon_HO = cms.vdouble(0.9, 0.9),
    muons = cms.InputTag("hltMuonsPPOnAA"),
    nsigma_TRACK = cms.double(1.0),
    pf_nsigma_ECAL = cms.double(0.0),
    pf_nsigma_HCAL = cms.double(1.0),
    pf_nsigma_HFEM = cms.double(1.0),
    pf_nsigma_HFHAD = cms.double(1.0),
    postHFCleaning = cms.bool(False),
    postMuonCleaning = cms.bool(True),
    pt_Error = cms.double(1.0),
    rejectTracks_Bad = cms.bool(False),
    rejectTracks_Step45 = cms.bool(False),
    resolHF_square = cms.vdouble(7.834401, 0.012996, 0.0),
    useCalibrationsFromDB = cms.bool(True),
    useEGammaElectrons = cms.bool(False),
    useEGammaFilters = cms.bool(False),
    useHO = cms.bool(False),
    usePFConversions = cms.bool(False),
    usePFDecays = cms.bool(False),
    usePFNuclearInteractions = cms.bool(False),
    useProtectionsForJetMET = cms.bool(True),
    useVerticesForNeutral = cms.bool(True),
    verbose = cms.untracked.bool(False),
    vertexCollection = cms.InputTag("hltPixelVerticesPPOnAA"),
    vetoEndcap = cms.bool(False)
)


process.hltParticleFlowRecHitECALUnseeded = cms.EDProducer("PFRecHitProducer",
    navigator = cms.PSet(
        barrel = cms.PSet(

        ),
        endcap = cms.PSet(

        ),
        name = cms.string('PFRecHitECALNavigator')
    ),
    producers = cms.VPSet(
        cms.PSet(
            name = cms.string('PFEBRecHitCreator'),
            qualityTests = cms.VPSet(
                cms.PSet(
                    applySelectionsToAllCrystals = cms.bool(True),
                    name = cms.string('PFRecHitQTestDBThreshold')
                ),
                cms.PSet(
                    cleaningThreshold = cms.double(2.0),
                    name = cms.string('PFRecHitQTestECAL'),
                    skipTTRecoveredHits = cms.bool(True),
                    timingCleaning = cms.bool(True),
                    topologicalCleaning = cms.bool(True)
                )
            ),
            srFlags = cms.InputTag(""),
            src = cms.InputTag("hltEcalRecHit","EcalRecHitsEB")
        ),
        cms.PSet(
            name = cms.string('PFEERecHitCreator'),
            qualityTests = cms.VPSet(
                cms.PSet(
                    applySelectionsToAllCrystals = cms.bool(True),
                    name = cms.string('PFRecHitQTestDBThreshold')
                ),
                cms.PSet(
                    cleaningThreshold = cms.double(2.0),
                    name = cms.string('PFRecHitQTestECAL'),
                    skipTTRecoveredHits = cms.bool(True),
                    timingCleaning = cms.bool(True),
                    topologicalCleaning = cms.bool(True)
                )
            ),
            srFlags = cms.InputTag(""),
            src = cms.InputTag("hltEcalRecHit","EcalRecHitsEE")
        )
    )
)


process.hltParticleFlowRecHitHBHE = cms.EDProducer("PFRecHitProducer",
    navigator = cms.PSet(
        hcalEnums = cms.vint32(1, 2),
        name = cms.string('PFRecHitHCALDenseIdNavigator')
    ),
    producers = cms.VPSet(cms.PSet(
        name = cms.string('PFHBHERecHitCreator'),
        qualityTests = cms.VPSet(
            cms.PSet(
                cuts = cms.VPSet(
                    cms.PSet(
                        depth = cms.vint32(1, 2, 3, 4),
                        detectorEnum = cms.int32(1),
                        threshold = cms.vdouble(0.1, 0.2, 0.3, 0.3)
                    ),
                    cms.PSet(
                        depth = cms.vint32(
                            1, 2, 3, 4, 5,
                            6, 7
                        ),
                        detectorEnum = cms.int32(2),
                        threshold = cms.vdouble(
                            0.1, 0.2, 0.2, 0.2, 0.2,
                            0.2, 0.2
                        )
                    )
                ),
                name = cms.string('PFRecHitQTestThreshold'),
                threshold = cms.double(0.8)
            ),
            cms.PSet(
                cleaningThresholds = cms.vdouble(0.0),
                flags = cms.vstring('Standard'),
                maxSeverities = cms.vint32(11),
                name = cms.string('PFRecHitQTestHCALChannel')
            )
        ),
        src = cms.InputTag("hltHbhereco")
    ))
)


process.hltParticleFlowRecHitHF = cms.EDProducer("PFRecHitProducer",
    navigator = cms.PSet(
        hcalEnums = cms.vint32(4),
        name = cms.string('PFRecHitHCALDenseIdNavigator')
    ),
    producers = cms.VPSet(cms.PSet(
        EMDepthCorrection = cms.double(22.0),
        HADDepthCorrection = cms.double(25.0),
        HFCalib29 = cms.double(1.07),
        LongFibre_Cut = cms.double(120.0),
        LongFibre_Fraction = cms.double(0.1),
        ShortFibre_Cut = cms.double(60.0),
        ShortFibre_Fraction = cms.double(0.01),
        name = cms.string('PFHFRecHitCreator'),
        qualityTests = cms.VPSet(
            cms.PSet(
                cleaningThresholds = cms.vdouble(0.0, 120.0, 60.0),
                flags = cms.vstring(
                    'Standard',
                    'HFLong',
                    'HFShort'
                ),
                maxSeverities = cms.vint32(11, 9, 9),
                name = cms.string('PFRecHitQTestHCALChannel')
            ),
            cms.PSet(
                cuts = cms.VPSet(cms.PSet(
                    depth = cms.vint32(1, 2),
                    detectorEnum = cms.int32(4),
                    threshold = cms.vdouble(1.2, 1.8)
                )),
                name = cms.string('PFRecHitQTestHCALThresholdVsDepth')
            )
        ),
        src = cms.InputTag("hltHfreco"),
        thresh_HF = cms.double(0.4)
    ))
)


process.hltParticleFlowRecHitPSUnseeded = cms.EDProducer("PFRecHitProducer",
    navigator = cms.PSet(
        name = cms.string('PFRecHitPreshowerNavigator')
    ),
    producers = cms.VPSet(cms.PSet(
        name = cms.string('PFPSRecHitCreator'),
        qualityTests = cms.VPSet(cms.PSet(
            name = cms.string('PFRecHitQTestThreshold'),
            threshold = cms.double(7e-06)
        )),
        src = cms.InputTag("hltEcalPreshowerRecHit","EcalRecHitsES")
    ))
)


process.hltPixelLayerQuadrupletsPPOnAA = cms.EDProducer("SeedingLayersEDProducer",
    BPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0027),
        hitErrorRZ = cms.double(0.006),
        useErrorsFromParam = cms.bool(True)
    ),
    FPix = cms.PSet(
        HitProducer = cms.string('hltSiPixelRecHitsPPOnAA'),
        TTRHBuilder = cms.string('hltESPTTRHBuilderPixelOnly'),
        hitErrorRPhi = cms.double(0.0051),
        hitErrorRZ = cms.double(0.0036),
        useErrorsFromParam = cms.bool(True)
    ),
    MTEC = cms.PSet(

    ),
    MTIB = cms.PSet(

    ),
    MTID = cms.PSet(

    ),
    MTOB = cms.PSet(

    ),
    TEC = cms.PSet(

    ),
    TIB = cms.PSet(

    ),
    TID = cms.PSet(

    ),
    TOB = cms.PSet(

    ),
    layerList = cms.vstring(
        'BPix1+BPix2+BPix3+BPix4',
        'BPix1+BPix2+BPix3+FPix1_pos',
        'BPix1+BPix2+BPix3+FPix1_neg',
        'BPix1+BPix2+FPix1_pos+FPix2_pos',
        'BPix1+BPix2+FPix1_neg+FPix2_neg',
        'BPix1+FPix1_pos+FPix2_pos+FPix3_pos',
        'BPix1+FPix1_neg+FPix2_neg+FPix3_neg'
    )
)


process.hltPixelTracksFilter = cms.EDProducer("PixelTrackFilterByKinematicsProducer",
    chi2 = cms.double(1000.0),
    nSigmaInvPtTolerance = cms.double(0.0),
    nSigmaTipMaxTolerance = cms.double(0.0),
    ptMin = cms.double(0.1),
    tipMax = cms.double(1.0)
)


process.hltPixelTracksFitter = cms.EDProducer("PixelFitterByHelixProjectionsProducer",
    scaleErrorsForBPix1 = cms.bool(False),
    scaleFactor = cms.double(0.65)
)


process.hltPixelTracksHitDoubletsPPOnAA = cms.EDProducer("HitPairEDProducer",
    clusterCheck = cms.InputTag(""),
    layerPairs = cms.vuint32(0, 1, 2),
    maxElement = cms.uint32(0),
    maxElementTotal = cms.uint32(50000000),
    produceIntermediateHitDoublets = cms.bool(True),
    produceSeedingHitSets = cms.bool(False),
    seedingLayers = cms.InputTag("hltPixelLayerQuadrupletsPPOnAA"),
    trackingRegions = cms.InputTag("hltPixelTracksTrackingRegionsPPOnAA"),
    trackingRegionsSeedingLayers = cms.InputTag("")
)


process.hltPixelTracksHitQuadrupletsPPOnAA = cms.EDProducer("CAHitQuadrupletEDProducer",
    CAHardPtCut = cms.double(0.0),
    CAPhiCut = cms.double(0.2),
    CAPhiCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    CAThetaCut = cms.double(0.002),
    CAThetaCut_byTriplets = cms.VPSet(cms.PSet(
        cut = cms.double(-1.0),
        seedingLayers = cms.string('')
    )),
    SeedComparitorPSet = cms.PSet(
        ComponentName = cms.string('LowPtClusterShapeSeedComparitor'),
        clusterShapeCacheSrc = cms.InputTag("hltSiPixelClustersCachePPOnAA"),
        clusterShapeHitFilter = cms.string('ClusterShapeHitFilter')
    ),
    doublets = cms.InputTag("hltPixelTracksHitDoubletsPPOnAA"),
    extraHitRPhitolerance = cms.double(0.032),
    fitFastCircle = cms.bool(True),
    fitFastCircleChi2Cut = cms.bool(True),
    maxChi2 = cms.PSet(
        enabled = cms.bool(True),
        pt1 = cms.double(0.7),
        pt2 = cms.double(2.0),
        value1 = cms.double(200.0),
        value2 = cms.double(50.0)
    ),
    useBendingCorrection = cms.bool(True)
)


process.hltPixelTracksPPOnAA = cms.EDProducer("PixelTrackProducer",
    Cleaner = cms.string('hltPixelTracksCleanerBySharedHits'),
    Filter = cms.InputTag("hltPixelTracksFilter"),
    Fitter = cms.InputTag("hltPixelTracksFitter"),
    SeedingHitSets = cms.InputTag("hltPixelTracksHitQuadrupletsPPOnAA"),
    passLabel = cms.string('')
)


process.hltPixelTracksTrackingRegionsPPOnAA = cms.EDProducer("GlobalTrackingRegionFromBeamSpotEDProducer",
    RegionPSet = cms.PSet(
        beamSpot = cms.InputTag("hltOnlineBeamSpot"),
        nSigmaZ = cms.double(4.0),
        originRadius = cms.double(0.02),
        precise = cms.bool(True),
        ptMin = cms.double(0.8)
    )
)


process.hltPixelVerticesPPOnAA = cms.EDProducer("PixelVertexProducer",
    Finder = cms.string('DivisiveVertexFinder'),
    Method2 = cms.bool(True),
    NTrkMin = cms.int32(2),
    PVcomparer = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPvClusterComparerForIT')
    ),
    PtMin = cms.double(1.0),
    TrackCollection = cms.InputTag("hltPixelTracksPPOnAA"),
    UseError = cms.bool(True),
    Verbosity = cms.int32(0),
    WtAverage = cms.bool(True),
    ZOffset = cms.double(5.0),
    ZSeparation = cms.double(0.05),
    beamSpot = cms.InputTag("hltOnlineBeamSpot")
)


process.hltPuAK4CaloCorrector = cms.EDProducer("ChainedJetCorrectorProducer",
    correctors = cms.VInputTag("hltAK4CaloRelativeCorrector", "hltAK4CaloAbsoluteCorrector")
)


process.hltPuAK4CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    DxyTrVtxMax = cms.double(0.0),
    DzTrVtxMax = cms.double(0.0),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.5),
    MaxVtxZ = cms.double(15.0),
    MinVtxNdof = cms.int32(5),
    R0 = cms.double(-1.0),
    Rho_EtaMax = cms.double(4.4),
    UseOnlyOnePV = cms.bool(False),
    UseOnlyVertexTracks = cms.bool(False),
    applyWeight = cms.bool(False),
    beta = cms.double(-1.0),
    correctShape = cms.bool(False),
    csRParam = cms.double(-1.0),
    csRho_EtaMax = cms.double(-1.0),
    dRMax = cms.double(-1.0),
    dRMin = cms.double(-1.0),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doFastJetNonUniform = cms.bool(False),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(False),
    doRhoFastjet = cms.bool(False),
    gridMaxRapidity = cms.double(-1.0),
    gridSpacing = cms.double(-1.0),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetCollInstanceName = cms.string(''),
    jetPtMin = cms.double(10.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxDepth = cms.int32(-1),
    maxInputs = cms.uint32(1),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    minimumTowersFraction = cms.double(0.0),
    muCut = cms.double(-1.0),
    muMax = cms.double(-1.0),
    muMin = cms.double(-1.0),
    nExclude = cms.uint32(0),
    nFilt = cms.int32(-1),
    nSigmaPU = cms.double(1.0),
    puCenters = cms.vdouble(),
    puPtMin = cms.double(10.0),
    puWidth = cms.double(0.0),
    rFilt = cms.double(-1.0),
    rFiltFactor = cms.double(-1.0),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    rcut_factor = cms.double(-1.0),
    restrictInputs = cms.bool(False),
    src = cms.InputTag("hltTowerMakerForAll"),
    srcPVs = cms.InputTag("NotUsed"),
    srcWeights = cms.InputTag(""),
    subjetPtMin = cms.double(-1.0),
    subtractorName = cms.string('MultipleAlgoIterator'),
    sumRecHits = cms.bool(False),
    trimPtFracMin = cms.double(-1.0),
    useCMSBoostedTauSeedingAlgorithm = cms.bool(False),
    useConstituentSubtraction = cms.bool(False),
    useDeterministicSeed = cms.bool(True),
    useDynamicFiltering = cms.bool(False),
    useExplicitGhosts = cms.bool(False),
    useFiltering = cms.bool(False),
    useKtPruning = cms.bool(False),
    useMassDropTagger = cms.bool(False),
    usePruning = cms.bool(False),
    useSoftDrop = cms.bool(False),
    useTrimming = cms.bool(False),
    verbosity = cms.int32(0),
    voronoiRfact = cms.double(-0.9),
    writeCompound = cms.bool(False),
    writeJetsWithConst = cms.bool(False),
    yCut = cms.double(-1.0),
    yMax = cms.double(-1.0),
    yMin = cms.double(-1.0),
    zcut = cms.double(-1.0)
)


process.hltPuAK4CaloJetsCorrected = cms.EDProducer("CorrectedCaloJetProducer",
    correctors = cms.VInputTag("hltPuAK4CaloCorrector"),
    src = cms.InputTag("hltPuAK4CaloJets")
)


process.hltPuAK4CaloJetsCorrectedIDPassed = cms.EDProducer("CorrectedCaloJetProducer",
    correctors = cms.VInputTag("hltPuAK4CaloCorrector"),
    src = cms.InputTag("hltPuAK4CaloJetsIDPassed")
)


process.hltPuAK4CaloJetsIDPassed = cms.EDProducer("HLTCaloJetIDProducer",
    JetIDParams = cms.PSet(
        ebRecHitsColl = cms.InputTag("hltEcalRecHit","EcalRecHitsEB"),
        eeRecHitsColl = cms.InputTag("hltEcalRecHit","EcalRecHitsEE"),
        hbheRecHitsColl = cms.InputTag("hltHbhereco"),
        hfRecHitsColl = cms.InputTag("hltHfreco"),
        hoRecHitsColl = cms.InputTag("hltHoreco"),
        useRecHits = cms.bool(True)
    ),
    jetsInput = cms.InputTag("hltPuAK4CaloJets"),
    max_EMF = cms.double(999.0),
    min_EMF = cms.double(1e-06),
    min_N90 = cms.int32(-2),
    min_N90hits = cms.int32(2)
)


process.hltRpcRecHits = cms.EDProducer("RPCRecHitProducer",
    deadSource = cms.string('File'),
    deadvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCDeadVec.dat'),
    maskSource = cms.string('File'),
    maskvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCMaskVec.dat'),
    recAlgo = cms.string('RPCRecHitStandardAlgo'),
    recAlgoConfig = cms.PSet(

    ),
    rpcDigiLabel = cms.InputTag("hltMuonRPCDigis")
)


process.hltScalersRawToDigi = cms.EDProducer("ScalersRawToDigi",
    scalersInputTag = cms.InputTag("rawDataCollector")
)


process.hltSiPixelClustersAfterSplittingPPOnAA = cms.EDProducer("JetCoreClusterSplitter",
    centralMIPCharge = cms.double(26000.0),
    chargeFractionMin = cms.double(2.0),
    chargePerUnit = cms.double(2000.0),
    cores = cms.InputTag("hltJetsForCoreTracking"),
    deltaRmax = cms.double(0.05),
    forceXError = cms.double(100.0),
    forceYError = cms.double(150.0),
    fractionalWidth = cms.double(0.4),
    pixelCPE = cms.string('hltESPPixelCPEGeneric'),
    pixelClusters = cms.InputTag("hltSiPixelClustersPPOnAA"),
    ptMin = cms.double(200.0),
    verbose = cms.bool(False),
    vertices = cms.InputTag("hltFullIter0PrimaryVerticesPreSplittingPPOnAA")
)


process.hltSiPixelClustersCacheAfterSplittingPPOnAA = cms.EDProducer("SiPixelClusterShapeCacheProducer",
    onDemand = cms.bool(False),
    src = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA")
)


process.hltSiPixelClustersCachePPOnAA = cms.EDProducer("SiPixelClusterShapeCacheProducer",
    onDemand = cms.bool(False),
    src = cms.InputTag("hltSiPixelClustersPPOnAA")
)


process.hltSiPixelClustersPPOnAA = cms.EDProducer("SiPixelClusterProducer",
    ChannelThreshold = cms.int32(10),
    ClusterMode = cms.string('PixelThresholdClusterizer'),
    ClusterThreshold = cms.int32(4000),
    ClusterThreshold_L1 = cms.int32(4000),
    ElectronPerADCGain = cms.double(135.0),
    MissCalibrate = cms.bool(True),
    Phase2Calibration = cms.bool(False),
    Phase2DigiBaseline = cms.double(1200.0),
    Phase2KinkADC = cms.int32(8),
    Phase2ReadoutMode = cms.int32(-1),
    SeedThreshold = cms.int32(1000),
    SplitClusters = cms.bool(False),
    VCaltoElectronGain = cms.int32(1),
    VCaltoElectronGain_L1 = cms.int32(1),
    VCaltoElectronOffset = cms.int32(0),
    VCaltoElectronOffset_L1 = cms.int32(0),
    maxNumberOfClusters = cms.int32(-1),
    payloadType = cms.string('Offline'),
    src = cms.InputTag("hltSiPixelDigisPPOnAA")
)


process.hltSiPixelDigisPPOnAA = cms.EDProducer("SiPixelRawToDigi",
    CablingMapLabel = cms.string(''),
    ErrorList = cms.vint32(29),
    IncludeErrors = cms.bool(True),
    InputLabel = cms.InputTag("rawDataCollector"),
    Regions = cms.PSet(

    ),
    SiPixelQualityLabel = cms.string(''),
    UsePhase1 = cms.bool(True),
    UsePilotBlade = cms.bool(False),
    UseQualityInfo = cms.bool(False),
    UserErrorList = cms.vint32()
)


process.hltSiPixelRecHitsAfterSplittingPPOnAA = cms.EDProducer("SiPixelRecHitConverter",
    CPE = cms.string('hltESPPixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),
    src = cms.InputTag("hltSiPixelClustersAfterSplittingPPOnAA")
)


process.hltSiPixelRecHitsPPOnAA = cms.EDProducer("SiPixelRecHitConverter",
    CPE = cms.string('hltESPPixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),
    src = cms.InputTag("hltSiPixelClustersPPOnAA")
)


process.hltSiStripClustersFullPPOnAA = cms.EDProducer("MeasurementTrackerEventProducer",
    Phase2TrackerCluster1DProducer = cms.string(''),
    badPixelFEDChannelCollectionLabels = cms.VInputTag(),
    inactivePixelDetectorLabels = cms.VInputTag(),
    inactiveStripDetectorLabels = cms.VInputTag("hltSiStripExcludedFEDListProducer"),
    measurementTracker = cms.string('hltESPMeasurementTracker'),
    pixelCablingMapLabel = cms.string(''),
    pixelClusterProducer = cms.string('hltSiPixelClustersAfterSplittingPPOnAA'),
    skipClusters = cms.InputTag(""),
    stripClusterProducer = cms.string('hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression'),
    switchOffPixelsIfEmpty = cms.bool(True),
    vectorHits = cms.InputTag(""),
    vectorHitsRej = cms.InputTag("")
)


process.hltSiStripClustersPPOnAA = cms.EDProducer("MeasurementTrackerEventProducer",
    Phase2TrackerCluster1DProducer = cms.string(''),
    badPixelFEDChannelCollectionLabels = cms.VInputTag(),
    inactivePixelDetectorLabels = cms.VInputTag(),
    inactiveStripDetectorLabels = cms.VInputTag("hltSiStripExcludedFEDListProducer"),
    measurementTracker = cms.string('hltESPMeasurementTracker'),
    pixelCablingMapLabel = cms.string(''),
    pixelClusterProducer = cms.string('hltSiPixelClustersPPOnAA'),
    skipClusters = cms.InputTag(""),
    stripClusterProducer = cms.string('hltHITrackingSiStripRawToClustersFacilityZeroSuppression'),
    switchOffPixelsIfEmpty = cms.bool(True),
    vectorHits = cms.InputTag(""),
    vectorHitsRej = cms.InputTag("")
)


process.hltSiStripDigiToZSRaw = cms.EDProducer("SiStripDigiToRawModule",
    CopyBufferHeader = cms.bool(True),
    FedReadoutMode = cms.string('ZERO_SUPPRESSED'),
    InputDigis = cms.InputTag("hltSiStripZeroSuppression","ZeroSuppressed"),
    PacketCode = cms.string('ZERO_SUPPRESSED'),
    RawDataTag = cms.InputTag("rawDataCollector"),
    UseFedKey = cms.bool(False),
    UseWrongDigiType = cms.bool(False)
)


process.hltSiStripExcludedFEDListProducer = cms.EDProducer("SiStripExcludedFEDListProducer",
    ProductLabel = cms.InputTag("rawDataCollector")
)


process.hltSiStripMatchedRecHitsFull = cms.EDProducer("SiStripRecHitConverter",
    ClusterProducer = cms.InputTag("hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression"),
    MaskBadAPVFibers = cms.bool(False),
    Matcher = cms.ESInputTag("SiStripRecHitMatcherESProducer","StandardMatcher"),
    StripCPE = cms.ESInputTag("hltESPStripCPEfromTrackAngle","hltESPStripCPEfromTrackAngle"),
    doMatching = cms.bool(True),
    matchedRecHits = cms.string('matchedRecHit'),
    rphiRecHits = cms.string('rphiRecHit'),
    siStripQualityLabel = cms.ESInputTag("",""),
    stereoRecHits = cms.string('stereoRecHit'),
    useSiStripQuality = cms.bool(False)
)


process.hltSiStripRawToDigi = cms.EDProducer("SiStripRawToDigiModule",
    AppendedBytes = cms.int32(0),
    DoAPVEmulatorCheck = cms.bool(False),
    DoAllCorruptBufferChecks = cms.bool(False),
    ErrorThreshold = cms.uint32(7174),
    LegacyUnpacker = cms.bool(False),
    MarkModulesOnMissingFeds = cms.bool(True),
    ProductLabel = cms.InputTag("rawDataCollector"),
    TriggerFedId = cms.int32(0),
    UnpackBadChannels = cms.bool(False),
    UnpackCommonModeValues = cms.bool(False),
    UseDaqRegister = cms.bool(False),
    UseFedKey = cms.bool(False)
)


process.hltSiStripZeroSuppression = cms.EDProducer("SiStripZeroSuppression",
    Algorithms = cms.PSet(
        APVInspectMode = cms.string('Hybrid'),
        APVRestoreMode = cms.string('BaselineFollower'),
        ApplyBaselineCleaner = cms.bool(True),
        ApplyBaselineRejection = cms.bool(True),
        CleaningSequence = cms.uint32(1),
        CommonModeNoiseSubtractionMode = cms.string('IteratedMedian'),
        CutToAvoidSignal = cms.double(2.0),
        DeltaCMThreshold = cms.uint32(20),
        Deviation = cms.uint32(25),
        ForceNoRestore = cms.bool(False),
        Fraction = cms.double(0.2),
        Iterations = cms.int32(3),
        MeanCM = cms.int32(0),
        PedestalSubtractionFedMode = cms.bool(False),
        SiStripFedZeroSuppressionMode = cms.uint32(4),
        TruncateInSuppressor = cms.bool(True),
        Use10bitsTruncation = cms.bool(False),
        consecThreshold = cms.uint32(5),
        discontinuityThreshold = cms.int32(12),
        distortionThreshold = cms.uint32(20),
        doAPVRestore = cms.bool(True),
        filteredBaselineDerivativeSumSquare = cms.double(30.0),
        filteredBaselineMax = cms.double(6.0),
        hitStripThreshold = cms.uint32(40),
        lastGradient = cms.int32(10),
        minStripsToFit = cms.uint32(4),
        nSaturatedStrip = cms.uint32(2),
        nSigmaNoiseDerTh = cms.uint32(4),
        nSmooth = cms.uint32(9),
        restoreThreshold = cms.double(0.5),
        sizeWindow = cms.int32(1),
        slopeX = cms.int32(3),
        slopeY = cms.int32(4),
        useCMMeanMap = cms.bool(False),
        useRealMeanCM = cms.bool(False),
        widthCluster = cms.int32(64)
    ),
    RawDigiProducersList = cms.VInputTag("hltSiStripRawToDigi:VirginRaw", "hltSiStripRawToDigi:ProcessedRaw", "hltSiStripRawToDigi:ScopeMode", "hltSiStripRawToDigi:ZeroSuppressed"),
    fixCM = cms.bool(False),
    produceBaselinePoints = cms.bool(False),
    produceCalculatedBaseline = cms.bool(False),
    produceHybridFormat = cms.bool(False),
    produceRawDigis = cms.bool(False),
    storeCM = cms.bool(False),
    storeInZScollBadAPV = cms.bool(True)
)


process.hltTowerMakerForAll = cms.EDProducer("CaloTowersCreator",
    AllowMissingInputs = cms.bool(False),
    EBGrid = cms.vdouble(),
    EBSumThreshold = cms.double(0.2),
    EBThreshold = cms.double(0.07),
    EBWeight = cms.double(1.0),
    EBWeights = cms.vdouble(),
    EEGrid = cms.vdouble(),
    EESumThreshold = cms.double(0.45),
    EEThreshold = cms.double(0.3),
    EEWeight = cms.double(1.0),
    EEWeights = cms.vdouble(),
    EcalRecHitSeveritiesToBeExcluded = cms.vstring(
        'kTime',
        'kWeird',
        'kBad'
    ),
    EcalSeveritiesToBeUsedInBadTowers = cms.vstring(),
    EcutTower = cms.double(-1000.0),
    HBGrid = cms.vdouble(),
    HBThreshold = cms.double(0.3),
    HBThreshold1 = cms.double(0.1),
    HBThreshold2 = cms.double(0.2),
    HBWeight = cms.double(1.0),
    HBWeights = cms.vdouble(),
    HEDGrid = cms.vdouble(),
    HEDThreshold = cms.double(0.2),
    HEDThreshold1 = cms.double(0.1),
    HEDWeight = cms.double(1.0),
    HEDWeights = cms.vdouble(),
    HESGrid = cms.vdouble(),
    HESThreshold = cms.double(0.2),
    HESThreshold1 = cms.double(0.1),
    HESWeight = cms.double(1.0),
    HESWeights = cms.vdouble(),
    HF1Grid = cms.vdouble(),
    HF1Threshold = cms.double(0.5),
    HF1Weight = cms.double(1.0),
    HF1Weights = cms.vdouble(),
    HF2Grid = cms.vdouble(),
    HF2Threshold = cms.double(0.85),
    HF2Weight = cms.double(1.0),
    HF2Weights = cms.vdouble(),
    HOGrid = cms.vdouble(),
    HOThreshold0 = cms.double(3.5),
    HOThresholdMinus1 = cms.double(3.5),
    HOThresholdMinus2 = cms.double(3.5),
    HOThresholdPlus1 = cms.double(3.5),
    HOThresholdPlus2 = cms.double(3.5),
    HOWeight = cms.double(1e-99),
    HOWeights = cms.vdouble(),
    HcalAcceptSeverityLevel = cms.uint32(9),
    HcalAcceptSeverityLevelForRejectedHit = cms.uint32(9999),
    HcalPhase = cms.int32(1),
    HcalThreshold = cms.double(-1000.0),
    MomConstrMethod = cms.int32(1),
    MomEBDepth = cms.double(0.3),
    MomEEDepth = cms.double(0.0),
    MomHBDepth = cms.double(0.2),
    MomHEDepth = cms.double(0.4),
    UseEcalRecoveredHits = cms.bool(False),
    UseEtEBTreshold = cms.bool(False),
    UseEtEETreshold = cms.bool(False),
    UseHO = cms.bool(False),
    UseHcalRecoveredHits = cms.bool(False),
    UseRejectedHitsOnly = cms.bool(False),
    UseRejectedRecoveredEcalHits = cms.bool(False),
    UseRejectedRecoveredHcalHits = cms.bool(False),
    UseSymEBTreshold = cms.bool(False),
    UseSymEETreshold = cms.bool(False),
    ecalInputs = cms.VInputTag("hltEcalRecHit:EcalRecHitsEB", "hltEcalRecHit:EcalRecHitsEE"),
    hbheInput = cms.InputTag("hltHbhereco"),
    hfInput = cms.InputTag("hltHfreco"),
    hoInput = cms.InputTag("hltHoreco"),
    missingHcalRescaleFactorForEcal = cms.double(0.0)
)


process.hltTriggerSummaryAOD = cms.EDProducer("TriggerSummaryProducerAOD",
    moduleLabelPatternsToMatch = cms.vstring('hlt*'),
    moduleLabelPatternsToSkip = cms.vstring(),
    processName = cms.string('@'),
    throw = cms.bool(False)
)


process.hltTriggerSummaryRAW = cms.EDProducer("TriggerSummaryProducerRAW",
    processName = cms.string('@')
)


process.hltTrimmedPixelVerticesPPOnAA = cms.EDProducer("PixelVertexCollectionTrimmer",
    PVcomparer = cms.PSet(
        refToPSet_ = cms.string('HLTPSetPvClusterComparerForIT')
    ),
    fractionSumPt2 = cms.double(0.3),
    maxVtx = cms.uint32(100),
    minSumPt2 = cms.double(0.0),
    src = cms.InputTag("hltPixelVerticesPPOnAA")
)


process.packCaloStage2 = cms.EDProducer("L1TDigiToRaw",
    FWId = cms.uint32(1),
    FedId = cms.int32(1366),
    InputLabel = cms.InputTag("simCaloStage2Digis"),
    Setup = cms.string('stage2::CaloSetup'),
    TowerInputLabel = cms.InputTag("simCaloStage2Layer1Digis"),
    lenSlinkHeader = cms.untracked.int32(8),
    lenSlinkTrailer = cms.untracked.int32(8)
)


process.packGmtStage2 = cms.EDProducer("L1TDigiToRaw",
    BMTFInputLabel = cms.InputTag("simKBmtfDigis","BMTF"),
    EMTFInputLabel = cms.InputTag("simEmtfDigis","EMTF"),
    EMTFShowerInputLabel = cms.InputTag("simEmtfShowers","EMTF"),
    FWId = cms.uint32(117440512),
    FedId = cms.int32(1402),
    ImdInputLabelBMTF = cms.InputTag("simGmtStage2Digis","imdMuonsBMTF"),
    ImdInputLabelEMTFNeg = cms.InputTag("simGmtStage2Digis","imdMuonsEMTFNeg"),
    ImdInputLabelEMTFPos = cms.InputTag("simGmtStage2Digis","imdMuonsEMTFPos"),
    ImdInputLabelOMTFNeg = cms.InputTag("simGmtStage2Digis","imdMuonsOMTFNeg"),
    ImdInputLabelOMTFPos = cms.InputTag("simGmtStage2Digis","imdMuonsOMTFPos"),
    InputLabel = cms.InputTag("simGmtStage2Digis"),
    OMTFInputLabel = cms.InputTag("simOmtfDigis","OMTF"),
    Setup = cms.string('stage2::GMTSetup'),
    ShowerInputLabel = cms.InputTag("simGmtShowerDigis"),
    lenSlinkHeader = cms.untracked.int32(8),
    lenSlinkTrailer = cms.untracked.int32(8)
)


process.packGtStage2 = cms.EDProducer("L1TDigiToRaw",
    EGammaInputTag = cms.InputTag("simCaloStage2Digis"),
    EtSumInputTag = cms.InputTag("simCaloStage2Digis"),
    ExtInputTag = cms.InputTag("simGtExtFakeStage2Digis"),
    FWId = cms.uint32(69377),
    FedId = cms.int32(1404),
    GtInputTag = cms.InputTag("simGtStage2Digis"),
    JetInputTag = cms.InputTag("simCaloStage2Digis"),
    MuonInputTag = cms.InputTag("simGmtStage2Digis"),
    Setup = cms.string('stage2::GTSetup'),
    ShowerInputLabel = cms.InputTag("simGmtShowerDigis"),
    TauInputTag = cms.InputTag("simCaloStage2Digis"),
    lenSlinkHeader = cms.untracked.int32(8),
    lenSlinkTrailer = cms.untracked.int32(8)
)


process.rawDataCollector = cms.EDProducer("RawDataCollectorByLabel",
    RawCollectionList = cms.VInputTag("packCaloStage2", "packGmtStage2", "packGtStage2", cms.InputTag("rawDataCollector","","@skipCurrentProcess")),
    verbose = cms.untracked.int32(0)
)


process.rawDataReducedFormat = cms.EDProducer("EvFFEDSelector",
    fedList = cms.vuint32( (
        100, 101, 102, 1024, 103,
        104, 105, 106, 107, 108,
        109, 110, 111, 1118, 1119,
        112, 1120, 1121, 1122, 1123,
        113, 1134, 1135, 114, 115,
        116, 117, 118, 119, 120,
        1200, 1201, 1202, 1203, 1204,
        1205, 1206, 1207, 1208, 1209,
        121, 1212, 1213, 1214, 1215,
        1216, 1217, 1218, 1219, 122,
        1220, 1221, 1224, 1225, 1226,
        1227, 1228, 1229, 123, 1230,
        1231, 1232, 1233, 1236, 1237,
        1238, 1239, 124, 1240, 1241,
        1242, 1243, 1244, 1245, 1248,
        1249, 125, 1250, 1251, 1252,
        1253, 1254, 1255, 1256, 1257,
        126, 1260, 1261, 1262, 1263,
        1264, 1265, 1266, 1267, 1268,
        1269, 127, 1272, 1273, 1274,
        1275, 1276, 1277, 1278, 1279,
        128, 1280, 1281, 1284, 1285,
        1286, 1287, 1288, 1289, 129,
        1290, 1291, 1292, 1293, 1296,
        1297, 1298, 1299, 130, 1300,
        1301, 1302, 1308, 1309, 131,
        1310, 1311, 1312, 1313, 1314,
        132, 1320, 1321, 1322, 1323,
        1324, 1325, 1326, 133, 1332,
        1333, 1334, 1335, 1336, 1337,
        1338, 134, 135, 1354, 1356,
        1358, 136, 1360, 1368, 1369,
        137, 1370, 1371, 1376, 1377,
        138, 1380, 1381, 1384, 1385,
        1386, 139, 1390, 1391, 1392,
        1393, 1394, 1395, 140, 1402,
        1404, 1405, 141, 142, 143,
        144, 145, 146, 147, 148,
        149, 150, 151, 152, 153,
        154, 155, 156, 157, 158,
        159, 160, 161, 162, 163,
        164, 165, 166, 167, 168,
        169, 170, 171, 172, 173,
        174, 175, 176, 177, 178,
        179, 180, 181, 182, 183,
        184, 185, 186, 187, 188,
        189, 190, 191, 192, 193,
        194, 195, 196, 197, 198,
        199, 200, 201, 202, 203,
        204, 205, 206, 207, 208,
        209, 210, 211, 212, 213,
        214, 215, 216, 217, 218,
        219, 220, 221, 222, 223,
        224, 225, 226, 227, 228,
        229, 230, 231, 232, 233,
        234, 235, 236, 237, 238,
        239, 240, 241, 242, 243,
        244, 245, 246, 247, 248,
        249, 250, 251, 252, 253,
        254, 255, 256, 257, 258,
        259, 260, 261, 262, 263,
        264, 265, 266, 267, 268,
        269, 270, 271, 272, 273,
        274, 275, 276, 277, 278,
        279, 280, 281, 282, 283,
        284, 285, 286, 287, 288,
        289, 290, 291, 292, 293,
        294, 295, 296, 297, 298,
        299, 300, 301, 302, 303,
        304, 305, 306, 307, 308,
        309, 310, 311, 312, 313,
        314, 315, 316, 317, 318,
        319, 320, 321, 322, 323,
        324, 325, 326, 327, 328,
        329, 330, 331, 332, 333,
        334, 335, 336, 337, 338,
        339, 340, 341, 342, 343,
        344, 345, 346, 347, 348,
        349, 350, 351, 352, 353,
        354, 355, 356, 357, 358,
        359, 360, 361, 362, 363,
        364, 365, 366, 367, 368,
        369, 370, 371, 372, 373,
        374, 375, 376, 377, 378,
        379, 380, 381, 382, 383,
        384, 385, 386, 387, 388,
        389, 390, 391, 392, 393,
        394, 395, 396, 397, 398,
        399, 400, 401, 402, 403,
        404, 405, 406, 407, 408,
        409, 410, 411, 412, 413,
        414, 415, 416, 417, 418,
        419, 420, 421, 422, 423,
        424, 425, 426, 427, 428,
        429, 430, 431, 432, 433,
        434, 435, 436, 437, 438,
        439, 440, 441, 442, 443,
        444, 445, 446, 447, 448,
        449, 450, 451, 452, 453,
        454, 455, 456, 457, 458,
        459, 460, 461, 462, 463,
        464, 465, 466, 467, 468,
        469, 470, 471, 472, 473,
        474, 475, 476, 477, 478,
        479, 480, 481, 482, 483,
        484, 485, 486, 487, 488,
        489, 50, 51, 52, 53,
        54, 55, 56, 57, 58,
        59, 60, 61, 62, 63,
        64, 65, 66, 67, 68,
        69, 690, 691, 692, 693,
        70, 71, 72, 73, 735,
        74, 75, 76, 77, 78,
        79, 790, 791, 792, 793,
        80, 81, 82, 83, 831,
        832, 833, 834, 835, 836,
        837, 838, 839, 84, 841,
        842, 843, 844, 845, 846,
        847, 848, 849, 85, 851,
        852, 853, 854, 855, 856,
        857, 858, 859, 86, 861,
        862, 863, 864, 865, 866,
        867, 868, 869, 87, 88,
        89, 90, 91, 92, 93,
        94, 95, 96, 97, 98,
        99
     ) ),
    inputTag = cms.InputTag("rawDataRepacker")
)


process.rawDataRepacker = cms.EDProducer("RawDataCollectorByLabel",
    RawCollectionList = cms.VInputTag("hltSiStripDigiToZSRaw", "source", "rawDataCollector"),
    verbose = cms.untracked.int32(0)
)


process.simBmtfDigis = cms.EDProducer("L1TMuonBarrelTrackProducer",
    DTDigi_Source = cms.InputTag("simTwinMuxDigis"),
    DTDigi_Theta_Source = cms.InputTag("simDtTriggerPrimitiveDigis"),
    Debug = cms.untracked.int32(0)
)


process.simCaloStage2Digis = cms.EDProducer("L1TStage2Layer2Producer",
    firmware = cms.int32(1),
    towerToken = cms.InputTag("simCaloStage2Layer1Digis"),
    useStaticConfig = cms.bool(False)
)


process.simCaloStage2Layer1Digis = cms.EDProducer("L1TCaloLayer1",
    ecalToken = cms.InputTag("unpackEcal","EcalTriggerPrimitives"),
    firmwareVersion = cms.int32(3),
    hcalToken = cms.InputTag("simHcalTriggerPrimitiveDigis"),
    unpackEcalMask = cms.bool(False),
    unpackHcalMask = cms.bool(False),
    useCalib = cms.bool(True),
    useECALLUT = cms.bool(True),
    useHCALLUT = cms.bool(True),
    useHFLUT = cms.bool(True),
    useLSB = cms.bool(True),
    verbose = cms.bool(False)
)


process.simCscTriggerPrimitiveDigis = cms.EDProducer("CSCTriggerPrimitivesProducer",
    CSCComparatorDigiProducer = cms.InputTag("unpackCSC","MuonCSCComparatorDigi"),
    CSCWireDigiProducer = cms.InputTag("unpackCSC","MuonCSCWireDigi"),
    GEMPadDigiClusterProducer = cms.InputTag("simMuonGEMPadDigiClusters"),
    MaxBX = cms.int32(11),
    MinBX = cms.int32(5),
    alctPhase1 = cms.PSet(
        alctAccelMode = cms.uint32(0),
        alctDriftDelay = cms.uint32(2),
        alctEarlyTbins = cms.int32(4),
        alctFifoPretrig = cms.uint32(10),
        alctFifoTbins = cms.uint32(16),
        alctGhostCancellationBxDepth = cms.int32(4),
        alctGhostCancellationSideQuality = cms.bool(False),
        alctHitPersist = cms.uint32(6),
        alctL1aWindowWidth = cms.uint32(7),
        alctNarrowMaskForR1 = cms.bool(False),
        alctNplanesHitAccelPattern = cms.uint32(4),
        alctNplanesHitAccelPretrig = cms.uint32(3),
        alctNplanesHitPattern = cms.uint32(4),
        alctNplanesHitPretrig = cms.uint32(3),
        alctPretrigDeadtime = cms.uint32(4),
        alctTrigMode = cms.uint32(2),
        alctUseCorrectedBx = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    alctPhase2 = cms.PSet(
        alctAccelMode = cms.uint32(0),
        alctDriftDelay = cms.uint32(2),
        alctEarlyTbins = cms.int32(4),
        alctFifoPretrig = cms.uint32(10),
        alctFifoTbins = cms.uint32(16),
        alctGhostCancellationBxDepth = cms.int32(1),
        alctGhostCancellationSideQuality = cms.bool(True),
        alctHitPersist = cms.uint32(6),
        alctL1aWindowWidth = cms.uint32(7),
        alctNarrowMaskForR1 = cms.bool(True),
        alctNplanesHitAccelPattern = cms.uint32(4),
        alctNplanesHitAccelPretrig = cms.uint32(3),
        alctNplanesHitPattern = cms.uint32(4),
        alctNplanesHitPretrig = cms.uint32(3),
        alctPretrigDeadtime = cms.uint32(0),
        alctTrigMode = cms.uint32(2),
        alctUseCorrectedBx = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    alctPhase2GEM = cms.PSet(
        alctAccelMode = cms.uint32(0),
        alctDriftDelay = cms.uint32(2),
        alctEarlyTbins = cms.int32(4),
        alctFifoPretrig = cms.uint32(10),
        alctFifoTbins = cms.uint32(16),
        alctGhostCancellationBxDepth = cms.int32(1),
        alctGhostCancellationSideQuality = cms.bool(True),
        alctHitPersist = cms.uint32(6),
        alctL1aWindowWidth = cms.uint32(7),
        alctNarrowMaskForR1 = cms.bool(True),
        alctNplanesHitAccelPattern = cms.uint32(4),
        alctNplanesHitAccelPretrig = cms.uint32(3),
        alctNplanesHitPattern = cms.uint32(4),
        alctNplanesHitPretrig = cms.uint32(3),
        alctPretrigDeadtime = cms.uint32(0),
        alctTrigMode = cms.uint32(2),
        alctUseCorrectedBx = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    checkBadChambers = cms.bool(False),
    clctPhase1 = cms.PSet(
        clctDriftDelay = cms.uint32(2),
        clctFifoPretrig = cms.uint32(7),
        clctFifoTbins = cms.uint32(12),
        clctHitPersist = cms.uint32(4),
        clctMinSeparation = cms.uint32(10),
        clctNplanesHitPattern = cms.uint32(4),
        clctNplanesHitPretrig = cms.uint32(3),
        clctPidThreshPretrig = cms.uint32(2),
        clctStartBxShift = cms.int32(0),
        useDeadTimeZoning = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    clctPhase2 = cms.PSet(
        clctDriftDelay = cms.uint32(2),
        clctFifoPretrig = cms.uint32(7),
        clctFifoTbins = cms.uint32(12),
        clctHitPersist = cms.uint32(4),
        clctMinSeparation = cms.uint32(5),
        clctNplanesHitPattern = cms.uint32(4),
        clctNplanesHitPretrig = cms.uint32(3),
        clctPidThreshPretrig = cms.uint32(2),
        clctPretriggerTriggerZone = cms.uint32(224),
        clctStartBxShift = cms.int32(0),
        clctStateMachineZone = cms.uint32(4),
        useDeadTimeZoning = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    clctPhase2GEM = cms.PSet(
        clctDriftDelay = cms.uint32(2),
        clctFifoPretrig = cms.uint32(7),
        clctFifoTbins = cms.uint32(12),
        clctHitPersist = cms.uint32(4),
        clctMinSeparation = cms.uint32(5),
        clctNplanesHitPattern = cms.uint32(4),
        clctNplanesHitPretrig = cms.uint32(3),
        clctPidThreshPretrig = cms.uint32(2),
        clctPretriggerTriggerZone = cms.uint32(224),
        clctStartBxShift = cms.int32(0),
        clctStateMachineZone = cms.uint32(4),
        useDeadTimeZoning = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    commonParam = cms.PSet(
        disableME1a = cms.bool(False),
        disableME42 = cms.bool(False),
        enableAlctPhase2 = cms.bool(False),
        gangedME1a = cms.bool(False),
        run3 = cms.bool(True),
        runCCLUT_OTMB = cms.bool(True),
        runCCLUT_TMB = cms.bool(False),
        runME11ILT = cms.bool(True),
        runME11Up = cms.bool(True),
        runME21ILT = cms.bool(False),
        runME21Up = cms.bool(True),
        runME31Up = cms.bool(True),
        runME41Up = cms.bool(True),
        runPhase2 = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    copadParamGE11 = cms.PSet(
        maxDeltaBX = cms.uint32(0),
        maxDeltaPad = cms.uint32(8),
        maxDeltaRoll = cms.uint32(1),
        verbosity = cms.uint32(0)
    ),
    copadParamGE21 = cms.PSet(
        maxDeltaBX = cms.uint32(0),
        maxDeltaPad = cms.uint32(8),
        maxDeltaRoll = cms.uint32(1),
        verbosity = cms.uint32(0)
    ),
    debugParameters = cms.bool(True),
    keepALCTPreTriggers = cms.bool(False),
    keepCLCTPreTriggers = cms.bool(True),
    keepShowers = cms.bool(True),
    mpcParam = cms.PSet(
        dropInvalidStubs = cms.bool(False),
        dropLowQualityStubs = cms.bool(False),
        maxStubs = cms.uint32(18),
        sortStubs = cms.bool(False)
    ),
    showerParam = cms.PSet(
        anodeShower = cms.PSet(
            minLayersCentralTBin = cms.uint32(5),
            showerMaxInTBin = cms.uint32(8),
            showerMaxOutTBin = cms.uint32(7),
            showerMinInTBin = cms.uint32(8),
            showerMinOutTBin = cms.uint32(4),
            showerThresholds = cms.vuint32(
                140, 140, 140, 20, 41,
                45, 8, 12, 16, 28,
                56, 58, 9, 18, 22,
                26, 55, 57, 8, 16,
                20, 31, 62, 64, 13,
                27, 31
            )
        ),
        cathodeShower = cms.PSet(
            minLayersCentralTBin = cms.uint32(5),
            showerMaxInTBin = cms.uint32(8),
            showerMaxOutTBin = cms.uint32(5),
            showerMinInTBin = cms.uint32(6),
            showerMinOutTBin = cms.uint32(2),
            showerThresholds = cms.vuint32(
                100, 100, 100, 0, 0,
                0, 0, 0, 0, 17,
                33, 35, 0, 0, 0,
                15, 31, 33, 0, 0,
                0, 17, 34, 36, 0,
                0, 0
            )
        ),
        source = cms.uint32(3)
    ),
    tmbPhase1 = cms.PSet(
        alctTrigEnable = cms.uint32(0),
        clctTrigEnable = cms.uint32(0),
        ignoreAlctCrossClct = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    tmbPhase2 = cms.PSet(
        alctTrigEnable = cms.uint32(0),
        clctTrigEnable = cms.uint32(0),
        ignoreAlctCrossClct = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    tmbPhase2GE11 = cms.PSet(
        BunchCrossingCSCminGEMwindow = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        alctTrigEnable = cms.uint32(0),
        assignGEMCSCBending = cms.bool(True),
        buildLCTfromALCTandGEM = cms.bool(True),
        buildLCTfromCLCTandGEM = cms.bool(False),
        clctTrigEnable = cms.uint32(0),
        delayGEMinOTMB = cms.uint32(0),
        dropLowQualityALCTs = cms.bool(True),
        dropLowQualityCLCTs = cms.bool(True),
        dropLowQualityCLCTs_ME1a = cms.bool(True),
        enableMatchGEMandME1a = cms.bool(True),
        enableMatchGEMandME1b = cms.bool(True),
        ignoreAlctCrossClct = cms.bool(True),
        matchCLCTpropagation = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        maxDeltaHsEven = cms.uint32(5),
        maxDeltaHsOdd = cms.uint32(10),
        maxDeltaWG = cms.uint32(7),
        mitigateSlopeByCosi = cms.bool(False),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0),
        windowBXALCTGEM = cms.uint32(3),
        windowBXCLCTGEM = cms.uint32(7)
    ),
    tmbPhase2GE21 = cms.PSet(
        BunchCrossingCSCminGEMwindow = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        alctTrigEnable = cms.uint32(0),
        assignGEMCSCBending = cms.bool(True),
        buildLCTfromALCTandGEM = cms.bool(True),
        buildLCTfromCLCTandGEM = cms.bool(False),
        clctTrigEnable = cms.uint32(0),
        delayGEMinOTMB = cms.uint32(0),
        dropLowQualityALCTs = cms.bool(True),
        dropLowQualityCLCTs = cms.bool(True),
        dropLowQualityCLCTs_ME1a = cms.bool(True),
        enableMatchGEMandME1a = cms.bool(True),
        enableMatchGEMandME1b = cms.bool(True),
        ignoreAlctCrossClct = cms.bool(True),
        matchCLCTpropagation = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        maxDeltaHsEven = cms.uint32(5),
        maxDeltaHsOdd = cms.uint32(10),
        maxDeltaWG = cms.uint32(7),
        mitigateSlopeByCosi = cms.bool(False),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0),
        windowBXALCTGEM = cms.uint32(3),
        windowBXCLCTGEM = cms.uint32(7)
    )
)


process.simCscTriggerPrimitiveDigisRun3 = cms.EDProducer("CSCTriggerPrimitivesProducer",
    CSCComparatorDigiProducer = cms.InputTag("simMuonCSCDigis","MuonCSCComparatorDigi"),
    CSCWireDigiProducer = cms.InputTag("simMuonCSCDigis","MuonCSCWireDigi"),
    GEMPadDigiClusterProducer = cms.InputTag("simMuonGEMPadDigiClusters"),
    MaxBX = cms.int32(11),
    MinBX = cms.int32(5),
    alctPhase1 = cms.PSet(
        alctAccelMode = cms.uint32(0),
        alctDriftDelay = cms.uint32(2),
        alctEarlyTbins = cms.int32(4),
        alctFifoPretrig = cms.uint32(10),
        alctFifoTbins = cms.uint32(16),
        alctGhostCancellationBxDepth = cms.int32(4),
        alctGhostCancellationSideQuality = cms.bool(False),
        alctHitPersist = cms.uint32(6),
        alctL1aWindowWidth = cms.uint32(7),
        alctNarrowMaskForR1 = cms.bool(False),
        alctNplanesHitAccelPattern = cms.uint32(4),
        alctNplanesHitAccelPretrig = cms.uint32(3),
        alctNplanesHitPattern = cms.uint32(4),
        alctNplanesHitPretrig = cms.uint32(3),
        alctPretrigDeadtime = cms.uint32(4),
        alctTrigMode = cms.uint32(2),
        alctUseCorrectedBx = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    alctPhase2 = cms.PSet(
        alctAccelMode = cms.uint32(0),
        alctDriftDelay = cms.uint32(2),
        alctEarlyTbins = cms.int32(4),
        alctFifoPretrig = cms.uint32(10),
        alctFifoTbins = cms.uint32(16),
        alctGhostCancellationBxDepth = cms.int32(1),
        alctGhostCancellationSideQuality = cms.bool(True),
        alctHitPersist = cms.uint32(6),
        alctL1aWindowWidth = cms.uint32(7),
        alctNarrowMaskForR1 = cms.bool(True),
        alctNplanesHitAccelPattern = cms.uint32(4),
        alctNplanesHitAccelPretrig = cms.uint32(3),
        alctNplanesHitPattern = cms.uint32(4),
        alctNplanesHitPretrig = cms.uint32(3),
        alctPretrigDeadtime = cms.uint32(0),
        alctTrigMode = cms.uint32(2),
        alctUseCorrectedBx = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    alctPhase2GEM = cms.PSet(
        alctAccelMode = cms.uint32(0),
        alctDriftDelay = cms.uint32(2),
        alctEarlyTbins = cms.int32(4),
        alctFifoPretrig = cms.uint32(10),
        alctFifoTbins = cms.uint32(16),
        alctGhostCancellationBxDepth = cms.int32(1),
        alctGhostCancellationSideQuality = cms.bool(True),
        alctHitPersist = cms.uint32(6),
        alctL1aWindowWidth = cms.uint32(7),
        alctNarrowMaskForR1 = cms.bool(True),
        alctNplanesHitAccelPattern = cms.uint32(4),
        alctNplanesHitAccelPretrig = cms.uint32(3),
        alctNplanesHitPattern = cms.uint32(4),
        alctNplanesHitPretrig = cms.uint32(3),
        alctPretrigDeadtime = cms.uint32(0),
        alctTrigMode = cms.uint32(2),
        alctUseCorrectedBx = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    checkBadChambers = cms.bool(False),
    clctPhase1 = cms.PSet(
        clctDriftDelay = cms.uint32(2),
        clctFifoPretrig = cms.uint32(7),
        clctFifoTbins = cms.uint32(12),
        clctHitPersist = cms.uint32(4),
        clctMinSeparation = cms.uint32(10),
        clctNplanesHitPattern = cms.uint32(4),
        clctNplanesHitPretrig = cms.uint32(3),
        clctPidThreshPretrig = cms.uint32(2),
        clctStartBxShift = cms.int32(0),
        useDeadTimeZoning = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    clctPhase2 = cms.PSet(
        clctDriftDelay = cms.uint32(2),
        clctFifoPretrig = cms.uint32(7),
        clctFifoTbins = cms.uint32(12),
        clctHitPersist = cms.uint32(4),
        clctMinSeparation = cms.uint32(5),
        clctNplanesHitPattern = cms.uint32(4),
        clctNplanesHitPretrig = cms.uint32(3),
        clctPidThreshPretrig = cms.uint32(2),
        clctPretriggerTriggerZone = cms.uint32(224),
        clctStartBxShift = cms.int32(0),
        clctStateMachineZone = cms.uint32(4),
        useDeadTimeZoning = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    clctPhase2GEM = cms.PSet(
        clctDriftDelay = cms.uint32(2),
        clctFifoPretrig = cms.uint32(7),
        clctFifoTbins = cms.uint32(12),
        clctHitPersist = cms.uint32(4),
        clctMinSeparation = cms.uint32(5),
        clctNplanesHitPattern = cms.uint32(4),
        clctNplanesHitPretrig = cms.uint32(3),
        clctPidThreshPretrig = cms.uint32(2),
        clctPretriggerTriggerZone = cms.uint32(224),
        clctStartBxShift = cms.int32(0),
        clctStateMachineZone = cms.uint32(4),
        useDeadTimeZoning = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    commonParam = cms.PSet(
        disableME1a = cms.bool(False),
        disableME42 = cms.bool(False),
        enableAlctPhase2 = cms.bool(False),
        gangedME1a = cms.bool(False),
        run3 = cms.bool(True),
        runCCLUT_OTMB = cms.bool(True),
        runCCLUT_TMB = cms.bool(False),
        runME11ILT = cms.bool(True),
        runME11Up = cms.bool(True),
        runME21ILT = cms.bool(False),
        runME21Up = cms.bool(True),
        runME31Up = cms.bool(True),
        runME41Up = cms.bool(True),
        runPhase2 = cms.bool(True),
        verbosity = cms.int32(0)
    ),
    copadParamGE11 = cms.PSet(
        maxDeltaBX = cms.uint32(0),
        maxDeltaPad = cms.uint32(8),
        maxDeltaRoll = cms.uint32(1),
        verbosity = cms.uint32(0)
    ),
    copadParamGE21 = cms.PSet(
        maxDeltaBX = cms.uint32(0),
        maxDeltaPad = cms.uint32(8),
        maxDeltaRoll = cms.uint32(1),
        verbosity = cms.uint32(0)
    ),
    debugParameters = cms.bool(True),
    keepALCTPreTriggers = cms.bool(False),
    keepCLCTPreTriggers = cms.bool(True),
    keepShowers = cms.bool(True),
    mpcParam = cms.PSet(
        dropInvalidStubs = cms.bool(False),
        dropLowQualityStubs = cms.bool(False),
        maxStubs = cms.uint32(18),
        sortStubs = cms.bool(False)
    ),
    showerParam = cms.PSet(
        anodeShower = cms.PSet(
            minLayersCentralTBin = cms.uint32(5),
            showerMaxInTBin = cms.uint32(8),
            showerMaxOutTBin = cms.uint32(7),
            showerMinInTBin = cms.uint32(8),
            showerMinOutTBin = cms.uint32(4),
            showerThresholds = cms.vuint32(
                140, 140, 140, 20, 41,
                45, 8, 12, 16, 28,
                56, 58, 9, 18, 22,
                26, 55, 57, 8, 16,
                20, 31, 62, 64, 13,
                27, 31
            )
        ),
        cathodeShower = cms.PSet(
            minLayersCentralTBin = cms.uint32(5),
            showerMaxInTBin = cms.uint32(8),
            showerMaxOutTBin = cms.uint32(5),
            showerMinInTBin = cms.uint32(6),
            showerMinOutTBin = cms.uint32(2),
            showerThresholds = cms.vuint32(
                100, 100, 100, 0, 0,
                0, 0, 0, 0, 17,
                33, 35, 0, 0, 0,
                15, 31, 33, 0, 0,
                0, 17, 34, 36, 0,
                0, 0
            )
        ),
        source = cms.uint32(3)
    ),
    tmbPhase1 = cms.PSet(
        alctTrigEnable = cms.uint32(0),
        clctTrigEnable = cms.uint32(0),
        ignoreAlctCrossClct = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    tmbPhase2 = cms.PSet(
        alctTrigEnable = cms.uint32(0),
        clctTrigEnable = cms.uint32(0),
        ignoreAlctCrossClct = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0)
    ),
    tmbPhase2GE11 = cms.PSet(
        BunchCrossingCSCminGEMwindow = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        alctTrigEnable = cms.uint32(0),
        assignGEMCSCBending = cms.bool(True),
        buildLCTfromALCTandGEM = cms.bool(True),
        buildLCTfromCLCTandGEM = cms.bool(False),
        clctTrigEnable = cms.uint32(0),
        delayGEMinOTMB = cms.uint32(0),
        dropLowQualityALCTs = cms.bool(True),
        dropLowQualityCLCTs = cms.bool(True),
        dropLowQualityCLCTs_ME1a = cms.bool(True),
        enableMatchGEMandME1a = cms.bool(True),
        enableMatchGEMandME1b = cms.bool(True),
        ignoreAlctCrossClct = cms.bool(True),
        matchCLCTpropagation = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        maxDeltaHsEven = cms.uint32(5),
        maxDeltaHsOdd = cms.uint32(10),
        maxDeltaWG = cms.uint32(7),
        mitigateSlopeByCosi = cms.bool(False),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0),
        windowBXALCTGEM = cms.uint32(3),
        windowBXCLCTGEM = cms.uint32(7)
    ),
    tmbPhase2GE21 = cms.PSet(
        BunchCrossingCSCminGEMwindow = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        alctTrigEnable = cms.uint32(0),
        assignGEMCSCBending = cms.bool(True),
        buildLCTfromALCTandGEM = cms.bool(True),
        buildLCTfromCLCTandGEM = cms.bool(False),
        clctTrigEnable = cms.uint32(0),
        delayGEMinOTMB = cms.uint32(0),
        dropLowQualityALCTs = cms.bool(True),
        dropLowQualityCLCTs = cms.bool(True),
        dropLowQualityCLCTs_ME1a = cms.bool(True),
        enableMatchGEMandME1a = cms.bool(True),
        enableMatchGEMandME1b = cms.bool(True),
        ignoreAlctCrossClct = cms.bool(True),
        matchCLCTpropagation = cms.bool(True),
        matchEarliestClctOnly = cms.bool(True),
        matchTrigEnable = cms.uint32(1),
        matchTrigWindowSize = cms.uint32(7),
        maxDeltaHsEven = cms.uint32(5),
        maxDeltaHsOdd = cms.uint32(10),
        maxDeltaWG = cms.uint32(7),
        mitigateSlopeByCosi = cms.bool(False),
        mpcBlockMe1a = cms.uint32(0),
        preferredBxMatch = cms.vint32(
            0, -1, 1, -2, 2,
            -3, 3
        ),
        tmbDropUsedClcts = cms.bool(False),
        tmbEarlyTbins = cms.int32(4),
        tmbL1aWindowSize = cms.uint32(7),
        tmbReadoutEarliest2 = cms.bool(True),
        useHighMultiplicityBits = cms.bool(False),
        verbosity = cms.int32(0),
        windowBXALCTGEM = cms.uint32(3),
        windowBXCLCTGEM = cms.uint32(7)
    )
)


process.simDtTriggerPrimitiveDigis = cms.EDProducer("DTTrigProd",
    DTTFSectorNumbering = cms.bool(True),
    debug = cms.untracked.bool(False),
    digiTag = cms.InputTag("unpackDT"),
    lutBtic = cms.untracked.int32(31),
    lutDumpFlag = cms.untracked.bool(False)
)


process.simEmtfDigis = cms.EDProducer("L1TMuonEndCapTrackProducer",
    BXWindow = cms.int32(2),
    CPPFEnable = cms.bool(False),
    CPPFInput = cms.InputTag("simCPPFDigis"),
    CSCComparatorInput = cms.InputTag("simMuonCSCDigis","MuonCSCComparatorDigi"),
    CSCEnable = cms.bool(True),
    CSCInput = cms.InputTag("simCscTriggerPrimitiveDigis","MPCSORTED"),
    CSCInputBXShift = cms.int32(-8),
    DTEnable = cms.bool(False),
    DTPhiInput = cms.InputTag("simTwinMuxDigis"),
    DTThetaInput = cms.InputTag("simDtTriggerPrimitiveDigis"),
    Era = cms.string('Run3_2021'),
    FWConfig = cms.bool(True),
    GEMEnable = cms.bool(False),
    GEMInput = cms.InputTag("simMuonGEMPadDigiClusters"),
    GEMInputBXShift = cms.int32(0),
    IRPCEnable = cms.bool(False),
    ME0Enable = cms.bool(False),
    ME0Input = cms.InputTag("me0TriggerConvertedPseudoDigis"),
    ME0InputBXShift = cms.int32(-8),
    MaxBX = cms.int32(3),
    MinBX = cms.int32(-3),
    RPCEnable = cms.bool(True),
    RPCInput = cms.InputTag("unpackRPC"),
    RPCInputBXShift = cms.int32(0),
    UseRun3CCLUT_OTMB = cms.bool(True),
    UseRun3CCLUT_TMB = cms.bool(False),
    spGCParams16 = cms.PSet(
        BugSameSectorPt0 = cms.bool(False),
        MaxRoadsPerZone = cms.int32(3),
        MaxTracks = cms.int32(3),
        UseSecondEarliest = cms.bool(True)
    ),
    spPAParams16 = cms.PSet(
        Bug9BitDPhi = cms.bool(False),
        BugGMTPhi = cms.bool(False),
        BugMode7CLCT = cms.bool(False),
        BugNegPt = cms.bool(False),
        FixMode15HighPt = cms.bool(True),
        ModeQualVer = cms.int32(2),
        PromoteMode7 = cms.bool(False),
        ProtobufFileName = cms.string('model_graph.displ.10.1.pb'),
        ReadPtLUTFile = cms.bool(False)
    ),
    spPCParams16 = cms.PSet(
        DuplicateTheta = cms.bool(True),
        FixME11Edges = cms.bool(True),
        FixZonePhi = cms.bool(True),
        IncludeNeighbor = cms.bool(True),
        UseNewZones = cms.bool(False),
        ZoneBoundaries = cms.vint32(0, 41, 49, 87, 127),
        ZoneOverlap = cms.int32(2)
    ),
    spPRParams16 = cms.PSet(
        PatternDefinitions = cms.vstring(
            '4,15:15,7:7,7:7,7:7',
            '3,16:16,7:7,7:6,7:6',
            '3,14:14,7:7,8:7,8:7',
            '2,18:17,7:7,7:5,7:5',
            '2,13:12,7:7,10:7,10:7',
            '1,22:19,7:7,7:0,7:0',
            '1,11:8,7:7,14:7,14:7',
            '0,30:23,7:7,7:0,7:0',
            '0,7:0,7:7,14:7,14:7'
        ),
        SymPatternDefinitions = cms.vstring(
            '4,15:15:15:15,7:7:7:7,7:7:7:7,7:7:7:7',
            '3,16:16:14:14,7:7:7:7,8:7:7:6,8:7:7:6',
            '2,18:17:13:12,7:7:7:7,10:7:7:4,10:7:7:4',
            '1,22:19:11:8,7:7:7:7,14:7:7:0,14:7:7:0',
            '0,30:23:7:0,7:7:7:7,14:7:7:0,14:7:7:0'
        ),
        UseSymmetricalPatterns = cms.bool(True)
    ),
    spTBParams16 = cms.PSet(
        BugAmbigThetaWin = cms.bool(False),
        BugME11Dupes = cms.bool(False),
        BugSt2PhDiff = cms.bool(False),
        ThetaWindow = cms.int32(8),
        ThetaWindowZone0 = cms.int32(4),
        TwoStationSameBX = cms.bool(True),
        UseSingleHits = cms.bool(False)
    ),
    verbosity = cms.untracked.int32(0)
)


process.simEmtfShowers = cms.EDProducer("L1TMuonEndCapShowerProducer",
    CSCShowerInput = cms.InputTag("simCscTriggerPrimitiveDigis"),
    enableOneNominalShowers = cms.bool(True),
    enableOneTightShowers = cms.bool(True),
    enableTwoLooseShowers = cms.bool(False),
    mightGet = cms.optional.untracked.vstring,
    nLooseShowers = cms.uint32(2),
    nNominalShowers = cms.uint32(1),
    nTightShowers = cms.uint32(1)
)


process.simGmtCaloSumDigis = cms.EDProducer("L1TMuonCaloSumProducer",
    caloStage2Layer2Label = cms.InputTag("simCaloStage2Layer1Digis")
)


process.simGmtShowerDigis = cms.EDProducer("L1TMuonShowerProducer",
    bxMax = cms.int32(0),
    bxMin = cms.int32(0),
    mightGet = cms.optional.untracked.vstring,
    showerInput = cms.InputTag("simEmtfShowers","EMTF")
)


process.simGmtStage2Digis = cms.EDProducer("L1TMuonProducer",
    autoBxRange = cms.bool(True),
    autoCancelMode = cms.bool(False),
    barrelTFInput = cms.InputTag("simKBmtfDigis","BMTF"),
    bmtfCancelMode = cms.string('kftracks'),
    bxMax = cms.int32(2),
    bxMin = cms.int32(-2),
    emtfCancelMode = cms.string('coordinate'),
    forwardTFInput = cms.InputTag("simEmtfDigis","EMTF"),
    overlapTFInput = cms.InputTag("simOmtfDigis","OMTF"),
    triggerTowerInput = cms.InputTag("simGmtCaloSumDigis","TriggerTowerSums")
)


process.simGtExtFakeStage2Digis = cms.EDProducer("L1TExtCondProducer",
    bxFirst = cms.int32(-2),
    bxLast = cms.int32(2),
    setBptxAND = cms.bool(True),
    setBptxMinus = cms.bool(True),
    setBptxOR = cms.bool(True),
    setBptxPlus = cms.bool(True),
    tcdsRecordLabel = cms.InputTag("")
)


process.simGtStage2Digis = cms.EDProducer("L1TGlobalProducer",
    AlgoBlkInputTag = cms.InputTag("gtStage2Digis"),
    AlgorithmTriggersUnmasked = cms.bool(True),
    AlgorithmTriggersUnprescaled = cms.bool(True),
    EGammaInputTag = cms.InputTag("simCaloStage2Digis"),
    EtSumInputTag = cms.InputTag("simCaloStage2Digis"),
    ExtInputTag = cms.InputTag("simGtExtFakeStage2Digis"),
    GetPrescaleColumnFromData = cms.bool(False),
    JetInputTag = cms.InputTag("simCaloStage2Digis"),
    MuonInputTag = cms.InputTag("simGmtStage2Digis"),
    MuonShowerInputTag = cms.InputTag("simGmtShowerDigis"),
    RequireMenuToMatchAlgoBlkInput = cms.bool(False),
    TauInputTag = cms.InputTag("simCaloStage2Digis"),
    useMuonShowers = cms.bool(True)
)


process.simHcalTriggerPrimitiveDigis = cms.EDProducer("HcalTrigPrimDigiProducer",
    FG_HF_thresholds = cms.vuint32(17, 255),
    FG_threshold = cms.uint32(12),
    FrontEndFormatError = cms.bool(False),
    InputTagFEDRaw = cms.InputTag("rawDataCollector"),
    LSConfig = cms.untracked.PSet(
        HcalFeatureHFEMBit = cms.bool(False),
        Long_Short_Offset = cms.double(10.1),
        Long_vrs_Short_Slope = cms.double(100.2),
        Min_Long_Energy = cms.double(10),
        Min_Short_Energy = cms.double(10)
    ),
    MinSignalThreshold = cms.uint32(0),
    PMTNoiseThreshold = cms.uint32(0),
    PeakFinderAlgorithm = cms.int32(2),
    RunZS = cms.bool(False),
    ZS_threshold = cms.uint32(1),
    applySaturationFix = cms.bool(True),
    inputLabel = cms.VInputTag("unpackHcal", "unpackHcal"),
    inputUpgradeLabel = cms.VInputTag("unpackHcal", "unpackHcal"),
    latency = cms.int32(1),
    numberOfFilterPresamplesHBQIE11 = cms.int32(0),
    numberOfFilterPresamplesHEQIE11 = cms.int32(0),
    numberOfPresamples = cms.int32(2),
    numberOfPresamplesHF = cms.int32(1),
    numberOfSamples = cms.int32(4),
    numberOfSamplesHF = cms.int32(2),
    overrideDBweightsAndFilterHB = cms.bool(False),
    overrideDBweightsAndFilterHE = cms.bool(False),
    peakFilter = cms.bool(True),
    tpScales = cms.PSet(
        HBHE = cms.PSet(
            LSBQIE11 = cms.double(0.0625),
            LSBQIE11Overlap = cms.double(0.0625),
            LSBQIE8 = cms.double(0.125)
        ),
        HF = cms.PSet(
            NCTShift = cms.int32(2),
            RCTShift = cms.int32(3)
        )
    ),
    upgradeHB = cms.bool(True),
    upgradeHE = cms.bool(True),
    upgradeHF = cms.bool(True),
    useTDCInMinBiasBits = cms.bool(False),
    weights = cms.vdouble(1.0, 1.0),
    weightsQIE11 = cms.PSet(
        ieta1 = cms.vint32(255, 255),
        ieta10 = cms.vint32(255, 255),
        ieta11 = cms.vint32(255, 255),
        ieta12 = cms.vint32(255, 255),
        ieta13 = cms.vint32(255, 255),
        ieta14 = cms.vint32(255, 255),
        ieta15 = cms.vint32(255, 255),
        ieta16 = cms.vint32(255, 255),
        ieta17 = cms.vint32(255, 255),
        ieta18 = cms.vint32(255, 255),
        ieta19 = cms.vint32(255, 255),
        ieta2 = cms.vint32(255, 255),
        ieta20 = cms.vint32(255, 255),
        ieta21 = cms.vint32(255, 255),
        ieta22 = cms.vint32(255, 255),
        ieta23 = cms.vint32(255, 255),
        ieta24 = cms.vint32(255, 255),
        ieta25 = cms.vint32(255, 255),
        ieta26 = cms.vint32(255, 255),
        ieta27 = cms.vint32(255, 255),
        ieta28 = cms.vint32(255, 255),
        ieta3 = cms.vint32(255, 255),
        ieta4 = cms.vint32(255, 255),
        ieta5 = cms.vint32(255, 255),
        ieta6 = cms.vint32(255, 255),
        ieta7 = cms.vint32(255, 255),
        ieta8 = cms.vint32(255, 255),
        ieta9 = cms.vint32(255, 255)
    )
)


process.simKBmtfDigis = cms.EDProducer("L1TMuonBarrelKalmanTrackProducer",
    algoSettings = cms.PSet(
        aPhi = cms.vdouble(1.942, 0.01511, 0.01476, 0.009799),
        aPhiB = cms.vdouble(-1.508, -0.1237, -0.1496, -0.1333),
        aPhiBNLO = cms.vdouble(0.000331, 0, 0, 0),
        bPhi = cms.vdouble(-1, 0.18245, 0.20898, 0.17286),
        bPhiB = cms.vdouble(-1, 1.18245, 1.20898, 1.17286),
        chiSquare = cms.vdouble(0.0, 0.109375, 0.234375, 0.359375),
        chiSquareCut = cms.vint32(126, 126, 126, 126, 126),
        chiSquareCutCurvMax = cms.vint32(2500, 2500, 2500, 2500, 2500),
        chiSquareCutPattern = cms.vint32(7, 11, 13, 14, 15),
        chiSquareCutTight = cms.vint32(
            40, 126, 60, 126, 126,
            126
        ),
        combos1 = cms.vint32(),
        combos2 = cms.vint32(3),
        combos3 = cms.vint32(5, 6, 7),
        combos4 = cms.vint32(
            9, 10, 11, 12, 13,
            14, 15
        ),
        eLoss = cms.vdouble(0.000765, 0, 0, 0),
        etaLUT0 = cms.vdouble(8.946, 7.508, 6.279, 6.399),
        etaLUT1 = cms.vdouble(0.159, 0.116, 0.088, 0.128),
        initialK = cms.vdouble(-1.196, -1.581, -2.133, -2.263),
        initialK2 = cms.vdouble(-0.000326, -0.0007165, 0.002305, -0.00563),
        lutFile = cms.string('L1Trigger/L1TMuon/data/bmtf_luts/kalmanLUTs_v302.root'),
        mScatteringPhi = cms.vdouble(0.00249, 5.47e-05, 3.49e-05, 1.37e-05),
        mScatteringPhiB = cms.vdouble(0.00722, 0.003461, 0.004447, 0.00412),
        phiAt2 = cms.double(0.15918),
        pointResolutionPhi = cms.double(1.0),
        pointResolutionPhiB = cms.double(500.0),
        pointResolutionPhiBH = cms.vdouble(151.0, 173.0, 155.0, 153.0),
        pointResolutionPhiBL = cms.vdouble(17866.0, 19306.0, 23984.0, 23746.0),
        pointResolutionVertex = cms.double(1.0),
        trackComp = cms.vdouble(1.75, 1.25, 0.625, 0.25),
        trackCompCut = cms.vint32(
            15, 15, 15, 15, 15,
            15
        ),
        trackCompCutCurvMax = cms.vint32(
            34, 34, 34, 34, 34,
            34
        ),
        trackCompCutPattern = cms.vint32(
            3, 5, 6, 9, 10,
            12
        ),
        trackCompErr1 = cms.vdouble(2.0, 2.0, 2.0, 2.0),
        trackCompErr2 = cms.vdouble(0.21875, 0.21875, 0.21875, 0.3125),
        useOfflineAlgo = cms.bool(False),
        verbose = cms.bool(False)
    ),
    bx = cms.vint32(-2, -1, 0, 1, 2),
    src = cms.InputTag("simKBmtfStubs"),
    trackFinderSettings = cms.PSet(
        sectorSettings = cms.PSet(
            regionSettings = cms.PSet(
                verbose = cms.int32(0)
            ),
            verbose = cms.int32(0),
            wheelsToProcess = cms.vint32(-2, -1, 0, 1, 2)
        ),
        sectorsToProcess = cms.vint32(
            0, 1, 2, 3, 4,
            5, 6, 7, 8, 9,
            10, 11
        ),
        verbose = cms.int32(0)
    )
)


process.simKBmtfStubs = cms.EDProducer("L1TMuonBarrelKalmanStubProducer",
    cotTheta_1 = cms.vint32(
        105, 101, 97, 93, 88,
        84, 79, 69, 64, 58,
        52, 46, 40, 34, 21,
        14, 7, 0, -7, -14,
        -21, -34, -40, -46, -52,
        -58, -64, -69, -79, -84,
        -88, -93, -97, -101, -105
    ),
    cotTheta_2 = cms.vint32(
        93, 89, 85, 81, 77,
        73, 68, 60, 55, 50,
        45, 40, 34, 29, 17,
        12, 6, 0, -6, -12,
        -17, -29, -34, -40, -45,
        -50, -55, -60, -68, -73,
        -77, -81, -85, -89, -93
    ),
    cotTheta_3 = cms.vint32(
        81, 77, 74, 70, 66,
        62, 58, 51, 46, 42,
        38, 33, 29, 24, 15,
        10, 5, 0, -5, -10,
        -15, -24, -29, -33, -38,
        -42, -46, -51, -58, -62,
        -66, -70, -74, -77, -81
    ),
    disableMasks = cms.bool(False),
    maxBX = cms.int32(2),
    minBX = cms.int32(-2),
    minPhiQuality = cms.int32(0),
    minThetaQuality = cms.int32(0),
    srcPhi = cms.InputTag("simTwinMuxDigis"),
    srcTheta = cms.InputTag("simDtTriggerPrimitiveDigis"),
    verbose = cms.int32(0)
)


process.simMuonGEMPadDigiClusters = cms.EDProducer("GEMPadDigiClusterProducer",
    InputCollection = cms.InputTag("simMuonGEMPadDigis"),
    maxClusterSize = cms.uint32(8),
    maxClustersOHGE11 = cms.uint32(8),
    maxClustersOHGE21 = cms.uint32(8),
    maxClustersPartitionGE11 = cms.uint32(4),
    maxClustersPartitionGE21 = cms.uint32(4),
    mightGet = cms.optional.untracked.vstring,
    nOHGE11 = cms.uint32(1),
    nOHGE21 = cms.uint32(4),
    nPartitionsGE11 = cms.uint32(4),
    nPartitionsGE21 = cms.uint32(4),
    sendOverflowClusters = cms.bool(False)
)


process.simMuonGEMPadDigis = cms.EDProducer("GEMPadDigiProducer",
    InputCollection = cms.InputTag("simMuonGEMDigis"),
    mightGet = cms.optional.untracked.vstring
)


process.simOmtfDigis = cms.EDProducer("L1TMuonOverlapPhase1TrackProducer",
    XMLDumpFileName = cms.string('TestEvents.xml'),
    bxMax = cms.int32(0),
    bxMin = cms.int32(0),
    dropCSCPrimitives = cms.bool(False),
    dropDTPrimitives = cms.bool(False),
    dropRPCPrimitives = cms.bool(False),
    dumpDetailedResultToXML = cms.bool(False),
    dumpGPToXML = cms.bool(False),
    dumpResultToXML = cms.bool(False),
    eventsXMLFiles = cms.vstring('TestEvents.xml'),
    processorType = cms.string('OMTFProcessor'),
    readEventsFromXML = cms.bool(False),
    srcCSC = cms.InputTag("simCscTriggerPrimitiveDigis","MPCSORTED"),
    srcDTPh = cms.InputTag("simDtTriggerPrimitiveDigis"),
    srcDTTh = cms.InputTag("simDtTriggerPrimitiveDigis"),
    srcRPC = cms.InputTag("unpackRPC")
)


process.simTwinMuxDigis = cms.EDProducer("L1TTwinMuxProducer",
    DTDigi_Source = cms.InputTag("simDtTriggerPrimitiveDigis"),
    DTThetaDigi_Source = cms.InputTag("simDtTriggerPrimitiveDigis"),
    RPC_Source = cms.InputTag("unpackRPC")
)


process.unpackCSC = cms.EDProducer("CSCDCCUnpacker",
    B904Setup = cms.untracked.bool(False),
    B904dmb = cms.untracked.int32(3),
    B904vmecrate = cms.untracked.int32(1),
    Debug = cms.untracked.bool(False),
    DisableMappingCheck = cms.untracked.bool(False),
    ErrorMask = cms.uint32(0),
    ExaminerMask = cms.uint32(535558134),
    FormatedEventDump = cms.untracked.bool(False),
    InputObjects = cms.InputTag("rawDataCollector","","@skipCurrentProcess"),
    PrintEventNumber = cms.untracked.bool(False),
    SuppressZeroLCT = cms.untracked.bool(True),
    UnpackStatusDigis = cms.bool(False),
    UseExaminer = cms.bool(True),
    UseFormatStatus = cms.bool(True),
    UseSelectiveUnpacking = cms.bool(True),
    VisualFEDInspect = cms.untracked.bool(False),
    VisualFEDShort = cms.untracked.bool(False),
    mightGet = cms.optional.untracked.vstring,
    runDQM = cms.untracked.bool(False),
    useCSCShowers = cms.bool(True),
    useGEMs = cms.bool(True),
    useRPCs = cms.bool(False)
)


process.unpackDT = cms.EDProducer("DTuROSRawToDigi",
    debug = cms.untracked.bool(False),
    inputLabel = cms.InputTag("rawDataCollector","","@skipCurrentProcess")
)


process.unpackEcal = cms.EDProducer("EcalRawToDigi",
    DoRegional = cms.bool(False),
    FEDs = cms.vint32(
        601, 602, 603, 604, 605,
        606, 607, 608, 609, 610,
        611, 612, 613, 614, 615,
        616, 617, 618, 619, 620,
        621, 622, 623, 624, 625,
        626, 627, 628, 629, 630,
        631, 632, 633, 634, 635,
        636, 637, 638, 639, 640,
        641, 642, 643, 644, 645,
        646, 647, 648, 649, 650,
        651, 652, 653, 654
    ),
    FedLabel = cms.InputTag("listfeds"),
    InputLabel = cms.InputTag("rawDataCollector","","@skipCurrentProcess"),
    eventPut = cms.bool(True),
    feIdCheck = cms.bool(True),
    feUnpacking = cms.bool(True),
    forceToKeepFRData = cms.bool(False),
    headerUnpacking = cms.bool(True),
    memUnpacking = cms.bool(True),
    mightGet = cms.optional.untracked.vstring,
    numbTriggerTSamples = cms.int32(1),
    numbXtalTSamples = cms.int32(10),
    orderedDCCIdList = cms.vint32(
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25,
        26, 27, 28, 29, 30,
        31, 32, 33, 34, 35,
        36, 37, 38, 39, 40,
        41, 42, 43, 44, 45,
        46, 47, 48, 49, 50,
        51, 52, 53, 54
    ),
    orderedFedList = cms.vint32(
        601, 602, 603, 604, 605,
        606, 607, 608, 609, 610,
        611, 612, 613, 614, 615,
        616, 617, 618, 619, 620,
        621, 622, 623, 624, 625,
        626, 627, 628, 629, 630,
        631, 632, 633, 634, 635,
        636, 637, 638, 639, 640,
        641, 642, 643, 644, 645,
        646, 647, 648, 649, 650,
        651, 652, 653, 654
    ),
    silentMode = cms.untracked.bool(True),
    srpUnpacking = cms.bool(True),
    syncCheck = cms.bool(True),
    tccUnpacking = cms.bool(True)
)


process.unpackHcal = cms.EDProducer("HcalRawToDigi",
    ComplainEmptyData = cms.untracked.bool(False),
    ElectronicsMap = cms.string(''),
    ExpectedOrbitMessageTime = cms.untracked.int32(-1),
    FEDs = cms.untracked.vint32(),
    FilterDataQuality = cms.bool(True),
    HcalFirstFED = cms.untracked.int32(700),
    InputLabel = cms.InputTag("rawDataCollector","","@skipCurrentProcess"),
    UnpackCalib = cms.untracked.bool(True),
    UnpackTTP = cms.untracked.bool(True),
    UnpackUMNio = cms.untracked.bool(True),
    UnpackZDC = cms.untracked.bool(True),
    UnpackerMode = cms.untracked.int32(0),
    firstSample = cms.int32(0),
    lastSample = cms.int32(9),
    mightGet = cms.optional.untracked.vstring,
    saveQIE10DataNSamples = cms.untracked.vint32(),
    saveQIE10DataTags = cms.untracked.vstring(),
    saveQIE11DataNSamples = cms.untracked.vint32(),
    saveQIE11DataTags = cms.untracked.vstring(),
    silent = cms.untracked.bool(True)
)


process.unpackRPC = cms.EDProducer("RPCUnpackingModule",
    InputLabel = cms.InputTag("rawDataCollector","","@skipCurrentProcess"),
    doSynchro = cms.bool(True),
    mightGet = cms.optional.untracked.vstring
)


process.hltEcalDigis = SwitchProducerCUDA(
    cpu = cms.EDAlias(
        hltEcalDigisLegacy = cms.VPSet(
            cms.PSet(
                type = cms.string('EBDigiCollection')
            ),
            cms.PSet(
                type = cms.string('EEDigiCollection')
            ),
            cms.PSet(
                type = cms.string('EBDetIdedmEDCollection')
            ),
            cms.PSet(
                type = cms.string('EEDetIdedmEDCollection')
            ),
            cms.PSet(
                type = cms.string('EBSrFlagsSorted')
            ),
            cms.PSet(
                type = cms.string('EESrFlagsSorted')
            ),
            cms.PSet(
                fromProductInstance = cms.string('EcalIntegrityBlockSizeErrors'),
                type = cms.string('EcalElectronicsIdedmEDCollection')
            ),
            cms.PSet(
                fromProductInstance = cms.string('EcalIntegrityTTIdErrors'),
                type = cms.string('EcalElectronicsIdedmEDCollection')
            ),
            cms.PSet(
                fromProductInstance = cms.string('EcalIntegrityZSXtalIdErrors'),
                type = cms.string('EcalElectronicsIdedmEDCollection')
            ),
            cms.PSet(
                type = cms.string('EcalPnDiodeDigisSorted')
            ),
            cms.PSet(
                fromProductInstance = cms.string('EcalPseudoStripInputs'),
                type = cms.string('EcalPseudoStripInputDigisSorted')
            ),
            cms.PSet(
                fromProductInstance = cms.string('EcalTriggerPrimitives'),
                type = cms.string('EcalTriggerPrimitiveDigisSorted')
            )
        )
    ),
    cuda = cms.EDAlias(
        hltEcalDigisFromGPU = cms.VPSet(cms.PSet(
            type = cms.string('*')
        ))
    )
)


process.hltEcalRecHit = SwitchProducerCUDA(
    cpu = cms.EDAlias(
        hltEcalRecHitWithTPs = cms.VPSet(cms.PSet(
            type = cms.string('*')
        ))
    ),
    cuda = cms.EDAlias(
        hltEcalRecHitWithoutTPs = cms.VPSet(cms.PSet(
            type = cms.string('*')
        ))
    )
)


process.hltEcalUncalibRecHit = SwitchProducerCUDA(
    cpu = cms.EDAlias(
        hltEcalUncalibRecHitLegacy = cms.VPSet(cms.PSet(
            type = cms.string('*')
        ))
    ),
    cuda = cms.EDAlias(
        hltEcalUncalibRecHitFromSoA = cms.VPSet(cms.PSet(
            type = cms.string('*')
        ))
    )
)


process.hltHbhereco = SwitchProducerCUDA(
    cpu = cms.EDAlias(
        hltHbherecoLegacy = cms.VPSet(cms.PSet(
            type = cms.string('*')
        ))
    ),
    cuda = cms.EDAlias(
        hltHbherecoFromGPU = cms.VPSet(cms.PSet(
            type = cms.string('HBHERecHitsSorted')
        ))
    )
)


process.hltAK4CaloJetsPFEt5 = cms.EDFilter("EtMinCaloJetSelector",
    etMin = cms.double(5.0),
    filter = cms.bool(False),
    src = cms.InputTag("hltAK4CaloJetsPF")
)


process.hltBoolEnd = cms.EDFilter("HLTBool",
    result = cms.bool(True)
)


process.hltBoolFalse = cms.EDFilter("HLTBool",
    result = cms.bool(False)
)


process.hltJetsForCoreTracking = cms.EDFilter("CandPtrSelector",
    cut = cms.string('pt > 100 && abs(eta) < 2.5'),
    src = cms.InputTag("hltPuAK4CaloJetsCorrectedIDPassed")
)


process.hltL1sSingleJet28BptxAND = cms.EDFilter("HLTL1TSeed",
    L1EGammaInputTag = cms.InputTag("hltGtStage2Digis","EGamma"),
    L1EtSumInputTag = cms.InputTag("hltGtStage2Digis","EtSum"),
    L1GlobalInputTag = cms.InputTag("hltGtStage2Digis"),
    L1JetInputTag = cms.InputTag("hltGtStage2Digis","Jet"),
    L1MuonInputTag = cms.InputTag("hltGtStage2Digis","Muon"),
    L1MuonShowerInputTag = cms.InputTag("hltGtStage2Digis","MuonShower"),
    L1ObjectMapInputTag = cms.InputTag("hltGtStage2ObjectMap"),
    L1SeedsLogicalExpression = cms.string('L1_AlwaysTrue'),
    L1TauInputTag = cms.InputTag("hltGtStage2Digis","Tau"),
    saveTags = cms.bool(True)
)


process.hltL1sSingleJet44BptxAND = cms.EDFilter("HLTL1TSeed",
    L1EGammaInputTag = cms.InputTag("hltGtStage2Digis","EGamma"),
    L1EtSumInputTag = cms.InputTag("hltGtStage2Digis","EtSum"),
    L1GlobalInputTag = cms.InputTag("hltGtStage2Digis"),
    L1JetInputTag = cms.InputTag("hltGtStage2Digis","Jet"),
    L1MuonInputTag = cms.InputTag("hltGtStage2Digis","Muon"),
    L1MuonShowerInputTag = cms.InputTag("hltGtStage2Digis","MuonShower"),
    L1ObjectMapInputTag = cms.InputTag("hltGtStage2ObjectMap"),
    L1SeedsLogicalExpression = cms.string('L1_AlwaysTrue'),
    L1TauInputTag = cms.InputTag("hltGtStage2Digis","Tau"),
    saveTags = cms.bool(True)
)


process.hltPreHICsAK4PFJet60Eta1p5 = cms.EDFilter("HLTPrescaler",
    L1GtReadoutRecordTag = cms.InputTag("hltGtStage2Digis"),
    offset = cms.uint32(0)
)


process.hltPreHIPuAK4CaloJet40Eta5p1 = cms.EDFilter("HLTPrescaler",
    L1GtReadoutRecordTag = cms.InputTag("hltGtStage2Digis"),
    offset = cms.uint32(0)
)


process.hltSingleCsPFJet60Eta1p5 = cms.EDFilter("HLT1PFJet",
    MaxEta = cms.double(5.1),
    MaxMass = cms.double(-1.0),
    MinE = cms.double(-1.0),
    MinEta = cms.double(-1.0),
    MinMass = cms.double(-1.0),
    MinN = cms.int32(1),
    MinPt = cms.double(0.0),
    inputTag = cms.InputTag("hltAK4PFJets"),
    saveTags = cms.bool(True),
    triggerType = cms.int32(85)
)


process.hltSinglePuAK4CaloJet40Eta5p1 = cms.EDFilter("HLT1CaloJet",
    MaxEta = cms.double(5.1),
    MaxMass = cms.double(-1.0),
    MinE = cms.double(-1.0),
    MinEta = cms.double(-1.0),
    MinMass = cms.double(-1.0),
    MinN = cms.int32(1),
    MinPt = cms.double(0.0),
    inputTag = cms.InputTag("hltPuAK4CaloJets"),
    saveTags = cms.bool(True),
    triggerType = cms.int32(85)
)


process.hltTriggerType = cms.EDFilter("HLTTriggerTypeFilter",
    SelectedTriggerType = cms.int32(1)
)


process.hltGetRaw = cms.EDAnalyzer("HLTGetRaw",
    RawDataCollection = cms.InputTag("rawDataCollector")
)


process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('output.root'),
    outputCommands = cms.untracked.vstring(
        'drop *',
        'keep *_TriggerResults_*_*',
        'keep *_hltTriggerSummaryAOD_*_*',
        'keep *_hltGtStage2Digis_*_*',
        'keep *_hltGtStage2ObjectMap_*_*'
    )
)


process.CUDAService = cms.Service("CUDAService",
    allocator = cms.untracked.PSet(
        devicePreallocate = cms.untracked.vuint32(),
        hostPreallocate = cms.untracked.vuint32()
    ),
    enabled = cms.untracked.bool(True),
    limits = cms.untracked.PSet(
        cudaLimitDevRuntimePendingLaunchCount = cms.untracked.int32(-1),
        cudaLimitDevRuntimeSyncDepth = cms.untracked.int32(-1),
        cudaLimitMallocHeapSize = cms.untracked.int32(-1),
        cudaLimitPrintfFifoSize = cms.untracked.int32(-1),
        cudaLimitStackSize = cms.untracked.int32(-1)
    ),
    verbose = cms.untracked.bool(False)
)


process.FastTimerService = cms.Service("FastTimerService",
    dqmLumiSectionsRange = cms.untracked.uint32(2500),
    dqmMemoryRange = cms.untracked.double(1000000.0),
    dqmMemoryResolution = cms.untracked.double(5000.0),
    dqmModuleMemoryRange = cms.untracked.double(100000.0),
    dqmModuleMemoryResolution = cms.untracked.double(500.0),
    dqmModuleTimeRange = cms.untracked.double(40.0),
    dqmModuleTimeResolution = cms.untracked.double(0.2),
    dqmPath = cms.untracked.string('HLT/TimerService'),
    dqmPathMemoryRange = cms.untracked.double(1000000.0),
    dqmPathMemoryResolution = cms.untracked.double(5000.0),
    dqmPathTimeRange = cms.untracked.double(100.0),
    dqmPathTimeResolution = cms.untracked.double(0.5),
    dqmTimeRange = cms.untracked.double(2000.0),
    dqmTimeResolution = cms.untracked.double(5.0),
    enableDQM = cms.untracked.bool(True),
    enableDQMTransitions = cms.untracked.bool(False),
    enableDQMbyLumiSection = cms.untracked.bool(True),
    enableDQMbyModule = cms.untracked.bool(False),
    enableDQMbyPath = cms.untracked.bool(False),
    enableDQMbyProcesses = cms.untracked.bool(True),
    jsonFileName = cms.untracked.string('resources.json'),
    printEventSummary = cms.untracked.bool(False),
    printJobSummary = cms.untracked.bool(True),
    printRunSummary = cms.untracked.bool(True),
    writeJSONSummary = cms.untracked.bool(False)
)


process.MessageLogger = cms.Service("MessageLogger",
    FastReport = cms.untracked.PSet(

    ),
    HLTrigReport = cms.untracked.PSet(

    ),
    L1GtTrigReport = cms.untracked.PSet(

    ),
    L1TGlobalSummary = cms.untracked.PSet(

    ),
    ThroughputService = cms.untracked.PSet(

    ),
    TriggerSummaryProducerAOD = cms.untracked.PSet(

    ),
    cerr = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        FwkReport = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            reportEvery = cms.untracked.int32(1)
        ),
        FwkSummary = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            reportEvery = cms.untracked.int32(1)
        ),
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        noTimeStamps = cms.untracked.bool(False),
        threshold = cms.untracked.string('INFO')
    ),
    debugModules = cms.untracked.vstring(),
    suppressDebug = cms.untracked.vstring(),
    suppressFwkInfo = cms.untracked.vstring(),
    suppressInfo = cms.untracked.vstring(),
    suppressWarning = cms.untracked.vstring(
        'hltOnlineBeamSpot',
        'hltCtf3HitL1SeededWithMaterialTracks',
        'hltL3MuonsOIState',
        'hltPixelTracksForHighMult',
        'hltHITPixelTracksHE',
        'hltHITPixelTracksHB',
        'hltCtfL1SeededWithMaterialTracks',
        'hltRegionalTracksForL3MuonIsolation',
        'hltSiPixelClusters',
        'hltActivityStartUpElectronPixelSeeds',
        'hltLightPFTracks',
        'hltPixelVertices3DbbPhi',
        'hltL3MuonsIOHit',
        'hltPixelTracks',
        'hltSiPixelDigis',
        'hltL3MuonsOIHit',
        'hltL1SeededElectronGsfTracks',
        'hltL1SeededStartUpElectronPixelSeeds',
        'hltBLifetimeRegionalCtfWithMaterialTracksbbPhiL1FastJetFastPV',
        'hltCtfActivityWithMaterialTracks'
    )
)


process.ThroughputService = cms.Service("ThroughputService",
    dqmPath = cms.untracked.string('HLT/Throughput'),
    dqmPathByProcesses = cms.untracked.bool(False),
    enableDQM = cms.untracked.bool(True),
    eventRange = cms.untracked.uint32(10000),
    eventResolution = cms.untracked.uint32(1),
    printEventSummary = cms.untracked.bool(False),
    timeRange = cms.untracked.double(60000.0),
    timeResolution = cms.untracked.double(5.828)
)


process.ProcessAcceleratorCUDA = ProcessAcceleratorCUDA()


process.AnyDirectionAnalyticalPropagator = cms.ESProducer("AnalyticalPropagatorESProducer",
    ComponentName = cms.string('AnyDirectionAnalyticalPropagator'),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('anyDirection')
)


process.CSCChannelMapperESProducer = cms.ESProducer("CSCChannelMapperESProducer",
    AlgoName = cms.string('CSCChannelMapperPostls1')
)


process.CSCGeometryESModule = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    debugV = cms.untracked.bool(False),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useGangedStripsInME1a = cms.bool(False),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.CSCIndexerESProducer = cms.ESProducer("CSCIndexerESProducer",
    AlgoName = cms.string('CSCIndexerPostls1')
)


process.CSCObjectMapESProducer = cms.ESProducer("CSCObjectMapESProducer",
    appendToDataLabel = cms.string('')
)


process.CaloGeometryBuilder = cms.ESProducer("CaloGeometryBuilder",
    SelectedCalos = cms.vstring(
        'HCAL',
        'ZDC',
        'EcalBarrel',
        'EcalEndcap',
        'EcalPreshower',
        'TOWER'
    )
)


process.CaloTPGTranscoder = cms.ESProducer("CaloTPGTranscoderULUTs",
    LUTfactor = cms.vint32(1, 2, 5, 0),
    RCTLSB = cms.double(0.25),
    ZS = cms.vint32(4, 2, 1, 0),
    hcalLUT1 = cms.FileInPath('CalibCalorimetry/CaloTPG/data/outputLUTtranscoder_physics.dat'),
    hcalLUT2 = cms.FileInPath('CalibCalorimetry/CaloTPG/data/TPGcalcDecompress2.txt'),
    ietaLowerBound = cms.vint32(1, 18, 27, 29),
    ietaUpperBound = cms.vint32(17, 26, 28, 32),
    linearLUTs = cms.bool(True),
    nominal_gain = cms.double(0.177),
    read_Ascii_Compression_LUTs = cms.bool(False),
    read_Ascii_RCT_LUTs = cms.bool(False),
    tpScales = cms.PSet(
        HBHE = cms.PSet(
            LSBQIE11 = cms.double(0.0625),
            LSBQIE11Overlap = cms.double(0.0625),
            LSBQIE8 = cms.double(0.125)
        ),
        HF = cms.PSet(
            NCTShift = cms.int32(2),
            RCTShift = cms.int32(3)
        )
    )
)


process.CaloTopologyBuilder = cms.ESProducer("CaloTopologyBuilder")


process.CaloTowerConstituentsMapBuilder = cms.ESProducer("CaloTowerConstituentsMapBuilder",
    MapAuto = cms.untracked.bool(False),
    MapFile = cms.untracked.string('Geometry/CaloTopology/data/CaloTowerEEGeometric.map.gz'),
    SkipHE = cms.untracked.bool(False),
    appendToDataLabel = cms.string('')
)


process.CaloTowerGeometryFromDBEP = cms.ESProducer("CaloTowerGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.CaloTowerTopologyEP = cms.ESProducer("CaloTowerTopologyEP",
    appendToDataLabel = cms.string('')
)


process.CastorDbProducer = cms.ESProducer("CastorDbProducer",
    appendToDataLabel = cms.string('')
)


process.ClusterShapeHitFilterESProducer = cms.ESProducer("ClusterShapeHitFilterESProducer",
    ComponentName = cms.string('ClusterShapeHitFilter'),
    PixelShapeFile = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_noL1.par'),
    PixelShapeFileL1 = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_loose.par'),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    doPixelShapeCut = cms.bool(True),
    doStripShapeCut = cms.bool(True),
    isPhase2 = cms.bool(False)
)


process.DTGeometryESModule = cms.ESProducer("DTGeometryESModule",
    DDDetector = cms.ESInputTag("",""),
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    attribute = cms.string('MuStructure'),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False),
    value = cms.string('MuonBarrelDT')
)


process.DTObjectMapESProducer = cms.ESProducer("DTObjectMapESProducer",
    appendToDataLabel = cms.string('')
)


process.EcalBarrelGeometryFromDBEP = cms.ESProducer("EcalBarrelGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalElectronicsMappingBuilder = cms.ESProducer("EcalElectronicsMappingBuilder")


process.EcalEndcapGeometryFromDBEP = cms.ESProducer("EcalEndcapGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.EcalLaserCorrectionService = cms.ESProducer("EcalLaserCorrectionService",
    appendToDataLabel = cms.string(''),
    maxExtrapolationTimeInSec = cms.uint32(0)
)


process.EcalPreshowerGeometryFromDBEP = cms.ESProducer("EcalPreshowerGeometryFromDBEP",
    applyAlignment = cms.bool(True)
)


process.GEMGeometryESModule = cms.ESProducer("GEMGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(False),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False)
)


process.GlobalParameters = cms.ESProducer("StableParametersTrivialProducer",
    IfCaloEtaNumberBits = cms.uint32(4),
    IfMuEtaNumberBits = cms.uint32(6),
    NumberChips = cms.uint32(1),
    NumberConditionChips = cms.uint32(1),
    NumberL1CenJet = cms.uint32(4),
    NumberL1EGamma = cms.uint32(12),
    NumberL1ForJet = cms.uint32(4),
    NumberL1IsoEG = cms.uint32(4),
    NumberL1Jet = cms.uint32(12),
    NumberL1JetCounts = cms.uint32(12),
    NumberL1Mu = cms.uint32(4),
    NumberL1Muon = cms.uint32(8),
    NumberL1NoIsoEG = cms.uint32(4),
    NumberL1Tau = cms.uint32(12),
    NumberL1TauJet = cms.uint32(4),
    NumberPhysTriggers = cms.uint32(512),
    NumberPhysTriggersExtended = cms.uint32(64),
    NumberPsbBoards = cms.int32(7),
    NumberTechnicalTriggers = cms.uint32(64),
    OrderConditionChip = cms.vint32(1),
    OrderOfChip = cms.vint32(1),
    PinsOnChip = cms.uint32(512),
    PinsOnConditionChip = cms.uint32(512),
    TotalBxInEvent = cms.int32(5),
    UnitLength = cms.int32(8),
    WordLength = cms.int32(64),
    appendToDataLabel = cms.string('')
)


process.HcalGeometryFromDBEP = cms.ESProducer("HcalGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.HcalTPGCoderULUT = cms.ESProducer("HcalTPGCoderULUT",
    FGLUTs = cms.FileInPath('CalibCalorimetry/HcalTPGAlgos/data/HBHE_FG_LUT.dat'),
    FG_HF_thresholds = cms.vuint32(17, 255),
    LUTGenerationMode = cms.bool(True),
    MaskBit = cms.int32(32768),
    RCalibFile = cms.FileInPath('CalibCalorimetry/HcalTPGAlgos/data/RecHit-TPG-calib.dat'),
    applyFixPCC = cms.bool(True),
    contain1TSHB = cms.bool(False),
    contain1TSHE = cms.bool(False),
    containPhaseNSHB = cms.double(6.0),
    containPhaseNSHE = cms.double(6.0),
    inputLUTs = cms.FileInPath('CalibCalorimetry/HcalTPGAlgos/data/inputLUTcoder_physics.dat'),
    linearLUTs = cms.bool(True),
    overrideDBweightsAndFilterHB = cms.bool(False),
    overrideDBweightsAndFilterHE = cms.bool(False),
    read_Ascii_LUTs = cms.bool(False),
    read_FG_LUTs = cms.bool(False),
    read_XML_LUTs = cms.bool(False),
    tpScales = cms.PSet(
        HBHE = cms.PSet(
            LSBQIE11 = cms.double(0.0625),
            LSBQIE11Overlap = cms.double(0.0625),
            LSBQIE8 = cms.double(0.125)
        ),
        HF = cms.PSet(
            NCTShift = cms.int32(2),
            RCTShift = cms.int32(3)
        )
    )
)


process.HcalTopologyIdealEP = cms.ESProducer("HcalTopologyIdealEP",
    Exclude = cms.untracked.string(''),
    MergePosition = cms.untracked.bool(True),
    appendToDataLabel = cms.string('')
)


process.HcalTrigTowerGeometryESProducer = cms.ESProducer("HcalTrigTowerGeometryESProducer")


process.L1DTConfigFromDB = cms.ESProducer("DTConfigDBProducer",
    DTTPGMap = cms.untracked.PSet(
    **dict(
        [
            ("wh0st1se1" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se10" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se11" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se12" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se2" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se3" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se4" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se5" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se6" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se7" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se8" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st1se9" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh0st2se1" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se10" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se11" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se12" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se2" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se3" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se4" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se5" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se6" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se7" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se8" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st2se9" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh0st3se1" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se10" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se11" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se12" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se2" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se3" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se4" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se5" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se6" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se7" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se8" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st3se9" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh0st4se1" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh0st4se10" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("wh0st4se11" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("wh0st4se12" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("wh0st4se13" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("wh0st4se14" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("wh0st4se2" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh0st4se3" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh0st4se4" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("wh0st4se5" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh0st4se6" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh0st4se7" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh0st4se8" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("wh0st4se9" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("wh1st1se1" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se10" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se11" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se12" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se2" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se3" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se4" , cms.untracked.vint32(50, 48, 50, 13) ),
            ("wh1st1se5" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se6" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se7" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se8" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st1se9" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh1st2se1" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se10" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se11" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se12" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se2" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se3" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se4" , cms.untracked.vint32(60, 48, 60, 15) ),
            ("wh1st2se5" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se6" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se7" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se8" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st2se9" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh1st3se1" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se10" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se11" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se12" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se2" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se3" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se4" , cms.untracked.vint32(72, 48, 72, 18) ),
            ("wh1st3se5" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se6" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se7" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se8" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st3se9" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh1st4se1" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh1st4se10" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("wh1st4se11" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("wh1st4se12" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("wh1st4se13" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("wh1st4se14" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("wh1st4se2" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh1st4se3" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh1st4se4" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("wh1st4se5" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh1st4se6" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh1st4se7" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh1st4se8" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("wh1st4se9" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("wh2st1se1" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se10" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se11" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se12" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se2" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se3" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se4" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se5" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se6" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se7" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se8" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st1se9" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("wh2st2se1" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se10" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se11" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se12" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se2" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se3" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se4" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se5" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se6" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se7" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se8" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st2se9" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("wh2st3se1" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se10" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se11" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se12" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se2" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se3" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se4" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se5" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se6" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se7" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se8" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st3se9" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("wh2st4se1" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh2st4se10" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("wh2st4se11" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("wh2st4se12" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("wh2st4se13" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("wh2st4se14" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("wh2st4se2" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh2st4se3" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh2st4se4" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("wh2st4se5" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh2st4se6" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh2st4se7" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("wh2st4se8" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("wh2st4se9" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("whm1st1se1" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se10" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se11" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se12" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se2" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se3" , cms.untracked.vint32(50, 48, 50, 13) ),
            ("whm1st1se4" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se5" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se6" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se7" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se8" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st1se9" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm1st2se1" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se10" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se11" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se12" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se2" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se3" , cms.untracked.vint32(60, 48, 60, 15) ),
            ("whm1st2se4" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se5" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se6" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se7" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se8" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st2se9" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm1st3se1" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se10" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se11" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se12" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se2" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se3" , cms.untracked.vint32(72, 48, 72, 18) ),
            ("whm1st3se4" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se5" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se6" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se7" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se8" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st3se9" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm1st4se1" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm1st4se10" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("whm1st4se11" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("whm1st4se12" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("whm1st4se13" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("whm1st4se14" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("whm1st4se2" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm1st4se3" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm1st4se4" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("whm1st4se5" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm1st4se6" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm1st4se7" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm1st4se8" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("whm1st4se9" , cms.untracked.vint32(48, 0, 48, 12) ),
        ] +
        [
            ("whm2st1se1" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se10" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se11" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se12" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se2" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se3" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se4" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se5" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se6" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se7" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se8" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st1se9" , cms.untracked.vint32(50, 58, 50, 13) ),
            ("whm2st2se1" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se10" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se11" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se12" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se2" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se3" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se4" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se5" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se6" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se7" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se8" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st2se9" , cms.untracked.vint32(60, 58, 60, 15) ),
            ("whm2st3se1" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se10" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se11" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se12" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se2" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se3" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se4" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se5" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se6" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se7" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se8" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st3se9" , cms.untracked.vint32(72, 58, 72, 18) ),
            ("whm2st4se1" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm2st4se10" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("whm2st4se11" , cms.untracked.vint32(48, 0, 48, 12) ),
            ("whm2st4se12" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("whm2st4se13" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("whm2st4se14" , cms.untracked.vint32(60, 0, 60, 15) ),
            ("whm2st4se2" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm2st4se3" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm2st4se4" , cms.untracked.vint32(72, 0, 72, 18) ),
            ("whm2st4se5" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm2st4se6" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm2st4se7" , cms.untracked.vint32(96, 0, 96, 24) ),
            ("whm2st4se8" , cms.untracked.vint32(92, 0, 92, 23) ),
            ("whm2st4se9" , cms.untracked.vint32(48, 0, 48, 12) ),
            ]
        )
    ),
    DTTPGParameters = cms.PSet(
        Debug = cms.untracked.bool(False),
        SectCollParameters = cms.PSet(
            Debug = cms.untracked.bool(False),
            SCCSP1 = cms.int32(0),
            SCCSP2 = cms.int32(0),
            SCCSP3 = cms.int32(0),
            SCCSP4 = cms.int32(0),
            SCCSP5 = cms.int32(0),
            SCECF1 = cms.bool(False),
            SCECF2 = cms.bool(False),
            SCECF3 = cms.bool(False),
            SCECF4 = cms.bool(False)
        ),
        TUParameters = cms.PSet(
            BtiParameters = cms.PSet(
                AC1 = cms.int32(0),
                AC2 = cms.int32(3),
                ACH = cms.int32(1),
                ACL = cms.int32(2),
                CH = cms.int32(41),
                CL = cms.int32(22),
                DEAD = cms.int32(31),
                Debug = cms.untracked.int32(0),
                KACCTHETA = cms.int32(1),
                KMAX = cms.int32(64),
                LH = cms.int32(21),
                LL = cms.int32(2),
                LTS = cms.int32(3),
                PTMS0 = cms.int32(0),
                PTMS1 = cms.int32(0),
                PTMS10 = cms.int32(1),
                PTMS11 = cms.int32(1),
                PTMS12 = cms.int32(1),
                PTMS13 = cms.int32(1),
                PTMS14 = cms.int32(1),
                PTMS15 = cms.int32(1),
                PTMS16 = cms.int32(1),
                PTMS17 = cms.int32(1),
                PTMS18 = cms.int32(1),
                PTMS19 = cms.int32(1),
                PTMS2 = cms.int32(0),
                PTMS20 = cms.int32(1),
                PTMS21 = cms.int32(1),
                PTMS22 = cms.int32(1),
                PTMS23 = cms.int32(1),
                PTMS24 = cms.int32(1),
                PTMS25 = cms.int32(1),
                PTMS26 = cms.int32(1),
                PTMS27 = cms.int32(1),
                PTMS28 = cms.int32(1),
                PTMS29 = cms.int32(1),
                PTMS3 = cms.int32(0),
                PTMS30 = cms.int32(0),
                PTMS31 = cms.int32(0),
                PTMS4 = cms.int32(1),
                PTMS5 = cms.int32(1),
                PTMS6 = cms.int32(1),
                PTMS7 = cms.int32(1),
                PTMS8 = cms.int32(1),
                PTMS9 = cms.int32(1),
                RE43 = cms.int32(2),
                RH = cms.int32(61),
                RL = cms.int32(42),
                RON = cms.bool(True),
                SET = cms.int32(7),
                ST43 = cms.int32(42),
                WEN0 = cms.int32(1),
                WEN1 = cms.int32(1),
                WEN2 = cms.int32(1),
                WEN3 = cms.int32(1),
                WEN4 = cms.int32(1),
                WEN5 = cms.int32(1),
                WEN6 = cms.int32(1),
                WEN7 = cms.int32(1),
                WEN8 = cms.int32(1),
                XON = cms.bool(False)
            ),
            Debug = cms.untracked.bool(False),
            LutParameters = cms.PSet(
                BTIC = cms.untracked.int32(0),
                D = cms.untracked.double(0),
                Debug = cms.untracked.bool(False),
                WHEEL = cms.untracked.int32(-1),
                XCN = cms.untracked.double(0)
            ),
            TSPhiParameters = cms.PSet(
                Debug = cms.untracked.bool(False),
                TSMCCE1 = cms.bool(True),
                TSMCCE2 = cms.bool(False),
                TSMCCEC = cms.bool(False),
                TSMCGS1 = cms.bool(True),
                TSMCGS2 = cms.bool(True),
                TSMGS1 = cms.int32(1),
                TSMGS2 = cms.int32(1),
                TSMHSP = cms.int32(1),
                TSMHTE1 = cms.bool(True),
                TSMHTE2 = cms.bool(False),
                TSMHTEC = cms.bool(False),
                TSMMSK1 = cms.int32(312),
                TSMMSK2 = cms.int32(312),
                TSMNOE1 = cms.bool(True),
                TSMNOE2 = cms.bool(False),
                TSMNOEC = cms.bool(False),
                TSMWORD = cms.int32(255),
                TSSCCE1 = cms.bool(True),
                TSSCCE2 = cms.bool(False),
                TSSCCEC = cms.bool(False),
                TSSCGS1 = cms.bool(True),
                TSSCGS2 = cms.bool(True),
                TSSGS1 = cms.int32(1),
                TSSGS2 = cms.int32(1),
                TSSHTE1 = cms.bool(True),
                TSSHTE2 = cms.bool(False),
                TSSHTEC = cms.bool(False),
                TSSMSK1 = cms.int32(312),
                TSSMSK2 = cms.int32(312),
                TSSNOE1 = cms.bool(True),
                TSSNOE2 = cms.bool(False),
                TSSNOEC = cms.bool(False),
                TSTREN0 = cms.bool(True),
                TSTREN1 = cms.bool(True),
                TSTREN10 = cms.bool(True),
                TSTREN11 = cms.bool(True),
                TSTREN12 = cms.bool(True),
                TSTREN13 = cms.bool(True),
                TSTREN14 = cms.bool(True),
                TSTREN15 = cms.bool(True),
                TSTREN16 = cms.bool(True),
                TSTREN17 = cms.bool(True),
                TSTREN18 = cms.bool(True),
                TSTREN19 = cms.bool(True),
                TSTREN2 = cms.bool(True),
                TSTREN20 = cms.bool(True),
                TSTREN21 = cms.bool(True),
                TSTREN22 = cms.bool(True),
                TSTREN23 = cms.bool(True),
                TSTREN3 = cms.bool(True),
                TSTREN4 = cms.bool(True),
                TSTREN5 = cms.bool(True),
                TSTREN6 = cms.bool(True),
                TSTREN7 = cms.bool(True),
                TSTREN8 = cms.bool(True),
                TSTREN9 = cms.bool(True)
            ),
            TSThetaParameters = cms.PSet(
                Debug = cms.untracked.bool(False)
            ),
            TracoParameters = cms.PSet(
                BTIC = cms.int32(32),
                DD = cms.int32(18),
                Debug = cms.untracked.int32(0),
                FHISM = cms.int32(0),
                FHTMSK = cms.int32(0),
                FHTPRF = cms.int32(1),
                FLTMSK = cms.int32(1),
                FPRGCOMP = cms.int32(2),
                FSLMSK = cms.int32(0),
                IBTIOFF = cms.int32(0),
                KPRGCOM = cms.int32(255),
                KRAD = cms.int32(0),
                LTF = cms.int32(0),
                LTS = cms.int32(0),
                LVALIDIFH = cms.int32(0),
                REUSEI = cms.int32(1),
                REUSEO = cms.int32(1),
                SHISM = cms.int32(0),
                SHTMSK = cms.int32(0),
                SHTPRF = cms.int32(1),
                SLTMSK = cms.int32(1),
                SPRGCOMP = cms.int32(2),
                SSLMSK = cms.int32(0),
                TRGENB0 = cms.int32(1),
                TRGENB1 = cms.int32(1),
                TRGENB10 = cms.int32(1),
                TRGENB11 = cms.int32(1),
                TRGENB12 = cms.int32(1),
                TRGENB13 = cms.int32(1),
                TRGENB14 = cms.int32(1),
                TRGENB15 = cms.int32(1),
                TRGENB2 = cms.int32(1),
                TRGENB3 = cms.int32(1),
                TRGENB4 = cms.int32(1),
                TRGENB5 = cms.int32(1),
                TRGENB6 = cms.int32(1),
                TRGENB7 = cms.int32(1),
                TRGENB8 = cms.int32(1),
                TRGENB9 = cms.int32(1)
            )
        )
    ),
    TracoLutsFromDB = cms.bool(True),
    UseBtiAcceptParam = cms.bool(True),
    UseT0 = cms.bool(False),
    bxOffset = cms.int32(19),
    cfgConfig = cms.bool(False),
    debug = cms.bool(False),
    debugBti = cms.int32(0),
    debugDB = cms.bool(False),
    debugLUTs = cms.bool(False),
    debugPed = cms.bool(False),
    debugSC = cms.bool(False),
    debugTSP = cms.bool(False),
    debugTST = cms.bool(False),
    debugTU = cms.bool(False),
    debugTraco = cms.int32(0),
    finePhase = cms.double(25.0)
)


process.L1TriggerMenu = cms.ESProducer("L1TUtmTriggerMenuESProducer",
    L1TriggerMenuFile = cms.string('L1Menu_CollisionsHeavyIons2022_v0_0_0.xml')
)


process.MaterialPropagator = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterial'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.MaterialPropagatorForHI = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialForHI'),
    Mass = cms.double(0.139),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.MaterialPropagatorParabolicMF = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialParabolicMf'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.OppositeMaterialPropagator = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialOpposite'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('oppositeToMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.OppositeMaterialPropagatorForHI = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialOppositeForHI'),
    Mass = cms.double(0.139),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('oppositeToMomentum'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.OppositeMaterialPropagatorParabolicMF = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialParabolicMfOpposite'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('oppositeToMomentum'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.OppositePropagatorWithMaterialForMixedStep = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialForMixedStepOpposite'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('oppositeToMomentum'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    ptMin = cms.double(0.1),
    useRungeKutta = cms.bool(False)
)


process.ParametrizedMagneticFieldProducer = cms.ESProducer("AutoParametrizedMagneticFieldProducer",
    label = cms.untracked.string('ParabolicMf'),
    valueOverride = cms.int32(-1),
    version = cms.string('Parabolic')
)


process.PixelCPEFastESProducer = cms.ESProducer("PixelCPEFastESProducer",
    Alpha2Order = cms.bool(True),
    ClusterProbComputationFlag = cms.int32(0),
    ComponentName = cms.string('PixelCPEFast'),
    EdgeClusterErrorX = cms.double(50.0),
    EdgeClusterErrorY = cms.double(85.0),
    LoadTemplatesFromDB = cms.bool(True),
    MagneticFieldRecord = cms.ESInputTag("",""),
    TruncatePixelCharge = cms.bool(True),
    UseErrorsFromTemplates = cms.bool(True),
    appendToDataLabel = cms.string(''),
    doLorentzFromAlignment = cms.bool(False),
    isPhase2 = cms.bool(False),
    lAOffset = cms.double(0.0),
    lAWidthBPix = cms.double(0.0),
    lAWidthFPix = cms.double(0.0),
    useLAFromDB = cms.bool(True),
    useLAWidthFromDB = cms.bool(True),
    xerr_barrel_l1 = cms.vdouble(0.00115, 0.0012, 0.00088),
    xerr_barrel_l1_def = cms.double(0.0103),
    xerr_barrel_ln = cms.vdouble(0.00115, 0.0012, 0.00088),
    xerr_barrel_ln_def = cms.double(0.0103),
    xerr_endcap = cms.vdouble(0.002, 0.002),
    xerr_endcap_def = cms.double(0.002),
    yerr_barrel_l1 = cms.vdouble(
        0.00375, 0.0023, 0.0025, 0.0025, 0.0023,
        0.0023, 0.0021, 0.0021, 0.0024
    ),
    yerr_barrel_l1_def = cms.double(0.0021),
    yerr_barrel_ln = cms.vdouble(
        0.00375, 0.0023, 0.0025, 0.0025, 0.0023,
        0.0023, 0.0021, 0.0021, 0.0024
    ),
    yerr_barrel_ln_def = cms.double(0.0021),
    yerr_endcap = cms.vdouble(0.0021),
    yerr_endcap_def = cms.double(0.00075)
)


process.PropagatorWithMaterialForLoopers = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialForLoopers'),
    Mass = cms.double(0.1396),
    MaxDPhi = cms.double(4.0),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.PropagatorWithMaterialForMixedStep = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('PropagatorWithMaterialForMixedStep'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string('ParabolicMf'),
    ptMin = cms.double(0.1),
    useRungeKutta = cms.bool(False)
)


process.RPCConeBuilder = cms.ESProducer("RPCConeBuilder",
    towerBeg = cms.int32(0),
    towerEnd = cms.int32(16)
)


process.RPCGeometryESModule = cms.ESProducer("RPCGeometryESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.untracked.bool(False),
    fromDDD = cms.untracked.bool(False)
)


process.SiStripClusterizerConditionsESProducer = cms.ESProducer("SiStripClusterizerConditionsESProducer",
    Label = cms.string(''),
    QualityLabel = cms.string(''),
    appendToDataLabel = cms.string('')
)


process.SiStripGainESProducer = cms.ESProducer("SiStripGainESProducer",
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


process.SiStripQualityESProducer = cms.ESProducer("SiStripQualityESProducer",
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
        )
    ),
    PrintDebugOutput = cms.bool(False),
    ReduceGranularity = cms.bool(False),
    ThresholdForReducedGranularity = cms.double(0.3),
    UseEmptyRunInfo = cms.bool(False),
    appendToDataLabel = cms.string('')
)


process.SiStripRecHitMatcherESProducer = cms.ESProducer("SiStripRecHitMatcherESProducer",
    ComponentName = cms.string('StandardMatcher'),
    NSigmaInside = cms.double(3.0),
    PreFilter = cms.bool(False)
)


process.SiStripRegionConnectivity = cms.ESProducer("SiStripRegionConnectivity",
    EtaDivisions = cms.untracked.uint32(20),
    EtaMax = cms.untracked.double(2.5),
    PhiDivisions = cms.untracked.uint32(20)
)


process.SimpleSecondaryVertex3TrkComputer = cms.ESProducer("SimpleSecondaryVertexESProducer",
    minTracks = cms.uint32(3),
    minVertices = cms.uint32(1),
    unBoost = cms.bool(False),
    use3d = cms.bool(True),
    useSignificance = cms.bool(True)
)


process.SteppingHelixPropagatorAny = cms.ESProducer("SteppingHelixPropagatorESProducer",
    ApplyRadX0Correction = cms.bool(True),
    AssumeNoMaterial = cms.bool(False),
    ComponentName = cms.string('SteppingHelixPropagatorAny'),
    NoErrorPropagation = cms.bool(False),
    PropagationDirection = cms.string('anyDirection'),
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


process.TrackerAdditionalParametersPerDetESModule = cms.ESProducer("TrackerAdditionalParametersPerDetESModule",
    appendToDataLabel = cms.string('')
)


process.TrackerDigiGeometryESModule = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(False)
)


process.TrackerGeometricDetESModule = cms.ESProducer("TrackerGeometricDetESModule",
    appendToDataLabel = cms.string(''),
    fromDD4hep = cms.bool(False),
    fromDDD = cms.bool(False)
)


process.TransientTrackBuilderESProducer = cms.ESProducer("TransientTrackBuilderESProducer",
    ComponentName = cms.string('TransientTrackBuilder')
)


process.VolumeBasedMagneticFieldESProducer = cms.ESProducer("VolumeBasedMagneticFieldESProducerFromDB",
    debugBuilder = cms.untracked.bool(False),
    label = cms.untracked.string(''),
    valueOverride = cms.int32(-1)
)


process.ZdcGeometryFromDBEP = cms.ESProducer("ZdcGeometryFromDBEP",
    applyAlignment = cms.bool(False)
)


process.caloConfig = cms.ESProducer("L1TCaloConfigESProducer",
    fwVersionLayer2 = cms.uint32(3),
    l1Epoch = cms.string('Stage1')
)


process.caloDetIdAssociator = cms.ESProducer("DetIdAssociatorESProducer",
    ComponentName = cms.string('CaloDetIdAssociator'),
    etaBinSize = cms.double(0.087),
    hcalRegion = cms.int32(2),
    includeBadChambers = cms.bool(False),
    includeGEM = cms.bool(False),
    includeME0 = cms.bool(False),
    nEta = cms.int32(70),
    nPhi = cms.int32(72)
)


process.cosmicsNavigationSchoolESProducer = cms.ESProducer("NavigationSchoolESProducer",
    ComponentName = cms.string('CosmicNavigationSchool'),
    SimpleMagneticField = cms.string('')
)


process.ctppsGeometryESModule = cms.ESProducer("CTPPSGeometryESModule",
    appendToDataLabel = cms.string(''),
    buildMisalignedGeometry = cms.bool(False),
    compactViewTag = cms.string(''),
    dbTag = cms.string(''),
    fromDD4hep = cms.untracked.bool(False),
    fromPreprocessedDB = cms.untracked.bool(True),
    isRun2 = cms.bool(False),
    verbosity = cms.untracked.uint32(1)
)


process.ctppsInterpolatedOpticalFunctionsESSource = cms.ESProducer("CTPPSInterpolatedOpticalFunctionsESSource",
    appendToDataLabel = cms.string(''),
    lhcInfoLabel = cms.string(''),
    opticsLabel = cms.string('')
)


process.ecalDetIdAssociator = cms.ESProducer("DetIdAssociatorESProducer",
    ComponentName = cms.string('EcalDetIdAssociator'),
    etaBinSize = cms.double(0.02),
    hcalRegion = cms.int32(2),
    includeBadChambers = cms.bool(False),
    includeGEM = cms.bool(False),
    includeME0 = cms.bool(False),
    nEta = cms.int32(300),
    nPhi = cms.int32(360)
)


process.ecalElectronicsMappingGPUESProducer = cms.ESProducer("EcalElectronicsMappingGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalGainRatiosGPUESProducer = cms.ESProducer("EcalGainRatiosGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalIntercalibConstantsGPUESProducer = cms.ESProducer("EcalIntercalibConstantsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalLaserAPDPNRatiosGPUESProducer = cms.ESProducer("EcalLaserAPDPNRatiosGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalLaserAPDPNRatiosRefGPUESProducer = cms.ESProducer("EcalLaserAPDPNRatiosRefGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalLaserAlphasGPUESProducer = cms.ESProducer("EcalLaserAlphasGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalLinearCorrectionsGPUESProducer = cms.ESProducer("EcalLinearCorrectionsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalPedestalsGPUESProducer = cms.ESProducer("EcalPedestalsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalPulseCovariancesGPUESProducer = cms.ESProducer("EcalPulseCovariancesGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalPulseShapesGPUESProducer = cms.ESProducer("EcalPulseShapesGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalRechitADCToGeVConstantGPUESProducer = cms.ESProducer("EcalRechitADCToGeVConstantGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalRechitChannelStatusGPUESProducer = cms.ESProducer("EcalRechitChannelStatusGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalSamplesCorrelationGPUESProducer = cms.ESProducer("EcalSamplesCorrelationGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalSeverityLevel = cms.ESProducer("EcalSeverityLevelESProducer",
    dbstatusMask = cms.PSet(
        kBad = cms.vstring(
            'kNonRespondingIsolated',
            'kDeadVFE',
            'kDeadFE',
            'kNoDataNoTP'
        ),
        kGood = cms.vstring('kOk'),
        kProblematic = cms.vstring(
            'kDAC',
            'kNoLaser',
            'kNoisy',
            'kNNoisy',
            'kNNNoisy',
            'kNNNNoisy',
            'kNNNNNoisy',
            'kFixedG6',
            'kFixedG1',
            'kFixedG0'
        ),
        kRecovered = cms.vstring(),
        kTime = cms.vstring(),
        kWeird = cms.vstring()
    ),
    flagMask = cms.PSet(
        kBad = cms.vstring(
            'kFaultyHardware',
            'kDead',
            'kKilled'
        ),
        kGood = cms.vstring('kGood'),
        kProblematic = cms.vstring(
            'kPoorReco',
            'kPoorCalib',
            'kNoisy',
            'kSaturated'
        ),
        kRecovered = cms.vstring(
            'kLeadingEdgeRecovered',
            'kTowerRecovered'
        ),
        kTime = cms.vstring('kOutOfTime'),
        kWeird = cms.vstring(
            'kWeird',
            'kDiWeird'
        )
    ),
    timeThresh = cms.double(2.0)
)


process.ecalTimeBiasCorrectionsGPUESProducer = cms.ESProducer("EcalTimeBiasCorrectionsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.ecalTimeCalibConstantsGPUESProducer = cms.ESProducer("EcalTimeCalibConstantsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.fakeTwinMuxParams = cms.ESProducer("L1TTwinMuxParamsESProducer",
    CorrectDTBxwRPC = cms.bool(True),
    dphiWindowBxShift = cms.uint32(9999),
    fwVersion = cms.uint32(1),
    useLowQDT = cms.bool(False),
    useOnlyDT = cms.bool(False),
    useOnlyRPC = cms.bool(False),
    useRpcBxForDtBelowQuality = cms.uint32(4),
    verbose = cms.bool(False)
)


process.hcalChannelPropertiesESProd = cms.ESProducer("HcalChannelPropertiesEP")


process.hcalChannelQualityGPUESProducer = cms.ESProducer("HcalChannelQualityGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalConvertedEffectivePedestalWidthsGPUESProducer = cms.ESProducer("HcalConvertedEffectivePedestalWidthsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label0 = cms.string('withTopoEff'),
    label1 = cms.string('withTopoEff'),
    label2 = cms.string(''),
    label3 = cms.string('')
)


process.hcalConvertedEffectivePedestalsGPUESProducer = cms.ESProducer("HcalConvertedEffectivePedestalsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label0 = cms.string('withTopoEff'),
    label1 = cms.string(''),
    label2 = cms.string('')
)


process.hcalConvertedPedestalWidthsGPUESProducer = cms.ESProducer("HcalConvertedPedestalWidthsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label0 = cms.string(''),
    label1 = cms.string(''),
    label2 = cms.string(''),
    label3 = cms.string('')
)


process.hcalConvertedPedestalsGPUESProducer = cms.ESProducer("HcalConvertedPedestalsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label0 = cms.string(''),
    label1 = cms.string(''),
    label2 = cms.string('')
)


process.hcalDDDRecConstants = cms.ESProducer("HcalDDDRecConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalDDDSimConstants = cms.ESProducer("HcalDDDSimConstantsESModule",
    appendToDataLabel = cms.string('')
)


process.hcalDetIdAssociator = cms.ESProducer("DetIdAssociatorESProducer",
    ComponentName = cms.string('HcalDetIdAssociator'),
    etaBinSize = cms.double(0.087),
    hcalRegion = cms.int32(2),
    includeBadChambers = cms.bool(False),
    includeGEM = cms.bool(False),
    includeME0 = cms.bool(False),
    nEta = cms.int32(70),
    nPhi = cms.int32(72)
)


process.hcalElectronicsMappingGPUESProducer = cms.ESProducer("HcalElectronicsMappingGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalGainWidthsGPUESProducer = cms.ESProducer("HcalGainWidthsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalGainsGPUESProducer = cms.ESProducer("HcalGainsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalLUTCorrsGPUESProducer = cms.ESProducer("HcalLUTCorrsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalQIECodersGPUESProducer = cms.ESProducer("HcalQIECodersGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalQIETypesGPUESProducer = cms.ESProducer("HcalQIETypesGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalRecAlgos = cms.ESProducer("HcalRecAlgoESProducer",
    DropChannelStatusBits = cms.vstring(
        'HcalCellMask',
        'HcalCellOff',
        'HcalCellDead'
    ),
    RecoveredRecHitBits = cms.vstring(),
    SeverityLevels = cms.VPSet(
        cms.PSet(
            ChannelStatus = cms.vstring(),
            Level = cms.int32(0),
            RecHitFlags = cms.vstring('TimingFromTDC')
        ),
        cms.PSet(
            ChannelStatus = cms.vstring('HcalCellCaloTowerProb'),
            Level = cms.int32(1),
            RecHitFlags = cms.vstring()
        ),
        cms.PSet(
            ChannelStatus = cms.vstring('HcalCellExcludeFromHBHENoiseSummary'),
            Level = cms.int32(5),
            RecHitFlags = cms.vstring()
        ),
        cms.PSet(
            ChannelStatus = cms.vstring(),
            Level = cms.int32(8),
            RecHitFlags = cms.vstring(
                'HBHEHpdHitMultiplicity',
                'HBHEIsolatedNoise',
                'HBHEFlatNoise',
                'HBHESpikeNoise',
                'HBHETS4TS5Noise',
                'HBHENegativeNoise',
                'HBHEPulseFitBit',
                'HBHEOOTPU'
            )
        ),
        cms.PSet(
            ChannelStatus = cms.vstring(),
            Level = cms.int32(11),
            RecHitFlags = cms.vstring(
                'HFLongShort',
                'HFS8S1Ratio',
                'HFPET',
                'HFSignalAsymmetry'
            )
        ),
        cms.PSet(
            ChannelStatus = cms.vstring('HcalCellHot'),
            Level = cms.int32(15),
            RecHitFlags = cms.vstring()
        ),
        cms.PSet(
            ChannelStatus = cms.vstring(
                'HcalCellOff',
                'HcalCellDead'
            ),
            Level = cms.int32(20),
            RecHitFlags = cms.vstring()
        )
    ),
    appendToDataLabel = cms.string(''),
    phase = cms.uint32(1)
)


process.hcalRecoParamsWithPulseShapesGPUESProducer = cms.ESProducer("HcalRecoParamsWithPulseShapesGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalRespCorrsGPUESProducer = cms.ESProducer("HcalRespCorrsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalSiPMCharacteristicsGPUESProducer = cms.ESProducer("HcalSiPMCharacteristicsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalSiPMParametersGPUESProducer = cms.ESProducer("HcalSiPMParametersGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcalTimeCorrsGPUESProducer = cms.ESProducer("HcalTimeCorrsGPUESProducer",
    ComponentName = cms.string(''),
    appendToDataLabel = cms.string(''),
    label = cms.string('')
)


process.hcal_db_producer = cms.ESProducer("HcalDbProducer")


process.hltBoostedDoubleSecondaryVertexAK8Computer = cms.ESProducer("CandidateBoostedDoubleSecondaryVertexESProducer",
    useAdaBoost = cms.bool(False),
    useCondDB = cms.bool(False),
    useGBRForest = cms.bool(True),
    weightFile = cms.FileInPath('RecoBTag/SecondaryVertex/data/BoostedDoubleSV_AK8_BDT_v4.weights.xml.gz')
)


process.hltCombinedSecondaryVertex = cms.ESProducer("CombinedSecondaryVertexESProducer",
    SoftLeptonFlip = cms.bool(False),
    calibrationRecords = cms.vstring(
        'CombinedSVRecoVertex',
        'CombinedSVPseudoVertex',
        'CombinedSVNoVertex'
    ),
    categoryVariableName = cms.string('vertexCategory'),
    charmCut = cms.double(1.5),
    correctVertexMass = cms.bool(True),
    minimumTrackWeight = cms.double(0.5),
    pseudoMultiplicityMin = cms.uint32(2),
    pseudoVertexV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.05)
    ),
    recordLabel = cms.string('HLT'),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(3),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5.0),
        maxDistToAxis = cms.double(0.07),
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
        totalHitsMin = cms.uint32(0)
    ),
    trackSelection = cms.PSet(
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5.0),
        maxDistToAxis = cms.double(0.07),
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
        totalHitsMin = cms.uint32(0)
    ),
    trackSort = cms.string('sip2dSig'),
    useCategories = cms.bool(True),
    useTrackWeights = cms.bool(True),
    vertexFlip = cms.bool(False)
)


process.hltCombinedSecondaryVertexV2 = cms.ESProducer("CombinedSecondaryVertexESProducer",
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
    recordLabel = cms.string('HLT'),
    trackFlip = cms.bool(False),
    trackMultiplicityMin = cms.uint32(3),
    trackPairV0Filter = cms.PSet(
        k0sMassWindow = cms.double(0.03)
    ),
    trackPseudoSelection = cms.PSet(
        a_dR = cms.double(-0.001053),
        a_pT = cms.double(0.005263),
        b_dR = cms.double(0.6263),
        b_pT = cms.double(0.3684),
        jetDeltaRMax = cms.double(0.3),
        maxDecayLen = cms.double(5.0),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500.0),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3.0),
        min_pT = cms.double(120.0),
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
        maxDecayLen = cms.double(5.0),
        maxDistToAxis = cms.double(0.07),
        max_pT = cms.double(500.0),
        max_pT_dRcut = cms.double(0.1),
        max_pT_trackPTcut = cms.double(3.0),
        min_pT = cms.double(120.0),
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


process.hltDisplacedDijethltESPPromptTrackCountingESProducer = cms.ESProducer("PromptTrackCountingESProducer",
    deltaR = cms.double(-1.0),
    deltaRmin = cms.double(0.0),
    impactParameterType = cms.int32(1),
    maxImpactParameter = cms.double(0.1),
    maxImpactParameterSig = cms.double(999999.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(999999.0),
    minimumImpactParameter = cms.double(-1.0),
    nthTrack = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True)
)


process.hltDisplacedDijethltESPTrackCounting2D1st = cms.ESProducer("TrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(1),
    max_pT = cms.double(500.0),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(9999999.0),
    min_pT = cms.double(120.0),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(0.05),
    nthTrack = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(False),
    useVariableJTA = cms.bool(False)
)


process.hltESPAnalyticalPropagator = cms.ESProducer("AnalyticalPropagatorESProducer",
    ComponentName = cms.string('hltESPAnalyticalPropagator'),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum')
)


process.hltESPBwdAnalyticalPropagator = cms.ESProducer("AnalyticalPropagatorESProducer",
    ComponentName = cms.string('hltESPBwdAnalyticalPropagator'),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('oppositeToMomentum')
)


process.hltESPBwdElectronPropagator = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('hltESPBwdElectronPropagator'),
    Mass = cms.double(0.000511),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('oppositeToMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.hltESPChi2ChargeLooseMeasurementEstimator16 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2ChargeLooseMeasurementEstimator16'),
    MaxChi2 = cms.double(16.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPChi2ChargeMeasurementEstimator16 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2ChargeMeasurementEstimator16'),
    MaxChi2 = cms.double(16.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPChi2ChargeMeasurementEstimator2000 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2ChargeMeasurementEstimator2000'),
    MaxChi2 = cms.double(2000.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPChi2ChargeMeasurementEstimator30 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2ChargeMeasurementEstimator30'),
    MaxChi2 = cms.double(30.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutNone')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPChi2ChargeMeasurementEstimator9 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2ChargeMeasurementEstimator9'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(15.0)
)


process.hltESPChi2ChargeMeasurementEstimator9ForHI = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2ChargeMeasurementEstimator9ForHI'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutForHI')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(15.0)
)


process.hltESPChi2ChargeTightMeasurementEstimator16 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2ChargeTightMeasurementEstimator16'),
    MaxChi2 = cms.double(16.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPChi2MeasurementEstimator100 = cms.ESProducer("Chi2MeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2MeasurementEstimator100'),
    MaxChi2 = cms.double(40.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    nSigma = cms.double(4.0)
)


process.hltESPChi2MeasurementEstimator16 = cms.ESProducer("Chi2MeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2MeasurementEstimator16'),
    MaxChi2 = cms.double(16.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    nSigma = cms.double(3.0)
)


process.hltESPChi2MeasurementEstimator30 = cms.ESProducer("Chi2MeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2MeasurementEstimator30'),
    MaxChi2 = cms.double(30.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    nSigma = cms.double(3.0)
)


process.hltESPChi2MeasurementEstimator9 = cms.ESProducer("Chi2MeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPChi2MeasurementEstimator9'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    nSigma = cms.double(3.0)
)


process.hltESPCloseComponentsMerger5D = cms.ESProducer("CloseComponentsMergerESProducer5D",
    ComponentName = cms.string('hltESPCloseComponentsMerger5D'),
    DistanceMeasure = cms.string('hltESPKullbackLeiblerDistance5D'),
    MaxComponents = cms.int32(12)
)


process.hltESPDetachedQuadStepChi2ChargeMeasurementEstimator9 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPDetachedQuadStepChi2ChargeMeasurementEstimator9'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPDetachedQuadStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPDetachedQuadStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.13)
)


process.hltESPDetachedStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPDetachedStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.13)
)


process.hltESPDetachedTripletStepChi2ChargeMeasurementEstimator9 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPDetachedTripletStepChi2ChargeMeasurementEstimator9'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPDetachedTripletStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPDetachedTripletStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.13)
)


process.hltESPDisplacedDijethltPromptTrackCountingESProducer = cms.ESProducer("PromptTrackCountingESProducer",
    deltaR = cms.double(-1.0),
    deltaRmin = cms.double(0.0),
    impactParameterType = cms.int32(1),
    maxImpactParameter = cms.double(0.1),
    maxImpactParameterSig = cms.double(999999.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(999999.0),
    minimumImpactParameter = cms.double(-1.0),
    nthTrack = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True)
)


process.hltESPDisplacedDijethltPromptTrackCountingESProducerLong = cms.ESProducer("PromptTrackCountingESProducer",
    deltaR = cms.double(-1.0),
    deltaRmin = cms.double(0.0),
    impactParameterType = cms.int32(1),
    maxImpactParameter = cms.double(0.2),
    maxImpactParameterSig = cms.double(999999.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(999999.0),
    minimumImpactParameter = cms.double(-1.0),
    nthTrack = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True)
)


process.hltESPDisplacedDijethltPromptTrackCountingESProducerShortSig5 = cms.ESProducer("PromptTrackCountingESProducer",
    deltaR = cms.double(-1.0),
    deltaRmin = cms.double(0.0),
    impactParameterType = cms.int32(1),
    maxImpactParameter = cms.double(0.05),
    maxImpactParameterSig = cms.double(5.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(999999.0),
    minimumImpactParameter = cms.double(-1.0),
    nthTrack = cms.int32(-1),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(False)
)


process.hltESPDisplacedDijethltTrackCounting2D1st = cms.ESProducer("TrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(1),
    max_pT = cms.double(500.0),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(9999999.0),
    min_pT = cms.double(120.0),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(0.05),
    nthTrack = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(False),
    useVariableJTA = cms.bool(False)
)


process.hltESPDisplacedDijethltTrackCounting2D1stLoose = cms.ESProducer("TrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(1),
    max_pT = cms.double(500.0),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(9999999.0),
    min_pT = cms.double(120.0),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(0.03),
    nthTrack = cms.int32(1),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(False),
    useVariableJTA = cms.bool(False)
)


process.hltESPDisplacedDijethltTrackCounting2D2ndLong = cms.ESProducer("TrackCountingESProducer",
    a_dR = cms.double(-0.001053),
    a_pT = cms.double(0.005263),
    b_dR = cms.double(0.6263),
    b_pT = cms.double(0.3684),
    deltaR = cms.double(-1.0),
    impactParameterType = cms.int32(1),
    max_pT = cms.double(500.0),
    max_pT_dRcut = cms.double(0.1),
    max_pT_trackPTcut = cms.double(3.0),
    maximumDecayLength = cms.double(999999.0),
    maximumDistanceToJetAxis = cms.double(9999999.0),
    min_pT = cms.double(120.0),
    min_pT_dRcut = cms.double(0.5),
    minimumImpactParameter = cms.double(0.2),
    nthTrack = cms.int32(2),
    trackQualityClass = cms.string('any'),
    useSignedImpactParameterSig = cms.bool(True),
    useVariableJTA = cms.bool(False)
)


process.hltESPDummyDetLayerGeometry = cms.ESProducer("DetLayerGeometryESProducer",
    ComponentName = cms.string('hltESPDummyDetLayerGeometry')
)


process.hltESPEcalTrigTowerConstituentsMapBuilder = cms.ESProducer("EcalTrigTowerConstituentsMapBuilder",
    MapFile = cms.untracked.string('Geometry/EcalMapping/data/EndCap_TTMap.txt')
)


process.hltESPElectronMaterialEffects = cms.ESProducer("GsfMaterialEffectsESProducer",
    BetheHeitlerCorrection = cms.int32(2),
    BetheHeitlerParametrization = cms.string('BetheHeitler_cdfmom_nC6_O5.par'),
    ComponentName = cms.string('hltESPElectronMaterialEffects'),
    EnergyLossUpdator = cms.string('GsfBetheHeitlerUpdator'),
    Mass = cms.double(0.000511),
    MultipleScatteringUpdator = cms.string('MultipleScatteringUpdator')
)


process.hltESPFastSteppingHelixPropagatorAny = cms.ESProducer("SteppingHelixPropagatorESProducer",
    ApplyRadX0Correction = cms.bool(True),
    AssumeNoMaterial = cms.bool(False),
    ComponentName = cms.string('hltESPFastSteppingHelixPropagatorAny'),
    NoErrorPropagation = cms.bool(False),
    PropagationDirection = cms.string('anyDirection'),
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
    useTuningForL2Speed = cms.bool(True)
)


process.hltESPFastSteppingHelixPropagatorOpposite = cms.ESProducer("SteppingHelixPropagatorESProducer",
    ApplyRadX0Correction = cms.bool(True),
    AssumeNoMaterial = cms.bool(False),
    ComponentName = cms.string('hltESPFastSteppingHelixPropagatorOpposite'),
    NoErrorPropagation = cms.bool(False),
    PropagationDirection = cms.string('oppositeToMomentum'),
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
    useTuningForL2Speed = cms.bool(True)
)


process.hltESPFittingSmootherIT = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(True),
    ComponentName = cms.string('hltESPFittingSmootherIT'),
    EstimateCut = cms.double(-1.0),
    Fitter = cms.string('hltESPTrajectoryFitterRK'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-16.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(3),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(True),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPTrajectorySmootherRK'),
    appendToDataLabel = cms.string('')
)


process.hltESPFittingSmootherRK = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(False),
    ComponentName = cms.string('hltESPFittingSmootherRK'),
    EstimateCut = cms.double(-1.0),
    Fitter = cms.string('hltESPTrajectoryFitterRK'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-16.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(5),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(False),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPTrajectorySmootherRK'),
    appendToDataLabel = cms.string('')
)


process.hltESPFlexibleKFFittingSmoother = cms.ESProducer("FlexibleKFFittingSmootherESProducer",
    ComponentName = cms.string('hltESPFlexibleKFFittingSmoother'),
    appendToDataLabel = cms.string(''),
    looperFitter = cms.string('hltESPKFFittingSmootherForLoopers'),
    standardFitter = cms.string('hltESPKFFittingSmootherWithOutliersRejectionAndRK')
)


process.hltESPFwdElectronPropagator = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('hltESPFwdElectronPropagator'),
    Mass = cms.double(0.000511),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(False)
)


process.hltESPGlobalDetLayerGeometry = cms.ESProducer("GlobalDetLayerGeometryESProducer",
    ComponentName = cms.string('hltESPGlobalDetLayerGeometry')
)


process.hltESPGlobalTrackingGeometryESProducer = cms.ESProducer("GlobalTrackingGeometryESProducer")


process.hltESPGsfElectronFittingSmoother = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(True),
    ComponentName = cms.string('hltESPGsfElectronFittingSmoother'),
    EstimateCut = cms.double(-1.0),
    Fitter = cms.string('hltESPGsfTrajectoryFitter'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-16.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(5),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(True),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPGsfTrajectorySmoother'),
    appendToDataLabel = cms.string('')
)


process.hltESPGsfTrajectoryFitter = cms.ESProducer("GsfTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPGsfTrajectoryFitter'),
    GeometricalPropagator = cms.string('hltESPAnalyticalPropagator'),
    MaterialEffectsUpdator = cms.string('hltESPElectronMaterialEffects'),
    Merger = cms.string('hltESPCloseComponentsMerger5D'),
    RecoGeometry = cms.string('hltESPGlobalDetLayerGeometry')
)


process.hltESPGsfTrajectorySmoother = cms.ESProducer("GsfTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPGsfTrajectorySmoother'),
    ErrorRescaling = cms.double(100.0),
    GeometricalPropagator = cms.string('hltESPBwdAnalyticalPropagator'),
    MaterialEffectsUpdator = cms.string('hltESPElectronMaterialEffects'),
    Merger = cms.string('hltESPCloseComponentsMerger5D'),
    RecoGeometry = cms.string('hltESPGlobalDetLayerGeometry')
)


process.hltESPHighPtTripletStepChi2ChargeMeasurementEstimator30 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPHighPtTripletStepChi2ChargeMeasurementEstimator30'),
    MaxChi2 = cms.double(30.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(15.0)
)


process.hltESPInitialStepChi2ChargeMeasurementEstimator30 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPInitialStepChi2ChargeMeasurementEstimator30'),
    MaxChi2 = cms.double(30.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(15.0)
)


process.hltESPInitialStepChi2MeasurementEstimator36 = cms.ESProducer("Chi2MeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPInitialStepChi2MeasurementEstimator36'),
    MaxChi2 = cms.double(36.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    nSigma = cms.double(3.0)
)


process.hltESPKFFittingSmoother = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(False),
    ComponentName = cms.string('hltESPKFFittingSmoother'),
    EstimateCut = cms.double(-1.0),
    Fitter = cms.string('hltESPKFTrajectoryFitter'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-16.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(5),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(False),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPKFTrajectorySmoother'),
    appendToDataLabel = cms.string('')
)


process.hltESPKFFittingSmootherForL2Muon = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(False),
    ComponentName = cms.string('hltESPKFFittingSmootherForL2Muon'),
    EstimateCut = cms.double(-1.0),
    Fitter = cms.string('hltESPKFTrajectoryFitterForL2Muon'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-16.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(5),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(False),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPKFTrajectorySmootherForL2Muon'),
    appendToDataLabel = cms.string('')
)


process.hltESPKFFittingSmootherForLoopers = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(True),
    ComponentName = cms.string('hltESPKFFittingSmootherForLoopers'),
    EstimateCut = cms.double(20.0),
    Fitter = cms.string('hltESPKFTrajectoryFitterForLoopers'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-14.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(3),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(True),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPKFTrajectorySmootherForLoopers'),
    appendToDataLabel = cms.string('')
)


process.hltESPKFFittingSmootherWithOutliersRejectionAndRK = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(True),
    ComponentName = cms.string('hltESPKFFittingSmootherWithOutliersRejectionAndRK'),
    EstimateCut = cms.double(20.0),
    Fitter = cms.string('hltESPRKTrajectoryFitter'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-14.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(3),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(True),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPRKTrajectorySmoother'),
    appendToDataLabel = cms.string('')
)


process.hltESPKFTrajectoryFitter = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPKFTrajectoryFitter'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(3)
)


process.hltESPKFTrajectoryFitterForL2Muon = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPKFTrajectoryFitterForL2Muon'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPFastSteppingHelixPropagatorAny'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(3)
)


process.hltESPKFTrajectoryFitterForLoopers = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPKFTrajectoryFitterForLoopers'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialForLoopers'),
    RecoGeometry = cms.string('hltESPGlobalDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(3)
)


process.hltESPKFTrajectorySmoother = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPKFTrajectorySmoother'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(100.0),
    minHits = cms.int32(3)
)


process.hltESPKFTrajectorySmootherForL2Muon = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPKFTrajectorySmootherForL2Muon'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPFastSteppingHelixPropagatorOpposite'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(100.0),
    minHits = cms.int32(3)
)


process.hltESPKFTrajectorySmootherForLoopers = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPKFTrajectorySmootherForLoopers'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialForLoopers'),
    RecoGeometry = cms.string('hltESPGlobalDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(10.0),
    minHits = cms.int32(3)
)


process.hltESPKFTrajectorySmootherForMuonTrackLoader = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPKFTrajectorySmootherForMuonTrackLoader'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPSmartPropagatorAnyOpposite'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(10.0),
    minHits = cms.int32(3)
)


process.hltESPKFUpdator = cms.ESProducer("KFUpdatorESProducer",
    ComponentName = cms.string('hltESPKFUpdator')
)


process.hltESPKullbackLeiblerDistance5D = cms.ESProducer("DistanceBetweenComponentsESProducer5D",
    ComponentName = cms.string('hltESPKullbackLeiblerDistance5D'),
    DistanceMeasure = cms.string('KullbackLeibler')
)


process.hltESPL3MuKFTrajectoryFitter = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPL3MuKFTrajectoryFitter'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPSmartPropagatorAny'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(3)
)


process.hltESPLowPtQuadStepChi2ChargeMeasurementEstimator9 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPLowPtQuadStepChi2ChargeMeasurementEstimator9'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPLowPtQuadStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPLowPtQuadStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.16)
)


process.hltESPLowPtStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPLowPtStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.16)
)


process.hltESPLowPtTripletStepChi2ChargeMeasurementEstimator9 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPLowPtTripletStepChi2ChargeMeasurementEstimator9'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPLowPtTripletStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPLowPtTripletStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.16)
)


process.hltESPMeasurementTracker = cms.ESProducer("MeasurementTrackerESProducer",
    ComponentName = cms.string('hltESPMeasurementTracker'),
    DebugPixelModuleQualityDB = cms.untracked.bool(False),
    DebugPixelROCQualityDB = cms.untracked.bool(False),
    DebugStripAPVFiberQualityDB = cms.untracked.bool(False),
    DebugStripModuleQualityDB = cms.untracked.bool(False),
    DebugStripStripQualityDB = cms.untracked.bool(False),
    HitMatcher = cms.string('StandardMatcher'),
    MaskBadAPVFibers = cms.bool(True),
    Phase2StripCPE = cms.string(''),
    PixelCPE = cms.string('hltESPPixelCPEGeneric'),
    SiStripQualityLabel = cms.string(''),
    StripCPE = cms.string('hltESPStripCPEfromTrackAngle'),
    UsePixelModuleQualityDB = cms.bool(True),
    UsePixelROCQualityDB = cms.bool(True),
    UseStripAPVFiberQualityDB = cms.bool(True),
    UseStripModuleQualityDB = cms.bool(True),
    UseStripStripQualityDB = cms.bool(True),
    appendToDataLabel = cms.string(''),
    badStripCuts = cms.PSet(
        TEC = cms.PSet(
            maxBad = cms.uint32(4),
            maxConsecutiveBad = cms.uint32(2)
        ),
        TIB = cms.PSet(
            maxBad = cms.uint32(4),
            maxConsecutiveBad = cms.uint32(2)
        ),
        TID = cms.PSet(
            maxBad = cms.uint32(4),
            maxConsecutiveBad = cms.uint32(2)
        ),
        TOB = cms.PSet(
            maxBad = cms.uint32(4),
            maxConsecutiveBad = cms.uint32(2)
        )
    )
)


process.hltESPMixedStepClusterShapeHitFilter = cms.ESProducer("ClusterShapeHitFilterESProducer",
    ComponentName = cms.string('hltESPMixedStepClusterShapeHitFilter'),
    PixelShapeFile = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_noL1.par'),
    PixelShapeFileL1 = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_loose.par'),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    doPixelShapeCut = cms.bool(True),
    doStripShapeCut = cms.bool(True),
    isPhase2 = cms.bool(False)
)


process.hltESPMixedStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPMixedStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.11)
)


process.hltESPMixedTripletStepChi2ChargeMeasurementEstimator16 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPMixedTripletStepChi2ChargeMeasurementEstimator16'),
    MaxChi2 = cms.double(16.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPMixedTripletStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPMixedTripletStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.11)
)


process.hltESPMuonDetLayerGeometryESProducer = cms.ESProducer("MuonDetLayerGeometryESProducer")


process.hltESPMuonTransientTrackingRecHitBuilder = cms.ESProducer("MuonTransientTrackingRecHitBuilderESProducer",
    ComponentName = cms.string('hltESPMuonTransientTrackingRecHitBuilder')
)


process.hltESPPixelCPEGeneric = cms.ESProducer("PixelCPEGenericESProducer",
    Alpha2Order = cms.bool(True),
    ClusterProbComputationFlag = cms.int32(0),
    ComponentName = cms.string('hltESPPixelCPEGeneric'),
    DoCosmics = cms.bool(False),
    EdgeClusterErrorX = cms.double(50.0),
    EdgeClusterErrorY = cms.double(85.0),
    IrradiationBiasCorrection = cms.bool(True),
    LoadTemplatesFromDB = cms.bool(True),
    MagneticFieldRecord = cms.ESInputTag("",""),
    NoTemplateErrorsWhenNoTrkAngles = cms.bool(False),
    SmallPitch = cms.bool(False),
    TruncatePixelCharge = cms.bool(True),
    Upgrade = cms.bool(False),
    UseErrorsFromTemplates = cms.bool(True),
    appendToDataLabel = cms.string(''),
    doLorentzFromAlignment = cms.bool(False),
    eff_charge_cut_highX = cms.double(1.0),
    eff_charge_cut_highY = cms.double(1.0),
    eff_charge_cut_lowX = cms.double(0.0),
    eff_charge_cut_lowY = cms.double(0.0),
    inflate_all_errors_no_trk_angle = cms.bool(False),
    inflate_errors = cms.bool(False),
    lAOffset = cms.double(0.0),
    lAWidthBPix = cms.double(0.0),
    lAWidthFPix = cms.double(0.0),
    size_cutX = cms.double(3.0),
    size_cutY = cms.double(3.0),
    useLAFromDB = cms.bool(True),
    useLAWidthFromDB = cms.bool(False),
    xerr_barrel_l1 = cms.vdouble(0.00115, 0.0012, 0.00088),
    xerr_barrel_l1_def = cms.double(0.0103),
    xerr_barrel_ln = cms.vdouble(0.00115, 0.0012, 0.00088),
    xerr_barrel_ln_def = cms.double(0.0103),
    xerr_endcap = cms.vdouble(0.002, 0.002),
    xerr_endcap_def = cms.double(0.002),
    yerr_barrel_l1 = cms.vdouble(
        0.00375, 0.0023, 0.0025, 0.0025, 0.0023,
        0.0023, 0.0021, 0.0021, 0.0024
    ),
    yerr_barrel_l1_def = cms.double(0.0021),
    yerr_barrel_ln = cms.vdouble(
        0.00375, 0.0023, 0.0025, 0.0025, 0.0023,
        0.0023, 0.0021, 0.0021, 0.0024
    ),
    yerr_barrel_ln_def = cms.double(0.0021),
    yerr_endcap = cms.vdouble(0.0021),
    yerr_endcap_def = cms.double(0.00075)
)


process.hltESPPixelCPETemplateReco = cms.ESProducer("PixelCPETemplateRecoESProducer",
    Alpha2Order = cms.bool(True),
    ClusterProbComputationFlag = cms.int32(0),
    ComponentName = cms.string('hltESPPixelCPETemplateReco'),
    LoadTemplatesFromDB = cms.bool(True),
    UseClusterSplitter = cms.bool(False),
    appendToDataLabel = cms.string(''),
    barrelTemplateID = cms.int32(0),
    directoryWithTemplates = cms.int32(0),
    doLorentzFromAlignment = cms.bool(False),
    forwardTemplateID = cms.int32(0),
    lAOffset = cms.double(0.0),
    lAWidthBPix = cms.double(0.0),
    lAWidthFPix = cms.double(0.0),
    speed = cms.int32(-2),
    useLAFromDB = cms.bool(True),
    useLAWidthFromDB = cms.bool(True)
)


process.hltESPPixelLessStepChi2ChargeMeasurementEstimator16 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPPixelLessStepChi2ChargeMeasurementEstimator16'),
    MaxChi2 = cms.double(16.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPPixelLessStepClusterShapeHitFilter = cms.ESProducer("ClusterShapeHitFilterESProducer",
    ComponentName = cms.string('hltESPPixelLessStepClusterShapeHitFilter'),
    PixelShapeFile = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_noL1.par'),
    PixelShapeFileL1 = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_loose.par'),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    doPixelShapeCut = cms.bool(True),
    doStripShapeCut = cms.bool(True),
    isPhase2 = cms.bool(False)
)


process.hltESPPixelLessStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPPixelLessStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.11)
)


process.hltESPPixelPairStepChi2ChargeMeasurementEstimator9 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPPixelPairStepChi2ChargeMeasurementEstimator9'),
    MaxChi2 = cms.double(9.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutLoose')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(15.0)
)


process.hltESPPixelPairStepChi2MeasurementEstimator25 = cms.ESProducer("Chi2MeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPPixelPairStepChi2MeasurementEstimator25'),
    MaxChi2 = cms.double(25.0),
    MaxDisplacement = cms.double(100.0),
    MaxSagitta = cms.double(-1.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(10.0),
    appendToDataLabel = cms.string(''),
    nSigma = cms.double(3.0)
)


process.hltESPPixelPairTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPPixelPairTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.19)
)


process.hltESPRKTrajectoryFitter = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPRKTrajectoryFitter'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    RecoGeometry = cms.string('hltESPGlobalDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(3)
)


process.hltESPRKTrajectorySmoother = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPRKTrajectorySmoother'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    RecoGeometry = cms.string('hltESPGlobalDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(100.0),
    minHits = cms.int32(3)
)


process.hltESPRungeKuttaTrackerPropagator = cms.ESProducer("PropagatorWithMaterialESProducer",
    ComponentName = cms.string('hltESPRungeKuttaTrackerPropagator'),
    Mass = cms.double(0.105),
    MaxDPhi = cms.double(1.6),
    PropagationDirection = cms.string('alongMomentum'),
    SimpleMagneticField = cms.string(''),
    ptMin = cms.double(-1.0),
    useRungeKutta = cms.bool(True)
)


process.hltESPSmartPropagator = cms.ESProducer("SmartPropagatorESProducer",
    ComponentName = cms.string('hltESPSmartPropagator'),
    Epsilon = cms.double(5.0),
    MuonPropagator = cms.string('hltESPSteppingHelixPropagatorAlong'),
    PropagationDirection = cms.string('alongMomentum'),
    TrackerPropagator = cms.string('PropagatorWithMaterial')
)


process.hltESPSmartPropagatorAny = cms.ESProducer("SmartPropagatorESProducer",
    ComponentName = cms.string('hltESPSmartPropagatorAny'),
    Epsilon = cms.double(5.0),
    MuonPropagator = cms.string('SteppingHelixPropagatorAny'),
    PropagationDirection = cms.string('alongMomentum'),
    TrackerPropagator = cms.string('PropagatorWithMaterial')
)


process.hltESPSmartPropagatorAnyOpposite = cms.ESProducer("SmartPropagatorESProducer",
    ComponentName = cms.string('hltESPSmartPropagatorAnyOpposite'),
    Epsilon = cms.double(5.0),
    MuonPropagator = cms.string('SteppingHelixPropagatorAny'),
    PropagationDirection = cms.string('oppositeToMomentum'),
    TrackerPropagator = cms.string('PropagatorWithMaterialOpposite')
)


process.hltESPSoftLeptonByDistance = cms.ESProducer("LeptonTaggerByDistanceESProducer",
    distance = cms.double(0.5)
)


process.hltESPSteppingHelixPropagatorAlong = cms.ESProducer("SteppingHelixPropagatorESProducer",
    ApplyRadX0Correction = cms.bool(True),
    AssumeNoMaterial = cms.bool(False),
    ComponentName = cms.string('hltESPSteppingHelixPropagatorAlong'),
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


process.hltESPSteppingHelixPropagatorOpposite = cms.ESProducer("SteppingHelixPropagatorESProducer",
    ApplyRadX0Correction = cms.bool(True),
    AssumeNoMaterial = cms.bool(False),
    ComponentName = cms.string('hltESPSteppingHelixPropagatorOpposite'),
    NoErrorPropagation = cms.bool(False),
    PropagationDirection = cms.string('oppositeToMomentum'),
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


process.hltESPStripCPEfromTrackAngle = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('hltESPStripCPEfromTrackAngle'),
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


process.hltESPTTRHBWithTrackAngle = cms.ESProducer("TkTransientTrackingRecHitBuilderESProducer",
    ComponentName = cms.string('hltESPTTRHBWithTrackAngle'),
    ComputeCoarseLocalPositionFromDisk = cms.bool(False),
    Matcher = cms.string('StandardMatcher'),
    Phase2StripCPE = cms.string(''),
    PixelCPE = cms.string('hltESPPixelCPEGeneric'),
    StripCPE = cms.string('hltESPStripCPEfromTrackAngle'),
    appendToDataLabel = cms.string('')
)


process.hltESPTTRHBuilderAngleAndTemplate = cms.ESProducer("TkTransientTrackingRecHitBuilderESProducer",
    ComponentName = cms.string('hltESPTTRHBuilderAngleAndTemplate'),
    ComputeCoarseLocalPositionFromDisk = cms.bool(False),
    Matcher = cms.string('StandardMatcher'),
    Phase2StripCPE = cms.string(''),
    PixelCPE = cms.string('hltESPPixelCPETemplateReco'),
    StripCPE = cms.string('hltESPStripCPEfromTrackAngle'),
    appendToDataLabel = cms.string('')
)


process.hltESPTTRHBuilderPixelOnly = cms.ESProducer("TkTransientTrackingRecHitBuilderESProducer",
    ComponentName = cms.string('hltESPTTRHBuilderPixelOnly'),
    ComputeCoarseLocalPositionFromDisk = cms.bool(False),
    Matcher = cms.string('StandardMatcher'),
    Phase2StripCPE = cms.string(''),
    PixelCPE = cms.string('hltESPPixelCPEGeneric'),
    StripCPE = cms.string('Fake'),
    appendToDataLabel = cms.string('')
)


process.hltESPTTRHBuilderWithoutAngle4PixelTriplets = cms.ESProducer("TkTransientTrackingRecHitBuilderESProducer",
    ComponentName = cms.string('hltESPTTRHBuilderWithoutAngle4PixelTriplets'),
    ComputeCoarseLocalPositionFromDisk = cms.bool(False),
    Matcher = cms.string('StandardMatcher'),
    Phase2StripCPE = cms.string(''),
    PixelCPE = cms.string('hltESPPixelCPEGeneric'),
    StripCPE = cms.string('Fake'),
    appendToDataLabel = cms.string('')
)


process.hltESPTobTecStepChi2ChargeMeasurementEstimator16 = cms.ESProducer("Chi2ChargeMeasurementEstimatorESProducer",
    ComponentName = cms.string('hltESPTobTecStepChi2ChargeMeasurementEstimator16'),
    MaxChi2 = cms.double(16.0),
    MaxDisplacement = cms.double(0.5),
    MaxSagitta = cms.double(2.0),
    MinPtForHitRecoveryInGluedDet = cms.double(1000000.0),
    MinimalTolerance = cms.double(0.5),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    nSigma = cms.double(3.0),
    pTChargeCutThreshold = cms.double(-1.0)
)


process.hltESPTobTecStepClusterShapeHitFilter = cms.ESProducer("ClusterShapeHitFilterESProducer",
    ComponentName = cms.string('hltESPTobTecStepClusterShapeHitFilter'),
    PixelShapeFile = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_noL1.par'),
    PixelShapeFileL1 = cms.string('RecoPixelVertexing/PixelLowPtUtilities/data/pixelShapePhase1_loose.par'),
    appendToDataLabel = cms.string(''),
    clusterChargeCut = cms.PSet(
        refToPSet_ = cms.string('HLTSiStripClusterChargeCutTight')
    ),
    doPixelShapeCut = cms.bool(True),
    doStripShapeCut = cms.bool(True),
    isPhase2 = cms.bool(False)
)


process.hltESPTobTecStepFittingSmoother = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(False),
    ComponentName = cms.string('hltESPTobTecStepFitterSmoother'),
    EstimateCut = cms.double(30.0),
    Fitter = cms.string('hltESPTobTecStepRKFitter'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-16.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(7),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(False),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPTobTecStepRKSmoother'),
    appendToDataLabel = cms.string('')
)


process.hltESPTobTecStepFittingSmootherForLoopers = cms.ESProducer("KFFittingSmootherESProducer",
    BreakTrajWith2ConsecutiveMissing = cms.bool(False),
    ComponentName = cms.string('hltESPTobTecStepFitterSmootherForLoopers'),
    EstimateCut = cms.double(30.0),
    Fitter = cms.string('hltESPTobTecStepRKFitterForLoopers'),
    HighEtaSwitch = cms.double(5.0),
    LogPixelProbabilityCut = cms.double(-16.0),
    MaxFractionOutliers = cms.double(0.3),
    MaxNumberOfOutliers = cms.int32(3),
    MinDof = cms.int32(2),
    MinNumberOfHits = cms.int32(7),
    MinNumberOfHitsHighEta = cms.int32(5),
    NoInvalidHitsBeginEnd = cms.bool(False),
    NoOutliersBeginEnd = cms.bool(False),
    RejectTracks = cms.bool(True),
    Smoother = cms.string('hltESPTobTecStepRKSmootherForLoopers'),
    appendToDataLabel = cms.string('')
)


process.hltESPTobTecStepFlexibleKFFittingSmoother = cms.ESProducer("FlexibleKFFittingSmootherESProducer",
    ComponentName = cms.string('hltESPTobTecStepFlexibleKFFittingSmoother'),
    appendToDataLabel = cms.string(''),
    looperFitter = cms.string('hltESPTobTecStepFitterSmootherForLoopers'),
    standardFitter = cms.string('hltESPTobTecStepFitterSmoother')
)


process.hltESPTobTecStepRKTrajectoryFitter = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPTobTecStepRKFitter'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(7)
)


process.hltESPTobTecStepRKTrajectoryFitterForLoopers = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPTobTecStepRKFitterForLoopers'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialForLoopers'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(7)
)


process.hltESPTobTecStepRKTrajectorySmoother = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPTobTecStepRKSmoother'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialParabolicMf'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(10.0),
    minHits = cms.int32(7)
)


process.hltESPTobTecStepRKTrajectorySmootherForLoopers = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPTobTecStepRKSmootherForLoopers'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('PropagatorWithMaterialForLoopers'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(10.0),
    minHits = cms.int32(7)
)


process.hltESPTobTecStepTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPTobTecStepTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(20.0),
    ValidHitBonus = cms.double(5.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.09)
)


process.hltESPTrackAlgoPriorityOrder = cms.ESProducer("TrackAlgoPriorityOrderESProducer",
    ComponentName = cms.string('hltESPTrackAlgoPriorityOrder'),
    algoOrder = cms.vstring(),
    appendToDataLabel = cms.string('')
)


process.hltESPTrackerRecoGeometryESProducer = cms.ESProducer("TrackerRecoGeometryESProducer",
    appendToDataLabel = cms.string(''),
    trackerGeometryLabel = cms.untracked.string(''),
    usePhase2Stacks = cms.bool(False)
)


process.hltESPTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('hltESPTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(0.0),
    ValidHitBonus = cms.double(100.0),
    allowSharedFirstHit = cms.bool(False),
    fractionShared = cms.double(0.5)
)


process.hltESPTrajectoryFitterRK = cms.ESProducer("KFTrajectoryFitterESProducer",
    ComponentName = cms.string('hltESPTrajectoryFitterRK'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    minHits = cms.int32(3)
)


process.hltESPTrajectorySmootherRK = cms.ESProducer("KFTrajectorySmootherESProducer",
    ComponentName = cms.string('hltESPTrajectorySmootherRK'),
    Estimator = cms.string('hltESPChi2MeasurementEstimator30'),
    Propagator = cms.string('hltESPRungeKuttaTrackerPropagator'),
    RecoGeometry = cms.string('hltESPDummyDetLayerGeometry'),
    Updator = cms.string('hltESPKFUpdator'),
    appendToDataLabel = cms.string(''),
    errorRescaling = cms.double(100.0),
    minHits = cms.int32(3)
)


process.hltOnlineBeamSpotESProducer = cms.ESProducer("OnlineBeamSpotESProducer",
    appendToDataLabel = cms.string(''),
    sigmaZThreshold = cms.double(2.0),
    timeThreshold = cms.int32(1000000)
)


process.hltPixelTracksCleanerBySharedHits = cms.ESProducer("PixelTrackCleanerBySharedHitsESProducer",
    ComponentName = cms.string('hltPixelTracksCleanerBySharedHits'),
    appendToDataLabel = cms.string(''),
    useQuadrupletAlgo = cms.bool(False)
)


process.hltTrackCleaner = cms.ESProducer("TrackCleanerESProducer",
    ComponentName = cms.string('hltTrackCleaner'),
    appendToDataLabel = cms.string('')
)


process.hoDetIdAssociator = cms.ESProducer("DetIdAssociatorESProducer",
    ComponentName = cms.string('HODetIdAssociator'),
    etaBinSize = cms.double(0.087),
    hcalRegion = cms.int32(2),
    includeBadChambers = cms.bool(False),
    includeGEM = cms.bool(False),
    includeME0 = cms.bool(False),
    nEta = cms.int32(30),
    nPhi = cms.int32(72)
)


process.multipleScatteringParametrisationMakerESProducer = cms.ESProducer("MultipleScatteringParametrisationMakerESProducer",
    appendToDataLabel = cms.string('')
)


process.muonDetIdAssociator = cms.ESProducer("DetIdAssociatorESProducer",
    ComponentName = cms.string('MuonDetIdAssociator'),
    etaBinSize = cms.double(0.125),
    hcalRegion = cms.int32(2),
    includeBadChambers = cms.bool(False),
    includeGEM = cms.bool(False),
    includeME0 = cms.bool(False),
    nEta = cms.int32(48),
    nPhi = cms.int32(48)
)


process.muonSeededTrajectoryCleanerBySharedHits = cms.ESProducer("TrajectoryCleanerESProducer",
    ComponentName = cms.string('muonSeededTrajectoryCleanerBySharedHits'),
    ComponentType = cms.string('TrajectoryCleanerBySharedHits'),
    MissingHitPenalty = cms.double(1.0),
    ValidHitBonus = cms.double(1000.0),
    allowSharedFirstHit = cms.bool(True),
    fractionShared = cms.double(0.1)
)


process.navigationSchoolESProducer = cms.ESProducer("NavigationSchoolESProducer",
    ComponentName = cms.string('SimpleNavigationSchool'),
    SimpleMagneticField = cms.string('ParabolicMf')
)


process.preshowerDetIdAssociator = cms.ESProducer("DetIdAssociatorESProducer",
    ComponentName = cms.string('PreshowerDetIdAssociator'),
    etaBinSize = cms.double(0.1),
    hcalRegion = cms.int32(2),
    includeBadChambers = cms.bool(False),
    includeGEM = cms.bool(False),
    includeME0 = cms.bool(False),
    nEta = cms.int32(60),
    nPhi = cms.int32(30)
)


process.siPixelGainCalibrationForHLTGPU = cms.ESProducer("SiPixelGainCalibrationForHLTGPUESProducer",
    appendToDataLabel = cms.string('')
)


process.siPixelQualityESProducer = cms.ESProducer("SiPixelQualityESProducer",
    siPixelQualityLabel = cms.string('')
)


process.siPixelROCsStatusAndMappingWrapperESProducer = cms.ESProducer("SiPixelROCsStatusAndMappingWrapperESProducer",
    CablingMapLabel = cms.string(''),
    ComponentName = cms.string(''),
    UseQualityInfo = cms.bool(False),
    appendToDataLabel = cms.string('')
)


process.siPixelTemplateDBObjectESProducer = cms.ESProducer("SiPixelTemplateDBObjectESProducer")


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


process.sistripconn = cms.ESProducer("SiStripConnectivity")


process.trackerTopology = cms.ESProducer("TrackerTopologyEP",
    appendToDataLabel = cms.string('')
)


process.CSCChannelMapperESSource = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('CSCChannelMapperRecord')
)


process.CSCINdexerESSource = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('CSCIndexerRecord')
)


process.CSCL1TPLookupTableEP = cms.ESSource("CSCL1TPLookupTableEP",
    esDiffToSlopeME11aFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11a_even_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11a_odd_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11a_even_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11a_odd_GEMlayer2.txt'
    ),
    esDiffToSlopeME11bFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11b_even_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11b_odd_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11b_even_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME11b_odd_GEMlayer2.txt'
    ),
    esDiffToSlopeME21Files = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME21_even_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME21_odd_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME21_even_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/BendingAngle/SlopeAmendment_ME21_odd_GEMlayer2.txt'
    ),
    gemCscSlopeCorrectionFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11a_even_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11b_even_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME21_even_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11a_odd_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11b_odd_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME21_odd_GEMlayer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11a_even_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11b_even_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME21_even_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11a_odd_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME11b_odd_GEMlayer2.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/ExtrapolationBySlope_ME21_odd_GEMlayer2.txt'
    ),
    gemCscSlopeCosiCorrectionFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/GEMCSCconsistentSlopeCorr_ME11a_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/GEMCSCconsistentSlopeCorr_ME11b_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/GEMCSCconsistentSlopeCorr_ME21_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/GEMCSCconsistentSlopeCorr_ME11a_odd_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/GEMCSCconsistentSlopeCorr_ME11b_odd_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/GEMCSCconsistentSlopeCorr_ME21_odd_layer1.txt'
    ),
    gemCscSlopeCosiFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_2to1_SlopeShift_ME11a_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_2to1_SlopeShift_ME11a_odd_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_3to1_SlopeShift_ME11a_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_3to1_SlopeShift_ME11a_odd_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_2to1_SlopeShift_ME11b_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_2to1_SlopeShift_ME11b_odd_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_3to1_SlopeShift_ME11b_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_3to1_SlopeShift_ME11b_odd_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_2to1_SlopeShift_ME21_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_2to1_SlopeShift_ME21_odd_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_3to1_SlopeShift_ME21_even_layer1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/SlopeCorrection/FacingChambers/CSCconsistency_3to1_SlopeShift_ME21_odd_layer1.txt'
    ),
    padToEsME11aFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_pad_es_ME1a_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_pad_es_ME1a_odd.txt'
    ),
    padToEsME11bFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_pad_es_ME1b_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_pad_es_ME1b_odd.txt'
    ),
    padToEsME21Files = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_pad_es_ME21_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_pad_es_ME21_odd.txt'
    ),
    positionLUTFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodePosOffsetLUT_pat0_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodePosOffsetLUT_pat1_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodePosOffsetLUT_pat2_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodePosOffsetLUT_pat3_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodePosOffsetLUT_pat4_v1.txt'
    ),
    rollToMaxWgME11Files = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_max_wg_ME11_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_max_wg_ME11_odd.txt'
    ),
    rollToMaxWgME21Files = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_max_wg_ME21_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_max_wg_ME21_odd.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l2_max_wg_ME21_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l2_max_wg_ME21_odd.txt'
    ),
    rollToMinWgME11Files = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_min_wg_ME11_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_min_wg_ME11_odd.txt'
    ),
    rollToMinWgME21Files = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_min_wg_ME21_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l1_min_wg_ME21_odd.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l2_min_wg_ME21_even.txt',
        'L1Trigger/CSCTriggerPrimitives/data/GEMCSC/CoordinateConversion/GEMCSCLUT_roll_l2_min_wg_ME21_odd.txt'
    ),
    slopeLUTFiles = cms.vstring(
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodeSlopeLUT_pat0_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodeSlopeLUT_pat1_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodeSlopeLUT_pat2_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodeSlopeLUT_pat3_v1.txt',
        'L1Trigger/CSCTriggerPrimitives/data/CCLUT/CSCComparatorCodeSlopeLUT_pat4_v1.txt'
    )
)


process.GlobalParametersRcdSource = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('L1TGlobalParametersRcd')
)


process.GlobalTag = cms.ESSource("PoolDBESSource",
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string('.'),
        connectionRetrialPeriod = cms.untracked.int32(10),
        connectionRetrialTimeOut = cms.untracked.int32(60),
        connectionTimeOut = cms.untracked.int32(0),
        enableConnectionSharing = cms.untracked.bool(True),
        enablePoolAutomaticCleanUp = cms.untracked.bool(False),
        enableReadOnlySessionOnUpdateConnection = cms.untracked.bool(False),
        idleConnectionCleanupPeriod = cms.untracked.int32(10),
        messageLevel = cms.untracked.int32(0)
    ),
    DumpStat = cms.untracked.bool(False),
    ReconnectEachRun = cms.untracked.bool(False),
    RefreshAlways = cms.untracked.bool(False),
    RefreshEachRun = cms.untracked.bool(False),
    RefreshOpenIOVs = cms.untracked.bool(False),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
    globaltag = cms.string('124X_mcRun3_2022_realistic_HI_v10'),
    pfnPostfix = cms.untracked.string('None'),
    snapshotTime = cms.string(''),
    toGet = cms.VPSet(
        cms.PSet(
            record = cms.string('BeamSpotOnlineLegacyObjectsRcd'),
            refreshTime = cms.uint64(2)
        ),
        cms.PSet(
            record = cms.string('BeamSpotOnlineHLTObjectsRcd'),
            refreshTime = cms.uint64(2)
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
            slope = cms.double(-1.5610227),
            tmax = cms.double(10.0),
            tzero = cms.double(11.977461)
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


process.bmbtfParamsSource = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('L1TMuonBarrelParamsRcd')
)


process.caloConfigSource = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('L1TCaloConfigRcd')
)


process.ecalMultifitParametersGPUESProducer = cms.ESSource("EcalMultifitParametersGPUESProducer",
    EBamplitudeFitParameters = cms.vdouble(1.138, 1.652),
    EBtimeFitParameters = cms.vdouble(
        -2.015452, 3.130702, -12.3473, 41.88921, -82.83944,
        91.01147, -50.35761, 11.05621
    ),
    EEamplitudeFitParameters = cms.vdouble(1.89, 1.4),
    EEtimeFitParameters = cms.vdouble(
        -2.390548, 3.553628, -17.62341, 67.67538, -133.213,
        140.7432, -75.41106, 16.20277
    ),
    appendToDataLabel = cms.string(''),
    pulseOffsets = cms.vint32(
        -3, -2, -1, 0, 1,
        2, 3, 4
    )
)


process.ecalRecHitParametersGPUESProducer = cms.ESSource("EcalRecHitParametersGPUESProducer",
    ChannelStatusToBeExcluded = cms.vstring(
        'kDAC',
        'kNoisy',
        'kNNoisy',
        'kFixedG6',
        'kFixedG1',
        'kFixedG0',
        'kNonRespondingIsolated',
        'kDeadVFE',
        'kDeadFE',
        'kNoDataNoTP'
    ),
    appendToDataLabel = cms.string(''),
    flagsMapDBReco = cms.PSet(
        kDead = cms.vstring('kNoDataNoTP'),
        kGood = cms.vstring(
            'kOk',
            'kDAC',
            'kNoLaser',
            'kNoisy'
        ),
        kNeighboursRecovered = cms.vstring(
            'kFixedG0',
            'kNonRespondingIsolated',
            'kDeadVFE'
        ),
        kNoisy = cms.vstring(
            'kNNoisy',
            'kFixedG6',
            'kFixedG1'
        ),
        kTowerRecovered = cms.vstring('kDeadFE')
    )
)


process.eegeom = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('EcalMappingRcd')
)


process.es_hardcode = cms.ESSource("HcalHardcodeCalibrations",
    fromDDD = cms.untracked.bool(False),
    toGet = cms.untracked.vstring('GainWidths')
)


process.hcalMahiPulseOffsetsGPUESProducer = cms.ESSource("HcalMahiPulseOffsetsGPUESProducer",
    appendToDataLabel = cms.string(''),
    pulseOffsets = cms.vint32(
        -3, -2, -1, 0, 1,
        2, 3, 4
    )
)


process.hltESSBTagRecord = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('JetTagComputerRecord')
)


process.hltESSEcalSeverityLevel = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('EcalSeverityLevelAlgoRcd')
)


process.hltESSHcalSeverityLevel = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('HcalSeverityLevelComputerRcd')
)


process.l1ugmtdb = cms.ESSource("PoolDBESSource",
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        connectionTimeout = cms.untracked.int32(0),
        messageLevel = cms.untracked.int32(0),
        security = cms.untracked.string('')
    ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
    toGet = cms.VPSet(cms.PSet(
        record = cms.string('L1TMuonGlobalParamsO2ORcd'),
        tag = cms.string('L1TMuonGlobalParamsPrototype_Stage2v0_hlt')
    ))
)


process.ppsPixelTopologyESSource = cms.ESSource("PPSPixelTopologyESSource",
    PitchSimX = cms.double(0.1),
    PitchSimY = cms.double(0.15),
    RunType = cms.string('Run3'),
    activeEdgeSigma = cms.double(0.02),
    appendToDataLabel = cms.string(''),
    deadEdgeWidth = cms.double(0.2),
    noOfPixelSimX = cms.int32(160),
    noOfPixelSimY = cms.int32(104),
    noOfPixels = cms.int32(16640),
    physActiveEdgeDist = cms.double(0.15),
    simXWidth = cms.double(16.6),
    simYWidth = cms.double(16.2),
    thickness = cms.double(0.23)
)


process.rpcconesrc = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('L1RPCConeBuilderRcd')
)


process.twinmuxParamsSource = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('L1TTwinMuxParamsRcd')
)


process.prefer("L1TriggerMenu")

process.SimL1TCalorimeterTask = cms.Task(process.simCaloStage2Digis, process.simCaloStage2Layer1Digis)


process.SimL1TGlobalTask = cms.Task(process.simGtStage2Digis)


process.SimL1TMuonCommonTask = cms.Task(process.simCscTriggerPrimitiveDigis, process.simDtTriggerPrimitiveDigis)


process.SimL1TechnicalTriggersTask = cms.Task(process.simGtExtFakeStage2Digis)


process.simMuonGEMPadTask = cms.Task(process.simMuonGEMPadDigiClusters, process.simMuonGEMPadDigis)


process.SimL1TMuonTask = cms.Task(process.SimL1TMuonCommonTask, process.simBmtfDigis, process.simCscTriggerPrimitiveDigisRun3, process.simEmtfDigis, process.simEmtfShowers, process.simGmtCaloSumDigis, process.simGmtShowerDigis, process.simGmtStage2Digis, process.simKBmtfDigis, process.simKBmtfStubs, process.simMuonGEMPadTask, process.simOmtfDigis, process.simTwinMuxDigis)


process.SimL1EmulatorCoreTask = cms.Task(process.SimL1TCalorimeterTask, process.SimL1TGlobalTask, process.SimL1TMuonTask, process.SimL1TechnicalTriggersTask)


process.SimL1EmulatorTask = cms.Task(process.SimL1EmulatorCoreTask, process.packCaloStage2, process.packGmtStage2, process.packGtStage2, process.rawDataCollector, process.simHcalTriggerPrimitiveDigis, process.unpackCSC, process.unpackDT, process.unpackEcal, process.unpackHcal, process.unpackRPC)


process.HLTDoFullUnpackingEgammaEcalWithoutPreshowerTask = cms.ConditionalTask(process.hltEcalDetIdToBeRecovered, process.hltEcalDigis, process.hltEcalDigisFromGPU, process.hltEcalDigisGPU, process.hltEcalDigisLegacy, process.hltEcalRecHit, process.hltEcalRecHitWithTPs, process.hltEcalRecHitWithoutTPs, process.hltEcalUncalibRecHit, process.hltEcalUncalibRecHitFromSoA, process.hltEcalUncalibRecHitGPU, process.hltEcalUncalibRecHitLegacy, process.hltEcalUncalibRecHitSoA)


process.HLTDoLocalHcalTask = cms.ConditionalTask(process.hltHbhereco, process.hltHbherecoFromGPU, process.hltHbherecoGPU, process.hltHbherecoLegacy, process.hltHcalDigis, process.hltHcalDigisGPU, process.hltHfprereco, process.hltHfreco, process.hltHoreco)


process.HLTPreshowerTask = cms.ConditionalTask(process.hltEcalPreshowerDigis, process.hltEcalPreshowerRecHit)


process.HLTL1UnpackerSequence = cms.Sequence(process.hltGtStage2Digis+process.hltGtStage2ObjectMap)


process.HLTBeamSpot = cms.Sequence(process.hltScalersRawToDigi+process.hltOnlineMetaDataDigis+process.hltOnlineBeamSpot)


process.HLTBeginSequence = cms.Sequence(process.hltTriggerType+process.HLTL1UnpackerSequence+process.HLTBeamSpot)


process.HLTDoFullUnpackingEgammaEcalWithoutPreshowerSequence = cms.Sequence(process.HLTDoFullUnpackingEgammaEcalWithoutPreshowerTask)


process.HLTDoLocalHcalSequence = cms.Sequence(process.HLTDoLocalHcalTask)


process.HLTDoCaloSequence = cms.Sequence(process.HLTDoFullUnpackingEgammaEcalWithoutPreshowerSequence+process.HLTDoLocalHcalSequence+process.hltTowerMakerForAll)


process.HLTPuAK4CaloJetsReconstructionSequence = cms.Sequence(process.HLTDoCaloSequence+process.hltPuAK4CaloJets+process.hltPuAK4CaloJetsIDPassed)


process.HLTPuAK4CaloCorrectorProducersSequence = cms.Sequence(process.hltAK4CaloFastJetCorrector+process.hltAK4CaloRelativeCorrector+process.hltAK4CaloAbsoluteCorrector+process.hltPuAK4CaloCorrector)


process.HLTPuAK4CaloJetsCorrectionSequence = cms.Sequence(process.hltFixedGridRhoFastjetAllCalo+process.HLTPuAK4CaloCorrectorProducersSequence+process.hltPuAK4CaloJetsCorrected+process.hltPuAK4CaloJetsCorrectedIDPassed)


process.HLTPuAK4CaloJetsSequence = cms.Sequence(process.HLTPuAK4CaloJetsReconstructionSequence+process.HLTPuAK4CaloJetsCorrectionSequence)


process.HLTDoHIStripZeroSuppression = cms.Sequence(process.hltSiStripRawToDigi+process.hltSiStripZeroSuppression+process.hltSiStripDigiToZSRaw+process.rawDataRepacker+process.rawDataReducedFormat)


process.HLTEndSequence = cms.Sequence(process.hltBoolEnd)


process.HLTDoCaloSequencePF = cms.Sequence(process.HLTDoFullUnpackingEgammaEcalWithoutPreshowerSequence+process.HLTDoLocalHcalSequence+process.hltTowerMakerForAll)


process.HLTAK4CaloJetsPrePFRecoSequence = cms.Sequence(process.HLTDoCaloSequencePF+process.hltAK4CaloJetsPF)


process.HLTPreAK4PFJetsRecoSequence = cms.Sequence(process.HLTAK4CaloJetsPrePFRecoSequence+process.hltAK4CaloJetsPFEt5)


process.HLTMuonLocalRecoSequence = cms.Sequence(process.hltMuonDTDigis+process.hltDt1DRecHits+process.hltDt4DSegments+process.hltMuonCSCDigis+process.hltCsc2DRecHits+process.hltCscSegments+process.hltMuonRPCDigis+process.hltRpcRecHits+process.hltMuonGEMDigis+process.hltGemRecHits+process.hltGemSegments)


process.HLTL2muonrecoNocandSequencePPOnAA = cms.Sequence(process.HLTMuonLocalRecoSequence+process.hltL2OfflineMuonSeeds+process.hltL2MuonSeedsPPOnAA+process.hltL2MuonsPPOnAA)


process.HLTL2muonrecoSequencePPOnAA = cms.Sequence(process.HLTL2muonrecoNocandSequencePPOnAA+process.hltL2MuonCandidatesPPOnAA)


process.HLTDoSiStripZeroSuppression = cms.Sequence(process.hltSiStripRawToDigi+process.hltSiStripZeroSuppression)


process.HLTDoLocalPixelSequencePPOnAA = cms.Sequence(process.hltSiPixelDigisPPOnAA+process.hltSiPixelClustersPPOnAA+process.hltSiPixelClustersCachePPOnAA+process.hltSiPixelRecHitsPPOnAA)


process.HLTDoLocalStripSequencePPOnAA = cms.Sequence(process.hltSiStripExcludedFEDListProducer+process.hltHITrackingSiStripRawToClustersFacilityZeroSuppression+process.hltSiStripClustersPPOnAA)


process.HLTIterL3OImuonTkCandidatePPOnAASequence = cms.Sequence(process.hltIterL3OISeedsFromL2MuonsPPOnAA+process.hltIterL3OITrackCandidatesPPOnAA+process.hltIterL3OIMuCtfWithMaterialTracksPPOnAA+process.hltIterL3OIMuonTrackCutClassifierPPOnAA+process.hltIterL3OIMuonTrackSelectionHighPurityPPOnAA+process.hltL3MuonsIterL3OIPPOnAA)


process.HLTIterL3MuonRecoPixelTracksPPOnAASequence = cms.Sequence(process.hltIterL3MuonPixelTracksFilter+process.hltIterL3MuonPixelTracksFitter+process.hltIterL3MuonPixelTracksTrackingRegionsPPOnAA+process.hltIterL3MuonPixelLayerQuadrupletsPPOnAA+process.hltIterL3MuonPixelTracksHitDoubletsPPOnAA+process.hltIterL3MuonPixelTracksHitQuadrupletsPPOnAA+process.hltIterL3MuonPixelTracksPPOnAA)


process.HLTIterL3MuonRecopixelvertexingPPOnAASequence = cms.Sequence(process.HLTIterL3MuonRecoPixelTracksPPOnAASequence+process.hltIterL3MuonPixelVerticesPPOnAA+process.hltIterL3MuonTrimmedPixelVerticesPPOnAA)


process.HLTIterativeTrackingIteration0ForIterL3MuonPPOnAA = cms.Sequence(process.hltIter0IterL3MuonPixelSeedsFromPixelTracksPPOnAA+process.hltIter0IterL3MuonCkfTrackCandidatesPPOnAA+process.hltIter0IterL3MuonCtfWithMaterialTracksPPOnAA+process.hltIter0IterL3MuonTrackCutClassifierPPOnAA+process.hltIter0IterL3MuonTrackSelectionHighPurityPPOnAA)


process.HLTIterativeTrackingIteration2ForIterL3MuonPPOnAA = cms.Sequence(process.hltIter2IterL3MuonClustersRefRemovalPPOnAA+process.hltIter2IterL3MuonMaskedMeasurementTrackerEventPPOnAA+process.hltIter2IterL3MuonPixelLayerTripletsPPOnAA+process.hltIter2IterL3MuonPixelClusterCheckPPOnAA+process.hltIter2IterL3MuonPixelHitDoubletsPPOnAA+process.hltIter2IterL3MuonPixelHitTripletsPPOnAA+process.hltIter2IterL3MuonPixelSeedsPPOnAA+process.hltIter2IterL3MuonCkfTrackCandidatesPPOnAA+process.hltIter2IterL3MuonCtfWithMaterialTracksPPOnAA+process.hltIter2IterL3MuonTrackCutClassifierPPOnAA+process.hltIter2IterL3MuonTrackSelectionHighPurityPPOnAA)


process.HLTIterativeTrackingIteration3ForIterL3MuonPPOnAA = cms.Sequence(process.hltIter3IterL3MuonClustersRefRemovalPPOnAA+process.hltIter3IterL3MuonMaskedMeasurementTrackerEventPPOnAA+process.hltIter3IterL3MuonPixelLayerPairsPPOnAA+process.hltIter3IterL3MuonL2CandidatesPPOnAA+process.hltIter3IterL3MuonTrackingRegionsPPOnAA+process.hltIter3IterL3MuonPixelClusterCheckPPOnAA+process.hltIter3IterL3MuonPixelHitDoubletsPPOnAA+process.hltIter3IterL3MuonPixelSeedsPPOnAA+process.hltIter3IterL3MuonCkfTrackCandidatesPPOnAA+process.hltIter3IterL3MuonCtfWithMaterialTracksPPOnAA+process.hltIter3IterL3MuonTrackCutClassifierPPOnAA+process.hltIter3IterL3MuonTrackSelectionHighPurityPPOnAA)


process.HLTIterativeTrackingIter023ForIterL3MuonPPOnAA = cms.Sequence(process.HLTIterativeTrackingIteration0ForIterL3MuonPPOnAA+process.HLTIterativeTrackingIteration2ForIterL3MuonPPOnAA+process.hltIter2IterL3MuonMergedPPOnAA+process.HLTIterativeTrackingIteration3ForIterL3MuonPPOnAA+process.hltIter3IterL3MuonMergedPPOnAA)


process.HLTIterL3IOmuonTkCandidatePPOnAASequence = cms.Sequence(process.HLTIterL3MuonRecopixelvertexingPPOnAASequence+process.HLTIterativeTrackingIter023ForIterL3MuonPPOnAA+process.hltL3MuonsIterL3IOPPOnAA)


process.HLTIterL3OIAndIOFromL2muonTkCandidatePPOnAASequence = cms.Sequence(process.HLTIterL3OImuonTkCandidatePPOnAASequence+process.hltIterL3OIL3MuonsLinksCombinationPPOnAA+process.hltIterL3OIL3MuonsPPOnAA+process.hltIterL3OIL3MuonCandidatesPPOnAA+process.hltL2SelectorForL3IOPPOnAA+process.HLTIterL3IOmuonTkCandidatePPOnAASequence+process.hltIterL3MuonsFromL2LinksCombinationPPOnAA)


process.HLTRecoPixelTracksSequenceForIterL3FromL1MuonPPOnAA = cms.Sequence(process.hltIterL3FromL1MuonPixelTracksTrackingRegionsPPOnAA+process.hltIterL3FromL1MuonPixelLayerQuadrupletsPPOnAA+process.hltIterL3FromL1MuonPixelTracksHitDoubletsPPOnAA+process.hltIterL3FromL1MuonPixelTracksHitQuadrupletsPPOnAA+process.hltIterL3FromL1MuonPixelTracksPPOnAA)


process.HLTRecopixelvertexingSequenceForIterL3FromL1MuonPPOnAA = cms.Sequence(process.HLTRecoPixelTracksSequenceForIterL3FromL1MuonPPOnAA+process.hltIterL3FromL1MuonPixelVerticesPPOnAA+process.hltIterL3FromL1MuonTrimmedPixelVerticesPPOnAA)


process.HLTIterativeTrackingIteration0ForIterL3FromL1MuonPPOnAA = cms.Sequence(process.hltIter0IterL3FromL1MuonPixelSeedsFromPixelTracksPPOnAA+process.hltIter0IterL3FromL1MuonCkfTrackCandidatesPPOnAA+process.hltIter0IterL3FromL1MuonCtfWithMaterialTracksPPOnAA+process.hltIter0IterL3FromL1MuonTrackCutClassifierPPOnAA+process.hltIter0IterL3FromL1MuonTrackSelectionHighPurityPPOnAA)


process.HLTIterativeTrackingIteration2ForIterL3FromL1MuonPPOnAA = cms.Sequence(process.hltIter2IterL3FromL1MuonClustersRefRemovalPPOnAA+process.hltIter2IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA+process.hltIter2IterL3FromL1MuonPixelLayerTripletsPPOnAA+process.hltIter2IterL3FromL1MuonPixelClusterCheckPPOnAA+process.hltIter2IterL3FromL1MuonPixelHitDoubletsPPOnAA+process.hltIter2IterL3FromL1MuonPixelHitTripletsPPOnAA+process.hltIter2IterL3FromL1MuonPixelSeedsPPOnAA+process.hltIter2IterL3FromL1MuonCkfTrackCandidatesPPOnAA+process.hltIter2IterL3FromL1MuonCtfWithMaterialTracksPPOnAA+process.hltIter2IterL3FromL1MuonTrackCutClassifierPPOnAA+process.hltIter2IterL3FromL1MuonTrackSelectionHighPurityPPOnAA)


process.HLTIterativeTrackingIteration3ForIterL3FromL1MuonPPOnAA = cms.Sequence(process.hltIter3IterL3FromL1MuonClustersRefRemovalPPOnAA+process.hltIter3IterL3FromL1MuonMaskedMeasurementTrackerEventPPOnAA+process.hltIter3IterL3FromL1MuonPixelLayerPairsPPOnAA+process.hltIter3IterL3FromL1MuonTrackingRegionsPPOnAA+process.hltIter3IterL3FromL1MuonPixelClusterCheckPPOnAA+process.hltIter3IterL3FromL1MuonPixelHitDoubletsPPOnAA+process.hltIter3IterL3FromL1MuonPixelSeedsPPOnAA+process.hltIter3IterL3FromL1MuonCkfTrackCandidatesPPOnAA+process.hltIter3IterL3FromL1MuonCtfWithMaterialTracksPPOnAA+process.hltIter3IterL3FromL1MuonTrackCutClassifierPPOnAA+process.hltIter3IterL3FromL1MuonTrackSelectionHighPurityPPOnAA)


process.HLTIterativeTrackingIter023ForIterL3FromL1MuonPPOnAA = cms.Sequence(process.HLTIterativeTrackingIteration0ForIterL3FromL1MuonPPOnAA+process.HLTIterativeTrackingIteration2ForIterL3FromL1MuonPPOnAA+process.hltIter2IterL3FromL1MuonMergedPPOnAA+process.HLTIterativeTrackingIteration3ForIterL3FromL1MuonPPOnAA+process.hltIter3IterL3FromL1MuonMergedPPOnAA)


process.HLTIterL3IOmuonFromL1TkCandidatePPOnAASequence = cms.Sequence(process.HLTRecopixelvertexingSequenceForIterL3FromL1MuonPPOnAA+process.HLTIterativeTrackingIter023ForIterL3FromL1MuonPPOnAA)


process.HLTIterL3muonTkCandidatePPOnAASequence = cms.Sequence(process.HLTDoSiStripZeroSuppression+process.HLTDoLocalPixelSequencePPOnAA+process.HLTDoLocalStripSequencePPOnAA+process.HLTIterL3OIAndIOFromL2muonTkCandidatePPOnAASequence+process.hltL1MuonsPt0PPOnAA+process.HLTIterL3IOmuonFromL1TkCandidatePPOnAASequence)


process.HLTL3muonrecoNocandPPOnAASequence = cms.Sequence(process.HLTIterL3muonTkCandidatePPOnAASequence+process.hltIterL3MuonMergedPPOnAA+process.hltIterL3MuonAndMuonFromL1MergedPPOnAA+process.hltIterL3GlbMuonPPOnAA+process.hltIterL3MuonsNoIDPPOnAA+process.hltIterL3MuonsPPOnAA+process.hltL3MuonsIterL3LinksPPOnAA+process.hltIterL3MuonTracksPPOnAA)


process.HLTL3muonrecoPPOnAASequence = cms.Sequence(process.HLTL3muonrecoNocandPPOnAASequence+process.hltIterL3MuonCandidatesPPOnAA)


process.HLTFullIterativeTrackingIteration0PreSplittingPPOnAA = cms.Sequence(process.hltFullIter0PixelQuadrupletsPreSplittingPPOnAA+process.hltFullIter0PixelTrackingRegionsPreSplitting+process.hltFullIter0PixelClusterCheckPreSplittingPPOnAA+process.hltFullIter0PixelHitDoubletsPreSplittingPPOnAA+process.hltFullIter0PixelHitQuadrupletsPreSplittingPPOnAA+process.hltFullIter0PixelSeedsPreSplittingPPOnAA+process.hltFullIter0CkfTrackCandidatesPreSplittingPPOnAA+process.hltFullIter0CtfWithMaterialTracksPreSplittingPPOnAA+process.hltFullIter0PrimaryVerticesPreSplittingPPOnAA)


process.HLTDoLocalPixelSequenceAfterSplittingPPOnAA = cms.Sequence(process.hltSiPixelClustersAfterSplittingPPOnAA+process.hltSiPixelClustersCacheAfterSplittingPPOnAA+process.hltSiPixelRecHitsAfterSplittingPPOnAA)


process.HLTDoLocalStripSequenceFullPPOnAA = cms.Sequence(process.hltSiStripExcludedFEDListProducer+process.hltHITrackingSiStripRawToClustersFacilityFullZeroSuppression+process.hltSiStripClustersFullPPOnAA+process.hltSiStripMatchedRecHitsFull)


process.HLTPixelClusterSplittingForPFPPOnAA = cms.Sequence(process.HLTDoSiStripZeroSuppression+process.hltJetsForCoreTracking+process.HLTDoLocalPixelSequencePPOnAA+process.HLTDoLocalStripSequencePPOnAA+process.HLTFullIterativeTrackingIteration0PreSplittingPPOnAA+process.HLTDoLocalPixelSequenceAfterSplittingPPOnAA+process.HLTDoLocalStripSequenceFullPPOnAA)


process.HLTRecoPixelTracksSequencePPOnAA = cms.Sequence(process.hltPixelTracksFilter+process.hltPixelTracksFitter+process.hltPixelTracksTrackingRegionsPPOnAA+process.hltPixelLayerQuadrupletsPPOnAA+process.hltPixelTracksHitDoubletsPPOnAA+process.hltPixelTracksHitQuadrupletsPPOnAA+process.hltPixelTracksPPOnAA)


process.HLTRecopixelvertexingSequencePPOnAA = cms.Sequence(process.HLTRecoPixelTracksSequencePPOnAA+process.hltPixelVerticesPPOnAA+process.hltTrimmedPixelVerticesPPOnAA)


process.HLTFullIterativeTrackingIteration0PPOnAA = cms.Sequence(process.hltFullIter0PixelQuadrupletsPPOnAA+process.hltFullIter0PixelTrackingRegions+process.hltFullIter0PixelClusterCheckPPOnAA+process.hltFullIter0PixelHitDoubletsPPOnAA+process.hltFullIter0PixelHitQuadrupletsPPOnAA+process.hltFullIter0PixelSeedsPPOnAA+process.hltFullIter0CkfTrackCandidatesPPOnAA+process.hltFullIter0CtfWithMaterialTracksPPOnAA+process.hltFullIter0PrimaryVerticesPPOnAA+process.hltFullIter0TrackMVAClassifierPPOnAA+process.hltFullIter0HighPurityTracksPPOnAA)


process.HLTFullIterativeTrackingIteration1PPOnAA = cms.Sequence(process.hltFullIter1ClustersRefRemovalPPOnAA+process.hltFullIter1MaskedMeasurementTrackerEventPPOnAA+process.hltFullIter1PixelQuadrupletsPPOnAA+process.hltFullIter1PixelTrackingRegionsPPOnAA+process.hltFullIter1PixelClusterCheckPPOnAA+process.hltFullIter1PixelHitDoubletsPPOnAA+process.hltFullIter1PixelHitQuadrupletsPPOnAA+process.hltFullIter1PixelSeedsPPOnAA+process.hltFullIter1CkfTrackCandidatesPPOnAA+process.hltFullIter1CtfWithMaterialTracksPPOnAA+process.hltFullIter1TrackMVAClassifierPPOnAA+process.hltFullIter1HighPurityTracksPPOnAA)


process.HLTIter1TrackAndTauJets4Iter2SequencePPOnAA = cms.Sequence(process.hltIter1TrackRefsForJets4Iter2PPOnAA+process.hltAK4Iter1TrackJets4Iter2PPOnAA+process.hltIter1TrackAndTauJets4Iter2PPOnAA)


process.HLTFullIterativeTrackingIteration2PPOnAA = cms.Sequence(process.hltFullIter2ClustersRefRemovalPPOnAA+process.hltFullIter2MaskedMeasurementTrackerEventPPOnAA+process.hltFullIter2PixelTripletsPPOnAA+process.hltFullIter2PixelTrackingRegionsPPOnAA+process.hltFullIter2PixelClusterCheckPPOnAA+process.hltFullIter2PixelHitDoubletsPPOnAA+process.hltFullIter2PixelHitTripletsPPOnAA+process.hltFullIter2PixelSeedsPPOnAA+process.hltFullIter2CkfTrackCandidatesPPOnAA+process.hltFullIter2CtfWithMaterialTracksPPOnAA+process.hltFullIter2TrackMVAClassifierPPOnAA+process.hltFullIter2HighPurityTracksPPOnAA)


process.HLTIterativeTrackingDoubletRecoveryPPOnAA = cms.Sequence(process.hltDoubletRecoveryClustersRefRemovalPPOnAA+process.hltDoubletRecoveryMaskedMeasurementTrackerEventPPOnAA+process.hltDoubletRecoveryPixelLayersAndRegionsPPOnAA+process.hltDoubletRecoveryPFlowPixelClusterCheckPPOnAA+process.hltDoubletRecoveryPFlowPixelHitDoubletsPPOnAA+process.hltDoubletRecoveryPFlowPixelSeedsPPOnAA+process.hltDoubletRecoveryPFlowCkfTrackCandidatesPPOnAA+process.hltDoubletRecoveryPFlowCtfWithMaterialTracksPPOnAA+process.hltDoubletRecoveryPFlowTrackCutClassifierPPOnAA+process.hltDoubletRecoveryPFlowTrackSelectionHighPurityPPOnAA)


process.HLTFullIterativeTrackingIteration02PPOnAA = cms.Sequence(process.HLTFullIterativeTrackingIteration0PPOnAA+process.HLTFullIterativeTrackingIteration1PPOnAA+process.hltIter1MergedPPOnAA+process.HLTIter1TrackAndTauJets4Iter2SequencePPOnAA+process.HLTFullIterativeTrackingIteration2PPOnAA+process.hltIter2MergedPPOnAA+process.HLTIterativeTrackingDoubletRecoveryPPOnAA+process.hltMergedTracksPPOnAA)


process.HLTTrackReconstructionForPFPPOnAA = cms.Sequence(process.HLTPixelClusterSplittingForPFPPOnAA+process.HLTRecopixelvertexingSequencePPOnAA+process.HLTFullIterativeTrackingIteration02PPOnAA+process.hltPFMuonMergingPPOnAA+process.hltMuonLinksPPOnAA+process.hltMuonsPPOnAA)


process.HLTPreshowerSequence = cms.Sequence(process.HLTPreshowerTask)


process.HLTParticleFlowSequencePPOnAA = cms.Sequence(process.HLTPreshowerSequence+process.hltParticleFlowRecHitECALUnseeded+process.hltParticleFlowRecHitHBHE+process.hltParticleFlowRecHitHF+process.hltParticleFlowRecHitPSUnseeded+process.hltParticleFlowClusterECALUncorrectedUnseeded+process.hltParticleFlowClusterPSUnseeded+process.hltParticleFlowClusterECALUnseeded+process.hltParticleFlowClusterHBHE+process.hltParticleFlowClusterHCAL+process.hltParticleFlowClusterHF+process.hltLightPFTracksPPOnAA+process.hltParticleFlowBlockPPOnAA+process.hltParticleFlowPPOnAA)


process.HLTCsAK4PFJetsReconstructionSequencePPOnAA = cms.Sequence(process.HLTL2muonrecoSequencePPOnAA+process.HLTL3muonrecoPPOnAASequence+process.HLTTrackReconstructionForPFPPOnAA+process.HLTParticleFlowSequencePPOnAA+process.hltKT4PFJetsForRho+process.hltAK4PFJets+process.hltHiFJRhoProducer+process.hltCsAK4PFJetsPPOnAA)


process.HLTCsAK4PFJetsSequence = cms.Sequence(process.HLTPreAK4PFJetsRecoSequence+process.HLTCsAK4PFJetsReconstructionSequencePPOnAA)


process.HLTDoHIStripZeroSuppressionRepacker = cms.Sequence(process.hltSiStripDigiToZSRaw+process.rawDataRepacker+process.rawDataReducedFormat)


process.SimL1Emulator = cms.Sequence(process.SimL1EmulatorTask)


process.HLTriggerFirstPath = cms.Path(process.SimL1Emulator+process.hltGetRaw+process.hltPSetMap+process.hltBoolFalse)


process.HLT_HIPuAK4CaloJet40Eta5p1_v1 = cms.Path(process.SimL1Emulator+process.HLTBeginSequence+process.hltL1sSingleJet28BptxAND+process.hltPreHIPuAK4CaloJet40Eta5p1+process.HLTPuAK4CaloJetsSequence+process.hltSinglePuAK4CaloJet40Eta5p1+process.HLTDoHIStripZeroSuppression+process.HLTEndSequence)


process.HLT_HICsAK4PFJet60Eta1p5_v1 = cms.Path(process.SimL1Emulator+process.HLTBeginSequence+process.hltL1sSingleJet44BptxAND+process.hltPreHICsAK4PFJet60Eta1p5+process.HLTCsAK4PFJetsSequence+process.hltSingleCsPFJet60Eta1p5+process.HLTDoHIStripZeroSuppressionRepacker+process.HLTEndSequence)


process.HLTriggerFinalPath = cms.Path(process.SimL1Emulator+process.hltGtStage2Digis+process.hltScalersRawToDigi+process.hltFEDSelector+process.hltTriggerSummaryAOD+process.hltTriggerSummaryRAW+process.hltBoolFalse)


process.output_path = cms.EndPath(process.output)


process.schedule = cms.Schedule(*[ process.HLTriggerFirstPath, process.HLT_HIPuAK4CaloJet40Eta5p1_v1, process.HLT_HICsAK4PFJet60Eta1p5_v1, process.HLTriggerFinalPath, process.output_path ])
