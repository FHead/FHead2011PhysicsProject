#include <cmath>
using namespace std;

#define PI 3.1415926535897932384626433832795028847971

class Vector4
{
private:
   double Positions[4];
public:
   Vector4();
   Vector4(double t, double x, double y, double z);
   ~Vector4();
   double &operator [](int index);
   Vector4 operator -();
   Vector4 operator +(Vector4 other);
   Vector4 operator *(double number);
   double Magnitude();
   double Magnitude2();
   double Theta();
   double Eta();
   double Phi();
   double PT();
   Vector4 BoostX(double beta);
   Vector4 RotateX(double angle);
   Vector4 RotateY(double angle);
   Vector4 RotateZ(double angle);
   Vector4 Boost(Vector4 Direction, double beta);
};

Vector4::Vector4()
{
   Positions[0] = 0;
   Positions[1] = 0;
   Positions[2] = 0;
   Positions[3] = 0;
}

Vector4::Vector4(double t, double x, double y, double z)
{
   Positions[0] = t;
   Positions[1] = x;
   Positions[2] = y;
   Positions[3] = z;
}

Vector4::~Vector4()
{
}

double &Vector4::operator [](int index)
{
   if(index < 4 && index >= 0)
      return Positions[index];
   return Positions[0];
}

Vector4 Vector4::operator -()
{
   Vector4 answer;

   answer[0] = -Positions[0];
   answer[1] = -Positions[1];
   answer[2] = -Positions[2];
   answer[3] = -Positions[3];

   return answer;
}

Vector4 Vector4::operator +(Vector4 other)
{
   Vector4 answer;

   answer[0] = Positions[0] + other[0];
   answer[1] = Positions[1] + other[1];
   answer[2] = Positions[2] + other[2];
   answer[3] = Positions[3] + other[3];

   return answer;
}

Vector4 Vector4::operator *(double number)
{
   Vector4 answer;

   answer[0] = Positions[0] * number;
   answer[1] = Positions[1] * number;
   answer[2] = Positions[2] * number;
   answer[3] = Positions[3] * number;

   return answer;
}

double Vector4::Magnitude()
{
   return sqrt(Magnitude2());
}

double Vector4::Magnitude2()
{
   return Positions[0] * Positions[0] - Positions[1] * Positions[1] - Positions[2] * Positions[2] - Positions[3] * Positions[3];
}

double Vector4::Theta()
{
   double length = sqrt(Positions[1] * Positions[1] + Positions[2] * Positions[2] + Positions[3] * Positions[3]);

   if(length < 1e-10)
      return 0;

   return acos(Positions[3] / length);
}

double Vector4::Eta()
{
   return -log(tan(Theta() / 2));
}

double Vector4::Phi()
{
   double xy_length = sqrt(Positions[1] * Positions[1] + Positions[2] * Positions[2]);

   if(xy_length < 1e-10)
      return 0;

   if(Positions[2] > 0)   // upper hemisphere in xy plane
      return acos(Positions[1] / xy_length);
   else   // lower hepmisphere
      return 2 * PI - acos(Positions[1] / xy_length);

   return 0;
}

double Vector4::PT()
{
   return sqrt(Positions[1] * Positions[1] + Positions[2] * Positions[2]);
}

Vector4 Vector4::BoostX(double beta)
{
   double gamma = 1 / sqrt(1 - beta * beta);

   Vector4 result;

   result[0] = gamma * Positions[0] - beta * gamma * Positions[1];
   result[1] = -beta * gamma * Positions[0] + gamma * Positions[1];
   result[2] = Positions[2];
   result[3] = Positions[3];

   return result;
}

Vector4 Vector4::RotateX(double angle)
{
   Vector4 result;

   result[0] = Positions[0];
   result[1] = Positions[1];
   result[2] = cos(angle) * Positions[2] + sin(angle) * Positions[3];
   result[3] = sin(angle) * Positions[2] - cos(angle) * Positions[3];

   return result;
}

Vector4 Vector4::RotateY(double angle)
{
   Vector4 result;

   result[0] = Positions[0];
   result[1] = sin(angle) * Positions[3] - cos(angle) * Positions[1];
   result[2] = Positions[2];
   result[3] = cos(angle) * Positions[3] + sin(angle) * Positions[1];

   return result;
}

Vector4 Vector4::RotateZ(double angle)
{
   Vector4 result;

   result[0] = Positions[0];
   result[1] = cos(angle) * Positions[1] + sin(angle) * Positions[2];
   result[2] = sin(angle) * Positions[1] - cos(angle) * Positions[2];
   result[3] = Positions[3];

   return result;
}

Vector4 Vector4::Boost(Vector4 Direction, double beta)
{
   double phi = Direction.Phi();
   double theta = Direction.Theta();

   // rotate z by -phi => to x-z plane
   // then rotate y by pi/2-theta => to x axis
   // ...then boost along x direction
   // then rotate back

   return RotateZ(-phi).RotateY(PI / 2 - theta).BoostX(beta).RotateY(-PI / 2 + theta).RotateZ(phi);
}




