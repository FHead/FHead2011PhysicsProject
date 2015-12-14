#!/bin/bash


DATA_AREA=/TB2009_data
DQM_DATA_AREA=${HOME}/DQM/dqmdata
WORKING_AREA=${HOME}/CMSSW_2_2_10_TB09/src

source /afs/cern.ch/cms/sw/cmsset_default.sh
cd $WORKING_AREA
eval `scramv1 runtime -sh`

if [  $# -ne 2 ]
then
   echo ""
   echo "--------------------------------------------------------------"
   echo "   Usage: ./runDQMJob.sh runnumber events"
   echo "   where 'runnumber' is a 6 digit number in HTB_runnumber.root"
   echo "   and 'events' is the number of events you want to process"
   echo "   ('-1' will process all events in a given run)"
   echo "--------------------------------------------------------------"
   echo ""
   exit 
fi

echo ""
echo " ----------------------------------------------------------------------"
echo "    Starting DQM job..." 
echo " ----------------------------------------------------------------------" 
echo ""

RUNNUMBER=$1
EVENTS=$2
  
# create the cfg file
# CFGFILE=${WORKING_AREA}/DQMJob_${USER}.py
CFGFILE=DQMJob_${USER}.py

cat > ${CFGFILE}<<EOF
import FWCore.ParameterSet.Config as cms
from DQM.HcalMonitorModule.HcalMonitorModule_cfi import *
from DQM.HcalMonitorClient.HcalMonitorClient_cfi import *

process = cms.Process("HCALDQM")
#----------------------------
# Event Source
#-----------------------------

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(${EVENTS})
    )

process.source = cms.Source("HcalTBSource",
    fileNames = cms.untracked.vstring(
        'file:${DATA_AREA}/HTB_${RUNNUMBER}.root'
    ),
    streams   = cms.untracked.vstring('HCAL_Trigger','HCAL_SlowData','HCAL_QADCTDC','HCAL_DCC021')
)
#----------------------------
# DQM Environment
#-----------------------------
process.load("DQMServices.Core.DQM_cfg")
process.load("DQMServices.Components.DQMEnvironment_cfi")
#process.DQMStore.referenceFileName = '/home/dqmdevlocal/reference/hcal_reference.root'

#----------------------------
# DQM Playback Environment
#-----------------------------
process.load("DQM.Integration.test.environment_playback_cfi")
process.dqmEnv.subSystemFolder    = "Hcal"

process.DQM.collectorHost='localhost'
process.DQM.collectorPort=9190
process.dqmSaver.dirName = '${DQM_DATA_AREA}' # specify output directory
process.dqmSaver.producer = 'DQM'
process.dqmSaver.saveByRun = 2
 

#-----------------------------
# Hcal Conditions:
#-----------------------------
process.hcal_db_producer = cms.ESProducer("HcalDbProducer",
   dump = cms.untracked.vstring(''),
   file = cms.untracked.string('')
)

process.es_hardcode = cms.ESSource("HcalHardcodeCalibrations",
    toGet = cms.untracked.vstring('GainWidths','PedestalWidths','QIEData','ChannelQuality','ZSThresholds','RespCorrs')
)

process.es_ascii = cms.ESSource("HcalTextCalibrations",
    input = cms.VPSet(
        cms.PSet(
            object = cms.string('ElectronicsMap'),
            file = cms.FileInPath('emap_TB2009_A.txt')
        ),
        cms.PSet(
            object = cms.string('Pedestals'),
            file = cms.FileInPath('pedestals_TB2009.txt')
        ),
        cms.PSet(
            object = cms.string('Gains'),
            file = cms.FileInPath('gains_TB2009.txt')
        )
    )
)
  
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


