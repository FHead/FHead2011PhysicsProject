#!/bin/sh

root -l -b -q "SummarizeScan.C+(\"ScanAlphaL\", \"OutputAlphaL.root\")"
root -l -b -q "SummarizeScan.C+(\"ScanAlphaR\", \"OutputAlphaR.root\")"
root -l -b -q "SummarizeScan.C+(\"ScanSigmaL\", \"OutputSigmaL.root\")"
root -l -b -q "SummarizeScan.C+(\"ScanSigmaR\", \"OutputSigmaR.root\")"


