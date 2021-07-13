#include "Component.h"
#include "Actor.h"
#include <iostream>

Component::Component(Actor* owner, int updateOrder)
  :mOwner(owner), mUpdateOrder(updateOrder)
{
  mOwner -> AddComponent(this);
}

Component::~Component()
{
  mOwner -> RemoveComponent(this);
}

void Component::Update(float deltaTime)
{}
