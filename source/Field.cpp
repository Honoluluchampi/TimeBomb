#include "Game.h"
#include "Field.h"
#include "SpriteComponent.h"
#include "Math.h"
#include <string>

//std::string DIRNAME = "/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/";

Field::Field(Game *game, float x, float y) : Actor(game)
{
    SetPosition(Vector2(x,y));
    SetRotation(0);

    SpriteComponent* sc = new SpriteComponent(this, 50);
    sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/dotpict.png"));

    game -> AddField(this);
    // floating move
    //void Field::UpdateActor(float deltaTime)
}

Field::~Field()
{
    GetGame()->RemoveField(this);
}