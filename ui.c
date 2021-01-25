#ifndef UI_H
#include <SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#endif


void destroy(SDL_Window * window, SDL_Texture ** bmps) {
	for (int i = 0; i < 5; ++i)
	{
		SDL_DestroyTexture(bmps[i]);
	}
	SDL_DestroyWindow( window );
	SDL_Quit();
	return;
}

bool wait_for_move(short * move, SDL_Event * e){
	if((*e).type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        //printf("x:%d;y:%d\n", x , y );

		if (move[0]==NULL && x<500){
			move[1] = x/50; move[0] = y/50;
		} else if ( move[2]==NULL && x<500){
			move[3] = x/50; move[2] = y/50;
			if(!(move[0]==move[2] && move[1]==move[3])){
				return true; 
			}else{
				move[2] = NULL; move[3] = NULL;
			}
		}
	}

	return false;
}

bool ui_endturn(SDL_Event * e, SDL_Renderer * renderer){
	if((*e).type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        if(x<700 && x>500 && y>100 && y<200){
        	SDL_Rect tmp;
			tmp.x = 501; tmp.y = 100; tmp.w = 198; tmp.h = 100;
        	SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/endturn.bmp") ), NULL, &tmp );
        	return true;
        }
    }
	return false;
}

bool ui_eject_button(SDL_Event * e, SDL_Renderer * renderer){
	if((*e).type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        if(x<700 && x>500 && y>300 && y<400){
        	SDL_Rect tmp;
			tmp.x = 501; tmp.y = 300; tmp.w = 198; tmp.h = 100;
        	SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/eject.bmp") ), NULL, &tmp );
        	return true;
        }
    }
	return false;
}

bool forfeit(SDL_Event * e, SDL_Window * window){
	return false;
}

void display_board(short ** damier, SDL_Renderer * renderer, SDL_Texture ** bmps){
	SDL_Rect tmp;
	short count = 0;
	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			if(count%2 != (y+1)%2){ //don't blit anything on invalid tiles !!! (bmp doesn't exists, thus will crash)
				tmp.x = y*50; tmp.y = x*50; tmp.w = 50; tmp.h = 50;
				SDL_RenderCopy(renderer, bmps[damier[x][y]], NULL, &tmp);
				//SDL_BlitSurface(bmps[damier[y][x]],NULL,screenSurface,NULL);
			}
			count++;
		}
	}
	return;
}

void load_images(SDL_Texture ** bmps, SDL_Renderer * renderer){
	bmps[0] = SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/tile.bmp") );
	bmps[1] = SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/Bpawn.bmp") );
	bmps[2] = SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/Bdraught.bmp") );
	bmps[3] = SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/Wpawn.bmp") );
	bmps[4] = SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/Wdraught.bmp") );
	bmps[5] = SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/select.bmp") );
	return;
}