for i in `ls *err* | cut --delim '.' --field=3`; do ls ../Output/Result_${i}.root; done
