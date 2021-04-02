#include "lab6.h"
extern char sz_menu[];

const char * sz_help6[] = {
    " ���������� ������� ������ ",
    "'1' ������������ ����",
    "'h' ��� 'H'. �������� ��� �������",
    "'E' ��� 'e'. ����� �� ���������"
};
int sz_help_data6 = sizeof(sz_help6) / sizeof(char *);

void lab6_help(){
    int i = 0;
    for(;i < sz_help_data6;i++){
        printf("*** %s ***\n",sz_help6[i]);
    }
}

int cmp(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

int cstring_cmp(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
}

void lab6_handle(){
	int i_end = 0; int c;
	puts("h - ������� ������ \n");
	while( 1 ){
		fflush(stdin);
		printf("->");
		switch(c = getchar()){
			case 'q' : {
				i_end = 1;
				break;
			}
			case '1' :{
				fflush(stdin);
			    int n, i;
			    int *a;
			    printf("������� ���������� �����->");
			    scanf("%d", &n);
			    printf("\n������� �������� ->");
			    a = (int*) malloc(sizeof(int)*n);
			    for(i = 0 ; i < n; i++) {
			        scanf("%d", &a[i]);
			    }
			    qsort(a, n, sizeof(int), cmp );
			    puts("���������� � ����� : \n");
			    for(i = 0 ; i < n; i++) {
			        printf("%d \n", a[i]);
			    }
			    puts("\n");
			    free(a);
				break;
			}
			case '2' :{
				fflush(stdin);
				fflush(stdin);
				printf("������� ������->");
				char ** str;
				int len = 1024;
				str = (char **)malloc(sizeof(char *) * len * 5);
				char sz_temp[1024] = {0};
				scanf("%1023[^\n]s",sz_temp);
				int n_temp = 0; char * t_temp;
				t_temp = strtok(sz_temp," ") ;
				while (t_temp != NULL)
				{
				  str[n_temp++] = t_temp;
				  t_temp = strtok (NULL," ");
				}

			    qsort(str, n_temp-1, sizeof(char*), cstring_cmp);
			    int i;
			    for (i=0; str[i] != NULL; i++)
			       printf("\n %s\n", str[i]);

				free(str);
				break;
			}
			case 'h' : {
				puts("������ : \n1. ������� ������ � ���������� INT\n2.������ ����� ������ � ����������\n");
				break;
			}
			default :{

				break;
			}
		}



		if(i_end){
			break;
			puts("\n����� � ���������� ���� ... \n");
		}
	}
}
void lab6(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"����#���6>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab6_handle();
                break;
            }
            case 'H' :
            case 'h' : {
                lab6_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"����� �� ���6!\n");
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
