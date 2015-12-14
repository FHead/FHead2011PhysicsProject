#!/bin/sh


hadd -f QCDAll.root SingleHistograms/QCD*
hadd -f SingleTopSAll.root SingleHistograms/SingleTop_sChannel*
hadd -f SingleTopTAll.root SingleHistograms/SingleTop_tChannel*
hadd -f SingleTopTWAll.root SingleHistograms/SingleTop_tWChannel*
hadd -f TTbarAll.root SingleHistograms/TTbar*
hadd -f WJetsAll.root SingleHistograms/WJets*
hadd -f ZJetsAll.root SingleHistograms/ZJets*
