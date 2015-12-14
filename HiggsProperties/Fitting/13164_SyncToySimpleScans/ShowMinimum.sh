for i in `seq 1 80`; do echo $i `grep FVAL ~/Submit_$i.sh.o* | awk '{print $3}' | sort -n | head -1`; done
