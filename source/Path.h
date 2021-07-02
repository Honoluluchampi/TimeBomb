#pragma once
#include "Actor.h"

class Path : public Actor
{
public:
    Path(class Game *game, class Field *nord1, class Field *nord2);
    ~Path();

private:
    class Field *mNord1;
    class Field *mNord2;
};