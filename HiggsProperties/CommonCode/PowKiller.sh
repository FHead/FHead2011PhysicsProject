cat $1 \
   | sed "s/pow(2,0.5)/Sqrt2/g" \
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
   | sed "s/pow(s,0.5)/MH/g" \
   | sed "s/pow(s,1.5)/(s*MH)/g" \
   | sed "s/pow(s,2)/(s*s)/g" \
   | sed "s/pow(Mq,2)/s/g" \
   | sed "s/pow(M1,2)/(M1*M1)/g" | sed "s/pow(M2,2)/(M2*M2)/g" \
   | sed "s/pow(MZ,2)/(MZ*MZ)/g" \
   | sed "s/pow(wZ,2)/(wZ*wZ)/g" \
   | sed "s/pow(gqL,2)/(gqL*gqL)/g" | sed "s/pow(gqR,2)/(gqR*gqR)/g" \
   | sed "s/pow(gL,2)/(gL*gL)/g" | sed "s/pow(gR,2)/(gR*gR)/g" \
   | sed "s/pow(el,2)/(el*el)/g" \
   | sed "s/pow(eq,2)/(eq*eq)/g" \
   | sed "s/pow(beta1,2)/(beta1*beta1)/g" \
   | sed "s/pow(beta2,2)/(beta2*beta2)/g" \
   | sed "s/pow(gamma1,2)/(gamma1*gamma1)/g" \
   | sed "s/pow(gamma2,2)/(gamma2*gamma2)/g" \
   | sed "s/pow(M1,3)/(M1*M1*M1)/g" | sed "s/pow(M2,3)/(M2*M2*M2)/g" \
   | sed "s/pow(MZ,3)/(MZ*MZ*MZ)/g" \
   | sed "s/pow(wZ,3)/(wZ*wZ*wZ)/g" \
   | sed "s/pow(gqL,3)/(gqL*gqL*gqL)/g" | sed "s/pow(gqR,3)/(gqR*gqR*gqR)/g" \
   | sed "s/pow(gL,3)/(gL*gL*gL)/g" | sed "s/pow(gR,3)/(gR*gR*gR)/g" \
   | sed "s/pow(el,3)/(el*el*el)/g" \
   | sed "s/pow(eq,3)/(eq*eq*eq)/g" \
   | sed "s/pow(M1,4)/(M1*M1*M1*M1)/g" | sed "s/pow(M2,4)/(M2*M2*M2*M2)/g" \
   | sed "s/pow(MZ,4)/(MZ*MZ*MZ*MZ)/g" \
   | sed "s/pow(wZ,4)/(wZ*wZ*wZ*wZ)/g" \
   | sed "s/pow(Mq,4)/(s*s)/g" \
   | sed "s/pow(gqL,4)/(gqL*gqL*gqL*gqL)/g" | sed "s/pow(gqR,4)/(gqR*gqR*gqR*gqR)/g" \
   | sed "s/pow(gL,4)/(gL*gL*gL*gL)/g" | sed "s/pow(gR,4)/(gR*gR*gR*gR)/g" \
   | sed "s/pow(el,4)/(el*el*el*el)/g" \
   | sed "s/pow(eq,4)/(eq*eq*eq*eq)/g" \
   | sed "s/pow(MZ,5)/(MZ*MZ*MZ*MZ*MZ)/g" \
   | sed "s/pow(wZ,5)/(wZ*wZ*wZ*wZ*wZ)/g" \
   | sed "s/pow(gL,5)/(gL*gL*gL*gL*gL)/g" | sed "s/pow(gR,5)/(gR*gR*gR*gR*gR)/g" \
   | sed "s/pow(el,5)/(el*el*el*el*el)/g" \
   | sed "s/pow(eq,5)/(eq*eq*eq*eq*eq)/g" \
   | sed "s/pow(MZ,6)/(MZ*MZ*MZ*MZ*MZ*MZ)/g" \
   | sed "s/pow(gL,6)/(gL*gL*gL*gL*gL*gL)/g" | sed "s/pow(gR,6)/(gR*gR*gR*gR*gR*gR)/g" \
   | sed "s/pow(el,6)/(el*el*el*el*el*el)/g" \
   | sed "s/pow(s,-1)/(1.0\/s)/g" \
   | sed "s/pow(s,-2)/(1.0\/(s*s))/g" \
   | sed "s/pow(M1,-2)/(1.0\/(M1*M1))/g" | sed "s/pow(M2,-2)/(1.0\/(M2*M2))/g" \
   | sed "s/pow(Mq,-2)/(1.0\/s)/g" \
   | sed "s/pow(M1,-4)/(1.0\/(M1*M1*M1*M1))/g" | sed "s/pow(M2,-4)/(1.0\/(M2*M2*M2*M2))/g" \
   | sed "s/pow(Mq,-4)/(1.0\/(s*s))/g" \
   | sed "s/cos(theta1)/X/g" | sed "s/sin(theta1)/sX/g" \
   | sed "s/cos(theta2)/Y/g" | sed "s/sin(theta2)/sY/g" \
   | sed "s/cos(Theta)/Z/g" | sed "s/sin(Theta)/sZ/g" \
   | sed "s/cos(2\*theta1)/X2/g" \
   | sed "s/cos(2\*theta2)/Y2/g" \
   | sed "s/cos(phi)/CosPhi/g" | sed "s/sin(phi)/SinPhi/g" \
   | sed "s/cos(Phi1)/CosPhi1/g" | sed "s/sin(Phi1)/SinPhi1/g" \
   | sed "s/cos(phi + Phi1)/(CosPhi*CosPhi1-SinPhi*SinPhi1)/g" \
   | sed "s/sin(phi + Phi1)/(SinPhi*CosPhi1+SinPhi1*CosPhi)/g" \
   | sed "s/pow(C12,2)/(C12*C12)/g" \
   | sed "s/pow(C13,2)/(C13*C13)/g" \
   | sed "s/pow(C14,2)/(C14*C14)/g" \
   | sed "s/pow(C15,2)/(C15*C15)/g" \
   | sed "s/pow(C16,2)/(C16*C16)/g" \
   | sed "s/pow(C23,2)/(C23*C23)/g" \
   | sed "s/pow(C24,2)/(C24*C24)/g" \
   | sed "s/pow(C25,2)/(C25*C25)/g" \
   | sed "s/pow(C26,2)/(C26*C26)/g" \
   | sed "s/pow(C34,2)/(C34*C34)/g" \
   | sed "s/pow(C35,2)/(C35*C35)/g" \
   | sed "s/pow(C36,2)/(C36*C36)/g" \
   | sed "s/pow(C45,2)/(C45*C45)/g" \
   | sed "s/pow(C46,2)/(C46*C46)/g" \
   | sed "s/pow(C56,2)/(C56*C56)/g" \
   | sed "s/pow(C12,0.5)/SqrtC12/g" \
   | sed "s/pow(C13,0.5)/SqrtC13/g" \
   | sed "s/pow(C14,0.5)/SqrtC14/g" \
   | sed "s/pow(C15,0.5)/SqrtC15/g" \
   | sed "s/pow(C16,0.5)/SqrtC16/g" \
   | sed "s/pow(C23,0.5)/SqrtC23/g" \
   | sed "s/pow(C24,0.5)/SqrtC24/g" \
   | sed "s/pow(C25,0.5)/SqrtC25/g" \
   | sed "s/pow(C26,0.5)/SqrtC26/g" \
   | sed "s/pow(C34,0.5)/SqrtC34/g" \
   | sed "s/pow(C35,0.5)/SqrtC35/g" \
   | sed "s/pow(C36,0.5)/SqrtC36/g" \
   | sed "s/pow(C45,0.5)/SqrtC45/g" \
   | sed "s/pow(C46,0.5)/SqrtC46/g" \
   | sed "s/pow(C56,0.5)/SqrtC56/g" \
   | sed "s/pow(C12,-1)/(1.0\/C12)/g" \
   | sed "s/pow(C13,-1)/(1.0\/C13)/g" \
   | sed "s/pow(C14,-1)/(1.0\/C14)/g" \
   | sed "s/pow(C15,-1)/(1.0\/C15)/g" \
   | sed "s/pow(C16,-1)/(1.0\/C16)/g" \
   | sed "s/pow(C23,-1)/(1.0\/C23)/g" \
   | sed "s/pow(C24,-1)/(1.0\/C24)/g" \
   | sed "s/pow(C25,-1)/(1.0\/C25)/g" \
   | sed "s/pow(C26,-1)/(1.0\/C26)/g" \
   | sed "s/pow(C34,-1)/(1.0\/C34)/g" \
   | sed "s/pow(C35,-1)/(1.0\/C35)/g" \
   | sed "s/pow(C36,-1)/(1.0\/C36)/g" \
   | sed "s/pow(C45,-1)/(1.0\/C45)/g" \
   | sed "s/pow(C46,-1)/(1.0\/C46)/g" \
   | sed "s/pow(C56,-1)/(1.0\/C56)/g" \
   | sed "s/pow(gL + gR,2)/((gL+gR)*(gL+gR))/g" \
   | sed "s/pow(gL - gR,2)/((gL-gR)*(gL-gR))/g" \
   | sed "s/pow(-s + (M2\*M2),2)/((M2*M2-s)*(M2*M2-s))/g" \
   | sed "s/pow(s - (MZ\*MZ),2)/((s-MZ*MZ)*(s-MZ*MZ))/g" \
   | sed "s/pow((M1\*M1) - (M2\*M2),2)/((M1*M1-M2*M2)*(M1*M1-M2*M2))/g" \
   | sed "s/pow((M1\*M1) + (M2\*M2),2)/((M1*M1+M2*M2)*(M1*M1+M2*M2))/g" \
   | sed "s/pow((M1\*M1) - (MZ\*MZ),2)/((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))/g" \
   | sed "s/pow((M2\*M2) - (MZ\*MZ),2)/((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))/g" \
   | sed "s/pow(s - 2\*(C14 + C24),-1)/(1.0\/(s-2*C14-2*C24))/g" \
   | sed "s/pow(s - 2\*(C14 + C24),-2)/(1.0\/(s-2*C14-2*C24)\/(s-2*C14-2*C24))/g" \
   | sed "s/pow(s - 2\*(C16 + C26),-1)/(1.0\/(s-2*C16-2*C26))/g" \
   | sed "s/pow(s - 2\*(C16 + C26),-2)/(1.0\/(s-2*C16-2*C26)\/(s-2*C16-2*C26))/g" \
   | sed "s/pow((M1\*M1) - 2\*(C13 + C14),-1)/(1.0\/(M1*M1-2*C13-2*C14))/g" \
   | sed "s/pow((M1\*M1) - 2\*(C13 + C14),-2)/(1.0\/(M1*M1-2*C13-2*C14)\/(M1*M1-2*C13-2*C14))/g" \
   | sed "s/pow((M1\*M1) + 2\*(C36 + C46),-1)/(1.0\/(M1*M1+2*C36+2*C46))/g" \
   | sed "s/pow((M1\*M1) + 2\*(C36 + C46),-2)/(1.0\/(M1*M1+2*C36+2*C46)\/(M1*M1+2*C36+2*C46))/g" \
   | sed "s/pow((M2\*M2) - 2\*(C15 + C16),-1)/(1.0\/(M2*M2-2*C15-2*C16))/g" \
   | sed "s/pow((M2\*M2) - 2\*(C15 + C16),-2)/(1.0\/(M2*M2-2*C15-2*C16)\/(M2*M2-2*C15-2*C16))/g" \
   | sed "s/pow((M2\*M2) + 2\*(C45 + C46),-1)/(1.0\/(M2*M2+2*C45+2*C46))/g" \
   | sed "s/pow((M2\*M2) + 2\*(C45 + C46),-2)/(1.0\/(M2*M2+2*C45+2*C46)\/(M2*M2+2*C45+2*C46))/g" \
   | sed "s/pow((gL\*gL) + (gR\*gR),2)/((gL*gL+gR*gR)*(gL*gL+gR*gR))/g" \
   | sed "s/pow((gL\*gL) - (gR\*gR),2)/((gL*gL-gR*gR)*(gL*gL-gR*gR))/g" \
   | sed "s/pow((MZ\*MZ)\*(wZ\*wZ) + ((s-MZ\*MZ)\*(s-MZ\*MZ)),-1)/(1.0\/((MZ*MZ)*(wZ*wZ) + ((s-MZ*MZ)*(s-MZ*MZ))))/g" \
   | sed "s/pow((MZ\*MZ)\*(wZ\*wZ) + ((M1\*M1-MZ\*MZ)\*(M1\*M1-MZ\*MZ)),-1)/(1.0\/((MZ*MZ)*(wZ*wZ) + ((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))/g" \
   | sed "s/pow((MZ\*MZ)\*(wZ\*wZ) + ((M2\*M2-MZ\*MZ)\*(M2\*M2-MZ\*MZ)),-1)/(1.0\/((MZ*MZ)*(wZ*wZ) + ((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))/g" \
   | sed "s/pow((gL\*gL\*gL) + (gR\*gR\*gR),2)/((gL*gL*gL+gR*gR*gR)*(gL*gL*gL+gR*gR*gR))/g" \
   | sed "s/pow(gL\*gR + (gL\*gL) + (gR\*gR),2)/((gL*gR+gL*gL+gR*gR)*(gL*gR+gL*gL+gR*gR))/g" \
   | sed "s/Complex/complex<double>/g" \
   | sed "s/pow(aAI,2)/(aAI*aAI)/g" | sed "s/pow(aAR,2)/(aAR*aAR)/g" \
   | sed "s/pow(aAdI,2)/(aAdI*aAdI)/g" | sed "s/pow(aAdR,2)/(aAdR*aAdR)/g" \
   | sed "s/pow(aZAI,2)/(aZAI*aZAI)/g" | sed "s/pow(aZAR,2)/(aZAR*aZAR)/g" \
   | sed "s/pow(aZAdI,2)/(aZAdI*aZAdI)/g" | sed "s/pow(aZAdR,2)/(aZAdR*aZAdR)/g" \
   | sed "s/pow(aZI,2)/(aZI*aZI)/g" | sed "s/pow(aZR,2)/(aZR*aZR)/g" \
   | sed "s/pow(aZdI,2)/(aZdI*aZdI)/g" | sed "s/pow(aZdR,2)/(aZdR*aZdR)/g" \
   | sed "s/pow(ahI,2)/(ahI*ahI)/g" | sed "s/pow(ahR,2)/(ahR*ahR)/g" \
   | sed "s/pow(aZAdR + aZAI,2)/((aZAdR+aZAI)*(aZAdR+aZAI))/g" \
   | sed "s/pow(aZAdR - aZAI,2)/((aZAdR-aZAI)*(aZAdR-aZAI))/g" \
   | sed "s/pow(aZAdI + aZAR,2)/((aZAdI+aZAR)*(aZAdI+aZAR))/g" \
   | sed "s/pow(aZAdI - aZAR,2)/((aZAdI-aZAR)*(aZAdI-aZAR))/g" \
   | sed "s/pow(aZdR + aZI,2)/((aZdR+aZI)*(aZdR+aZI))/g" \
   | sed "s/pow(-aZdR + aZI,2)/((aZdR-aZI)*(aZdR-aZI))/g" \
   | sed "s/pow(aZdI + aZR,2)/((aZdI+aZR)*(aZdI+aZR))/g" \
   | sed "s/pow(-aZdI + aZR,2)/((aZdI-aZR)*(aZdI-aZR))/g" \
   | sed "s/pow(vh,-2)/(1\/(vh*vh))/g" \
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


