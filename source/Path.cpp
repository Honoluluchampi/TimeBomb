#include "Path.h"
#include "Field.h"

Path::Path(Game *game, Field *nord1, Field *nord2)
:Actor(game), mNord1(nord1), mNord2(nord2)
{

}

Path::~Path()
{
    
}