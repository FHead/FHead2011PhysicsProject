
WorkspaceBase=~/work/PhysicsWorkspace/HIJetMass/
InputFolder=CombinedResult
OutputFolder=ScaledResult
CrossSectionFile=$WorkspaceBase/CommonCode/input/SampleCrossSection.input

mkdir -p $OutputFolder

for i in `ls $InputFolder`
do
   Tag=${i/.root}
   InputFile=$InputFolder/$i
   OutputFile=$OutputFolder/$i

   if grep -q $Tag $CrossSectionFile
   then
      CrossSection=`grep $Tag $CrossSectionFile | awk '{print $2}'`
      if [ "$CrossSection" != "-1" ]
      then
         $WorkspaceBase/CommonCode/bin/ScaleHistograms $InputFile $OutputFile $CrossSection $Tag
      else
         $WorkspaceBase/CommonCode/bin/AttachTags $InputFile ${OutputFile/.root/_NoCrossSection.root} $Tag
      fi
   else
      $WorkspaceBase/CommonCode/bin/AttachTags $InputFile ${OutputFile/.root/_NoSuchSample.root} $Tag
   fi
done



