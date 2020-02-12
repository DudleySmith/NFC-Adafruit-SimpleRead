#ifndef cnam_game_guard
#define cnam_game_guard

#include <EEPROMWrapper.h>
#include <Tags.h>

class CnamGame{

public:
  bool isTagOk(String tag);
  void setup();
  String boardName();

private:
  bool sendAndLog(String boardName, String tag, bool answer);
  String _boardName;

};

#endif /* end of include guard: cnam_game */
