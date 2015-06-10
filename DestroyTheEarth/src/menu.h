int MenuPrincipal(){
    bool desenha = false, NG = false, Tuto = false, Exit = false;

    Cursor mouse;
    
    al_hide_mouse_cursor(janela);
    al_start_timer(timer_menu);

    while(1){

        al_play_sample(intro, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

        while(!al_is_event_queue_empty(fila_eventos_menu)){

            ALLEGRO_EVENT eventoMenu;
            al_wait_for_event(fila_eventos_menu, &eventoMenu);

            if(eventoMenu.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

                if(mouse.x >= 522 && mouse.x <= 758 && mouse.y >= 502 && mouse.y <= 540){
                    if(eventoMenu.mouse.button & 1){
                        al_destroy_sample(intro);
                        return 1;
                    }
                }

                else if(mouse.x >= 543 && mouse.x <= 739 && mouse.y >= 565 && mouse.y <= 603){
                    if(eventoMenu.mouse.button & 1){
                        return 2;
                    }
                }

                else if(mouse.x >= 594 && mouse.x <= 687 && mouse.y >= 624 && mouse.y <= 662){
                    if(eventoMenu.mouse.button & 1){
                        al_destroy_sample(intro);
                        return -1;
                    }
                }
            }

            else if(eventoMenu.type == ALLEGRO_EVENT_KEY_DOWN){
                if(eventoMenu.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                    al_destroy_sample(intro);
                    return -1;
                }
            }

            else if(eventoMenu.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                al_destroy_sample(intro);
            	return -1;
            }

            else if(eventoMenu.type == ALLEGRO_EVENT_TIMER){

                
                /* New Game */

                if(mouse.x >= 522 && mouse.x <= 758 && mouse.y >= 502 && mouse.y <= 540)
                    NG = true;


                /* Tutorial */

                else if(mouse.x >= 543 && mouse.x <= 739 && mouse.y >= 565 && mouse.y <= 603)
                    Tuto = true;


                /* Sair */

                else if(mouse.x >= 594 && mouse.x <= 687 && mouse.y >= 624 && mouse.y <= 662)
                    Exit = true;


                desenha = true;
            }

            if(desenha && al_is_event_queue_empty(fila_eventos_menu)){

                camera_atualiza(cam);
                mouse = converte_HSV(cam, mouse);

                if(NG){
                    al_draw_bitmap(NewGame, 0, 0, 0);
                    NG = false;
                }

                if(Tuto){
                    al_draw_bitmap(Tutorial, 0, 0, 0);
                    Tuto = false;
                }

                if(Exit){
                    al_draw_bitmap(Sair, 0, 0, 0);
                    Exit = false;
                }

                al_draw_bitmap(Shot, mouse.x, mouse.y, 0);

                al_flip_display();
                al_draw_bitmap(Menu, 0, 0, 0);

                desenha = false;
            }
        }
    }

    al_stop_timer(timer_menu);
    al_unregister_event_source(fila_eventos_menu, al_get_timer_event_source(timer_menu));
    al_destroy_timer(timer_menu);
    al_unregister_event_source(fila_eventos_menu, al_get_keyboard_event_source());
    al_unregister_event_source(fila_eventos_menu, al_get_mouse_event_source());
    al_destroy_bitmap(Menu);
    al_destroy_bitmap(NewGame);
    al_destroy_bitmap(Tutorial);
    al_destroy_bitmap(Sair);
    al_unregister_event_source(fila_eventos_menu, al_get_display_event_source(janela));
    al_destroy_event_queue(fila_eventos_menu);
}