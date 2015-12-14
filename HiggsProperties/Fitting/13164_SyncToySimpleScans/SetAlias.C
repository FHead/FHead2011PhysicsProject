{
   ResultTree->SetAlias("SA1L1ZZ", "(A1L1ZZ*A1L1ZZ/0.0001204601/0.0001204601)");
   ResultTree->SetAlias("FL1", "SA1L1ZZ/(1+SA1L1ZZ)*((A1L1ZZ>0)-(A1L1ZZ<0))");
   
   ResultTree->SetAlias("SA2ZA", "(A2ZA*A2ZA/0.1/0.1)");
   ResultTree->SetAlias("FA2ZA", "SA2ZA/(1+SA2ZA)*((A2ZA>0)-(A2ZA<0))");
   ResultTree->SetAlias("SA3ZA", "(A3ZA*A3ZA/0.11/0.11)");
   ResultTree->SetAlias("FA3ZA", "SA3ZA/(1+SA3ZA)*((A3ZA>0)-(A3ZA<0))");
   ResultTree->SetAlias("SA2AA", "(A2AA*A2AA/0.108/0.108)");
   ResultTree->SetAlias("FA2AA", "SA2AA/(1+SA2AA)*((A2AA>0)-(A2AA<0))");
   ResultTree->SetAlias("SA3AA", "(A3AA*A3AA/0.109/0.109)");
   ResultTree->SetAlias("FA3AA", "SA3AA/(1+SA3AA)*((A3AA>0)-(A3AA<0))");
}
