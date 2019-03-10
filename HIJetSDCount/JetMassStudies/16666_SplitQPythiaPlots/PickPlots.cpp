#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

int main();
void PickFile(TFile &File, string FileName, string Tag, bool SD0);

int main()
{
   TFile File0("PickedPlots_SD0.root", "RECREATE");
   PickFile(File0, "Plots_Vac_S_N.root", "JewelVacS", true);
   PickFile(File0, "Plots_Vac_SB_N.root", "JewelVacSB", true);
   PickFile(File0, "Plots_Off_S_N.root", "JewelOffS", true);
   PickFile(File0, "Plots_On_S_Y.root", "JewelOnS", true);
   PickFile(File0, "Plots_Off_SB_N.root", "JewelOffSB", true);
   PickFile(File0, "Plots_On_SB_Y.root", "JewelOnSB", true);
   PickFile(File0, "Plots_qhat1_S_N.root", "QPythiaMedS", true);
   PickFile(File0, "Plots_qhat1_SB_N.root", "QPythiaMedSB", true);
   PickFile(File0, "Plots_vac_S_N.root", "QPythiaVacS", true);
   PickFile(File0, "Plots_vac_SB_N.root", "QPythiaVacSB", true);
   File0.Close();

   TFile File7("PickedPlots_SD7.root", "RECREATE");
   PickFile(File7, "Plots_Vac_S_N.root", "JewelVacS", false);
   PickFile(File7, "Plots_Vac_SB_N.root", "JewelVacSB", false);
   PickFile(File7, "Plots_Off_S_N.root", "JewelOffS", false);
   PickFile(File7, "Plots_On_S_Y.root", "JewelOnS", false);
   PickFile(File7, "Plots_Off_SB_N.root", "JewelOffSB", false);
   PickFile(File7, "Plots_On_SB_Y.root", "JewelOnSB", false);
   PickFile(File7, "Plots_qhat1_S_N.root", "QPythiaMedS", false);
   PickFile(File7, "Plots_qhat1_SB_N.root", "QPythiaMedSB", false);
   PickFile(File7, "Plots_vac_S_N.root", "QPythiaVacS", false);
   PickFile(File7, "Plots_vac_SB_N.root", "QPythiaVacSB", false);
   File7.Close();

   return 0;
}

void PickFile(TFile &File, string FileName, string Tag, bool SD0)
{
   TFile InputFile(FileName.c_str());

   File.cd();
   for(int i = 0; i <= 5; i++)
      InputFile.Get(Form("HSD%dCSPT%d", SD0 ? 0 : 7, i))->Clone(Form("%s_C0PT%d", Tag.c_str(), i))->Write();

   InputFile.Close();
}

