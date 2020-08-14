#!/bin/bash

Version=$1

AllLevel="EtaResolution:EtaResolution PtResolution:PtResolution PhiResolution:PhiResolution"
AlgorithmList="AK4PF AK4PFchs AK4PFPuppi AK8PF AK8PFchs AK8PFPuppi"

echo "   JER_$Version:"
echo "   {"
for Algorithm in $AlgorithmList
do
   echo "      $Algorithm:"
   echo "      {"
   for Level in $AllLevel
   do
      LevelTag=`echo $Level | cut --delim=':' --field=1`
      LevelName=`echo $Level | cut --delim=':' --field=2`
      echo "         $LevelTag:"
      echo "         {"
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 15 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 20 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 40 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 60 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 30 --FixRho 40 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 300 --FixRho 40 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 0.0 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 1.5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.3 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.9 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 3.0 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 4.0 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 0 --FixRho 30 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 1.5 --FixRho 30 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 2.3 --FixRho 30 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 2.9 --FixRho 30 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 3.0 --FixRho 30 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 4.0 --FixRho 30 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 0.0 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 1.5 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 1.5 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 2.3 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 2.9 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 3.0 --FixRho 5 --JER true
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 7000 --NBin 100 --FixEta 4.0 --FixRho 5 --JER true
      echo "         },"
   done
      echo "         JERSF:"
      echo "         {"
      ./ExecuteJERSF --Version $Version --Algorithm $Algorithm --Dependent Eta --Min -5.2 --Max 5.2 --NBin -1 \
         --FixPT 30 --FixRho 20
      ./ExecuteJERSF --Version $Version --Algorithm $Algorithm --Dependent Eta --Min -5.2 --Max 5.2 --NBin -1 \
         --FixPT 100 --FixRho 20
      ./ExecuteJERSF --Version $Version --Algorithm $Algorithm --Dependent Eta --Min -5.2 --Max 5.2 --NBin -1 \
         --FixPT 300 --FixRho 20
      ./ExecuteJERSF --Version $Version --Algorithm $Algorithm --Dependent PT --Min 10 --Max 1000 --NBin 50 \
         --FixEta 2.900 --FixRho 20
      ./ExecuteJERSF --Version $Version --Algorithm $Algorithm --Dependent PT --Min 10 --Max 1000 --NBin 50 \
         --FixEta 2.750 --FixRho 20
      ./ExecuteJERSF --Version $Version --Algorithm $Algorithm --Dependent PT --Min 10 --Max 1000 --NBin 50 \
         --FixEta 2.550 --FixRho 20
      ./ExecuteJERSF --Version $Version --Algorithm $Algorithm --Dependent PT --Min 10 --Max 1000 --NBin 50 \
         --FixEta 2.400 --FixRho 20
      echo "         },"
   echo "      },"
done
echo "   },"
