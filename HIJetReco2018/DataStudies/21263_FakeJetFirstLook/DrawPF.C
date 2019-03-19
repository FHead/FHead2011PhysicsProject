{
   PFJet->Draw("rawpt:abs(jteta)>>A(15,0,3)", "HLT.HLT_HIPuAK4CaloJet100Eta5p1_v1 && (rawpt == Max$(rawpt)) && (HI.run < 327401)", "prof");
   PFJet->Draw("rawpt:abs(jteta)>>B(15,0,3)", "HLT.HLT_HIPuAK4CaloJet100Eta5p1_v1 && (rawpt == Max$(rawpt)) && (HI.run > 327401)", "prof same");
   B->Divide(A);
   B->SetStats(0);
   B->SetTitle("PFJet");
   B->GetXaxis()->SetTitle("|#eta|");
   B->GetYaxis()->SetTitle("After / Before");
   B->Draw("hist");
}
