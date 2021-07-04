#pragma once
#include "Actor.h"

class Cursor : public Actor
{
public:
    Cursor(class Game *game, class TurnManager *manager);
    ~Cursor();

    void ChangePointingField(class Field *field);
    class Field* GetPointingField(){return mPointingField;}
private:
    class Field *mPointingField;
    class TurnManager *mManager;
};