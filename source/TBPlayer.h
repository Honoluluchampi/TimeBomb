#pragma once
#include "Actor.h"
#include "Math.h"

class TBPlayer : public Actor
{
public:
    TBPlayer(class Game* game, class Field* ip, bool player, const int &bombnum); // ip : initial position
    ~TBPlayer(); // call the ending manager

    void UpdateActor(float deltaTime);

    // getter setter
    class Field* GetCurrentField(){return mCurrentField;}
    void GetBomb();
    void SetBomb(int count);
    void SetCountSprite(int &count);
    void SetCountSprite(const int &count);
    int GetHitPoint(){return mHitPoint;}
    int GetPendingBombNum(){return mPendingBombNum;}

    void DecrementHitPoint(){mHitPoint--;}
    void ChangeCurrentField(class Field *field);
    // true:delete false:alive
    bool CheckHitPoint();

private:
    int mHitPoint;
    int mPendingBombNum;
    class Field* mCurrentField;
    bool mIsMoving;
    float mTime;
    Vector2 mFloatingPosition;
    class SpriteComponent* mBallSprite;
    class SpriteComponent* mShadowSprite;
};