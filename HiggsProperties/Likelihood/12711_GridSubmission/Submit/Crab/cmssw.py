import FWCore.ParameterSet.Config as cms

process = cms.Process('Hack')

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.source = cms.Source("EmptySource")

process.program = cms.EDAnalyzer('RecoAnalyzer',
   Data = cms.untracked.string('http://cmsdoc.cern.ch/~chenyi/12677_SignalSplineProjectionUltimateSampling.tar.gz')
)

# process.output = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string("DummyFile.root")
# )

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
   program = cms.PSet(
      initialSeed = cms.untracked.uint32(31426),
      engineName = cms.untracked.string('HepJamesRandom')
   )
)

process.path = cms.Path(process.program)

# process.endpath = cms.EndPath(process.output)




