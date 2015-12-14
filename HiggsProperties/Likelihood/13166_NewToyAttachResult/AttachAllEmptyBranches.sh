for i in Destination/*2e2mu*
do
   ./AttachEmptyBranch "logLGGZZ_4e" $i
   ./AttachEmptyBranch "logLGGZZ_4mu" $i
   ./AttachEmptyBranch "logLZJets_4e" $i
   ./AttachEmptyBranch "logLZJets_4mu" $i
done

for i in Destination/*4e4mu*
do
   ./AttachEmptyBranch "logLGGZZ_2e2mu" $i
   ./AttachEmptyBranch "logLGGZZ_2mu2e" $i
   ./AttachEmptyBranch "logLZJets_2e2mu" $i
   ./AttachEmptyBranch "logLZJets_2mu2e" $i
done

