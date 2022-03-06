#include <iostream>
#include <ostream>
#include <string>
#define OLC_PGE_APPLICATION

#include "GameOfLife.h"
#include "olcPixelGameEngine.h"

const int SIZE_X = 200;
const int SIZE_Y = 200;
const int PIX_SIZE = 4;

const std::string FILES[] = {"patterns/gospers_gun.txt",
								"patterns/demonoid.txt",
								"patterns/wheel.txt"};
const std::vector<olc::Key> KEYS = {olc::K1, olc::K2, olc::K3};

class Example : public olc::PixelGameEngine
{
	public:
		Example() : board(SIZE_X, SIZE_Y), period(0), max_FPS(1)
		{
			sAppName = "Game Of Life - Erik";
			playing = true;

			// board.random();
			std::vector<std::vector<bool>> setup;
			for(int i = 0; i < SIZE_X; i++)
			{
				std::vector<bool> row;
				for(int j = 0; j < SIZE_Y; j++)
					row.push_back(false);
				setup.push_back(row);
    		}
			int middle_x = SIZE_X / 2;
			int middle_y = SIZE_Y / 2;

			setup[middle_x - 1][middle_y] = true;
			setup[middle_x - 1][middle_y + 1] = true;
			setup[middle_x][middle_y] = true;
			setup[middle_x][middle_y - 1] = true;
			setup[middle_x + 1][middle_y] = true;
			
			board.Setup(setup);

			showHelp();
		};

	public:
		bool OnUserCreate() override
		{

			// Called once at the start, so create things here
			return true;
		};

		bool OnUserUpdate(float fElapsedTime) override
		{
			// std::cout << fElapsedTime << "\n";
			period += fElapsedTime;

			// called once per frame
			// Show the board
			showBoard();

			// DrawString(0,0,std::to_string(max_FPS), olc::WHITE, 1);

			if(GetKey(olc::SPACE).bPressed)
				playing = !playing;

			if(GetKey(olc::C).bPressed)
				board.clear();

			if(GetKey(olc::R).bPressed)
				board.random();

			if(GetKey(olc::UP).bPressed)
				max_FPS++;

			if(GetKey(olc::DOWN).bPressed && max_FPS > 0)
				max_FPS--;			
			
			if(GetKey(olc::RIGHT).bPressed)
				max_FPS += 10;

			if(GetKey(olc::LEFT).bPressed && max_FPS > 9)
				max_FPS -= 10;

			if(GetMouse(0).bPressed)
				board.change(GetMouseX(), GetMouseY());	

			if(GetKey(olc::S).bPressed)
			{
				SavePos("test.txt");
			}
			if(GetKey(olc::O).bPressed)
			{
				LoadPos("test.txt");
			}

			for(int i = 0; i < KEYS.size(); i++)
				if(GetKey(KEYS[i]).bPressed)
					LoadPos(FILES[i]);


			if(period * 100 < 60 / float(max_FPS))
				return true;

			period = 0;

			if(playing)
				board.nextGen();
			return true;
		};

		void showBoard()
		{
			for (int x = 0; x < ScreenWidth(); x++)
				for (int y = 0; y < ScreenHeight(); y++)
				{
						// Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
					// Draw(x, y, olc::Pixel(x, y, x));	
					if (board.isAlive(x, y))
						Draw(x, y, olc::Pixel(255, 255, 255));	
					else
						Draw(x, y, olc::Pixel(0, 0, 0));
				}
		};
		void showHelp()
		{
			std::cout << "Help - GameOfLife - Erik\n";
			std::cout << "\n";
			std::cout << "c : clear\n";
			std::cout << "r : random\n";
			std::cout << "UP : go faster\n";
			std::cout << "DOWN : go slower\n";
			std::cout << "RIGHT : go way faster\n";
			std::cout << "LEFT : go way slower\n";
			std::cout << "s : save to file (test.txt)\n";
			std::cout << "o : open file (test.txt)\n";
			for(int i = 0; i < KEYS.size(); i++)
				std::cout << i << " : open " << FILES[i] << "\n";
			std::cout << "SPACE : pause/play\n";
			std::cout << "Clicking with the mouse : change a cell\n";
		};
		void SavePos(std::string filename)
		{
			std::fstream of(filename, std::ios::out | std::ios::app);
			if (of.is_open())
			{
				board.SaveToFile(of);
				// writemap(std::cout, map);
				of.close();
			}
		}
		void LoadPos(std::string filename)
		{
			std::fstream in(filename, std::ios::in | std::ios::app);
			if (in.is_open())
			{
				board.LoadFromFile(in);
				// writemap(std::cout, map);
				in.close();
			}
		}

	private:
		int max_FPS;
		float period;
		GameOfLife board;
		bool playing;
};


int main()
{
	bool fullscreen = false;
	Example demo;
	if (demo.Construct(SIZE_X, SIZE_Y, PIX_SIZE, PIX_SIZE, fullscreen, true))
		demo.Start();

	return 0;
}
