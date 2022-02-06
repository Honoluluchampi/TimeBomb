#include "TurnManager.h"
#include "TimeBombApp.h"
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
#include <cassert>
#include "ExplosionAnimeSpriteComponent.h"
#include "Actor.h"

TurnManager::TurnManager(TimeBombApp *game, TBPlayer *player1, TBPlayer *player2) : 
Actor(game), mApp(game), mPlayer1(player1), mPlayer2(player2),
mCursor(nullptr), mPhase(GET_CANDIDATE_FIELDS), mDistributeBomb(1)
{
    // player1 plays first
    mCurrentPlayer = mPlayer1;
    mOppositePlayer = mPlayer2;
    mTurn = true;

    // first true means manual positioning, second true means manual scaling
    mRemainingBombNum1 = new SpriteComponent(this, 200, MANUAL_POSITIONING);
    mRemainingBombNum2 = new SpriteComponent(this, 200, MANUAL_POSITIONING);
    mRemainingLifeNum1 = new SpriteComponent(this, 200, MANUAL_POSITIONING);
    mRemainingLifeNum2 = new SpriteComponent(this, 200, MANUAL_POSITIONING);
    mLifeString = new SpriteComponent(this, 200, MANUAL_POSITIONING, MANUAL_SCALING);
    mBombString = new SpriteComponent(this, 200, MANUAL_POSITIONING, MANUAL_SCALING);

    // SET POSTION
    mRemainingBombNum1->SetPosition(PENDING_BOMB_NUM_POSITION1);
    mRemainingBombNum2->SetPosition(PENDING_BOMB_NUM_POSITION2);
    mRemainingLifeNum1->SetPosition(HIT_POINT_POSITION1);
    mRemainingLifeNum2->SetPosition(HIT_POINT_POSITION2);
    mBombString->SetPosition(PENDING_BOMB_STRING_POSITION);
    mLifeString->SetPosition(HIT_POINT_STRING_POSITION);
    
    // SET SPRITE
    SetNumberSprite(mRemainingBombNum1, INITIAL_PENDING_BOMB_NUM);
    SetNumberSprite(mRemainingBombNum2, INITIAL_PENDING_BOMB_NUM);
    SetNumberSprite(mRemainingLifeNum1, INITIAL_HIT_POINT);
    SetNumberSprite(mRemainingLifeNum2, INITIAL_HIT_POINT);
    mBombString->SetTexture(mApp->GetTexture("Assets/bomb_string.png"));
    mLifeString->SetTexture(mApp->GetTexture("Assets/life_string.png"));

    // SET SCALE
    mBombString->SetScale(STRING_SCALE);
    mLifeString->SetScale(STRING_SCALE);

    SetRotation(0);
}

TurnManager::~TurnManager()
{
}

