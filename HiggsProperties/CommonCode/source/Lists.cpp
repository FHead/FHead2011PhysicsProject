//---------------------------------------------------------------------------
#include <vector>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
#include "Lists.h"
//---------------------------------------------------------------------------
vector<string> GetHLLSignalSuffixList()
{
   string suffix[153] =
   {
      "A1ZZRA1ZZR",        // 1
      "A2ZZRA2ZZR",        // 2
      "A2ZZIA2ZZI",        // 3
      "A3ZZRA3ZZR",        // 4
      "A3ZZIA3ZZI",        // 5
      "A2ZARA2ZAR",        // 6
      "A2ZAIA2ZAI",        // 7
      "A3ZARA3ZAR",        // 8
      "A3ZAIA3ZAI",        // 9
      "A2AARA2AAR",        // 10
      "A2AAIA2AAI",        // 11
      "A3AARA3AAR",        // 12
      "A3AAIA3AAI",        // 13
      "A1ZZRA2ZZR",        // 14
      "A1ZZRA2ZZI",        // 15
      "A1ZZRA3ZZR",        // 16
      "A1ZZRA3ZZI",        // 17
      "A1ZZRA2ZAR",        // 18
      "A1ZZRA2ZAI",        // 19
      "A1ZZRA3ZAR",        // 20
      "A1ZZRA3ZAI",        // 21
      "A1ZZRA2AAR",        // 22
      "A1ZZRA2AAI",        // 23
      "A1ZZRA3AAR",        // 24
      "A1ZZRA3AAI",        // 25
      "A2ZZRA2ZZI",        // 26
      "A2ZZRA3ZZR",        // 27
      "A2ZZRA3ZZI",        // 28
      "A2ZZRA2ZAR",        // 29
      "A2ZZRA2ZAI",        // 30
      "A2ZZRA3ZAR",        // 31
      "A2ZZRA3ZAI",        // 32
      "A2ZZRA2AAR",        // 33
      "A2ZZRA2AAI",        // 34
      "A2ZZRA3AAR",        // 35
      "A2ZZRA3AAI",        // 36
      "A2ZZIA3ZZR",        // 37
      "A2ZZIA3ZZI",        // 38
      "A2ZZIA2ZAR",        // 39
      "A2ZZIA2ZAI",        // 40
      "A2ZZIA3ZAR",        // 41
      "A2ZZIA3ZAI",        // 42
      "A2ZZIA2AAR",        // 43
      "A2ZZIA2AAI",        // 44
      "A2ZZIA3AAR",        // 45
      "A2ZZIA3AAI",        // 46
      "A3ZZRA3ZZI",        // 47
      "A3ZZRA2ZAR",        // 48
      "A3ZZRA2ZAI",        // 49
      "A3ZZRA3ZAR",        // 50
      "A3ZZRA3ZAI",        // 51
      "A3ZZRA2AAR",        // 52
      "A3ZZRA2AAI",        // 53
      "A3ZZRA3AAR",        // 54
      "A3ZZRA3AAI",        // 55
      "A3ZZIA2ZAR",        // 56
      "A3ZZIA2ZAI",        // 57
      "A3ZZIA3ZAR",        // 58
      "A3ZZIA3ZAI",        // 59
      "A3ZZIA2AAR",        // 60
      "A3ZZIA2AAI",        // 61
      "A3ZZIA3AAR",        // 62
      "A3ZZIA3AAI",        // 63
      "A2ZARA2ZAI",        // 64
      "A2ZARA3ZAR",        // 65
      "A2ZARA3ZAI",        // 66
      "A2ZARA2AAR",        // 67
      "A2ZARA2AAI",        // 68
      "A2ZARA3AAR",        // 69
      "A2ZARA3AAI",        // 70
      "A2ZAIA3ZAR",        // 71
      "A2ZAIA3ZAI",        // 72
      "A2ZAIA2AAR",        // 73
      "A2ZAIA2AAI",        // 74
      "A2ZAIA3AAR",        // 75
      "A2ZAIA3AAI",        // 76
      "A3ZARA3ZAI",        // 77
      "A3ZARA2AAR",        // 78
      "A3ZARA2AAI",        // 79
      "A3ZARA3AAR",        // 80
      "A3ZARA3AAI",        // 81
      "A3ZAIA2AAR",        // 82
      "A3ZAIA2AAI",        // 83
      "A3ZAIA3AAR",        // 84
      "A3ZAIA3AAI",        // 85
      "A2AARA2AAI",        // 86
      "A2AARA3AAR",        // 87
      "A2AARA3AAI",        // 88
      "A2AAIA3AAR",        // 89
      "A2AAIA3AAI",        // 90
      "A3AARA3AAI",        // 91
    
      "A1L1ZZRA1L1ZZR",    // 92
      "A1L1ZZIA1L1ZZI",    // 93
      "A1LQZZRA1LQZZR",    // 94
      "A1LQZZIA1LQZZI",    // 95
     
      "A1ZZRA1L1ZZR",      // 96
      "A1L1ZZRA2ZZR",      // 97
      "A1L1ZZRA2ZZI",      // 98
      "A1L1ZZRA3ZZR",      // 99
      "A1L1ZZRA3ZZI",      // 100
      "A1L1ZZRA2ZAR",      // 101
      "A1L1ZZRA2ZAI",      // 102
      "A1L1ZZRA3ZAR",      // 103
      "A1L1ZZRA3ZAI",      // 104
      "A1L1ZZRA2AAR",      // 105
      "A1L1ZZRA2AAI",      // 106
      "A1L1ZZRA3AAR",      // 107
      "A1L1ZZRA3AAI",      // 108
        
      "A1ZZRA1L1ZZI",      // 109
      "A1L1ZZIA2ZZR",      // 110
      "A1L1ZZIA2ZZI",      // 111
      "A1L1ZZIA3ZZR",      // 112
      "A1L1ZZIA3ZZI",      // 113
      "A1L1ZZIA2ZAR",      // 114
      "A1L1ZZIA2ZAI",      // 115
      "A1L1ZZIA3ZAR",      // 116
      "A1L1ZZIA3ZAI",      // 117
      "A1L1ZZIA2AAR",      // 118
      "A1L1ZZIA2AAI",      // 119
      "A1L1ZZIA3AAR",      // 120
      "A1L1ZZIA3AAI",      // 121
      "A1L1ZZRA1L1ZZI",    // 122
           
      "A1ZZRA1LQZZR",      // 123
      "A1LQZZRA2ZZR",      // 124
      "A1LQZZRA2ZZI",      // 125
      "A1LQZZRA3ZZR",      // 126
      "A1LQZZRA3ZZI",      // 127
      "A1LQZZRA2ZAR",      // 128
      "A1LQZZRA2ZAI",      // 129
      "A1LQZZRA3ZAR",      // 130
      "A1LQZZRA3ZAI",      // 131
      "A1LQZZRA2AAR",      // 132
      "A1LQZZRA2AAI",      // 133
      "A1LQZZRA3AAR",      // 134
      "A1LQZZRA3AAI",      // 135
      "A1L1ZZRA1LQZZR",    // 136
      "A1L1ZZIA1LQZZR",    // 137
          
      "A1ZZRA1LQZZI",      // 138
      "A1LQZZIA2ZZR",      // 139
      "A1LQZZIA2ZZI",      // 140
      "A1LQZZIA3ZZR",      // 141
      "A1LQZZIA3ZZI",      // 142
      "A1LQZZIA2ZAR",      // 143
      "A1LQZZIA2ZAI",      // 144
      "A1LQZZIA3ZAR",      // 145
      "A1LQZZIA3ZAI",      // 146
      "A1LQZZIA2AAR",      // 147
      "A1LQZZIA2AAI",      // 148
      "A1LQZZIA3AAR",      // 149
      "A1LQZZIA3AAI",      // 150
      "A1L1ZZRA1LQZZI",    // 151
      "A1L1ZZIA1LQZZI",    // 152
      "A1LQZZRA1LQZZI"     // 153
   };

   vector<string> Result(suffix, suffix + 153);
   return Result;
}
//---------------------------------------------------------------------------
vector<string> GetVffSignalSuffixList()
{
   string suffix[213] =
   {
      "000404",
      "000413",
      "000422",
      "000431",
      "000440",
      "000503",
      "000512",
      "000521",
      "000530",
      "000602",
      "000611",
      "000620",
      "001304",
      "001313",
      "001322",
      "001331",
      "001340",
      "001403",
      "001412",
      "001421",
      "001430",
      "001502",
      "001511",
      "001520",
      "002204",
      "002213",
      "002222",
      "002231",
      "002240",
      "002303",
      "002312",
      "002321",
      "002330",
      "002402",
      "002411",
      "002420",
      "003104",
      "003113",
      "003122",
      "003131",
      "003140",
      "003203",
      "003212",
      "003221",
      "003230",
      "003302",
      "003311",
      "003320",
      "004004",
      "004013",
      "004022",
      "004031",
      "004040",
      "004103",
      "004112",
      "004121",
      "004130",
      "004202",
      "004211",
      "004220",
      "005003",
      "005012",
      "005021",
      "005030",
      "005102",
      "005111",
      "005120",
      "006002",
      "006011",
      "006020",
      "110303",
      "110312",
      "110321",
      "110330",
      "110402",
      "110411",
      "110420",
      "110501",
      "110510",
      "111203",
      "111212",
      "111221",
      "111230",
      "111302",
      "111311",
      "111320",
      "111401",
      "111410",
      "112103",
      "112112",
      "112121",
      "112130",
      "112202",
      "112211",
      "112220",
      "112301",
      "112310",
      "113003",
      "113012",
      "113021",
      "113030",
      "113102",
      "113111",
      "113120",
      "113201",
      "113210",
      "114002",
      "114011",
      "114020",
      "114101",
      "114110",
      "115001",
      "115010",
      "200303",
      "200312",
      "200321",
      "200330",
      "200402",
      "200411",
      "200420",
      "201203",
      "201212",
      "201221",
      "201230",
      "201302",
      "201311",
      "201320",
      "202103",
      "202112",
      "202121",
      "202130",
      "202202",
      "202211",
      "202220",
      "203003",
      "203012",
      "203021",
      "203030",
      "203102",
      "203111",
      "203120",
      "204002",
      "204011",
      "204020",
      "220202",
      "220211",
      "220220",
      "220301",
      "220310",
      "220400",
      "221102",
      "221111",
      "221120",
      "221201",
      "221210",
      "221300",
      "222002",
      "222011",
      "222020",
      "222101",
      "222110",
      "222200",
      "223001",
      "223010",
      "223100",
      "224000",
      "310202",
      "310211",
      "310220",
      "310301",
      "310310",
      "311102",
      "311111",
      "311120",
      "311201",
      "311210",
      "312002",
      "312011",
      "312020",
      "312101",
      "312110",
      "313001",
      "313010",
      "330101",
      "330110",
      "330200",
      "331001",
      "331010",
      "331100",
      "332000",
      "400202",
      "400211",
      "400220",
      "401102",
      "401111",
      "401120",
      "402002",
      "402011",
      "402020",
      "420101",
      "420110",
      "420200",
      "421001",
      "421010",
      "421100",
      "422000",
      "440000",
      "510101",
      "510110",
      "511001",
      "511010",
      "530000",
      "620000"
   };
   
   vector<string> Result(suffix, suffix + 213);
   return Result;
}
//---------------------------------------------------------------------------
vector<string> GetHLLZASignalSuffixList()
{
   string suffix[28] =
   {
      "A2ZARA2ZAR",        // 1
      "A3ZARA3ZAR",        // 2
      "A3ZAIA3ZAI",        // 3
      "A2AARA2AAR",        // 4
      "A2AAIA2AAI",        // 5
      "A3AARA3AAR",        // 6
      "A3AAIA3AAI",        // 7
      "A2ZARA3ZAR",        // 8
      "A2ZARA3ZAI",        // 9
      "A2ZARA2AAR",        // 10
      "A2ZARA2AAI",        // 11
      "A2ZARA3AAR",        // 12
      "A2ZARA3AAI",        // 13
      "A3ZARA3ZAI",        // 14
      "A3ZARA2AAR",        // 15
      "A3ZARA2AAI",        // 16
      "A3ZARA3AAR",        // 17
      "A3ZARA3AAI",        // 18
      "A3ZAIA2AAR",        // 19
      "A3ZAIA2AAI",        // 20
      "A3ZAIA3AAR",        // 21
      "A3ZAIA3AAI",        // 22
      "A2AARA2AAI",        // 23
      "A2AARA3AAR",        // 24
      "A2AARA3AAI",        // 25
      "A2AAIA3AAR",        // 26
      "A2AAIA3AAI",        // 27
      "A3AARA3AAI",        // 28
   };

   vector<string> Result(suffix, suffix + 28);
   return Result;
}
//---------------------------------------------------------------------------
vector<string> GetXVVSignalSuffixList()
{
   string suffix[72] =
   {
      "A1ZZR",
      "A1ZZI",
      "A2ZZR",
      "A2ZZI",
      "A3ZZR",
      "A3ZZI",
      "A4ZZR",
      "A4ZZI",
      "A1ZVR",
      "A1ZVI",
      "A2ZVR",
      "A2ZVI",
      "A3ZVR",
      "A3ZVI",
      "A4ZVR",
      "A4ZVI",
      "A1ZAR",
      "A1ZAI",
      "A2ZAR",
      "A2ZAI",
      "A3ZAR",
      "A3ZAI",
      "A4ZAR",
      "A4ZAI",
      "A1VZR",
      "A1VZI",
      "A2VZR",
      "A2VZI",
      "A3VZR",
      "A3VZI",
      "A4VZR",
      "A4VZI",
      "A1VVR",
      "A1VVI",
      "A2VVR",
      "A2VVI",
      "A3VVR",
      "A3VVI",
      "A4VVR",
      "A4VVI",
      "A1VAR",
      "A1VAI",
      "A2VAR",
      "A2VAI",
      "A3VAR",
      "A3VAI",
      "A4VAR",
      "A4VAI",
      "A1AZR",
      "A1AZI",
      "A2AZR",
      "A2AZI",
      "A3AZR",
      "A3AZI",
      "A4AZR",
      "A4AZI",
      "A1AVR",
      "A1AVI",
      "A2AVR",
      "A2AVI",
      "A3AVR",
      "A3AVI",
      "A4AVR",
      "A4AVI",
      "A1AAR",
      "A1AAI",
      "A2AAR",
      "A2AAI",
      "A3AAR",
      "A3AAI",
      "A4AAR",
      "A4AAI"
   };

   return vector<string>(suffix, suffix + 72);
}
//---------------------------------------------------------------------------
