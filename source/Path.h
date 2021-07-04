#pragma once
#include "Actor.h"

const int DEFAULT_WEIGHT = 1;
const int DEFAULT_HEAVY_WEIGHT = 10000;

class Path : public Actor
{
public:
    Path(class Game *game, class Field *nord1, class Field *nord2);
    ~Path();

    void ChangeWeightHeavier(int weight = DEFAULT_HEAVY_WEIGHT){mWeight = weight;}
    void ChangeWeightLighter(int weight = DEFAULT_WEIGHT){mWeight = weight;}
    class Field* GetNord1(){return mNord1;}
    class Field* GetNord2(){return mNord2;}

private:
    class Field *mNord1;
    class Field *mNord2;
    int mWeight;
};