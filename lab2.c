#include "lab2.h"
extern char sz_menu[];

const char * sz_help2[] = {
    " ������� ����� �� ������� . ����� ������ ������ ����� ",
    "'1' ������������ ����",
    "'h' ��� 'H'. �������� ��� �������",
    "'E' ��� 'e'. ����� �� ���������"
};
int sz_help_data2 = sizeof(sz_help2) / sizeof(char *);

void lab2_help(){
    int i = 0;
    for(;i < sz_help_data2;i++){
        printf("*** %s ***\n",sz_help2[i]);
    }
}
void lab2_handle(){
	printf("������� ����� �� ������� \n ������� �����. ����� � ����� E ��� �\n->");
	int c = 0;
	c = getchar();int i = 0;
	while( c != EOF){
		if ( (c != '\n') && (isdigit(c)) ){
			printf("����� : %i ����� = %c \n",++i,c);
		}
		c = getchar();
		if( (c == 'e') || (c == 'E') ) break;
	}
}
void lab2(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"����#���2>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab2_handle();
                break;
            }
            case 'H' :
            case 'h' : {
                lab2_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"����� �� ���2!\n");
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
