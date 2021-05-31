
#include "common.h"

extern void blit(SDL_Texture* texture, float x, float y);
extern void blitRect(SDL_Texture* texture, SDL_Rect* src, float x, float y);

extern int collision(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);
extern void calcSlope(float x1, float y1, float x2, float y2, float* dx, float* dy);

extern void doBackground(void);
extern void doStarfield(void);
extern void drawBackground(void);
extern void drawStarfield(void);

extern void drawText(int x, int y, int r, int g, int b, int align, const char* format, ...);
extern void initHighscores(void);

extern SDL_Texture* loadTexture(string path);

extern void addHighscore(int score);

extern void playSound(int id, int channel);

extern App app;
extern Stage stage;
extern Highscores highscores;