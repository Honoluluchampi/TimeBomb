#include "TurnManager.h"
#include "Game.h"
#include "TBPlayer.h"
#include "Field.h"
#include "Cursor.h"

TurnManager::TurnManager(Game *game, TBPlayer *player1, TBPlayer *player2) : 
Actor(game), mPlayer1(player1), mPlayer2(player2), mCursor(nullptr), mPhase(0)
{
    // player1 play first
    mCurrentPlayer = mPlayer1;
}

TurnManager::~TurnManager()
{
}

void TurnManager::ActorInput(const uint8_t *keyState)
{
    switch(mPhase)
    {
        case CREATE_CURSOR :
            mCursor = new Cursor(this->GetGame(), this);
            mPhase = CHOOSE_FIELD;
            break;
        case CHOOSE_FIELD :
            ChooseField(keyState);
            break;
        case DELETE_CURSOR :
            delete mCursor;
            mPhase = CHANGE_PLAYER;
            break;
        case CHANGE_PLAYER :
            if(mCurrentPlayer == mPlayer1) mCurrentPlayer = mPlayer2;
            else mCurrentPlayer = mPlayer1;
            mPhase = CREATE_CURSOR;
    }
    // decide wether set a bomb phase : 1
    // decide time limit phase : 2
}

//void TurnManager::TurnSequence(bool turn)
//{
    // current player
    //TBPlayer* cp = GetCurrentPlayer(turn);
    //std::vector<Field*> cf = GetCandFields(this->GetGame()->GetFields(), cp->GetCurrentField());
    // create cursor
    //mCursor = new Cursor(this->GetGame(), this);
    //bool chosing = true;
    //while(chosing)
    //{
        //ChooseField();
    //}
    //ChangeTurn();
//}

void TurnManager::ChangeTurn()
{
    //mTurn = !mTurn;
}

void TurnManager::ChangeCursor()
{

}

void TurnManager::ChooseField(const uint8_t *state)
{
    if(mCursor == nullptr) mCursor = new Cursor(this->GetGame(), this);
    if(state[SDL_SCANCODE_RIGHT])
    {

    }
    if(state[SDL_SCANCODE_LEFT])
    {

    }
    if(state[SDL_SCANCODE_SPACE])
    {
        mPhase = DELETE_CURSOR;
        //if(mCurrentPlayer == mPlayer1) mCurrentPlayer = mPlayer2;
        //else mCurrentPlayer = mPlayer1;
    }
}

//std::vector<Field*> TurnManager::GetCandFields(std::vector<Field*> fields, Field* field)
//{

//}