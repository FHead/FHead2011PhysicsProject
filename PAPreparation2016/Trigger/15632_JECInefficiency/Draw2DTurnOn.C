{
   HAllPFJetsPTEta->Rebin2D(2, 2);
   HPass40PFJetsPTEta->Rebin2D(2, 2);
   HPass40PFJetsPTEta->Divide(HAllPFJetsPTEta);
   HPass40PFJetsPTEta->Draw("colz");
}
