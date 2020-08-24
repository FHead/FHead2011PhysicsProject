#!/bin/bash

echo "var JECData ="
echo "{"
for Version in Fall17_17Nov2017_V32_MC Autumn18_V8_MC Summer16_07Aug2017_V11_MC Summer16_07Aug2017_V15_MC Summer16_07Aug2017_V20_MC
do
   echo "   $Version:"
   echo "   {"
   for Algorithm in AK4PFchs
   do
      echo "      $Algorithm:"
      echo "      {"
      for Level in L1FastJet:L1FastJet L2Relative:L2Relative L1L2L3:L1FastJet,L2Relative
      do
         LevelTag=`echo $Level | cut --delim=':' --field=1`
         LevelName=`echo $Level | cut --delim=':' --field=2`
         echo "         $LevelTag:"
         echo "         {"
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 20
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 40
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 100 --FixRho 60
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 30 --FixRho 40
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -5.18 --Max 5.18 --NBin -1 --FixPT 300 --FixRho 40
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 100 --FixPT 100 --FixEta 0.0
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 100 --FixPT 100 --FixEta 1.5
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 100 --FixPT 100 --FixEta 2.3
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 100 --FixPT 100 --FixEta 2.9
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 100 --FixPT 100 --FixEta 3.0
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 100 --FixPT 100 --FixEta 4.0
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 5 --Max 1000 --NBin 200 --FixEta 0 --FixRho 30
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 5 --Max 1000 --NBin 200 --FixEta 1.5 --FixRho 30
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 5 --Max 1000 --NBin 200 --FixEta 2.3 --FixRho 30
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 5 --Max 1000 --NBin 200 --FixEta 2.9 --FixRho 30
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 5 --Max 1000 --NBin 200 --FixEta 3.0 --FixRho 30
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 5 --Max 1000 --NBin 200 --FixEta 4.0 --FixRho 30
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
done
echo "}"
