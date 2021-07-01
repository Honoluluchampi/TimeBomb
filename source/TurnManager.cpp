#include "TurnManager.h"
#include "Game.h"
#include "TBPlayer.h"

TurnManager::TurnManager(Game *game, TBPlayer *player1, TBPlayer *player2) : 
mGame(game), mPlayer1(player1), mPlayer2(player2)
{
    // player1 moves first.
    mTurn = true;
}