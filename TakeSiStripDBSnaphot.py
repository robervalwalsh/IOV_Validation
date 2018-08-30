import ConfigParser
import glob
import os
import numpy
import re
import ROOT
import string
import subprocess
import sys
import optparse
import time
import json
import datetime
from datetime import datetime
import CondCore.Utilities.conddblib as conddb

##############################################
def run_checked(cmd, suppress_stderr = False):
##############################################
    """Run `cmd` and exit in case of failures.
    Arguments:
    - `cmd`: list containing the strings of the command
    - `suppress_stderr`: suppress output from stderr
    """

    try:
        with open(os.devnull, "w") as devnull:
            if suppress_stderr:
                subprocess.check_call(cmd, stdout = devnull, stderr = devnull)
            else:
                subprocess.check_call(cmd, stdout = devnull)
    except subprocess.CalledProcessError as e:
        print("Problem in running the following command:")
        print(" ".join(e.cmd))
    sys.exit(1)

##############################################
def getCommandOutput(command):
##############################################
    """This function executes `command` and returns it output.
    Arguments:
    - `command`: Shell command to be invoked by this function.
    """
    child = os.popen(command)
    data = child.read()
    err = child.close()
    if err:
        print '%s failed w/ exit code %d' % (command, err)
    return data

##############################################
def getFSCR():
##############################################
    out = subprocess.check_output(["curl", "-k", "-s", "https://cmsweb.cern.ch/t0wmadatasvc/prod/firstconditionsaferun"])
    response = json.loads(out)["result"][0]
    return int(response)

##############################################
def getPromptGT():
##############################################
    out = subprocess.check_output(["curl", "-k", "-s", "https://cmsweb.cern.ch/t0wmadatasvc/prod/reco_config"])
    response = json.loads(out)["result"][0]['global_tag']
    return response

##############################################
def getExpressGT():
##############################################
    out = subprocess.check_output(["curl", "-k", "-s", "https://cmsweb.cern.ch/t0wmadatasvc/prod/express_config"])
    response = json.loads(out)["result"][0]['global_tag']
    return response

##############################################
if __name__ == "__main__":
##############################################

    parser = optparse.OptionParser(usage = 'Usage: %prog [options] <file> [<file> ...]\n')
          
    parser.add_option('-s', '--since',
                      dest = 'since',
                      default = -1,
                      help = 'sinces to copy from validation tag',
                      )
     
    (options, arguments) = parser.parse_args()


    FSCR = getFSCR()
    promptGT  = getPromptGT()
    expressGT = getExpressGT() 
    print "Current FSCR:",FSCR,"| Express Global Tag",expressGT,"| Prompt Global Tag",promptGT

    con = conddb.connect(url = conddb.make_url("pro"))
    session = con.session()
    IOV     = session.get_dbtype(conddb.IOV)
    TAG     = session.get_dbtype(conddb.Tag)
    GT      = session.get_dbtype(conddb.GlobalTag)
    GTMAP   = session.get_dbtype(conddb.GlobalTagMap)
    RUNINFO = session.get_dbtype(conddb.RunInfo)

    myGTMap = session.query(GTMAP.record, GTMAP.label, GTMAP.tag_name).\
        filter(GTMAP.global_tag_name == str(expressGT)).\
        order_by(GTMAP.record, GTMAP.label).\
        all()

    SiStripRecords = ["SiStripApvGain2Rcd", "SiStripApvGainRcd", "SiStripBadChannelRcd", "SiStripFedCablingRcd", "SiStripLatencyRcd", "SiStripNoisesRcd", "SiStripPedestalsRcd","SiStripThresholdRcd"]

    for element in myGTMap:
        Record = element[0]
        Label  = element[1]
        Tag = element[2]
        if Record in SiStripRecords:
            TagIOVs = session.query(IOV.since,IOV.payload_hash,IOV.insertion_time).filter(IOV.tag_name == Tag).all()
            found=False
            for count,info in enumerate(TagIOVs):
                if(int(info[0])>int(options.since)):
                    #print Record,Tag
                    #print "IOV since:",TagIOVs[count-1][0],"payload hash:",TagIOVs[count-1][1],"insertion time:",TagIOVs[count-1][2] 
                    command = 'conddb_import -c sqlite_file:DBSnapshot.db -f frontier://FrontierProd/CMS_CONDITIONS -i '+str(Tag) +' -t '+Record.replace("Rcd","")+' -b '+str(TagIOVs[count-1][0])+' -e '+str(TagIOVs[count-1][0])
                    print command
                    getCommandOutput(command)
                    found=True
                    break
            if(not found):
                command = 'conddb_import -c sqlite_file:DBSnapshot.db -f frontier://FrontierProd/CMS_CONDITIONS -i '+str(Tag) +' -t '+Record.replace("Rcd","")+' -b '+str(options.since)+' -e '+str(options.since)
                print command
                getCommandOutput(command)

    run_checked(["sqlite3","DBSnapshot.db", "update iov set since=1"])




         
