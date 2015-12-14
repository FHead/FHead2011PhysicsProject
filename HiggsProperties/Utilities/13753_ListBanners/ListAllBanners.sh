mkdir -p Banners

for i in `find ~/Hadoop/MadgraphSampleRepository | grep unweighted_events.lhe`
do
   Folder=`echo $i | cut --delim='/' --field=6`
   Name=`echo $i | cut --delim='/' --field=7`

   echo $Folder, $Name

   mkdir -p Banners/$Folder
   sed -e '/<event>/,$d' $i > Banners/$Folder/$Name.banner.txt
done

tar zcvf Banners.tar.gz Banners


