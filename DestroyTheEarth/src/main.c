#include <opencv2/highgui/highgui_c.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "inicializar.h"
#include "camera.h"
#include "menu.h"
#include "tutorial.h"
#include "nave.h"
#include "tiro.h"
#include "hud.h"
#include "inimigos.h"
#include "game.h"
#include "over.h"
#include "finaliza.h"

int main(){
	int i = 0;

	if(!inicializar())
		return -1;

	while(i >= 0){
		if(i == 0)
	        i = menuPrincipal();

	    if(i == 1)
	    	i = Jogo();

	    if(i == 2)
	    	i = telaTutorial();

	    if(i == 3)
	    	i = gameOver();

	    if(i == 4)
	    	i = Finaliza();
	}

    return 0;
}
