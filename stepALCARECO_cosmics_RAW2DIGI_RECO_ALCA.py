# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: stepALCARECO_cosmics --conditions 113X_dataRun3_Prompt_v3 -s RAW2DIGI,RECO,ALCA:SiStripCalCosmics --datatier ALCARECO -n 100 --scenario cosmics --eventcontent ALCARECO --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')

options.register('conditionGT',
                 "113X_dataRun3_Prompt_v3",
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
		 "condition global tag for the job (\"auto:run3_data\" is default)")

options.register ('newNoise',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.bool,
		  "Run with new noise IOV")

options.register ('newG1',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.bool,
		  "Run with new G1 IOV")

options.register ('newG2',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.bool,
		  "Run with new G2 IOV")

options.register ('newBC',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.bool,
		  "Run with new BadComponent IOV")

options.register ('newPedestals',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.bool,
		  "Run with new Pedestals IOV")

options.register ('takeAll',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.bool,
		  "Run with full DB snapshot")
				  
options.register ('nevents',
		  0,
		  VarParsing.multiplicity.singleton,
		  VarParsing.varType.int,
		  "number of events")

# options.register('outputFile',
#                  "output.root",
#                  VarParsing.multiplicity.singleton,
#                  VarParsing.varType.string,
#                  "name for the output file")

# options.register('inputFiles',
# 		 "root://cms-xrd-global.cern.ch//store/data/Run2018D/ZeroBias/RAW/v1/000/321/475/00000/FC884CAC-2AA4-E811-9216-FA163EBF0D83.root",
#                  VarParsing.multiplicity.list,
#                  VarParsing.varType.string,
# 		 "file to process")		
		  				  
options.parseArguments()


process = cms.Process('RERECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')

process.load('Configuration.EventContent.EventContentCosmics_cff')
process.load('SimGeneral.MixingModule.mixCosmics_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.ReconstructionCosmics_cff')
process.load('Configuration.StandardSequences.AlCaRecoStreams_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load("RecoTracker.TrackProducer.TrackRefitter_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("RecoTracker.MeasurementDet.MeasurementTrackerEventProducer_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.nevents),
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet()

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('stepALCARECO_cosmics nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

# # Additional output definition
# process.ALCARECOStreamSiStripCalCosmics = cms.OutputModule("PoolOutputModule",
#     SelectEvents = cms.untracked.PSet(
#         SelectEvents = cms.vstring('pathALCARECOSiStripCalCosmics')
#     ),
#     dataset = cms.untracked.PSet(
#         dataTier = cms.untracked.string('ALCARECO'),
#         filterName = cms.untracked.string('SiStripCalCosmics')
#     ),
#     eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
#     fileName = cms.untracked.string('SiStripCalCosmics.root'),
#     outputCommands = cms.untracked.vstring(
#         'drop *', 
#         'keep *_ALCARECOSiStripCalCosmics_*_*', 
#         'keep *_siStripClusters_*_*', 
#         'keep *_siPixelClusters_*_*', 
#         'keep DetIdedmEDCollection_siStripDigis_*_*', 
#         'keep L1AcceptBunchCrossings_*_*_*', 
#         'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*', 
#         'keep LumiScalerss_scalersRawToDigi_*_*', 
#         'keep DcsStatuss_scalersRawToDigi_*_*', 
#         'keep *_TriggerResults_*_*'
#     )
# )

'''
process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('step1_RAW2DIGI_L1Reco_RECO.root'),
    outputCommands = process.RECOEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)
'''

# Additional output definition
process.analysis = cms.EDAnalyzer('TrackerCluster',
				  trackLabel         = cms.InputTag("generalTracks"),
				  tkTraj             = cms.InputTag('TrackRefitter'),
				  labelTrajToTrack   = cms.InputTag('TrackRefitter'),
				  siStripClusters    = cms.InputTag('TrackRefitter'),
				  TTRHBuilder        = cms.string('WithAngleAndTemplate') # was WithTrackAngle (why use Generic CPE?)
				  )

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, options.conditionGT, '')

SiStripRecords = {"SiStripApvGain2Rcd"   : False, 
		  "SiStripApvGainRcd"    : False, 
		  "SiStripBadChannelRcd" : False, 
		  "SiStripFedCablingRcd" : False, 
		  "SiStripLatencyRcd"    : False, 
		  "SiStripNoisesRcd"     : False, 
		  "SiStripPedestalsRcd"  : False,
		  "SiStripThresholdRcd"  : False}

if(options.newNoise):
	SiStripRecords.update({"SiStripNoisesRcd" : True})
if(options.newG1):
	SiStripRecords.update({"SiStripApvGainRcd" : True})
if(options.newG2):
	SiStripRecords.update({"SiStripApvGain2Rcd" : True})
if(options.newBC):
	SiStripRecords.update({"SiStripBadChannelRcd" : True})
if(options.newPedestals):
	SiStripRecords.update({"SiStripPedestalsRcd" : True})

if(options.takeAll):
	for entry,item in SiStripRecords.iteritems():
		SiStripRecords.update({entry : True})
	

AcceptedRecords=[]
for entry,item in SiStripRecords.iteritems():
	if item:
		AcceptedRecords.append(entry)

print AcceptedRecords

records = []
for rcd in AcceptedRecords:
	records.append(
		cms.PSet(
			record = cms.string(rcd),
			tag    = cms.string(rcd.replace("Rcd","")),
			connect = cms.string("sqlite_file:DBSnapshot.db")
			)
		)

process.GlobalTag.toGet = cms.VPSet(*records)
process.GlobalTag.dumpStat = cms.untracked.bool(True)

process.TFileService = cms.Service("TFileService", 
				   fileName =  cms.string (options.outputFile) 
				   )

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstructionCosmics)
process.analysis_step = cms.Path(process.MeasurementTrackerEvent*process.TrackRefitter*process.analysis)


# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.analysis_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion


process.GlobalTag.DumpStat = cms.untracked.bool(True)

