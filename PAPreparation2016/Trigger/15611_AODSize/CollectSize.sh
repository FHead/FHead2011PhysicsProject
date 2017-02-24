for Tag in `cat TriggerList2.txt`
do
   Tag=${Tag::${#Tag}-1}
   echo $Tag `root -l -b -q Done/${Tag}[0-9]_AOD_l4.root EntryCount.C | grep ENTRYCOUNT | awk '{print $2}'` \
      `edmEventSize -v Done/${Tag}[0-9]_AOD_l4.root | awk '{print $2}' | grep ^[0-9] | Sum` \
      `edmEventSize -v Done/${Tag}[0-9]_AOD_l4.root | awk '{print $3}' | grep ^[0-9] | Sum` \
      `edmEventSize -v Done/${Tag}[0-9]_AOD_l7.root | awk '{print $3}' | grep ^[0-9] | Sum`
done | tee Result2.txt
