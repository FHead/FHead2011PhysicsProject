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

hadd -f AK2.root TidyRoot/*akCs2*root
hadd -f AK10.root TidyRoot/*akCs10*root
