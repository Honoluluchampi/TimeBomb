#include "Game.h"
// player
const int PLAYER_STEP = 2;
const int DISTRIBUTE_BOMB_TURN = 3;
const float STANDARD_HEIGHT = -25;
const float AMPLITUDE = 10;
const float VIBRATION_BOOST = 4.0f;
const float MOVE_BOOST = 300.0f;
const float PATH_SCALE_X = 0.006f;
const float PATH_SCALE_Y = 0.55f;
const Vector2 PATH_SLIDE = Vector2(20.0f, 65.0f);
const int MAX_PENDING_BOMB_NUM = 3;
const int INITIAL_PENDING_BOMB_NUM = 3;
const float EXPLOSION_ANIM_FPS = 16.0f;
const int INITIAL_HIT_POINT = 3;
const int INITIAL_FIELD_NUM = 16;
const Vector2 FIELD_POSITION[] = {
  Vector2(WIDTH/7, HEIGHT/5),
  Vector2(WIDTH*1/3, HEIGHT*1/4),
  Vector2(WIDTH*4/7, HEIGHT*2/9),
  Vector2(WIDTH*3/4, HEIGHT*1/7),
  Vector2(WIDTH*8/9, HEIGHT*2/9),
  Vector2(WIDTH*1/6, HEIGHT*5/9),
  Vector2(WIDTH*2/7, HEIGHT*3/7),
  Vector2(WIDTH*1/2, HEIGHT*4/9),
  Vector2(WIDTH*4/5, HEIGHT*1/3),
  Vector2(WIDTH*1/8, HEIGHT*5/6),
  Vector2(WIDTH*1/3, HEIGHT*2/3),
  Vector2(WIDTH*3/5, HEIGHT*3/5),
  Vector2(WIDTH*8/9, HEIGHT*2/3),
  Vector2(WIDTH*1/3, HEIGHT*7/8),
  Vector2(WIDTH*3/5, HEIGHT*6/7),
  Vector2(WIDTH*6/7, HEIGHT*5/6)
};
const std::pair<int,int> PATH_EDGES[] = {
  {1,0}, {2,1}, {3,2}, {4,3}, {5,0}, {6,1}, {7,2}, {8,4}, {6,5}, {7,6}, {8,7},
  {9,5}, {10,9}, {10,7}, {11,8}, {12,8}, {7,11}, {12,11}, {10,13}, {11,14}, {15,12}, {14,13}, {15,14}
};
const int INITIAL_FIELD_FOR_1 = 0;
const int INITIAL_FIELD_FOR_2 = 15;

const Vector2 PENDING_BOMB_STRING_POSITION = Vector2(WIDTH * 7/9, HEIGHT * 1/11);
const Vector2 PENDING_BOMB_NUM_POSITION1 = Vector2(WIDTH * 10/12 + 10, HEIGHT * 1/11);
const Vector2 PENDING_BOMB_NUM_POSITION2 = Vector2(WIDTH * 10/11, HEIGHT * 1/11);

const Vector2 HIT_POINT_STRING_POSITION = Vector2(WIDTH * 2/9, HEIGHT * 1/11);
const Vector2 HIT_POINT_POSITION1 = Vector2(WIDTH * 2/7, HEIGHT * 1/11);
const Vector2 HIT_POINT_POSITION2 = Vector2(WIDTH * 5/14, HEIGHT * 1/11);

const float STRING_SCALE = 0.2;

class TimeBombApp : public Game
{
public:
    TimeBombApp() : Game() {}
    // game specific
    void AddField(class Field* field);
    void RemoveField(class Field* field);
    std::vector<class Field*> GetFields() {return mFields;}

    void AddPath(class Path* path);
    void RemovePath(class Path* path);
    std::vector<class Path*> GetPaths() { return mPaths;}

    void AddSettedBomb(class Bomb* bomb);
    void RemoveSettedBomb(class Bomb* bomb);
    std::vector<class Bomb*> GetSettedBombs() {return mSettedBombs;}
private:
    void LoadData() override;
    class TBPlayer* mTBPlayer1;
    class TBPlayer* mTBPlayer2;
    class TurnManager* mTurnManager;
    std::vector<class Field*> mFields;
    std::vector<class Path*> mPaths;
    std::vector<class Bomb*> mSettedBombs;
    std::vector<class AnimeSpriteComponent*> mExplosionAnime;
};