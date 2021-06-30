#include "Game.h"
#include "Field.h"
#include "SpriteComponent.h"

Field::Field(Game *game) : Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this, 50);
    sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/dotpict.png"));

    // floating move
    //void Field::UpdateActor(float deltaTime)
}