#!/bin/sh

for i in crab_[0-9]*.cfg
do
   crab -create -cfg $i
done



