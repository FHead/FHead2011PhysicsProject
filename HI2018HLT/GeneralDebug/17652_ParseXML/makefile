default: DoParsing

DoParsing:
	egrep -e "^    <name>|^    <index>" L1Menu_CollisionsHeavyIons2018_v4_2_0-d1.xml \
	   | sed "s/name//g" | sed "s/index//g" | tr -d '<>/' | Reformat 2 | awk '{if($$2<1000) print $$2,$$1}' \
		| sort -n > Temp
	awk '{print $$1}' < Temp
	awk '{print $$2}' < Temp



