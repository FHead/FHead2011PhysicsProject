{
   double P[7];
   P[0] = 0.9749;
   P[1] = 0.7382;
   P[2] = -0.8869;
   P[3] = 0.3503;
   P[4] = -0.05973;
   P[5] = 0.004686;
   P[6] = -0.0001403;

   TH1D H("H", "", 100, 0, 10);

   for(int i = 1; i <= 100; i++)
   {
      double PT = H.GetXaxis()->GetBinCenter(i);
      
      double Factor = PT;
      if(PT < 1)
         Factor = PT;
      else if(PT < 10)
         Factor = P[0] + P[1] * PT + P[2] * PT * PT + P[3] * PT * PT * PT + P[4] * PT * PT * PT * PT + P[5] * PT * PT * PT * PT * PT + P[6] * PT * PT * PT * PT * PT * PT;
      else
         Factor = 1;
      Factor = Factor / 2;

      H.SetBinContent(i, Factor);
   }
}


