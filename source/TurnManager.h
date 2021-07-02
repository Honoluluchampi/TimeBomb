#pragma once
#include <vector>

class TurnManager
{
public:
    TurnManager(class Game* game, class TBPlayer* player1, class TBPlayer* player2);
    ~TurnManager();

    // turn over the turn
    void ChangeTurn();
    void TurnSequence();
    // returns fields where players can visit
    std::vector<class Field*> GetCandFields(std::vector<class Field*>);
    void ChangeCursor();
    void ChooseField();


private:
    class Game* mGame;
    class TBPlayer* mPlayer1;
    class TBPlayer* mPlayer2;

    // represent which current turn is. (true:1, flase:2)
    bool mTurn;
};