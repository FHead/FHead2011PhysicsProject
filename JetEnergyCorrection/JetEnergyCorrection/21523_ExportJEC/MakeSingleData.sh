#!/bin/bash

Version=$1

OldEta=false
if [[ $Version == "HLT_2016_BX25_V11_MC" ]]; then
   OldEta=true
fi

AllLevel="L1RC:L1RC L1FastJet:L1FastJet L2Relative:L2Relative L1L2L3:L1FastJet,L2Relative"
if [[ $Version == *"DATA" ]]; then
   AllLevel="L1RC:L1RC L1FastJet:L1FastJet L2Relative:L2Relative L1L2L3:L1FastJet,L2Relative L2Residual:L2Residual L2L3Residual:L2L3Residual L1L2L3L2L3Res:L1FastJet,L2Relative,L2L3Residual"
fi
if [[ $Version == "HLT"* ]]; then
   AllLevel="L1FastJet:L1FastJet L2Relative:L2Relative L1L2L3:L1FastJet,L2Relative"
fi
if [[ $Version == *"Flavor"* ]]; then
   AllLevel="L1FastJet:L1FastJet L2Relative:L2Relative L1L2L3:L1FastJet,L2Relative L5b:b_L5Flavor L5c:c_L5Flavor L5g:g_L5Flavor L5s:s_L5Flavor L5ud:ud_L5Flavor"
fi

AlgorithmList="AK4PF AK4PFchs AK4PFPuppi AK8PF AK8PFchs AK8PFPuppi"
ExtraAlgorithmList=""
if [[ $Version == *"DATA" ]]; then
   AlgorithmList="AK4PFchs AK4PFPuppi"
   ExtraAlgorithmList="AK4PF AK8PF AK8PFchs AK8PFPuppi"
fi
if [[ $Version == "HLT"* ]]; then
   AlgorithmList="AK4PFHLT AK8PFHLT AK4CaloHLT AK8CaloHLT"
fi
if [[ $Version == *"Flavor"* ]]; then
   AlgorithmList="AK4PFchs"
fi
if [[ $Version == *_"HI"_* ]]; then
   AlgorithmList="AK2PF AK3PF AK4PF AK5PF AK6PF AK3Calo AK4Calo"
   ExtraAlgorithmList=""
fi
if [[ $Version == *_"ppRef5TeV"_* ]]; then
   AlgorithmList="AK2PF AK3PF AK4PF AK5PF AK6PF AK3Calo AK4Calo"
   ExtraAlgorithmList=""
fi
if [[ $Version == "Winter14"* ]]; then
   AlgorithmList="AK5PF AK5PFchs AK5Calo AK7PF AK7PFchs AK7calo"
   ExtraAlgorithmList=""
fi
if [[ $Version == "Summer19UL17"* ]]; then
   AlgorithmList="AK4PFchs AK4PFPuppi"
fi

DoHEM=
if [[ $Version == *"HEM"* ]]; then
   DoHEM=1
fi
if [[ $Version == "Autumn18_HI_V"*"_MC" ]]; then
   DoHEM=1
fi

DoUncertainty=Yes
if [[ $Version == "HLT"* ]]; then
   DoUncertainty=No
fi

MaxEta=5.18
ReducedEta=false
if [[ $Version == "HLT"* ]]; then
   MaxEta=4.999
   ReducedEta=true
fi

echo "   $Version:"
echo "   {"
for Algorithm in $AlgorithmList
do
   Area=0.5026544
   if [[ $Algorithm == AK8* ]]; then
      Area=2.0106176
   fi

   echo "      $Algorithm:"
   echo "      {"
   for Level in $AllLevel
   do
      LevelTag=`echo $Level | cut --delim=':' --field=1`
      LevelName=`echo $Level | cut --delim=':' --field=2`
      echo "         $LevelTag:"
      echo "         {"
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]] || [[ $LevelTag == "L1RC" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --FixRho 20 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --FixRho 40 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]] || [[ $LevelTag == "L1RC" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --FixRho 60 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 30 --FixRho 40 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 300 --FixRho 40 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      if [[ $DoHEM == 1 ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --FixRho 40 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 30 --FixRho 40 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 300 --FixRho 40 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      fi
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]] || [[ $LevelTag == "L1RC" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 0.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 1.5 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.3 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.9 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 3.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 4.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         if [[ $DoHEM == 1 ]]; then
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 0.0 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -1.5 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -2.3 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -2.9 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -3.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -4.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -1.5 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -2.3 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -2.9 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -3.0 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
            ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
               --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta -4.0 --FixPhi -1.2 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         fi
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 1.5 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 2.3 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 2.9 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 3.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 4.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      if [[ $DoHEM == 1 ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -1.5 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -2.3 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -2.9 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -3.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -4.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -1.5 --FixPhi -1.2 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -2.3 --FixPhi -1.2 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -2.9 --FixPhi -1.2 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -3.0 --FixPhi -1.2 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta -4.0 --FixPhi -1.2 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta 0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta 1.5 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta 2.3 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta 2.9 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta 3.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta 4.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta -1.5 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta -2.3 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta -2.9 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta -3.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixEta -4.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta 0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta 1.5 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta 2.3 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta 2.9 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta 3.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta 4.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta -1.5 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta -2.3 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta -2.9 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta -3.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Phi --Min -3.14159 --Max 3.14159 --NBin 100 --FixPT 30 --FixEta -4.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      fi
      echo "         },"
   done
   if [[ $DoUncertainty == "Yes" ]]; then
      for Level in Uncertainty
      do
         echo "         $Level:"
         echo "         {"
         ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 300 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
            --Dependent PT --Min 10 --Max 7000 --NBin 100 --FixEta 0.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
            --Dependent PT --Min 10 --Max 7000 --NBin 100 --FixEta 2.9 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
            --Dependent PT --Min 10 --Max 7000 --NBin 100 --FixEta 1.5 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./ExecuteUncertainty --Version $Version --Algorithm $Algorithm --Level $Level \
            --Dependent PT --Min 10 --Max 7000 --NBin 100 --FixEta 4.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         echo "         },"
      done
   fi
   echo "      },"
done
for Algorithm in $ExtraAlgorithmList
do
   echo "      $Algorithm:"
   echo "      {"
   for Level in L1RC:L1RC
   do
      LevelTag=`echo $Level | cut --delim=':' --field=1`
      LevelName=`echo $Level | cut --delim=':' --field=2`
      echo "         $LevelTag:"
      echo "         {"
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]] || [[ $LevelTag == "L1RC" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --FixRho 20 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --FixRho 40 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]] || [[ $LevelTag == "L1RC" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 100 --FixRho 60 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 30 --FixRho 40 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent Eta --Min -$MaxEta --Max $MaxEta --NBin -1 --FixPT 300 --FixRho 40 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      if [[ $LevelTag == "L1FastJet" ]] || [[ $LevelTag == "L1L2L3" ]] || [[ $LevelTag == "L1RC" ]]; then
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 0.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 1.5 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.3 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 2.9 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 3.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
         ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
            --Dependent Rho --Min 0 --Max 70 --NBin 50 --FixPT 100 --FixEta 4.0 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      fi
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 1.5 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 2.3 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 2.9 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 3.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      ./Execute --Version $Version --Algorithm $Algorithm --Level $LevelName \
         --Dependent PT --Min 1 --Max 7000 --NBin 100 --FixEta 4.0 --FixRho 30 --ReducedEta $ReducedEta --DoOldEta $OldEta --FixArea $Area
      echo "         },"
   done
   echo "      },"
done
echo "   },"
