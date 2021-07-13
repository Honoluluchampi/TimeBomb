#include "Bomb.h"
#include "Game.h"
#include "TBPlayer.h"
#include "SpriteComponent.h"
#include "Field.h"
#include <iostream>

Bomb::Bomb(Game *game, TBPlayer *owner, Field *field, int &count) : 
Actor(game), mReadyToExplode(false), mBombOwner(owner), mField(field)
{
    // bomb sprite
    SpriteComponent *sc = new SpriteComponent(this, 130);
    sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/bomb.png"));
    
    // coutn sprite
    SetCount(count);
    mCountSprite = new SpriteComponent(this, 140);
    SetCountSprite();

    // position, rotation
    SetPosition(mField->GetPosition());
    SetRotation(mField->GetRotation());

    // add in turnmanager::setbomb
    //game->AddSettedBomb(this);
}

Bomb::~Bomb()
{
    // explosion
    
    std::cout << "Deconstruct bomb " << std::endl;
    GetGame()->RemoveSettedBomb(this);
}

void Bomb::SetCountSprite()
{
    switch(mCount){
        case 1 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/one.png"));
            break;
        case 2 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/two.png"));
            break;
        case 3 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/three.png"));
            break;
        case 4 : 
            mCountSprite->SetTexture(GetGame()->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/four.png"));
            break;
        default :
            break;
    }
}

void Bomb::DecrementCount()
{
    mCount--;
    std::cout << "decrement" << std::endl;
    SetCountSprite();
}

bool Bomb::CheckBombCount()
{
    // delete by turn manager
    if(mCount <= 0) return true;
    else return false;
}