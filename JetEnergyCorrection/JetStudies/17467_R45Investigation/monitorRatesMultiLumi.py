#!/bin/env python

# Sam modified version of the script to deal with multiple lumisections
import sys, os
import collections
import datetime
import json

# length of a lumisections, corresponding to 2**18 LHC orbits, or 23.31 seconds
SECS_PER_LUMI = 23.31040958083832;


# Supply this method with a FULL PATH to a .jsndata file to read it and put the HLT or L1 rates inside into the database.
# The jsndata needs the .ini descriptor files to be there or this will fail
#
# For the HLT rates, each lumisection has several path IDs which get their own row for that LS.
# We get these path IDs by looking up the path names provided in the .ini file in a mapping
# from the production database.
# For the L1 rates, we insert a single row per LS.
# However in this row are two Varrays containing 128 and 64 bits respectively, for the trigger rates, accomplishing in
# 1 row what the HLT rates table does with many rows.

def monitorRates(jsndata_files,outputRates):
    # This takes the full path of a .jsndata file as parameter
    # Any other call of this function is inappropriate and will just not work!
    # e.g. jsndata_file='/store/lustre/mergeMiniDAQMacro/run230852/run230852_ls0110_streamHLTRates_mrg-c2f13-37-01.jsndata'
    HLT_rates = collections.OrderedDict()
    nrLumiSecs=0
    for jsndata_file in jsndata_files:
        nrLumiSecs+=1
        json_dir=os.path.dirname(jsndata_file)
        jsndata_filename=os.path.basename(jsndata_file)
        file_raw, file_ext = os.path.splitext(jsndata_filename)
        raw_pieces=file_raw.split( '_' , 3 ) # this is not an emoji!
        run_number=raw_pieces[0][3:] # 123456
        ls=raw_pieces[1] # ls1234
        stream=raw_pieces[2][6:] # HLTRates | L1Rates
        extra=raw_pieces[3]

        if stream != "HLTRates" and stream != "L1Rates":
            print 'Unrecognized rate stream: '+raw_pieces[2]
            return False
    
        # Open the jsndata file
        # If it doesn't exist, this function will crash
    
        try:
            rates_json=open(jsndata_file).read()
        except (OSError, IOError) as e:
            print 'Error finding or opening jsndata file: "'+jsndata_file+'"'
            return False
        rates=json.loads(rates_json)

        # Get the ini in the directory with rates corresponding to specified run number, lumi section, and HLT|L1
        # The correspondence might look like:
        # run230852_ls0110_streamL1Rates_mrg-c2f13-37-01.jsndata =>
        # run230852_ls0000_streamL1Rates_mrg-c2f13-37-01.ini
        # If the INI file is not there, this function will crash

        ini_filename=raw_pieces[0]+'_ls0000_'+raw_pieces[2]+'_'+raw_pieces[3]+'.ini'
        if stream=='HLTRates':
            try:
                HLT_json=open(json_dir+'/'+ini_filename).read()
            except (OSError, IOError) as e:
                print 'Error finding or opening ini file: "'+json_dir+'/'+ini_filename+'"'
            HLT_names = json.loads(HLT_json)
            
                # Get the rates for each trigger path
            for i, pathname in enumerate(HLT_names['Path-Names']):
                if pathname not in HLT_rates:
                    HLT_rates[pathname] = {}
                if 'L1PASS' in HLT_rates[pathname]:
                    #print "adding"
                    HLT_rates[pathname]['L1PASS']   += rates['data'][2][i]
                    HLT_rates[pathname]['PSPASS']   += rates['data'][3][i]
                    HLT_rates[pathname]['PACCEPT']  += rates['data'][4][i]
                    HLT_rates[pathname]['PREJECT']  += rates['data'][5][i]
                    HLT_rates[pathname]['PEXCEPT']  += rates['data'][6][i]
                else:
                 #   print "not adding"
                    HLT_rates[pathname]['L1PASS']   = rates['data'][2][i]
                    HLT_rates[pathname]['PSPASS']   = rates['data'][3][i]
                    HLT_rates[pathname]['PACCEPT']  = rates['data'][4][i]
                    HLT_rates[pathname]['PREJECT']  = rates['data'][5][i]
                    HLT_rates[pathname]['PEXCEPT']  = rates['data'][6][i]


    sys.stdout.write("\x1b[0;0;32m")
    if outputRates==True:  print "%-60s       %12s    %12s    %12s" % ("HLT Path Name", "L1 seed rate", "Prescale rate", "HLT path rate")
    else: print "%-60s       %12s    %12s    %12s" % ("HLT Path Name", "L1 seed counts", "Prescale counts", "HLT path counts")
    sys.stdout.write("\x1b[0;0m")
    for (pathname, rate) in HLT_rates.iteritems():
        if outputRates==True:
            rateConversion=1./SECS_PER_LUMI/nrLumiSecs
            outputStr="%-60s    %10.2f Hz    %10.2f Hz    %10.2f Hz"
        else:
            rateConversion=1.;
            outputStr="%-60s    %10i    %10i     %10i "
        
        print  outputStr % (pathname, rate['L1PASS'] * rateConversion, rate['PSPASS'] * rateConversion, rate['PACCEPT'] * rateConversion)
    print


#for arg in sys.argv[1:]:
  #  sys.stdout.write("\x1b[0;0;31m")
#    print arg
 #   sys.stdout.write("\x1b[0;0m")

import argparse

parser = argparse.ArgumentParser(description='outputs the counts/rates of paths given the input rate files')
parser.add_argument('inputFiles',help='input filelist',nargs="+")
parser.add_argument('--outputRates',help="outputs rates rather than counts",dest='outputRates',action='store_true')
parser.set_defaults(outputRates=False)
args = parser.parse_args()

#print args.inputFiles
monitorRates(args.inputFiles,args.outputRates)
