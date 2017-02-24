# rm LOG
# 
# for i in `ls Trees15352`
# do
#    ./Run Trees15352/$i
# done > LOG
# 
# for i in `ls Trees15254 | grep -v gg`
# do
#    ./Run Trees15254/$i
# done >> LOG
# 
# for i in `ls Trees15315`
# do
#    ./Run Trees15315/$i
# done >> LOG

for i in uubar ddbar SMVV 5plet 5PpYT SMpMYT
do
   for j in 2e2mu 4e
   do
      echo -ne "$i\t$j\t"
      grep $i LOG | grep -v ForEff | grep $j | cut --delim=' ' --field=2- | ColumnSum \
         | awk '{print $2/$1"\t"$3/$1"\t"$4/$1"\t"$5/$1"\t"$6/$1"\t"$7/$1"\t"$8/$1"\t"$9/$1"\t"$10/$1"\t"$11/$1"\t"$12/$1"\t"$13/$1"\t"$14/$1}'
   done
done




