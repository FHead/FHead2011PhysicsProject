#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void QuickDraw(double PTMin, double PTMax, double CentralityMin, double CentralityMax, bool UseSmearWeight);
void TidyHistogram(TH1D &H1, TH1D &H2, TH1D &H3, TH1D &H4);
void TidyHistogram(TH2D &H1, TH2D &H2, TH2D &H3, TH2D &H4);
void TidyHistogram(TH1D &H2, TH1D &H3, TH1D &H4);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " PTMin PTMax CentralityMin CentralityMax UseSmearWeight" << endl;
      return -1;
   }

   QuickDraw(atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), bool(argv[5][0] == 'Y'));

   return 0;
}

void QuickDraw(double PTMin, double PTMax, double CentralityMin, double CentralityMax, bool UseSmearWeight)
{
   string Baseline1 = Form("Centrality >= %f && Centrality < %f && JetPT >= %f && JetPT < %f && SubJetDR > 0.0 && SubJetDR < 1.0 && abs(JetEta) < 1.3 && min(SubJet1PT,SubJet2PT)/(SubJet1PT+SubJet2PT) > 0.00", CentralityMin, CentralityMax, PTMin, PTMax);
   string Baseline2 = Form("SmearWeight * (Centrality >= %f && Centrality < %f && BestJetPT >= %f && BestJetPT < %f && BestJetDR > 0.0 && BestJetDR < 1.0 && abs(BestJetEta) < 1.3 && BestJetZG > 0.00 && MatchedDR < 0.10 && JetPT > 0)", CentralityMin * 100, CentralityMax * 100, PTMin, PTMax);
   string Baseline3 = Form("Centrality >= %f && Centrality < %f && MatchPT >= %f && MatchPT < %f && SubJetDR0 > 0.0 && SubJetDR0 < 1.0 && abs(JetEta) < 1.3 && min(SubJet1PT0,SubJet2PT0)/(SubJet1PT0+SubJet2PT0) > 0.00", CentralityMin, CentralityMax, PTMin, PTMax);
   string Baseline4 = Form("Centrality >= %f && Centrality < %f && JetPT >= %f && JetPT < %f && SubJetDR > 0.0 && SubJetDR < 1.0 && abs(Eta) < 1.3 && min(SubJet1PT,SubJet2PT)/(SubJet1PT+SubJet2PT) > 0.00", CentralityMin, CentralityMax, PTMin, PTMax);
   
   string Baseline72 = Form("SmearWeight * (Centrality >= %f && Centrality < %f && BestJetPT >= %f && BestJetPT < %f && BestJetDR2 > 0.00 && BestJetDR2 < 1.0 && abs(BestJetEta) < 1.3 && BestJetZG2 > 0.00 && MatchedDR < 0.10 && JetPT > 0)", CentralityMin * 100, CentralityMax * 100, PTMin, PTMax);
   string Baseline73 = Form("Centrality >= %f && Centrality < %f && MatchPT >= %f && MatchPT < %f && SubJetDR7 > 0.00 && SubJetDR7 < 1.0 && abs(JetEta) < 1.3 && min(SubJet1PT7,SubJet2PT7)/(SubJet1PT7+SubJet2PT7) > 0.00", CentralityMin, CentralityMax, PTMin, PTMax);
   string Baseline74 = Form("Centrality >= %f && Centrality < %f && JetPT >= %f && JetPT < %f && SubJetDR7 > 0.00 && SubJetDR7 < 1.0 && abs(Eta) < 1.3 && min(SubJet1PT7,SubJet2PT7)/(SubJet1PT7+SubJet2PT7) > 0.00", CentralityMin, CentralityMax, PTMin, PTMax);

   if(UseSmearWeight == false)
      Baseline2 = Form("(Centrality >= %f && Centrality < %f && BestJetPT >= %f && BestJetPT < %f && BestJetDR > 0 && abs(BestJetEta) < 1.3)", CentralityMin * 100, CentralityMax * 100, PTMin, PTMax);

   string Tag = Form("C_%.0f_%.0f_PT_%.0f_%.0f", CentralityMin * 100, CentralityMax * 100, PTMin, PTMax);
   if(UseSmearWeight == false)
      Tag = Tag + "_NoSmearWeight";
   else
      Tag = Tag + "_WithSmearWeight";

   TCanvas Canvas;

   TFile F1("Output_HiForest_2.root");
   TFile F2("Output_All.root");
   // TFile F3("Output_HiForest_2.root");
   TFile F4("OutputIV.root");

   TTree *T1 = (TTree *)F1.Get("T");
   TTree *T2 = (TTree *)F2.Get("OutputTree");
   TTree *T3 = T1;
   TTree *T4 = (TTree *)F4.Get("T");

   T2->SetAlias("X", "(Centrality/100)");
   T2->SetAlias("RMS1", "(exp(1.482-26.28*X)+exp(3.337-3.542*X))");
   T2->SetAlias("RMSA", "(27.83-165.2*X+682.8*X*X-1987*X*X*X+3409*X*X*X*X-3043*X*X*X*X*X+1097*X*X*X*X*X*X-7.243*X*X*X*X*X*X*X)");
   T2->SetAlias("RMS2", "(19.15-23.28*X+4.567e-7*X*X-467.4*X*X*X+2110*X*X*X*X-2993*X*X*X*X*X+227.9*X*X*X*X*X*X+2019*X*X*X*X*X*X*X+876.3*X*X*X*X*X*X*X*X-3027*X*X*X*X*X*X*X*X*X+1239*X*X*X*X*X*X*X*X*X*X)");
   T2->SetAlias("ExcessPT", "(TotalPTInJet-Rho*0.4*0.4*3.1415926535)");
   T2->SetAlias("ExcessPT2", "((TotalPT-Rho*1.2*1.2*3.1415926535)/9)");
   // T2->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT/(2*RMS2*RMS2))/exp(-ExcessPT*ExcessPT/(2*RMS1*RMS1)))");
   T2->SetAlias("SmearWeight", "(exp(-ExcessPT2*ExcessPT2/(2*RMS2*RMS2/3/3))/exp(-ExcessPT2*ExcessPT2/(2*RMSA*RMSA)))");
   T2->SetAlias("JetPTWeight", "(1.03506+0.660936*exp(-(BestJetPT-169.995)*(BestJetPT-169.995)/(2*28.597*28.597))-0.000959956*BestJetPT)");

   T2->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T2->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T2->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T2->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");

   T2->SetAlias("PTPT", "(BestJetSDPT/BestJetPT)");

   TH1D HB0("HB0", ";PT/PT;a.u.", 50, 0.5, 1);   HB0.Sumw2();
   TH1D HC0("HC0", ";PT/PT;a.u.", 50, 0.5, 1);   HC0.Sumw2();

   T2->Draw("BestJetSDPT/BestJetPT>>HB0", Baseline2.c_str(), "same");
   T3->Draw("SDPT0/MatchPT>>HC0", Baseline3.c_str(), "hist");
  
   string PTPTWeight = "(";
   for(int i = 1; i <= HB0.GetNbinsX(); i++)
   {
      double B = HB0.GetBinContent(i);
      double C = HC0.GetBinContent(i);
      if(i != 1)
         PTPTWeight = PTPTWeight + "+";

      double Ratio = C / B;
      if(B == 0)
         Ratio = 1;

      double L = HB0.GetXaxis()->GetBinLowEdge(i);
      double R = HB0.GetXaxis()->GetBinUpEdge(i);
      PTPTWeight = PTPTWeight + Form("(PTPT>=%f&&PTPT<%f)*%f", L, R, Ratio);
   }
   PTPTWeight = PTPTWeight + ")";
   T2->SetAlias("PTPTWeight", PTPTWeight.c_str());
   
   // Baseline2 = Form("SmearWeight * PTPTWeight * (Centrality >= %f && Centrality < %f && BestJetPT >= %f && BestJetPT < %f && BestJetDR > 0 && abs(BestJetEta) < 1.3)", CentralityMin * 100, CentralityMax * 100, PTMin, PTMax);
   // cout << PTPTWeight << endl;
   
   TH1D HA1("HA1", ";DR;a.u.", 50, 0, 0.5);   HA1.Sumw2();
   TH1D HB1("HB1", ";DR;a.u.", 50, 0, 0.5);   HB1.Sumw2();
   TH1D HC1("HC1", ";DR;a.u.", 50, 0, 0.5);   HC1.Sumw2();
   TH1D HD1("HD1", ";DR;a.u.", 50, 0, 0.5);   HD1.Sumw2();

   T1->Draw("SubJetDR>>HA1", Baseline1.c_str(), "hist");
   T2->Draw("BestJetDR>>HB1", Baseline2.c_str(), "same");
   T3->Draw("SubJetDR0>>HC1", Baseline3.c_str(), "same");
   T4->Draw("SubJetDR>>HD1", Baseline4.c_str(), "same");
   
   TidyHistogram(HA1, HB1, HC1, HD1);

   HA1.Draw();
   HB1.Draw("same");
   HC1.Draw("same");
   HD1.Draw("same");

   // Canvas.SaveAs(Form("Plots/DR_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/DR_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/DR_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/DR_%s.pdf", Tag.c_str()));

   TH1D HA2("HA2", ";Centrality;a.u.", 20, 0, 0.8);   HA2.Sumw2();
   TH1D HB2("HB2", ";Centrality;a.u.", 20, 0, 0.8);   HB2.Sumw2();
   TH1D HC2("HC2", ";Centrality;a.u.", 20, 0, 0.8);   HC2.Sumw2();
   TH1D HD2("HD2", ";Centrality;a.u.", 20, 0, 0.8);   HD2.Sumw2();

   T1->Draw("Centrality>>HA2", Baseline1.c_str(), "hist");
   T2->Draw("Centrality/100>>HB2", Baseline2.c_str(), "same");
   T3->Draw("Centrality>>HC2", Baseline3.c_str(), "same");
   T4->Draw("Centrality>>HD2", Baseline4.c_str(), "same");
   
   TidyHistogram(HA2, HB2, HC2, HD2);

   HA2.Draw();
   HB2.Draw("same");
   HC2.Draw("same");
   HD2.Draw("same");

   // Canvas.SaveAs(Form("Plots/Centrality_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/Centrality_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/Centrality_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/Centrality_%s.pdf", Tag.c_str()));

   TH1D HA3("HA3", ";Mass/PT;a.u.", 30, 0, 0.3);   HA3.Sumw2();
   TH1D HB3("HB3", ";Mass/PT;a.u.", 30, 0, 0.3);   HB3.Sumw2();
   TH1D HC3("HC3", ";Mass/PT;a.u.", 30, 0, 0.3);   HC3.Sumw2();
   TH1D HD3("HD3", ";Mass/PT;a.u.", 30, 0, 0.3);   HD3.Sumw2();

   T1->Draw("SDMass/JetPT>>HA3", Baseline1.c_str(), "hist");
   T2->Draw("BestJetSDMass/BestJetPT>>HB3", Baseline2.c_str(), "same");
   T3->Draw("SDMass0/MatchPT>>HC3", Baseline3.c_str(), "same");
   T4->Draw("Mass/JetPT>>HD3", Baseline4.c_str(), "same");

   TidyHistogram(HA3, HB3, HC3, HD3);

   HA3.Draw();
   HB3.Draw("same");
   HC3.Draw("same");
   HD3.Draw("same");

   // Canvas.SaveAs(Form("Plots/SDMass_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/SDMass_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/SDMass_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/SDMass_%s.pdf", Tag.c_str()));

   TH1D HA4("HA4", ";z_{g};a.u.", 25, 0, 0.5);   HA4.Sumw2();
   TH1D HB4("HB4", ";z_{g};a.u.", 25, 0, 0.5);   HB4.Sumw2();
   TH1D HC4("HC4", ";z_{g};a.u.", 25, 0, 0.5);   HC4.Sumw2();
   TH1D HD4("HD4", ";z_{g};a.u.", 25, 0, 0.5);   HD4.Sumw2();

   T1->Draw("min(SubJet1PT,SubJet2PT)/(SubJet1PT+SubJet2PT)>>HA4", Baseline1.c_str(), "hist");
   T2->Draw("BestJetZG>>HB4", Baseline2.c_str(), "same");
   T3->Draw("min(SubJet1PT0,SubJet2PT0)/(SubJet1PT0+SubJet2PT0)>>HC4", Baseline3.c_str(), "hist");
   T4->Draw("min(SubJet1PT,SubJet2PT)/(SubJet1PT+SubJet2PT)>>HD4", Baseline4.c_str(), "hist");
   
   TidyHistogram(HA4, HB4, HC4, HD4);

   HA4.Draw();
   HB4.Draw("same");
   HC4.Draw("same");
   HD4.Draw("same");

   // Canvas.SaveAs(Form("Plots/ZG_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/ZG_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/ZG_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/ZG_%s.pdf", Tag.c_str()));

   TH1D HA5("HA5", ";PT;a.u.", 50, 0, 500);   HA5.Sumw2();
   TH1D HB5("HB5", ";PT;a.u.", 50, 0, 500);   HB5.Sumw2();
   TH1D HC5("HC5", ";PT;a.u.", 50, 0, 500);   HC5.Sumw2();
   TH1D HD5("HD5", ";PT;a.u.", 50, 0, 500);   HD5.Sumw2();

   T1->Draw("JetPT>>HA5", Baseline1.c_str(), "hist");
   T2->Draw("BestJetPT>>HB5", Baseline2.c_str(), "same");
   T3->Draw("MatchPT>>HC5", Baseline3.c_str(), "hist");
   T4->Draw("JetPT>>HD5", Baseline4.c_str(), "hist");
   
   TidyHistogram(HA5, HB5, HC5, HD5);

   HA5.Draw();
   HB5.Draw("same");
   HC5.Draw("same");
   HD5.Draw("same");

   // Canvas.SaveAs(Form("Plots/JetPT_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/JetPT_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/JetPT_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/JetPT_%s.pdf", Tag.c_str()));

   TH1D HA6("HA6", ";PT/PT;a.u.", 50, 0.5, 1);   HA6.Sumw2();
   TH1D HB6("HB6", ";PT/PT;a.u.", 50, 0.5, 1);   HB6.Sumw2();
   TH1D HC6("HC6", ";PT/PT;a.u.", 50, 0.5, 1);   HC6.Sumw2();
   TH1D HD6("HD6", ";PT/PT;a.u.", 50, 0.5, 1);   HD6.Sumw2();

   T1->Draw("JetSDPT/JetPT>>HA6", Baseline1.c_str(), "hist");
   T2->Draw("BestJetSDPT/BestJetPT>>HB6", Baseline2.c_str(), "same");
   T3->Draw("SDPT0/MatchPT>>HC6", Baseline3.c_str(), "hist");
   T4->Draw("GroomedPT/JetPT>>HD6", Baseline4.c_str(), "hist");
   
   TidyHistogram(HA6, HB6, HC6, HD6);

   HA6.Draw();
   HB6.Draw("same");
   HC6.Draw("same");
   HD6.Draw("same");

   // Canvas.SaveAs(Form("Plots/GroomedPTFraction_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/GroomedPTFraction_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/GroomedPTFraction_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/GroomedPTFraction_%s.pdf", Tag.c_str()));

   TH2D HA7("HA7", ";DR;zg", 50, 0.0, 0.5, 50, 0.0, 0.5);   HA7.Sumw2();
   TH2D HB7("HB7", ";DR;zg", 50, 0.0, 0.5, 50, 0.0, 0.5);   HB7.Sumw2();
   TH2D HC7("HC7", ";DR;zg", 50, 0.0, 0.5, 50, 0.0, 0.5);   HC7.Sumw2();
   TH2D HD7("HD7", ";DR;zg", 50, 0.0, 0.5, 50, 0.0, 0.5);   HD7.Sumw2();

   T1->Draw("min(SubJet1PT,SubJet2PT)/(SubJet1PT+SubJet2PT):SubJetDR>>HA7", Baseline1.c_str(), "goff");
   T2->Draw("BestJetZG:BestJetDR>>HB7", Baseline2.c_str(), "goff");
   T3->Draw("min(SubJet1PT0,SubJet2PT0)/(SubJet1PT0+SubJet2PT0):SubJetDR0>>HC7", Baseline3.c_str(), "goff");
   T4->Draw("min(SubJet1PT,SubJet2PT)/(SubJet1PT+SubJet2PT):SubJetDR>>HD7", Baseline4.c_str(), "goff");
   
   TidyHistogram(HA7, HB7, HC7, HD7);
   
   TCanvas Canvas2;
   Canvas2.Divide(2,2);

   Canvas2.cd(1);
   HA7.Draw("colz");
   Canvas2.cd(2);
   HB7.Draw("colz");
   Canvas2.cd(3);
   HC7.Draw("colz");
   Canvas2.cd(4);
   HD7.Draw("colz");

   // Canvas2.SaveAs(Form("Plots/DRZG_%s.png", Tag.c_str()));
   // Canvas2.SaveAs(Form("Plots/DRZG_%s.C",   Tag.c_str()));
   // Canvas2.SaveAs(Form("Plots/DRZG_%s.eps", Tag.c_str()));
   Canvas2.SaveAs(Form("Plots/DRZG_%s.pdf", Tag.c_str()));

   TH2D HA8("HA8", ";DR;Groomed PT fraction", 50, 0.0, 0.5, 50, 0.5, 1.0);   HA8.Sumw2();
   TH2D HB8("HB8", ";DR;Groomed PT fraction", 50, 0.0, 0.5, 50, 0.5, 1.0);   HB8.Sumw2();
   TH2D HC8("HC8", ";DR;Groomed PT fraction", 50, 0.0, 0.5, 50, 0.5, 1.0);   HC8.Sumw2();
   TH2D HD8("HD8", ";DR;Groomed PT fraction", 50, 0.0, 0.5, 50, 0.5, 1.0);   HD8.Sumw2();

   T1->Draw("JetSDPT/JetPT:SubJetDR>>HA8", Baseline1.c_str(), "colz goff");
   T2->Draw("BestJetSDPT/BestJetPT:BestJetDR>>HB8", Baseline2.c_str(), "colz goff");
   T3->Draw("SDPT0/MatchPT:SubJetDR0>>HC8", Baseline3.c_str(), "colz goff");
   T4->Draw("GroomedPT/JetPT:SubJetDR>>HD8", Baseline4.c_str(), "colz goff");
   
   TidyHistogram(HA8, HB8, HC8, HD8);
   
   Canvas2.cd(1);
   HA8.Draw("colz");
   Canvas2.cd(2);
   HB8.Draw("colz");
   Canvas2.cd(3);
   HC8.Draw("colz");
   Canvas2.cd(4);
   HD8.Draw("colz");

   // Canvas2.SaveAs(Form("Plots/DRGroomedPTFraction_%s.png", Tag.c_str()));
   // Canvas2.SaveAs(Form("Plots/DRGroomedPTFraction_%s.C",   Tag.c_str()));
   // Canvas2.SaveAs(Form("Plots/DRGroomedPTFraction_%s.eps", Tag.c_str()));
   Canvas2.SaveAs(Form("Plots/DRGroomedPTFraction_%s.pdf", Tag.c_str()));

   TH1D HB9("HB9", ";DR;a.u.", 50, 0, 0.5);   HB9.Sumw2();
   TH1D HC9("HC9", ";DR;a.u.", 50, 0, 0.5);   HC9.Sumw2();
   TH1D HD9("HD9", ";DR;a.u.", 50, 0, 0.5);   HD9.Sumw2();

   T2->Draw("BestJetDR2>>HB9", Baseline72.c_str(), "same");
   T3->Draw("SubJetDR7>>HC9", Baseline73.c_str(), "same");
   T4->Draw("SubJetDR7>>HD9", Baseline74.c_str(), "same");
   
   TidyHistogram(HB9, HC9, HD9);

   Canvas.cd();

   HB9.Draw();
   HC9.Draw("same");
   HD9.Draw("same");

   // Canvas.SaveAs(Form("Plots/DR7_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/DR7_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/DR7_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/DR7_%s.pdf", Tag.c_str()));

   TH1D HB10("HB10", ";Mass/PT;a.u.", 30, 0, 0.3);   HB10.Sumw2();
   TH1D HC10("HC10", ";Mass/PT;a.u.", 30, 0, 0.3);   HC10.Sumw2();
   TH1D HD10("HD10", ";Mass/PT;a.u.", 30, 0, 0.3);   HD10.Sumw2();

   T2->Draw("BestJetSDMass2/BestJetPT>>HB10", Baseline72.c_str(), "same");
   T3->Draw("SDMass7/MatchPT>>HC10", Baseline73.c_str(), "same");
   T4->Draw("Mass7/JetPT>>HD10", Baseline74.c_str(), "same");

   TidyHistogram(HB10, HC10, HD10);

   HB10.Draw();
   HC10.Draw("same");
   HD10.Draw("same");

   // Canvas.SaveAs(Form("Plots/SDMass7_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/SDMass7_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/SDMass7_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/SDMass7_%s.pdf", Tag.c_str()));

   TH1D HB11("HB11", ";z_{g};a.u.", 25, 0, 0.5);   HB11.Sumw2();
   TH1D HC11("HC11", ";z_{g};a.u.", 25, 0, 0.5);   HC11.Sumw2();
   TH1D HD11("HD11", ";z_{g};a.u.", 25, 0, 0.5);   HD11.Sumw2();

   T2->Draw("BestJetZG2>>HB11", Baseline72.c_str(), "same");
   T3->Draw("min(SubJet1PT7,SubJet2PT7)/(SubJet1PT7+SubJet2PT7)>>HC11", Baseline73.c_str(), "hist");
   T4->Draw("min(SubJet1PT7,SubJet2PT7)/(SubJet1PT7+SubJet2PT7)>>HD11", Baseline74.c_str(), "hist");
   
   TidyHistogram(HB11, HC11, HD11);

   HB11.Draw();
   HC11.Draw("same");
   HD11.Draw("same");

   // Canvas.SaveAs(Form("Plots/ZG7_%s.png", Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/ZG7_%s.C",   Tag.c_str()));
   // Canvas.SaveAs(Form("Plots/ZG7_%s.eps", Tag.c_str()));
   Canvas.SaveAs(Form("Plots/ZG7_%s.pdf", Tag.c_str()));

}

