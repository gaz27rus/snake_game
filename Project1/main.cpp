#include <SDL.h>
#include <SDL_mouse.h>
#include <SDL_image.h>
#include <cstdio>
#include <thread>
#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
enum Directions
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

class window
{
public:
	window(int w, int h) : WIDTH(w), HEIGHT(h)
	{
		win = SDL_CreateWindow("Game", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	}

	SDL_Window *get_win()
	{
		return win;
	}

	~window()
	{
		SDL_DestroyWindow(win);

	}

private:
	int WIDTH, HEIGHT;
	SDL_Window *win = NULL; 
};

class Renderer
{
public:
	Renderer(SDL_Window* window, int index, Uint32 flag)
	{
		renderer = SDL_CreateRenderer(window, index, flag);
	}

	SDL_Renderer *get_ren()
	{
		return renderer;
	}

	~Renderer()
	{
		SDL_DestroyRenderer(renderer);
	}
	

private:
	SDL_Renderer *renderer = NULL;
};


class Texture
{
public:
	Texture(SDL_Renderer* renderer, char* path, int X, int Y)
	{
		x = X;
		y = Y;
		surface = IMG_Load(path);
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			std::cout << "Failed" << IMG_GetError() << std::endl;
		}

		if (surface == nullptr){
			std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
	}

	SDL_Texture* get_texture()
	{
		return texture;
	}

	void set_DestR(int x, int y, int w, int h)
	{
		DestR.x = x;
		DestR.y = y;
		DestR.w = w;
		DestR.h = h;
	}

	SDL_Rect* get_DestR()
	{
		return &DestR;
	}

	int get_x()
	{
		return x;
	}

	int get_y()
	{
		return y;
	}

	void set_x(int X)
	{
		x = X;
	}

	void set_y(int Y)
	{
		y = Y;
	}

	~Texture()
	{
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}

	
private:
	int x;
	int y;
	SDL_Rect DestR;
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
};

void keyboard_event()
{

}

/*struct snake_elem
{

	snake_elem(Renderer renderer)
	{
		Texture elem(renderer.get_ren(), "1.png");
		dir = RIGHT;
	}
	Directions dir;
};*/

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_VIDEO);
	int x, y;

	window w1(300, 300);
	Renderer renderer(w1.get_win(), -1, SDL_RENDERER_ACCELERATED);
	Texture image(renderer.get_ren(), "C:/Programming/Games_images/XO/bg.jpg", 0, 0);
	//Texture snake(renderer.get_ren(), "1.png");
	//snake.set_DestR(300, 300, 16, 16);
	std::vector<Texture*> snake;
	std::vector<Directions> dirs;
	int x_dir = 300;
	int y_dir = 300;
	
	snake.push_back(new Texture(renderer.get_ren(), "1.png", x_dir - 16 * 0, y_dir));
	dirs.push_back(RIGHT);
	snake.push_back(new Texture(renderer.get_ren(), "1.png", x_dir - 16 * 1, y_dir));
	dirs.push_back(RIGHT);
	snake.push_back(new Texture(renderer.get_ren(), "1.png", x_dir - 16 * 2, y_dir));
	dirs.push_back(RIGHT);
	snake.push_back(new Texture(renderer.get_ren(), "1.png", x_dir - 16 * 3, y_dir));
	dirs.push_back(RIGHT);
	snake.push_back(new Texture(renderer.get_ren(), "1.png", x_dir - 16 * 4, y_dir));
	dirs.push_back(RIGHT);
	snake.push_back(new Texture(renderer.get_ren(), "1.png", x_dir - 16 * 5, y_dir));
	dirs.push_back(RIGHT);
	int k = 300;
	SDL_Rect SrcR;
	SDL_Rect DestR;
	Directions dir = RIGHT;
	
	snake[0]->set_DestR(x_dir - 16 * 0, y_dir, 16, 16);
	snake[1]->set_DestR(x_dir - 16 * 1, y_dir, 16, 16);
	snake[2]->set_DestR(x_dir - 16 * 2, y_dir, 16, 16);
	snake[3]->set_DestR(x_dir - 16 * 3, y_dir, 16, 16);
	snake[4]->set_DestR(x_dir - 16 * 4, y_dir, 16, 16);
	snake[5]->set_DestR(x_dir - 16 * 5, y_dir, 16, 16);

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cout << "Failed" << IMG_GetError() << std::endl;
	}

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SDL_GetMouseState(&x, &y);

		SDL_RenderClear(renderer.get_ren());
		SDL_RenderCopy(renderer.get_ren(), image.get_texture(), NULL, NULL);
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
			{
							dirs[0] = UP;
			} break;
			case SDLK_DOWN:
			{
							  dirs[0] = DOWN;
			} break;
			case SDLK_RIGHT:
			{
							   dirs[0] = RIGHT;
			} break;
			case SDLK_LEFT:
			{
							  dirs[0] = LEFT;
			} break;
			default:
				break;
			}
		}

		for (int i = 1; i < snake.size(); i++)
		{
			if (dirs[i - 1] == UP || dirs[i - 1] == DOWN)
			{
				if (abs(snake[i - 1]->get_y() - snake[i]->get_y()) >= 16)// || abs(snake[i - 1]->get_x() - snake[i]->get_x()) > 16)
				{
					std::cout << " hi " << dirs[i] << snake[i]->get_x() << " " << snake[i]->get_y() << " ";
					dirs[i] = dirs[i - 1];
				}
			}
			else if (dirs[i - 1] == RIGHT || dirs[i - 1] == LEFT)
			{
				if (abs(snake[i - 1]->get_x() - snake[i]->get_x()) >= 16)
				{
					std::cout << " hi " << dirs[i] << snake[i]->get_x() << " " << snake[i]->get_y() << " ";
					dirs[i] = dirs[i - 1];
				}
			}
		}

		for (int i = 0; i < snake.size(); i++)
		{
			//std::cout << dirs[i] << " ";
			switch (dirs[i])
			{
			case UP:
			{
						  //y_dir -= 1;
						  snake[i]->set_y(snake[i]->get_y() - 2);
						  snake[i]->set_DestR(snake[i]->get_x(), snake[i]->get_y(), 16, 16);
			} break;
			case DOWN:
			{
						  snake[i]->set_y(snake[i]->get_y() + 2);
						  snake[i]->set_DestR(snake[i]->get_x(), snake[i]->get_y(), 16, 16);
			} break; 
			case RIGHT:
			{
						  snake[i]->set_x(snake[i]->get_x() + 2);
						  snake[i]->set_DestR(snake[i]->get_x(), snake[i]->get_y(), 16, 16);

			} break;
			case LEFT:
			{
						  snake[i]->set_x(snake[i]->get_x() - 2);
						  snake[i]->set_DestR(snake[i]->get_x(), snake[i]->get_y(), 16, 16);
			} break;
			default:
				break;
			}
		}
		for (auto i : snake)
		{
			SDL_RenderCopy(renderer.get_ren(), i->get_texture(), NULL, i->get_DestR());
		}
		
		SDL_RenderPresent(renderer.get_ren());
		SDL_ShowWindow(w1.get_win());
		std::cout << snake.size() << " " << dirs.size() << std::endl;
		SDL_Delay(30);
	}
	
	SDL_Quit();
	return 0;
}