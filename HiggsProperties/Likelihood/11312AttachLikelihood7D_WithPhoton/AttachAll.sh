#!/bin/sh

for i in hzzTree_id100.root
do
   time ./a.out $i All_Scalar.map7 logLikelihood_scalar
   time ./a.out $i All_PseudoScalar.map7 logLikelihood_pseudoscalar
   time ./a.out $i All_Background.map7 logLikelihood_background
done




