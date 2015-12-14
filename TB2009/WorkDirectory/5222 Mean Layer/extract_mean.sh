grep -H MaxLayer *log | grep Motherboard\ 0 | grep "Mean of mean" | cut --f=1-1,8-8 --delim=' ' | cut --b=1-6,55-

