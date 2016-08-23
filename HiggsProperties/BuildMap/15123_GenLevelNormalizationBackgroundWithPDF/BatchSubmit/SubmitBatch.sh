#!/bin/bash
#BSUB -J prog[1-4]
# %I will be replaced by 1, 2, etc. in -e and -o
#BSUB -e Log/proglsf%I.err
#BSUB -o Log/proglsf%I.out

echo $PWD
touch Log/${LSB_JOB_INDEX}.txt

echo "LSB_JOB_INDEX = ${LSB_JOB_INDEX}"
echo "LSB_JOBINDEX = ${LSB_JOBINDEX}"
echo "LSBJOBINDEX = ${LSBJOBINDEX}"

