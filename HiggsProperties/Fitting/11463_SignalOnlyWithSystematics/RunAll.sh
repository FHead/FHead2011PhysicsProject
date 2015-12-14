for i in `seq 1 100` `seq 110 10 500` `seq 550 50 1000`
do
   ./a.out $i 1125
   ./a.out $i 8125
done

mkdir -p Results
mv FitResults* Result/

hadd -f AllResult_1125.root Result/*1125*root
hadd -f AllResult_8125.root Result/*8125*root



