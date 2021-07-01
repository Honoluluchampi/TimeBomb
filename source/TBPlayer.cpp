#include "TBPlayer.h"
#include "Game.h"
//#include "Bomb.h"
#include "SpriteComponent.h"

TBPlayer::TBPlayer(Game *game) : Actor(game)
{
    const std::string FIELD_IMAGE_PATH = "/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/ball_blue.png";
    SpriteComponent *sc = new SpriteComponent(this, 100);
    sc->SetTexture(game->GetTexture(FIELD_IMAGE_PATH));
}

TBPlayer::~TBPlayer()
{

}

//void TBPlayer::GetBomb(Bomb *bomb)
//{
    //mPendingBombs.push_back(bomb);
//}

//void TBPlayer::SetBomb()
//{

//}

