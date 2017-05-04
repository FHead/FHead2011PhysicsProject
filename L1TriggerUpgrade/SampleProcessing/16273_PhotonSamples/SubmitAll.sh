for PU in 200 140
do
   mkdir -p Result/PU$PU

   for File in `ls SampleBase/PU$PU/`
   do
      echo $File

      cat BatchScript.sh | sed "s/__PU__/$PU/g" | sed "s/__File__/$File/g" | \
         bsub -J RunHGaGaPU$PU
   done
done
