{
   TFile File("~/EOSHome/PPTrigger2017/OpenHLT/MenuV14_GeorgeMB.root");

   TTree *Tree = (TTree *)File.Get("hltbitanalysis/HltTree");

   double All = Tree->GetEntries();
   double PF30 = Tree->GetEntries("HLT_AK4PFJet30_v15");
   double PF40 = Tree->GetEntries("HLT_AK4PFJet40_v15");
   double PF60 = Tree->GetEntries("HLT_AK4PFJet60_v15");
   double PF50 = Tree->GetEntries("HLT_AK4PFJet50_v15");
   double PF80 = Tree->GetEntries("HLT_AK4PFJet80_v15");
   double PF100 = Tree->GetEntries("HLT_AK4PFJet100_v15");
   double PF120 = Tree->GetEntries("HLT_AK4PFJet120_v14");
   double Calo30 = Tree->GetEntries("HLT_AK4CaloJet30_v10");
   double Calo40 = Tree->GetEntries("HLT_AK4CaloJet40_v9");
   double Calo50 = Tree->GetEntries("HLT_AK4CaloJet50_v9");
   double Calo60 = Tree->GetEntries("HLT_AK4CaloJet60_v9");
   double Calo80 = Tree->GetEntries("HLT_AK4CaloJet80_v9");
   double Calo100 = Tree->GetEntries("HLT_AK4CaloJet100_v9");
   double Calo120 = Tree->GetEntries("HLT_AK4CaloJet120_v8");
   double L120 = Tree->GetEntries("HLT_L1SingleJet20FWD");
   double L135 = Tree->GetEntries("HLT_L1SingleJet35FWD");
   double L140 = Tree->GetEntries("HLT_L1SingleJet40FWD");
   double L150 = Tree->GetEntries("HLT_L1SingleJet50FWD");
   double L160 = Tree->GetEntries("HLT_L1SingleJet60FWD");
   double PF30FWD = Tree->GetEntries("HLT_AK4PFJet30FWD_v14");
   double PF40FWD = Tree->GetEntries("HLT_AK4PFJet40FWD_v14");
   double PF60FWD = Tree->GetEntries("HLT_AK4PFJet60FWD_v14");
   double PF70FWD = Tree->GetEntries("HLT_AK4PFJet70FWD_v14");
   double PF80FWD = Tree->GetEntries("HLT_AK4PFJet80FWD_v14");
   double Calo30FWD = Tree->GetEntries("HLT_AK4CaloJet30FWD_v8");
   double Calo40FWD = Tree->GetEntries("HLT_AK4CaloJet40FWD_v8");
   double Calo60FWD = Tree->GetEntries("HLT_AK4CaloJet60FWD_v8");
   double Calo70FWD = Tree->GetEntries("HLT_AK4CaloJet70FWD_v8");
   double Calo80FWD = Tree->GetEntries("HLT_AK4CaloJet80FWD_v8");

   cout << "Counts: " << All << endl;
   cout << endl;

   cout << "CaloJet30" << endl;
   cout << "   MB Ratio = " << Calo30 << " / " << All << " = " << Calo30 / All << endl;
   cout << "   Rate (Hz) = " << Calo30 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet40" << endl;
   cout << "   MB Ratio = " << Calo40 << " / " << All << " = " << Calo40 / All << endl;
   cout << "   Rate (Hz) = " << Calo40 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet50" << endl;
   cout << "   MB Ratio = " << Calo50 << " / " << All << " = " << Calo50 / All << endl;
   cout << "   Rate (Hz) = " << Calo50 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet60" << endl;
   cout << "   MB Ratio = " << Calo60 << " / " << All << " = " << Calo60 / All << endl;
   cout << "   Rate (Hz) = " << Calo60 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet80" << endl;
   cout << "   MB Ratio = " << Calo80 << " / " << All << " = " << Calo80 / All << endl;
   cout << "   Rate (Hz) = " << Calo80 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet100" << endl;
   cout << "   MB Ratio = " << Calo100 << " / " << All << " = " << Calo100 / All << endl;
   cout << "   Rate (Hz) = " << Calo100 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet120" << endl;
   cout << "   MB Ratio = " << Calo120 << " / " << All << " = " << Calo120 / All << endl;
   cout << "   Rate (Hz) = " << Calo120 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet30" << endl;
   cout << "   MB Ratio = " << PF30 << " / " << All << " = " << PF30 / All << endl;
   cout << "   Rate (Hz) = " << PF30 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet40" << endl;
   cout << "   MB Ratio = " << PF40 << " / " << All << " = " << PF40 / All << endl;
   cout << "   Rate (Hz) = " << PF40 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet50" << endl;
   cout << "   MB Ratio = " << PF50 << " / " << All << " = " << PF50 / All << endl;
   cout << "   Rate (Hz) = " << PF50 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet60" << endl;
   cout << "   MB Ratio = " << PF60 << " / " << All << " = " << PF60 / All << endl;
   cout << "   Rate (Hz) = " << PF60 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet80" << endl;
   cout << "   MB Ratio = " << PF80 << " / " << All << " = " << PF80 / All << endl;
   cout << "   Rate (Hz) = " << PF80 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet100" << endl;
   cout << "   MB Ratio = " << PF100 << " / " << All << " = " << PF100 / All << endl;
   cout << "   Rate (Hz) = " << PF100 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet120" << endl;
   cout << "   MB Ratio = " << PF120 << " / " << All << " = " << PF120 / All << endl;
   cout << "   Rate (Hz) = " << PF120 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "L1 20 FWD" << endl;
   cout << "   MB Ratio = " << L120 << " / " << All << " = " << L120 / All << endl;
   cout << "   Rate (Hz) = " << L120 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "L1 35 FWD" << endl;
   cout << "   MB Ratio = " << L135 << " / " << All << " = " << L135 / All << endl;
   cout << "   Rate (Hz) = " << L135 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "L1 40 FWD" << endl;
   cout << "   MB Ratio = " << L140 << " / " << All << " = " << L140 / All << endl;
   cout << "   Rate (Hz) = " << L140 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "L1 50 FWD" << endl;
   cout << "   MB Ratio = " << L150 << " / " << All << " = " << L150 / All << endl;
   cout << "   Rate (Hz) = " << L150 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "L1 60 FWD" << endl;
   cout << "   MB Ratio = " << L160 << " / " << All << " = " << L160 / All << endl;
   cout << "   Rate (Hz) = " << L160 / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet30 FWD" << endl;
   cout << "   MB Ratio = " << PF30FWD << " / " << All << " = " << PF30FWD / All << endl;
   cout << "   Rate (Hz) = " << PF30FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet40 FWD" << endl;
   cout << "   MB Ratio = " << PF40FWD << " / " << All << " = " << PF40FWD / All << endl;
   cout << "   Rate (Hz) = " << PF40FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet60 FWD" << endl;
   cout << "   MB Ratio = " << PF60FWD << " / " << All << " = " << PF60FWD / All << endl;
   cout << "   Rate (Hz) = " << PF60FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet70 FWD" << endl;
   cout << "   MB Ratio = " << PF70FWD << " / " << All << " = " << PF70FWD / All << endl;
   cout << "   Rate (Hz) = " << PF70FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "PFJet80 FWD" << endl;
   cout << "   MB Ratio = " << PF80FWD << " / " << All << " = " << PF80FWD / All << endl;
   cout << "   Rate (Hz) = " << PF80FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet30 FWD" << endl;
   cout << "   MB Ratio = " << Calo30FWD << " / " << All << " = " << Calo30FWD / All << endl;
   cout << "   Rate (Hz) = " << Calo30FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet40 FWD" << endl;
   cout << "   MB Ratio = " << Calo40FWD << " / " << All << " = " << Calo40FWD / All << endl;
   cout << "   Rate (Hz) = " << Calo40FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet60 FWD" << endl;
   cout << "   MB Ratio = " << Calo60FWD << " / " << All << " = " << Calo60FWD / All << endl;
   cout << "   Rate (Hz) = " << Calo60FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet70 FWD" << endl;
   cout << "   MB Ratio = " << Calo70FWD << " / " << All << " = " << Calo70FWD / All << endl;
   cout << "   Rate (Hz) = " << Calo70FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   cout << "CaloJet80 FWD" << endl;
   cout << "   MB Ratio = " << Calo80FWD << " / " << All << " = " << Calo80FWD / All << endl;
   cout << "   Rate (Hz) = " << Calo80FWD / All * 20000000 * 2.0 << endl;
   cout << endl;

   File.Close();
}
