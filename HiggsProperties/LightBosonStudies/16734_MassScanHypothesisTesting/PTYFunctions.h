//---------------------------------------------------------------------------
// #define PTY_USE_TOY
// #define PTY_USE_MADGRAPH_ROBERTO12261
// #define PTY_USE_SI12621
// #define PTY_USE_SI13142
#define PTY_USE_LATEST
//---------------------------------------------------------------------------
// Toy densities
double ToyYDensity(double y);
double ToyPTDensity(double pt);
double ToyPTYDensity(double pt, double y, double s = 125 * 125);
double JustFlatPTYDensity(double pt, double y, double s);
//---------------------------------------------------------------------------
// Madgraph densities
double MadgraphLogXDensity_Roberto12261(double x);
double MadgraphTotalDensity_Roberto12261(double pt, double y, double s);
//---------------------------------------------------------------------------
// Densities from Si from POWHEG from beginning of 2014
double GetPTDensity8TeVSignal_Si12621(double pt, double s);
double GetYDensity8TeVSignal_Si12621(double y);
double GetPTYDensity8TeVSignal_Si12621(double pt, double y, double s = 125 * 125);
double GetPTOverMDensity8TeVBackgroundUUbar2e2mu_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundDDbar2e2mu_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGU2e2mu_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGUbar2e2mu_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGD2e2mu_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGDbar2e2mu_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundUUbar4e_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundDDbar4e_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGU4e_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGUbar4e_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGD4e_Si12624(double pt, double s);
double GetPTOverMDensity8TeVBackgroundGDbar4e_Si12624(double pt, double s);
double GetYDensity8TeVBackgroundUUbar2e2mu_Si12624(double y);
double GetYDensity8TeVBackgroundDDbar2e2mu_Si12624(double y);
double GetYDensity8TeVBackgroundGU2e2mu_Si12624(double y);
double GetYDensity8TeVBackgroundGUbar2e2mu_Si12624(double y);
double GetYDensity8TeVBackgroundGD2e2mu_Si12624(double y);
double GetYDensity8TeVBackgroundGDbar2e2mu_Si12624(double y);
double GetYDensity8TeVBackgroundUUbar4e_Si12624(double y);
double GetYDensity8TeVBackgroundDDbar4e_Si12624(double y);
double GetYDensity8TeVBackgroundGU4e_Si12624(double y);
double GetYDensity8TeVBackgroundGUbar4e_Si12624(double y);
double GetYDensity8TeVBackgroundGD4e_Si12624(double y);
double GetYDensity8TeVBackgroundGDbar4e_Si12624(double y);
double GetMDensityConditionalOnY8TeVBackgroundUUbar2e2mu_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundDDbar2e2mu_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGU2e2mu_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGUbar2e2mu_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGD2e2mu_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGDbar2e2mu_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundUUbar4e_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundDDbar4e_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGU4e_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGUbar4e_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGD4e_Si12624(double s, double y);
double GetMDensityConditionalOnY8TeVBackgroundGDbar4e_Si12624(double s, double y);
double GetPTYDensity8TeVBackgroundUUbar2e2mu_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundDDbar2e2mu_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGU2e2mu_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGUbar2e2mu_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGD2e2mu_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGDbar2e2mu_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundUUbar4e_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundDDbar4e_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGU4e_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGUbar4e_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGD4e_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundGDbar4e_Si12624(double pt, double y, double s);
double GetPTYDensity8TeVBackgroundCombinedUUbar2e2mu_Si12624(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundCombinedDDbar2e2mu_Si12624(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundCombinedUUbar4e_Si12624(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundCombinedDDbar4e_Si12624(double pt, double y, double s = 125 * 125);
//---------------------------------------------------------------------------
// Densities from Si on (1)3142
double GetPTDensity8TeVSignal_Si13142(double pt, double s);
double GetYDensity8TeVSignal_Si13142(double y);
double GetPTYDensity8TeVSignal_Si13142(double pt, double y, double s = 125 * 125);
double GetPTDensity7TeVSignal_Si13142(double pt, double s);
double GetYDensity7TeVSignal_Si13142(double y);
double GetPTYDensity7TeVSignal_Si13142(double pt, double y, double s = 125 * 125);
double GetPTOverMDensity7TeVBackgroundUUbar2e2mu_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundDDbar2e2mu_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGU2e2mu_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGUbar2e2mu_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGD2e2mu_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGDbar2e2mu_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundUUbar4e_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundDDbar4e_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGU4e_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGUbar4e_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGD4e_Si13142(double pt, double s);
double GetPTOverMDensity7TeVBackgroundGDbar4e_Si13142(double pt, double s);
double GetYDensity7TeVBackgroundUUbar2e2mu_Si13142(double y);
double GetYDensity7TeVBackgroundDDbar2e2mu_Si13142(double y);
double GetYDensity7TeVBackgroundGU2e2mu_Si13142(double y);
double GetYDensity7TeVBackgroundGUbar2e2mu_Si13142(double y);
double GetYDensity7TeVBackgroundGD2e2mu_Si13142(double y);
double GetYDensity7TeVBackgroundGDbar2e2mu_Si13142(double y);
double GetYDensity7TeVBackgroundUUbar4e_Si13142(double y);
double GetYDensity7TeVBackgroundDDbar4e_Si13142(double y);
double GetYDensity7TeVBackgroundGU4e_Si13142(double y);
double GetYDensity7TeVBackgroundGUbar4e_Si13142(double y);
double GetYDensity7TeVBackgroundGD4e_Si13142(double y);
double GetYDensity7TeVBackgroundGDbar4e_Si13142(double y);
double GetMDensityConditionalOnY7TeVBackgroundUUbar2e2mu_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundDDbar2e2mu_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGU2e2mu_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGUbar2e2mu_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGD2e2mu_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGDbar2e2mu_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundUUbar4e_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundDDbar4e_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGU4e_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGUbar4e_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGD4e_Si13142(double s, double y);
double GetMDensityConditionalOnY7TeVBackgroundGDbar4e_Si13142(double s, double y);
double GetPTYDensity7TeVBackgroundUUbar2e2mu_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundDDbar2e2mu_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGU2e2mu_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGUbar2e2mu_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGD2e2mu_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGDbar2e2mu_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundUUbar4e_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundDDbar4e_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGU4e_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGUbar4e_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGD4e_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundGDbar4e_Si13142(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundCombinedUUbar2e2mu_Si13142(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundCombinedDDbar2e2mu_Si13142(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundCombinedUUbar4e_Si13142(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundCombinedDDbar4e_Si13142(double pt, double y, double s = 125 * 125);
//---------------------------------------------------------------------------
// CTEQ6l1 densities
double GetUxDensity_MZ_CTEQ6l1_13432(double x);
double GetDxDensity_MZ_CTEQ6l1_13432(double x);
double GetSxDensity_MZ_CTEQ6l1_13432(double x);
double GetCxDensity_MZ_CTEQ6l1_13432(double x);
double GetBxDensity_MZ_CTEQ6l1_13432(double x);
double GetUBarxDensity_MZ_CTEQ6l1_13432(double x);
double GetDBarxDensity_MZ_CTEQ6l1_13432(double x);
double GetSBarxDensity_MZ_CTEQ6l1_13432(double x);
double GetCBarxDensity_MZ_CTEQ6l1_13432(double x);
double GetBBarxDensity_MZ_CTEQ6l1_13432(double x);
double GetGxDensity_MZ_CTEQ6l1_13432(double x);
double GetFxDensity_MZ_CTEQ6l1_13432(double x, int PID);
double GetUxDensity_2_CTEQ6l1_13432(double x);
double GetDxDensity_2_CTEQ6l1_13432(double x);
double GetSxDensity_2_CTEQ6l1_13432(double x);
double GetCxDensity_2_CTEQ6l1_13432(double x);
double GetBxDensity_2_CTEQ6l1_13432(double x);
double GetUBarxDensity_2_CTEQ6l1_13432(double x);
double GetDBarxDensity_2_CTEQ6l1_13432(double x);
double GetSBarxDensity_2_CTEQ6l1_13432(double x);
double GetCBarxDensity_2_CTEQ6l1_13432(double x);
double GetBBarxDensity_2_CTEQ6l1_13432(double x);
double GetGxDensity_2_CTEQ6l1_13432(double x);
double GetFxDensity_2_CTEQ6l1_13432(double x, int PID);
//---------------------------------------------------------------------------
double GetPTYDensity_MZ_CTEQ6l1_13432(int PID1, int PID2, double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityUUbar_MZ_CTEQ6l1_13432(double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityDDbar_MZ_CTEQ6l1_13432(double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityGG_MZ_CTEQ6l1_13432(double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityUUbar_MZ_CTEQ6l1_14TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityDDbar_MZ_CTEQ6l1_14TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityGG_MZ_CTEQ6l1_14TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityUUbar_MZ_CTEQ6l1_13TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityDDbar_MZ_CTEQ6l1_13TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityGG_MZ_CTEQ6l1_13TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensity_2_CTEQ6l1_13432(int PID1, int PID2, double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityUUbar_2_CTEQ6l1_13432(double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityDDbar_2_CTEQ6l1_13432(double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityGG_2_CTEQ6l1_13432(double pt, double y, double s = 125 * 125, double S = 14000 * 14000);
double GetPTYDensityUUbar_2_CTEQ6l1_14TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityDDbar_2_CTEQ6l1_14TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityGG_2_CTEQ6l1_14TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityUUbar_2_CTEQ6l1_13TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityDDbar_2_CTEQ6l1_13TeV_13432(double pt, double y, double s = 125 * 125);
double GetPTYDensityGG_2_CTEQ6l1_13TeV_13432(double pt, double y, double s = 125 * 125);
//---------------------------------------------------------------------------
// Tofu
double GetTofuDensity(double pt, double y, double s = 125 * 125);
//---------------------------------------------------------------------------
// Universal entrance point
double GetPTYDensity(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVSignal(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVSignal(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUUbar2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarU2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbar2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarD2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbar2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarU2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbar2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarD2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUUbar4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarU4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbar4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarD4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbar4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarU4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbar4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarD4e(double pt, double y, double s = 125 * 125);

double GetPTYDensity7TeVSignalHard(double pt, double y, double s);
double GetPTYDensity8TeVSignalHard(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundUUbarHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDHard2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUUbarHard4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUHard4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarHard4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDHard4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarHard4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUHard4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarHard4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDHard4e(double pt, double y, double s = 125 * 125);

double GetPTYDensity7TeVSignalSoft(double pt, double y, double s);
double GetPTYDensity8TeVSignalSoft(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundUUbarSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDSoft2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUUbarSoft4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUSoft4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarSoft4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDSoft4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarSoft4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUSoft4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarSoft4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDSoft4e(double pt, double y, double s = 125 * 125);

double GetPTYDensity7TeVSignalForward(double pt, double y, double s);
double GetPTYDensity8TeVSignalForward(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundUUbarForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDForward2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUUbarForward4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUForward4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarForward4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDForward4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarForward4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUForward4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarForward4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDForward4e(double pt, double y, double s = 125 * 125);

double GetPTYDensity7TeVSignalCentral(double pt, double y, double s);
double GetPTYDensity8TeVSignalCentral(double pt, double y, double s);
double GetPTYDensity7TeVBackgroundUUbarCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDCentral2e2mu(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUUbarCentral4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundUbarUCentral4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDDbarCentral4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity7TeVBackgroundDbarDCentral4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUUbarCentral4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundUbarUCentral4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDDbarCentral4e(double pt, double y, double s = 125 * 125);
double GetPTYDensity8TeVBackgroundDbarDCentral4e(double pt, double y, double s = 125 * 125);
//---------------------------------------------------------------------------
// Utility functions
double PDFLinearInterpolate(const double x, const int BinCount,
   const double Min, const double Max, const double *Data);
//---------------------------------------------------------------------------

