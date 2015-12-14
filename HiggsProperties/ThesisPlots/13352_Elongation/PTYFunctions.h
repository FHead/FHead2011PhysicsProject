// #define PTY_USE_TOY
#define PTY_USE_MADGRAPH_ROBERTO12261

// Toy densities
double ToyYDensity(double y);
double ToyPTDensity(double pt);
double ToyPTYDensity(double pt, double y, double s = 125 * 125);

// Madgraph densities
double MadgraphLogXDensity_Roberto12261(double x);
double MadgraphTotalDensity_Roberto12261(double pt, double y, double s);

// Universal entrance point
double GetPTYDensity(double pt, double y, double s = 125 * 125);

