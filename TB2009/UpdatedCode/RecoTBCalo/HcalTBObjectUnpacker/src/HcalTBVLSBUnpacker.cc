#include "RecoTBCalo/HcalTBObjectUnpacker/interface/HcalTBVLSBUnpacker.h"

namespace hcaltb {
  
  HcalTBVLSBUnpacker::HcalTBVLSBUnpacker(){
    for (int iWord=0;iWord<nWordsExpected;iWord++) {
      badWordCounts_.push_back(0);
    }
  }

  HcalTBVLSBUnpacker::~HcalTBVLSBUnpacker(){
    printf("\n");
    printf("----------------------------------------------\n");
    printf("|            VLSB Unpacker report            |\n");
    printf("----------------------------------------------\n");

    for (int iMotherBoard=0;iMotherBoard<HcalTBVLSBData::maxMotherBoards;iMotherBoard++) {
      bool allSame=true;
      int firstWord=(iMotherBoard  )*nWordsExpected/HcalTBVLSBData::maxMotherBoards;
      int lastWord= (iMotherBoard+1)*nWordsExpected/HcalTBVLSBData::maxMotherBoards;
      
      int firstCount=badWordCounts_.at(firstWord);
      for (int iWord=firstWord;iWord<lastWord;iWord++) {
	if (badWordCounts_.at(iWord)!=firstCount) {
	  allSame=false;
	}
      } //end loop over words

      if (allSame) {
	printf("| All words for MB %d were bad %7d times. |\n",iMotherBoard,firstCount);	
      }
      else {
	for (int iWord=firstWord;iWord<lastWord;iWord++) {
	  if (badWordCounts_.at(iWord)>0) {
	    printf("| Word  %4d was  bad %7d times. |\n",iWord,badWordCounts_.at(iWord));
	  } 
	}
      } //end else

    } //end loop over MB
    printf("----------------------------------------------\n");

    //int lastCount=badWordCounts_.at(nWordsExpected-1);
    //int lastIndex=nWordsExpected-1;
    //for (int iWord=nWordsExpected-2;iWord>=0;iWord--) {
    //  if (badWordCounts_.at(iWord)!=lastCount) {
    //	lastIndex=iWord;
    //	break;
    //  }
    //}
    //for (int iWord=0;iWord<=lastIndex;iWord++) {
    //  if (badWordCounts_.at(iWord)>0) {
    //	printf("Word  %4d was  bad %5d times.\n",iWord,badWordCounts_.at(iWord));
    //  } 
    //}
    //printf("Words>%4d were bad %5d times.\n",lastIndex,lastCount);
  } //end destructor

  
  struct ClassicVLSBDataFormat {
    unsigned int cdfHeader0,cdfHeader1,cdfHeader2,cdfHeader3;
    uint32_t words[HcalTBVLSBUnpacker::nWordsExpected];
    unsigned int cdfTrailer0,cdfTrailer1;
  };
  
  void HcalTBVLSBUnpacker::unpack(const FEDRawData& raw,HcalTBVLSBData& vlsbdata) {
    const ClassicVLSBDataFormat* vlsb=(const ClassicVLSBDataFormat*)raw.data();
    //uint32_t* vlsb_words=(uint32_t*)raw.data();

    /*std::cout << "CDFversionNumber=" << ((vlsb->cdfHeader0>>4) & 0x0F) 
	      << "; SourceId=" <<  ((vlsb->cdfHeader0>>8)&0xFFF)
	      << "; BunchId=" <<  ((vlsb->cdfHeader0>>20)&0xFFF)
	      << "; EventNo=" <<  (vlsb->cdfHeader1 & 0x00FFFFFF)
	      << "; OrbitNo=" << (vlsb->cdfHeader2>>4)
	      << std::endl;*/

    int sizeMod4=raw.size()%4;
    int wordsSeen=raw.size()/4;

    if (sizeMod4!=0) std::cout << "Fail: sizeMod4=" << sizeMod4 << std::endl;
    if (wordsSeen!=(nWordsExpected+6)) std::cout << "Fail: expect " << (nWordsExpected+6) << " words; actually see "<< wordsSeen << std::endl;

    for (int iMotherBoard=0;iMotherBoard<HcalTBVLSBData::maxMotherBoards;iMotherBoard++) {
      for (int iChannel=0;iChannel<HcalTBVLSBData::maxChannels;iChannel++) {

	//int moboCoords=iMotherBoard<<4;
	//moboCoords|=iChannel;
	//
	//int socketCoords=mapper_.preampLemoToSocket_[mapper_.moboToPreampLemo_[moboCoords]];
	//vlsbdata.strip_[iMotherBoard][iChannel]=socketCoords>>5;
	//vlsbdata.pixel_[iMotherBoard][iChannel]=socketCoords&0x0000001F;
	
	//std::cout << "iMotherBoard=" << iMotherBoard 
	//	  << "; iChannel= " << iChannel 
	//	  << "; strip= " << (socketCoords>>5)
	//	  << "; pixel=" << (socketCoords&0x0000001F)
	//	  << std::endl;

	for (int iDoubleSample=0;iDoubleSample<HcalTBVLSBData::maxSamples/2;iDoubleSample++) {
	  int iWord=iDoubleSample + iChannel*HcalTBVLSBData::maxSamples/2 + iMotherBoard*HcalTBVLSBData::maxChannels*HcalTBVLSBData::maxSamples/2;

	  unsigned short  leftCheckExpected=0x3;
	  unsigned short rightCheckExpected=0x3;
	  if (iChannel==0 && iDoubleSample==0) leftCheckExpected=0x1;
	  if (iChannel==(HcalTBVLSBData::maxChannels-1) && iDoubleSample==(HcalTBVLSBData::maxSamples/2-1)) rightCheckExpected=0x2;

	  unsigned short  leftAdc=HcalTBVLSBData::badCode;
	  unsigned short rightAdc=HcalTBVLSBData::badCode;
	  if (iWord<wordsSeen) {
	    uint32_t word=vlsb->words[iWord];

	    //if constant bits are ok, extract ADC values
	    if ( ((word&0xC0000000)>>30)==leftCheckExpected && ((word&0x0000C000)>>14)==rightCheckExpected ) {
	      leftAdc  =(word&0x3FFF0000)>>16;
	      rightAdc = word&0x00003FFF;
	      //printf("iWord=%3d; value=0x%08X\n",iWord,word);
	    }
	    else {
	      //printf("Fail: iWord=%3d; value=0x%08X is bad.\n",iWord,word);
	      badWordCounts_.at(iWord)++;
	    }
	  }

	  vlsbdata.setAdc(iMotherBoard,iChannel,2*iDoubleSample  ,leftAdc);
	  vlsbdata.setAdc(iMotherBoard,iChannel,2*iDoubleSample+1,rightAdc);
	}
      }
    }
    
  } //end unpack
  
} //end namespace
