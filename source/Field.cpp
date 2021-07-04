#include "Game.h"
#include "Field.h"
#include "SpriteComponent.h"
#include "Math.h"
#include <string>
#include "Path.h"
#include <algorithm>

//std::string DIRNAME = "/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/";

Field::Field(Game *game, float x, float y) : Actor(game)
{
    SetPosition(Vector2(x,y));
    SetRotation(0);

    SpriteComponent* sc = new SpriteComponent(this, 50);
    sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/field.png"));

    game -> AddField(this);
    // floating move
    //void Field::UpdateActor(float deltaTime)
}

Field::~Field()
{
    GetGame()->RemoveField(this);
}

void Field::CreateCandSprite(Game *game, bool turn)
{
    //cand sprite component
    mTemporalCandSprite = new SpriteComponent(this, 55);
    if(turn) mTemporalCandSprite->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/blue_cand_field.png"));
    else mTemporalCandSprite->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/red_cand_field.png"));
}

void Field::DeleteCandSprite()
{
    delete mTemporalCandSprite;
}

void Field::AddPath(Path *path)
{
    mPaths.push_back(path);
}

void Field::RemovePath(Path *path)
{
    auto iter = std::find(mPaths.begin(), mPaths.end(), path);
    // memory leak ? double delete?
    mPaths.erase(iter);
}