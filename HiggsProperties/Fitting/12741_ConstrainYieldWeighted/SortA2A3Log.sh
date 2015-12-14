grep ^LIKELIHOOD LOG | awk '{print $2,$3,$5,$4}' | sort -g | awk '{print $1,$2,$4,$3}' > A2A3ProfileFB
grep ^LIKELIHOOD LOG | awk '{if($4 == 0.5) {print $2,$3,$5,$4}}' | sort -g | awk '{print $1,$2,$4,$3}' > A2A3FixFB

