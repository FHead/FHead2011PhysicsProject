{
   string filenames[4] = {"SecondaryShift.root", "SecondaryShift.root", "", "SecondaryShift.root"};

   int layerToChannel[16];
   for(int i = 0; i < 15; i++)
      layerToChannel[i+1] = i;
   layerToChannel[0] = 15;

   for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
   {
      if(filenames[iMotherBoard] == "")
         continue;

      TFile f(filenames[iMotherBoard].c_str());

      for(int iLayer = 0; iLayer < 16; iLayer++)
      {
         TH1D *H = (TH1D *)f.Get(Form("ChargeDistribution_%d_%d", iMotherBoard, iLayer));
         if(H == 0)
            continue;

         cout << iMotherBoard << " " << layerToChannel[iLayer] << " " << H->GetMean() << endl;
      }
   }
}
