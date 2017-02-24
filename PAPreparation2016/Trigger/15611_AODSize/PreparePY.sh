for i in *txt
do
   TAG=${i/.txt/}
   EVENTS=`cat $i | sed "s/,$//"`

   cat Estimate_template.py | sed "s/__EVENTS__/$EVENTS/g" | sed "s/__TAG__/$TAG/g" > ${TAG}.py
done
