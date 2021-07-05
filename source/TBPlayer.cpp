#include "TBPlayer.h"
#include "Game.h"
#include "Bomb.h"
#include "SpriteComponent.h"
#include "Field.h"
#include <algorithm>
#include <iostream>

TBPlayer::TBPlayer(Game *game, Field *ip, bool player, const int &bombnum) : Actor(game), mCurrentField(ip)
{
    SpriteComponent *sc = new SpriteComponent(this, 100);
    if(player) sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/blue_ball.png"));
    else sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/red_ball.png"));
    SetPosition(mCurrentField->GetPosition());
    SetRotation(mCurrentField->GetRotation());

    mPendingBombNum = bombnum;
}

TBPlayer::~TBPlayer()
{
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
        std::cout << "set" << std::endl;
        return;
    }
    mPendingBombNum--;
    Bomb *bomb = new Bomb(GetGame(), this, mCurrentField, count);
    std::cout << "before add" << std::endl;
    std::cout << "after add" << std::endl;
}