#include <map>
#include <vector>
#include <cmath>

class JetImage;
class JetMode;
std::pair<double, double> GetCoefficient(JetImage &Image, int KX, int KY);
JetMode Transform(JetImage &Image, int KeepMinX = -1000, int KeepMaxX = 1000, int KeepMinY = -1000, int KeepMaxY = 1000);
JetImage Transform(JetMode &Mode);
double GetPhase(double x, double y);
double GetSize(double x, double y);

class JetImage
{
public:
   double **Data;
   int Size;
public:
   JetImage();
   JetImage(int size);
   ~JetImage();
   void Initialize(int size);
   JetImage operator +(JetImage &other);
   JetImage operator -(JetImage &other);
   JetImage &operator =(JetImage &other);
};

class JetMode
{
public:
   double **Real;
   double **Imag;
   int Size;
public:
   JetMode();
   JetMode(int size);
   ~JetMode();
   void Initialize(int size);
   JetMode operator +(JetMode &other);
   JetMode operator -(JetMode &other);
   JetMode &operator =(JetMode &other);
};

