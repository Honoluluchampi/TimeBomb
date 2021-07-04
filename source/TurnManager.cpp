#include "TurnManager.h"
#include "Game.h"
#include "TBPlayer.h"
#include "Field.h"
#include "Cursor.h"
#include <algorithm>
#include <queue>
#include <unordered_map>
#include "Path.h"
#include <utility>

TurnManager::TurnManager(Game *game, TBPlayer *player1, TBPlayer *player2) : 
Actor(game), mPlayer1(player1), mPlayer2(player2), mCursor(nullptr), mPhase(GET_CANDIDATE_FIELDS)
{
    // player1 play first
    mCurrentPlayer = mPlayer1;
    mOppositePlayer = mPlayer2;
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
            std::swap(mCurrentPlayer, mOppositePlayer);
            mTurn = !mTurn;
            mPhase = GET_CANDIDATE_FIELDS;
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
    auto start = field;
    std::unordered_map<Field*, int> dist;
    // initialize dist
    for(auto f : fields)
    {
        dist[f] = 1000;
    }
    dist[field] = 0;
    std::vector<Field*> cf; // candidate fields
    std::queue<Field*> que;
    que.push(start);
    while(!que.empty())
    {
        auto nord = que.front();
        int value = dist[nord];
        que.pop();
        if(value >= PLAYER_STEP) continue;
        for(auto path : nord->GetPaths())
        {
            Field *target;
            if(path->GetNord1() == nord) target = path->GetNord2();
            else target = path->GetNord1();
            // opposite player's position is not available.
            if(target == mOppositePlayer->GetCurrentField()) continue;
            if(dist[target] > value + 1)
            {
                dist[target] = value + 1;
                que.push(target);
            }
        }
    }
    for(auto f : fields)
    {
        if(dist[f] <= PLAYER_STEP) cf.push_back(f);
    }
    return cf;
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