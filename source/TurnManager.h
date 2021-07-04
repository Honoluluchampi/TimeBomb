#pragma once
#include <vector>
#include "Actor.h"

enum Phase
{
    GET_CANDIDATE_FIELDS,
    CREATE_CURSOR,
    CREATE_CAND_FIELD_SPRITE,
    CHOOSE_AND_MOVE_FIELD,
    DELETE_CURSOR,
    DELETE_CAND_FIELD_SPITE,
    CHANGE_PLAYER
};

class TurnManager : public Actor
{
public:
    TurnManager(class Game* game, class TBPlayer* player1, class TBPlayer* player2);
    ~TurnManager();

    // turn over the turn
    void ChangeTurn();
    // organize actions which dont depend on input
    void UpdateActor(float deltaTime)override;
    // organize actions in a turn
    void ActorInput(SDL_Event &event)override;
    //void TurnSequence(bool turn);
    class TBPlayer* GetCurrentPlayer(){return mCurrentPlayer;}
    // returns fields where players can visit
    std::vector<class Field*> GetCandFields(std::vector<class Field*>, class Field*);
    void ChooseField(SDL_Event &event);
    void MovePlayer(class Field* field);


private:
    class TBPlayer* mPlayer1;
    class TBPlayer* mPlayer2;
    class TBPlayer* mCurrentPlayer;
    class Cursor* mCursor;
    std::vector<class Field*> mCandFields;

    int mPhase;
    bool mTurn; // player1:true, player2:false
};