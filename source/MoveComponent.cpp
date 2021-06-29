#include "MoveComponent.h"
#include "Math.h"
#include "Actor.h"

const float WIDTH = 1024.0f;
const float HEIGHT = 768.0f;

MoveComponent::MoveComponent(Actor* owner, int updateOrder):Component(owner, updateOrder), mAngularSpeed(0.0f), mForwardSpeed(0.0f){}

void MoveComponent::Update(float deltaTime)
{
  if(!Math::NearZero(mAngularSpeed))
  {
    float rot = mOwner->GetRotation();
    rot += mAngularSpeed * deltaTime;
    mOwner->SetRotation(rot);
  }
  
  if(!Math::NearZero(mForwardSpeed))
  {
    Vector2 pos = mOwner->GetPosition();
    pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
    
    // screen wrapping (game specific)
    if(pos.x < 0.0f) {pos.x = WIDTH-2.0f;}
    else if (pos.x > WIDTH) { pos.x = 2.0f;}
    
    if(pos.y < 0.0f) { pos.y = HEIGHT - 2.0f; }
    else if (pos.y > HEIGHT) { pos.y = 2.0f; }
    mOwner->SetPosition(pos);
  }
  
  //
}
