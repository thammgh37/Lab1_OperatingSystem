#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <termios.h>
#include <unistd.h> 
#include <regex.h>

extern const char* exitstr;
extern const char* ansstr;
extern char* num1;
extern char* num2;
extern char* op;

int checkValid ();
void calc(char* num1, char* num2,char* op);
void excuteInput(char* name);
void pressAnyKeyToContinue();
float readFromFile(const char* filename);
void writeToFile(const char* filename, char* floatstr);