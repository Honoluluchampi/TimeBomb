#include "Bomb.h"
#include "Game.h"
#include "TBPlayer.h"

Bomb::Bomb(Game *game, TBPlayer *owner) : Actor(game), mBombOwner(owner)
{
    owner->GetBomb(this);
}