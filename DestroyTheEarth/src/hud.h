void DesenhaHud(NaveEspacial nave){

	if(nave.vidas <= 1000 && nave.vidas > 900){
		al_draw_bitmap(Hud5, 10, 615, 0);
	}

	if(nave.vidas <= 900 && nave.vidas > 600){
		al_draw_bitmap(Hud4, 10, 615, 0);
	}

	if(nave.vidas <= 600 && nave.vidas > 400){
		al_draw_bitmap(Hud3, 10, 615, 0);
	}

	if(nave.vidas == 400 && nave.vidas > 150){
		al_draw_bitmap(Hud2, 10, 615, 0);
	}

	if(nave.vidas <= 150){
		al_draw_bitmap(Hud1, 10, 615, 0);
	}

	if(nave.vidas <= 0){
		exit(EXIT_SUCCESS);
	}

}