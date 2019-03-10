for i in 18p4 18p8 18p9 18p92 18p94 19p0 19p3
do
   for j in 5 10 # 5 10 20 50 100 200 500 1000
   do
      State="$i A1UU A2UU CutP S($j $j -1 -1) [A1UU A2UU] Fixed"
      echo 1 ${i/p/.} $j `DHQuery ResultDatabase.dh "$State" "Model PValue"`
      State="$i A1UU A2UA CutP S($j $j -1 -1) [A1UU A2UA] Fixed"
      echo 2 ${i/p/.} $j `DHQuery ResultDatabase.dh "$State" "Model PValue"`
      State="$i A1UU A2UZ CutP S($j $j -1 -1) [A1UU A2UZ] Fixed"
      echo 3 ${i/p/.} $j `DHQuery ResultDatabase.dh "$State" "Model PValue"`
      State="$i A1UU A3UU CutP S($j $j -1 -1) [A1UU A3UU] Fixed"
      echo 4 ${i/p/.} $j `DHQuery ResultDatabase.dh "$State" "Model PValue"`
      State="$i A1UU A1UZ CutP S($j $j -1 -1) [A1UU A1UZ] Fixed"
      echo 5 ${i/p/.} $j `DHQuery ResultDatabase.dh "$State" "Model PValue"`
   done
done | tee Tree.txt | TextToTree PValues.root 4 "T:M:N:P"