void TurnManager::UpdateActor(float deltaTime)
{
    switch(mPhase)
    {
        case DISTRIBUTE_BOMB :
            if(mDistributeBomb == 0)
            {
                mCurrentPlayer->GetBomb();
                if(mCurrentPlayer == mPlayer1) SetNumberSprite(mRemainingBombNum1, mPlayer1->GetPendingBombNum());
                else SetNumberSprite(mRemainingBombNum2, mPlayer2->GetPendingBombNum());
            }
            if(mCurrentPlayer == mPlayer2) mDistributeBomb == DISTRIBUTE_BOMB_TURN - 1 ? mDistributeBomb = 0 : mDistributeBomb++;
            mPhase = GET_CANDIDATE_FIELDS;
            break;

        case GET_CANDIDATE_FIELDS :
            mCandFields = GetCandFields(mApp->GetFields(), mCurrentPlayer->GetCurrentField());
            mPhase = CREATE_CURSOR;
            //std::cout << "get_cand_fields" << std::endl;
            break;

        case CREATE_CURSOR :
            mCursor = new Cursor(mApp, this, mTurn);
            mPhase = CREATE_CAND_FIELD_SPRITE;
            //std::cout << "create_cursor" << std::endl;
            break;

        case CREATE_CAND_FIELD_SPRITE :
            for(auto field : mCandFields)
            {
                field->CreateCandSprite(this->mApp, mTurn);
            }
            // CHOOSE MACUALY ONLY IF PALYER IS MANUAL
            if(mCurrentPlayer->GetPlayerType() == MANUAL_PLAYER) mPhase = MANUAL_CHOOSE_FIELD;
            else mPhase = AUTOMATIC_CHOOSE_FIELD;
            //std::cout << "create_cand_field_sprite" << std::endl;
            break;

        case AUTOMATIC_CHOOSE_FIELD :
            {
                auto newField = mCurrentPlayer->ChooseField(mCandFields);
                mCurrentPlayer->SetDestinationField(newField);
            }
            mPhase = DELETE_CAND_FIELD_SPITE;
            break;

        case DELETE_CURSOR :
            //std::cout << "chooose_and_mobe_fields" << std::endl;
            delete mCursor;
            mPhase = CHANGE_PLAYER;
            //std::cout << "delete_cursor" << std::endl;
            break;

        case DELETE_CAND_FIELD_SPITE :
            for(auto field : mCandFields)
            {
                field->DeleteCandSprite();
            }
            mCurrentPlayer->SetIsMoving(true);
            mPhase = MOVE_TO_DESTINATION_FIELD;
            //std::cout << "delete_cand_fields_sprite" << std::endl;
            break;

        case MOVE_TO_DESTINATION_FIELD :
            if(mCurrentPlayer->GetIsMoving()) break;
            else mPhase = DECREMENT_OPPOSITE_PLAYERS_BOMB;

        case DECREMENT_OPPOSITE_PLAYERS_BOMB :
            for(auto bomb : mApp->GetSettedBombs())
            {
                if(bomb->GetBombOwner() == mOppositePlayer)
                {
                    //std::cout << "dec" << std::endl;
                    bomb->DecrementCount();
                }
            }
            mPhase = CHECK_BOMB_COUNT;
            //std::cout << "decreametn bomb" << std::endl;
            break;

        case CHECK_BOMB_COUNT :
            for(auto bomb : mApp->GetSettedBombs())
            {
                if(bomb->GetBombOwner() == mOppositePlayer)
                {
                   if(bomb->CheckBombCount())
                   {
                       // these bombs will explode in next phase
                       bomb->SetReadyToExplode();
                       // decrement hit-point in this phase
                       Explosion(bomb);
                       // bombs will be deleted in next phase
                   }
                }
            }
            
            // create explosion sprite 
            for (auto bomb : mApp->GetSettedBombs())
            {
                if(bomb->GetReadyToExplode())
                {
                    CreateExplosionAnim(bomb->GetBombField());
                    // neighber s anime
                    for(auto path : mApp->GetPaths())
                    {
                        if(path->GetNord1() == bomb->GetBombField()) 
                        {
                            CreateExplosionAnim(path->GetNord2());
                        }
                        else if(path->GetNord2() == bomb->GetBombField())
                        {
                            CreateExplosionAnim(path->GetNord1());
                        }
                    }
                    delete bomb;
                }
            }
            mPhase = EXPLOSION_ANIM;
            break;

        case EXPLOSION_ANIM :
            if(mExplosionAnim.size()!= 0) break;
            else
            {
                mPhase = CHECK_PLAYER_HIT_POINT;
                break;
            }

        case CHECK_PLAYER_HIT_POINT :
            if (mCurrentPlayer->GetHitPoint()<=0)
            {
                mCurrentPlayer->DeleteSprite();
                mPhase = ENDING;
                break;
            }
            // player cant put bomb if pending bomb num is less than 0
            if(mCurrentPlayer->GetPendingBombNum() <= 0) mPhase = DELETE_CURSOR;
            else
            {
                if(mCurrentPlayer->GetPlayerType() == MANUAL_PLAYER) mPhase = MANUAL_WHETHER_SET_BOMB;
                else mPhase = AUTOMATIC_WHETHER_SET_BOMB;
            }
            //std::cout << "check_bomb_count" << std::endl;
            break;

        case AUTOMATIC_WHETHER_SET_BOMB :
            {
                int timeLimit = mCurrentPlayer->ChooseTimeLimit();
                if(timeLimit != 0) SetBomb(timeLimit);
                mPhase = DELETE_CURSOR;
            }
            break;

        case CHANGE_PLAYER :
            std::swap(mCurrentPlayer, mOppositePlayer);
            mTurn = !mTurn;
            mPhase = DISTRIBUTE_BOMB;
            //std::cout << "change_plyaer" << std::endl;
            break;

        default :
            break;
    }
}

