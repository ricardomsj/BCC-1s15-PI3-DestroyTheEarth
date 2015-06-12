int gameOver(){

    Cursor mouse;

    while(1){

        while(!al_is_event_queue_empty(fila_eventos_over)){

            ALLEGRO_EVENT eventoOver;
            al_wait_for_event(fila_eventos_over, &eventoOver);

            if(eventoOver.type == ALLEGRO_EVENT_KEY_DOWN){
                if(eventoOver.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    return 4;
                }

                else if(eventoOver.keyboard.keycode == ALLEGRO_KEY_ENTER){
                    return 1;
                }
            }

            else if(eventoOver.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                return 4;
            }

            if(al_is_event_queue_empty(fila_eventos_over)){

                al_draw_bitmap(GameOver, 0, 0, 0);
                al_flip_display();                
            }
        }
    }

    al_unregister_event_source(fila_eventos_over, al_get_keyboard_event_source());
    al_unregister_event_source(fila_eventos_over, al_get_mouse_event_source());
    al_unregister_event_source(fila_eventos_over, al_get_display_event_source(janela));
}