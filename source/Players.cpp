#include "Players.h"
#include "Game.h"
#include <random>

RandomPlayer::RandomPlayer(class Game* game, class Field* ip, bool player, const int &bombnum, int playerType)
: TBPlayer(game, ip, player, bombnum, playerType)
{}

Field* RandomPlayer::ChooseField (std::vector<Field *> candFields)
{
    int n = candFields.size();
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(0,n-1);
    return candFields[distr(eng)];
}

int RandomPlayer::ChooseTimeLimit()
{
    int n = 5; // 0, 1, 2, 3, 4
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> distr(0, n-1);
    return distr(eng);
}