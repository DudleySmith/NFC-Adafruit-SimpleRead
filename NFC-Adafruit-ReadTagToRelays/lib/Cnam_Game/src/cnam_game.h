#ifndef cnam_game_guard
#define cnam_game_guard

#include <EEPROMWrapper.h>
#include <Tags.h>

class CnamGame{

  public:
    bool isTagOk(String tag){

      // DEBUG CARD -------------------------------------------------------
      // Green = OK
      if(tag.startsWith(TAG_DGBOK)){
        return true;
      }

      // REd = KO
      if(tag.startsWith(TAG_DGBKO)){
        return false;
      }

      String boardName = readString(0);
      Serial.println(boardName);

      //if(boardName.startsWith(BOARD_NAME_COCO))

      return false;

    };

};



#endif /* end of include guard: cnam_game */
