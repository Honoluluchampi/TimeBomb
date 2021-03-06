#pragma once
#include "Actor.h"

class Cursor : public Actor
{
public:
    Cursor(class TimeBombApp *game, class TurnManager *manager, bool turn);
    ~Cursor();

    void ChangePointingField(class Field *field);
    class Field* GetPointingField(){return mPointingField;}
private:
    class Field *mPointingField;
    class TurnManager *mManager;
};