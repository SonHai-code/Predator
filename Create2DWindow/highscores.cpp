

#include "highscores.h"

static void logic(void);
static void draw(void);
static int highscoreComparator(const void* a, const void* b);
static void drawHighscores(void);
static void doNameInput(void);
static void drawNameInput(void);

static Highscore* newHighscore;
static int cursorBlink;
static int timeout;

void initHighscoreTable(void)
{
	int i;

	memset(&highscores, 0, sizeof(Highscores));

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		highscores.highscore[i].score = NUM_HIGHSCORES - i;
		strncpy_s(highscores.highscore[i].name, "NONAME", MAX_SCORE_NAME_LENGTH);
	}

	newHighscore = NULL;

	cursorBlink = 0;
}

void initHighscores(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	timeout = FPS * 5;
}

static void logic(void)
{
	doBackground();

	doStarfield();

	if (newHighscore != NULL)
	{
		doNameInput();
	}
	else
	{
		if (--timeout <= 0)
		{
			initTitle();
		}

		if (app.keyboard[SDL_SCANCODE_LCTRL])
		{
			initStage();
		}
	}

	if (++cursorBlink >= FPS)
	{
		cursorBlink = 0;
	}
}

static void doNameInput(void)
{
	int i, n;
	char c;

	n = strlen(newHighscore->name);

	for (i = 0; i < strlen(app.inputText); i++)
	{
		c = toupper(app.inputText[i]);

		if (n < MAX_SCORE_NAME_LENGTH - 1 && c >= ' ' && c <= 'Z')
		{
			newHighscore->name[n++] = c;
		}
	}

	if (n > 0 && app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		newHighscore->name[--n] = '\0';

		app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
	}

	if (app.keyboard[SDL_SCANCODE_RETURN])
	{
		if (strlen(newHighscore->name) == 0)
		{
		    strncpy_s(newHighscore->name, "ANONYMOUS", MAX_SCORE_NAME_LENGTH);
		}

		newHighscore = NULL;
	}
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	if (newHighscore != NULL)
	{
		drawNameInput();
	}
	else
	{
		drawHighscores();

		if (timeout % 40 < 20)
		{
			drawText(SCREEN_WIDTH / 2, 600, 255, 255, 255, TEXT_CENTER, "PRESS FIRE TO PLAY!");
		}
	}
}

static void drawNameInput(void)
{
	SDL_Rect r;

	drawText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, "CONGRATULATIONS, YOU'VE GAINED A HIGHSCORE!");

	drawText(SCREEN_WIDTH / 2, 120, 255, 255, 255, TEXT_CENTER, "ENTER YOUR NAME BELOW:");

	drawText(SCREEN_WIDTH / 2, 250, 128, 255, 128, TEXT_CENTER, newHighscore->name);

	if (cursorBlink < FPS / 2)
	{
		r.x = ((SCREEN_WIDTH / 2) + (strlen(newHighscore->name) * GLYPH_WIDTH) / 2) + 5;
		r.y = 250;
		r.w = GLYPH_WIDTH;
		r.h = GLYPH_HEIGHT;

		SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(app.renderer, &r);
	}

	drawText(SCREEN_WIDTH / 2, 625, 255, 255, 255, TEXT_CENTER, "PRESS CTRL LEFT TO PLAY AGAIN");
}

static void drawHighscores(void)
{
	int i, y, r, g, b;

	y = 150;

	drawText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, "HIGHSCORES");

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		r = 255;
		g = 255;
		b = 255;

		if (highscores.highscore[i].recent)
		{
			b = 0;
		}

		drawText(SCREEN_WIDTH / 2, y, r, g, b, TEXT_CENTER, "#%d. %-15s ...... %03d", (i + 1), highscores.highscore[i].name, highscores.highscore[i].score);

		y += 50;
	}
}

void addHighscore(int score)
{
	Highscore newHighscores[NUM_HIGHSCORES + 1];
	int i;

	memset(newHighscores, 0, sizeof(Highscore) * (NUM_HIGHSCORES + 1));

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		newHighscores[i] = highscores.highscore[i];
		newHighscores[i].recent = 0;
	}

	newHighscores[NUM_HIGHSCORES].score = score;
	newHighscores[NUM_HIGHSCORES].recent = 1;

	qsort(newHighscores, NUM_HIGHSCORES + 1, sizeof(Highscore), highscoreComparator);

	newHighscore = NULL;

	for (i = 0; i < NUM_HIGHSCORES; i++)
	{
		highscores.highscore[i] = newHighscores[i];

		if (highscores.highscore[i].recent)
		{
			newHighscore = &highscores.highscore[i];
		}
	}
}

static int highscoreComparator(const void* a, const void* b)
{
	Highscore* h1 = ((Highscore*)a);
	Highscore* h2 = ((Highscore*)b);

	return h2->score - h1->score;
}
