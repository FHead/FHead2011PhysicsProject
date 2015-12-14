#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main()
{
   SetStyle();

   TFile FA1("EventsA_unweighted.root");
   TFile FA2("EventsA_unweighted_born.root");
   TFile FB1("EventsB_unweighted.root");
   TFile FB2("EventsB_unweighted_born.root");
   TFile FC1("EventsC_unweighted.root");
   TFile FC2("EventsC_unweighted_born.root");

   TTree *TA1 = (TTree *)FA1.Get("Tree");
   TTree *TA2 = (TTree *)FA2.Get("Tree");
   TTree *TB1 = (TTree *)FB1.Get("Tree");
   TTree *TB2 = (TTree *)FB2.Get("Tree");
   TTree *TC1 = (TTree *)FC1.Get("Tree");
   TTree *TC2 = (TTree *)FC2.Get("Tree");

   vector<string> Label;
   Label.push_back("M_{4l}");
   Label.push_back("M_{1}");
   Label.push_back("M_{2}");
   Label.push_back("#Phi_{1}");
   Label.push_back("cos #Theta_{0}");
   Label.push_back("#phi");
   Label.push_back("cos #theta_{1}");
   Label.push_back("cos #theta_{2}");
   Label.push_back("y_{4l}");
   Label.push_back("P{T,4l}");
   Label.push_back("#phi_{4l}");
   Label.push_back("#phi_{offset}");

   vector<string> ToPlot;
   ToPlot.push_back("MH");
   ToPlot.push_back("M1");
   ToPlot.push_back("M2");
   ToPlot.push_back("Phi0+2*3.1415926535*(Phi0<0)");
   ToPlot.push_back("cos(Theta0)");
   ToPlot.push_back("Phi+2*3.1415926535*(Phi<0)");
   ToPlot.push_back("cos(Theta1)");
   ToPlot.push_back("cos(Theta2)");
   ToPlot.push_back("YH");
   ToPlot.push_back("PTH");
   ToPlot.push_back("PhiH+2*3.1415926535*(PhiH<0)");
   ToPlot.push_back("PhiOffset+2*3.1415926535*(PhiOffset<0)");

   double Min[] = {90, 0, 0, 0, -1, 0, -1, -1, -2, 0, 0, 0};
   double Max[] = {135, 120, 100, 2 * PI, 1, 2 * PI, 1, 1, 2, 100, 2 * PI, 2 * PI};

   double Height[] = {0.5, 0.20, 0.06, 0.02, 0.02, 0.02, 0.0238, 0.0238, 0.6, 1, 0.04, 0.04};

   for(int i = 0; i < 12; i++)
   {
      TH1D HA1(Form("HA1_%d", i), Form("%s;%s;a.u.", Label[i].c_str(), Label[i].c_str()), 100, Min[i], Max[i]);
      TH1D HA2(Form("HA2_%d", i), Form("%s;%s;a.u.", Label[i].c_str(), Label[i].c_str()), 100, Min[i], Max[i]);
      TH1D HB1(Form("HB1_%d", i), Form("%s;%s;a.u.", Label[i].c_str(), Label[i].c_str()), 100, Min[i], Max[i]);
      TH1D HB2(Form("HB2_%d", i), Form("%s;%s;a.u.", Label[i].c_str(), Label[i].c_str()), 100, Min[i], Max[i]);
      TH1D HC1(Form("HC1_%d", i), Form("%s;%s;a.u.", Label[i].c_str(), Label[i].c_str()), 100, Min[i], Max[i]);
      TH1D HC2(Form("HC2_%d", i), Form("%s;%s;a.u.", Label[i].c_str(), Label[i].c_str()), 100, Min[i], Max[i]);

      TA1->Draw(Form("%s>>HA1_%d", ToPlot[i].c_str(), i), "", "");
      TA2->Draw(Form("%s>>HA2_%d", ToPlot[i].c_str(), i), "", "");
      TB1->Draw(Form("%s>>HB1_%d", ToPlot[i].c_str(), i), "", "");
      TB2->Draw(Form("%s>>HB2_%d", ToPlot[i].c_str(), i), "", "");
      TC1->Draw(Form("%s>>HC1_%d", ToPlot[i].c_str(), i), "", "");
      TC2->Draw(Form("%s>>HC2_%d", ToPlot[i].c_str(), i), "", "");

      HA1.Scale(1 / HA1.Integral());
      HA2.Scale(1 / HA2.Integral());
      HB1.Scale(1 / HB1.Integral());
      HB2.Scale(1 / HB2.Integral());
      HC1.Scale(1 / HC1.Integral());
      HC2.Scale(1 / HC2.Integral());

      HA1.SetStats(0);
      HA1.GetXaxis()->SetTitleOffset(1.1);
      HA1.GetYaxis()->SetTitleOffset(1.2);
      HA1.SetMaximum(Height[i]);
      HA1.SetMinimum(0);

      HA1.SetLineWidth(2);
      HA1.SetLineStyle(1);
      HA1.SetLineColor(kBlack);
      HA2.SetLineWidth(2);
      HA2.SetLineStyle(kDashed);
      HA2.SetLineColor(kBlack);
      HB1.SetLineWidth(2);
      HB1.SetLineStyle(1);
      HB1.SetLineColor(kBlue);
      HB2.SetLineWidth(2);
      HB2.SetLineStyle(kDashed);
      HB2.SetLineColor(kBlue);
      HC1.SetLineWidth(2);
      HC1.SetLineStyle(1);
      HC1.SetLineColor(kRed);
      HC2.SetLineWidth(2);
      HC2.SetLineStyle(kDashed);
      HC2.SetLineColor(kRed);

      TLegend *Legend;
      if(i == 0 || i == 1)
         Legend = new TLegend(0.20, 0.8, 0.50, 0.6);
      else
         Legend = new TLegend(0.55, 0.8, 0.85, 0.6);
      Legend->SetTextFont();
      Legend->SetBorderSize(0);
      Legend->SetFillStyle(0);
      Legend->AddEntry(&HA1, "Default", "l");
      Legend->AddEntry(&HA2, "Default (born)", "l");
      Legend->AddEntry(&HB1, "m_{b} = m_{c} = 0.19", "l");
      Legend->AddEntry(&HB2, "m_{b} = m_{c} = 0.19 (born)", "l");
      Legend->AddEntry(&HC1, "m_{q} = 0.19", "l");
      Legend->AddEntry(&HC2, "m_{q} = 0.19 (born)", "l");

      TCanvas C("C", "C", 1024, 1024);

      HA1.Draw();
      HA2.Draw("same");
      HB1.Draw("same");
      HB2.Draw("same");
      HC1.Draw("same");
      HC2.Draw("same");
      Legend->Draw();

      C.SaveAs(Form("ProphecyComparison%02dLinear.png", i + 1));
      C.SaveAs(Form("ProphecyComparison%02dLinear.C", i + 1));
      C.SaveAs(Form("ProphecyComparison%02dLinear.eps", i + 1));
      C.SaveAs(Form("ProphecyComparison%02dLinear.pdf", i + 1));

      // HA1.SetMinimum(0.0001);
      // C.SetLogy();
      // C.SaveAs(Form("ProphecyComparison%dLog.png", i + 1));
      // C.SaveAs(Form("ProphecyComparison%dLog.C", i + 1));
      // C.SaveAs(Form("ProphecyComparison%dLog.eps", i + 1));
      // C.SaveAs(Form("ProphecyComparison%dLog.pdf", i + 1));
   }

   FC2.Close();
   FC1.Close();
   FB2.Close();
   FB1.Close();
   FA2.Close();
   FA1.Close();

   return 0;
}


