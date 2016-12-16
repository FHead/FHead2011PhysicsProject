rm -f Header
mkdir -p Cleaned

for i in RR
do
   for j in $i/*
   do
      echo $j

      Component1=`echo $j | cut -d '_' -f 2`
      Component2=`echo $j | cut -d '_' -f 3`

      Source=Cleaned/Function_${Component1}_${Component2}

      FunctionName=GetFullWithZPrime_${Component1}_${Component2}_15672
      
      echo "void $FunctionName(LeptonVectors &leptons, ZPrimeParameters &P);" >> Header
      
      rm -f $Source
      touch $Source

      if [ "`cat $j | wc -c`" -gt 2 ]; then
         rm Temp
         touch Temp
         while [ ! -s Temp ]
         do
            echo Rerun!
            sh AlternativePowKiller.sh < $j > Temp
         done
      
         echo "void $FunctionName(LeptonVectors &leptons, ZPrimeParameters &P)" >> $Source
         echo "{" >> $Source
         echo "   const double Pi = CONST_PI;" >> $Source
         echo >> $Source
         echo "   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();" >> $Source
         echo "   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();" >> $Source
         echo >> $Source
         echo "   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();" >> $Source
         echo "   const double MZ = CONST_MZ;" >> $Source
         echo "   const double wZ = CONST_WZ;" >> $Source
         echo >> $Source
         echo "   const double vh = CONST_VH;" >> $Source
         echo "   const double gL = CONST_GL;" >> $Source
         echo "   const double gR = CONST_GR;" >> $Source
         echo "   const double EE = CONST_EE;" >> $Source
         echo "   const double el = -EE;" >> $Source
         echo >> $Source
         echo "   FourVector P3 = leptons.Lepton11;" >> $Source
         echo "   FourVector P4 = leptons.Lepton12;" >> $Source
         echo "   FourVector P5 = leptons.Lepton21;" >> $Source
         echo "   FourVector P6 = leptons.Lepton22;" >> $Source
         echo >> $Source
         echo "   double C34 = P3 * P4;" >> $Source
         echo "   double C35 = P3 * P5;" >> $Source
         echo "   double C36 = P3 * P6;" >> $Source
         echo "   double C45 = P4 * P5;" >> $Source
         echo "   double C46 = P4 * P6;" >> $Source
         echo "   double C56 = P5 * P6;" >> $Source
         echo "   double E3456 = EPS(P3, P4, P5, P6);" >> $Source
         echo >> $Source
         echo "   double Sqrt2 = sqrt(2);" >> $Source
         echo "   double SqrtC45 = sqrt(C45);" >> $Source
         echo "   double SqrtC56 = sqrt(C56);" >> $Source
         echo "   double SqrtC36 = sqrt(C36);" >> $Source
         echo "   double SqrtC34 = sqrt(C34);" >> $Source
         echo >> $Source
         echo "   double Mv = P.VMass;" >> $Source
         echo "   double wV = P.VWidth;" >> $Source
         echo "   double g1VL = P.G1VL;" >> $Source
         echo "   double g1VR = P.G1VR;" >> $Source
         echo "   double g2VL = P.G2VL;" >> $Source
         echo "   double g2VR = P.G2VR;" >> $Source
         echo >> $Source
         echo "   return" >> $Source
         cat Temp >> $Source
         echo "   ;" >> $Source
         echo "}" >> $Source
      else
         echo "void $FunctionName(LeptonVectors &leptons, ZPrimeParameters &P)" >> $Source
         echo "{" >> $Source
         echo "   return 0;" >> $Source
         echo "}" >> $Source
      fi
   done
done
