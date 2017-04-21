void run(string FileBase)
{
   gROOT->ProcessLine(".x init.C");

   L1UpgradeNtuple X(FileBase);
   X.testPerformance();
}
