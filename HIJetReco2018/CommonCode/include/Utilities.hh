#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>



#include <stdexcept>


namespace 
{
  void handleError(const std::string& fClass, const std::string& fMessage);
  float getFloat(const std::string& token) ;
  unsigned getUnsigned(const std::string& token) ;
  std::string getSection(const std::string& token) ;
  std::vector<std::string> getTokens(const std::string& fLine);
  std::string getDefinitions(const std::string& token) ;
  void handleError(const std::string& fClass, const std::string& fMessage);
  float quadraticInterpolation(float fZ, const float fX[3], const float fY[3]);
}
#endif
