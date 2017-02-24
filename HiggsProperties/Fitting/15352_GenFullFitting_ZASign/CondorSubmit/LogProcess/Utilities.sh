function FRunRemaining()
{
   for i in `seq 1 100000`
   do
      sh CalculateAll.sh
      echo Sleeping, safe to terminate
      sleep 60
   done
}
