#include "Cursor.h"
#include "Game.h"
#include "Field.h"
#include "TurnManager.h"
#include "TBPlayer.h"

Cursor::Cursor(Game *game, TurnManager *manager, bool turn) : //TurnManager *manager) : 
Actor(game), mManager(manager)
{
    // get current field
    mPointingField = mManager->GetCurrentPlayer()->GetCurrentField();
    this->SetPosition(mPointingField->GetPosition());

    SpriteComponent* sc = new SpriteComponent(this, 60);
    if(turn) sc->SetTexture(game->GetTexture("Assets/red_cursor.png"));
    else sc->SetTexture(game->GetTexture("Assets/blue_cursor.png"));
}

Cursor::~Cursor()
{
}

void Cursor::ChangePointingField(Field *field)
{
    mPointingField = field;
    this->SetPosition(mPointingField->GetPosition());
}
