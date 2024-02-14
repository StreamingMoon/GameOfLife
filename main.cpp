#include<iostream>
#include<random>
#include<string>
#include<Windows.h>

using namespace std;

enum mode
{
	RandomMode,
	EditMode
};

enum entrance
{
	Initialization,
	MainPage
};

int STEP = 0;
short WIDTH;
short HEIGHT;
short NUM_CROWDED;
short NUM_LONELY;
bool** SCENE;
mode MODE;
entrance ENTRANCE = Initialization;
HANDLE HANDLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE HANDLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
_CONSOLE_CURSOR_INFO SHOWN = { 1,1 };
_CONSOLE_CURSOR_INFO HIDDEN = { 1,0 };
_CONSOLE_CURSOR_INFO EDIT = { 100,1 };

bool random()
{
	random_device seed;//硬件生成随机数种子
	ranlux48 engine(seed());//利用种子生成随机数引擎
	uniform_int_distribution<> distrib(0, 1);//设置随机数范围，并为均匀分布
	return distrib(engine);//随机数

	//return rand()%2;
}

bool** random_build()
{
	bool** scene = new bool* [HEIGHT];
	for (short height = 0; height < HEIGHT; height++)
	{
		bool* line = new bool[WIDTH];
		for (short width = 0; width < WIDTH; width++)
		{
			line[width] = random();
		}
		scene[height] = line;
	}
	return scene;
}

void display(bool** scene)
{
	SetConsoleCursorPosition(HANDLE_OUTPUT, { 0,0 });
	SetConsoleCursorInfo(HANDLE_OUTPUT, &HIDDEN);
	cout << "TIME STEP: " << STEP << endl;
	for (short y = 0; y < HEIGHT; y++)
	{
		for (short x = 0; x < WIDTH; x++)
		{
			SCENE[y][x] = scene[y][x];

			if (SCENE[y][x])
			{
				cout << "■";
			}
			else
			{
				cout << "□";
			}
		}
		cout << endl;
	}
}

void error(string text)
{
	system("cls");
	cout << text << endl;
	system("color 4f");
	system("color f4");
	system("color 4f");
	system("color f4");
	system("color 4f");
	system("color f4");
	system("color 4f");
	system("color f4");
	system("color 02");
	system("pause");
}

int choose(string text, int start, int end)
{
	int choice;
	while (true)
	{
		cout << text << endl << ">>> ";
		cin >> choice;
		if (start <= choice && choice <= end)
		{
			return choice;
		}
		else
		{
			error("ILLEGAL ARGUMENTS!!!");
			cin.ignore(INT_MAX, '\n');
			cin.clear();
		}
	}
}

