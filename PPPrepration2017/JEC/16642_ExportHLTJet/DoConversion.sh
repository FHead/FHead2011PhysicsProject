grep JETEXPORTER LSFJOB*/STDOUT | grep PFJets | cut --delim=' ' --field=3- | ./a.out PFJets.root
grep JETEXPORTER LSFJOB*/STDOUT | grep PFRawJets | cut --delim=' ' --field=3- | ./a.out PFRawJets.root

