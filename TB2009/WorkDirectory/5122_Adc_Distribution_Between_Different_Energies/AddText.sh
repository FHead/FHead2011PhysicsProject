# $1 input
# $2 output
# $3 text to add

cat $1 | sed "s/ /_/g" > $1.temp
(for i in `cat $1.temp`
do
   echo $3 $i
done) > $1.temp2
cat $1.temp2 | sed "s/_/ /g" > $2
rm $1.temp
rm $1.temp2

