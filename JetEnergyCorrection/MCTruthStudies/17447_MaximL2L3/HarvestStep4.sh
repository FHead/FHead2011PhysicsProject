#!/bin/bash

source Setup_FileLocation.sh

hadd -k -f $Step4Output/Merged.root $Step4Output/Closure_*root

jet_draw_closure_x \
   -doPt true \
   -doEta true \
   -path $Step4Output/ \
   -filename Merged \
   -histMet median \
   -outputDir Files/ \
   -outputFormat .pdf \
   -draw_guidelines true \
   -algs ak4pfchs \
   -doRatioPt false \
   -doRatioEta false


