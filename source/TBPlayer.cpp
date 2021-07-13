#include "TBPlayer.h"
#include "Game.h"
#include "Bomb.h"
#include "SpriteComponent.h"
#include "Field.h"
#include <algorithm>
#include <iostream>

TBPlayer::TBPlayer(Game *game, Field *ip, bool player, const int &bombnum) : 
Actor(game),  mHitPoint(INITIAL_HIT_POINT), mCurrentField(ip), mIsMoving(false), mTime(0.0f)
{
    mBallSprite = new SpriteComponent(this, 100, MANUAL_POSITIONING);
    if(player) mBallSprite->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/blue_ball.png"));
    else mBallSprite->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/red_ball.png"));
    mBallSprite->SetPosition(mCurrentField->GetPosition());
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
    Vector2 floatingPos = Vector2(0, STANDARD_HEIGHT + std::sin(mTime*3.0f)*AMPLITUDE);
    mBallSprite->SetPosition(GetPosition() + floatingPos);
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

void TBPlayer::SetBomb(int count)
{
    if(mPendingBombNum <= 0){
        return;
    }
    mPendingBombNum--;
    Bomb *bomb = new Bomb(GetGame(), this, mCurrentField, count);
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