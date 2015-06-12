#Pasta com as .h
IDIR=-I include

#Pasta com as .c
SDIR=src

#Compilador
CC=gcc

#pkg config do Allegro, incluir mais se necessário
PKG_CONFIG=`pkg-config --cflags --libs allegro-5.0 allegro_acodec-5.0 allegro_audio-5.0 allegro_color-5.0 allegro_dialog-5.0 allegro_font-5.0 allegro_image-5.0 allegro_main-5.0 allegro_memfile-5.0 allegro_physfs-5.0 allegro_primitives-5.0 allegro_ttf-5.0 opencv`

# todas as minhas .c
_SRC=main.c

SRC=$(patsubst %,$(SDIR)/%,$(_SRC))

#nome do meu exe
EXECUTABLE=pi

all:
	gcc $(SRC) -o $(EXECUTABLE) $(PKG_CONFIG) $(IDIR) -lm -lopencv_core -lopencv_highgui -std=c99;
