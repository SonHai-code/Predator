#include "draw.h"

void prepareScene(void)
{
	// Clear screen 
	SDL_SetRenderDrawColor(app.renderer, 32, 32, 32, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	// Update screen 
	SDL_RenderPresent(app.renderer);
}

static SDL_Texture* getTexture(string name)
{
	Texture* t;

	for (t = app.textureHead.next; t != NULL; t = t->next)
	{
		if ( t->name.compare (name) == 0 )
		{
			return t->texture;
		}
	}
	return NULL;
}

static void addTextureToCache(string name, SDL_Texture* sdlTexture)
{
	Texture* texture = new Texture();
	memset(texture, 0, sizeof(Texture));
	app.textureTail = texture;
	app.textureTail->next = texture;
	
	//strncpy_s(texture->name, name, MAX_NAME_LENGTH);
	texture->name = name;

	texture->texture = sdlTexture;
}

SDL_Texture *loadTexture(string filename)
{
	SDL_Texture* texture;

	texture = getTexture(filename);

	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename.c_str());
		texture = IMG_LoadTexture(app.renderer, filename.c_str());
		addTextureToCache(filename, texture);
	}
	return texture;
}


void blit(SDL_Texture* texture, float x, float y)
{
	SDL_Rect dest;

	dest.x = (int)  x;
	dest.y = (int)  y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture* texture, SDL_Rect* src, float x, float y)
{
	SDL_Rect dest;

	dest.x = (int) x;
	dest.y = (int) y;
	dest.w = src->w;
	dest.h = src->h;

	SDL_RenderCopy(app.renderer, texture, src, &dest);
}
