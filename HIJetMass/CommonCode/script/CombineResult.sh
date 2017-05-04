ResultDirectory=$1
CombinedDirectory=$2

if [ -z $1 ]
then
   echo "[Notice] Please specify the directory where the individual results are in!"
   exit
fi

if [ -z $2 ]
then
   echo "[Notice] Using default combined folder name: CombinedResult"
   CombinedDirectory=CombinedResult
fi

mkdir -p $CombinedDirectory

for i in `ls $ResultDirectory | grep root$ | rev | cut -d '_' -f 2- | rev | sort | uniq`
do
   hadd -f -k $CombinedDirectory/${i}.root $ResultDirectory/${i}_[0-9]*.root
done






