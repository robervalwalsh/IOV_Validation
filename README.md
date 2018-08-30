# IOV Validation

This repository is meant for CMS Strip Conditions Validation

## Instructions:

* Setup lxplus area

```
cd /tmp/login/
cmsrel CMSSW_10_2_0
cd CMSSW_10_2_0/src
cmsenv
git clone git@github.com:jandrea/IOV_Validation.git .
scramv1 b -j4
```

* Retrieve SiStrip Offline DB snapshot at a given run-number

```
python TakeSiStripDBSnaphot.py -s 321493
```

* Run the re-reconstruction 

```
grid-proxy-init
 
cmsRun stepALCARECO_RAW2DIGI_RECO_ALCA.py inputFiles=root://cms-xrd-global.cern.ch//store/data/Run2018D/ZeroBias/RAW/v1/000/321/475/00000/FC884CAC-2AA4-E811-9216-FA163EBF0D83.root outputFile=histo_Old.root nevents=10
cmsRun stepALCARECO_RAW2DIGI_RECO_ALCA.py newNoise=True  inputFiles=root://cms-xrd-global.cern.ch//store/data/Run2018D/ZeroBias/RAW/v1/000/321/475/00000/FC884CAC-2AA4-E811-9216-FA163EBF0D83.root outputFile=histo_New.root nevents=10
```

* Run the plot comparison

```
root -l runScript.C+
```