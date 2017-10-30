#include <stdlib.h>
#include <stdio.h>
#include "game_states.h"

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface* message = NULL;
SDL_Surface* message2 = NULL;
SDL_Surface* player = NULL;
SDL_Surface* ball = NULL;

SDL_Event event;
TTF_Font *font = NULL;

SDL_Rect balls[MAX_BALLS];

SDL_Color textColor = { 0, 0, 0 };

int main(int argc, char* argv[])
{
	bool quit = false;
	int selector = 0;

	if (init() == false)
	{
		return 1;
	}

	if (load_files() == false)
	{
		return 1;
	}

	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{
			message = TTF_RenderText_Solid(font, "Press space to start, any other to quit", textColor);
			apply_surface(0, 0, background, screen);
			apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
			message = TTF_RenderText_Solid(font, "초급\t\t중급\t\t고급", textColor);//난이도 선택기능
			apply_surface((640 - message->w) / 2, 480 / 2 + message->h, message, screen);
			message2 = TTF_RenderText_Solid(font, "초급\t\t", textColor);
			int tmp = message2->w;
			message2 = TTF_RenderText_Solid(font, ">", textColor);//난이도 선택
			apply_surface(640 / 2 - message->w -5 + selector * tmp, (480 + message->h) / 2, message, screen);
			SDL_Flip(screen);
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
				{
					if (selector >= 2) break;
					selector++;
					break;
				}
				case SDLK_LEFT:
				{
					if (selector <= 0) break;
					selector--;
					break;
				}
				case SDLK_SPACE:
				{
					message = NULL;
					init();
					main_game(selector);
					break;
				}
				default: quit = true;
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			
		}
		
	}
	clean_up();
	return 0;
}

