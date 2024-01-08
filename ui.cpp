#include<windows.h>

#include "ui.h"

#define upspace 3
#define leftspace 4

using namespace std;

void ui::go(int x, int y)
{
    COORD coord; // 宣告COORD結構體，這是Windows API中表示控制台光標位置的結構體
    coord.X = (x + leftspace) * 2; // 設定光標的橫坐標，*2是因為一個字符在控制台中佔據兩個橫向位置
    coord.Y = y + upspace; // 設定光標的縱坐標
    HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE); // 取得標準輸出的處理器，即控制台窗口的處理器
    SetConsoleCursorPosition(a, coord); // 設定控制台光標位置為指定的(coord.X, coord.Y)
}

void ui::color(int a){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void ui::printmap()
{
    go(0,15);
    for(int i=0;i<24;i++)//20
    {
        for(int j=0;j<15;j++)
        {
            go(i,j);
            if(i==0||i==23||j==0||j==14)
            {
                printf("■");
            }
            else
            {
                printf("  ");
            }
        }
    }
}


bool ui::goout(int x,int y)
{
	if(x<1||x>22||y<1||y>13)return 1;//18
	return 0;
}