Input=OriginalLog_HZZ4l

grep Central $Input | cut --delim=' ' --field=3- | sort -n > Log_HZZ4l_Central
grep LeptonUp $Input | cut --delim=' ' --field=3- | sort -n > Log_HZZ4l_LeptonUp
grep LeptonDown $Input | cut --delim=' ' --field=3- | sort -n > Log_HZZ4l_LeptonDown
grep LeptonWide $Input | cut --delim=' ' --field=3- | sort -n > Log_HZZ4l_LeptonWide
grep LeptonNarrow $Input | cut --delim=' ' --field=3- | sort -n > Log_HZZ4l_LeptonNarrow








