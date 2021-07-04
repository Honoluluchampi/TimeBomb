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
    mTurn = true;
}

TurnManager::~TurnManager()
{
}

void TurnManager::UpdateActor(float deltaTime)
{
    switch(mPhase)
    {
        case GET_CANDIDATE_FIELDS :
            mCandFields = GetCandFields(GetGame()->GetFields(), mCurrentPlayer->GetCurrentField());
            mPhase = CREATE_CURSOR;
            break;
        case CREATE_CURSOR :
            mCursor = new Cursor(this->GetGame(), this, mTurn);
            mPhase = CREATE_CAND_FIELD_SPRITE;
            break;
        case CREATE_CAND_FIELD_SPRITE :
            for(auto field : mCandFields)
            {
                field->CreateCandSprite(this->GetGame(), mTurn);
            }
            mPhase = CHOOSE_AND_MOVE_FIELD;
            break;
        case DELETE_CURSOR :
            delete mCursor;
            mPhase = DELETE_CAND_FIELD_SPITE;
            break;
        case DELETE_CAND_FIELD_SPITE :
            for(auto field : mCandFields)
            {
                field->DeleteCandSprite();
            }
            mPhase = CHANGE_PLAYER;
        case CHANGE_PLAYER :
            if(mCurrentPlayer == mPlayer1) mCurrentPlayer = mPlayer2;
            else mCurrentPlayer = mPlayer1;
            mTurn = !mTurn;
            mPhase = CREATE_CURSOR;
            break;
    }
}

void TurnManager::ActorInput(SDL_Event &event)
{
    switch(mPhase)
    {
        case CHOOSE_AND_MOVE_FIELD :
            ChooseField(event);
            break;
    }
}

std::vector<Field*> TurnManager::GetCandFields(std::vector<Field*> fields, Field* field)
{
    return GetGame()->GetFields();
}

void TurnManager::ChooseField(SDL_Event &event)
{
    // cursor is already created in create_cursor phase.
    //if(mCursor == nullptr) mCursor = new Cursor(this->GetGame(), this);
    switch(event.type)
    {
    case SDL_KEYDOWN:
        {
            auto key = event.key.keysym.sym;
            if(key == SDLK_RIGHT)
            {
                auto iter = std::find(mCandFields.begin(), mCandFields.end(), mCursor->GetPointingField());
                ++iter;
                if(iter == mCandFields.end()) iter = mCandFields.begin();
                mCursor->ChangePointingField(*iter);
            }
            if(key == SDLK_LEFT)
            {
                auto iter = std::find(mCandFields.begin(), mCandFields.end(), mCursor->GetPointingField());
                if(iter == mCandFields.begin()) iter = mCandFields.end();
                --iter;
                mCursor->ChangePointingField(*iter);
            }
            if(key == SDLK_SPACE)
            {
                auto iter = std::find(mCandFields.begin(), mCandFields.end(), mCursor->GetPointingField());
                // MOVE ONTO NEXT FIELD
                MovePlayer(*iter);
                mPhase = DELETE_CURSOR;
            }
        }
        break;
    default:
        break;
    }
}

void TurnManager::MovePlayer(Field *field)
{
    mCurrentPlayer->ChangeCurrentField(field);
}