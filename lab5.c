#include "lab5.h"
extern char sz_menu[];

const char * sz_help5[] = {
    " Калькулятор(расстановка скобок) ",
    "'1' Активировать ввод",
    "'h' или 'H'. Показать эту справку",
    "'E' или 'e'. Выход из программы"
};
int sz_help_data5 = sizeof(sz_help5) / sizeof(char *);

void lab5_help(){
    int i = 0;
    for(;i < sz_help_data5;i++){
        printf("*** %s ***\n",sz_help5[i]);
    }
}
void lab5_handle(){
    char in[256];
    while(1) {
        fflush(stdin);
        printf("Введите новое выражение ( Чтобы выйти - введите quit) ");
        // Чтение ввода от пользователя
        getInput(in);
        if (strncmp(in, "quit", 4) == 0) break;

        // Выполнять расчеты
        int result = calcExpression(in);
        printf("%d\n", result);
    }
}
void getInput(char * in) {
    printf("> ");
    fgets(in, 256, stdin);
}

int isLeftParantheses(char p) {
    if (p == '(') return 1;
    else return 0;
}

int isRightParantheses(char p) {
    if (p == ')') return 1;
    else return 0;
}

int isOperator(char p) {
    if (p == '+' || p == '-' || p == '*' || p == '/') return p;
    else return 0;
}

int performOperator(int a, int b, char p) {
    switch(p) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/':
            if (b == 0) { printf("Невозможно разделить на 0, прервать ...\n"); exit(1); }
            return a/b;
    }
    return 0;
}


char isDigit(char p) {
    if (p >= '0' && p <= '9') return 1;
    else return 0;
}

int charToDigit(char p) {
    if (p >= '0' && p <= '9') return p - '0';
    else return 0;
}

int isNumber(char * p) {
    while(*p) {
        if (!isDigit(*p)) return 0;
        p++;
    }
    return 1;
}

int len(char * p) {
    return strlen(p);
}

int numOfOperands(char * p) {
    int total = 0;
    while(*p) {
        if (isOperator(*p)) total++;
        p++;
    }
    return total+1;
}

int isMDGRoup(char * p) {

    while(*p) {
        if (!isDigit(*p) && *p != '/' && *p != '*')
            return 0;
        p++;
    }
    return 1;
}

int getLeftOperand(char * p, char * l) {
    // Возьмите левый операнд в p, поместите его в l,
    //вернет, где он заканчивается.
    int i = 0;

    // Операнд является частью мультигруппы
    if (isMDGRoup(p)) {
        while(1) {
            if (*p == '*' || *p == '/') break;
            l[i++] = *p++;
        }
        return i;
    }

    // Операнд находится в круглых скобках
    if(isLeftParantheses(*p)) {
        int LeftParantheses = 1;
        int RightParantheses= 0;
        p++;
        while(1) {
            if (isLeftParantheses(*p))  LeftParantheses++;
            if (isRightParantheses(*p)) RightParantheses++;

            if (isRightParantheses(*p) && LeftParantheses == RightParantheses)
                break;
            l[i++] = *p++;
        }
        l[i] = '\0';
        return i+2;
    }

    // Операнд - это число
    while (1) {
        if (!isDigit(*p)) break;
        l[i++] = *p++;
    }
    l[i] = '\0';
    return i;
}

int getOperator(char * p, int index, char * op) {
    *op = p[index];
    return index + 1;
}

int getRightOperand(char * p, char * l) {
    // Возьмите левый операнд в p, поместите его в l,
    //вернет индекс, где он заканчивается.
    while(*p && (isDigit(*p) || isOperator(*p) ||
                 isLeftParantheses(*p) || isRightParantheses(*p))) {
        *l++ = *p++;
    }
    *l = '\0';

    return 0;
}

int isEmpty(char * p) {
    // Проверьте, не является ли строка / char пустой
    if (len(p) == 0) return 1;
    else return 0;
}

int calcExpression(char * p) {

    // Если p - число
    if (isNumber(p)) return atoi(p);

    // Получить влево, вправо и вправо от p.
    char leftOperand[256] = ""; char rightOperand[256]= "";
    char op;

    int leftOpIndex   = getLeftOperand(p, leftOperand);
    int operatorIndex = getOperator(p, leftOpIndex, &op);
    int rightOpIndex  = getRightOperand(p+operatorIndex, rightOperand);
    printf("rightOpIndex : %i\n",rightOpIndex);
    printf("%s, %c, %s", leftOperand, op, rightOperand);
    getchar();

    if (isEmpty(rightOperand)) return calcExpression(leftOperand);

    return performOperator(
        calcExpression(leftOperand),
        calcExpression(rightOperand),
        op
    );
}
void lab5(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"Меню#Лаб5>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab5_handle();
                break;
            }
            case 'H' :
            case 'h' : {
                lab5_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"Выход из Лаб5!\n");
                is_exit = 1;
                break;
            }
            default :{
                fprintf(stdout,"Введите h для отображения подсказки\n");
            }
        }
        if(is_exit) break;
    }
}
