
---+ Quick start

Example usage:

```bash
make
bash Example.sh charged_dobido10meow.csv charged_dobido10meow_test_GAN.csv
```

The first argument is the base file, and the second one is the GAN output.


---+ Under the hood:

There are four executables

---++ ExecuteConversion

This one turns csv into root tree, in an ALEPH-like format

---++ ExeucteJetClustering

This one takes the particle tree from the previous step and calculate jets

---++ ExecuteBasicPlots

This one makes basic plots for particles (and D candidates)

---++ ExecuteJetPlost

This one runs on the jet tree and make jet comparison plots



