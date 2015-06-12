int telaTutorial(){
    bool desenha = false, voltar = false;

    Cursor mouse;

    al_hide_mouse_cursor(janela);
    al_start_timer(timer_tuto);

    while(1){

        while(!al_is_event_queue_empty(fila_eventos_tuto)){

            ALLEGRO_EVENT eventoTuto;
            al_wait_for_event(fila_eventos_tuto, &eventoTuto);

            if(eventoTuto.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

                if(mouse.x >= 1130 && mouse.x <= 1266 && mouse.y >= 670 && mouse.y <= 720){
                    if(eventoTuto.mouse.button & 1){
                        return 0;
                    }
                }
            }

            else if(eventoTuto.type == ALLEGRO_EVENT_KEY_DOWN){
                if(eventoTuto.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    al_destroy_sample(intro);
                    return 4;
                }
            }

            else if(eventoTuto.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                al_destroy_sample(intro);
                return 4;
            }

            else if(eventoTuto.type == ALLEGRO_EVENT_TIMER){


                /* Voltar */

                if(mouse.x >= 1130 && mouse.x <= 1266 && mouse.y >= 670 && mouse.y <= 720)
                    voltar = true;

                desenha = true;
            }

            if(desenha && al_is_event_queue_empty(fila_eventos_tuto)){

                camera_atualiza(cam);
                mouse = converte_HSV(cam, mouse);

                if(voltar){
                    al_draw_bitmap(Voltar, 0, 0, 0);
                    voltar = false;
                }

                al_draw_bitmap(Mira, mouse.x, mouse.y, 0);

                al_flip_display();
                al_draw_bitmap(Tuto, 0, 0, 0);

                desenha = false;
            }
        }
    }

    al_stop_timer(timer_tuto);
    al_unregister_event_source(fila_eventos_tuto, al_get_timer_event_source(timer_tuto));
    al_unregister_event_source(fila_eventos_tuto, al_get_keyboard_event_source());
    al_unregister_event_source(fila_eventos_tuto, al_get_mouse_event_source());
    al_unregister_event_source(fila_eventos_tuto, al_get_display_event_source(janela));
}
