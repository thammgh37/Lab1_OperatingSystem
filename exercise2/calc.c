#include "implement.h"

int main(){
    while (1){
        char name[256];
        printf(">> ");
        fgets(name, sizeof(name), stdin);
        name[strlen(name)-1] = '\0';

        if ( strcmp(name,exitstr) != 0 ){
            excuteInput(name);
            if (checkValid() == 0){
                printf("Syntax error");
            }
            else {
                calc(num1,num2,op);
            }
        }
        else{
            break;
        }
        pressAnyKeyToContinue();
        printf("\n");
    }
}