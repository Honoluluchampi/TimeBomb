#pragma once
#include "Actor.h"
#include <memory>
class Cursor : public Actor
{
public:
    Cursor(std::unique_ptr<class Game>& game, class TurnManager *manager, bool turn);
    ~Cursor();

    void ChangePointingField(class Field *field);
    class Field* GetPointingField(){return mPointingField;}
private:
    class Field *mPointingField;
    class TurnManager *mManager;
};