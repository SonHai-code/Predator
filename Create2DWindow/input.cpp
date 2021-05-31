
#include "input.h"

void doKeyUp(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		int temp = event->keysym.scancode;
		app.keyboard[ temp ] = 0;

	}
}

void doKeyDown(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		int temp = event->keysym.scancode;
		app.keyboard[ temp ] = 1;
	}
}

void doInput(void)
{
	SDL_Event event;

	memset(app.inputText, '\0', MAX_LINE_LENGTH);

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			doKeyDown( &event.key );
			break;

		case SDL_KEYUP:
			doKeyUp(&event.key);
			break;

		case SDL_TEXTINPUT:
			strncpy_s(app.inputText, event.text.text, MAX_LINE_LENGTH);
			break;

		default:
			break;
		}
	}
}

