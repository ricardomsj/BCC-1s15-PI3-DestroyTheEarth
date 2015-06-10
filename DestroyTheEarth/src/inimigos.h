void InitInimigos(NavesInimigas inimigos[], int tamanho, NaveEspacial nave){

	for(int i = 0; i < tamanho; i++){

		inimigos[i].velocidade = 1;
		inimigos[i].borda_x = nave.tamanho_x / 2;
		inimigos[i].borda_y = nave.tamanho_y / 2;
		inimigos[i].ativo = false;
	}
}

void LiberaInimigos(NavesInimigas inimigos[], int tamanho){

	int aleatorio;

	for(int i = 0; i < tamanho; i++){

		if(!inimigos[i].ativo){

			if(rand() % 100 == 0){

				aleatorio = rand() % 5;

				if(aleatorio <= 2)
					inimigos[i].x = 0;

				if(aleatorio > 2)
					inimigos[i].x = 1280;
				 
				inimigos[i].y = rand() % ALT;
				inimigos[i].ativo = true;
				break;
			}
		}
	}
}

void AtualizarInimigos(NavesInimigas inimigos[], int tamanho, NaveEspacial nave){

	double disx, disy;

	for(int i = 0; i < tamanho; i++){

		if(inimigos[i].ativo){

			if(inimigos[i].x < nave.x){
				disx = nave.x - inimigos[i].x;
			}
			if(inimigos[i].x > nave.x){
				disx = inimigos[i].x - nave.x;
			}
			if(inimigos[i].y > nave.y){
				disy = inimigos[i].y - nave.y;
			}
			if(inimigos[i].y < nave.y){
				disy = nave.y - inimigos[i].y;
			}
			if(disx > disy){
				
				if(inimigos[i].y <= nave.y)
					inimigos[i].y += inimigos[i].velocidade;
				
				if(inimigos[i].y > nave.y)
					inimigos[i].y -= inimigos[i].velocidade;
				
				if(inimigos[i].x <= nave.x){
					if((disx / (disy / inimigos[i].velocidade)) > 4)
						inimigos[i].x += 4;

					else
						inimigos[i].x += disx / (disy / inimigos[i].velocidade);
				}

				if(inimigos[i].x > nave.x){
					if((disx / (disy / inimigos[i].velocidade)) > 4)
						inimigos[i].x -= 4;

					else
						inimigos[i].x -= disx / (disy / inimigos[i].velocidade);
				}
			}

			if(disx > disy){
				if(inimigos[i].y <= nave.y){
					if((disy / (disx / inimigos[i].velocidade)) > 4)
					inimigos[i].y += 4;
					else
					inimigos[i].y += disy / (disx / inimigos[i].velocidade);
				}
				if(inimigos[i].y > nave.y){
					if((disy / (disx / inimigos[i].velocidade)) > 4)
					inimigos[i].y -= 4;
					else
					inimigos[i].y -= disy / (disx / inimigos[i].velocidade);
				}
				if(inimigos[i].x <= nave.x)
					inimigos[i].x += inimigos[i].velocidade;
				if(inimigos[i].x > nave.x)
					inimigos[i].x -= inimigos[i].velocidade;
			}
		}
	}
}

void DesenhaInimigos(NavesInimigas inimigos[], int tamanho, NaveEspacial nave){

	for(int i = 0; i < tamanho; i++){

		if(inimigos[i].ativo){

			al_draw_rotated_bitmap(Enemy, nave.tamanho_x / 2, 0, inimigos[i].x, inimigos[i].y, inimigos[i].angulo, 0);
		}
	}
}


int InimigoColidido(NavesInimigas inimigos[], int i_tamanho, NaveEspacial nave){
	int perdeuvida = 0;
	for(int i = 0; i < i_tamanho; i++){

	
		if(nave.angulo > 85 && nave.angulo <= 88.812546){

			if(inimigos[i].y > nave.y -5 && inimigos[i].y < nave.y + 100 && inimigos[i].x > nave.x - 58 && inimigos[i].x < nave.x + 58){
				inimigos[i].ativo = false;
				
				if(perdeuvida < 1)
					perdeuvida++;
			}
			//^ NAVE CIMA
		}

		if(nave.angulo > 88.812546 && nave.angulo <= 90.190862){

			if(inimigos[i].y > nave.y - 58 && inimigos[i].y < nave.y + 58 && inimigos[i].x < nave.x + 5 && inimigos[i].x > nave.x - 115){
				inimigos[i].ativo = false;
				if(perdeuvida < 1)
					perdeuvida++;		
			}
			//> NAVE DIREITA
		}

		if(nave.angulo > 91.964251 && nave.angulo <= 95){

			if(inimigos[i].y > nave.y - 58 && inimigos[i].y < nave.y + 58 && inimigos[i].x > nave.x -5 && inimigos[i].x < nave.x + 105){
				inimigos[i].ativo = false;
				if(perdeuvida < 1)
					perdeuvida++;
			}
			//< NAVE ESQUERDA
		}

		if(nave.angulo > 90.190862 && nave.angulo <= 91.964251){

			if(inimigos[i].y < nave.y + 5 && inimigos[i].y > nave.y - 100 && inimigos[i].x > nave.x -58 && inimigos[i].x < nave.x +58){
				inimigos[i].ativo = false;
				if(perdeuvida < 1)
					perdeuvida++;		
			}
			//V NAVE BAIXO
		}
	}

	return(perdeuvida);
}