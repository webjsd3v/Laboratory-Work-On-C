#include "lab1.h"
extern char sz_menu[];

const char * sz_help1[] = {
    "Математическое выражение (a^f/2+b-(f/a)+f*a^2-(a^2+b^2)",
    "'1' Пользователь вводит по порядку a, b и f и по формуле получает результат",
    "'h' или 'H'. Показать эту справку",
    "'E' или 'e'. Выход из программы"
};
int sz_help_data1 = sizeof(sz_help1) / sizeof(char *);

void lab1_help(){
    int i = 0;
    for(;i < sz_help_data1;i++){
        printf("*** %s ***\n",sz_help1[i]);
    }
}

void lab1_math(){
    double a = 0, b = 0, f = 0;
    float i_result = 0.0;
    fprintf(stdout,"Введите цифры а,b и f \n>");
    scanf("%lf %lf %lf",&a,&b,&f);
    fprintf(stdout,"a = %f, b = %f, f = %f\n",a,b,f);
    i_result = ( ( a*(f/2) + b - (f/a) ) + f*pow(a,2.0) - (pow(a,2.0) + pow(b,2.0)) );
    fprintf(stdout,"Вычисляем по формуле (a^f/2+b-(f/a)+f*a^2-(a^2+b^2) = %f \n",(float)i_result);

}
void lab1(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"Меню#Лаб1>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab1_math();
                break;
            }
            case 'H' :
            case 'h' : {
                lab1_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"Выход из Лаб1!\n");
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
