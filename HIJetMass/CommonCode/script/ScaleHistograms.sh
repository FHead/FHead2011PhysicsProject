
WorkspaceBase=~/work/PhysicsWorkspace/HIJetMass/
InputFolder=CombinedResult
IntermediateFolder=TempResult
OutputFolder=ScaledResult
CrossSectionFile=$WorkspaceBase/CommonCode/input/SampleCrossSection.input
CombinationFile=$WorkspaceBase/CommonCode/input/SampleCombination.input

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


