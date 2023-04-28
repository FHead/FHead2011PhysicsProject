
rm -f x*

split -l 20 AllFiles.txt

for Tag in x*
do
   sed "s/__TAG__/$Tag/g" < Macro.py > Run.py
   cmsRun Run.py
   rm -f Run.py
done



