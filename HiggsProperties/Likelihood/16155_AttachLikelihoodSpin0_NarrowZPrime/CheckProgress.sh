for i in `ls | grep AttachedTrees | sed "s/AttachedTrees//"`
do
   All=`ls OriginalTrees$i | wc -l`
   Done=`ls AttachedTrees$i | wc -l`
   echo "$i $All $Done" | awk '{print $1":",$3"/"$2,"=",$3/$2*100"%"}'
done
