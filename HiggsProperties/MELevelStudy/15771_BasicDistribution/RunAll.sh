for i in `ls MGSample/ | grep ^15773`
do
   mkdir -p Result/$i

   for j in `ls MGSample/$i/Processed/`
   do
      echo $i $j
      Tag=${j/.root}

      ./a.out MGSample/$i/Processed/$j $Tag

      mv QuickLook_${Tag}.pdf Result/$i/
   done
done
