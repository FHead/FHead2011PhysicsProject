
WorkspaceBase=~/work/PhysicsWorkspace/HIJetMass/
InputFolder=$1
IntermediateFolder=$TMPDIR/TempResult
OutputFolder=$2
CrossSectionFile=$3
CombinationFile=$4

if [ -z $1 ]
then
   echo "[Notice] Using default combined folder name: CombinedResult"
   InputFolder=CombinedResult
fi

if [ -z $2 ]
then
   echo "[Notice] Using default scaled folder name: ScaledResult"
   OutputFolder=ScaledResult
fi

if [ -z $3 ]
then
   echo "[Notice] Using default cross section"
   CrossSectionFile=$WorkspaceBase/CommonCode/input/SampleCrossSection.input
fi

if [ -z $4 ]
then
   echo "[Notice] Using default sample combination scheme"
   CombinationFile=$WorkspaceBase/CommonCode/input/SampleCombination.input
fi

mkdir -p $IntermediateFolder
mkdir -p $OutputFolder

rm -f $IntermediateFolder/*
rm -f $OutputFolder/*

for i in `ls $InputFolder`
do
   Tag=${i/.root}
   InputFile=$InputFolder/$i
   OutputFile=$IntermediateFolder/$i

   if grep -q "^$Tag " $CrossSectionFile
   then
      CrossSection=`grep "^$Tag " $CrossSectionFile | awk '{print $2}'`
      if [ "$CrossSection" != "-1" ]
      then
         $WorkspaceBase/CommonCode/bin/ScaleHistograms $InputFile $OutputFile $CrossSection
      else
         cp $InputFile ${OutputFile/.root/_NoCrossSection.root}
      fi
   else
      cp $InputFile ${OutputFile/.root/_NoSuchSample.root}
   fi
done

while read i
do
   i=`echo "$i " | sed "s/[ ]* / /g" | sed "s/^[ ]* //g"`
   Tag=`echo $i | cut --delim=' ' --field=1-1`
   Others=`echo $i | cut --delim=' ' --field=2-`
   HAddString=$OutputFolder/${Tag}.root
   for j in `echo $Others`
   do
      HAddString="$HAddString $IntermediateFolder/${j}.root"
   done
   hadd -k -f $HAddString
   for j in `echo $Others`
   do
      rm -f $IntermediateFolder/${j}.root
   done
done < $CombinationFile

mv $IntermediateFolder/*root $OutputFolder
rmdir $IntermediateFolder


