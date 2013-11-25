DIRSRC		=	./

SRCS		=	$(DIRSRC)contrast.correction.c

INCLUDE		=	-I../headers/

LIB_PATH	=	

LIBS		=	

NAME		=	test

FLAGS		=	-g -O2 -Wall

OBJS		=	$(SRCS:%.c=%.o)

%.o: %.c
	gcc -c $(FLAGS) -o $@ $< $(INCLUDE) #-fPIC

all: compile

compile: $(OBJS)
	@echo "\n================== Compile $(NAME) ===================="
	gcc $(OBJS) -o $(NAME) `GraphicsMagick-config --cppflags --libs --ldflags` $(LIB_PATH) $(LIBS) $(FLAGS)

clean:
	@echo "\n==================== Cleaning $(NAME) ====================="
	rm -rf *~ \#*\# $(NAME)
	rm -rf $(DIRSRC)*.o
	rm -rf *.so
	rm -rf core

re:	clean all

.PHONY: all compile clean re
