#!/bin/sh

grep MassScanResult SubmitDirectory/LSFJOB*/STDOUT | cut --delim=' ' --field=2- > Result.txt




