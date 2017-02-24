function FCompileAll()
{
   for i in A B BPrime C D E F G I J K L M N O
   do
      CompileRootMacro MakeFigure$i.cpp RunFigure$i
   done

   for i in C E F G GPart2 H L M MPart2
   do
      CompileRootMacro PrepareFigure$i.cpp PrepareFigure$i
   done
}

function FPrepareFigureC()
{
   mkdir -p Plots/
   mkdir -p Temp/
   
   ./PrepareFigureC SignResult/Fix_JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
      JobBothS_SMVV_A 1.21
   ./PrepareFigureC SignResult/Fix_JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
      JobBothS_SMVV_J 1.16
   ./PrepareFigureC SignResult/Fix_JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
      JobBothS_5plet_A 1.10
   ./PrepareFigureC SignResult/Fix_JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
      JobBothS_5plet_J 1.05
   ./PrepareFigureC SignResult/Fix_JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
      JobBoth_SMVV_A 1.00
   ./PrepareFigureC SignResult/Fix_JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
      JobBoth_SMVV_J 0.95
   ./PrepareFigureC SignResult/Fix_JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
      JobBoth_5plet_A 0.91
   ./PrepareFigureC SignResult/Fix_JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
      JobBoth_5plet_J 0.86
   hadd -f FigureCGraphs.root Temp/*root
   rm Temp/*root
}

   
function FPrepareFigureE()
{
   ./PrepareFigureE SignResultYT/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
      JobBothS_SMVV_A 1.21
   ./PrepareFigureE SignResultYT/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
      JobBothS_SMVV_J 1.16
   ./PrepareFigureE SignResultYT/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
      JobBothS_5plet_A 1.10
   ./PrepareFigureE SignResultYT/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
      JobBothS_5plet_J 1.05
   ./PrepareFigureE SignResultYT/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
      JobBoth_SMVV_A 1.00
   ./PrepareFigureE SignResultYT/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
      JobBoth_SMVV_J 0.95
   ./PrepareFigureE SignResultYT/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
      JobBoth_5plet_A 0.91
   ./PrepareFigureE SignResultYT/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
      JobBoth_5plet_J 0.86
   hadd -f FigureEGraphs.root Temp/*root
   rm Temp/*root
}
 
function FPrepareFigureF()
{
   ./PrepareFigureF SignResult/Int_JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
      JobBothS_SMVV_A 1.21
   ./PrepareFigureF SignResult/Int_JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
      JobBothS_SMVV_J 1.16
   ./PrepareFigureF SignResult/Int_JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
      JobBothS_5plet_A 1.10
   ./PrepareFigureF SignResult/Int_JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
      JobBothS_5plet_J 1.05
   ./PrepareFigureF SignResult/Int_JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
      JobBoth_SMVV_A 1.00
   ./PrepareFigureF SignResult/Int_JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
      JobBoth_SMVV_J 0.95
   ./PrepareFigureF SignResult/Int_JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
      JobBoth_5plet_A 0.91
   ./PrepareFigureF SignResult/Int_JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
      JobBoth_5plet_J 0.86
   hadd -f FigureFGraphs.root Temp/*root
   rm Temp/*root
}
   
function FPrepareFigureG()
{
   ./PrepareFigureG SignResultInt/JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
      JobBothS_SMVV_A 1.21
   ./PrepareFigureG SignResultInt/JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
      JobBothS_SMVV_J 1.16
   ./PrepareFigureG SignResultInt/JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
      JobBothS_5plet_A 1.10
   ./PrepareFigureG SignResultInt/JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
      JobBothS_5plet_J 1.05
   ./PrepareFigureG SignResultInt/JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
      JobBoth_SMVV_A 1.00
   ./PrepareFigureG SignResultInt/JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
      JobBoth_SMVV_J 0.95
   ./PrepareFigureG SignResultInt/JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
      JobBoth_5plet_A 0.91
   ./PrepareFigureG SignResultInt/JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
      JobBoth_5plet_J 0.86
   hadd -f FigureGGraphs.root Temp/*root
   rm Temp/*root
}
 
function FPrepareFigureGPart2()
{
   ./PrepareFigureGPart2 SignResult/Int_JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
      JobBothS_SMVV_A 1.21
   ./PrepareFigureGPart2 SignResult/Int_JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
      JobBothS_SMVV_J 1.16
   ./PrepareFigureGPart2 SignResult/Int_JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
      JobBothS_5plet_A 1.10
   ./PrepareFigureGPart2 SignResult/Int_JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
      JobBothS_5plet_J 1.05
   ./PrepareFigureGPart2 SignResult/Int_JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
      JobBoth_SMVV_A 1.00
   ./PrepareFigureGPart2 SignResult/Int_JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
      JobBoth_SMVV_J 0.95
   ./PrepareFigureGPart2 SignResult/Int_JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
      JobBoth_5plet_A 0.91
   ./PrepareFigureGPart2 SignResult/Int_JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
      JobBoth_5plet_J 0.86
   hadd -f FigureGGraphs.root Temp/*root
   rm Temp/*root
}
      
function FPrepareFigureH()
{
   ./PrepareFigureH SignResult/Fix_JobBothS_SMVV_A.root Temp/JobBothS_SMVV_A.root \
      JobBothS_SMVV_A 1.21
   ./PrepareFigureH SignResult/Fix_JobBothS_SMVV_J.root Temp/JobBothS_SMVV_J.root \
      JobBothS_SMVV_J 1.16
   ./PrepareFigureH SignResult/Fix_JobBothS_5plet_A.root Temp/JobBothS_5plet_A.root \
      JobBothS_5plet_A 1.10
   ./PrepareFigureH SignResult/Fix_JobBothS_5plet_J.root Temp/JobBothS_5plet_J.root \
      JobBothS_5plet_J 1.05
   ./PrepareFigureH SignResult/Fix_JobBoth_SMVV_A.root Temp/JobBoth_SMVV_A.root \
      JobBoth_SMVV_A 1.00
   ./PrepareFigureH SignResult/Fix_JobBoth_SMVV_J.root Temp/JobBoth_SMVV_J.root \
      JobBoth_SMVV_J 0.95
   ./PrepareFigureH SignResult/Fix_JobBoth_5plet_A.root Temp/JobBoth_5plet_A.root \
      JobBoth_5plet_A 0.91
   ./PrepareFigureH SignResult/Fix_JobBoth_5plet_J.root Temp/JobBoth_5plet_J.root \
      JobBoth_5plet_J 0.86
   hadd -f FigureHGraphs.root Temp/*root
   rm Temp/*root
}
 
function FPrepareFigureL()
{
   for i in Both BothS
   do
      for j in A J
      do
         for k in Y N
         do
            ./PrepareFigureL \
               SignResult/Hyp_Job${i}_SMVV_${j}.root \
               SignResult/Hyp_Job${i}_5plet_${j}.root \
               Y Temp/${i}_${j}_SM_$k.root ${i}_${j}_SM_${k} $k
            ./PrepareFigureL \
               SignResult/Hyp_Job${i}_5plet_${j}.root \
               SignResult/Hyp_Job${i}_SMVV_${j}.root \
               N Temp/${i}_${j}_5plet_$k.root ${i}_${j}_5plet_${k} $k
         done
      done
   done
   hadd -f FigureLGraphs.root Temp/*root
   rm Temp/*root
}
   
function FPrepareFigureM()
{
   for i in Both BothS
   do
      for j in A J
      do
         for k in Y N
         do
            echo $i $j $k
            # ./PrepareFigureM \
            #    SignResult/Hyp_Job${i}_SMVV_${j}.root \
            #    SignResult/Hyp_Job${i}_5plet_${j}.root \
            #    Temp/Job${i}_${j}_${k}.root \
            #    ${i}_${j}_${k} ${k}
            ./PrepareFigureMPart2 \
               SignResult/Hyp_Job${i}_SMVV_${j}.root \
               SignResult/Hyp_Job${i}_5plet_${j}.root \
               Temp/Job${i}_${j}_${k}.root \
               ${i}_${j}_${k} ${k} ${j}
         done
      done
   done
   hadd -f FigureMGraphs.root Temp/*root
   rm Temp/*root
}
 
function FRunFigureA()
{
   ./RunFigureA Result/JobBoth_SMVV_ggPDF_A_ A_SMVV
   ./RunFigureA Result/JobBoth_SMVV_ggPDF_J_ J_SMVV
   ./RunFigureA Result/JobBoth_5plet_ggPDF_A_ A_5plet
   ./RunFigureA Result/JobBoth_5plet_ggPDF_J_ J_5plet
}

function FRunFigureB()
{
   for i in 0 1 2
   do
      ./RunFigureB Result/JobBoth_SMVV_ggPDF_A_ A_SMVV 1 $i
      ./RunFigureB Result/JobBoth_SMVV_ggPDF_J_ J_SMVV 1 $i
      ./RunFigureB Result/JobBoth_5plet_ggPDF_A_ A_5plet -0.5 $i
      ./RunFigureB Result/JobBoth_5plet_ggPDF_J_ J_5plet -0.5 $i
      ./RunFigureBPrime Result/JobBoth_SMVV_ggPDF_A_ A_SMVV 1 A SMVV $i
      ./RunFigureBPrime Result/JobBoth_SMVV_ggPDF_J_ J_SMVV 1 J SMVV $i
      ./RunFigureBPrime Result/JobBoth_5plet_ggPDF_A_ A_5plet -0.5 A 5plet $i
      ./RunFigureBPrime Result/JobBoth_5plet_ggPDF_J_ J_5plet -0.5 J 5plet $i
   done
}

function FRunFigureC()
{
   ./RunFigureC
}

function FRunFigureD()
{
   for i in `seq 1 20`
   do
      ./RunFigureD `echo $i | MultiplyConst 17`
   done
}

function FRunFigureE()
{
   ./RunFigureE
}

function FRunFigureF()
{
   ./RunFigureF
   ./RunFigureF _Prior
   ./RunFigureF _LoosePrior
}

function FRunFigureG()
{
   ./RunFigureG
   ./RunFigureG _Prior
   ./RunFigureG _LoosePrior
}

function FRunFigureI()
{
   ./RunFigureI
}

function FRunFigureJ()
{
   ./RunFigureJ
}

function FRunFigureK()
{
   ./RunFigureK Y
   ./RunFigureK N
}

function FRunFigureL()
{
   for i in Both BothS
   do
      for j in A J
      do
         for k in Y N
         do
            ./RunFigureL ${i}_${j}_SM_${k} ${i}_${j}_SM_${k}
            ./RunFigureL ${i}_${j}_5plet_${k} ${i}_${j}_5plet_${k}
         done
      done
   done
}

function FRunFigureM()
{
   for i in Both BothS
   do
      for j in A J
      do
         ./RunFigureM ${i}_${j}_Y ${i}_${j}_Y
         ./RunFigureM ${i}_${j}_N ${i}_${j}_N
      done
   done
}

function FRunFigureN()
{
   ./RunFigureN
}

function FRunFigureO()
{
   ./RunFigureO N
   ./RunFigureO Y
}
 
function FUpload()
{
   cd Plots/
   sh ../ListPlot.sh
   cd ..
   
   scp Plots/* yichen@positron01.hep.caltech.edu:public_html/15275_GWWPaperPlots/
}
   
