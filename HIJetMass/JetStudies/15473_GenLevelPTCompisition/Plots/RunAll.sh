#!/bin/sh

hadd -f -k AA6Dijet.root Result/AA6Dijet*.root
hadd -f -k AA8Dijet.root Result/AA8Dijet*.root

./a.out AA6Dijet.root AA6Dijet
./a.out AA8Dijet.root AA8Dijet
