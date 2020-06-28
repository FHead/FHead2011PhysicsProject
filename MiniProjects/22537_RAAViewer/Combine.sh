echo "[" > Data.json
cat `cat Fragments/RecordList.txt | awk '{print "Fragments/"$$1}'` >> Data.json
echo "]" >> Data.json

