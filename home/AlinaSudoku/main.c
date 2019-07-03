#include "Header.h"
#pragma comment (lib, "SDL2_mixer.lib")
#undef main 

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Sudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("2.ttf", 100);

	Mix_Init(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024); // звук
	Mix_Music * fon_m = NULL;
	loadmusic(fon_m, 0);

	int a[N]; // массив цифр
	int lv = 0; // уровень
	int emd; // сложность
	int index[N]; // массив цифр на поле

	SDL_Rect button[3], cell[N] = {}; // структура для кнопок, структура для клеток поля
	SDL_Texture *fon = NULL, *fon_rec = NULL, *text_logo = NULL, *exit_texture = NULL; // текстура фона, текстура рекордов, текстура лого, текстура кнопки выход
	SDL_Texture  *texture_button = NULL, *button_text[3] = {}, *winner_text[2] = {}, *cell_text[257] = {}, *game_sudocu = NULL, *cell_fon = NULL;
	// текстура фона кнопки, текстура текста на кнопке, текстура если победа, текстура для цифр, текстура ?, текстура фона клетки
	SDL_Event event;
	bool quit = false;
	int sign = 0, theme = 0, play = 0, exit = 1, win = -1, plan;
	int i_menu = -1; // номер экрана

	init_rect(button, 1, 0, 0); // инициализация первого экрана
	
	SDL_Surface *fonImage = IMG_Load("theme.bmp");
	SDL_SetColorKey(fonImage, SDL_TRUE, SDL_MapRGB(fonImage->format, 0, 0, 0));
	texture_button = SDL_CreateTextureFromSurface(renderer, fonImage);
	char t[] = "SUDOCU";
	text_logo = get_text_texture_text(renderer, font, t, theme);
	fonImage = IMG_Load("fon_0.bmp");
	fon = SDL_CreateTextureFromSurface(renderer, fonImage);
	fonImage = IMG_Load("fon_record.bmp");
	fon_rec = SDL_CreateTextureFromSurface(renderer, fonImage);
	fonImage = IMG_Load("exit.bmp");
	SDL_SetColorKey(fonImage, SDL_TRUE, SDL_MapRGB(fonImage->format, 255, 255, 255));
	exit_texture = SDL_CreateTextureFromSurface(renderer, fonImage);
	fonImage = IMG_Load("cell.bmp");
	cell_fon = SDL_CreateTextureFromSurface(renderer, fonImage);
	SDL_FreeSurface(fonImage);

	init_text(renderer, button_text, 1, font, theme); // получаем текстуры текста для первого экрана
	draw_game(0,lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture); // отрисовка первого экрана
	
	int i_help = -5;
	char winner_name[5][12] = {};
	int count[N] = {};
	int start = 0; // гл. меню
	int l = 0; //  индексы
	int red[N] = {};
	int z = 0; // для ввода двузначных цифр
	int time = 0, time_min = 0;
	int new_record = 0;
	int start_time, end_time; // время
	int winner_time[5] = {100,100,100,100,100};
	char t_name[12] = {};
	int stop = -1; // рекорды
	int winner = 0;
	SDL_Rect ex_rect = { 700, 500, 75, 75 };
	SDL_Texture* name_text[13] = {};
	SDL_Texture* record_texture[10] = {};
	SDL_Rect name_win[13];
	SDL_Rect record_rect[10] = {};
	SDL_Rect winner_new_rect[2];
	int key = -1;

	winner_new_rect[0] = { 275, 250, 250, 75 };
	winner_new_rect[1] = { 275, 350, 250, 75 };
	for (int i = 0; i < 12; i++)
	{
		name_win[i] = { 100 + i * 50, 300, 50, 50 };
	}
	int ex = 1;
	name_win[12] = { 375, 400, 50, 50 };
	int in_time;
	while (!quit)
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT)
			quit = true;
		if (exit == 0) // выход при нажатии кнопки exit
			quit = true;

		if ((ex == 0) && (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) && (is_user_hit(ex_rect, event.button.x, event.button.y))) // переход от таблицы рекордов в главное меню
		{
			ex = 1;
			sign = 1;
			init_text(renderer, button_text, 2, font, theme);
			draw_game(0,lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
		}
		if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) && (start == 0) && (winner == 2) && (sign == 1))
		{
			draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
		}
		if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) && (start == 0))
		{
			for (int i = 0; i < 3; i++)
			{
				if (is_user_hit(button[i], event.button.x, event.button.y))
				{
					event.type = NULL;
					switch (sign)
					{
					case 0: // экран 1. выбор темы
					{
						loadmusic(fon_m, i);
						SDL_Surface *fonImage = NULL;
						switch (i)
						{
						case 0:
						{
							fonImage = IMG_Load("key_0.bmp");
						} break;
						case 1:
						{
							fonImage = IMG_Load("key_1.bmp");
						} break;
						case 2:
						{
							fonImage = IMG_Load("key_2.bmp");
						} break;
						}

						SDL_SetColorKey(fonImage, SDL_TRUE, SDL_MapRGB(fonImage->format, 0, 0, 0));
						texture_button = SDL_CreateTextureFromSurface(renderer, fonImage);
						theme = i;
						switch (i)
						{
						case 0: {
							fonImage = IMG_Load("fon_3.bmp");
						} break;
						case 1:
						{
							fonImage = IMG_Load("fon_1.bmp");
						} break;
						case 2:
						{
							fonImage = IMG_Load("fon_2.bmp");
						} break;
						}
						fon = SDL_CreateTextureFromSurface(renderer, fonImage);
						SDL_FreeSurface(fonImage);

						sign = 1;
						init_text(renderer, button_text, 2, font, theme);
						draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
					} break;
					case 1: // экран 2. главное меню
					{
						if (i == 0) // игра
						{
							sign = 2;
							play = 0;
							init_text(renderer, button_text, 5, font, theme);
							draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 2, exit_texture);
						}
						if (i == 1) // рекорды
						{
							sign = 3;
							init_text(renderer, button_text, 4, font, theme);
							draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
							stop = 0;
						}
						if (i == 2) // выход
						{
							quit = true;
						}
					} break;
					case 2:
					{
						switch (play) // выбор уровня, сложности и режима игры
						{
						case 0: // режим
						{
							init_text(renderer, button_text, 3, font, theme);
							draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
							in_time = i;
							play = 1;
						} break;
						case 1: // уровень
						{
							lv = i;
							if (lv == 0)
							{
								lv = 4;
							}
							if (lv == 1)
							{
								lv = 9;
							}
							if (lv == 2)
							{
								lv = 16;
							}
							init_text(renderer, button_text, 4, font, theme);
							draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
							play = 2;
						} break;
						case 2: // сложность и отрисовка поля
						{
							emd = i;
							init_rect(cell, 2, lv, 0); // координаты клеток
							read_file(lv, a, index, emd, count); // цифры
							for (int j = 0; j < lv*lv; j++)
							{
								if (index[l] == 0)
									break;
								else {
									cell_text[index[l]] = get_text_texture(renderer, font, a[index[l]], a[index[l]], &red[l]);
									l++;
								}
							}
							draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
							start = 1;
							play = 0;
							start_time = clock(); // начинаем отсчет времени
						} break;
						}
					}break;
					case 3: // таблица рекордов
					{
						switch (stop)
						{
						case 0: // выбор уровня
						{
							init_text(renderer, button_text, 3, font, theme);
							draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
							lv = i;
							if (lv == 0)
							{
								lv = 4;
							}
							if (lv == 1)
							{
								lv = 9;
							}
							if (lv == 2)
							{
								lv = 16;
							}
							stop = 1;
						} break;
						case 1: // выбор сложности
						{
							emd = i;
							read_file_winner(lv, emd, winner_time, winner_name);
							for (int j = 5; j < 10; j++)
							{
								if (winner_time[j-5] < 10)
								{
									init_rect(record_rect, 3, 1, j);
								}
								else if (winner_time[j-5] < 100)
								{
									init_rect(record_rect, 3, 2, j);
								}
								else if (winner_time[j-5] < 1000)
								{
									init_rect(record_rect, 3, 3, j);
								}
								else if (winner_time[j-5] < 10000)
								{
									init_rect(record_rect, 3, 4, j);
								}
								else
								{
									init_rect(record_rect, 3, 5, j);
								}
							}
							for (int j = 0; j < 5; j++)
							{
								init_rect(record_rect, 4, strlen(winner_name[j]), j);
							}

							for (int j = 0; j < 5; j++) // текстура со временем( в секундах)
							{
								record_texture[j + 5] = get_text_texture(renderer, font, winner_time[j], winner_time[j], &in_time);
							}
							for (int j = 0; j < 5; j++) // текстура с именем
							{
								record_texture[j] = get_text_texture_text(renderer, font, winner_name[j], theme);
							}
							draw_record(renderer, fon, fon_rec, text_logo, record_texture, record_rect, 10, exit_texture);
							ex = 0;
						} break;
						}
					} break;
					}
				}
			}
		}
		if ((event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) && (start == 1)) // игровой процесс (узнаем значение какой клетки хочет поменять пользователь)
		{
			for (int i = 0; i < lv*lv; i++)
				{
					if (is_user_hit(cell[i], event.button.x, event.button.y) == 1)
					{
						play = i;
					}
				}
		}
		if ((event.type == SDL_KEYDOWN) && (play == i_help)) // для вывода цифр от 10 до 16(для уровня 16х16)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
			{
				cell_text[play] = get_text_texture(renderer, font, 11, a[play], &red[play]);
				count[play] = 1;
				draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
				start = game_end(count, red, lv);
				i_help = -5;
				z = 1;
			} break;
			case SDLK_2:
			{
				cell_text[play] = get_text_texture(renderer, font, 12, a[play], &red[play]);
				count[play] = 1;
				draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
				start = game_end(count, red, lv);
				i_help = -5;
				z = 1;
			} break;
			case SDLK_3:
			{
				cell_text[play] = get_text_texture(renderer, font, 13, a[play], &red[play]);
				count[play] = 1;
				draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
				start = game_end(count, red, lv);
				i_help = -5;
				z = 1;
			} break;
			case SDLK_4:
			{
				cell_text[play] = get_text_texture(renderer, font, 14, a[play], &red[play]);
				count[play] = 1;
				draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
				start = game_end(count, red, lv);
				i_help = -5;
				z = 1;
			} break;
			case SDLK_5:
			{
				cell_text[play] = get_text_texture(renderer, font, 15, a[play], &red[play]);
				count[play] = 1;
				draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
				start = game_end(count, red, lv);
				i_help = -5;
				z = 1;
				
			} break;
			case SDLK_6:
			{
				cell_text[play] = get_text_texture(renderer, font, 16, a[play], &red[play]);
				count[play] = 1;
				draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
				start = game_end(count, red, lv);
				i_help = -5;
				z = 1;
			} break;
			case SDLK_0:
			{
				cell_text[play] = get_text_texture(renderer, font, 10, a[play], &red[play]);
				count[play] = 1;
				draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
				start = game_end(count, red, lv);	
				i_help = -5;
				z = 1;
			} break;
			case SDLK_7:
			{
				if (lv > 4)
				{
					cell_text[play] = get_text_texture(renderer, font, 7, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
					i_help = -5;
					z = 1;
				}
			} break;
			case SDLK_8:
			{
				if (lv > 4)
				{
					cell_text[play] = get_text_texture(renderer, font, 8, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
					i_help = -5;
					z = 1;
				}
			} break;
			case SDLK_9:
			{
				if (lv > 4)
				{
					cell_text[play] = get_text_texture(renderer, font, 9, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
					i_help = -5;
					z = 1;
				}
			} break;
			}
		}
		if ((event.type == SDL_KEYDOWN) && (play >= 0) && (play != i_help)) // ввод цифр пользователем
		{			
			switch (event.key.keysym.sym)
			{
			case SDLK_1:
			{
				if ((lv == 16) && (z != 1))
				{
					i_help = play;
				}
				if (z != 1) {

					cell_text[play] = get_text_texture(renderer, font, 1, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
				}
			} break;
			case SDLK_2:
			{
				if (z != 1) {

					cell_text[play] = get_text_texture(renderer, font, 2, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
				}
			} break;
			case SDLK_3:
			{
				if (z != 1) {
					cell_text[play] = get_text_texture(renderer, font, 3, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
				}
			} break;
			case SDLK_4:
			{
				if (z != 1) {
					cell_text[play] = get_text_texture(renderer, font, 4, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
				}
			} break;
			case SDLK_5:
			{
				if (lv > 4)
				{
					if (z != 1) {
						cell_text[play] = get_text_texture(renderer, font, 5, a[play], &red[play]);
						count[play] = 1;
						draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
						start = game_end(count, red, lv);
					}
				}
			} break;
			case SDLK_6:
			{
				if (lv > 4)
				{
					if (z != 1) {
						cell_text[play] = get_text_texture(renderer, font, 6, a[play], &red[play]);
						count[play] = 1;
						draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
						start = game_end(count, red, lv);
					}
				}
			} break;
			case SDLK_7:
			{
				if (lv > 4)
				{
					cell_text[play] = get_text_texture(renderer, font, 7, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
				}
			} break;
			case SDLK_8:
			{
				if (lv > 4)
				{
					cell_text[play] = get_text_texture(renderer, font, 8, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
				}
			} break;
			case SDLK_9:
			{
				if (lv > 4)
				{
					cell_text[play] = get_text_texture(renderer, font, 9, a[play], &red[play]);
					count[play] = 1;
					draw_game(0, lv, renderer, fon, cell_fon, text_logo, cell_text, cell, lv*lv, exit_texture);
					start = game_end(count, red, lv);
				}
			} break;
			}
		}
		z = 0;
		if ((winner == 3)  && (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)) // возврат в главное меню после игры?
		{
			event.type = NULL;
			start = 0;
			sign = 1;
			init_text(renderer, button_text, 2, font, theme);
			draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
		}
		if (new_record == 1) // пользователь вводит свое имя
		{
			draw_name(renderer, fon, text_logo, cell_fon, winner_text, winner_new_rect, name_text, name_win);
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				for (int i = 0; i < 13; i++)
				{
					if (is_user_hit(name_win[i], event.button.x, event.button.y) == 1)
					{
						if (i == 12)
						{
							time_win(time, winner_time, lv, emd, winner_name, t_name); // запись в файл
							start = 0;
							init_text(renderer, button_text, 2, font, theme);
							draw_game(0, lv, renderer, fon, texture_button, text_logo, button_text, button, 3, exit_texture);
							new_record = 0;
							sign = 1;
						}
						else
						{
							key = i;
						}
					}
				}
			}
		}
		if (winner == 1) // время - рекорд
		{
			draw_game(0, lv, renderer, fon, NULL, text_logo, winner_text, winner_new_rect, 2, exit_texture);
			init_text(renderer, winner_text, 8, font, theme);
			winner_new_rect[0] = { 275, 250, 250, 50 };
			winner_new_rect[1] = { 375, 400, 50, 50 };
			new_record = 1;
			winner = 2;
		}
		if (start == 2) // пользователь победил
		{
			end_time = clock(); // время окончания игры
			time = (end_time - start_time) / CLOCKS_PER_SEC; // время игры в секундах
	
			init_text(renderer, winner_text, 7, font, theme);
			start = 3;
			play = -1;
			if (in_time == 0) // проверяем новое время( если новое время рекорд, то просим пользователя ввести имя)
			{
				for (int i = 0; i < 5; i++) 
				{
					for (int j = 0; j < 5; j++)
					{
						if (time < winner_time[j])
						{
							winner = 1;
							draw_game(0, lv, renderer, fon, NULL, text_logo, &winner_text[0], &winner_new_rect[0], 1, exit_texture);
						}
					}
				}
			}
			else
			{
				if (winner != 1)
				{
					draw_game(0, lv, renderer, fon, NULL, text_logo, &winner_text[0], &winner_new_rect[0], 1, exit_texture);
					winner = 3;
				}
			}
		}
		if ((event.type == SDL_KEYDOWN) && (key >= 0)) // ввод имени
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
			{
				t_name[key] = 'A';
				char t[] = "A";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_b:
			{
				t_name[key] = 'B';
				char t[] = "B";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_c:
			{
				t_name[key] = 'C';
				char t[] = "C";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_d:
			{
				t_name[key] = 'D';
				char t[] = "D";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_e:
			{
				t_name[key] = 'E';
				char t[] = "E";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_f:
			{
				t_name[key] = 'F';
				char t[] = "F";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_g:
			{
				t_name[key] = 'G';
				char t[] = "G";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_h:
			{
				t_name[key] = 'H';
				char t[] = "H";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_i:
			{
				t_name[key] = 'I';
				char t[] = "I";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_j:
			{
				t_name[key] = 'J';
				char t[] = "J";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_k:
			{
				t_name[key] = 'K';
				char t[] = "K";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_l:
			{
				t_name[key] = 'L';
				char t[] = "L";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_n:
			{
				t_name[key] = 'N';
				char t[] = "N";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_m:
			{
				t_name[key] = 'M';
				char t[] = "M";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_o:
			{
				t_name[key] = 'O';
				char t[] = "O";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_p:
			{
				t_name[key] = 'P';
				char t[] = "P";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_q:
			{
				t_name[key] = 'Q';
				char t[] = "Q";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_r:
			{
				t_name[key] = 'R';
				char t[] = "R";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_s:
			{
				t_name[key] = 'S';
				char t[] = "S";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_t:
			{
				t_name[key] = 'T';
				char t[] = "T";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_u:
			{
				t_name[key] = 'U';
				char t[] = "U";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_v:
			{
				t_name[key] = 'V';
				char t[] = "V";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_w:
			{
				t_name[key] = 'W';
				char t[] = "W";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_x:
			{
				t_name[key] = 'X';
				char t[] = "X";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_y:
			{
				t_name[key] = 'Y';
				char t[] = "Y";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;
			case SDLK_z:
			{
				t_name[key] = 'Z';
				char t[] = "Z";
				name_text[key] = get_text_texture_text(renderer, font, t, 0);
			} break;

			}
		}

	}

	for (int i = 0; i < 2; i++)
	{
		SDL_DestroyTexture(winner_text[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		SDL_DestroyTexture(button_text[i]);
	}
	SDL_DestroyTexture(texture_button);
	SDL_DestroyTexture(game_sudocu);
	SDL_DestroyTexture(fon);
	SDL_DestroyTexture(text_logo);

	TTF_CloseFont(font); 
	TTF_Quit();				
	Mix_FreeMusic(fon_m);
	Mix_CloseAudio();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}