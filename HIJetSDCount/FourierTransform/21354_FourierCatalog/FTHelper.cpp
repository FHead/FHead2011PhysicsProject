#include <iostream>

#include "FTHelper.h"
   
JetImage::JetImage()
{
   Data = nullptr;
   Size = 0;
}

JetImage::JetImage(int size)
{
   Data = nullptr;
   Initialize(size);
}

JetImage::~JetImage()
{
   if(Data == nullptr)
      return;

   for(int i = 0; i < Size; i++)
      delete[] Data[i];
   delete[] Data;
}

void JetImage::Initialize(int size)
{
   Size = size;

   Data = new double *[Size];
   for(int i = 0; i < Size; i++)
      Data[i] = new double[Size];
   for(int i = 0; i < Size; i++)
      for(int j = 0; j < Size; j++)
         Data[i][j] = 0;
}
   
JetImage JetImage::operator +(JetImage &other)
{
   JetImage Result(Size);

   for(int i = 0; i < Size; i++)
   {
      for(int j = 0; j < Size; j++)
      {
         Result.Data[i][j] = Data[i][j];
         if(i < other.Size && j < other.Size)
            Result.Data[i][j] += other.Data[i][j];
      }
   }

   return Result;
}

JetImage JetImage::operator -(JetImage &other)
{
   JetImage Result(Size);

   for(int i = 0; i < Size; i++)
   {
      for(int j = 0; j < Size; j++)
      {
         Result.Data[i][j] = Data[i][j];
         if(i < other.Size && j < other.Size)
            Result.Data[i][j] -= other.Data[i][j];
      }
   }

   return Result;
}
   
JetImage &JetImage::operator =(JetImage &other)
{
   if(Size != other.Size)
   {
      if(Data != nullptr)
      {
         for(int i = 0; i < Size; i++)
            delete[] Data[i];
         delete[] Data;
      }
      Initialize(other.Size);
   }

   for(int i = 0; i < Size; i++)
      for(int j = 0; j < Size; j++)
         Data[i][j] = other.Data[i][j];

   return (*this);
}

JetMode::JetMode()
{
   Real = nullptr;
   Imag = nullptr;
   Size = 0;
}

JetMode::JetMode(int size)
{
   Real = nullptr;
   Imag = nullptr;
   Initialize(size);
}

JetMode::~JetMode()
{
   if(Real != nullptr)
   {
      for(int i = 0; i < Size; i++)
         delete[] Real[i];
      delete[] Real;
   }
   
   if(Imag != nullptr)
   {
      for(int i = 0; i < Size; i++)
         delete[] Imag[i];
      delete[] Imag;
   }
}

void JetMode::Initialize(int size)
{
   Size = size;

   Real = new double *[Size];
   for(int i = 0; i < Size; i++)
      Real[i] = new double[Size];
   for(int i = 0; i < Size; i++)
      for(int j = 0; j < Size; j++)
         Real[i][j] = 0;
   
   Imag = new double *[Size];
   for(int i = 0; i < Size; i++)
      Imag[i] = new double[Size];
   for(int i = 0; i < Size; i++)
      for(int j = 0; j < Size; j++)
         Imag[i][j] = 0;
}

JetMode JetMode::operator +(JetMode &other)
{
   JetMode Result(Size);

   for(int i = 0; i < Size; i++)
   {
      for(int j = 0; j < Size; j++)
      {
         Result.Real[i][j] = Real[i][j];
         Result.Imag[i][j] = Imag[i][j];
         if(i < other.Size && j < other.Size)
         {
            Result.Real[i][j] += other.Real[i][j];
            Result.Imag[i][j] += other.Imag[i][j];
         }
      }
   }

   return Result;
}

JetMode JetMode::operator -(JetMode &other)
{
   JetMode Result(Size);

   for(int i = 0; i < Size; i++)
   {
      for(int j = 0; j < Size; j++)
      {
         Result.Real[i][j] = Real[i][j];
         Result.Imag[i][j] = Imag[i][j];
         if(i < other.Size && j < other.Size)
         {
            Result.Real[i][j] -= other.Real[i][j];
            Result.Imag[i][j] -= other.Imag[i][j];
         }
      }
   }

   return Result;
}

