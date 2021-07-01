TARGET = timebomb
SOURCES = main.cpp Game.cpp Actor.cpp Component.cpp SpriteComponent.cpp Field.cpp Math.cpp TBPlayer.cpp

COMPILER  = g++
CFLAGS    = -Wall -std=c++17 -MMD -MP
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = /usr/local/Cellar/sdl2_image/2.0.5/lib/libSDL2_image-2.0.0.dylib /usr/local/Cellar/sdl2/2.0.14_1/lib/libSDL2-2.0.0.dylib
else
  LDFLAGS =
endif
LIBS      = 
INCLUDE   = -I/usr/local/Cellar/sdl2_image/2.0.5/include -I/usr/local/Cellar/sdl2/2.0.14_1/include -I./**
SRCROOT = ./source
OBJROOT = ./obj
OBJECTS = $(addprefix $(OBJROOT)/, $(notdir $(SOURCES:.cpp=.o)))
DEPENDS   = $(OBJECTS:.o=.d)

$(TARGET): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(OBJROOT)/%.o: $(SRCROOT)/%.cpp
	-mkdir -p $(OBJROOT)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: clean $(TARGET)

clean:
	-rm -r $(OBJROOT)
	-rm -f $(notdir $(TARGET)) $(DEPENDS) 

-include $(DEPENDS)