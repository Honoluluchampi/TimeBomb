#pragma once
#include <cstdint>


class Component
{
public:
  // Constractor
  // the smaller component's updateOrder, the earlier updateted.
  Component(class Actor* owner, int updateOrder = 100);
  // Destractor
  virtual ~Component();
  // update function
  virtual void Update(float deltaTime);
  virtual void ProcessInput(const uint8_t* keyState){}

  int GetUpdateOrder() const{return mUpdateOrder;}
  
protected:
  // owener actor of component
  class Actor* mOwner;
  // update order of component
  int mUpdateOrder;
};
