#!/bin/sh
#$ -S /bin/sh
#$ -V

cd /home/yichen/PhysicsWorkspace/HiggsProperties/HiggsShape/12523_HiggsShape
g++ PropagateShape.cpp
./a.out | tee log



