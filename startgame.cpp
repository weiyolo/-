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
	set.go(12,15);cout<<"�бN��J�k�զ��^���ENG"<<endl; 
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
	set.go(24,8);printf("�}");
	set.go(24,9);printf("�l");
	set.go(24,10);printf("�C");
	set.go(24,11);printf("��");
	set.go(23,10);printf("��");
	
	set.go(26,0);printf("�ާ@��k:                                       "); 
	set.go(26,1);printf("A�BD�䥪�k���ʸ}��  W�BS��W�U���ʸ}��/��ܿﶵ��");
	set.go(26,2);printf("Enter��T�{/�ʶR/�˳�/�����˳�");
	set.go(26,3);printf("Tab�䥴�}�I�]");
	set.go(26,4);printf("�I�]��Backspace���X���~");
	set.go(26,5);printf("Esc��i�H�h�X���󤣬O���ˬɭ�(�԰��ɭ����~)���ɭ�");
	set.go(26,6);printf("����ؿv��/�Ǫ���m�W�i�H�i�J�����ɭ�");
	set.go(26,7);printf(".�Omove���O");
	set.go(26,8);printf("f = ����ө� , w = �Z���ө� , n = ���Ȥ���������");
	set.go(26,9);printf("g = ���~ , 1 = room1 , 2 = room2");
	set.go(26,10);printf("3 = �q�@�ɦa�ϸ��^�� , 4 = ���i�@�ɦa��");
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
			set.go(23,10);printf("��");
			if(plx!=24||ply!=10)
			{
				set.go(plx,ply);
				set.color(240);printf("I");
			}
			
		}
		Sleep(100);
	}
}