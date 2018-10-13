#!/bin/bash

Input=openHLT.root
Trigger=HLT_PuAK4CaloJet40Eta5p1_v1

Input=$1
Trigger=$2

cat > XD.C <<EOF
{
   TTree *T = (TTree *)hltbitanalysis->Get("HltTree");
   cout << "Trigger $Trigger"
      << " " << T->GetEntries("$Trigger")
      << " " << T->GetEntries("") << endl;
   return 0;
}
EOF

root -l -b -q $Input XD.C




