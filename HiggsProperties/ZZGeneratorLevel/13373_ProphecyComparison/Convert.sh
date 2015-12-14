for i in *lhe
do
   grep "^ [ ]*[- ]1[13]" $i \
      | awk '{print $1,$7,$8,$9}' \
      | ~/PhysicsWorkspace/HiggsProperties/Utilities/bin/ConvertXYZToVectors \
      | ~/PhysicsWorkspace/HiggsProperties/Utilities/bin/ConvertVectorsToAnglesRoberto \
      | TextToTree ${i/.lhe/.root} 12 "MH:M1:M2:Phi0:Theta0:Phi:Theta1:Theta2:YH:PTH:PhiH:PhiOffset"
done

