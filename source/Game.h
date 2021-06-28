struct Vector2
{
  float x;
  float z;
};

class Game
{
public:
  
  // Constracter
  Game();
  
  // Initializer
  bool Initialize();
  
  // Game Looper
  void RunLoop();
  
  // ShutDown Game
  void Shutdown();
  
private:
  // Helper functions for RunLoop()
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();
  
  // continue instractor
  bool mlsRunning;
  
};
