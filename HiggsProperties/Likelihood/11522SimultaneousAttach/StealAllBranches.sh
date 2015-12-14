cp HZZ4l_Prophecy4f_125_100K_tree_11521_Backup.root HZZ4l_Prophecy4f_125_100K_tree_11521.root

for i in EffMEE ExtSig1 ExtSig2 ExtSig3 ExtSig4 ExtSig5 \
   ExtSig12 ExtSig13 ExtSig14 ExtSig15 ExtSig23 ExtSig24 ExtSig25 ExtSig34 ExtSig35 ExtSig45
do
   ./a.out BatchResult/HZZ4l_Prophecy4f_125_100K_tree_11521_$i.root zz4lTree/probe_tree HZZ4l_Prophecy4f_125_100K_tree_11521.root zz4lTree zz4lTree/probe_tree Likelihood_$i
   ./a.out BatchResult/HZZ4l_Prophecy4f_125_100K_tree_11521_$i.root zz4lTree/probe_tree HZZ4l_Prophecy4f_125_100K_tree_11521.root zz4lTree zz4lTree/probe_tree Likelihood_${i}_Integral
   ./a.out BatchResult/HZZ4l_Prophecy4f_125_100K_tree_11521_$i.root zz4lTree/probe_tree HZZ4l_Prophecy4f_125_100K_tree_11521.root zz4lTree zz4lTree/probe_tree LikelihoodUp_$i
   ./a.out BatchResult/HZZ4l_Prophecy4f_125_100K_tree_11521_$i.root zz4lTree/probe_tree HZZ4l_Prophecy4f_125_100K_tree_11521.root zz4lTree zz4lTree/probe_tree LikelihoodUp_${i}_Integral
   ./a.out BatchResult/HZZ4l_Prophecy4f_125_100K_tree_11521_$i.root zz4lTree/probe_tree HZZ4l_Prophecy4f_125_100K_tree_11521.root zz4lTree zz4lTree/probe_tree LikelihoodDown_$i
   ./a.out BatchResult/HZZ4l_Prophecy4f_125_100K_tree_11521_$i.root zz4lTree/probe_tree HZZ4l_Prophecy4f_125_100K_tree_11521.root zz4lTree zz4lTree/probe_tree LikelihoodDown_${i}_Integral
done
