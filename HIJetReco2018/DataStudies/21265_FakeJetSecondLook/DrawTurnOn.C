{
   CsPFJet->Draw("Max$(jtpt)>>A(50,0,200)", "", "");
   CsPFJet->Draw("Max$(jtpt)>>B", "HLT.L1_SingleJet56_BptxAND", "same");
   TGraphAsymmErrors G;
   G.Divide(B, A);
   G.Draw("pla");
}
