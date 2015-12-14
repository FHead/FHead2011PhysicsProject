{
   TFile File("Output_1_0_0_0_0_0_0_2.root");

   TH1D HFA2("HFA2", "", 100, -1, 1);

   int iC = 0;
   int Count = 0;

   TIter NextKey(File.GetListOfKeys());
   TObject *Object;
   while(Object = (TObject *)NextKey())
   {
      TString Name = Object->GetName();
      if(Name.Contains(Form("HScanFA2_%d", iC)) == false)
         continue;

      TH1D *Hist = (TH1D *)(((TKey *)Object)->ReadObj());

      double Max = Hist->GetMinimum();
      for(int i = 1; i <= Hist->GetNbinsX(); i++)
         Hist->SetBinContent(i, (Hist->GetBinContent(i) - Max));

      HFA2->Add(Hist);
      Count = Count + 1;
   }

   HFA2->Scale(1.0 / Count);
   for(int i = 1; i <= Hist->GetNbinsX(); i++)
      HFA2->SetBinContent(i, (HFA2->GetBinContent(i)));

   cout << Count << endl;

   HFA2->Draw();
}