JetMode &JetMode::operator =(JetMode &other)
{
   if(Size != other.Size)
   {
      if(Real != nullptr)
      {
         for(int i = 0; i < Size; i++)
            delete[] Real[i];
         delete[] Real;
      }
      if(Imag != nullptr)
      {
         for(int i = 0; i < Size; i++)
            delete[] Imag[i];
         delete[] Imag;
      }
      Initialize(other.Size);
   }

   for(int i = 0; i < Size; i++)
   {
      for(int j = 0; j < Size; j++)
      {
         Real[i][j] = other.Real[i][j];
         Imag[i][j] = other.Imag[i][j];
      }
   }

   return (*this);
}

std::pair<double, double> GetCoefficient(JetImage &Image, int KX, int KY)
{
   double FR = 0, FI = 0;

   static std::vector<double> Cos(0);
   static std::vector<double> Sin(0);

   if(Cos.size() != Image.Size || Sin.size() != Image.Size)
   {
      Cos.resize(Image.Size);
      Sin.resize(Image.Size);
      for(int i = 0; i < Image.Size; i++)
      {
         Cos[i] = std::cos(2 * M_PI / Image.Size * i);
         Sin[i] = std::sin(2 * M_PI / Image.Size * i);
      }
   }

   for(int iX = 0; iX < Image.Size; iX++)
   {
      for(int iY = 0; iY < Image.Size; iY++)
      {
         int K = (KX * iX + KY * iY) % Image.Size;

         FR = FR + Image.Data[iX][iY] * Cos[K] / Image.Size;
         FI = FI - Image.Data[iX][iY] * Sin[K] / Image.Size;
      }
   }

   return std::pair<double, double>(FR, FI);
}

JetMode Transform(JetImage &Image, int KeepMinX, int KeepMaxX, int KeepMinY, int KeepMaxY)
{
   if(KeepMinX < 0)   KeepMinX = KeepMinX + Image.Size;
   if(KeepMinY < 0)   KeepMinY = KeepMinY + Image.Size;

   JetMode Result(Image.Size);

   for(int KX = 0; KX < Image.Size; KX++)
   {
      if(KeepMinX <= KeepMaxX && (KX < KeepMinX || KX > KeepMaxX))
         continue;
      if(KeepMinX > KeepMaxX && (KX > KeepMaxX && KX < KeepMinX))
         continue;

      for(int KY = 0; KY < Image.Size; KY++)
      {
         if(KeepMinY <= KeepMaxY && (KY < KeepMinY || KY > KeepMaxY))
            continue;
         if(KeepMinY > KeepMaxY && (KY > KeepMaxY && KY < KeepMinY))
            continue;

         std::pair<double, double> C = GetCoefficient(Image, KX, KY);

         Result.Real[KX][KY] = C.first / Image.Size;
         Result.Imag[KX][KY] = C.second / Image.Size;
      }
   }

   return Result;
}

JetImage Transform(JetMode &Mode)
{
   JetImage Result(Mode.Size);

   static std::vector<double> Cos(0);
   static std::vector<double> Sin(0);

   if(Cos.size() != Mode.Size || Sin.size() != Mode.Size)
   {
      Cos.resize(Mode.Size);
      Sin.resize(Mode.Size);
      for(int i = 0; i < Mode.Size; i++)
      {
         Cos[i] = std::cos(2 * M_PI / Mode.Size * i);
         Sin[i] = std::sin(2 * M_PI / Mode.Size * i);
      }
   }

   for(int KX = 0; KX < Mode.Size; KX++)
   {
      for(int KY = 0; KY < Mode.Size; KY++)
      {
         if(Mode.Real[KX][KY] == 0)
            continue;

         for(int X = 0; X < Result.Size; X++)
         {
            for(int Y = 0; Y < Result.Size; Y++)
            {
               int K = (KX * X + KY * Y) % Mode.Size;
               Result.Data[X][Y] = Result.Data[X][Y] + Mode.Real[KX][KY] * Cos[K] - Mode.Imag[KX][KY] * Sin[K];
            }
         }
      }
   }

   return Result;
}

double GetPhase(double x, double y)
{
   double size = GetSize(x, y);

   if(y > 0)
      return acos(x / size);
   return -acos(x / size);
}

double GetSize(double x, double y)
{
   return std::sqrt(x * x + y * y);
}


