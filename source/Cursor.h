#pragma once
#include "Actor.h"

class Cursor : public Actor
{
public:
    Cursor(class Game *game, class TurnManager *manager);
    ~Cursor();

    void ChangeChosingField(class Field *field);
private:
    class Field *mPointingField;
    class TurnManager *mManager;
};