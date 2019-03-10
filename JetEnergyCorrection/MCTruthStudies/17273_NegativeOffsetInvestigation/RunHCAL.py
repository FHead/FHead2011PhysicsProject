import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

from Geometry.CMSCommonData.cmsIdealGeometryXML_cfi import *
from Geometry.TrackerNumberingBuilder.trackerNumberingGeometry_cfi import *

# Reconstruction geometry services
from Configuration.Geometry.GeometryReco_cff import *

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        # 'file:/afs/cern.ch/user/k/kirschen/public/forJERC/forMCTruthDebugging/pickevents_WithPU.root'
        # 'file:/afs/cern.ch/user/k/kirschen/public/forJERC/forMCTruthDebugging/pickevents_NoPU.root'
        'file:__FILE__.root'
        )
)

process.rechits = cms.EDAnalyzer('HCALAnalyzer',
      HBHEInput = cms.InputTag("reducedHcalRecHits", "hbhereco", "RECO"),
      HOInput = cms.InputTag("horeco"),
      HFInput = cms.InputTag("hfreco")
      )

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("HCAL___FILE__.root")
      )

process.p = cms.Path(process.rechits)
