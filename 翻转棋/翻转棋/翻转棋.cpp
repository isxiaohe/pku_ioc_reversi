
#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<Windows.h>

using namespace std;
#define Row 8
#define Col 17

string order;
char winner = 'n';
string menu = "";
char now_c = 'x';
char c='n', my_c;
int ai = 1;

char board[Row + 2][Col + 1]{};
bool Move(int x, int y);//判断是否有效，若有效则下在此处
void judge(int x);//判断输赢
void Print(int x);//输出棋盘 
void Save(int x);
void Read(int y);
void hint(int x);


int main()
{
	cout << "----R E V E R S I----\n\n\n";
	for (int i = 1; i <= Row + 1; i++)
		for (int j = 0; j <= Col; j++)
			board[i][j] = ' ';
	for (int i = 1; i <= Row; i++)
		for (int j = 0; j < Col; j += 2)
		{
			board[i][j] = '|';
		}
	for (int i = 1; i < Col; i += 2)
		board[Row + 1][i] = (i + 1) / 2 + '0';
	for (int i = 1; i <= Row; i++)
		board[i][Col] = 96 + i;
	board[4][7] = 'o';
	board[5][9] = 'o';
	board[5][7] = 'x';
	board[4][9] = 'x';
	
	cout << "DO you wanna play with AI?'1'for yes,0 for no(rather paly with real persons)：\n";
	cin >> ai;
	begin__:cout << "This is Reversi!\nHave fun!\n\nInput \"New\" to begin a new game, \"Continue\" to continue the last game, or \"Introduce\" to see the rules.\n\n";

begin_:cin >> order;//初始化游戏
	if (order == "Introduce")
	{
		cout <<1;
		goto begin__;
	}
	if (order == "New")
	{
	choose_c:cout << "Choose your/A's color(\"b\" for black,\"w\" for white):\n";
		cin >> c;
		if (c == 'b')
		{
			c = 'x';
			my_c = 'o';
			cout << "You/A choose black!\n\n";
		}
		else if (c == 'w')
		{
			c = 'o';
			my_c = 'x';
			cout << "You/A choose white!\n\n";
			Move(3, 9);
			now_c = c;
		}
		else
		{
			cout << "Invalid!\n\n";
			goto choose_c;
		}
		Save(0);
		cout << "Let the game begin!Input your move,or input \"Pause\" to temporarily stop the game.\n\n";
	}
	else if (order == "Continue")
	{
		Read(0);
	}
	else
	{
		cout << "Invalid input.Please try again:\n";
		goto begin_;
	}
	Sleep(3 * 1000);
	Print(0);
	//下面开始下棋
	while (true)
	{
		cout << "It's your/A's turn:\n";
		cin >> order;
		if (order == "Pause")
			return 0;
		else if (winner == 'n')
		{
			if (!(order.size() == 2 && order[0] >= 'a' && order[0] <= 'h' && order[1] >= '1' && order[1] <= '8'))
			{
				cout << "Invalid input!Try again please!\n";
				continue;
			}
			int x = order[0] - 96;
			int y = 2 * (order[1] - '0') - 1;
			if (Move(x, y) == 0)
			{
				cout << "Invalid move!Try again please!\n";
				continue;
			}
			Print(0);
			now_c = my_c;
		}
		else
		{
			cout << "You/A can't move this turn!\n";
			winner = 'n';
			now_c = my_c;
		}
		judge(0);
		if (winner == my_c)
		{
			if (!ai)cout << "B " << "whose color is " << my_c << " win!\n";
			else cout << "You lose...\n";
			return 2;
		}
		else if (winner == c)
		{
			if (!ai)cout << "A " << "whose color is " << c << " win!\n";
			else cout << "You win!\n";
			return 1;
		}
		Sleep(1 * 1000);
		if (winner == 'n')
		{
			if (!ai)
			{
				cout << "It's B's turn:\n";
				cin >> order;
				int x = order[0] - 96;
				int y = 2 * (order[1] - '0') - 1;
				Move(x, y);
			}//对战
			else
			{
				hint(0);//*AI算法
				cout << "Do you regret? 'y' for yes,and 'n' for no.\n";
				cin >> order;
				if (order[0] == 'y')
				{
					Read(0);
					Print(0);
					now_c = c;
					continue;
				}
			}
			Print(0);
			now_c = c;
		}
		else
		{
			cout << "AI/B can't move this turn.\n";
			winner = 'n';
			now_c = c;
		}

		//人机对战
		judge(0);
		if (winner == my_c)
		{
			if (!ai)cout << "B " << "whose color is " << my_c << " win!\n";
			else cout << "You lose...\n";
			return 2;
		}
		else if (winner == c)
		{
			if (!ai)cout << "A " << "whose color is " << c << " win!\n";
			else cout << "You win!\n";
			return 1;
		}

		Save(0);
	}
}