void TidyHistogram(TH1D &H1, TH1D &H2, TH1D &H3, TH1D &H4)
{
   double BinSize1 = (H1.GetXaxis()->GetBinUpEdge(H1.GetNbinsX()) - H1.GetXaxis()->GetBinLowEdge(1)) / H1.GetNbinsX();
   double BinSize2 = (H2.GetXaxis()->GetBinUpEdge(H2.GetNbinsX()) - H2.GetXaxis()->GetBinLowEdge(1)) / H2.GetNbinsX();
   double BinSize3 = (H3.GetXaxis()->GetBinUpEdge(H3.GetNbinsX()) - H3.GetXaxis()->GetBinLowEdge(1)) / H3.GetNbinsX();
   double BinSize4 = (H4.GetXaxis()->GetBinUpEdge(H4.GetNbinsX()) - H4.GetXaxis()->GetBinLowEdge(1)) / H4.GetNbinsX();

   H1.Scale(1 / H1.Integral() / BinSize1);
   H2.Scale(1 / H2.Integral() / BinSize2);
   H3.Scale(1 / H3.Integral() / BinSize3);
   H4.Scale(1 / H4.Integral() / BinSize4);
   
   H1.SetStats(0);
   H2.SetStats(0);
   H3.SetStats(0);
   H4.SetStats(0);

   H1.SetLineColor(kRed);
   H1.SetMarkerColor(kRed);
   H1.SetMinimum(0);
   
   H3.SetLineColor(kBlue);
   H3.SetMarkerColor(kBlue);
   
   H4.SetLineColor(kGreen + 3);
   H4.SetMarkerColor(kGreen + 3);

   double Maximum = max(max(H1.GetMaximum(), H2.GetMaximum()), max(H3.GetMaximum(), H4.GetMaximum()));
   H1.SetMaximum(Maximum * 1.1);

   H1.SetMarkerSize(1.4);
   H2.SetMarkerSize(1.3);
   H3.SetMarkerSize(1.2);
   H4.SetMarkerSize(1.1);
}

