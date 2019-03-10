head -n 500 Meow | \
   while read Lumi File1 File2; do
      echo Start running lumisection $Lumi
      ./a.out $File1 ResultNoPU/Result_Lumi${Lumi}.root ak4pfchs $Lumi
      ./a.out $File2 ResultWithPU/Result_Lumi${Lumi}.root ak4pfchs $Lumi
   done
