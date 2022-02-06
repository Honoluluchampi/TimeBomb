#pragma once
#include "Actor.h"

class Bomb : public Actor
{
public:
    Bomb(class TimeBombApp* app, class TBPlayer* owner,
     class Field *field, int count, bool visible);
    ~Bomb();

    // change count function
    class TBPlayer* GetBombOwner(){return mBombOwner;}
    class Field* GetBombField(){return mField;}
    void SetCount(int &count){mCount = count;}
    void SetCountSprite();
    void SetReadyToExplode(){mReadyToExplode = true;}
    bool GetReadyToExplode(){return mReadyToExplode;}
    void DecrementCount();
    bool CheckBombCount();
    
private:
    class TimeBombApp* mApp;
    int mCount;
    bool mReadyToExplode;
    class TBPlayer* mBombOwner;
    class SpriteComponent* mCountSprite;
    class Field* mField;
    bool mIsVisible;
};