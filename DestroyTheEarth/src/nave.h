void DesenhaNave(NaveEspacial nave){
	al_draw_rotated_bitmap(Ship, nave.tamanho_x / 2, 0, nave.x, nave.y, nave.angulo, 0);	
}