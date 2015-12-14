#!/bin/sh

root -l -b -q "ConvertToDataset.C+(\"WJetsAll.root\", \"WJetsAll.Dataset.root\", 28000)"
root -l -b -q "ConvertToDataset.C+(\"ZJetsAll.root\", \"ZJetsAll.Dataset.root\", 2800)"
root -l -b -q "ConvertToDataset.C+(\"TTbarAll.root\", \"TTbarAll.Dataset.root\", 165)"
root -l -b -q "ConvertToDataset.C+(\"QCDAll.root\", \"QCDAll.Dataset.root\", 79687)"
root -l -b -q "ConvertToDataset.C+(\"SingleTopSAll.root\", \"SingleTopSAll.Dataset.root\", 4.5)"
root -l -b -q "ConvertToDataset.C+(\"SingleTopTAll.root\", \"SingleTopTAll.Dataset.root\", 63)"
root -l -b -q "ConvertToDataset.C+(\"SingleTopTWAll.root\", \"SingleTopTWAll.Dataset.root\", 10.6)"
root -l -b -q "ConvertToDataset.C+(\"DatasetMuAll.root\", \"DatasetMu.Dataset.root\", 1)"
root -l -b -q "ConvertToDataset.C+(\"DatasetPDMuSmallFile.root\", \"DatasetPDMuSmallFile.Dataset.root\", 1)"
root -l -b -q "ConvertToDataset.C+(\"DatasetPDMuLargeFile.root\", \"DatasetPDMuLargeFile.Dataset.root\", 1)"

