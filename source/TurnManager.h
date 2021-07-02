#pragma once
#include <vector>
#include "Actor.h"

class TurnManager : public Actor
{
public:
    TurnManager(class Game* game, class TBPlayer* player1, class TBPlayer* player2);
    ~TurnManager();

    // turn over the turn
    void ChangeTurn();
    // organize actions in a turn
    void TurnSequence(bool turn);
    class TBPlayer* GetCurrentPlayer(bool turn);
    // returns fields where players can visit
    std::vector<class Field*> GetCandFields(std::vector<class Field*>, class Field*);
    void ChangeCursor();
    void ChooseField();


private:
    class TBPlayer* mPlayer1;
    class TBPlayer* mPlayer2;

    // represent which current turn is. (true:1, flase:2)
    bool mTurn;
};