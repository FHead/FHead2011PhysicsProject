#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   gStyle->SetErrorX(0);

   double Bins[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 20, 23, 27, 30, 35, 40, 45, 57, 72, 90, 120, 150, 200, 300, 400, 550, 750, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000};

   TH1D H1("H1", ";;", 51, Bins);
   TH1D H2("H2", ";;", 51, Bins);
   TH1D H3("H3", ";;", 51, Bins);
   TH1D H4("H4", ";;", 51, Bins);

   H1.SetBinContent(3,1.011239);
   H1.SetBinContent(4,0.8276024);
   H1.SetBinContent(5,0.88954);
   H1.SetBinContent(6,0.9684128);
   H1.SetBinContent(7,0.9892469);
   H1.SetBinContent(8,0.99654);
   H1.SetBinContent(9,0.9994989);
   H1.SetBinContent(10,1.000205);
   H1.SetBinContent(11,1.000187);
   H1.SetBinContent(12,0.9997671);
   H1.SetBinContent(13,0.9992155);
   H1.SetBinContent(14,0.9990993);
   H1.SetBinContent(15,0.998794);
   H1.SetBinContent(16,0.9988946);
   H1.SetBinContent(17,0.9991037);
   H1.SetBinContent(18,0.9992833);
   H1.SetBinContent(19,0.999297);
   H1.SetBinContent(20,0.9993143);
   H1.SetBinContent(21,0.9995353);
   H1.SetBinContent(22,0.9996549);
   H1.SetBinContent(23,1.000333);
   H1.SetBinContent(24,0.9997815);
   H1.SetBinContent(25,1.000114);
   H1.SetBinContent(26,1.000398);
   H1.SetBinContent(27,0.9998692);
   H1.SetBinContent(28,1.000747);
   H1.SetBinContent(29,1.00008);
   H1.SetBinContent(30,1.000004);
   H1.SetBinContent(31,0.9998756);
   H1.SetBinContent(32,0.9948374);
   H1.SetBinContent(33,0.9998283);
   H1.SetBinContent(35,0.9998337);
   H1.SetBinContent(37,0.9999295);
   H1.SetBinContent(38,1.000069);
   H1.SetBinContent(39,0.9996625);
   H1.SetBinContent(40,0.9957941);
   H1.SetBinContent(41,0.9915035);
   H1.SetBinContent(42,1.001295);
   H1.SetBinError(3,0.008761183);
   H1.SetBinError(4,0.007602436);
   H1.SetBinError(5,0.009540033);
   H1.SetBinError(6,0.008412813);
   H1.SetBinError(7,0.009246883);
   H1.SetBinError(8,0.006539928);
   H1.SetBinError(9,0.009498878);
   H1.SetBinError(10,0.009795201);
   H1.SetBinError(11,0.009812761);
   H1.SetBinError(12,0.009767038);
   H1.SetBinError(13,0.009215496);
   H1.SetBinError(14,0.009099332);
   H1.SetBinError(15,0.008793934);
   H1.SetBinError(16,0.008894605);
   H1.SetBinError(17,0.009103678);
   H1.SetBinError(18,0.009283239);
   H1.SetBinError(19,0.009296958);
   H1.SetBinError(20,0.00931429);
   H1.SetBinError(21,0.009535264);
   H1.SetBinError(22,0.009654875);
   H1.SetBinError(23,0.009667307);
   H1.SetBinError(24,0.009781526);
   H1.SetBinError(25,0.009885838);
   H1.SetBinError(26,0.009601703);
   H1.SetBinError(27,0.00986921);
   H1.SetBinError(28,0.009252608);
   H1.SetBinError(29,0.00992032);
   H1.SetBinError(30,0.009996312);
   H1.SetBinError(31,0.009875628);
   H1.SetBinError(32,0.005162576);
   H1.SetBinError(33,0.009828282);
   H1.SetBinError(35,0.009833725);
   H1.SetBinError(37,0.009929497);
   H1.SetBinError(38,0.009930617);
   H1.SetBinError(39,0.009662437);
   H1.SetBinError(40,0.005794099);
   H1.SetBinError(41,0.008496529);
   H1.SetBinError(42,0.008704753);

   H2.SetBinContent(3,0.9939659);
   H2.SetBinContent(4,0.8114594);
   H2.SetBinContent(5,0.758729);
   H2.SetBinContent(6,0.9258147);
   H2.SetBinContent(7,0.9654759);
   H2.SetBinContent(8,0.9820747);
   H2.SetBinContent(9,0.9922357);
   H2.SetBinContent(10,0.996399);
   H2.SetBinContent(11,0.9986368);
   H2.SetBinContent(12,1.000002);
   H2.SetBinContent(13,1.000339);
   H2.SetBinContent(14,1.000289);
   H2.SetBinContent(15,1.000005);
   H2.SetBinContent(16,0.99967);
   H2.SetBinContent(17,0.9991758);
   H2.SetBinContent(18,0.9987529);
   H2.SetBinContent(19,0.9986432);
   H2.SetBinContent(20,0.9984126);
   H2.SetBinContent(21,0.9982752);
   H2.SetBinContent(22,0.9990367);
   H2.SetBinContent(23,0.9995245);
   H2.SetBinContent(24,0.9992907);
   H2.SetBinContent(25,0.9994313);
   H2.SetBinContent(26,0.999614);
   H2.SetBinContent(27,0.9993663);
   H2.SetBinContent(28,0.999202);
   H2.SetBinContent(29,0.9994736);
   H2.SetBinContent(30,0.9991907);
   H2.SetBinContent(31,0.9992032);
   H2.SetBinContent(32,0.9956378);
   H2.SetBinContent(33,0.9993293);
   H2.SetBinContent(34,0.9995781);
   H2.SetBinContent(35,0.9996012);
   H2.SetBinContent(36,0.9985198);
   H2.SetBinContent(37,1.013934);
   H2.SetBinError(3,0.006034163);
   H2.SetBinError(4,0.008540622);
   H2.SetBinError(5,0.008728961);
   H2.SetBinError(6,0.005814693);
   H2.SetBinError(7,0.00547585);
   H2.SetBinError(8,0.007925317);
   H2.SetBinError(9,0.00776435);
   H2.SetBinError(10,0.006398957);
   H2.SetBinError(11,0.008636765);
   H2.SetBinError(12,0.009998352);
   H2.SetBinError(13,0.009661504);
   H2.SetBinError(14,0.00971141);
   H2.SetBinError(15,0.009995349);
   H2.SetBinError(16,0.009670025);
   H2.SetBinError(17,0.009175859);
   H2.SetBinError(18,0.008752871);
   H2.SetBinError(19,0.008643225);
   H2.SetBinError(20,0.008412607);
   H2.SetBinError(21,0.008275233);
   H2.SetBinError(22,0.009036661);
   H2.SetBinError(23,0.009524529);
   H2.SetBinError(24,0.009290716);
   H2.SetBinError(25,0.009431325);
   H2.SetBinError(26,0.009614004);
   H2.SetBinError(27,0.009366263);
   H2.SetBinError(28,0.009201984);
   H2.SetBinError(29,0.009473549);
   H2.SetBinError(30,0.009190699);
   H2.SetBinError(31,0.009203213);
   H2.SetBinError(32,0.005637835);
   H2.SetBinError(33,0.009329324);
   H2.SetBinError(34,0.00957805);
   H2.SetBinError(35,0.009601265);
   H2.SetBinError(36,0.008519773);
   H2.SetBinError(37,0.006066316);

   H3.SetBinContent(3,0.9460435);
   H3.SetBinContent(4,0.7729586);
   H3.SetBinContent(5,0.6518129);
   H3.SetBinContent(6,0.5714717);
   H3.SetBinContent(7,0.525705);
   H3.SetBinContent(8,0.551623);
   H3.SetBinContent(9,0.71207);
   H3.SetBinContent(10,0.8571922);
   H3.SetBinContent(11,0.9284886);
   H3.SetBinContent(12,0.9621984);
   H3.SetBinContent(13,0.9843679);
   H3.SetBinContent(14,0.9947068);
   H3.SetBinContent(15,1.008198);
   H3.SetBinContent(16,1.014471);
   H3.SetBinContent(17,1.013135);
   H3.SetBinContent(18,1.006931);
   H3.SetBinContent(19,0.9998709);
   H3.SetBinContent(20,0.995456);
   H3.SetBinContent(21,0.9940376);
   H3.SetBinContent(22,0.9939432);
   H3.SetBinContent(23,0.9957476);
   H3.SetBinContent(24,0.9953599);
   H3.SetBinContent(25,0.9994319);
   H3.SetBinContent(26,0.9966508);
   H3.SetBinContent(27,0.997713);
   H3.SetBinContent(28,0.9976971);
   H3.SetBinContent(29,0.998143);
   H3.SetBinContent(30,0.9979899);
   H3.SetBinContent(31,0.9986029);
   H3.SetBinContent(32,1.001371);
   H3.SetBinContent(33,0.9995307);
   H3.SetBinError(3,0.00604349);
   H3.SetBinError(4,0.007041368);
   H3.SetBinError(5,0.008187077);
   H3.SetBinError(6,0.008528308);
   H3.SetBinError(7,0.005704965);
   H3.SetBinError(8,0.008377038);
   H3.SetBinError(9,0.007930035);
   H3.SetBinError(10,0.007192155);
   H3.SetBinError(11,0.008488562);
   H3.SetBinError(12,0.007801599);
   H3.SetBinError(13,0.005632097);
   H3.SetBinError(14,0.005293166);
   H3.SetBinError(15,0.008198171);
   H3.SetBinError(16,0.005528744);
   H3.SetBinError(17,0.006865194);
   H3.SetBinError(18,0.006931022);
   H3.SetBinError(19,0.009870876);
   H3.SetBinError(20,0.005456026);
   H3.SetBinError(21,0.005962419);
   H3.SetBinError(22,0.006056875);
   H3.SetBinError(23,0.005747572);
   H3.SetBinError(24,0.005359925);
   H3.SetBinError(25,0.0094319);
   H3.SetBinError(26,0.006650764);
   H3.SetBinError(27,0.007712978);
   H3.SetBinError(28,0.007697088);
   H3.SetBinError(29,0.008142969);
   H3.SetBinError(30,0.007989865);
   H3.SetBinError(31,0.008602907);
   H3.SetBinError(32,0.008628861);
   H3.SetBinError(33,0.009530717);

   H4.SetBinContent(3,1.067925);
   H4.SetBinContent(4,0.8689815);
   H4.SetBinContent(5,0.7362052);
   H4.SetBinContent(6,0.7090341);
   H4.SetBinContent(7,0.7422896);
   H4.SetBinContent(8,0.7284588);
   H4.SetBinContent(9,0.7146434);
   H4.SetBinContent(10,0.7051918);
   H4.SetBinContent(11,0.7108447);
   H4.SetBinContent(12,0.7513416);
   H4.SetBinContent(13,0.9318612);
   H4.SetBinContent(14,1.01083);
   H4.SetBinContent(15,1.024222);
   H4.SetBinContent(16,1.019347);
   H4.SetBinContent(17,1.014362);
   H4.SetBinContent(18,1.009467);
   H4.SetBinContent(19,1.005071);
   H4.SetBinContent(20,1.003476);
   H4.SetBinContent(21,1.002283);
   H4.SetBinContent(22,1.001987);
   H4.SetBinContent(23,1.002257);
   H4.SetBinContent(24,1.00243);
   H4.SetBinContent(25,1.001758);
   H4.SetBinContent(26,1.002559);
   H4.SetBinContent(27,1.003079);
   H4.SetBinContent(28,1.003819);
   H4.SetBinContent(29,1.008183);
   H4.SetBinContent(30,1.011125);
   H4.SetBinContent(31,1.001509);
   H4.SetBinError(3,0.00792456);
   H4.SetBinError(4,0.008981477);
   H4.SetBinError(5,0.006205157);
   H4.SetBinError(6,0.009034103);
   H4.SetBinError(7,0.007710415);
   H4.SetBinError(8,0.008458824);
   H4.SetBinError(9,0.005356565);
   H4.SetBinError(10,0.005191777);
   H4.SetBinError(11,0.009155316);
   H4.SetBinError(12,0.00865842);
   H4.SetBinError(13,0.008138761);
   H4.SetBinError(14,0.009169611);
   H4.SetBinError(15,0.005778469);
   H4.SetBinError(16,0.009346564);
   H4.SetBinError(17,0.005638431);
   H4.SetBinError(18,0.009466747);
   H4.SetBinError(19,0.005071437);
   H4.SetBinError(20,0.006524232);
   H4.SetBinError(21,0.007717128);
   H4.SetBinError(22,0.008012516);
   H4.SetBinError(23,0.00774317);
   H4.SetBinError(24,0.00756962);
   H4.SetBinError(25,0.008242098);
   H4.SetBinError(26,0.007440767);
   H4.SetBinError(27,0.006920998);
   H4.SetBinError(28,0.006180612);
   H4.SetBinError(29,0.008182801);
   H4.SetBinError(30,0.008874671);
   H4.SetBinError(31,0.008490908);

   for(int i = 1; i <= 14; i++)
   {
      H1.SetBinContent(i, 0);
      H1.SetBinError(i, 0);
      H2.SetBinContent(i, 0);
      H2.SetBinError(i, 0);
      H3.SetBinContent(i, 0);
      H3.SetBinError(i, 0);
      H4.SetBinContent(i, 0);
      H4.SetBinError(i, 0);
   }

   H1.SetLineColor(kBlack);
   H1.SetMarkerColor(kBlack);
   H1.SetMarkerStyle(20);
   H1.SetLineWidth(2);
   H1.SetMarkerSize(2.10);
   
   H2.SetLineColor(kBlue);
   H2.SetMarkerColor(kBlue);
   H2.SetMarkerStyle(24);
   H2.SetLineWidth(2);
   H2.SetMarkerSize(2.06);
   
   H3.SetLineColor(kRed);
   H3.SetMarkerColor(kRed);
   H3.SetMarkerStyle(22);
   H3.SetLineWidth(2);
   H3.SetMarkerSize(2.03);
   
   H4.SetLineColor(kMagenta);
   H4.SetMarkerColor(kMagenta);
   H4.SetMarkerStyle(26);
   H4.SetLineWidth(2);
   H4.SetMarkerSize(2.00);

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";p_{T}^{Ref} (GeV);Response", 100, 15, 5000, 100, 0.95, 1.05);
   HWorld.SetStats(0);

   HWorld.GetXaxis()->SetLabelSize(0.04);
   HWorld.GetXaxis()->SetTitleSize(0.04);
   HWorld.GetXaxis()->SetMoreLogLabels();
   HWorld.GetXaxis()->SetNoExponent();

   HWorld.GetYaxis()->SetLabelSize(0.04);
   HWorld.GetYaxis()->SetTitleSize(0.04);
   HWorld.GetYaxis()->SetTitleOffset(1.25);

   HWorld.Draw("");

   TGraph GLine;
   GLine.SetPoint(0, 0, 0.99);
   GLine.SetPoint(1, 10000, 0.99);
   GLine.SetPoint(2, 10000, 1.01);
   GLine.SetPoint(3, 0, 1.01);
   GLine.SetLineStyle(kDotted);
   GLine.Draw("l");

   H1.Draw("same");
   H2.Draw("same");
   H3.Draw("same");
   H4.Draw("same");

   TLegend Legend(0.52, 0.15, 0.8, 0.37);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.040);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&H1, "|#eta| < 1.3", "pl");
   Legend.AddEntry(&H2, "1.3 < |#eta| < 2.5", "pl");
   Legend.AddEntry(&H3, "2.5 < |#eta| < 3.0", "pl");
   Legend.AddEntry(&H4, "3.0 < |#eta| < 5.0", "pl");
   Legend.Draw();

   TLatex Latex;
   Latex.SetNDC();

   Latex.SetTextFont(42);
   Latex.SetTextSize(0.045);
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.82, 0.84, "2016 JES: QCD Monte Carlo");
   Latex.DrawLatex(0.82, 0.78, "Anti-k_{T} R = 0.4, PF + PUPPI");
   
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.045);
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.85, 0.925, "13 TeV");
   
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.045);
   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.925, "#bf{CMS} #it{Simulation Preliminary}");

   Canvas.SetLogx();
   Canvas.SaveAs("Puppi.pdf");

   return 0;
}



