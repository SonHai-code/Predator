#include "common.h"

#include "SDL_image.h"
#include "SDL_mixer.h"

extern void initBackground(void);
extern void initFonts(void);
extern void initHighscoreTable(void);
extern void initSounds(void);
extern void initStarfield(void);

extern void loadMusic(string filename);
extern void playMusic(int loop);

extern App app;
extern Stage stage;
