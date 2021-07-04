#include "TurnManager.h"
#include "Game.h"
#include "TBPlayer.h"
#include "Field.h"
#include "Cursor.h"
#include <algorithm>

TurnManager::TurnManager(Game *game, TBPlayer *player1, TBPlayer *player2) : 
Actor(game), mPlayer1(player1), mPlayer2(player2), mCursor(nullptr), mPhase(GET_CANDIDATE_FIELDS)
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
        case GET_CANDIDATE_FIELDS :
            mCandFields = GetCandFields(GetGame()->GetFields(), mCurrentPlayer->GetCurrentField());
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
}

void TurnManager::ChooseField(const uint8_t *state)
{
    if(mCursor == nullptr) mCursor = new Cursor(this->GetGame(), this);
    if(state[SDL_SCANCODE_RIGHT])
    {
        auto iter = std::find(mCandFields.begin(), mCandFields.end(), mCursor->GetPointingField());
        ++iter;
        if(iter == mCandFields.end()) iter = mCandFields.begin();
        mCursor->ChangePointingField(*iter);
    }
    if(state[SDL_SCANCODE_LEFT])
    {
        auto iter = std::find(mCandFields.begin(), mCandFields.end(), mCursor->GetPointingField());
        if(iter == mCandFields.begin()) iter = mCandFields.end();
        --iter;
        mCursor->ChangePointingField(*iter);
    }
    if(state[SDL_SCANCODE_SPACE])
    {
        mPhase = DELETE_CURSOR;
    }
}

std::vector<Field*> TurnManager::GetCandFields(std::vector<Field*> fields, Field* field)
{
    return GetGame()->GetFields();
}