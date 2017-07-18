{
   TGraph G;
   for(int i = 0; i <= 80; i++)
   {
      cout << "Processing centrality bin " << i << endl;
      TH1D H(Form("H%d", i), "", 4000, -200, 200);
      OutputTree->Draw(Form("TotalPTInJet-Rho*0.4*0.4*3.1415926535>>H%d", i),
         Form("MCWeight * (Centrality >= %d && Centrality < %d)", i, i + 1));
      G.SetPoint(i, i, H.GetRMS());
   }

   G.Draw();
}
