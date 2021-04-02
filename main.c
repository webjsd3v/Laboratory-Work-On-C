#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"
#include "lab5.h"
#include "lab6.h"
#include "lab7.h"
#include "lab8.h"

const char * sz_con_help[] = {
    "************************* ? ************************ \n",
    "*                                                  * \n",
    "* ������������  -? --fin -i -fout -f ��� ��������� * \n",
    "* 1.  -i -fin=filename.xxx  | �������� ����        * \n",
    "* 2.  -f -fout=filename.xxx | �������� ����������� * \n",
    "* 3.  -? | �������� ���� �����                     * \n",
    "*                                                  * \n",
    "*********************** ����� ********************** \n"
};


int sz_con_help_max = sizeof(sz_con_help) / sizeof(const char*); // �������� ������ ������ sz_help

char f_input[254] = {0},f_output[254] = {0};

void m_help();
int unitd(int argc,char * argv[]);// ��������� ���������� ���������� ��� ������� ���������
void terminal_help();

char sz_menu[1024] = {0};

const char * sz_help[] = {
    "'1'. ������������ ������ #1",
    "'2'. ������������ ������ #2",
    "'3'. ������������ ������ #3",
    "'4'. ������������ ������ #4",
    "'5'. ������������ ������ #5",
    "'6'. ������������ ������ #6",
    "'7'. ������������ ������ #7",
    "'8'. ������������ ������ #8",
    "'h' ��� 'H'. �������� ��� �������",
    "'E' ��� 'e'. ����� �� ���������"
};

int sz_help_data = sizeof(sz_help) / sizeof(char *);
void m_help(){
    int i = 0;
    for(;i < sz_help_data;i++){
        printf("*** %s ***\n",sz_help[i]);
    }
}

// ��������� ���������� ���������� ��� ������� ���������
int unitd(int argc,char * argv[]){
	const char* short_options = "?fi::";

	const struct option long_options[] = {
		{"help",no_argument,NULL,'?'},
		{"fin",optional_argument,NULL,'i'},
		{"fout",optional_argument,NULL,'f'},
		{NULL,0,NULL,0}
	};

	int rez;
	int option_index;
	while((rez = getopt_long(argc,argv,short_options,long_options,&option_index)) != -1){
        switch(rez){
            case 'f' :{
				if (optarg!=NULL){
                    strcpy(f_output,optarg); // ����������� ���� ��� ������
				}else{
				    strcpy(f_output,"output.txt"); // ����������� ���� ��� ������
				}
				break;
            }
            case 'i' :{
				if (optarg!=NULL){

                    strcpy(f_input,optarg); // ����������� ���� ��� �����
				}else{
				    strcpy(f_input,"input.txt"); // ����������� ���� ��� �����
				}
				break;
            }
            case '?' : default :{
              terminal_help  (); //������� �������
                exit(1);
                break;
            }
        }
        option_index = -1; // ����� ������ ������
	}
	if( (strlen(f_input) != 0) || (strlen(f_output) != 0) ){
        lab8_handle(f_input,f_output);
	}
	return 0;
}

void terminal_help(){ // ����� ������� � ������� ����� �������� -h --help
    int i;
    puts("\n");
    for(i = 0 ; i < sz_con_help_max ;i++) printf("%s",sz_con_help[i]); // ���������� ������
}

int main(int argc,char * argv[])
{
    setlocale(LC_ALL, ".1251");
    system("chcp 1251 >NULL"); // ������������� ��������� ������� ��� WINDOWS NT
    unitd(argc,argv);
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"����>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab1();
                break;
            }
            case '2' : {
                lab2();
                break;
            }
            case '3' : {
                lab3();
                break;
            }
            case '4' : {
                lab4();
                break;
            }
            case '5' : {
                lab5();
                break;
            }
            case '6' : {
                lab6();
                break;
            }
            case '7' : {
                lab7();
                break;
            }
            case '8' : {
                lab8();
                break;
            }
            case 'H' :
            case 'h' : {
                m_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"����!\n");
                is_exit = 1;
                break;
            }
            default :{
                fprintf(stdout,"������� h ��� ����������� ���������\n");
            }
        }
        if(is_exit) break;
    }
    return 0;
}
