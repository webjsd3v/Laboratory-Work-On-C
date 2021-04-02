#include "lab3.h"

#define CASE_1 "Вычислить факториал (рекурсия) по номеру"
#define CASE_2 "Вычислить число в факториал (рекурсия)"
#define CASE_3 "Вычислить все числа в факториале (рекурсия)"
#define CASE_4 "Вычислить факториал (без рекурсии) по номеру"
#define CASE_5 "Вычислить число в факториал (без рекурсии)"
long factorlial(long n){
	if(n >= 1){
		return n*factorlial(n-1);
	}else{
		return 1;
	}
}
float factorlial_float(float n){
	if(n >= 1){
		return n*factorlial_float(n-1);
	}else{
		return 1;
	}
}
float num_to_fac_float(float n){
	if(n < 1){
		return 1;
	}
	for(float n2 = 2.0; n2 < 1000.0	; n2+=0.000001){
		if(factorlial_float(n2) >= n){
			return n2;
		}
	}
	return 0;
}
long num_to_fac(long n,long n2){
	if(n < 1){
		return 1;
	}else if(factorlial(n2) == n){
		return n2;
	}else{
		return num_to_fac(n,n2+=1);
	}
}
// без рекурсии
long factorlial_non(long n){
	if(n >= 1){
		int i,res = 1;
		for(i = 1;i < n+1; i++){
			res *= i;
		}
		return res;
	}else{
		return 1;
	}
}
int num_to_fac_non(int n){
	for(int n2 = 1; n2 < 1000	; n2++){
		if(factorlial_non(n2) == n){
			return n2;
		}
	}
	return 0;
}

extern char sz_menu[];

const char * sz_help3[] = {
    " Нахождение факториала",
    "'1' Нахождение факториала рекурсивным методом",
    "'2' Нахождение факториала не рекурсивным методом",
    "'h' или 'H'. Показать эту справку",
    "'E' или 'e'. Выход из программы"
};
int sz_help_data3 = sizeof(sz_help3) / sizeof(char *);

void lab3_help(){
    int i = 0;
    for(;i < sz_help_data3;i++){
        printf("*** %s ***\n",sz_help3[i]);
    }
}
void lab3_handle(){
    int i_lab3_handle_e = 0;
			printf("=================*Вычисление Факториала*===================\n");
			printf("1.%s.\n",CASE_1);
			printf("2.%s.\n",CASE_2);
			printf("3.%s.\n",CASE_3);
			printf("4.%s.\n",CASE_4);
			printf("5.%s.\n",CASE_5);
            printf("e или E . Выход в предыдущее меню \n");

		int t = 1;
		while (t == 1){

            fflush(stdin);char std_c = getchar();fflush(stdin);
            switch(std_c){

                case '1': {
                            long i[1];
                            printf("%s : \n",CASE_1);
                            scanf("%li",&i[0]);
                            fflush(stdin);
                            printf("Результаты : %li = %li\n",i[0],factorlial(i[0]));
                            break;
                        }
                case '2': {
                            long i[1];
                            printf(" %s: \n",CASE_2);
                            scanf("%li",&i[0]);
                            fflush(stdin);
                            printf("Результаты : %li = %li\n",i[0],num_to_fac(i[0],1));
                            break ;
                        }
                case '3': {
                            float i[1];
                            printf("%s : \n",CASE_3);
                            scanf("%f",&i[0]);
                            fflush(stdin);
                            printf("Результаты : %f = %f\n",i[0],num_to_fac_float(i[0]));
                        }
                case '4' :{
                            long i[1];
                            printf("%s : \n",CASE_4);
                            scanf("%li",&i[0]);
                            fflush(stdin);
                            printf("Результаты : %li = %li\n",i[0],factorlial_non(i[0]));
                            break;
                }
                case '5' :{
                            long i[1];
                            printf("%s : \n",CASE_5);
                            scanf("%li",&i[0]);
                            fflush(stdin);
                            printf("Результаты : %li = %i\n", i[0], num_to_fac_non(i[0]) );
                            break;
                }
                case 'E' :
                case 'e' :{
                            i_lab3_handle_e = 1;
                            break;
                }
                default:{
                    puts("Неправильный ввод , попробуй еще раз");
                }

            }
            if(i_lab3_handle_e) break;

        }
}
void lab3(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"Меню#Лаб3>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab3_handle();
                break;
            }
            case 'H' :
            case 'h' : {
                lab3_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"Выход из Лаб3!\n");
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
