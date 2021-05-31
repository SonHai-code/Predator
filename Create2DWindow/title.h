
#include "common.h"

extern void blitRect(SDL_Texture* texture, SDL_Rect* src, float x, float y);
extern void doBackground(void);
extern void doStarfield(void);
extern void drawBackground(void);
extern void drawStarfield(void);

extern void drawText(int x, int y, int r, int g, int b, int align, const char* format, ...);
extern void initHighscores(void);
extern void initStage(void);

extern SDL_Texture* loadTexture(string filename);

extern App app;
