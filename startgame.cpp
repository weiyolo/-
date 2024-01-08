#include "ui.h"
#include <windows.h>
#include <conio.h>

void startgame()
{
int plx = 20,ply = 10;
ui set;
set.go(10,0);cout <<"    *****       *****       ****     ****   "<<endl;
set.go(10,1);cout <<"    **  **     **  **         ***   ***     "<<endl;
set.go(10,2);cout <<"    **   **  **    **           ** **       "<<endl;
set.go(10,3);cout <<"    **     **      **            ***        "<<endl;
set.go(10,4);cout <<"    **             **            ***        "<<endl; 
set.go(10,5);cout <<"    **             **            ***        "<<endl;
set.go(10,6);cout <<"                                            "<<endl;
set.go(10,7);cout <<"    **   **     *********    ************   "<<endl;
set.go(10,8);cout <<"    ** **       *       *    **             "<<endl;
set.go(10,9);cout <<"    ** *        *********    **             "<<endl;
set.go(10,10);cout<<"    **          **           **     *****   "<<endl;
set.go(10,11);cout<<"    **          **           **         *   "<<endl;
set.go(10,12);cout<<"    **          **           ************   "<<endl;
set.go(10,13);cout<<"                                            "<<endl;
set.go(10,14);cout<<"                                            "<<endl;
	Sleep(1000);
	set.go(12,15);cout<<"請將輸入法調成英文或ENG"<<endl; 
	set.go(12,16);
	Sleep(100);
	system("pause");
	system("cls");
	set.go(0,0);
	set.printmap();
	int key=0;
	set.go(20,10);
	set.color(240);printf("I");
	set.color(15);
	set.go(24,8);printf("開");
	set.go(24,9);printf("始");
	set.go(24,10);printf("遊");
	set.go(24,11);printf("戲");
	set.go(23,10);printf("→");
	
	set.go(26,0);printf("操作方法:                                       "); 
	set.go(26,1);printf("A、D鍵左右移動腳色  W、S鍵上下移動腳色/選擇選項鍵");
	set.go(26,2);printf("Enter鍵確認/購買/裝備/取消裝備");
	set.go(26,3);printf("Tab鍵打開背包");
	set.go(26,4);printf("背包中Backspace鍵賣出物品");
	set.go(26,5);printf("Esc鍵可以退出任何不是村裝界面(戰鬥界面除外)的界面");
	set.go(26,6);printf("走到建築物/怪物位置上可以進入相應界面");
	set.go(26,7);printf(".是move指令");
	set.go(26,8);printf("f = 防具商店 , w = 武器商店 , n = 任務中接取中心");
	set.go(26,9);printf("g = 野外 , 1 = room1 , 2 = room2");
	set.go(26,10);printf("3 = 從世界地圖跳回來 , 4 = 跳進世界地圖");
	while(plx!=24||ply!=10)
	{
		if(kbhit)
		{
			key=getch();
			if((key=='W'||key=='w')&&!set.goout(plx,ply-1))
			{
				set.go(plx,ply);
				set.color(15);printf("  ");
				ply--;
			}
			if((key=='S'||key=='s')&&!set.goout(plx,ply+1))
			{
				set.go(plx,ply);
				set.color(15);printf("  ");
				ply++;
			}
			if((key=='A'||key=='a')&&!set.goout(plx-1,ply))
			{
				set.go(plx,ply);
				set.color(15);printf("  ");
				plx--;
			}	
			if((key=='D'||key=='d'))
			{
				if(!set.goout(plx+1,ply)||ply==10)
				{
					set.go(plx,ply);
					set.color(15);printf("  ");
					plx++;
				}
			}
			set.color(15);
			set.go(23,10);printf("→");
			if(plx!=24||ply!=10)
			{
				set.go(plx,ply);
				set.color(240);printf("I");
			}
			
		}
		Sleep(100);
	}
}