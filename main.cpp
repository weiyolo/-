#include <windows.h>
#include "startgame.h"
#include "cho.h"
 

int main(){
	system("mode con cols=110 lines=28");
	system("color 0F");
    startgame();
    cho();
    gaming();
    
	return 0;
} 