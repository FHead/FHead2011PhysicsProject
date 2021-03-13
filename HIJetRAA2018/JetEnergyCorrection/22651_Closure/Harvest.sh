Year=$1

mkdir -p Files${Year}

jet_draw_closure_x \
   -doPt true \
   -doEta true \
   -path ./ \
   -filename Closure${Year} \
   -histMet median \
   -outputDir Files${Year}/ \
   -outputFormat .pdf \
   -draw_guidelines true \
   -doRatioPt false \
   -doRatioEta false
