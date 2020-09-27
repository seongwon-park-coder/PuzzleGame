#define _CRT_SECURE_NO_WARNINGS

#include <bangtal.h>
#include<ctime>
#include<iostream>

using namespace bangtal;
using namespace std;


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);


	srand((unsigned int)time(NULL));
	time_t start_time;

	auto scene0 = Scene::create("puzzle", "images/초기화면.png");
	auto scene1 = Scene::create("puzzle", "images/원본.png");
	auto scene2 = Scene::create("puzzle", "images/배경.png");
	auto scene3 = Scene::create("puzzle", "images2/원본.png");
	auto scene4 = Scene::create("puzzle", "images2/배경.png");

	auto pic1 = Object::create("images/원본.png", scene0, 120, 100, true);
	pic1->setScale(0.4f);
	auto pic2 = Object::create("images2/원본.png", scene0, 660, 100, true);
	pic2->setScale(0.4f);


	pic1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	pic2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene3->enter();
		return true;
		});

	auto startButton = Object::create("images/start.png", scene1, 500, 100, true);
	startButton->setScale(2.0f);
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	auto startButton2 = Object::create("images2/start.png", scene3, 500, 100, true);
	startButton2->setScale(2.0f);
	startButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene4->enter();
		return true;
		});

	ObjectPtr board[16], init_board[16];
	int blank = 15;

	for (int i = 0; i < 16; i++) {
		string filename = "images/" + to_string(i + 1) + ".png";
		board[i] = Object::create(filename, scene2, 300 + (i % 4) * 150, 470 - (i / 4) * 150);

		init_board[i] = board[i];

		board[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)->bool {
			int j;
			for (j = 0;j < 16;j++) {
				if (board[j] == object)
					break;
			}

			if ((j % 4 > 0 && j - 1 == blank) ||
				(j % 4 < 3 && j + 1 == blank) ||
				(j > 3 && j - 4 == blank) ||
				(j < 12 && j + 4 == blank)) {


				board[j]->locate(scene2, 300 + (blank % 4) * 150, 470 - (blank / 4) * 150);
				board[blank]->locate(scene2, 300 + (j % 4) * 150, 470 - (j / 4) * 150);

				board[j] = board[blank];
				board[blank] = object;
				blank = j;

				int k;

				for (k = 0; k < 16;k++)
				{
					if (board[k] != init_board[k]) break;
				}

				if (k == 16) {
					auto end_time = time(NULL);
					string buf = to_string(difftime(end_time, start_time))
						+ "걸렸습니다!";
					showMessage(buf.c_str());

				}
			}

			return true;
			});
	}

	board[blank]->hide();

	auto count = 0;
	auto timer = Timer::create(0.1f);
	timer->setOnTimerCallback([&](TimerPtr t)->bool {
		int j;
		do {
			switch (rand() % 4) {
			case 0: j = blank - 1; break;
			case 1: j = blank + 1; break;
			case 2: j = blank - 4; break;
			case 3: j = blank + 4; break;
			}
		} while (j < 0 || j > 15 || !((j % 4 > 0 && j - 1 == blank) ||
			(j % 4 < 3 && j + 1 == blank) ||
			(j > 3 && j - 4 == blank) ||
			(j < 12 && j + 4 == blank)));

		board[j]->locate(scene2, 300 + (blank % 4) * 150, 470 - (blank / 4) * 150);
		board[blank]->locate(scene2, 300 + (j % 4) * 150, 470 - (j / 4) * 150);

		auto object = board[j];
		board[j] = board[blank];
		board[blank] = object;
		blank = j;

		count++;
		if (count < 100) {
			t->set(0.1f);
			t->start();
		}
		return true;
		});


	ObjectPtr board2[16], init_board2[16];
	int blank2 = 15;

	for (int i = 0; i < 16; i++) {
		string filename = "images2/" + to_string(i + 1) + ".png";
		board2[i] = Object::create(filename, scene4, 300 + (i % 4) * 150, 470 - (i / 4) * 150);

		init_board2[i] = board2[i];

		board2[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)->bool {
			int j;
			for (j = 0;j < 16;j++) {
				if (board2[j] == object)
					break;
			}

			if ((j % 4 > 0 && j - 1 == blank2) ||
				(j % 4 < 3 && j + 1 == blank2) ||
				(j > 3 && j - 4 == blank2) ||
				(j < 12 && j + 4 == blank2)) {


				board2[j]->locate(scene4, 300 + (blank2 % 4) * 150, 470 - (blank2 / 4) * 150);
				board2[blank2]->locate(scene4, 300 + (j % 4) * 150, 470 - (j / 4) * 150);

				board2[j] = board2[blank2];
				board2[blank2] = object;
				blank2 = j;

				int k;

				for (k = 0; k < 16;k++)
				{
					if (board2[k] != init_board2[k]) break;
				}

				if (k == 16) {
					auto end_time = time(NULL);
					string buf = to_string(difftime(end_time, start_time))
						+ "걸렸습니다!";
					showMessage(buf.c_str());

				}
			}

			return true;
			});
	}

	board2[blank2]->hide();

	auto count2 = 0;
	auto timer2 = Timer::create(0.1f);

	timer2->setOnTimerCallback([&](TimerPtr t2)->bool {
		int k;
		do {
			switch (rand() % 4) {
			case 0: k = blank2 - 1; break;
			case 1: k = blank2 + 1; break;
			case 2: k = blank2 - 4; break;
			case 3: k = blank2 + 4; break;
			}
		} while (k < 0 || k > 15 || !((k % 4 > 0 && k - 1 == blank2) ||
			(k % 4 < 3 && k + 1 == blank2) ||
			(k > 3 && k - 4 == blank2) ||
			(k < 12 && k + 4 == blank2)));

		board2[k]->locate(scene4, 300 + (blank2 % 4) * 150, 470 - (blank2 / 4) * 150);
		board2[blank2]->locate(scene4, 300 + (k % 4) * 150, 470 - (k / 4) * 150);

		auto object2 = board2[k];
		board2[k] = board2[blank2];
		board2[blank2] = object2;
		blank2 = k;

		count++;
		if (count < 100) {
			t2->set(0.1f);
			t2->start();
		}
		return true;
		});

	timer->start();
	timer2->start();

	start_time = time(NULL);
	startGame(scene0);
}
