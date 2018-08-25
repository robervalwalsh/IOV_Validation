# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: stepALCARECO --conditions 102X_dataRun2_Prompt_v1 -s RAW2DIGI,RECO:reconstruction_trackingOnly,ALCA:SiStripCalMinBias --datatier ALCARECO -n 100 --scenario pp --era Run2_2018 --eventcontent ALCARECO --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')

options.register ('newIOV',
				  0,
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.bool,
				  "Run with new IOV")
				  
options.register ('nevents',
				  0,
				  VarParsing.multiplicity.singleton,
				  VarParsing.varType.int,
				  "number of events")
				  
				  
options.parseArguments()


process = cms.Process('RECO',eras.Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.AlCaRecoStreams_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load("RecoTracker.TrackProducer.TrackRefitter_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("RecoTracker.MeasurementDet.MeasurementTrackerEventProducer_cfi")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.nevents)
)

# Input source
process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2018D/ZeroBias/RAW/v1/000/321/475/00000/FC884CAC-2AA4-E811-9216-FA163EBF0D83.root'),
    fileNames = cms.untracked.vstring(options.inputFiles),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('stepALCARECO nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

## Additional output definition
#process.ALCARECOStreamSiStripCalMinBias = cms.OutputModule("PoolOutputModule",
#    SelectEvents = cms.untracked.PSet(
#        SelectEvents = cms.vstring('pathALCARECOSiStripCalMinBias')
#    ),
#    dataset = cms.untracked.PSet(
#        dataTier = cms.untracked.string('ALCARECO'),
#        filterName = cms.untracked.string('SiStripCalMinBias')
#    ),
#    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
#    fileName = cms.untracked.string('SiStripCalMinBias.root'),
#    outputCommands = cms.untracked.vstring(
#        'drop *', 
#        'keep *_ALCARECOSiStripCalMinBias_*_*', 
#        'keep *_siStripClusters_*_*', 
#        'keep *_siPixelClusters_*_*', 
#        'keep DetIdedmEDCollection_siStripDigis_*_*', 
#        'keep L1AcceptBunchCrossings_*_*_*', 
#        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*', 
#        'keep LumiScalerss_scalersRawToDigi_*_*', 
#        'keep DcsStatuss_scalersRawToDigi_*_*', 
#        'keep *_TriggerResults_*_*'
#    )
#)

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
    TTRHBuilder        = cms.string('WithTrackAngle')
)

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Express_v1', '')


if options.newIOV == True:
	process.GlobalTag.toGet = cms.VPSet(
      	  cms.PSet(record = cms.string("SiStripNoisesRcd"),
	      		tag = cms.string("myTag"),
	      		connect = cms.string('sqlite_file:myNoise.db')
	     	  )
	)

process.GlobalTag.dumpStat = cms.untracked.bool(True)

#process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )
process.TFileService = cms.Service("TFileService", fileName =  cms.string (options.outputFile) )




# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction_trackingOnly)
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

