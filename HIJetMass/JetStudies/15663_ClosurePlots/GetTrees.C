{
   gROOT->LoadMacro("~/RootMacros/SetStyle.h");
   SetThesisStyleNoPalette();

   gROOT->LoadMacro("Functions.C");

   TFile F1("Straight/AA6Dijet.root");
   TFile F2("Straight/AA8Dijet.root");
   // TFile F3("Straight/AA6DijetNo80.root");
   TFile F4("Straight/PP6Dijet.root");
   TFile F5("Straight/PP8Dijet.root");
   TFile F6("ScaledResult1/PP6Dijet.root");
   TFile F7("ScaledResult1/PP8Dijet.root");
   TFile F8("ScaledResult13/PP6Dijet.root");
   TFile F9("ScaledResult13/PP8Dijet.root");
   TFile F10("ScaledResult17/PP6Dijet.root");
   TFile F11("ScaledResult17/PP8Dijet.root");
   TFile F12("ScaledResult18/PP6Dijet.root");
   TFile F13("ScaledResult18/PP8Dijet.root");
   TFile F14("Straight/PPDataHighPTJet_NoCrossSection.root");
   TFile F15("Straight/AAData_NoCrossSection.root");
   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");
   // TTree *T3 = (TTree *)F3.Get("Tree");
   TTree *T4 = (TTree *)F4.Get("Tree");
   TTree *T5 = (TTree *)F5.Get("Tree");
   TTree *T6 = (TTree *)F6.Get("OutputTree");
   TTree *T7 = (TTree *)F7.Get("OutputTree");
   TTree *T8 = (TTree *)F8.Get("OutputTree");
   TTree *T9 = (TTree *)F9.Get("OutputTree");
   TTree *T10 = (TTree *)F10.Get("OutputTree");
   TTree *T11 = (TTree *)F11.Get("OutputTree");
   TTree *T12 = (TTree *)F12.Get("OutputTree");
   TTree *T13 = (TTree *)F13.Get("OutputTree");
   TTree *T14 = (TTree *)F14.Get("Tree");
   TTree *T15 = (TTree *)F15.Get("Tree");

   if(T2)   T2->SetAlias("PTWeight10000", "(0.733067+exp(-0.143422-0.00839608*JetPT))");

   if(T1)   T1->SetAlias("PTWeightToAAData", "(1/(1.01000-exp(11.4934-0.103388*JetPT)))");
   if(T2)   T2->SetAlias("PTWeightToAAData", "(1/(1.11170-exp(1.91036-0.0250308*JetPT)))");
   if(T4)   T4->SetAlias("PTWeightToPPData", "(1/(1.06469-exp(5.61511-0.0524620*JetPT)))");
   if(T5)   T5->SetAlias("PTWeightToPPData", "(1/(1.26582-exp(2.04079-0.0203018*JetPT)))");

   if(T1)   T1->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   if(T1)   T1->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   if(T1)   T1->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   if(T1)   T1->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");

   if(T1)   T1->SetAlias("C0", "(Centrality < 0.1)");
   if(T1)   T1->SetAlias("C1", "(Centrality < 0.3 && Centrality >= 0.1)");
   if(T1)   T1->SetAlias("C2", "(Centrality < 0.5 && Centrality >= 0.3)");
   if(T1)   T1->SetAlias("C3", "(Centrality < 0.8 && Centrality >= 0.5)");
   if(T1)   T1->SetAlias("C4", "(Centrality < 1.0 && Centrality >= 0.8)");
   if(T2)   T2->SetAlias("C0", "(Centrality < 0.1)");
   if(T2)   T2->SetAlias("C1", "(Centrality < 0.3 && Centrality >= 0.1)");
   if(T2)   T2->SetAlias("C2", "(Centrality < 0.5 && Centrality >= 0.3)");
   if(T2)   T2->SetAlias("C3", "(Centrality < 0.8 && Centrality >= 0.5)");
   if(T2)   T2->SetAlias("C4", "(Centrality < 1.0 && Centrality >= 0.8)");
   if(T15)  T15->SetAlias("C0", "(Centrality < 0.1)");
   if(T15)  T15->SetAlias("C1", "(Centrality < 0.3 && Centrality >= 0.1)");
   if(T15)  T15->SetAlias("C2", "(Centrality < 0.5 && Centrality >= 0.3)");
   if(T15)  T15->SetAlias("C3", "(Centrality < 0.8 && Centrality >= 0.5)");
   if(T15)  T15->SetAlias("C4", "(Centrality < 1.0 && Centrality >= 0.8)");

   if(T6)   T6->SetAlias("ExcessPT", "((TotalPT-0.8*0.8*3.1415926535*Rho)*0.25)");
   if(T6)   T6->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*21.4*21.4)))");
   if(T6)   T6->SetAlias("SmearWeightV2Positive", "(12891000*exp(-0.5*((ExcessPT+0.236714)/27.4658)**2))");
   if(T6)   T6->SetAlias("SmearWeightV2Negative", "(exp(15.5537+0.322953*ExcessPT)+9063180*exp(-0.5*((ExcessPT+2.73170)/14.3526)**2))");
   if(T6)   T6->SetAlias("SmearWeightV2", "(exp(-ExcessPT*ExcessPT/(2*18*18))/(((ExcessPT>0)*SmearWeightV2Positive)+((ExcessPT<0)*SmearWeightV2Negative)))");
   if(T6)   T6->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   if(T6)   T6->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   if(T6)   T6->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   if(T6)   T6->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   if(T6)   T6->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   if(T6)   T6->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   if(T6)   T6->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   if(T6)   T6->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
    
   if(T8)   T8->SetAlias("ExcessPT", "((TotalPT-1.2*1.2*3.1415926535*Rho)/9)");
   if(T8)   T8->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*21.4*21.4)))");
   if(T8)   T8->SetAlias("SmearWeightV2Positive", "(12891000*exp(-0.5*((ExcessPT+0.236714)/27.4658)**2))");
   if(T8)   T8->SetAlias("SmearWeightV2Negative", "(exp(15.5537+0.322953*ExcessPT)+9063180*exp(-0.5*((ExcessPT+2.73170)/14.3526)**2))");
   if(T8)   T8->SetAlias("SmearWeightV2", "(exp(-ExcessPT*ExcessPT/(2*18*18))/(((ExcessPT>0)*SmearWeightV2Positive)+((ExcessPT<0)*SmearWeightV2Negative)))");
   if(T8)   T8->SetAlias("SmearWeightV3", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*27.3*27.3)))");
   if(T8)   T8->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   if(T8)   T8->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   if(T8)   T8->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   if(T8)   T8->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   if(T8)   T8->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   if(T8)   T8->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   if(T8)   T8->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   if(T8)   T8->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
      
   if(T10)  T10->SetAlias("ExcessPT", "((TotalPT-1.6*1.6*3.1415926535*Rho)/16)");
   if(T10)  T10->SetAlias("AdjustedExcessPT", "(ExcessPT*(ExcessPT>0)+ExcessPT*16*(ExcessPT<0))");
   if(T10)  T10->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*21.4*21.4)))");
   if(T10)  T10->SetAlias("SmearWeightV2Positive", "(12891000*exp(-0.5*((ExcessPT+0.236714)/27.4658)**2))");
   if(T10)  T10->SetAlias("SmearWeightV2Negative", "(exp(15.5537+0.322953*ExcessPT)+9063180*exp(-0.5*((ExcessPT+2.73170)/14.3526)**2))");
   if(T10)  T10->SetAlias("SmearWeightV2", "(exp(-ExcessPT*ExcessPT/(2*18*18))/(((ExcessPT>0)*SmearWeightV2Positive)+((ExcessPT<0)*SmearWeightV2Negative)))");
   if(T10)  T10->SetAlias("SmearWeightV3", "(exp(-ExcessPT*ExcessPT / (2*17.2*17.2)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   if(T10)  T10->SetAlias("SmearWeightV4", "(exp(-ExcessPT*ExcessPT / (2*12.8*12.8)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   if(T10)  T10->SetAlias("SmearWeightV5", "(exp(-ExcessPT*ExcessPT / (2*7.5*7.5)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   if(T10)  T10->SetAlias("SmearWeightV6", "(exp(-ExcessPT*ExcessPT / (2*3.1*3.1)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   if(T10)  T10->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   if(T10)  T10->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   if(T10)  T10->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   if(T10)  T10->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   if(T10)  T10->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   if(T10)  T10->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   if(T10)  T10->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   if(T10)  T10->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
   if(T10)  T10->SetAlias("PTWeightToEmbedded", "(0.929846+exp(9.16730-0.0754417*NewJetPT))");
   if(T10)  T10->SetAlias("JetShiftWeight", "(exp(-JetShift*JetShift/(2*0.1*0.1)))");
   if(T10)  T10->SetAlias("SmearWeightInJet", "(exp(-ExcessPT*ExcessPT / (2*15.2*15.2)) / exp(-ExcessPT*ExcessPT / (2*31.13*31.13)))");
   if(T10)  T10->SetAlias("SmearWeightAdjusted", "(((AdjustedExcessPT>0)+16*(AdjustedExcessPT<0)*(exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35))/exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35*16*16))))*(exp(-AdjustedExcessPT*AdjustedExcessPT/(2*17.2*17.2))/exp(-AdjustedExcessPT*AdjustedExcessPT/(2*27.35*27.35))))");
   if(T10)  T10->SetAlias("JetPTWeight", "(1 / (0.526940+0.475752*erf(0.0379893*(JetPT-95.6267))))");
   if(T10)  T10->SetAlias("SmearWeightAdjusted2", "(((AdjustedExcessPT>0)+16*(AdjustedExcessPT<0)*(exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35))/exp(-AdjustedExcessPT*AdjustedExcessPT/2/(27.35*27.35*16*16))))*(exp(-AdjustedExcessPT*AdjustedExcessPT/(2*12.2*12.2))/exp(-AdjustedExcessPT*AdjustedExcessPT/(2*27.35*27.35))))");
   if(T10)  T10->SetAlias("JetPTWeight2", "(1 / (0.126940+0.875752*erf(0.0379893*(JetPT-95.6267))))");
   if(T10)  T10->SetAlias("ExcessPTExtraWeight", "(exp(-(AdjustedExcessPT*AdjustedExcessPT)/(2*17.2*17.2))/(exp(-(AdjustedExcessPT-11.5)*(AdjustedExcessPT-11.5)/(2*17*17))))");
     
   if(T12)  T12->SetAlias("ExcessPT", "((TotalPT-2.0*2.0*3.1415926535*Rho)/25)");
   if(T12)  T12->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*21.4*21.4)))");
   if(T12)  T12->SetAlias("SmearWeightV2Positive", "(12891000*exp(-0.5*((ExcessPT+0.236714)/27.4658)**2))");
   if(T12)  T12->SetAlias("SmearWeightV2Negative", "(exp(15.5537+0.322953*ExcessPT)+9063180*exp(-0.5*((ExcessPT+2.73170)/14.3526)**2))");
   if(T12)  T12->SetAlias("SmearWeightV2", "(exp(-ExcessPT*ExcessPT/(2*18*18))/(((ExcessPT>0)*SmearWeightV2Positive)+((ExcessPT<0)*SmearWeightV2Negative)))");
   if(T12)  T12->SetAlias("SmearWeightV3", "(exp(-ExcessPT*ExcessPT / (2*18*18)) / exp(-ExcessPT*ExcessPT / (2*27.4*27.4)))");
   if(T12)  T12->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   if(T12)  T12->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   if(T12)  T12->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   if(T12)  T12->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   if(T12)  T12->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   if(T12)  T12->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   if(T12)  T12->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   if(T12)  T12->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
}

