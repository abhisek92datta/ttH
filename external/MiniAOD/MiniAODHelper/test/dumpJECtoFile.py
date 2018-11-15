import FWCore.ParameterSet.Config as cms

process = cms.Process("jectxt")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# define your favorite global tag
process.GlobalTag.globaltag = 'PLS170_V7AN1::All'
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))
process.source = cms.Source("EmptySource")

process.readAK4PF    = cms.EDAnalyzer('JetCorrectorDBReader',  
        # below is the communication to the database 
        payloadName    = cms.untracked.string('AK4PF'),
        # this is used ONLY for the name of the printed txt files. You can use any name that you like, 
        # but it is recommended to use the GT name that you retrieved the files from.
        globalTag      = cms.untracked.string('PLS170_V7AN1'),  
        printScreen    = cms.untracked.bool(False),
        createTextFile = cms.untracked.bool(True)
)

#process.readAK5Calo = process.readAK5PF.clone(payloadName = 'AK5Calo')
#process.readAK5JPT = process.readAK5PF.clone(payloadName = 'AK5JPT')
process.p = cms.Path( process.readAK4PF )
#process.p = cms.Path(process.readAK5PF * process.readAK5Calo * process.readAK5JPT)
