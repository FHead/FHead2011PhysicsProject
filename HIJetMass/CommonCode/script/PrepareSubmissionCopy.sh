#!/bin/sh

SampleLocation=$1
Executable=$2
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
   echo "[Notice] Please supply the executable you want to run!"
   echo "         The executable should take three arguments, one input rootfile and one output rootfile"
   echo "         and then the sample tag"
   echo "         the rest of the arguments after this one will be passed into the executable"
   exit
fi

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

   echo "function Run$Tag()"
   echo "{"
   echo "   echo start running $Tag"
   echo

   FileCount=0
   for i in `ls $EOSBase/$Location | grep root$`
   do
      echo "   " $Executable $EOSBase/$Location/$i Result/${Tag}_${FileCount}.root $Tag "$@"
      FileCount=$((FileCount+1))
   done

   echo "}"
   
   echo "function Submit$Tag()"
   echo "{"
   echo "   echo start submitting $Tag"
   echo

   FileCount=0
   for i in `ls $EOSBase/$Location | grep root$`
   do
      echo "   sed \"s#__EXECUTABLE__#$PWD/$Executable#g\" < BatchTemplate.submit \\"
      echo "      | sed \"s#__INPUT__#$Location/$i#g\" \\"
      echo "      | sed \"s#__OUTPUT__#$PWD/Result/${Tag}_${FileCount}.root#g\" \\"
      echo "      | sed \"s#__TAG__#$Tag#g\" | bsub"
      FileCount=$((FileCount+1))
   done

   echo "}"
   
   echo "Run$Tag" >> $TempFile1
   echo "# Submit$Tag" >> $TempFile2
   echo

done < $SampleLocation | tee RunAll.sh

cat RunAll.sh $TempFile1 $TempFile2 > Total$TempFile
rm -f $TempFile1 $TempFile2
mv Total$TempFile RunAll.sh

cp $WorkspaceBase/CommonCode/script/BatchHeaderCopy.txt BatchTemplate.submit
echo "__EXECUTABLE__ Input.root Output.root __TAG__ $@" >> BatchTemplate.submit
echo "mv Output.root __OUTPUT__" >> BatchTemplate.submit


