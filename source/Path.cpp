#include "Path.h"
#include "Field.h"

Path::Path(Game *game, Field *nord1, Field *nord2)
:Actor(game), mNord1(nord1), mNord2(nord2), mWeight(DEFAULT_HEAVY_WEIGHT)
{
    mNord1->AddPath(this);
    mNord2->AddPath(this);
}

Path::~Path()
{
    
}