#include "lab4.h"
#define F_CM_MAX_NAME_SZ 20

#define FUNC_1 "������� �������� �������� � �������"
#define FUNC_E "������ � ���������� ����"
#define FUNC_EH "����� ����� � ���������� ���� , ������� �"
#define FUNC_H "��������� - ������� h"
#define FUNC_2 "���� �������"
#define FUNC_D "������������ ���� ... "


extern char sz_menu[];

const char * sz_help4[] = {
    " ���� ������� ������  ",
    "'1' ������������ ����",
    "'h' ��� 'H'. �������� ��� �������",
    "'E' ��� 'e'. ����� �� ���������"
};
int sz_help_data4 = sizeof(sz_help4) / sizeof(char *);

void lab4_help(){
    int i = 0;
    for(;i < sz_help_data4;i++){
        printf("*** %s ***\n",sz_help4[i]);
    }
}
int is_mixed_ctype(char *s){ // ������ ���� <ctype.h>
	int x1 = 0,x2 = 0,x3 =0;
	while(s[x3] != '\0'){
		if(isdigit(s[x3])){
			x1++;
		}else if(s[x3] == '\n' || s[x3] == ' ' || s[x3] == '-'){
			// ������
		}else{
			x2++;
		}
		x3++;
	}
	if( (x1 && x2) || x2){
		return 1;
	}else{
		return 0;
	}
}

int f_calc_massive(){
	int i_print_mixed = 0;
	fflush(stdin);
	char * t_buffer = (char*) malloc(F_CM_MAX_NAME_SZ+1);
	if(t_buffer==NULL) exit (1);
	int * t_buffer_digit = (int*) malloc(sizeof (int) * F_CM_MAX_NAME_SZ+1);
	if(t_buffer_digit==NULL) exit (1);

	// ���� � ��������
	char input_data[F_CM_MAX_NAME_SZ];
	char *temp_data = input_data;
	fgets(temp_data,sizeof input_data,stdin);
	if(*temp_data == '\n'){
		return puts("[������] ��� �����.>");
	}
	printf("�� ������� : %s Len : %i \n ",temp_data,strlen(temp_data));
	int p1 = -1,x_len = 0,x_col = 0;
	if(is_mixed_ctype(temp_data)){
		while(temp_data[++p1] != '\0'){
			t_buffer[p1] = temp_data[p1];
			i_print_mixed = 1;
			x_len++;
		}
	}else{
		while(temp_data[++p1] != '\0'){
			x_len++;
		}
		char * pch = strtok (temp_data," ");

		while (pch != NULL)
		{
			t_buffer_digit[x_col] = atoi(pch);
			x_col++;
			pch = strtok (NULL, " ");
		}
	}
	t_buffer[x_len] = '\0'; // ��������� ������
	t_buffer_digit[x_col] = '\0'; // ��������� ������
	if(i_print_mixed){
		printf("STR ����� : %i \n",strlen(t_buffer));
		printf("[�������] Outline ����� : %s \n",t_buffer);
		printf("������ ��������� � ������ ������ = %i \n ����� ��������� : %i \n",x_len,strlen(t_buffer));
	}else{
		int a1 = -1;
		printf("Outline ����� : %i ",t_buffer_digit[a1]);
		while(t_buffer_digit[++a1] != '\0'){
			printf("%i ",t_buffer_digit[a1]);
		}
		printf("\n");
		printf("������ ��������� � ������ ������ = %i \n ����� ��������� : %i \n",x_len,x_col);
		printf("\n");
	}

	free(t_buffer);free(t_buffer_digit);
	return 0;
}
void lab4_handle(){
	int i_exm = 0;
	int *i_exms = &i_exm;
	while(!*i_exms){
		printf(">");
		fflush(stdin);
		char g_char = getchar();
		char *g_chars = &g_char;
		switch(*g_chars){
			case '1' : {
				printf("������� : %s .\n",FUNC_1);
				f_calc_massive();
				break;
			}

			case 'h' : {
				printf(" 1. %s,\n 2. %s. \n 3. %s. \n ",FUNC_1,FUNC_H,FUNC_EH);
				printf("������� ������ : \n");

				break;
			}
			case 'e' :{
				printf("������� : %s .\n",FUNC_E);
				*i_exms = 1;
				break;
			}
			default : {
				printf("%s",FUNC_D);
			}
		}
	}
}
void lab4(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"����#���4>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab4_handle();
                break;
            }
            case 'H' :
            case 'h' : {
                lab4_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"����� �� ���4!\n");
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
#undef F_CM_MAX_NAME_SZ

#undef FUNC_1
#undef FUNC_E
#undef FUNC_EH
#undef FUNC_H
#undef FUNC_2
#undef FUNC_D
