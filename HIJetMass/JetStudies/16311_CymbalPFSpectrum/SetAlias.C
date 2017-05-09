{
   T2->SetAlias("TargetRMS", "(-7.449+exp(3.206-0.01377*(Centrality+1))+exp(-6.072+0.06855*(Centrality+1)))");
   T2->SetAlias("SourceRMS", "(-0.4159+exp(0.7852-0.5525*Centrality)+exp(3.238-0.03464*Centrality))");
   T2->SetAlias("ExcessPT", "(TotalPTInJet-0.4*0.4*3.1415926535*Rho)");
   T2->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT/(2*TargetRMS*TargetRMS)) / exp(-ExcessPT*ExcessPT/(2*SourceRMS*SourceRMS)))");
}
