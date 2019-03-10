for i in `cat ToSubmit.txt`
do
   Tag=`echo $i | cut -d ':' -f 1`v3
   Dataset=`echo $i | cut -d ':' -f 2`
   echo $Tag $Dataset

   FileName=Submit_${Tag}.py

   echo "DatasetName = '$Dataset'" > $FileName
   echo "Tag = '$Tag'" >> $FileName
   cat Submit_Template.py >> $FileName
done
