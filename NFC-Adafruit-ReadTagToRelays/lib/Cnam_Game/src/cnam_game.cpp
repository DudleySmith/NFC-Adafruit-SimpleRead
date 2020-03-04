#include <cnam_game.h>

void CnamGame::setup(){
  _boardName = readString(0);
}

String CnamGame::boardName(){
  return _boardName;

}

bool CnamGame::isTagOk(String tag){

  bool answer = false;

  // DEBUG CARD -------------------------------------------------------
  // Green = OK
  if(tag.startsWith(TAG_DGBOK)){
    answer = true;
  }

  // REd = KO
  if(tag.startsWith(TAG_DGBKO)){
    answer = false;
  }

  /*
  Chaque carte répond positivement pour un tag, négativement pour les autres
  */
  // Carte Coconut
  if (_boardName.startsWith(BOARD_NAME_BIPD)){
    // --
    if(tag.startsWith(TAG_ROBOT)){
      answer = true;
    }

  }else if (_boardName.startsWith(BOARD_NAME_COLN)){
    // --
    if(tag.startsWith(TAG_JUMEL)){
      answer = true;
    }

  }else if (_boardName.startsWith(BOARD_NAME_COCO)){
    // --
    if(tag.startsWith(TAG_COCOT)){
      answer = true;
    }

  }else if (_boardName.startsWith(BOARD_NAME_PRLV)){
    // --
    if(tag.startsWith(TAG_SERIN)){
      answer = true;
    }

  }else if (_boardName.startsWith(BOARD_NAME_PYRO)){
    // --
    if(tag.startsWith(TAG_THERM)){
      answer = true;
    }

  }else if (_boardName.startsWith(BOARD_NAME_COEU)){
    // --
    if(tag.startsWith(TAG_POMPE)){
      answer = true;
    }

  }else if (_boardName.startsWith(BOARD_NAME_CAGE)){
    // --
    if(tag.startsWith(TAG_BOULI)){
      answer = true;
    }

  }else if (_boardName.startsWith(BOARD_NAME_ISOC)){
    // --
    if(tag.startsWith(TAG_PHOTO)){
      answer = true;
    }

  }

  if(answer == true){
    Serial.print("FOUND : ");
  }else{
    Serial.print("NOT FOUND : ");
  }
  logAnswer(_boardName, tag, answer);

  return answer;

}

void CnamGame::logAnswer(String _boardName, String tag, bool answer){
  Serial.print("Board is "); Serial.print(_boardName);
  Serial.print(" - Tag is "); Serial.print(tag);
  Serial.print(" - Answer is "); Serial.println(answer ? "TRUE" : "FALSE");

}

String _boardName();
