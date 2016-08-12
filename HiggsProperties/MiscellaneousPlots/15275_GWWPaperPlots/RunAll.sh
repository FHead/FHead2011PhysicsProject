for i in K # A B BPrime C D E F G I J K L M N O
do
   CompileRootMacro MakeFigure$i.cpp RunFigure$i
done

# for i in MPart2 # C E F G GPart2 H L M MPart2
# do
#    CompileRootMacro PrepareFigure$i.cpp PrepareFigure$i
# done

mkdir -p Plots/
mkdir -p Temp/

# ./PrepareFigureC SignResult/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
#    JobBothS_SMVV_A 1.21
# ./PrepareFigureC SignResult/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
#    JobBothS_SMVV_J 1.16
# ./PrepareFigureC SignResult/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
#    JobBothS_5plet_A 1.10
# ./PrepareFigureC SignResult/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
#    JobBothS_5plet_J 1.05
# ./PrepareFigureC SignResult/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
#    JobBoth_SMVV_A 1.00
# ./PrepareFigureC SignResult/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
#    JobBoth_SMVV_J 0.95
# ./PrepareFigureC SignResult/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
#    JobBoth_5plet_A 0.91
# ./PrepareFigureC SignResult/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
#    JobBoth_5plet_J 0.86
# hadd -f FigureCGraphs.root Temp/*root
# rm Temp/*root
   
# ./PrepareFigureE SignResultYT/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
#    JobBothS_SMVV_A 1.21
# ./PrepareFigureE SignResultYT/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
#    JobBothS_SMVV_J 1.16
# ./PrepareFigureE SignResultYT/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
#    JobBothS_5plet_A 1.10
# ./PrepareFigureE SignResultYT/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
#    JobBothS_5plet_J 1.05
# ./PrepareFigureE SignResultYT/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
#    JobBoth_SMVV_A 1.00
# ./PrepareFigureE SignResultYT/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
#    JobBoth_SMVV_J 0.95
# ./PrepareFigureE SignResultYT/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
#    JobBoth_5plet_A 0.91
# ./PrepareFigureE SignResultYT/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
#    JobBoth_5plet_J 0.86
# hadd -f FigureEGraphs.root Temp/*root
# rm Temp/*root
   
# ./PrepareFigureF SignResultInt/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
#    JobBothS_SMVV_A 1.21
# ./PrepareFigureF SignResultInt/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
#    JobBothS_SMVV_J 1.16
# ./PrepareFigureF SignResultInt/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
#    JobBothS_5plet_A 1.10
# ./PrepareFigureF SignResultInt/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
#    JobBothS_5plet_J 1.05
# ./PrepareFigureF SignResultInt/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
#    JobBoth_SMVV_A 1.00
# ./PrepareFigureF SignResultInt/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
#    JobBoth_SMVV_J 0.95
# ./PrepareFigureF SignResultInt/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
#    JobBoth_5plet_A 0.91
# ./PrepareFigureF SignResultInt/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
#    JobBoth_5plet_J 0.86
# hadd -f FigureFGraphs.root Temp/*root
# rm Temp/*root

# ./PrepareFigureG SignResultInt/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
#    JobBothS_SMVV_A 1.21
# ./PrepareFigureG SignResultInt/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
#    JobBothS_SMVV_J 1.16
# ./PrepareFigureG SignResultInt/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
#    JobBothS_5plet_A 1.10
# ./PrepareFigureG SignResultInt/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
#    JobBothS_5plet_J 1.05
# ./PrepareFigureG SignResultInt/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
#    JobBoth_SMVV_A 1.00
# ./PrepareFigureG SignResultInt/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
#    JobBoth_SMVV_J 0.95
# ./PrepareFigureG SignResultInt/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
#    JobBoth_5plet_A 0.91
# ./PrepareFigureG SignResultInt/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
#    JobBoth_5plet_J 0.86
# hadd -f FigureGGraphs.root Temp/*root
# rm Temp/*root
   
# ./PrepareFigureGPart2 SignResultInt/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
#    JobBothS_SMVV_A 1.21
# ./PrepareFigureGPart2 SignResultInt/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
#    JobBothS_SMVV_J 1.16
# ./PrepareFigureGPart2 SignResultInt/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
#    JobBothS_5plet_A 1.10
# ./PrepareFigureGPart2 SignResultInt/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
#    JobBothS_5plet_J 1.05
# ./PrepareFigureGPart2 SignResultInt/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
#    JobBoth_SMVV_A 1.00
# ./PrepareFigureGPart2 SignResultInt/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
#    JobBoth_SMVV_J 0.95
# ./PrepareFigureGPart2 SignResultInt/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
#    JobBoth_5plet_A 0.91
# ./PrepareFigureGPart2 SignResultInt/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
#    JobBoth_5plet_J 0.86
# hadd -f FigureGGraphs.root Temp/*root
# rm Temp/*root
   
