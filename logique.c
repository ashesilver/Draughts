#ifndef LOGIQUE_H

#include <time.h>
#include <stdbool.h>
#endif
#include <stdio.h>



bool move_check(short ** damier, bool player, short * move){
	// 0 (case vide), 1 (pion noirs), 2 (dames noires), 3 (pion blancs), 4 (dames blanches), 5 (case invalide)
	short pawn; short draught;
	printf("Checking for validity : |");
	for (int i = 0; i < 4; ++i)
	{
		printf("%d|", move[i]);
	}
	if (damier[move[0]][move[1]] == 0 || damier[move[0]][move[1]] == 5){
		printf("  Square is empty\n");
		return true;
	}
	if (!player) {pawn = 1;draught = 2;} else {pawn = 3; draught = 4;}

	//wrong pawn
	if (damier[move[0]][move[1]] != pawn && damier[move[0]][move[1]] != draught) {
		printf("  Wrong pawn\n");
		return true;
	}
	//overlaping
	if (damier[move[2]][move[3]] != 0 ){
		printf("  Target is occupied\n");
		return true;
	}
	printf("  Move is allowed.\n");
	damier[move[2]][move[3]] = damier[move[0]][move[1]];damier[move[0]][move[1]] = 0;
	move[0]=move[2];move[1]=move[3];move[2]=NULL;move[3]=NULL;
	return false;
}

void transform(short ** damier, bool player){
	if(!player){
		for (int i = 0; i < 5; ++i)
		{
			if(damier[9][(i*2)+1] == 1){
				damier[9][(i*2)+1] = 2;
			}
		}
	} else {
		for (int i = 0; i < 5; ++i)
		{
			if(damier[0][(i*2)] == 3){
				damier[0][(i*2)] = 4;
			}
		}
	}
	return;
}

void oie(short ** damier){
	srand(time(NULL));
	int depart; int arrivee;
	do {
		depart = rand()%100;
		arrivee = rand()%100;
	}while( (damier[depart/10][depart%10]==0 || damier[depart/10][depart%10]==5 ) || damier[arrivee/10][arrivee%10]!=0);

	damier[arrivee/10][arrivee%10] = damier[depart/10][depart%10];
	damier[depart/10][depart%10] = 0;

	return;
}

bool wincheck(short ** damier, bool player) {
	bool res = false;
	int count = 0;

	while(!(res) && count < 100) {
	    res = ( 
	    		( 
	    			player && ( damier[count/10][count%10]==1 || damier[count/10][count%10]==2 ) 
	    		) || ( 
	    			!( player ) && ( damier[count/10][count%10]==3 || damier[count/10][count%10]==4 ) 
	    		) 
	    	);
	    count++;
	}

	#ifdef DEBUG
	if (!res) {
		win((int)player + 1);
	}
	#endif

	return !(res);
}

#ifdef DEBUG
#include <stdio.h>
void affichage_damier_console(short ** damier) {
	for (int i = 0; i < 10; ++i)
	{
		for (int y = 0; y < 10; ++y)
		{
			printf("|%d", damier[i][y]);
		}
		printf("|\n");
	}
	return;
}

void win(int winner){
	printf("\nFini ! Gagnant: J%d\n", winner);
	return;
}
#endif