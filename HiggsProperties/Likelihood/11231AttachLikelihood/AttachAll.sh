#!/bin/sh

time ./a.out HZZEventNtuple_HZZ125.root All_Scalar.map logLikelihood_scalar_125
time ./a.out HZZEventNtuple_HZZ125.root All_PseudoScalar.map logLikelihood_pseudoscalar_125
time ./a.out HZZEventNtuple_HZZ125_FastSimFromHist.root All_Scalar.map logLikelihood_scalar_125
time ./a.out HZZEventNtuple_HZZ125_FastSimFromHist.root All_PseudoScalar.map logLikelihood_pseudoscalar_125
time ./a.out HZZEventNtuple_ZZ.root All_Scalar.map logLikelihood_scalar_125
time ./a.out HZZEventNtuple_ZZ.root All_PseudoScalar.map logLikelihood_pseudoscalar_125
time ./a.out HZZEventNtuple_ZZ_FastSimFromHist.root All_Scalar.map logLikelihood_scalar_125
time ./a.out HZZEventNtuple_ZZ_FastSimFromHist.root All_PseudoScalar.map logLikelihood_pseudoscalar_125




