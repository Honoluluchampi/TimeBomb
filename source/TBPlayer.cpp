#include "TBPlayer.h"
#include "Game.h"
//#include "Bomb.h"
#include "SpriteComponent.h"
#include "Field.h"

TBPlayer::TBPlayer(Game *game, Field *ip, bool player) : Actor(game), mCurrentField(ip)
{
    SpriteComponent *sc = new SpriteComponent(this, 100);
    if(player) sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/blue_ball.png"));
    else sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/red_ball.png"));
    SetPosition(mCurrentField->GetPosition());
    SetRotation(mCurrentField->GetRotation());
}

TBPlayer::~TBPlayer()
{

}

void TBPlayer::ChangeCurrentField(Field *field)
{
    mCurrentField = field;
    SetPosition(field->GetPosition());
}

//void TBPlayer::GetBomb(Bomb *bomb)
//{
    //mPendingBombs.push_back(bomb);
//}

//void TBPlayer::SetBomb()
//{

//}
