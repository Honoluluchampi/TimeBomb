#include "TBPlayer.h"
#include "Game.h"
//#include "Bomb.h"
#include "SpriteComponent.h"
#include "Field.h"

TBPlayer::TBPlayer(Game *game, Field *ip) : Actor(game), mCurrentField(ip)
{
    SpriteComponent *sc = new SpriteComponent(this, 100);
    sc->SetTexture(game->GetTexture(BLUE_BALL_IMAGE_PATH));
    SetPosition(mCurrentField->GetPosition());
    SetRotation(mCurrentField->GetRotation());
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

