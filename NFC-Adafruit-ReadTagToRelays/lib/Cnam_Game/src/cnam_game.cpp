#include <cnam_game.h>

void CnamGame::setup(){
  _boardName = readString(0);
}

String CnamGame::boardName(){
  return _boardName;

}

bool CnamGame::isTagOk(String tag){

  // DEBUG CARD -------------------------------------------------------
  // Green = OK
  if(tag.startsWith(TAG_DGBOK)){
    return true;
  }

  // REd = KO
  if(tag.startsWith(TAG_DGBKO)){
    return false;
  }

  /*
  Chaque carte répond positivement pour un tag, négativement pour les autres
  */
  // Carte Coconut
  if (_boardName.startsWith(BOARD_NAME_BIPD)){
    // --
    if(tag.startsWith(TAG_ROBOT)){
      return sendAndLog(_boardName, tag, true);
    }

  }else if (_boardName.startsWith(BOARD_NAME_COLN)){
    // --
    if(tag.startsWith(TAG_LOUPE)){
      return sendAndLog(_boardName, tag, true);
    }

  }else if (_boardName.startsWith(BOARD_NAME_COCO)){
    // --
    if(tag.startsWith(TAG_COCOT)){
      return sendAndLog(_boardName, tag, true);
    }

  }else if (_boardName.startsWith(BOARD_NAME_PRLV)){
    // --
    if(tag.startsWith(TAG_SERIN)){
      return sendAndLog(_boardName, tag, true);
    }

  }else if (_boardName.startsWith(BOARD_NAME_PYRO)){
    // --
    if(tag.startsWith(TAG_THERM)){
      return sendAndLog(_boardName, tag, true);
    }

  }else if (_boardName.startsWith(BOARD_NAME_COEU)){
    // --
    if(tag.startsWith(TAG_POMPE)){
      return sendAndLog(_boardName, tag, true);
    }

  }else if (_boardName.startsWith(BOARD_NAME_CAGE)){
    // --
    if(tag.startsWith(TAG_BOULI)){
      return sendAndLog(_boardName, tag, true);
    }

  }else if (_boardName.startsWith(BOARD_NAME_ISOC)){
    // --
    if(tag.startsWith(TAG_PHOTO)){
      return sendAndLog(_boardName, tag, true);
    }

  }

  return sendAndLog(_boardName, tag, false);

}

bool CnamGame::sendAndLog(String _boardName, String tag, bool answer){
  Serial.print("Board is "); Serial.print(_boardName);
  Serial.print(" - Tag is "); Serial.print(tag);
  Serial.print(" - Answer is "); Serial.println(answer);

  return answer;

}

String _boardName();
