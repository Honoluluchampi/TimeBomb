#pragma once

class TurnManager
{
public:
    TurnManager(class Game* game, class TBPlayer* player1, class TBPlayer* player2);
    ~TurnManager();

    

private:
    class Game* mGame;
    class TBPlayer* mPlayer1;
    class TBPlayer* mPlayer2;

    // represent which current turn is. (true:1, flase:2)
    bool mTurn;
};