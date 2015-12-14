{
   string filenames[4] = {"mip_108528.root", "mip_108525.root", "", "mip_108523.root"};

   int layerToChannel[16];
   for(int i = 0; i < 15; i++)
      layerToChannel[i+1] = i;
   layerToChannel[0] = 15;

   for(int iFile = 0; iFile < 4; iFile++)
   {
      if(filenames[iFile] == "")
         continue;

      TFile f(filenames[iFile].c_str());

      for(int iMotherBoard = 0; iMotherBoard < 4; iMotherBoard++)
      {
         for(int iLayer = 0; iLayer < 16; iLayer++)
         {
            TH1D *H = (TH1D *)f.Get(Form("ChargeDistribution_%d_%d", iMotherBoard, iLayer));
            if(H == 0)
               continue;

            cout << iFile << " " << iMotherBoard << " " << layerToChannel[iLayer] << " " << H->GetMean() << endl;
         }
      }
   }
}
