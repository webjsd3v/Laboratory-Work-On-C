#ifndef _LAB5_H
    #define _LAB5_h
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    void lab5();
    void lab5_help();
    void lab5_handle();
    void getInput(char * in);
    int isLeftParantheses(char p);
    int isRightParantheses(char p);
    int isOperator(char p);
    int performOperator(int a, int b, char p) ;
    char isDigit(char p);
    int charToDigit(char p);
    int isNumber(char * p);
    int len(char * p);
    int numOfOperands(char * p);
    int isMDGRoup(char * p);
    int getLeftOperand(char * p, char * l);
    int getOperator(char * p, int index, char * op) ;
    int getRightOperand(char * p, char * l);
    int isEmpty(char * p);
    int calcExpression(char * p);
#endif // _LAB5_H
