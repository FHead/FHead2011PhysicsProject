#!/bin/sh

for i in hzzTree_id1125.root hzzTree_id100.root
do
   time ./a.out $i SignalMaps/All_Scalar logLikelihood_scalar
   time ./a.out $i SignalMaps/All_PseudoScalar logLikelihood_pseudoscalar
   # time ./a.out $i All_Background.map7 logLikelihood_background
done