void TidyHistogram(TH2D &H1, TH2D &H2, TH2D &H3, TH2D &H4)
{
   double BinSizeX1 = (H1.GetXaxis()->GetBinUpEdge(H1.GetNbinsX()) - H1.GetXaxis()->GetBinLowEdge(1)) / H1.GetNbinsX();
   double BinSizeX2 = (H2.GetXaxis()->GetBinUpEdge(H2.GetNbinsX()) - H2.GetXaxis()->GetBinLowEdge(1)) / H2.GetNbinsX();
   double BinSizeX3 = (H3.GetXaxis()->GetBinUpEdge(H3.GetNbinsX()) - H3.GetXaxis()->GetBinLowEdge(1)) / H3.GetNbinsX();
   double BinSizeX4 = (H4.GetXaxis()->GetBinUpEdge(H4.GetNbinsX()) - H4.GetXaxis()->GetBinLowEdge(1)) / H4.GetNbinsX();
   
   double BinSizeY1 = (H1.GetYaxis()->GetBinUpEdge(H1.GetNbinsY()) - H1.GetYaxis()->GetBinLowEdge(1)) / H1.GetNbinsY();
   double BinSizeY2 = (H2.GetYaxis()->GetBinUpEdge(H2.GetNbinsY()) - H2.GetYaxis()->GetBinLowEdge(1)) / H2.GetNbinsY();
   double BinSizeY3 = (H3.GetYaxis()->GetBinUpEdge(H3.GetNbinsY()) - H3.GetYaxis()->GetBinLowEdge(1)) / H3.GetNbinsY();
   double BinSizeY4 = (H4.GetYaxis()->GetBinUpEdge(H4.GetNbinsY()) - H4.GetYaxis()->GetBinLowEdge(1)) / H4.GetNbinsY();
   
   H1.Scale(1 / H1.Integral() / BinSizeX1 / BinSizeY1);
   H2.Scale(1 / H2.Integral() / BinSizeX2 / BinSizeY2);
   H3.Scale(1 / H3.Integral() / BinSizeX3 / BinSizeY3);
   H4.Scale(1 / H4.Integral() / BinSizeX4 / BinSizeY4);

   H1.SetStats(0);
   H2.SetStats(0);
   H3.SetStats(0);
   H4.SetStats(0);
}

