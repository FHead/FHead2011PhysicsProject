for Location in `cat Input`
do
   Run2=`basename $Location`
   Run1=`basename \`dirname $Location\``
   Version=`basename \`dirname \\\`dirname \\\\\\\`dirname $Location\\\\\\\`\\\`\``

   echo $Location $Version $Run1 $Run2

   ./b.out ${Version}_${Run1}${Run2}
done




