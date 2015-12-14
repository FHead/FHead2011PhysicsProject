#!/bin/sh

root -l -b -q "ConvertToDataset.C+(\"DatasetMuAll.root\", \"DatasetMu.Dataset.root\", 1)"
root -l -b -q "ConvertToDataset.C+(\"DatasetPDMu.root\", \"DatasetPDMu.Dataset.root\", 1)"

