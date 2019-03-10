
JRATemplate=run_JRA_cfg.py
NoPUFile=InputTrees/NoPU/JME-RunIIAutumn18DR-00002.root
WithPUFileBase=InputTrees/FlatPU/
MinID=$1
MaxID=$2

function RunJRA
{
   [ -f "$1" ] || return
   [ ! -f "$2" ] || return
   sed "s#__FILE__#$1#g" < $JRATemplate > Temp.py
   cmsRun Temp.py
   rm Temp.py
   mv JRA.root $2
}

function RunJRANoPU
{
   RunJRA "$NoPUFile" "Output/JRANoPU/JRA.root"
}

function RunJRAWithPU
{
   for i in `seq $MinID $MaxID`
   do
      RunJRA "$WithPUFileBase/Run$i/JME-RunIIAutumn18DR-00003.root" "Output/JRAFlatPU/JRA_${i}.root"
   done
}

function RunSynchTree
{
   for i in `seq $MinID $MaxID`
   do
      [ -f Output/JRAFlatPU/JRA_${i}.root ] || continue
      [ -f Output/JRANoPU/JRA.root ] || continue
      [ ! -f Output/SynchTree/SynchTree_${i}.root ] || continue

      jet_synchtree_x \
         -basepath '//' \
         -samplePU `pwd`/Output/JRAFlatPU/JRA_${i}.root \
         -sampleNoPU `pwd`/Output/JRANoPU/JRA.root \
         -algo1 ak4pf \
         -algo2 ak4pf \
         -iftest false \
         -maxEvts 10000000 \
         -ApplyJEC false \
         -outputPath `pwd`/Output/SynchTree/ \
         -npvRhoNpuBinWidth 10 \
         -NBinsNpvRhoNpu 6 \
         -useweight true \
         -nrefmax 3 \
         -doNotSave true

      mv `pwd`/Output/SynchTree/output_ak4pf.root `pwd`/Output/SynchTree/SynchTree_${i}.root
   done
}

function MergeResult
{
   hadd -f Output/SynchTree/All.root Output/SynchTree/SynchTree*
}

# RunJRANoPU
RunJRAWithPU
RunSynchTree
MergeResult
