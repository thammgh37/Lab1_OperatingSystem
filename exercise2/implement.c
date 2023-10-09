#include "implement.h"

const char* exitstr = "EXIT";
const char* ansstr = "ANS";
const char* fileSaveANS = "variable.txt";

char* num1;
char* num2;
char* op;

int checkValid (){

    // Check valid of 2 operands
    char * pattern = "^[-+]?[0-9]+\\.?[0-9]*$";
    regex_t regex;
    int result = regcomp(&regex, pattern,REG_EXTENDED);
    if (result) {
        printf("Regex compilation failed\n");
        return 0;
    }
    int checkNum1 = regexec(&regex, num1, 0, NULL, 0);
    int checkNum2 = regexec(&regex, num2, 0, NULL, 0);
    if (checkNum1 != 0 && strcmp(num1,ansstr) != 0){
        return 0;
    }
    if (checkNum2 != 0 && strcmp(num2,ansstr) != 0){
        return 0;
    }

    // check valid of operator
    if (strlen(op) != 1){
        printf("%s\n",op);
        printf("error2\n");
        return 0;
    }

    if (*op == '+'){
        return 1;
    }
    else if (*op == '-'){
        return 1;
    }
    else if (*op == '*'){
        return 1;
    }
    else if (*op == '/'){
        return 1;
    }
    else if (*op == '%'){
        return 1;
    }
    else {
        return 0;
    }
}
void excuteInput(char* name){
    int count = 0;
    char* token = strtok(name, " ");
    while( token != NULL ) {
        if(count == 0){
            num1 = token;
        }
        else if ( count == 1){
            op = token;
        }
        else if ( count == 2){
            num2 = token;
        }
        token = strtok(NULL, " ");
        count++;
    }
}
void pressAnyKeyToContinue(){
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    system("clear");
}

float readFromFile(const char* filename){
    char buf[100];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    fgets(buf, sizeof(buf), file);
    fclose(file);
    return strtof(buf, NULL);
}
void writeToFile(const char* filename, char* floatstr){
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    strcat(floatstr,"\n");
    fputs(floatstr, file);
    fclose(file);
}
void calc(char* num1, char* num2, char* op){
    float operator1 = strtof( num1,NULL);
    float operator2 = strtof( num2,NULL);
    char floatString[20];
    if (strcmp(num1, ansstr) == 0){
        operator1 = readFromFile(fileSaveANS);
    }
    if (strcmp(num2, ansstr) == 0){
        operator2 = readFromFile(fileSaveANS);
    }
    
    if (*op == '+'){
        printf("%.2f",operator1 + operator2);
        snprintf(floatString, sizeof(floatString), "%.2f", operator1 + operator2);
    }
    else if (*op == '-'){
        printf("%.2f",operator1 - operator2);
        snprintf(floatString, sizeof(floatString), "%.2f", operator1 - operator2);
    }
    else if (*op == '*'){
        printf("%.2f",operator1 * operator2);
        snprintf(floatString, sizeof(floatString), "%.2f", operator1 * operator2);
    }
    else if (*op == '/'){
        if (operator2 == 0){
            printf("MATH ERROR");
            return;
        }
        printf("%.2f",operator1 / operator2);
        snprintf(floatString, sizeof(floatString), "%.2f", operator1 / operator2);
    }
    else if (*op == '%'){
        if (operator2 == 0){
            printf("MATH ERROR");
            return;
        }
        printf("%d",(int)(operator1 / operator2));
        snprintf(floatString, sizeof(floatString), "%d", (int)(operator1 / operator2));
    }
    writeToFile(fileSaveANS,floatString);
}