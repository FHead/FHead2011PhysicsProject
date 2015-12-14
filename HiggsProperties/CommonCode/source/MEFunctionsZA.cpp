//----------------------------------------------------------------------------
#include "AngleConversion.h"
#include "CalculateZAME.h"
#include "Constants.h"
//----------------------------------------------------------------------------
#include "MEFunctions.h"
//----------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------
double CalculateA2ZARA2ZARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p;   p.aZAR = 1;
   return GetSpin0ZAME(Event, p);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3ZARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAR = 1;
   GeneralScalarParameters p2;   p2.aZAdR = 1;
   GeneralScalarParameters p3;   p3.aZAR = 1;   p3.aZAdR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3ZAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAR = 1;
   GeneralScalarParameters p2;   p2.aZAdI = 1;
   GeneralScalarParameters p3;   p3.aZAR = 1;   p3.aZAdI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAR = 1;
   GeneralScalarParameters p2;   p2.aAR = 1;
   GeneralScalarParameters p3;   p3.aZAR = 1;   p3.aAR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA2AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAR = 1;
   GeneralScalarParameters p2;   p2.aAI = 1;
   GeneralScalarParameters p3;   p3.aZAR = 1;   p3.aAI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAR = 1;
   GeneralScalarParameters p2;   p2.aAdR = 1;
   GeneralScalarParameters p3;   p3.aZAR = 1;   p3.aAdR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2ZARA3AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAR = 1;
   GeneralScalarParameters p2;   p2.aAdI = 1;
   GeneralScalarParameters p3;   p3.aZAR = 1;   p3.aAdI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3ZARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p;   p.aZAdR = 1;
   return GetSpin0ZAME(Event, p);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3ZAISignal(ZALeptonVectors &Event)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA3ZARA2AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdR = 1;
   GeneralScalarParameters p2;   p2.aAR = 1;
   GeneralScalarParameters p3;   p3.aZAdR = 1;   p3.aAR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA2AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdR = 1;
   GeneralScalarParameters p2;   p2.aAI = 1;
   GeneralScalarParameters p3;   p3.aZAdR = 1;   p3.aAI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdR = 1;
   GeneralScalarParameters p2;   p2.aAdR = 1;
   GeneralScalarParameters p3;   p3.aZAdR = 1;   p3.aAdR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZARA3AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdR = 1;
   GeneralScalarParameters p2;   p2.aAdI = 1;
   GeneralScalarParameters p3;   p3.aZAdR = 1;   p3.aAdI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3ZAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p;   p.aZAdR = 1;
   return GetSpin0ZAME(Event, p);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA2AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdI = 1;
   GeneralScalarParameters p2;   p2.aAR = 1;
   GeneralScalarParameters p3;   p3.aZAdI = 1;   p3.aAR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA2AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdI = 1;
   GeneralScalarParameters p2;   p2.aAI = 1;
   GeneralScalarParameters p3;   p3.aZAdI = 1;   p3.aAI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdI = 1;
   GeneralScalarParameters p2;   p2.aAdR = 1;
   GeneralScalarParameters p3;   p3.aZAdI = 1;   p3.aAdR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3ZAIA3AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aZAdI = 1;
   GeneralScalarParameters p2;   p2.aAdI = 1;
   GeneralScalarParameters p3;   p3.aZAdI = 1;   p3.aAdI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2AARA2AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p;   p.aAR = 1;
   return GetSpin0ZAME(Event, p);
}
//----------------------------------------------------------------------------
double CalculateA2AARA2AAISignal(ZALeptonVectors &Event)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA2AARA3AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aAR = 1;
   GeneralScalarParameters p2;   p2.aAdR = 1;
   GeneralScalarParameters p3;   p3.aAR = 1;   p3.aAdR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2AARA3AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aAR = 1;
   GeneralScalarParameters p2;   p2.aAdI = 1;
   GeneralScalarParameters p3;   p3.aAR = 1;   p3.aAdI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA2AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p;   p.aAI = 1;
   return GetSpin0ZAME(Event, p);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA3AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aAI = 1;
   GeneralScalarParameters p2;   p2.aAdR = 1;
   GeneralScalarParameters p3;   p3.aAI = 1;   p3.aAdR = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA2AAIA3AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p1;   p1.aAI = 1;
   GeneralScalarParameters p2;   p2.aAdI = 1;
   GeneralScalarParameters p3;   p3.aAI = 1;   p3.aAdI = 1;
   return GetSpin0ZAME(Event, p3)
      - GetSpin0ZAME(Event, p1)
      - GetSpin0ZAME(Event, p2);
}
//----------------------------------------------------------------------------
double CalculateA3AARA3AARSignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p;   p.aAdR = 1;
   return GetSpin0ZAME(Event, p);
}
//----------------------------------------------------------------------------
double CalculateA3AARA3AAISignal(ZALeptonVectors &Event)
{
   return 0;
}
//----------------------------------------------------------------------------
double CalculateA3AAIA3AAISignal(ZALeptonVectors &Event)
{
   GeneralScalarParameters p;   p.aAdI = 1;
   return GetSpin0ZAME(Event, p);
}
//----------------------------------------------------------------------------
double CalculateQQBackground(ZALeptonVectors &Event)
{
   return GetqqZAME(Event, false, false)
      + GetqqZAME(Event, true, false)
      + GetqqZAME(Event, false, true)
      + GetqqZAME(Event, true, true);
}
//----------------------------------------------------------------------------