short count(short x, short y)
{
	short num = 0;
	//u
	if (y > 0)
	{
		//ud
		if (y + 1 < HEIGHT)
		{
			//udl
			if (x > 0)
			{
				//udlr
				if (x + 1 < WIDTH)
				{
					if (SCENE[y - 1][x - 1])
					{
						num++;
					}
					if (SCENE[y - 1][x])
					{
						num++;
					}
					if (SCENE[y - 1][x + 1])
					{
						num++;
					}
					if (SCENE[y][x - 1])
					{
						num++;
					}
					if (SCENE[y][x + 1])
					{
						num++;
					}
					if (SCENE[y + 1][x - 1])
					{
						num++;
					}
					if (SCENE[y + 1][x])
					{
						num++;
					}
					if (SCENE[y + 1][x + 1])
					{
						num++;
					}
				}
				//udl!r
				else
				{
					if (SCENE[y - 1][x - 1])
					{
						num++;
					}
					if (SCENE[y - 1][x])
					{
						num++;
					}
					if (SCENE[y][x - 1])
					{
						num++;
					}
					if (SCENE[y + 1][x - 1])
					{
						num++;
					}
					if (SCENE[y + 1][x])
					{
						num++;
					}
				}
			}
			//ud!l(r)
			else
			{
				if (SCENE[y - 1][x])
				{
					num++;
				}
				if (SCENE[y - 1][x + 1])
				{
					num++;
				}
				if (SCENE[y][x + 1])
				{
					num++;
				}
				if (SCENE[y + 1][x])
				{
					num++;
				}
				if (SCENE[y + 1][x + 1])
				{
					num++;
				}
			}
		}
		//u!d
		else
		{
			//u!dl
			if (x > 0)
			{
				//u!dlr
				if (x + 1 < WIDTH)
				{
					if (SCENE[y - 1][x - 1])
					{
						num++;
					}
					if (SCENE[y - 1][x])
					{
						num++;
					}
					if (SCENE[y - 1][x + 1])
					{
						num++;
					}
					if (SCENE[y][x - 1])
					{
						num++;
					}
					if (SCENE[y][x + 1])
					{
						num++;
					}
				}
				//u!dl!r
				else
				{
					if (SCENE[y - 1][x - 1])
					{
						num++;
					}
					if (SCENE[y - 1][x])
					{
						num++;
					}
					if (SCENE[y][x - 1])
					{
						num++;
					}

				}
			}
			//u!d!l(r)
			else
			{
				if (SCENE[y - 1][x])
				{
					num++;
				}
				if (SCENE[y - 1][x + 1])
				{
					num++;
				}
				if (SCENE[y][x + 1])
				{
					num++;
				}

			}
		}
	}
	//!u
	else
	{
		//!u(d)l
		if (x > 0)
		{
			//!u(d)lr
			if (x + 1 < WIDTH)
			{
				if (SCENE[y][x - 1])
				{
					num++;
				}
				if (SCENE[y][x + 1])
				{
					num++;
				}
				if (SCENE[y + 1][x - 1])
				{
					num++;
				}
				if (SCENE[y + 1][x])
				{
					num++;
				}
				if (SCENE[y + 1][x + 1])
				{
					num++;
				}
			}
			//!u(d)l!r
			else
			{
				if (SCENE[y][x - 1])
				{
					num++;
				}
				if (SCENE[y + 1][x - 1])
				{
					num++;
				}
				if (SCENE[y + 1][x])
				{
					num++;
				}
			}
		}
		//!u(d)!l(r)
		else
		{
			if (SCENE[y][x + 1])
			{
				num++;
			}
			if (SCENE[y + 1][x])
			{
				num++;
			}
			if (SCENE[y + 1][x + 1])
			{
				num++;
			}
		}
	}
	return num;
}

