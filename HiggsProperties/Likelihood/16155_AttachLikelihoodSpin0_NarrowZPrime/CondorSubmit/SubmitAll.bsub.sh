D=$1

DirName=`ls /eos/user/c/chenyi/MGSample/ | grep $D`

echo $D
echo $DirName

for i in `ls ../OriginalTrees$D/ | grep -v ForEff | grep "_[1-6].root"`
do
   # cat BatchTemplate.submit | \
   #    sed "s#__INPUT__#/store/cmst3/user/chenyi/MGSamples/$DirName/Processed/$i#g" | \
   #    sed "s#__OUTPUT__#/store/cmst3/user/chenyi/MGSamples/$DirName/AttachedSpin0XVV/$i#g" | \
   #    sed "s#__SEED__#-1#g" | \
   #    sed "s#__ENERGY__#0#g" | bsub -J Likelihood$D
   cat BatchTemplate.submit | \
      sed "s#__INPUT__#/eos/user/c/chenyi/MGSample/$DirName/Processed/$i#g" | \
      sed "s#__OUTPUT__#/eos/user/c/chenyi/MGSample/$DirName/AttachedSpin0XVV/$i#g" | \
      sed "s#__SEED__#-1#g" | \
      sed "s#__ENERGY__#0#g" | bsub -J Likelihood$D
done

