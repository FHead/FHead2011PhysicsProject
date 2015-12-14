echo > AllLog
grep LOG log_C | sed "s/LOG/0/" | awk '{print $1,$2,$3,$4,$5,$7}' >> AllLog
grep LOG log_B | sed "s/LOG/1/" | awk '{print $1,$2,$3,$4,$5,$7}' >> AllLog
grep LOG log_5B | sed "s/LOG/2/" | awk '{print $1,$2,$3,$4,$5,$7}' >> AllLog
grep LOG log_15B | sed "s/LOG/3/" | awk '{print $1,$2,$3,$4,$5,$7}' >> AllLog
grep LOG log_T | sed "s/LOG/4/" | awk '{print $1,$2,$3,$4,$5,$7}' >> AllLog

cat AllLog | TextToTree Meow.root 6 "Particle:Sigma:Radius:Density:SpeedOfChange:Acceleration"


