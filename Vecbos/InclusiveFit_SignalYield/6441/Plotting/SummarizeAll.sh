#!/bin/sh

root -l -b -q "PFThresholdScan.C+(\"PF\", \"\")"
root -l -b -q "PFThresholdScan.C+(\"PF\", \"_Eta10\")"
root -l -b -q "PFThresholdScan.C+(\"PF\", \"_Eta24\")"
root -l -b -q "PFThresholdScan.C+(\"Calo\", \"\")"
root -l -b -q "PFThresholdScan.C+(\"Calo\", \"_Eta10\")"
root -l -b -q "PFThresholdScan.C+(\"Calo\", \"_Eta24\")"



