#include<windows.h>

#include "ui.h"

#define upspace 3
#define leftspace 4

using namespace std;

void ui::go(int x, int y)
{
    COORD coord; // �ŧiCOORD���c��A�o�OWindows API����ܱ���x���Ц�m�����c��
    coord.X = (x + leftspace) * 2; // �]�w���Ъ���СA*2�O�]���@�Ӧr�Ŧb����x�����ڨ�Ӿ�V��m
    coord.Y = y + upspace; // �]�w���Ъ��a����
    HANDLE a = GetStdHandle(STD_OUTPUT_HANDLE); // ���o�зǿ�X���B�z���A�Y����x���f���B�z��
    SetConsoleCursorPosition(a, coord); // �]�w����x���Ц�m�����w��(coord.X, coord.Y)
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
                printf("��");
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