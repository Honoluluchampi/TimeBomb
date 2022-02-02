#include <iostream>
#include <memory>
#include "TimeBombApp.h"

int main(int argc, const char * argv[])
{
  auto app = std::make_unique<TimeBombApp>();
  bool success = app->Initialize();
  if(success)
  {
    app->RunLoop();
  }
  app->Shutdown();
}