bool compute(short x, short y)
{
	bool isalive = SCENE[y][x];
	short num = count(x, y);
	if (((num >= NUM_LONELY + 1) && (num <= NUM_CROWDED - 1) && (isalive)) || (num == NUM_CROWDED - 1))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool** update()
{
	bool** scene = new bool* [HEIGHT];
	for (int i = 0; i < HEIGHT; i++)
	{
		scene[i] = new bool[WIDTH];
	}
	for (short y = 0; y < HEIGHT; y++)
	{
		for (short x = 0; x < WIDTH; x++)
		{
			scene[y][x] = compute(x, y);
		}
	}
	return scene;
}

bool** edit(bool** scene)
{
	DWORD mode;
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleMode(HANDLE_INPUT, &mode);
	SetConsoleMode(HANDLE_INPUT, mode & (~ENABLE_ECHO_INPUT));
	GetConsoleScreenBufferInfo(HANDLE_OUTPUT, &buffer_info);
	SetConsoleCursorPosition(HANDLE_OUTPUT, { 0,1 });
	SetConsoleCursorInfo(HANDLE_OUTPUT, &EDIT);
	COORD position = buffer_info.dwCursorPosition = {0,1};
	while (true)
	{
		if (GetForegroundWindow() == GetConsoleWindow())
		{
			if (GetAsyncKeyState(VK_UP) & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState(VK_UP) & 0x01)
					{
						if (position.Y - 1 > 0)
						{
							position.Y--;
						}
						SetConsoleCursorPosition(HANDLE_OUTPUT, position);
						break;
					}
				}
			}
			if (GetAsyncKeyState(VK_DOWN) & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState(VK_DOWN) & 0x01)
					{
						if (position.Y + 1 <= HEIGHT)
						{
							position.Y++;
						}
						SetConsoleCursorPosition(HANDLE_OUTPUT, position);
						break;
					}
				}
			}
			if (GetAsyncKeyState(VK_LEFT) & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState(VK_LEFT) & 0x01)
					{
						if (position.X - 2 >= 0)
						{
							position.X--;
							position.X--;
						}
						SetConsoleCursorPosition(HANDLE_OUTPUT, position);
						break;
					}
				}
			}
			if (GetAsyncKeyState(VK_RIGHT) & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState(VK_RIGHT) & 0x01)
					{
						if (position.X + 2 <= WIDTH * 2)
						{
							position.X++;
							position.X++;
						}
						SetConsoleCursorPosition(HANDLE_OUTPUT, position);
						break;
					}
				}
			}
			if (GetAsyncKeyState(VK_RETURN) & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState(VK_RETURN) & 0x01)
					{
						if (GetConsoleScreenBufferInfo(HANDLE_OUTPUT, &buffer_info))
						{
							COORD position = buffer_info.dwCursorPosition;
							if (0 <= position.X && position.X < WIDTH * 2 && 1 <= position.Y && position.Y <= HEIGHT)
							{
								GetConsoleMode(HANDLE_INPUT, &mode);
								SetConsoleMode(HANDLE_INPUT, mode | (ENABLE_ECHO_INPUT));
								scene[position.Y - 1][position.X / 2] = !scene[position.Y - 1][position.X / 2];
								update();
								display(scene);
								GetConsoleMode(HANDLE_INPUT, &mode);
								SetConsoleMode(HANDLE_INPUT, mode & (~ENABLE_ECHO_INPUT));
								SetConsoleCursorPosition(HANDLE_OUTPUT, position);
								SetConsoleCursorInfo(HANDLE_OUTPUT, &EDIT);

							}

						}
						break;
					}
				}
			}
			if (GetAsyncKeyState('E') & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState('E') & 0x01)
					{
						if (GetAsyncKeyState(VK_MENU) & 0x01)
						{
							while (true)
							{
								if (!GetAsyncKeyState(VK_MENU) & 0x01)
								{
									SetConsoleCursorInfo(HANDLE_OUTPUT, &HIDDEN);
									FlushConsoleInputBuffer(HANDLE_INPUT);
									return scene;
								}
							}
						}
					}
				}
			}
		}
	}
}

bool** edit_build()
{
	DWORD mode;
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	bool** scene = new bool* [HEIGHT];
	for (short height = 0; height < HEIGHT; height++)
	{
		bool* line = new bool[WIDTH];
		for (short width = 0; width < WIDTH; width++)
		{
			line[width] = 0;
		}
		scene[height] = line;
	}
	system("cls");
	display(scene);
	return(edit(scene));
}

void initialization();

void main_page(mode mode);

entrance contorl()
{
	cout << R"(-------------------------------------
Press "N" to Next Step
Press "A" to Auto Play
Press "P" to Pause(No Auto Play)
Press "R" to Restart(Keep Settings)
Press "Ctrl"+"E" to Edit
Press "Alt"+"E" to Exit Edit
Press "↑","↓","←","→" to move cursor
Press "E" to Exit(Clear Settings)
-------------------------------------)";
	SetConsoleCursorInfo(HANDLE_OUTPUT, &HIDDEN);
	while (true)
	{
		if (GetForegroundWindow() == GetConsoleWindow())
		{
			if (GetAsyncKeyState('N') & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState('N') & 0x01)
					{
						STEP++;
						display(update());
						break;
					}
				}
			}
			if (GetAsyncKeyState('A') & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState('A') & 0x01)
					{
						while (true)
						{
							if (GetForegroundWindow() == GetConsoleWindow())
							{
								if (GetAsyncKeyState('P') & 0x01)
								{
									while (true)
									{
										if (!GetAsyncKeyState('P') & 0x01)
										{
											break;
										}
									}
									break;
								}
								if (GetAsyncKeyState('E') & 0x01 && !GetAsyncKeyState(VK_MENU) & 0x01)
								{
									while (true)
									{
										if (!GetAsyncKeyState('E') & 0x01 )
										{
											if (GetAsyncKeyState(VK_CONTROL) & 0x01)
											{
												while (true)
												{
													if (!GetAsyncKeyState(VK_CONTROL) & 0x01)
													{
														edit(SCENE);
														SetConsoleCursorInfo(HANDLE_OUTPUT, &HIDDEN);
														break;
													}
												}
											}
											else
											{
												return Initialization;
											}
										}
										break;
									}
								}
								if (GetAsyncKeyState('R') & 0x01)
								{
									while (true)
									{
										if (!GetAsyncKeyState('R') & 0x01)
										{
											return MainPage;
										}
									}
								}
								STEP++;
								display(update());
							}
						}
						break;
					}
				}
			}
			if (GetAsyncKeyState('R') & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState('R') & 0x01)
					{
						return MainPage;
					}
				}
			}
			if (GetAsyncKeyState('E') & 0x01 && !GetAsyncKeyState(VK_MENU) & 0x01)
			{
				while (true)
				{
					if (!GetAsyncKeyState('E') & 0x01)
					{
						if (GetAsyncKeyState(VK_CONTROL) & 0x01)
						{
							while (true)
							{
								if (!GetAsyncKeyState(VK_CONTROL) & 0x01)
								{
									edit(SCENE);
									SetConsoleCursorInfo(HANDLE_OUTPUT, &HIDDEN);
									break;
								}
							}
						}
						else
						{
							return Initialization;
						}
						break;
					}
				}
			}
		}
	}
}

