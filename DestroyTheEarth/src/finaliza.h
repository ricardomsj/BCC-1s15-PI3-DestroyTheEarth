int Finaliza(){

	/* Menu */
	
    al_destroy_bitmap(Menu);
    al_destroy_bitmap(NewGame);
    al_destroy_bitmap(Tutorial);
    al_destroy_bitmap(Sair);
    al_destroy_event_queue(fila_eventos_menu);
    al_destroy_timer(timer_menu);

    /* Tutorial */

    al_destroy_timer(timer_tuto);
    al_destroy_bitmap(Tuto);
    al_destroy_bitmap(Voltar);
    al_destroy_event_queue(fila_eventos_tuto);

    /* Jogo */

    al_destroy_timer(timer);
    al_destroy_font(fonte);
    al_destroy_font(fonte1);
    al_destroy_bitmap(Hud1);
    al_destroy_bitmap(Hud2);
    al_destroy_bitmap(Hud3);
    al_destroy_bitmap(Hud4);
    al_destroy_bitmap(Hud5);
    al_destroy_bitmap(Shot);
    al_destroy_sample(tiro);
    al_destroy_bitmap(Ship);
    al_destroy_bitmap(Tela1);
    al_destroy_bitmap(Mira);
    al_destroy_bitmap(TelaEstrela);
    al_destroy_bitmap(Planeta);
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos_Tela1);

    /* Game Over */

    al_destroy_bitmap(GameOver);
    al_destroy_event_queue(fila_eventos_over);

    // ---------------------------------------- \\

    al_uninstall_system();
    camera_finaliza(cam);

    return -1;
}