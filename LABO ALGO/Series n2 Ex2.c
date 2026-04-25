/*

Exercise 2
Write a C program that counts the digits of a given number using recursion. The program should prompt
the user to input a number and then recursively count the number of digits. Finally, the program should
display the count of digits.

*/

#include <stdio.h>


int ex2(int number){
    if (number == 0) return 0;
    return 1 + ex2(number/10);
}

int main(){
    printf("%d",ex2(123456789));
    return 0;
}
