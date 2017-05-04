{
   TGraphErrors G;
   for(int i = 1; i <= 100; i++)
   {
      double RMS = HSubtractedPTCentrality->ProjectionY(Form("X%d", i), i, i)->GetRMS();
      double RMSError = HSubtractedPTCentrality->ProjectionY(Form("X%d", i), i, i)->GetRMSError();
      G.SetPoint(i - 1, i * 0.01, RMS);
      G.SetPointError(i - 1, 0, RMSError);
   }
}
