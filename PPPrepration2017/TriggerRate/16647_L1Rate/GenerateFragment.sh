#!/bin/sh

for i in `cat ListOfSeeds_v3.txt`
do
   j=`echo $i | tr -d '_'`
   echo "process.hlt$j = process.hltL1sZeroBias.clone()"
   echo "process.hlt${j}.L1SeedsLogicalExpression = cms.string('$i')"
   echo "process.hltPre$j = process.hltPreL1ZeroBias.clone()"
   echo "process.HLT_$i = cms.Path( process.HLTBeginSequence + process.hlt$j + process.hltPre$j + process.HLTEndSequence )"
   echo "# process.HLTSchedule.extend(*(process.HLT_$i))"
   echo
done

