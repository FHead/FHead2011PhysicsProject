#!/bin/sh

for i in *.pdf.broken
do
   Model=`echo $i | cut --delim='_' --field=2`
   Cut=`echo $i | cut --delim='_' --field=3`
   ID=`echo $i | cut --delim='_' --field=4`
   ID=${ID/.pdf.broken}

   echo $Model $Cut $ID
   
   cat BatchSubmit.template | \
      sed "s/__MODEL__/$Model/g" | \
      sed "s/__CUT__/$Cut/g" | \
      sed "s/__ID__/$ID/g" | \
      bsub -J BetterHypothesisTesting -q 1nw
done
