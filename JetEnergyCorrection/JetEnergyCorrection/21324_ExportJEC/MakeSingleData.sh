#!/bin/bash

Version=$1

AllLevel="L1FastJet:L1FastJet L2Relative:L2Relative L1L2L3:L1FastJet,L2Relative"
if [[ $Version == *"DATA" ]]; then
   AllLevel="L1FastJet:L1FastJet L2Relative:L2Relative L1L2L3:L1FastJet,L2Relative L2Residual:L2Residual L2L3Residual:L2L3Residual L1L2L3L2L3Res:L1FastJet,L2Relative,L2L3Residual"
fi

AlgorithmList="AK4PF AK4PFchs AK4PFPuppi AK8PF AK8PFchs AK8PFPuppi"
if [[ $Version == *"DATA" ]]; then
   AlgorithmList="AK4PFchs"
fi

echo "   $Version:"
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
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 20
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 40
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 60
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 30 --FixRho 40
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 300 --FixRho 40
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 0.0
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 1.5
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.3
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.9
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 3.0
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 4.0
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 1000 --NBin 100 --FixEta 0 --FixRho 30
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 1000 --NBin 100 --FixEta 1.5 --FixRho 30
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 1000 --NBin 100 --FixEta 2.3 --FixRho 30
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 1000 --NBin 100 --FixEta 2.9 --FixRho 30
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 1000 --NBin 100 --FixEta 3.0 --FixRho 30
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 5 --Max 1000 --NBin 100 --FixEta 4.0 --FixRho 30
      echo "         },"
   done
   for Level in Uncertainty
   do
      echo "         $Level:"
      echo "         {"
      ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 30
      ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100
      ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
         --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 300
      ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
         --Dependent PT --Min 10 --Max 1000 --NBin 100 --FixEta 0.0
      ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
         --Dependent PT --Min 10 --Max 1000 --NBin 100 --FixEta 2.9
      ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
         --Dependent PT --Min 10 --Max 1000 --NBin 100 --FixEta 1.5
      ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
         --Dependent PT --Min 10 --Max 1000 --NBin 100 --FixEta 4.0
      echo "         },"
   done
   echo "      },"
done
echo "   },"
