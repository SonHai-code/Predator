

#include "text.h"

static SDL_Texture* fontTexture;
static char drawTextBuffer[MAX_LINE_LENGTH];

void initFonts(void)
{
	fontTexture = loadTexture("D:\\game\\gfx\\font.png");
}

void drawText(int x, int y, int r, int g, int b, int align, const char* format, ...)
{
	int i, len, c;
	SDL_Rect rect;
	va_list args;

	memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

	va_start(args, format);
	vsprintf_s(drawTextBuffer, format, args);
	va_end(args);

	len = strlen(drawTextBuffer);

	switch (align)
	{
	case TEXT_RIGHT:
		x -= (len * GLYPH_WIDTH);
		break;

	case TEXT_CENTER:
		x -= (len * GLYPH_WIDTH) / 2;
		break;
	}

	rect.w = GLYPH_WIDTH;
	rect.h = GLYPH_HEIGHT;
	rect.y = 0;

	SDL_SetTextureColorMod(fontTexture, r, g, b);

	for (i = 0; i < len; i++)
	{
		c = drawTextBuffer[i];

		if (c >= ' ' && c <= 'Z')
		{
			rect.x = (c - ' ') * GLYPH_WIDTH;

			blitRect(fontTexture, &rect, x, y);

			x += GLYPH_WIDTH;
		}
	}
}
