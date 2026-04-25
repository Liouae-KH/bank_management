/*

Exercise 3
Write a C program that recursively finds the first uppercase letter in a given string. The program should
prompt the user to input a string and then recursively search for the first uppercase letter in it. Once found,
the program should display the uppercase letter. If no uppercase letter is found in the string, the program
should display a message indicating so.

*/

#include <stdio.h>

char ex3 (char *str) {
    if (*str >= 'A' && *str <= 'Z') return *str;
    if (*str == '\0') return '0';
    return ex3(str + 1);
}


int main(){
 
    char string[50]= {'\0'};
    printf("input : ");
    scanf("%49s",string);
    printf("output : %c\n",ex3(string));
    return 0;
}
