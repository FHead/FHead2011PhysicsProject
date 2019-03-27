# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: Configuration/GenProduction/python/JME-RunIIFall18GS-00015-fragment.py --fileout file:JME-RunIIFall18GS-00015.root --mc --eventcontent RAWSIM --datatier GEN-SIM --conditions 102X_upgrade2018_realistic_v11 --beamspot Realistic25ns13TeVEarly2018Collision --step GEN --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename RunHerwig.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring -n 1000 --no_output
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('GEN',eras.Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic25ns13TeVEarly2018Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(20000)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('Configuration/GenProduction/python/JME-RunIIFall18GS-00015-fragment.py nevts:1000'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
      generator = cms.PSet(
         initialSeed = cms.untracked.uint32(82),
         engineName = cms.untracked.string('TRandom3'),
         ),
      VtxSmeared = cms.PSet(
         initialSeed = cms.untracked.uint32(15),
         engineName = cms.untracked.string('TRandom3')
         ),
      )


# Output definition

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v11', '')

process.generator = cms.EDFilter("Herwig7GeneratorFilter",
    configFiles = cms.vstring(),
    crossSection = cms.untracked.double(1363000000),
    dataLocation = cms.string('${HERWIGPATH:-6}'),
    eventHandlers = cms.string('/Herwig/EventHandlers'),
    filterEfficiency = cms.untracked.double(1.0),
    generatorModule = cms.string('/Herwig/Generators/EventGenerator'),
    herwig7CH2AlphaS = cms.vstring(
        'cd /Herwig/Shower',
        'set AlphaQCD:AlphaMZ 0.118',
        'cd /'
    ),
    herwig7CH2MPISettings = cms.vstring(
        'read snippets/SoftModel.in',
        'set /Herwig/Hadronization/ColourReconnector:ReconnectionProbability 0.479',
        'set /Herwig/UnderlyingEvent/MPIHandler:pTmin0 3.138',
        'set /Herwig/UnderlyingEvent/MPIHandler:InvRadius 1.174',
        'set /Herwig/UnderlyingEvent/MPIHandler:Power 0.1203',
        'set /Herwig/Partons/RemnantDecayer:ladderPower -0.08',
        'set /Herwig/Partons/RemnantDecayer:ladderNorm 0.95'
    ),
    herwig7CH2PDF = cms.vstring(
        'cd /Herwig/Partons',
        'create ThePEG::LHAPDF PDFSet_nnlo ThePEGLHAPDF.so',
        'set PDFSet_nnlo:PDFName NNPDF31_nnlo_as_0118.LHgrid',
        'set PDFSet_nnlo:RemnantHandler HadronRemnants',
        'set /Herwig/Particles/p+:PDF PDFSet_nnlo',
        'set /Herwig/Particles/pbar-:PDF PDFSet_nnlo',
        'set /Herwig/Partons/PPExtractor:FirstPDF  PDFSet_nnlo',
        'set /Herwig/Partons/PPExtractor:SecondPDF PDFSet_nnlo',
        'set /Herwig/Shower/ShowerHandler:PDFA PDFSet_nnlo',
        'set /Herwig/Shower/ShowerHandler:PDFB PDFSet_nnlo',
        'create ThePEG::LHAPDF PDFSet_lo ThePEGLHAPDF.so',
        'set PDFSet_lo:PDFName NNPDF31_lo_as_0118.LHgrid',
        'set PDFSet_lo:RemnantHandler HadronRemnants',
        'set /Herwig/Shower/ShowerHandler:PDFARemnant PDFSet_lo',
        'set /Herwig/Shower/ShowerHandler:PDFBRemnant PDFSet_lo',
        'set /Herwig/Partons/MPIExtractor:FirstPDF PDFSet_lo',
        'set /Herwig/Partons/MPIExtractor:SecondPDF PDFSet_lo',
        'cd /'
    ),
    parameterSets = cms.vstring(
        'productionParameters',
        'herwig7CH2PDF',
        'herwig7CH2AlphaS',
        'herwig7CH2MPISettings'
    ),
    productionParameters = cms.vstring(
        'read snippets/PPCollider.in',
        'mkdir /Herwig/Weights',
        'cd /Herwig/Weights',
        'create ThePEG::ReweightMinPT reweightMinPT ReweightMinPT.so',
        'cd /Herwig/MatrixElements/',
        'insert SubProcess:MatrixElements[0] MEQCD2to2',
        'insert SubProcess:Preweights[0] /Herwig/Weights/reweightMinPT',
        'cd /',
        'set /Herwig/Cuts/JetKtCut:MinKT 15.*GeV',
        'set /Herwig/Cuts/JetKtCut:MaxKT 250.*GeV',
        'set /Herwig/Cuts/Cuts:MHatMin  0.0*GeV',
        'set /Herwig/Cuts/Cuts:X1Min    1e-07',
        'set /Herwig/Cuts/Cuts:X2Min    1e-07',
        'set /Herwig/Cuts/MassCut:MinM  0.0*GeV',
        'set /Herwig/Weights/reweightMinPT:Power 4.5',
        'set /Herwig/Weights/reweightMinPT:Scale 15*GeV',
        # 'library HwEvtGenInterface.so',
        # 'mkdir /Herwig/Decays',
        # 'create Herwig::EvtGenInterface /Herwig/Decays/EvtGen',
        # 'create Herwig::EvtGenDecayer /Herwig/Decays/EvtGenDecayer',
        # 'set /Herwig/Particles/D0/D0->pi+,K-;:Decayer /Herwig/Decays/EvtGenDecayer'
        'do /Herwig/Particles/D0:SelectDecayModes D0->K-,pi+;',
        'do /Herwig/Particles/Dbar0:SelectDecayModes Dbar0->K+,pi-;',
        # 'do /Herwig/Particles/D0:PrintDecayModes',
        # 'do /Herwig/Particles/Dbar0:PrintDecayModes',
        # 'mkdir /Herwig/Matchers',
        # 'cd /Herwig/Matchers',
        # 'ls',
        # 'create ThePEG::Matcher<Herwig::D0> D0',
        # 'mkdir /Herwig/Cuts',
        # 'cd /Herwig/Cuts',
        # 'create ThePEG::SimpleKTCut D0KtCut SimpleKTCut.so',
        # 'DISABLEREADONLY',
        # 'newdef D0KtCut:Matcher /Herwig/Matchers/D0',
        # 'newdef D0KtCut:MinKT 2.0*GeV',
        # 'newdef D0KtCut:MinEta -3.',
        # 'newdef D0KtCut:MaxEta  3.',
        # 'cd /',
    ),
    repository = cms.string('${HERWIGPATH}/HerwigDefaults.rpo'),
    run = cms.string('InterfaceMatchboxTest'),
    runModeList = cms.untracked.string('read,run'),
    seed = cms.untracked.int32(13579)
)

process.D0Filter = cms.EDFilter("PythiaFilter", ParticleID = cms.untracked.int32(421))

process.D0KinematicsFilter = cms.EDFilter("MCSingleParticleYPt",
      CheckAntiparticle = cms.untracked.bool(True),
      ParticleID = cms.untracked.vint32(421),
      MinPt = cms.untracked.vdouble(2.0),
      MinY = cms.untracked.vdouble(-2.),
      MaxY = cms.untracked.vdouble(2.)
      )

process.ProductionFilterSequence = cms.Sequence(process.generator*process.D0Filter*process.D0KinematicsFilter)

process.HiGenParticleAna = cms.EDAnalyzer(
      'HiGenAnalyzer',
      doVertex = cms.untracked.bool(False),
      etaMax = cms.untracked.double(5.0),
      ptMin = cms.untracked.double(0),
      chargedOnly = cms.untracked.bool(False),
      stableOnly = cms.untracked.bool(False),
      src = cms.untracked.InputTag("generator"),
      genParticleSrc = cms.untracked.InputTag("genParticles"),
      genHIsrc = cms.untracked.InputTag("heavyIon"),
      doParticles = cms.untracked.bool(True),
      doHI = cms.untracked.bool(False)
      )

process.hiEvtAnalyzer = cms.EDAnalyzer('HiEvtAnalyzer',
      CentralitySrc    = cms.InputTag("hiCentrality"),
      CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
      EvtPlane         = cms.InputTag("hiEvtPlane"),
      EvtPlaneFlat     = cms.InputTag("hiEvtPlaneFlat",""),
      HiMC             = cms.InputTag("heavyIon"),
      Vertex           = cms.InputTag("offlinePrimaryVertices"),
      doCentrality     = cms.bool(False),
      doEvtPlane       = cms.bool(False),
      doEvtPlaneFlat   = cms.bool(False),
      doVertex         = cms.bool(False),
      doMC             = cms.bool(True),
      doHiMC           = cms.bool(False),
      useHepMC         = cms.bool(False),
      HepMCSrc         = cms.InputTag("generatorSmeared::GEN"),
      evtPlaneLevel    = cms.int32(0)
      )

process.runAnalyzer = cms.EDAnalyzer('RunAnalyzer')

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest 103X")
import subprocess, os
version = subprocess.check_output(['git', '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
if version == '':
   version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)



process.TFileService = cms.Service("TFileService",
      fileName = cms.string("HiForestGEN.root"))



# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen * process.HiForest * process.runAnalyzer * process.hiEvtAnalyzer * process.HiGenParticleAna)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.endjob_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(8)
process.options.numberOfStreams=cms.untracked.uint32(0)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# End of customisation functions

# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
