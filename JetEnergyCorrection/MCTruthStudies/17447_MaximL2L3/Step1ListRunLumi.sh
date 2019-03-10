#!/bin/sh --login

#BSUB -q 1nh

WorkDir=__WORKDIR__

source $WorkDir/Setup_CMSSW.sh

echo "$WorkDir/a.out __FILE__ > __OUTPUT__"
$WorkDir/RunListRunLumi __FILE__ > Result.txt
mv Result.txt __OUTPUT__

