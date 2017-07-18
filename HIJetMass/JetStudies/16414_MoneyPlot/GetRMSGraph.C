{
   TGraph G;
   for(int i = 0; i <= 80; i++)
   {
      cout << "Processing centrality bin " << i << endl;
      TH1D H(Form("H%d", i), "", 4000, -200, 200);
      OutputTree->Draw(Form("TotalPTInJet-Rho*0.4*0.4*3.1415926535>>H%d", i),
         Form("Centrality >= %d && Centrality < %d", i, i + 1));
      G.SetPoint(i, 0.01 * i, H.GetRMS());
   }

   G.Draw();
}
