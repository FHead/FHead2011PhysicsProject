for i in A B C
do
   CompileRootMacro MakeFigure$i.cpp RunFigure$i
done

CompileRootMacro PrepareFigureC.cpp PrepareFigureC

mkdir -p Plots/
mkdir -p Temp/

./PrepareFigureC SignResult/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
   JobBothS_SMVV_A 1.21
./PrepareFigureC SignResult/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
   JobBothS_SMVV_J 1.16
./PrepareFigureC SignResult/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
   JobBothS_5plet_A 1.10
./PrepareFigureC SignResult/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
   JobBothS_5plet_J 1.05
./PrepareFigureC SignResult/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
   JobBoth_SMVV_A 1.00
./PrepareFigureC SignResult/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
   JobBoth_SMVV_J 0.95
./PrepareFigureC SignResult/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
   JobBoth_5plet_A 0.91
./PrepareFigureC SignResult/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
   JobBoth_5plet_J 0.86
hadd -f FigureCGraphs.root Temp/*root
rm Temp/*root
   
./RunFigureA Result/JobBoth_SMVV_ggPDF_A_ A_SMVV
./RunFigureA Result/JobBoth_SMVV_ggPDF_J_ J_SMVV
./RunFigureA Result/JobBoth_5plet_ggPDF_A_ A_5plet
./RunFigureA Result/JobBoth_5plet_ggPDF_J_ J_5plet
./RunFigureB Result/JobBoth_SMVV_ggPDF_A_ A_SMVV 1
./RunFigureB Result/JobBoth_SMVV_ggPDF_J_ J_SMVV 1
./RunFigureB Result/JobBoth_5plet_ggPDF_A_ A_5plet -0.5
./RunFigureB Result/JobBoth_5plet_ggPDF_J_ J_5plet -0.5
./RunFigureC

cd Plots/
sh ../ListPlot.sh
cd ..

scp Plots/* yichen@positron01.hep.caltech.edu:public_html/15275_GWWPaperPlots/

