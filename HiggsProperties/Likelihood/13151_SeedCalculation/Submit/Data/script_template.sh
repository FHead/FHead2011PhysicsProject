#!/bin/sh

Seed=`expr "$1" "-" "1"`

curl http://cmsdoc.cern.ch/~chenyi/13151_SeedTrees/__ROOTFILE__ > __ROOTFILE__
curl http://cmsdoc.cern.ch/~chenyi/13151_SeedCalculation_AdditionalData.tar.gz > Executable.tar.gz
tar zxvf Executable.tar.gz
./Run__TYPE____ENERGY__ __ROOTFILE__ ${Seed} ${Seed} __BRANCH__ __FLAVOR__ > Result.txt







