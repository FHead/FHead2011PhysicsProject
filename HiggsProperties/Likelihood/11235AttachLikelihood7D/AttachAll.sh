#!/bin/sh

time ./a.out HZZEventNtuple_HZZ125.root All_Scalar.map7 logLikelihood_scalar
time ./a.out HZZEventNtuple_HZZ125.root All_PseudoScalar.map7 logLikelihood_pseudoscalar
time ./a.out HZZEventNtuple_HZZ125.root All_ZZ.map7 logLikelihood_zz
time ./a.out HZZEventNtuple_HZZ125.root All_ZA.map7 logLikelihood_za
time ./a.out HZZEventNtuple_HZZ125_FastSimFromHist.root All_Scalar.map7 logLikelihood_scalar
time ./a.out HZZEventNtuple_HZZ125_FastSimFromHist.root All_PseudoScalar.map7 logLikelihood_pseudoscalar
time ./a.out HZZEventNtuple_HZZ125_FastSimFromHist.root All_ZZ.map7 logLikelihood_zz
time ./a.out HZZEventNtuple_HZZ125_FastSimFromHist.root All_ZA.map7 logLikelihood_za
time ./a.out HZZEventNtuple_ZZ.root All_Scalar.map7 logLikelihood_scalar
time ./a.out HZZEventNtuple_ZZ.root All_PseudoScalar.map7 logLikelihood_pseudoscalar
time ./a.out HZZEventNtuple_ZZ.root All_ZZ.map7 logLikelihood_zz
time ./a.out HZZEventNtuple_ZZ.root All_ZA.map7 logLikelihood_za
time ./a.out HZZEventNtuple_ZZ_FastSimFromHist.root All_Scalar.map7 logLikelihood_scalar
time ./a.out HZZEventNtuple_ZZ_FastSimFromHist.root All_PseudoScalar.map7 logLikelihood_pseudoscalar
time ./a.out HZZEventNtuple_ZZ_FastSimFromHist.root All_ZZ.map7 logLikelihood_zz
time ./a.out HZZEventNtuple_ZZ_FastSimFromHist.root All_ZA.map7 logLikelihood_za




