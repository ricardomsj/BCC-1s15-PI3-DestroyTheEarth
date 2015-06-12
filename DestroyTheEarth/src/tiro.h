void InitBalas(Projeteis balas[], int tamanho){

	for(int i = 0; i < tamanho; i++){

		balas[i].velocidade = 20;
		balas[i].ativo = false;
	}
}

void AtiraBalas(Projeteis balas[], int tamanho, NaveEspacial nave){

	for(int i = 0; i < tamanho; i++){

		if(!balas[i].ativo){
			balas[i].x = nave.x;
			balas[i].y = nave.y - 3;

			balas[i].velocidade_x = cos(nave.angulo - (360/3.14)) * balas[i].velocidade;
			balas[i].velocidade_y = sin(nave.angulo - (360/3.14)) * balas[i].velocidade;

			al_play_sample(tiro, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			balas[i].ativo = true;
			break;

		}
	}
}

void AtiraBalasInimigas(Projeteis balas[], int tamanho, NavesInimigas inimigos[]){

	for(int i = 0; i < tamanho; i++){

		if(!balas[i].ativo){
			balas[i].x = inimigos[i].x;
			balas[i].y = inimigos[i].y - 3;

			balas[i].velocidade_x = cos(inimigos[i].angulo - (360/3.14)) * balas[i].velocidade;
			balas[i].velocidade_y = sin(inimigos[i].angulo - (360/3.14)) * balas[i].velocidade;

			al_play_sample(tiro, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			balas[i].ativo = true;
			break;

		}
	}
}

void AtualizarBalas(Projeteis balas[], int tamanho){

	for(int i = 0; i < tamanho; i++){

		if(balas[i].ativo){
			balas[i].x += balas[i].velocidade_x;
			balas[i].y += balas[i].velocidade_y;

			if (balas[i].x < 0 || balas[i].x > LARG || balas[i].y < 0 || balas[i].y > 720){
				balas[i].ativo = false;
			}

		}
	}
}

void DesenhaBalas(Projeteis balas[], int tamanho, NaveEspacial nave){

	for(int i = 0; i < tamanho; i++){

		if(balas[i].ativo){
			al_draw_rotated_bitmap(Shot, 6, 0, balas[i].x, balas[i].y, nave.angulo, 0);
		}
	}
}

void DesenhaBalasInimigas(Projeteis balas[], int tamanho, NavesInimigas inimigos[]){

	for(int i = 0; i < tamanho; i++){

		if(balas[i].ativo){
			al_draw_rotated_bitmap(Shot, 6, 0, balas[i].x, balas[i].y, inimigos[i].angulo, 0);
		}
	}
}

int BalaColidida(Projeteis balas[], int b_tamanho, NavesInimigas inimigos[], int i_tamanho, NaveEspacial nave){
	int pontos = 0, aumenta = 5, vel = i_tamanho;

	if (nave.pontos > 50 && nave.pontos <= 100)
		aumenta = 10;

	if (nave.pontos > 100 && nave.pontos <= 200)
		aumenta = 25;

	if (nave.pontos > 200 && nave.pontos <= 300)
		aumenta = 35;

	if (nave.pontos > 300 && nave.pontos <= 400)
		aumenta = 60;

	if (nave.pontos > 400)
		aumenta = 100;

	for(int i = 0; i < b_tamanho; i++){

		if(balas[i].ativo){

			for(int j = 0; j < i_tamanho; j++){

				if(inimigos[j].ativo){

					if(balas[i].x > ((inimigos[j].x - inimigos[j].borda_x) + 55) &&
						balas[i].x < ((inimigos[j].x + inimigos[j].borda_x) + 55) &&
						balas[i].y > (inimigos[j].y - inimigos[j].borda_y) &&
						balas[i].y < (inimigos[j].y + inimigos[j].borda_y)){

						balas[i].ativo = false;
						inimigos[j].ativo = false;
						pontos += aumenta;
					}
				}
			}
		}
	}

	return pontos;
}
