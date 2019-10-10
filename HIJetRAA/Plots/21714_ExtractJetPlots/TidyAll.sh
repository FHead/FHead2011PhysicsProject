mkdir -p TidyRoot

for i in `ls Root | grep _CentTest_`
do
   echo $i
   ./Tidy --Input Root/$i --Output TidyRoot/$i --IsMu true
done
for i in `ls Root | grep _ResCentTest_`
do
   echo $i
   ./Tidy --Input Root/$i --Output TidyRoot/$i --IsSigma true
done
for i in `ls Root | grep _ResOverMuCentTest_`
do
   echo $i
   ./Tidy --Input Root/$i --Output TidyRoot/$i --IsSigmaMu true
done

hadd -f AK4.root TidyRoot/*akCs4*root
hadd -f AK8.root TidyRoot/*akCs8*root
