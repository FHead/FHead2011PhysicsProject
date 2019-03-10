#!/bin/sh

source Setup_FileLocation.sh

cat Step2PUMatching.sh \
   | sed "s#__PUFILE__#hadd -f -k PUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi1.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi10.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi101.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi102.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi104.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi105.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi106.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi108.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi109.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi110.root#" \
   | sed "s#__NOPUFILE__#hadd -f -k NoPUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi1.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi10.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi101.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi102.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi104.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi105.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi106.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi108.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi109.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi110.root#" \
   | sed "s#__ID__#0#" \
   | sed "s#__WORKDIR__#`pwd`#" \
   | sed "s#__OUTPUT__#$Step2Output#" \
   | bsub -J PUMatching

cat Step2PUMatching.sh \
   | sed "s#__PUFILE__#hadd -f -k PUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi111.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi114.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi117.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi119.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi120.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi121.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi122.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi126.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi127.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi128.root#" \
   | sed "s#__NOPUFILE__#hadd -f -k NoPUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi111.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi114.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi117.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi119.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi120.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi121.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi122.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi126.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi127.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi128.root#" \
   | sed "s#__ID__#1#" \
   | sed "s#__WORKDIR__#`pwd`#" \
   | sed "s#__OUTPUT__#$Step2Output#" \
   | bsub -J PUMatching

cat Step2PUMatching.sh \
   | sed "s#__PUFILE__#hadd -f -k PUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi13.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi134.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi138.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi14.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi142.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi143.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi144.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi145.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi146.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi15.root#" \
   | sed "s#__NOPUFILE__#hadd -f -k NoPUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi13.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi134.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi138.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi14.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi142.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi143.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi144.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi145.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi146.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi15.root#" \
   | sed "s#__ID__#2#" \
   | sed "s#__WORKDIR__#`pwd`#" \
   | sed "s#__OUTPUT__#$Step2Output#" \
   | bsub -J PUMatching

cat Step2PUMatching.sh \
   | sed "s#__PUFILE__#hadd -f -k PUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi150.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi152.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi155.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi156.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi157.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi161.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi162.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi163.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi165.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi167.root#" \
   | sed "s#__NOPUFILE__#hadd -f -k NoPUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi150.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi152.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi155.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi156.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi157.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi161.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi162.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi163.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi165.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi167.root#" \
   | sed "s#__ID__#3#" \
   | sed "s#__WORKDIR__#`pwd`#" \
   | sed "s#__OUTPUT__#$Step2Output#" \
   | bsub -J PUMatching

cat Step2PUMatching.sh \
   | sed "s#__PUFILE__#hadd -f -k PUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi168.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi169.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi173.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi178.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi184.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi185.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi187.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi195.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi197.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi198.root#" \
   | sed "s#__NOPUFILE__#hadd -f -k NoPUFile.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi168.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi169.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi173.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi178.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi184.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi185.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi187.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi195.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi197.root ///eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi198.root#" \
   | sed "s#__ID__#4#" \
   | sed "s#__WORKDIR__#`pwd`#" \
   | sed "s#__OUTPUT__#$Step2Output#" \
   | bsub -J PUMatching

cat Step2PUMatching.sh \
   | sed "s#__PUFILE__#cp /eos/user/c/chenyi/Share/17344_ParallelWorkspace/PUInput/Result_Lumi199.root PUFile.root#" \
   | sed "s#__NOPUFILE__#cp /eos/user/c/chenyi/Share/17344_ParallelWorkspace/NoPUInput/Result_Lumi199.root NoPUFile.root#" \
   | sed "s#__ID__#5#" \
   | sed "s#__WORKDIR__#`pwd`#" \
   | sed "s#__OUTPUT__#$Step2Output#" \
   | bsub -J PUMatching

