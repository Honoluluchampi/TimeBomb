#include "TurnManager.h"
#include "Game.h"
#include "TBPlayer.h"
#include "Field.h"

TurnManager::TurnManager(Game *game, TBPlayer *player1, TBPlayer *player2) : 
Actor(game), mPlayer1(player1), mPlayer2(player2)
{
    // player1 moves first.
    mTurn = true;
}

TurnManager::~TurnManager()
{
}

void TurnManager::TurnSequence(bool turn)
{
    // current player
    TBPlayer* cp = GetCurrentPlayer(turn);
    std::vector<Field*> cf = GetCandFields(this->GetGame()->GetFields(), cp->GetCurrentField());
    ChooseField();
    ChangeTurn();
}

TBPlayer* TurnManager::GetCurrentPlayer(bool turn)
{
    if(turn) return mPlayer1;
    else return mPlayer2;
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

std::vector<Field*> TurnManager::GetCandFields(std::vector<Field*> fields, Field* field)
{

}