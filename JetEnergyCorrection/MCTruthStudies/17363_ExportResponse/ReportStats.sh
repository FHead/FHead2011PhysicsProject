File=$1

echo "Raw average     = `awk '{print $2/$1}' < $File | Average`"
echo "L1 average      = `awk '{print $3/$1}' < $File | Average`"
echo "L1+L2L3 average = `awk '{print $4/$1}' < $File | Average`"
echo "Raw median      = `awk '{print $2/$1}' < $File | Median`"
echo "L1 median       = `awk '{print $3/$1}' < $File | Median`"
echo "L1+L2L3 median  = `awk '{print $4/$1}' < $File | Median`"


