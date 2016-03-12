#include <iostream>
#include <algorithm>
using namespace std;

class Particle;
int main();

class Particle
{
public:
   int ID;
   double px;
   double py;
   double pz;
public:
   Particle &operator =(const Particle &other)
   {
      ID = other.ID;
      px = other.px;
      py = other.py;
      pz = other.pz;
      return *this;
   }
};

int main()
{
   while(cin)
   {
      Particle P1, P2, P3, P4;

      cin >> P1.ID >> P1.px >> P1.py >> P1.pz;
      cin >> P2.ID >> P2.px >> P2.py >> P2.pz;
      cin >> P3.ID >> P3.px >> P3.py >> P3.pz;
      cin >> P4.ID >> P4.px >> P4.py >> P4.pz;

      if(P1.ID < 0)
      {
         if(P2.ID > 0)        swap(P1, P2);
         else if(P4.ID > 0)   swap(P1, P4);
      }
      if(P3.ID < 0)
      {
         if(P2.ID > 0)        swap(P2, P3);
         else if(P4.ID > 0)   swap(P3, P4);
      }

      if(P1.ID % 2 == 0)      swap(P1, P3);
      if(P2.ID % 2 != 0)      swap(P2, P4);

      cout << P1.ID << " " << P1.px << " " << P1.py << " " << P1.pz << endl;
      cout << P2.ID << " " << P2.px << " " << P2.py << " " << P2.pz << endl;
      cout << P3.ID << " " << P3.px << " " << P3.py << " " << P3.pz << endl;
      cout << P4.ID << " " << P4.px << " " << P4.py << " " << P4.pz << endl;
   }

   return 0;
}



