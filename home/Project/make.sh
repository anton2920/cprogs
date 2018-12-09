cc -std=c90 -Wall -c libs/menu.c && cc -std=c90 -Wall -c libs/menu2.c && cc -std=c90 -Wall -c main.c && cc -std=c90 -Wall main.o menu.o menu2.o -o main -ldialog -lcursesw
