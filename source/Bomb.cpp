#include "Bomb.h"
#include "Game.h"
#include "TBPlayer.h"
#include "SpriteComponent.h"
#include "Field.h"
#include <iostream>

Bomb::Bomb(std::unique_ptr<Game>& game, TBPlayer *owner, Field *field, int &count, bool visible) : 
Actor(game), mReadyToExplode(false), mBombOwner(owner), mField(field), mIsVisible(visible)
{
    // bomb sprite
    SpriteComponent *sc = new SpriteComponent(this, 130);
    sc->SetTexture(game->GetTexture("Assets/bomb.png"));
    
    // coutn sprite
    SetCount(count);
    mCountSprite = new SpriteComponent(this, 140);
    if(mIsVisible) SetCountSprite();

    // position, rotation
    SetPosition(mField->GetPosition());
    SetRotation(mField->GetRotation());

    // add in turnmanager::setbomb
    //game->AddSettedBomb(this);
}

Bomb::~Bomb()
{
    // explosion
    GetGame()->RemoveSettedBomb(this);
}

void Bomb::SetCountSprite()
{
    switch(mCount){
        case 1 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("Assets/one.png"));
            break;
        case 2 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("Assets/two.png"));
            break;
        case 3 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("Assets/three.png"));
            break;
        case 4 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("Assets/four.png"));
            break;
        default :
            break;
    }
}

void Bomb::DecrementCount()
{
    mCount--;
    if(mIsVisible) SetCountSprite();
}

bool Bomb::CheckBombCount()
{
    // delete by turn manager
    if(mCount <= 0) return true;
    else return false;
}