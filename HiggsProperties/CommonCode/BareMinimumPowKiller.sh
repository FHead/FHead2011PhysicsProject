cat $1 \
   | sed "s/Mz/MZ/g" \
   | sed "s/SC(p1,p2)/C12/g" \
   | sed "s/SC(p1,p3)/C13/g" \
   | sed "s/SC(p1,p4)/C14/g" \
   | sed "s/SC(p1,p5)/C15/g" \
   | sed "s/SC(p1,p6)/C16/g" \
   | sed "s/SC(p2,p3)/C23/g" \
   | sed "s/SC(p2,p4)/C24/g" \
   | sed "s/SC(p2,p5)/C25/g" \
   | sed "s/SC(p2,p6)/C26/g" \
   | sed "s/SC(p3,p4)/C34/g" \
   | sed "s/SC(p3,p5)/C35/g" \
   | sed "s/SC(p3,p6)/C36/g" \
   | sed "s/SC(p4,p5)/C45/g" \
   | sed "s/SC(p4,p6)/C46/g" \
   | sed "s/SC(p5,p6)/C56/g" \
   | sed "s/SC(p2,p1)/C12/g" \
   | sed "s/SC(p3,p1)/C13/g" \
   | sed "s/SC(p4,p1)/C14/g" \
   | sed "s/SC(p5,p1)/C15/g" \
   | sed "s/SC(p6,p1)/C16/g" \
   | sed "s/SC(p3,p2)/C23/g" \
   | sed "s/SC(p4,p2)/C24/g" \
   | sed "s/SC(p5,p2)/C25/g" \
   | sed "s/SC(p6,p2)/C26/g" \
   | sed "s/SC(p4,p3)/C34/g" \
   | sed "s/SC(p5,p3)/C35/g" \
   | sed "s/SC(p6,p3)/C36/g" \
   | sed "s/SC(p5,p4)/C45/g" \
   | sed "s/SC(p6,p4)/C46/g" \
   | sed "s/SC(p6,p5)/C56/g" \
   | sed "s/EPS(p1,p2,p3,p4)/E1234/g" \
   | sed "s/EPS(p1,p2,p4,p3)/(-E1234)/g" \
   | sed "s/EPS(p1,p2,p3,p5)/E1235/g" \
   | sed "s/EPS(p1,p2,p5,p3)/(-E1235)/g" \
   | sed "s/EPS(p1,p2,p3,p6)/E1236/g" \
   | sed "s/EPS(p1,p2,p4,p5)/E1245/g" \
   | sed "s/EPS(p1,p2,p5,p4)/(-E1245)/g" \
   | sed "s/EPS(p1,p2,p4,p6)/E1246/g" \
   | sed "s/EPS(p1,p2,p5,p6)/E1256/g" \
   | sed "s/EPS(p1,p3,p4,p5)/E1345/g" \
   | sed "s/EPS(p1,p5,p4,p3)/(-E1345)/g" \
   | sed "s/EPS(p1,p3,p4,p6)/E1346/g" \
   | sed "s/EPS(p1,p4,p3,p6)/(-E1346)/g" \
   | sed "s/EPS(p1,p3,p5,p6)/E1356/g" \
   | sed "s/EPS(p1,p5,p3,p6)/(-E1356)/g" \
   | sed "s/EPS(p1,p4,p5,p6)/E1456/g" \
   | sed "s/EPS(p1,p5,p4,p6)/(-E1456)/g" \
   | sed "s/EPS(p2,p3,p4,p5)/E2345/g" \
   | sed "s/EPS(p2,p5,p4,p3)/(-E2345)/g" \
   | sed "s/EPS(p2,p3,p4,p6)/E2346/g" \
   | sed "s/EPS(p2,p4,p3,p6)/(-E2346)/g" \
   | sed "s/EPS(p2,p3,p5,p6)/E2356/g" \
   | sed "s/EPS(p2,p5,p3,p6)/(-E2356)/g" \
   | sed "s/EPS(p2,p4,p5,p6)/E2456/g" \
   | sed "s/EPS(p2,p5,p4,p6)/(-E2456)/g" \
   | sed "s/EPS(p3,p4,p5,p6)/E3456/g" \
   | sed "s/EPS(p5,p4,p3,p6)/(-E3456)/g" \
   | sed "s/pow(Mq,2)/s/g" \
   | sed "s/cos(theta1)/X/g" | sed "s/sin(theta1)/sX/g" \
   | sed "s/cos(theta2)/Y/g" | sed "s/sin(theta2)/sY/g" \
   | sed "s/cos(Theta)/Z/g" | sed "s/sin(Theta)/sZ/g" \
   | sed "s/cos(2\*theta1)/X2/g" \
   | sed "s/cos(2\*theta2)/Y2/g" \
   | sed "s/cos(phi)/CosPhi/g" | sed "s/sin(phi)/SinPhi/g" \
   | sed "s/cos(Phi1)/CosPhi1/g" | sed "s/sin(Phi1)/SinPhi1/g" \
   | sed "s/Complex/complex<double>/g" \
   | sed "s/\[Gamma]/Gamma/g" | sed "s/\[Beta]/Beta/g" \
   | tr -d '\'

   # | sed '/(-MZ + pow(2,0.5)\*pow(C12,0.5))\*$/{N;s/(-MZ + pow(2,0.5)\*pow(C12,0.5))\*\n[ ]*(MZ + pow(2,0.5)\*pow(C12,0.5))/(-MZ*MZ + 2*C12)/}' \
   # | sed '/(-MZ + pow(2,0.5)\*pow(C34,0.5))\*$/{N;s/(-MZ + pow(2,0.5)\*pow(C34,0.5))\*\n[ ]*(MZ + pow(2,0.5)\*pow(C34,0.5))/(-MZ*MZ + 2*C34)/}' \
   # | sed '/(-MZ + pow(2,0.5)\*pow(C36,0.5))\*$/{N;s/(-MZ + pow(2,0.5)\*pow(C36,0.5))\*\n[ ]*(MZ + pow(2,0.5)\*pow(C36,0.5))/(-MZ*MZ + 2*C36)/}' \
   # | sed '/(MZ - pow(2,0.5)\*pow(C36,0.5))\*$/{N;s/(MZ - pow(2,0.5)\*pow(C36,0.5))\*\n[ ]*(MZ + pow(2,0.5)\*pow(C36,0.5))/(MZ*MZ - 2*C36)/}' \
   # | sed '/(-MZ + pow(2,0.5)\*pow(C45,0.5))\*$/{N;s/(-MZ + pow(2,0.5)\*pow(C45,0.5))\*\n[ ]*(MZ + pow(2,0.5)\*pow(C45,0.5))/(-MZ*MZ + 2*C45)/}' \
   # | sed '/(MZ - pow(2,0.5)\*pow(C45,0.5))\*$/{N;s/(MZ - pow(2,0.5)\*pow(C45,0.5))\*\n[ ]*(MZ + pow(2,0.5)\*pow(C45,0.5))/(MZ*MZ - 2*C45)/}' \
   # | sed '/(MZ - pow(2,0.5)\*pow(C56,0.5))\*$/{N;s/(MZ - pow(2,0.5)\*pow(C56,0.5))\*\n[ ]*(MZ + pow(2,0.5)\*pow(C56,0.5))/(MZ*MZ - 2*C56)/}' \
   # | sed '/(pow(2,0.5)\*pow(C34,0.5) - pow(2,0.5)\*pow(C36,0.5))\*$/{N;s/(pow(2,0.5)\*pow(C34,0.5) - pow(2,0.5)\*pow(C36,0.5))\*\n[ ]*(pow(2,0.5)\*pow(C34,0.5) + pow(2,0.5)\*pow(C36,0.5))/(2*C34-2*C36)/}' \
   # | sed '/(pow(2,0.5)\*pow(C34,0.5) - pow(2,0.5)\*pow(C45,0.5))\*$/{N;s/(pow(2,0.5)\*pow(C34,0.5) - pow(2,0.5)\*pow(C45,0.5))\*\n[ ]*(pow(2,0.5)\*pow(C34,0.5) + pow(2,0.5)\*pow(C45,0.5))/(2*C34-2*C45)/}' \
   # | tr -d '\'


# echo "Check the final few multi-line patterns!"