# ./PrepareFigureH SignResult/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
#    JobBothS_SMVV_A 1.21
# ./PrepareFigureH SignResult/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
#    JobBothS_SMVV_J 1.16
# ./PrepareFigureH SignResult/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
#    JobBothS_5plet_A 1.10
# ./PrepareFigureH SignResult/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
#    JobBothS_5plet_J 1.05
# ./PrepareFigureH SignResult/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
#    JobBoth_SMVV_A 1.00
# ./PrepareFigureH SignResult/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
#    JobBoth_SMVV_J 0.95
# ./PrepareFigureH SignResult/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
#    JobBoth_5plet_A 0.91
# ./PrepareFigureH SignResult/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
#    JobBoth_5plet_J 0.86
# hadd -f FigureHGraphs.root Temp/*root
# rm Temp/*root

# for i in Both BothS
# do
#    for j in A J
#    do
#       for k in Y N
#       do
#          ./PrepareFigureL \
#             HypothesisTestingResult/Job${i}_SMVV_${j}.root \
#             HypothesisTestingResult/Job${i}_5plet_${j}.root \
#             Y Temp/${i}_${j}_SM_$k.root ${i}_${j}_SM_${k} $k
#          ./PrepareFigureL \
#             HypothesisTestingResult/Job${i}_5plet_${j}.root \
#             HypothesisTestingResult/Job${i}_SMVV_${j}.root \
#             N Temp/${i}_${j}_5plet_$k.root ${i}_${j}_5plet_${k} $k
#       done
#    done
# done
# hadd -f FigureLGraphs.root Temp/*root
# rm Temp/*root

# for i in Both BothS
# do
#    for j in A J
#    do
#       for k in Y N
#       do
#          echo $i $j $k
#          # ./PrepareFigureM \
#          #    HypothesisTestingResult/Job${i}_SMVV_${j}.root \
#          #    HypothesisTestingResult/Job${i}_5plet_${j}.root \
#          #    Temp/Job${i}_${j}_${k}.root \
#          #    ${i}_${j}_${k} ${k}
#          ./PrepareFigureMPart2 \
#             HypothesisTestingResult/Job${i}_SMVV_${j}.root \
#             HypothesisTestingResult/Job${i}_5plet_${j}.root \
#             Temp/Job${i}_${j}_${k}.root \
#             ${i}_${j}_${k} ${k}
#       done
#    done
# done
# hadd -f FigureMGraphs.root Temp/*root
# rm Temp/*root

# ./RunFigureA Result/JobBoth_SMVV_ggPDF_A_ A_SMVV
# ./RunFigureA Result/JobBoth_SMVV_ggPDF_J_ J_SMVV
# ./RunFigureA Result/JobBoth_5plet_ggPDF_A_ A_5plet
# ./RunFigureA Result/JobBoth_5plet_ggPDF_J_ J_5plet
# for i in 0 1 2
# do
#    ./RunFigureB Result/JobBoth_SMVV_ggPDF_A_ A_SMVV 1 $i
#    ./RunFigureB Result/JobBoth_SMVV_ggPDF_J_ J_SMVV 1 $i
#    ./RunFigureB Result/JobBoth_5plet_ggPDF_A_ A_5plet -0.5 $i
#    ./RunFigureB Result/JobBoth_5plet_ggPDF_J_ J_5plet -0.5 $i
#    ./RunFigureBPrime Result/JobBoth_SMVV_ggPDF_A_ A_SMVV 1 A SMVV $i
#    ./RunFigureBPrime Result/JobBoth_SMVV_ggPDF_J_ J_SMVV 1 J SMVV $i
#    ./RunFigureBPrime Result/JobBoth_5plet_ggPDF_A_ A_5plet -0.5 A 5plet $i
#    ./RunFigureBPrime Result/JobBoth_5plet_ggPDF_J_ J_5plet -0.5 J 5plet $i
# done
# ./RunFigureC
# for i in `seq 1 20`
# do
#    ./RunFigureD `echo $i | MultiplyConst 17`
# done
# ./RunFigureE
# ./RunFigureF
# ./RunFigureF _Prior
# ./RunFigureF _LoosePrior
# ./RunFigureG
# ./RunFigureG _Prior
# ./RunFigureG _LoosePrior
# ./RunFigureI
# ./RunFigureJ
./RunFigureK Y
./RunFigureK N
# for i in Both BothS
# do
#    for j in A J
#    do
#       for k in Y N
#       do
#          ./RunFigureL ${i}_${j}_SM_${k} ${i}_${j}_SM_${k}
#          ./RunFigureL ${i}_${j}_5plet_${k} ${i}_${j}_5plet_${k}
#       done
#    done
# done
# for i in Both BothS
# do
#    for j in A J
#    do
#       ./RunFigureM ${i}_${j}_Y ${i}_${j}_Y
#       ./RunFigureM ${i}_${j}_N ${i}_${j}_N
#    done
# done
# ./RunFigureN
# ./RunFigureO

cd Plots/
sh ../ListPlot.sh
cd ..

scp Plots/* yichen@positron01.hep.caltech.edu:public_html/15275_GWWPaperPlots/

