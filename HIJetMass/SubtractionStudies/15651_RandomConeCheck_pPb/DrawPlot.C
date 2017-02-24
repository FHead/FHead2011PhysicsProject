{
   gROOT->LoadMacro("~/RootMacros/SetStyle.h");
   SetThesisStyle();

   TFile File("Output.root");

   TCanvas Canvas;

   Canvas.SetLogy();

   HTotalPT->Draw();

   Canvas.SaveAs("TotalPT.png");
   Canvas.SaveAs("TotalPT.C");
   Canvas.SaveAs("TotalPT.eps");
   Canvas.SaveAs("TotalPT.pdf");

   HSubtractedPT->Draw();

   Canvas.SaveAs("SubtractedPT.png");
   Canvas.SaveAs("SubtractedPT.C");
   Canvas.SaveAs("SubtractedPT.eps");
   Canvas.SaveAs("SubtractedPT.pdf");
}
