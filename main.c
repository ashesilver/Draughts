//#define DEBUG

#include "logique.h"
#include <stdio.h>

#ifndef DEBUG
#include "ui.h"
#endif

int main(int argc, char *argv[])
{

	//étape 1 - initialisation

	short ** damier = (short**)malloc(10*sizeof(short*));
	int count = 0;
	for (int i = 0; i < 10; ++i)
	{
		damier[i] = (short*)malloc(10*sizeof(short));
		for (int y = 0; y < 10; ++y)
		{	
			if (count < 40 && count%2==i%2){
				damier[i][y] = 1;
			} else if (count > 59 && count%2==i%2) {
				damier[i][y] = 3;
			} else if (count%2==(1+i)%2){
				damier[i][y] = 5;
			} else {
				damier[i][y] = 0;
			}
			// 0 (case vide), 1 (pion noirs), 2 (dames noires), 3 (pion blancs), 4 (dames blanches), 5 (case invalide)
			count++;
		}
	}


	bool finDuJeu = false;
	int tour = 0;
	bool joueur = false; //(J1 = false, J2 = true)
	
	bool invalid_move = true;
	bool endturn = false;
	short * move = (short*)malloc(4*sizeof(short)); // {x_départ,y_départ,x_arrivée,y_arrivée}
	for (int i = 0; i < 4; ++i)
	{
		move[i] = NULL;
	}

	#ifndef DEBUG
	//SDL UI elements
	short * screen_size = (short*)malloc(2*sizeof(short));
	SDL_Window * window = NULL;
	SDL_Renderer * renderer = NULL;
	SDL_Texture * background = NULL;
	SDL_Rect rect_tmp;

	bool quit = false;
	bool eject_mode = false;
	SDL_Event e;

	if (argc > 1) { //int conversion causes trouble !! do not use
		screen_size[0] = (int)argv[1]; //x
		screen_size[1] = (int)argv[2]; //y
	} else {
		screen_size[0] = 700;screen_size[1] = 500;
	}
	
	SDL_Texture ** bmps = (SDL_Texture **)malloc(6*sizeof(SDL_Texture*));

	for (int i = 0; i < 6; ++i)
	{
		bmps[i] = NULL;
	}

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Create window
			window = SDL_CreateWindow( "Jeu de dames", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_size[0], screen_size[1], SDL_WINDOW_SHOWN );
			if( window == NULL )
			{
				printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			}
			else
			{	
				renderer = SDL_CreateRenderer( window, -1 , SDL_RENDERER_ACCELERATED );
				SDL_RenderClear(renderer);
				background = SDL_CreateTextureFromSurface( renderer, SDL_LoadBMP("./IMG/bckg.bmp") );
				SDL_RenderPresent(renderer);
				load_images(bmps , renderer);
			}
		}

	#endif

	//étape 2 - Logique

	while( !finDuJeu
	#ifdef DEBUG
		&& tour < 1000
	#endif
	#ifndef DEBUG 
		&& !quit
	#endif
		){
		
		#ifndef DEBUG
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL,NULL);

		if(!eject_mode) {
			invalid_move = false;
			if (wait_for_move(move,&e) && move[2] != NULL){
				if (move_check(damier,joueur,move)){
					for (int i = 0; i < 4; ++i)
					{
						move[i] = NULL;
					}
				} else {
					transform(damier,joueur);
				}
			}
			eject_mode = ui_eject_button(&e, renderer);
		}else{
			wait_for_move(move,&e);
			if (move[0]!=NULL){
				damier[move[0]][move[1]]=0;
				move[0]=0; move[1]=0;
			}
			eject_mode = !(ui_eject_button(&e, renderer));

		}
		display_board(damier,renderer,bmps);
		if (move[0]!=NULL){
			/*for (int i = 0; i < 4; ++i)
			{
				printf("[%d]|", move[i]);
			}printf("\n");*/
			rect_tmp.x = (move[1])*50; rect_tmp.y = (move[0]*50); rect_tmp.w = 50; rect_tmp.h = 50;
			SDL_RenderCopy(renderer, bmps[5], NULL , &rect_tmp );

		}
		endturn = ui_endturn(&e, renderer);
		//finDuJeu = forfeit();
		#endif
		#ifdef DEBUG
			affichage_damier_console(damier);
			printf("Tour n%d\n", tour+1);
		#endif


		if (endturn) {
		    tour = tour + (int)joueur;
		    printf("Joueur Suivant\n");
		    joueur = !(joueur);

		    /* TEST pour wincheck
			if(damier[tour/10][tour%10]!=0) {
			    damier[tour/10][tour%10] = 0;
			}*/

		    finDuJeu = wincheck(damier, joueur);
		    if (joueur) {oie(damier);
		    	printf("Nouveau tour !\n");}
		    transform(damier,!joueur);
		}

		#ifndef DEBUG

			SDL_RenderPresent(renderer);
			while( SDL_PollEvent( &e ) != 0 )
		        {
		            if( e.type == SDL_QUIT )
		            {
		                quit = true;
		            }
		        }
		    SDL_Delay(125);
		#endif
		
	}


	//étape 3 - Fermeture
	
	for (int i = 0; i < 10; ++i)
	{
		free(damier[i]);
	} free(damier);
	free(move);

	#ifndef DEBUG
	destroy(window,bmps);
	free(bmps);
	free(screen_size);
	#endif

	return 0;
}