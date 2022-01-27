#pragma once
#include "TBPlayer.h"
#include <memory>
class RandomPlayer : public TBPlayer
{
public:
    RandomPlayer(std::unique_ptr<Game>& game, class Field* ip, bool player, const int &bombnum, int playerType = 0);
    ~RandomPlayer(){};

    class Field* ChooseField(std::vector<class Field*> candFields) override;
    int ChooseTimeLimit() override;
};