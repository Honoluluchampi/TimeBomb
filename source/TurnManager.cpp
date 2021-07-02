#include "TurnManager.h"
#include "Game.h"
#include "TBPlayer.h"
#include "Field.h"

TurnManager::TurnManager(Game *game, TBPlayer *player1, TBPlayer *player2) : 
mGame(game), mPlayer1(player1), mPlayer2(player2)
{
    // player1 moves first.
    mTurn = true;
}

TurnManager::~TurnManager()
{
}

void TurnManager::TurnSequence()
{
    std::vector<Field*> cf = GetCandFields(mGame->mFields);
    ChooseField();
    ChangeTurn();
}

void TurnManager::ChangeTurn()
{
    mTurn = !mTurn;
}

void TurnManager::ChangeCursor()
{

}

void TurnManager::ChooseField()
{

}

std::vector<Field*> TurnManager::GetCandFields(std::vector<Field*> fields)
{

}