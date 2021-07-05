#include "Path.h"
#include "Field.h"
#include "SpriteComponent.h"
#include "Game.h"
#include <cmath>

Path::Path(Game *game, Field *nord1, Field *nord2)
:Actor(game), mNord1(nord1), mNord2(nord2), mWeight(DEFAULT_HEAVY_WEIGHT)
{
    if(mNord1->GetPosition().y < mNord2->GetPosition().y) std::swap(mNord1, mNord2);
    SpriteComponent *sc = new SpriteComponent(this, 30);
    sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/path.png"));
    auto pos = mNord1->GetPosition() + mNord2->GetPosition();
    pos.x /= 2.0f; pos.y /= 2.0f;
    float rotation;
    if(std::abs(mNord1->GetPosition().x - mNord2->GetPosition().x) < 0.001f)
    {
        rotation = M_PI/2.0f;
    }
    else rotation = std::atan((mNord2->GetPosition().y-mNord1->GetPosition().y)/(mNord2->GetPosition().x - mNord1->GetPosition().x));
    SetPosition(pos);
    SetRotation(rotation);
    game->AddPath(this);
}

Path::~Path()
{
    GetGame()->RemovePath(this);
}