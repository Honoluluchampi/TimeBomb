#pragma once
#include "Actor.h"

const int INITIAL_BOMB = 2;

class TBPlayer : public Actor
{
public:
    TBPlayer(class Game* game, class Field* ip, bool player, const int &bombnum); // ip : initial position
    ~TBPlayer(); // call the ending manager

    // getter
    class Field* GetCurrentField(){return mCurrentField;}
    void ChangeCurrentField(class Field *field);

    void GetBomb();
    void SetBomb(int count);

    void SetCountSprite(int &count);
    void SetCountSprite(const int &count);

    int GetPendingBombNum(){return mPendingBombNum;}
private:
    int mPendingBombNum;
    class Field* mCurrentField;
};