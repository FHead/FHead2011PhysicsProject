#!/bin/bash

for i in */
do
   echo $i
   j=`echo $i | tr -d '/'`
   (cd $i && git remote set-url origin git@github.com:FHead/Physics${j}.git)
done

# Ugh...typo...
(cd L1TriggerUpgrade && git remote set-url origin git@github.com:FHead/PhysicsL1TriggerUpdate.git)
(cd L1TriggerUpgrade2018 && git remote set-url origin git@github.com:FHead/PhysicsL1TriggerUpdate2018.git)
(cd PPPrepration2017 && git remote set-url origin git@github.com:FHead/PhysicsPPPreparation2017.git)
