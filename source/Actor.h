#pragma once
#include <vector>
#include "Math.h"

class Actor
{
public:
  // actor's state
  enum State
  {
    EActive,
    EPaused,
    EDead
  };
  // Constractor and Destractor
  Actor(class Game *game); // choose Game object which the actor belongs to.
  virtual ~Actor();
  
  // update function called by game object
  void Update(float deltaTime);
  // update componets
  void UpdateComponents(float deltaTime);
  // Actor original update funcion (can be overrided)
  virtual void UpdateActor(float deltaTime);
  
  // called from game, cannot override
  void ProcessInput(const uint8_t* keyState);
  // Actor origin input func, can override
  virtual void ActorInput(const uint8_t* keyState);
  
  // Getters/ Setters
  const Vector2& GetPosition() const { return mPosition; }
  void SetPosition(const Vector2& pos) { mPosition = pos; }
  float GetScale() const { return mScale; }
  void SetScale(float scale) { mScale = scale; }
  float GetRotation() const { return mRotation; }
  void SetRotation(float rotation) { mRotation = rotation; }
  
  Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation));}
  
  // get actor state
  State GetState() const {return mState;}
  void SetState(State state) { mState = state; }
  
  class Game* GetGame() { return mGame;}
  
  // manage componets
  void AddComponent(class Component *component);
  void RemoveComponent(class Component *component);
  
private:
  State mState;
  // Affine transformation
  Vector2 mPosition;
  float mScale;
  float mRotation;
  
  // Actors Component
  std::vector<class Component*> mComponents;
  class Game* mGame;
};