void TurnManager::ActorInput(SDL_Event &event)
{
    switch(mPhase)
    {
        case MANUAL_CHOOSE_FIELD :
            ChooseField(event);
            break;

        case MANUAL_WHETHER_SET_BOMB :
            ChooseWhetherSetBomb(event);
            break;

        case ENDING :
            //std::cout << "ending" << std::endl;
            mApp->SetIsRunning(false);
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
        for(auto path : mApp->GetPaths())
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
    //if(mCursor == nullptr) mCursor = new Cursor(this->mApp, this);
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
                mCurrentPlayer->SetDestinationField(*iter);
                mPhase = DELETE_CAND_FIELD_SPITE;
            }
        }
        break;
    default:
        break;
    }
}

void TurnManager::SetNumberSprite(SpriteComponent* sc, int num)
{
    assert(sc != nullptr);
    switch(num){
        case 0 :
            sc->SetTexture(mApp->GetTexture("Assets/zero.png"));
            break;
        case 1 : 
            sc->SetTexture(mApp->GetTexture("Assets/one.png"));
            break;
        case 2 : 
            sc->SetTexture(mApp->GetTexture("Assets/two.png"));
            break;
        case 3 : 
            sc->SetTexture(mApp->GetTexture("Assets/three.png"));
            break;
        case 4 : 
            sc->SetTexture(mApp->GetTexture("Assets/four.png"));
            break;
        default :
            break;
    }
}

void TurnManager::ChooseWhetherSetBomb(SDL_Event &event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
            {
                auto key = event.key.keysym.sym;
                if(key == SDLK_1)
                {
                    // decrement pending bomb num in setbomb of player
                    SetBomb(1);
                    mPhase = DELETE_CURSOR;
                    break;
                }
                if(key == SDLK_2)
                {
                    SetBomb(2);
                    mPhase = DELETE_CURSOR;
                    break;
                }
                if(key == SDLK_3)
                {
                    SetBomb(3);
                    mPhase = DELETE_CURSOR;
                    break;
                }
                if(key == SDLK_4)
                {
                    SetBomb(4);
                    mPhase = DELETE_CURSOR;
                    break;
                }
                if(key == SDLK_n)
                {
                    mPhase = DELETE_CURSOR;
                    break;
                }
            }
            break;
        default:
            break;
    }
}

void TurnManager::SetBomb(int count)
{
    mCurrentPlayer->SetBomb(count, mTurn);
    if(mTurn) SetNumberSprite(mRemainingBombNum1, mPlayer1->GetPendingBombNum());
    else SetNumberSprite(mRemainingBombNum2, mPlayer2->GetPendingBombNum());
}

void TurnManager::Explosion(Bomb *bomb)
{
    // bomb field
    Field* bf = bomb->GetBombField();
    // target field
    Field* tf = mCurrentPlayer->GetCurrentField();
    if(bf == tf)
    {
        mCurrentPlayer->DecrementHitPoint();
        if(mTurn) SetNumberSprite(mRemainingLifeNum1, mCurrentPlayer->GetHitPoint());
        else SetNumberSprite(mRemainingLifeNum2, mCurrentPlayer->GetHitPoint());
    }
    for(auto path : mApp->GetPaths())
    {
        if((path->GetNord1() == bf && path->GetNord2() == tf) || (path->GetNord2() == bf && path->GetNord1() == tf))
        {
            mCurrentPlayer->DecrementHitPoint();
            if(mTurn) SetNumberSprite(mRemainingLifeNum1, mCurrentPlayer->GetHitPoint());
            else SetNumberSprite(mRemainingLifeNum2, mCurrentPlayer->GetHitPoint());
        }
    }
}

void TurnManager::CreateExplosionAnim(Actor *owner)
{
    ExplosionAnimSpriteComponent* ea = new ExplosionAnimSpriteComponent(owner, 150, !mTurn, this);
    AddExplosionAnim(ea);
}

void TurnManager::AddExplosionAnim(ExplosionAnimSpriteComponent *ea)
{
    mExplosionAnim.push_back(ea);
}

void TurnManager::RemoveExplosionAnim(ExplosionAnimSpriteComponent* ea)
{
    auto iter = std::find(mExplosionAnim.begin(), mExplosionAnim.end(), ea);
    if(iter != mExplosionAnim.end())
    {
        mExplosionAnim.erase(iter);
    }
}