#!/bin/sh

SampleLocation=$1
SamplePTHat=$2
Executable=$3
Parameters=...
WorkspaceBase=/afs/cern.ch/work/c/chenyi/PhysicsWorkspace/HIJetMass/
EOSBase=/afs/cern.ch/user/c/chenyi/EOS/cms/
TempFile=JAKSDJGKAHWIEHNDFJNSDLJFHADOSHGAJHEGJHW

TempFile1=${TempFile}1
TempFile2=${TempFile}2

if [ -z "$1" ]
then
   echo "[Notice] No argument supplied, using default sample locations"
   SampleLocation=$WorkspaceBase/CommonCode/input/SampleLocation.input
fi

if [ "$1" = "DEFAULT" ]
then
   echo "[Notice] using default sample locations"
   SampleLocation=$WorkspaceBase/CommonCode/input/SampleLocation.input
fi

shift

if [ -z "$1" ]
then
   echo "[Notice] No argument supplied, using default sample PT hat range"
   SamplePTHat=$WorkspaceBase/CommonCode/input/SamplePTHat.input
fi

if [ "$1" = "NONE" ]
then
   echo "[Notice] don't use PT hat range"
   SamplePTHat=
fi

if [ "$1" = "DEFAULT" ]
then
   echo "[Notice] using default sample PT hat range"
   SamplePTHat=$WorkspaceBase/CommonCode/input/SamplePTHat.input
fi

shift

if [ -z "$1" ]
then
   echo "[Notice] Please supply the executable you want to run!"
   echo "         The executable should take three arguments, one input rootfile and one output rootfile"
   echo "         and then the sample tag"
   echo "         the rest of the arguments after this one will be passed into the executable"
   exit
fi

shift

shift

mkdir -p Result/

rm -f $TempFile1 $TempFile2
touch $TempFile1 $TempFile2

while read p
do
   Tag=`echo $p | awk '{print $1}'`
   Location=`echo $p | awk '{print $2}'`

   if [ "$Location" = "NONE" ]; then
      continue
   fi

   if [ -z "$Tag" ]; then
      continue
   fi

   PTHatMin=`grep "^$Tag " $SamplePTHat | awk '{print $2}'`
   PTHatMax=`grep "^$Tag " $SamplePTHat | awk '{print $3}'`
   
   if [ "$SamplePTHat" = "NONE" ]; then
      PTHatMin=
      PTHatMax=
   fi

   echo "function Run$Tag()"
   echo "{"
   echo "   echo start running $Tag"
   echo

   FileCount=0
   if [[ $Location == root*root ]]
   then
      echo "   " $Executable $Location Result/${Tag}_${FileCount}.root $Tag $PTHatMin $PTHatMax \$1 \$2 \$3 "$@"
      FileCount=$((FileCount+1))
   else
      for i in $EOSBase/$Location/*root
      do
         echo "   " $Executable $i Result/${Tag}_${FileCount}.root $Tag $PTHatMin $PTHatMax \$1 \$2 \$3 "$@"
         FileCount=$((FileCount+1))
      done
   fi

   echo "}"
   
   echo "function Submit$Tag()"
   echo "{"
   echo "   echo start submitting $Tag"
   echo

   FileCount=0
   if [[ $Location == root*root ]]
   then
      echo "   sed \"s#__EXECUTABLE__#$PWD/$Executable#g\" < BatchTemplate.submit \\"
      echo "      | sed \"s#__INPUT__#$Location#g\" \\"
      echo "      | sed \"s#__OUTPUT__#$PWD/Result/${Tag}_${FileCount}.root#g\" \\"
      echo "      | sed \"s#__PTHATMIN__#$PTHatMin#g\" \\"
      echo "      | sed \"s#__PTHATMAX__#$PTHatMax#g\" \\"
      echo "      | sed \"s#__EXTRA1__#\$1#g\" \\"
      echo "      | sed \"s#__EXTRA2__#\$2#g\" \\"
      echo "      | sed \"s#__EXTRA3__#\$3#g\" \\"
      echo "      | sed \"s#__TAG__#$Tag#g\" | bsub -J ${Tag}"
      FileCount=$((FileCount+1))
   else
      for i in $EOSBase/$Location/*root
      do
         i=`echo $i | sed "s#$EOSBase/##g"`
         echo "   sed \"s#__EXECUTABLE__#$PWD/$Executable#g\" < BatchTemplate.submit \\"
         echo "      | sed \"s#__INPUT__#$i#g\" \\"
         echo "      | sed \"s#__OUTPUT__#$PWD/Result/${Tag}_${FileCount}.root#g\" \\"
         echo "      | sed \"s#__PTHATMIN__#$PTHatMin#g\" \\"
         echo "      | sed \"s#__PTHATMAX__#$PTHatMax#g\" \\"
         echo "      | sed \"s#__EXTRA1__#\$1#g\" \\"
         echo "      | sed \"s#__EXTRA2__#\$2#g\" \\"
         echo "      | sed \"s#__EXTRA3__#\$3#g\" \\"
         echo "      | sed \"s#__TAG__#$Tag#g\" | bsub -J ${Tag}"
         FileCount=$((FileCount+1))
      done
   fi

   echo "}"
   
   echo "# Run$Tag" >> $TempFile1
   echo "# Submit$Tag" >> $TempFile2
   echo

done < $SampleLocation > RunAll.sh

cat RunAll.sh $TempFile1 $TempFile2 > Total$TempFile
rm -f $TempFile1 $TempFile2
mv Total$TempFile RunAll.sh

cp $WorkspaceBase/CommonCode/script/BatchHeaderCopy.txt BatchTemplate.submit

echo "if [[ __INPUT__ != root* ]]" >> BatchTemplate.submit
echo "then" >> BatchTemplate.submit
echo "   __EXECUTABLE__ /eos/cms/__INPUT__ Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ __EXTRA1__ __EXTRA2__ __EXTRA3__ $@" >> BatchTemplate.submit
echo "else" >> BatchTemplate.submit
echo "   __EXECUTABLE__ __INPUT___ Output.root __TAG__ __PTHATMIN__ __PTHATMAX__ __EXTRA1__ __EXTRA2__ __EXTRA3__ $@" >> BatchTemplate.submit
echo "fi" >> BatchTemplate.submit

BaseDirAfterWorkspace=`echo $PWD | tr '/' '\n' | grep -A 999 PhysicsWorkspace | tail -n+2 | tr '\n' '/'`
echo "# mv Output.root /eos/cms/store/cmst3/user/chenyi/BatchOutput/$BaseDirAfterWorkspace/Result/\`basename __OUTPUT__\`" >> BatchTemplate.submit
echo "mv Output.root __OUTPUT__" >> BatchTemplate.submit


