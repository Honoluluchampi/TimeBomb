#include "Game.h"
#include "Field.h"
#include "SpriteComponent.h"
#include "Math.h"
#include <string>
#include "Path.h"
#include <algorithm>

Field::Field(std::unique_ptr<Game>& game, float x, float y) : Actor(game)
{
    SetPosition(Vector2(x,y));
    SetRotation(0);

    SpriteComponent* sc = new SpriteComponent(this, 50);
    sc->SetTexture(game->GetTexture("Assets/green_field.png"));

    game -> AddField(this);
}

Field::~Field()
{
    GetGame()->RemoveField(this);
    for(auto path : GetGame()->GetPaths())
    {
        if(path->GetNord1() == this || path->GetNord2() == this)
        {
            GetGame()->RemovePath(path);
        }
    }
}

void Field::CreateCandSprite(std::unique_ptr<Game>& game, bool turn)
{
    //cand sprite component
    mTemporalCandSprite = new SpriteComponent(this, 55);
    if(turn) mTemporalCandSprite->SetTexture(game->GetTexture("Assets/blue_cand_field.png"));
    else mTemporalCandSprite->SetTexture(game->GetTexture("Assets/red_cand_field.png"));
}

void Field::DeleteCandSprite()
{
    delete mTemporalCandSprite;
}