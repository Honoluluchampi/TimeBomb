#pragma once
#include "Actor.h"
#include "Math.h"

class TBPlayer : public Actor
{
public:
    TBPlayer(class Game* game, class Field* ip, bool player, const int &bombnum); // ip : initial position
    ~TBPlayer(); // call the ending manager

    void UpdateActor(float deltaTime);
    void MoveToNextField(float deltaTime);

    // getter setter
    class Field* GetCurrentField(){return mCurrentField;}
    void GetBomb();
    // move
    bool GetIsMoving(){return mIsMoving;}
    void SetIsMoving(bool move){mIsMoving = move;}
    // bomb
    void SetBomb(int count, bool visible);
    void SetCountSprite(int &count);
    void SetCountSprite(const int &count);
    void SetDestinationField(class Field *field);
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
    class Field* mDestinationField;
    bool mIsMoving;
    float mTime;
    Vector2 mFloatingPosition;
    Vector2 mForwardVec;
    class SpriteComponent* mBallSprite;
    class SpriteComponent* mShadowSprite;
};