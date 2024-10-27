#include "check.h"

//This function takes a character as a parameter and changes it into an integer between the minimum and the maximum
//The minimum must always be >= 0 and the maximum must always be <= 9
int verifyNumber(char c, char min, char max){
    int number=0;
    if(c >= min && c <= max){
        number=c-'0';
    }
    else{
        number=(c+(max-min+1)*100)%(max-min+1)+(min-'0');
        //The +(max-min+1)*100 is to avoid having a negative value of c
    }
    return number;
}

//This function swaps 2 characters
void swap(char *a, char *b){
    char tmp=0;
    tmp=*a;
    *a=*b;
    *b=tmp;
}