bool Move(int x, int y)
{
	int b = 0;
	if (x <= 0 || x > Row || y <= 0 || y >= Col) return b;
	if (board[x][y] != ' ') return b;
	if (x - 1 > 0 && board[x - 1][y] != ' ' && board[x - 1][y] != now_c)
		for (int i = x - 1; i >= 1; i--)
		{
			if (board[i][y] == board[x - 1][y])
				continue;
			else if (board[i][y] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = x - 1; j > i; j--) board[j][y] = now_c;
				break;
			}
		}
	if (x + 1 < Row && board[x + 1][y] != ' ' && board[x + 1][y] != now_c)
		for (int i = x + 1; i <= Row; i++)
		{
			if (board[i][y] == board[x + 1][y])
				continue;
			else if (board[i][y] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = x + 1; j < i; j++) board[j][y] = now_c;
				break;
			}
		}
	if (y - 2 > 0 && board[x][y - 2] != ' ' && board[x][y - 2] != now_c)
		for (int i = y - 2; i > 0; i -= 2)
		{
			if (board[x][i] == board[x][y - 2])
				continue;
			else if (board[x][i] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = y - 2; j > i; j -= 2) board[x][j] = now_c;
				break;
			}
		}
	if (y + 2 < Col && board[x][y + 2] != ' ' && board[x][y + 2] != now_c)
		for (int i = y + 2; i < Col; i += 2)
		{
			if (board[x][i] == board[x][y + 2])
				continue;
			else if (board[x][i] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = y + 2; j < i; j += 2) board[x][j] = now_c;
				break;
			}
		}
	if (x - 1 > 0 && y - 2 > 0 && board[x - 1][y - 2] != ' ' && board[x - 1][y - 2] != now_c)
		for (int i = x - 1; i > 0 && y - 2 * x + 2 * i > 0; i--)
		{
			if (board[i][y - 2 * x + 2 * i] == board[x - 1][y - 2])
				continue;
			else if (board[i][y - 2 * x + 2 * i] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = x - 1; j > i; j--) board[j][y - 2 * x + 2 * j] = now_c;
				break;
			}
		}
	if (x - 1 > 0 && y + 2 < Col && board[x - 1][y + 2] != ' ' && board[x - 1][y + 2] != now_c)
		for (int i = x - 1; i > 0 && y + 2 * x - 2 * i < Col; i--)
		{
			if (board[i][y + 2 * x - 2 * i] == board[x - 1][y + 2])
				continue;
			else if (board[i][y + 2 * x - 2 * i] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = x - 1; j > i; j--) board[j][y + 2 * x - 2 * j] = now_c;
				break;
			}
		}
	if (x + 1 < Row && y + 2 < Col && board[x + 1][y + 2] != ' ' && board[x + 1][y + 2] != now_c)
		for (int i = x + 1; i <= Row && y - 2 * x + 2 * i < Col; i++)
		{
			if (board[i][y - 2 * x + 2 * i] == board[x + 1][y + 2])
				continue;
			else if (board[i][y - 2 * x + 2 * i] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = x + 1; j < i; j++)board[j][y - 2 * x + 2 * j] = now_c;
				break;
			}
		}
	if (x + 1 < Row && y - 2 > 0 && board[x + 1][y - 2] != ' ' && board[x + 1][y - 2] != now_c)
		for (int i = x + 1; i <= Row && y + 2 * x - 2 * i < Col; i++)
		{
			if (board[i][y + 2 * x - 2 * i] == board[x + 1][y - 2])
				continue;
			else if (board[i][y + 2 * x - 2 * i] == ' ')
				break;
			else
			{
				b = 1;
				for (int j = x + 1; j < i; j++)board[j][y + 2 * x - 2 * j] = now_c;
				break;
			}
		}
	if (b) board[x][y] = now_c;
	return b;
}

