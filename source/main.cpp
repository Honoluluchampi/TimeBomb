#include <iostream>
#include <memory>
#include "Game.h"

int main(int argc, const char * argv[])
{
  auto game = std::make_unique<Game>();
  game->GetOwnOwnership(game);
  bool success = game->Initialize();
  if(success)
  {
    game->RunLoop();
  }
  game->Shutdown();
  return 0;
}