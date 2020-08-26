
Setup=$1
Data=$2
Cov=$3

ls -tr txt/ | grep _${Setup}_ | grep _Data${Data}_ | grep _CovType${Cov}_ | cut -d '_' -f 1-13 | uniq | tail -n1
ls -tr txt/ | grep _${Setup}_ | grep _Data${Data}_ | grep _CovType${Cov}_ | cut -d '_' -f 1-13 | uniq | tail -n1 1>&2