void main_page(mode mode)
{
	STEP = 0;
	if (mode == RandomMode)
	{
		SCENE = random_build();
	}
	else
	{
		SCENE = edit_build();
	}
	system("cls");
	STEP++;
	display(SCENE);
	ENTRANCE = contorl();
}

void initialization()
{
	STEP = 0;
	SetConsoleCursorInfo(HANDLE_OUTPUT, &SHOWN);
	SetConsoleTitleA("Game of Life");
	DWORD mode;
	GetConsoleMode(HANDLE_INPUT,&mode);
	SetConsoleMode(HANDLE_INPUT, mode | (ENABLE_ECHO_INPUT));
	
	system("cls");
	cout <<
		R"(□□□□□□□□□□□□□□□□□□□□□□
□□■■■□□□□□□□□□□□□□□□□□
□■□□□□□□□□□□□□□□□□□□□□
□■□□□□□□□□□□□□□□□□■■□□
□■□■■□■■■□□■■■■■□■□□■□
□■□□■□■□■□□■□■□■□■■■■□
□□■■■□■■■■□■□■□■□■□□□□
□□□□□□□□□□□□□□□□□□■■□□
□□□□□□□□□□□□■■□□□□□□□□
□□□□□□■■■□□□■□□□□□□□□□
□□□□□□■□■□□□■□□□□□□□□□
□□□□□□■■■□■■■■■□□□□□□□
□□□□□□□□□□□□■□□□□□□□□□
□□■□□□□□■□□□■□□□□□□□□□
□□■□□□□□□□□□■□□□□■■□□□
□□■□□□□□■□□□■□□□■□□■□□
□□■□□□□□■□□□■□□□■■■■□□
□□■□□□□□■□□□■□□□■□□□□□
□□■■■■□□■□□□■□□□□■■□□□
□□□□□□□□□□□□□□□□□□□□□□
)";
	FlushConsoleInputBuffer(HANDLE_INPUT);
	switch (choose(R"(1.Random Mode
2.Edit Mode
0.Exit)", 0, 2))
	{
	case 0:
		exit(0);
		break;
	case 1:
		MODE = RandomMode;
		break;
	case 2:
		MODE = EditMode;
		break;
	}
	system("cls");
	cout << "WIDTH:" << endl << ">>> ";
	cin >> WIDTH;
	cout << "HEIGHT:" << endl << ">>> ";
	cin >> HEIGHT;
	cout << "NUM_CROWDED:" << endl << ">>> ";
	cin >> NUM_CROWDED;
	cout << "NUM_LONELY:" << endl << ">>> ";
	cin >> NUM_LONELY;
	SCENE = new bool* [HEIGHT];
	for (short height = 0; height < HEIGHT; height++)
	{
		bool* line = new bool[WIDTH];
		for (short width = 0; width < WIDTH; width++)
		{
			line[width] = 0;
		}
		SCENE[height] = line;
	}
}

int main()
{
	while (true)
	{
		if (ENTRANCE == Initialization)
		{
			initialization();
		}
		main_page(MODE);
	}
	return 0;
}
