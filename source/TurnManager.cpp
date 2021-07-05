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
#include "Bomb.h"
#include <iostream>
#include "SpriteComponent.h"

TurnManager::TurnManager(Game *game, TBPlayer *player1, TBPlayer *player2) : 
Actor(game), mPlayer1(player1), mPlayer2(player2), mCursor(nullptr), mPhase(GET_CANDIDATE_FIELDS)
{
    // player1 plays first
    mCurrentPlayer = mPlayer1;
    mOppositePlayer = mPlayer2;
    mTurn = true;

    mRemainingBombNum = new SpriteComponent(this, 200);
    // not sofisticated
    int inibom = INITIAL_PENDING_BOMB_NUM;
    SetRemainingBombNum(inibom);
    SetPosition(PENDING_BOMB_NUM_POSITION);
    SetRotation(0);
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
            std::cout << "get_cand_fields" << std::endl;
            break;

        case CREATE_CURSOR :
            mCursor = new Cursor(this->GetGame(), this, mTurn);
            mPhase = CREATE_CAND_FIELD_SPRITE;
            std::cout << "create_cursor" << std::endl;
            break;

        case CREATE_CAND_FIELD_SPRITE :
            for(auto field : mCandFields)
            {
                field->CreateCandSprite(this->GetGame(), mTurn);
            }
            mPhase = CHOOSE_AND_MOVE_FIELD;
            std::cout << "create_cand_field_sprite" << std::endl;
            break;

        case DELETE_CURSOR :
            std::cout << "chooose_and_mobe_fields" << std::endl;
            delete mCursor;
            mPhase = DELETE_CAND_FIELD_SPITE;
            std::cout << "delete_cursor" << std::endl;
            break;

        case DELETE_CAND_FIELD_SPITE :
            for(auto field : mCandFields)
            {
                field->DeleteCandSprite();
            }
            mPhase = DECREMENT_OPPOSITE_PLAYERS_BOMB;
            std::cout << "delete_cand_fields_sprite" << std::endl;
            break;

        case DECREMENT_OPPOSITE_PLAYERS_BOMB :
            for(auto bomb : GetGame()->GetSettedBombs())
            {
                if(bomb->GetBombOwner() == mOppositePlayer)
                {
                    std::cout << "dec" << std::endl;
                    bomb->DecrementCount();
                }
            }
            mPhase = CHECK_BOMB_COUNT;
            std::cout << "decreametn bomb" << std::endl;
            break;

        case CHECK_BOMB_COUNT :
            for(auto bomb : GetGame()->GetSettedBombs())
            {
                if(bomb->GetBombOwner() == mOppositePlayer)
                {
                   bomb->CheckBombCount();
                }
            }
            mPhase = WHETHER_SET_BOMB;
            std::cout << "check_bomb_count" << std::endl;
            break;

        case WHETHER_SET_BOMB :
            // judge whether set a bomb or not
            mCurrentPlayer->SetBomb(2);
            if(mCurrentPlayer == mPlayer1) ChangePendingBombNum(mPlayer1->GetPendingBombNum());
            mPhase = CHANGE_PLAYER;
            std::cout << "whether set_bomb" << std::endl;
            std::cout << "owner is " << mCurrentPlayer << std::endl;
            break;

        case CHANGE_PLAYER :
            std::swap(mCurrentPlayer, mOppositePlayer);
            mTurn = !mTurn;
            mPhase = GET_CANDIDATE_FIELDS;
            std::cout << "change_plyaer" << std::endl;
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
        for(auto path : GetGame()->GetPaths())
        {
            Field *target;
            if(path->GetNord1() != nord && path->GetNord2() != nord) continue;
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

void TurnManager::SetRemainingBombNum(int &num)
{
    switch(num){
        case 0 :
            mRemainingBombNum->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/zero.png"));
            break;
        case 1 : 
            mRemainingBombNum->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/one.png"));
            break;
        case 2 : 
            mRemainingBombNum->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/two.png"));
            break;
        case 3 : 
            mRemainingBombNum->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/three.png"));
            break;
        case 4 : 
            mRemainingBombNum->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/four.png"));
            break;
        default :
            break;
    }
}

void TurnManager::ChangePendingBombNum(int count)
{
    delete mRemainingBombNum;
    mRemainingBombNum = new SpriteComponent(this, 200);
    SetRemainingBombNum(count);
    SetPosition(PENDING_BOMB_NUM_POSITION);
    SetRotation(0);
}