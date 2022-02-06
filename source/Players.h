#pragma once
#include "TBPlayer.h"

class RandomPlayer : public TBPlayer
{
public:
    RandomPlayer(class TimeBombApp* game, class Field* ip, bool player, const int &bombnum, int playerType = 0);
    ~RandomPlayer(){};

    class Field* ChooseField(std::vector<class Field*> candFields) override;
    int ChooseTimeLimit() override;
};