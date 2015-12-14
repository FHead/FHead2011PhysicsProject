{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Aug 22 16:35:04 2009) by ROOT version5.18/00a
   TCanvas *c1 = new TCanvas("c1", "c1",12,38,699,501);
   c1->Range(-2.5,-0.03186907,17.5,0.2868216);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TH1 *FirstClusterDepth = new TH1D("FirstClusterDepth","Depth of first cluster, 108537 vs. 108300",16,-0.5,15.5);
   FirstClusterDepth->SetBinContent(1,0.004025302);
   FirstClusterDepth->SetBinContent(2,0.09301323);
   FirstClusterDepth->SetBinContent(3,0.242812);
   FirstClusterDepth->SetBinContent(4,0.1779758);
   FirstClusterDepth->SetBinContent(5,0.1424669);
   FirstClusterDepth->SetBinContent(6,0.09660725);
   FirstClusterDepth->SetBinContent(7,0.06569868);
   FirstClusterDepth->SetBinContent(8,0.04830362);
   FirstClusterDepth->SetBinContent(9,0.036659);
   FirstClusterDepth->SetBinContent(10,0.02587694);
   FirstClusterDepth->SetBinContent(11,0.01940771);
   FirstClusterDepth->SetBinContent(12,0.01523864);
   FirstClusterDepth->SetBinContent(13,0.008481886);
   FirstClusterDepth->SetBinContent(14,0.009488212);
   FirstClusterDepth->SetBinContent(15,0.009631972);
   FirstClusterDepth->SetBinContent(16,0.004312823);
   FirstClusterDepth->SetEntries(6956);
   FirstClusterDepth->SetDirectory(0);
   FirstClusterDepth->SetLineColor(2);
   FirstClusterDepth->SetLineWidth(2);
   FirstClusterDepth->GetXaxis()->SetTitle("Depth of first cluster (layer)");
   FirstClusterDepth->GetYaxis()->SetTitle("Percentage of events");
   FirstClusterDepth->GetYaxis()->SetTitleOffset(1.05);
   FirstClusterDepth->SetStats(0);
   FirstClusterDepth->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9401777,0.6092164,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("Depth of first cluster, 108537 vs. 108300");
   pt->Draw();
   
   TH1 *FirstClusterDepth2 = new TH1D("FirstClusterDepth","Depth of first cluster",16,-0.5,15.5);
   FirstClusterDepth2->SetBinContent(1,0.001554574);
   FirstClusterDepth2->SetBinContent(2,0.07490591);
   FirstClusterDepth2->SetBinContent(3,0.2244723);
   FirstClusterDepth2->SetBinContent(4,0.1908444);
   FirstClusterDepth2->SetBinContent(5,0.1430617);
   FirstClusterDepth2->SetBinContent(6,0.1003927);
   FirstClusterDepth2->SetBinContent(7,0.06504664);
   FirstClusterDepth2->SetBinContent(8,0.05228277);
   FirstClusterDepth2->SetBinContent(9,0.03984618);
   FirstClusterDepth2->SetBinContent(10,0.02970054);
   FirstClusterDepth2->SetBinContent(11,0.02250041);
   FirstClusterDepth2->SetBinContent(12,0.0170594);
   FirstClusterDepth2->SetBinContent(13,0.008222877);
   FirstClusterDepth2->SetBinContent(14,0.01161839);
   FirstClusterDepth2->SetBinContent(15,0.01362297);
   FirstClusterDepth2->SetBinContent(16,0.00486827);
   FirstClusterDepth2->SetEntries(24444);
   FirstClusterDepth2->SetDirectory(0);
   FirstClusterDepth2->SetLineColor(4);
   FirstClusterDepth2->SetLineWidth(2);
   FirstClusterDepth2->Draw("same");

   TLegend *legend = new TLegend(0.7, 0.7, 0.95, 0.95);
   legend->AddEntry(FirstClusterDepth, "Run 108300", "l");
   legend->AddEntry(FirstClusterDepth2, "Run 108537", "l");
   legend->Draw();

   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
