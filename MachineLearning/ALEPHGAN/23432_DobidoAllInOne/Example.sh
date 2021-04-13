#!/bin/sh

BaseInput=$1
VariantInput=$2

# Convert to ALEPH-like tree.  DoCharge = false => 4-tuple px,py,pz,m.  true => 5-tuple px,py,pz,m,q
./ExecuteConversion \
   --Input $BaseInput \
   --Output ${BaseInput/csv/root} \
   --DoCharge true
./ExecuteConversion \
   --Input $VariantInput \
   --Output ${VariantInput/csv/root} \
   --DoCharge true

# Cluster jets
./ExecuteJetClustering \
   --Input ${BaseInput/csv/root} \
   --Output Jet_${BaseInput/csv/root}
./ExecuteJetClustering \
   --Input ${VariantInput/csv/root} \
   --Output Jet_${VariantInput/csv/root}

# Make comparison plots
./ExecuteBasicPlots \
   --Base ${BaseInput/csv/root} \
   --Variant ${VariantInput/csv/root} \
   --Output Plots_${VariantInput/csv/pdf}
./ExecuteJetPlots \
   --Base Jet_${BaseInput/csv/root} \
   --Variant Jet_${VariantInput/csv/root} \
   --Output JetPlots_${VariantInput/csv/pdf}
