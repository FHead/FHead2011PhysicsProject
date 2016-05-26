{
   HYHMG.Draw("hist");
   for(int i = 1; i <= HYHToy.GetNbinsX() / 2; i++)
   {
      double X = HYHToy.GetBinContent(i) + HYHToy.GetBinContent(HYHToy.GetNbinsX() - i + 1);
      X = X / 2;
      HYHToy.SetBinContent(i, X);
      HYHToy.SetBinContent(HYHToy.GetNbinsX() - i + 1, X);
   }
   HYHToy.Draw("same");
   c1.SaveAs("SymmetrizedYH.png");
}