void judge(int k)
{
	int b = 0, kc = 0;
	for (int x = 1; x <= Row; x++)
		for (int y = 1; y < Col; y += 2)
			if (board[x][y] == ' ' && (b == 0 || kc == 0))
			{
				if (x - 1 > 0 && board[x - 1][y] != ' ')
					for (int i = x - 1; i >= 1; i--)
					{
						if (board[i][y] == board[x - 1][y])
							continue;
						else if (board[i][y] == ' ')
							break;
						else
						{
							if (board[x - 1][y] == my_c)b = 1;
							else kc = 1;
							break;
						}
					}
				if (x + 1 < Row && board[x + 1][y] != ' ')
					for (int i = x + 1; i <= Row; i++)
					{
						if (board[i][y] == board[x + 1][y])
							continue;
						else if (board[i][y] == ' ')
							break;
						else
						{
							if (board[x + 1][y] == my_c)b = 1;
							else kc = 1;
							break;
						}
					}
				if (y - 2 > 0 && board[x][y - 2] != ' ')
					for (int i = y - 2; i > 0; i -= 2)
					{
						if (board[x][i] == board[x][y - 2])
							continue;
						else if (board[x][i] == ' ')
							break;
						else
						{
							if (board[x][y - 2] == my_c)b = 1;
							else kc = 1;
							break;
						}
					}
				if (y + 2 < Col && board[x][y + 2] != ' ')
					for (int i = y + 2; i < Col; i += 2)
					{
						if (board[x][i] == board[x][y + 2])
							continue;
						else if (board[x][i] == ' ')
							break;
						else
						{
							if (board[x][y + 2] == my_c) b = 1;
							else kc = 1;
							break;
						}
					}
				if (x - 1 > 0 && y - 2 > 0 && board[x - 1][y - 2] != ' ')
					for (int i = x - 1; i > 0 && y - 2 * x + 2 * i > 0; i--)
					{
						if (board[i][y - 2 * x + 2 * i] == board[x - 1][y - 2])
							continue;
						else if (board[i][y - 2 * x + 2 * i] == ' ')
							break;
						else
						{
							if (board[x - 1][y - 2] == my_c)b = 1;
							else kc = 1;
							break;
						}
					}
				if (x - 1 > 0 && y + 2 < Col && board[x - 1][y + 2] != ' ')
					for (int i = x - 1; i > 0 && y + 2 * x - 2 * i < Col; i--)
					{
						if (board[i][y + 2 * x - 2 * i] == board[x - 1][y + 2])
							continue;
						else if (board[i][y + 2 * x - 2 * i] == ' ')
							break;
						else
						{
							if (board[x - 1][y + 2] == my_c)b = 1;
							else kc = 1;
							break;
						}
					}
				if (x + 1 < Row && y + 2 < Col && board[x + 1][y + 2] != ' ')
					for (int i = x + 1; i <= Row && y - 2 * x + 2 * i < Col; i++)
					{
						if (board[i][y - 2 * x + 2 * i] == board[x + 1][y + 2])
							continue;
						else if (board[i][y - 2 * x + 2 * i] == ' ')
							break;
						else
						{
							if (board[x + 1][y - 2] == my_c)b = 1;
							else kc = 1;
							break;
						}
					}
				if (x + 1 < Row && y - 2 > 0 && board[x + 1][y - 2] != ' ')
					for (int i = x + 1; i <= Row && y + 2 * x - 2 * i > 0; i++)
					{
						if (board[i][y + 2 * x - 2 * i] == board[x + 1][y - 2])
							continue;
						else if (board[i][y + 2 * x - 2 * i] == ' ')
							break;
						else
						{
							if (board[x + 1][y + 2] == my_c)b = 1;
							else kc = 1;
							break;
						}
					}
			}
	if (b && kc)
	{
		winner = 'n';
	}
	else if (b && !kc)
	{
		if (now_c == c)
			winner = 's';
	}
	else if (!b && kc)
	{
		if (now_c == my_c)
			winner = 's';
	}
	else
	{
		int num_m = 0, num_y = 0;
		for (int i = 1; i <= Row; i++)
			for (int j = 1; j < Col; j += 2)
			{
				if (board[i][j] == my_c) num_m++;
				if (board[i][j] == c) num_y++;
			}
		winner = num_m > num_y ? my_c : c;
	}
}

void Print(int k)
{
	system("cls");
	for (int i = 1; i <= Row + 1; i++)
		for (int j = 0; j <= Col; j++)
		{
			cout << board[i][j];
			if (j == Col) cout << endl;
		}
	cout << endl;
}

void Save(int k)
{
	ofstream ofs;
	ofs.open("save.txt", ios::out | ios::trunc);
	ofs << c;
	for (int i = 1; i <= Row; i++)
		for (int j = 1; j < Col; j += 2)
		{
			if (board[i][j] == ' ') ofs << 't';
			else ofs << board[i][j];
		}
	ofs.close();
}

void Read(int k)
{
	ifstream ifs;
	ifs.open("save.txt", ios::in);
	ifs >> c;
	char tmp;
	for (int i = 1; i <= Row; i++)
		for (int j = 1; j < Col; j += 2)
		{
			ifs >> tmp;
			if (tmp != 't') board[i][j] = tmp;
			else board[i][j] = ' ';
		}
	ifs.close();
}

void hint(int k)
{
	if (Move(1, 1)) return;
	if (Move(1, 15)) return;
	if (Move(8, 1)) return;
	if (Move(8, 15)) return;
	for (int i = 3; i <= 6; i++)
		for (int j = 5; j <= 11; j += 2)
			if (Move(i, j)) return;
	for (int i = 1; i <= Row; i++)
	{
		if (Move(i, 1)) return;
		else if (Move(i, 15)) return;
	}
	for (int j = 1; j <= 15; j += 2)
	{
		if (Move(1, j)) return;
		else if (Move(8, j)) return;
	}
	for (int i = 2; i < Row; i++)
	{
		if (Move(i, 3)) return;
		else if (Move(i, 13)) return;
	}
	for (int j = 3; j <= 13; j += 2)
	{
		if (Move(2, j)) return;
		else if (Move(7, j)) return;
	}
}







