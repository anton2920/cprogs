/*
 * aclock - ascii clock for UNIX Console
 *
 * Copyright (c) 2002 Antoni Sawicki <as@tenoware.com>
 * Version 2.3 (unix-curses); Mountain View, July 2013
 *
 * Compilation: cc aclock-unix-knr.c -o aclock -lcurses -lm
 *
 * this is K&R version modified for old unices (but still with curses)
 *
 */

#include <unistd.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>

int ch ; 


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define FontWH_Ratio 2

nrclock_drw_cir(hand_max, sycen, sxcen)
int hand_max; int sycen; int sxcen;
{
	int x,y,r;
	char c;

	for(r=0;r<60;r++){
		x=cos(r*M_PI/180*6)*hand_max*FontWH_Ratio+sxcen;
		y=sin(r*M_PI/180*6)*hand_max+sycen;
		switch (r) {
			case 0:
			case 5:
			case 10:
			case 15:
			case 20:
			case 25:
			case 30:
			case 35:
			case 40:
			case 45:
			case 50:
			case 55:
				c='o';
				break;
			default:
				c='.';
				break;
		}
		mvaddch(y,x,c);
	}
}

nrclock_draw_hand(minute, hlenght, c, sxcen, sycen)
int minute; int hlenght; char c; int sxcen; int sycen;
{
	int x,y,n;
	float r=(minute-15)*(M_PI/180)*6;

	for(n=1; n<hlenght; n++){
		x=cos(r)*n*FontWH_Ratio+sxcen;
		y=sin(r)*n+sycen;
		mvaddch(y,x,c);
	}
}




void nrclock(){
	char digital_time[15];
	int sXmax, sYmax, smax, hand_max, sXcen, sYcen;
	long t;
	struct tm *ltime;

	// initscr();
	// for(;;){
        int nrclock_gameover =  0;
   curs_set( 0 );
   attroff( A_REVERSE);
   attron( A_BOLD);
   color_set( 2,NULL);
   nodelay( stdscr, TRUE);

        nrclock_gameover =  0;
        while( nrclock_gameover == 0 ){

		time(&t);
		ltime=localtime(&t);
		sXmax = COLS;
		sYmax = LINES;

		if(sXmax/2<=sYmax)
			smax=sXmax/2;
		else
			smax=sYmax;

		hand_max = (smax/2)-1;

		sXcen = sXmax/2;
		sYcen = sYmax/2;

		erase();
		nrclock_drw_cir(hand_max, sYcen, sXcen);

		nrclock_draw_hand((ltime->tm_hour*5)+(ltime->tm_min/10), 2*hand_max/3, 'h', sXcen, sYcen);
		nrclock_draw_hand(ltime->tm_min, hand_max-2, 'm', sXcen, sYcen);
		nrclock_draw_hand(ltime->tm_sec, hand_max-1, '.', sXcen, sYcen);

		mvaddstr(sYcen-(3*hand_max/5), sXcen-5, ".:NRCLOCK:.");
		mvprintw(sYcen-(3*hand_max/5)   +1, sXcen-5    +2, ".:J-%d:.", 22 - ltime->tm_mday  );
		mvprintw(sYcen+(3*hand_max/5), sXcen-5, "[%02d:%02d:%02d]", ltime->tm_hour, ltime->tm_min, ltime->tm_sec);


  refresh();

     nodelay( stdscr, TRUE);
                ch = getch(); 
		switch( ch ){
		   case KEY_F(10):
		   case 'i':
		   case 'q':
		    nrclock_gameover = 1;
		    break;
		}

               usleep( 1e6 /2 /5 ); 
		// sleep(1);
	}
	// endwin();
   curs_set( 1 );
   attroff( A_REVERSE);
   color_set(0,NULL);
   nodelay( stdscr, FALSE);
}










void drawit(){
        int rows, cols;  
        getmaxyx( stdscr, rows, cols);
        mvprintw(5 , 5, "Hello World !!!");	
        mvprintw(rows-1 , 0, "<Press Key to Continue>");
}


int main()
{	
	initscr();	
        curs_set( 0 );

        drawit();
        nrclock();

	refresh();			
        curs_set( 1 );
	endwin();		
	return 0;
}