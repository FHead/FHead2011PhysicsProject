for i in `ls CombinedResult/`; do echo $i; ./a.out CombinedResult/$i ${i/.root}; done

