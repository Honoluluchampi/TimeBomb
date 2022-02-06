#include "TimeBombApp.h"
#include "Field.h"
#include "Path.h"
#include "TBPlayer.h"
#include "Players.h"
#include "TurnManager.h"
#include <algorithm> //for std::find

void TimeBombApp::LoadData()
{
  // create field
  for(auto vec : FIELD_POSITION)
  {
    new Field(this, vec.x, vec.y);
  }

  // create path
  for(auto path : PATH_EDGES)
  {
    new Path(this, mFields[path.first], mFields[path.second]);
  }

  // create players
  mTBPlayer1 = new TBPlayer(this, mFields[INITIAL_FIELD_FOR_1], true, INITIAL_PENDING_BOMB_NUM, MANUAL_PLAYER);
  mTBPlayer2 = new RandomPlayer(this, mFields[INITIAL_FIELD_FOR_2], false, INITIAL_PENDING_BOMB_NUM, RANDOM_PLAYER);

  // create TurnManager
  mTurnManager = new TurnManager(this, mTBPlayer1, mTBPlayer2);
}

void TimeBombApp::AddField(Field *field)
{
  mFields.push_back(field);
}

void TimeBombApp::RemoveField(Field *field)
{
  auto iter = std::find(mFields.begin(), mFields.end(), field);
  if(iter != mFields.end())
  {
    mFields.erase(iter);
  }
}

void TimeBombApp::AddPath(Path *path)
{
  mPaths.push_back(path);
}

void TimeBombApp::RemovePath(Path *path)
{
  auto iter = std::find(mPaths.begin(), mPaths.end(), path);
  if(iter != mPaths.end())
  {
    mPaths.erase(iter);
  }
}

void TimeBombApp::AddSettedBomb(Bomb *bomb)
{
  mSettedBombs.push_back(bomb);
}

void TimeBombApp::RemoveSettedBomb(Bomb *bomb)
{
  auto iter = std::find(mSettedBombs.begin(), mSettedBombs.end(), bomb);
  if(iter != mSettedBombs.end())
  {
    std::iter_swap(iter, mSettedBombs.end() - 1);
    mSettedBombs.pop_back();
  }
}