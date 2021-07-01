#pragma once
#include "Actor.h"

const int INITIAL_BOMB = 2;

class TBPlayer : public Actor
{
public:
    TBPlayer(class Game* game);
    ~TBPlayer(); // call the ending manager

    //void GetBomb(class Bomb* bomb);
    //void SetBomb();

private:
    //std::vector<class Bomb*> mPendingBombs;
    //std::vector<class Bomb*> mSettedBombs;
    //int mBombNum;
};