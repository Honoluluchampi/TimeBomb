#pragma once
#include "Actor.h"

const int INITIAL_BOMB = 2;

class TBPlayer : public Actor
{
public:
    TBPlayer(class Game* game, class Field* ip); // ip : initial position
    ~TBPlayer(); // call the ending manager

    // getter
    class Field* GetCurrentField(){return mCurrentField;}

    void ChangeCurrentField(class Field *field);

    //void GetBomb(class Bomb* bomb);
    //void SetBomb();

private:
    //std::vector<class Bomb*> mPendingBombs;
    //std::vector<class Bomb*> mSettedBombs;
    //int mBombNum;
    class Field* mCurrentField;
};