#!/bin/sh

Seed=$1

curl http://cmsdoc.cern.ch/~chenyi/HZZFullSimTrees/__ROOTFILE__ > __ROOTFILE__
curl http://cmsdoc.cern.ch/~chenyi/12711_GridSubmission___TYPE__AdditionalData.tar.gz > Executable.tar.gz
tar zxvf Executable.tar.gz
./Run__TYPE__ __ROOTFILE__ ${Seed}00 ${Seed}99 __BRANCH__ > Result.txt







