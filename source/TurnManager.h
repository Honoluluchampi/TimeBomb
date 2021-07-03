#pragma once
#include <vector>
#include "Actor.h"

enum Phase
{
    CREATE_CURSOR,
    CHOOSE_FIELD,
    DELETE_CURSOR,
    CHANGE_PLAYER
};

class TurnManager : public Actor
{
public:
    TurnManager(class Game* game, class TBPlayer* player1, class TBPlayer* player2);
    ~TurnManager();

    // turn over the turn
    void ChangeTurn();
    // organize actions in a turn
    void ActorInput(const uint8_t* keyState)override;
    //void TurnSequence(bool turn);
    class TBPlayer* GetCurrentPlayer(){return mCurrentPlayer;}
    // returns fields where players can visit
    //std::vector<class Field*> GetCandFields(std::vector<class Field*>, class Field*);
    void ChangeCursor();
    void ChooseField(const uint8_t *keyState);


private:
    class TBPlayer* mPlayer1;
    class TBPlayer* mPlayer2;
    class TBPlayer* mCurrentPlayer;
    class Cursor* mCursor;

    // -1 : not input phase
    // 0 : choosing field phase
    // 1 : deciding whether set a bomb phase
    // 2 : deciding time limit phase
    int mPhase;
};