#include "TBPlayer.h"
#include "Game.h"
#include "Bomb.h"
#include "SpriteComponent.h"
#include "Field.h"
#include <algorithm>
#include <cmath>
#include <iostream>

TBPlayer::TBPlayer(Game *game, Field *ip, bool player, const int &bombnum, int playerType) : 
Actor(game),  mHitPoint(INITIAL_HIT_POINT), mCurrentField(ip), mIsMoving(false), mTime(0.0f), mPlayerType(playerType)
{
    // ball sprite
    mBallSprite = new SpriteComponent(this, 100, MANUAL_POSITIONING);
    if(player) mBallSprite->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/blue_ball.png"));
    else mBallSprite->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/red_ball.png"));
    mBallSprite->SetPosition(mCurrentField->GetPosition());

    // shadow sprite
    mShadowSprite = new SpriteComponent(this, 100);
    mShadowSprite->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/ball_shadow.png"));
    SetPosition(mCurrentField->GetPosition());
    SetRotation(mCurrentField->GetRotation());

    mPendingBombNum = bombnum;
}

TBPlayer::~TBPlayer()
{
}

void TBPlayer::UpdateActor(float deltaTime)
{
    mTime += deltaTime;
    Vector2 floatingPos = Vector2(0, STANDARD_HEIGHT + std::sin(mTime*VIBRATION_BOOST)*AMPLITUDE);
    mBallSprite->SetPosition(GetPosition() + floatingPos);
    if(mIsMoving)
    {
        MoveToNextField(deltaTime);
    }
}

void TBPlayer::ChangeCurrentField(Field *field)
{
    mCurrentField = field;
    SetPosition(field->GetPosition());
}

void TBPlayer::GetBomb()
{
    if(mPendingBombNum < MAX_PENDING_BOMB_NUM)
    {
        mPendingBombNum++;
    }
}

void TBPlayer::SetBomb(int count, bool visible)
{
    if(mPendingBombNum <= 0){
        return;
    }
    mPendingBombNum--;
    Bomb *bomb = new Bomb(GetGame(), this, mCurrentField, count, visible);
    GetGame()->AddSettedBomb(bomb);
    std::cout << "before add" << std::endl;
    std::cout << "after add" << std::endl;
}

bool TBPlayer::CheckHitPoint()
{
    if(mHitPoint <= 0)
    {
        delete this;
        return true;
    }
    return false;
}

void TBPlayer::MoveToNextField(float deltaTime)
{
    float dist = std::pow(GetPosition().x - mDestinationField->GetPosition().x, 2.0) + std::pow(GetPosition().y - mDestinationField->GetPosition().y, 2.0);
    if(dist < 50)
    {
        mIsMoving = false;
        ChangeCurrentField(mDestinationField);
        return;
    }
    SetPosition(GetPosition() + (mForwardVec * deltaTime)*MOVE_BOOST);
}

void TBPlayer::SetDestinationField(class Field *field)
{
    mDestinationField = field;
    mForwardVec = mDestinationField->GetPosition() - mCurrentField->GetPosition();
    mForwardVec.Normalize();
}