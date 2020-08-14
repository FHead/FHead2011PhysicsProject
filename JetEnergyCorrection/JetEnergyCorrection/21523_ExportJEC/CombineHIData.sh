#!/bin/bash

echo "var JECData ="
echo "{"
for Version in `ls Fragments/*HI*` Fragments/Autumn18_V*_MC.txt Fragments/Autumn18_Run*_V8_DATA.txt `ls Fragments/*ppRef*` `ls Fragments/PFCalibration*` Fragments/Fall17*V32* Fragments/Summer18* Fragments/Fall18*
do
   cat ${Version}
done
echo "}"
