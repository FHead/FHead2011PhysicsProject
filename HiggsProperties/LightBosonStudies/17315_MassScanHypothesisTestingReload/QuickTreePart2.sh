DumpDHFile ResultDatabase.dh  | grep -v L[12]D | sed ':a;N;$!ba;s/Fixed\n/ /g' | grep -v "^$" \
   | tr '[]()' ' ' \
   | awk '{if($3 == "A1UU") {print;}}' \
   | awk '{if($11 == "A1UU") {print;}}' \
   | awk '{if($4 == $12) {print;}}' \
   | grep " -1 -1 -1" \
   | awk '{print $4,$2,$7,$16}' \
   | sed "s/A2UU/1/g" \
   | sed "s/A2UA/2/g" \
   | sed "s/A2UZ/3/g" \
   | sed "s/A3UU/4/g" \
   | sed "s/A1UZ/5/g" \
   | sed "s/A3UA/6/g" \
   | sed "s/A3UZ/7/g" \
   | tr 'p' '.' \
   | TextToTree PValues2e2mu.root 4 "T:M:N:P"

DumpDHFile ResultDatabase.dh  | grep -v L[12]D | sed ':a;N;$!ba;s/Fixed\n/ /g' | grep -v "^$" \
   | tr '[]()' ' ' \
   | awk '{if($3 == "A1UU") {print;}}' \
   | awk '{if($11 == "A1UU") {print;}}' \
   | awk '{if($4 == $12) {print;}}' \
   | grep " -1 -1" \
   | grep -v " -1 -1 -1" \
   | awk '{print $4,$2,$7,$16}' \
   | sed "s/A2UU/1/g" \
   | sed "s/A2UA/2/g" \
   | sed "s/A2UZ/3/g" \
   | sed "s/A3UU/4/g" \
   | sed "s/A1UZ/5/g" \
   | sed "s/A3UA/6/g" \
   | sed "s/A3UZ/7/g" \
   | tr 'p' '.' \
   | TextToTree PValues4e4mu.root 4 "T:M:N:P"
