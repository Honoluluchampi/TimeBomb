#pragma once
#include <vector>
#include "Actor.h"

enum Phase
{
    DISTRIBUTE_BOMB,
    GET_CANDIDATE_FIELDS,
    CREATE_CURSOR,
    CREATE_CAND_FIELD_SPRITE,
    MANUAL_CHOOSE_FIELD,
    AUTOMATIC_CHOOSE_FIELD,
    DELETE_CURSOR,
    DELETE_CAND_FIELD_SPITE,
    MOVE_TO_DESTINATION_FIELD,
    DECREMENT_OPPOSITE_PLAYERS_BOMB,
    CHECK_BOMB_COUNT,
    EXPLOSION_ANIM,
    CHECK_PLAYER_HIT_POINT,
    MANUAL_WHETHER_SET_BOMB,
    AUTOMATIC_WHETHER_SET_BOMB,
    CHOOSE_TIME_LIMIT,
    CHANGE_PLAYER,
    ENDING
};

class TurnManager : public Actor
{
public:
    TurnManager(class TimeBombApp* game, class TBPlayer* player1, class TBPlayer* player2);
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
    void Explosion(class Bomb* bomb);
   // remaining bomb number sprite
    void SetNumberSprite(class SpriteComponent* sc, int count);
    void ChooseWhetherSetBomb(SDL_Event &event);
    void SetBomb(int count);

    void CreateExplosionAnim(class Actor* owner);
    void AddExplosionAnim(class ExplosionAnimSpriteComponent *ea);
    void RemoveExplosionAnim(class ExplosionAnimSpriteComponent* ea);
private:
    class TimeBombApp* mApp;
    class TBPlayer* mPlayer1;
    class TBPlayer* mPlayer2;
    class TBPlayer* mCurrentPlayer;
    class TBPlayer* mOppositePlayer;
    class Cursor* mCursor;
    std::vector<class Field*> mCandFields;
    class SpriteComponent* mBombString;
    class SpriteComponent* mRemainingBombNum1;
    class SpriteComponent* mRemainingBombNum2;
    class SpriteComponent* mLifeString;
    class SpriteComponent* mColon;
    class SpriteComponent* mRemainingLifeNum1;
    class SpriteComponent* mRemainingLifeNum2;
    std::vector<class ExplosionAnimSpriteComponent*> mExplosionAnim;

    int mPhase;
    bool mTurn; // player1:true, player2:false
    int mDistributeBomb;
};