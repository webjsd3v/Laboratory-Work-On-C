#include "lab5.h"
extern char sz_menu[];

const char * sz_help5[] = {
    " �����������(����������� ������) ",
    "'1' ������������ ����",
    "'h' ��� 'H'. �������� ��� �������",
    "'E' ��� 'e'. ����� �� ���������"
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
        printf("������� ����� ��������� ( ����� ����� - ������� quit) ");
        // ������ ����� �� ������������
        getInput(in);
        if (strncmp(in, "quit", 4) == 0) break;

        // ��������� �������
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
            if (b == 0) { printf("���������� ��������� �� 0, �������� ...\n"); exit(1); }
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
    // �������� ����� ������� � p, ��������� ��� � l,
    //������, ��� �� �������������.
    int i = 0;

    // ������� �������� ������ ������������
    if (isMDGRoup(p)) {
        while(1) {
            if (*p == '*' || *p == '/') break;
            l[i++] = *p++;
        }
        return i;
    }

    // ������� ��������� � ������� �������
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

    // ������� - ��� �����
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
    // �������� ����� ������� � p, ��������� ��� � l,
    //������ ������, ��� �� �������������.
    while(*p && (isDigit(*p) || isOperator(*p) ||
                 isLeftParantheses(*p) || isRightParantheses(*p))) {
        *l++ = *p++;
    }
    *l = '\0';

    return 0;
}

int isEmpty(char * p) {
    // ���������, �� �������� �� ������ / char ������
    if (len(p) == 0) return 1;
    else return 0;
}

int calcExpression(char * p) {

    // ���� p - �����
    if (isNumber(p)) return atoi(p);

    // �������� �����, ������ � ������ �� p.
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
        strcpy(sz_menu,"����#���5>");
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
                fprintf(stdout,"����� �� ���5!\n");
                is_exit = 1;
                break;
            }
            default :{
                fprintf(stdout,"������� h ��� ����������� ���������\n");
            }
        }
        if(is_exit) break;
    }
}