void TidyHistogram(TH1D &H2, TH1D &H3, TH1D &H4)
{
   double BinSize2 = (H2.GetXaxis()->GetBinUpEdge(H2.GetNbinsX()) - H2.GetXaxis()->GetBinLowEdge(1)) / H2.GetNbinsX();
   double BinSize3 = (H3.GetXaxis()->GetBinUpEdge(H3.GetNbinsX()) - H3.GetXaxis()->GetBinLowEdge(1)) / H3.GetNbinsX();
   double BinSize4 = (H4.GetXaxis()->GetBinUpEdge(H4.GetNbinsX()) - H4.GetXaxis()->GetBinLowEdge(1)) / H4.GetNbinsX();

   H2.Scale(1 / H2.Integral() / BinSize2);
   H3.Scale(1 / H3.Integral() / BinSize3);
   H4.Scale(1 / H4.Integral() / BinSize4);
   
   H2.SetStats(0);
   H3.SetStats(0);
   H4.SetStats(0);

   H2.SetMinimum(0);
   
   H3.SetLineColor(kBlue);
   H3.SetMarkerColor(kBlue);
   
   H4.SetLineColor(kGreen + 3);
   H4.SetMarkerColor(kGreen + 3);

   double Maximum = max(max(H2.GetMaximum(), H2.GetMaximum()), max(H3.GetMaximum(), H4.GetMaximum()));
   H2.SetMaximum(Maximum * 1.1);

   H2.SetMarkerSize(1.3);
   H3.SetMarkerSize(1.2);
   H4.SetMarkerSize(1.1);
}