#-----------------------------
# Hcal DQM Source, including SimpleReconstrctor
#-----------------------------
process.tbUnpacker = cms.EDFilter("HcalTBObjectUnpacker",
   IncludeUnmatchedHits = cms.untracked.bool(False),
   HcalTDCFED = cms.untracked.int32(8),
   HcalQADCFED = cms.untracked.int32(8),
   HcalSlowDataFED = cms.untracked.int32(3),
   HcalTriggerFED = cms.untracked.int32(1),
   ConfigurationFile = cms.untracked.string('configQADCTDC_TB2009.txt')
)
process.hcalDigis = cms.EDFilter("HcalRawToDigi",
    # Flag to enable unpacking of ZDC channels (default = false)
    UnpackZDC = cms.untracked.bool(True),
    # Optional filter to remove any digi with "data valid" off, "error" on, 
    # or capids not rotating
    FilterDataQuality = cms.bool(True),
    # Do not complain about missing FEDs
    ExceptionEmptyData = cms.untracked.bool(True),
    InputLabel = cms.InputTag("source"),
    # Use the defaults for FED numbers
    # Do not complain about missing FEDs
    ComplainEmptyData = cms.untracked.bool(False),
    # Flag to enable unpacking of calibration channels (default = false)
    UnpackCalib = cms.untracked.bool(False),
    # At most ten samples can be put into a digi, if there are more
    # than ten, firstSample and lastSample select which samples
    # will be copied to the digi
    firstSample = cms.int32(0),
    lastSample = cms.int32(9),
    FEDs = cms.untracked.vint32(21),
    HcalFirstFED = cms.untracked.int32(21)
)
process.load("RecoLocalCalo.HcalRecProducers.HcalSimpleReconstructor_hbhe_cfi")
process.load("RecoLocalCalo.HcalRecProducers.HcalSimpleReconstructor_ho_cfi")
process.load("RecoLocalCalo.HcalRecProducers.HcalSimpleReconstructor_hf_cfi")
process.hbhereco.firstSample = 5
process.hbhereco.samplesToAdd = 4
process.horeco.firstSample = 6
process.horeco.samplesToAdd = 4
process.hfreco.firstSample = 6
process.hfreco.samplesToAdd = 1

process.load("DQM.HcalMonitorModule.HcalMonitorModule_cfi")
# hcalMonitor configurable values -----------------------
process.hcalMonitor.debug = 0
#process.hcalMonitor.DigiOccThresh = -999999999 ##Temporary measure while DigiOcc is reworked.
process.hcalMonitor.pedestalsInFC = True
process.hcalMonitor.showTiming = False
process.hcalMonitor.checkNevents=1000
process.hcalMonitor.dump2database = False
process.hcalMonitor.AnalyzeOrbitGap = False
process.hcalMonitor.checkHF = False
process.hcalMonitor.checkHE = False
process.hcalMonitor.checkHB = False
process.hcalMonitor.checkHO = False
process.hcalMonitor.checkZDC= False

# Turn on/off individual hcalMonitor modules ------------
process.hcalMonitor.DataFormatMonitor   = False
process.hcalMonitor.DataIntegrityTask   = False
process.hcalMonitor.DigiMonitor         = False
process.hcalMonitor.RecHitMonitor       = False
process.hcalMonitor.TrigPrimMonitor     = False
process.hcalMonitor.DeadCellMonitor     = False
process.hcalMonitor.HotCellMonitor      = False
process.hcalMonitor.BeamMonitor         = False
process.hcalMonitor.PedestalMonitor     = False
process.hcalMonitor.ZDCMonitor          = False
process.hcalMonitor.LEDMonitor          = False
process.hcalMonitor.CaloTowerMonitor    = False
process.hcalMonitor.MTCCMonitor         = False
process.hcalMonitor.HcalAnalysis        = False
# Testbeam related
process.hcalMonitor.H2BeamLineMonitor   = True
process.hcalMonitor.H2PedestalMonitor   = True
process.hcalMonitor.outputPedestalFile  = ''     # Must end with '.txt'. Set to '' to prevent output
process.hcalMonitor.H2RecHitMonitor     = True
process.hcalMonitor.H2TriggerMonitor    = True


# This takes the default cfg values from the hcalMonitor base class and applies them to the subtasks.
setHcalTaskValues(process.hcalMonitor)

# Set individual Task values here (otherwise they will remain set to the values specified for the hcalMonitor.)

process.hcalMonitor.HotCellMonitor_makeDiagnosticPlots  = False
process.hcalMonitor.HotCellMonitor_test_neighbor        = False


#-----------------------------
# Scheduling
#-----------------------------
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound', 
        'TooManyProducts', 
        'TooFewProducts')
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('output.root')
)

process.p = cms.Path(process.tbUnpacker
                     *process.hcalDigis
                     *process.hbhereco*process.horeco*process.hfreco
                     *process.hcalMonitor
                     *process.dqmEnv*process.dqmSaver
#                      *process.output
                     )


#-----------------------------
# Quality Tester 
# will add switch to select histograms to be saved soon
#-----------------------------
process.qTester = cms.EDFilter("QualityTester",
    prescaleFactor = cms.untracked.int32(1),
    qtList = cms.untracked.FileInPath('DQM/HcalMonitorClient/data/hcal_qualitytest_config.xml'),
    getQualityTestsFromFile = cms.untracked.bool(True)
)

EOF


# run cmsRun
# cmsRun ${CFGFILE}

# ${HOME}/DQM/registerDQMFiles.sh

echo ""
echo " ----------------------------------------------------------------------"
echo "    DQM job completed!" 
echo "    Check the DQM output at http://`hostname -f`:8888/dqm/testbeam/"
echo " ----------------------------------------------------------------------" 
echo ""
