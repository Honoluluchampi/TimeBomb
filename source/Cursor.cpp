#include "Cursor.h"
#include "Game.h"
#include "Field.h"
#include "TurnManager.h"
#include "TBPlayer.h"

Cursor::Cursor(Game *game, TurnManager *manager) : //TurnManager *manager) : 
Actor(game), mManager(manager)
{
    // get current field
    mPointingField = mManager->GetCurrentPlayer()->GetCurrentField();
    this->SetPosition(mPointingField->GetPosition());

    SpriteComponent* sc = new SpriteComponent(this, 60);
    sc->SetTexture(game->GetTexture("/Users/toyotariku/Library/Mobile Documents/com~apple~CloudDocs/TimeBomb/cursor.png"));
}

Cursor::~Cursor()
{
}

void Cursor::ChangePointingField(Field *field)
{
    mPointingField = field;
    this->SetPosition(mPointingField->GetPosition());
}
