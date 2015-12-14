(echo "Hello,"; \
   echo "Final matrix with partial statistics is attached."; \
   echo "Since I don't have computer I'm sending this from command line."; \
   echo ""; \
   echo "Best,"; \
   echo "Yi Chen"; \
   uuencode FinalMatrixPlots.pdf FinalMatrixPlots.pdf && \
   uuencode PartialCrossSectionResultEELoose.pdf PartialCrossSectionResultEELoose.pdf && \
   uuencode PartialCrossSectionResultEETight.pdf PartialCrossSectionResultEETight.pdf && \
   uuencode PartialCrossSectionResultEEOpt.pdf PartialCrossSectionResultEEOpt.pdf && \
   uuencode PartialCrossSectionResultEMLoose.pdf PartialCrossSectionResultEMLoose.pdf && \
   uuencode PartialCrossSectionResultEMTight.pdf PartialCrossSectionResultEMTight.pdf && \
   uuencode PartialCrossSectionResultEMOpt.pdf PartialCrossSectionResultEMOpt.pdf) | \
   mail -s "Final matrix" chen.yi.first@gmail.com




