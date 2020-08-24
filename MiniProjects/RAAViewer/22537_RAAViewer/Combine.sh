echo "Data = [" > Data.json
# cat `cat Fragments/RecordList.txt | awk '{print "Fragments/"$$1}'` >> Data.json
cat Fragments/*json >> Data.json
echo "]" >> Data.json

