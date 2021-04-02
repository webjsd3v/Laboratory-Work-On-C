#include "lab7.h"
#define SZ_MAXLEN 1024
#define SZ_MAXNUM 254
#define SZ_MAXSTORE 254

extern char sz_menu[];

const char * sz_help7[] = {
    " Конвертер систем счисления ",
    "'1' Активировать ввод",
    "'h' или 'H'. Показать эту справку",
    "'E' или 'e'. Выход из программы"
};
int sz_help_data7 = sizeof(sz_help7) / sizeof(char *);

void lab7_help(){
    int i = 0;
    for(;i < sz_help_data7;i++){
        printf("*** %s ***\n",sz_help7[i]);
    }
}
int is_allowed(char str ){
	const char is_valid[] =  "0123456789ABCDEF";
	const char * p = is_valid;
	while (*p){
		if(str == *p){
			return 1;
		}
		p++;
	}
	return 0;
}

long any_to_dec(const char * str,int i_num_system){
	int i_result = 0;
	int i_len = strlen(str)-1; // Потому что последняя степень равна нулю
	while(*str){
		if(i_num_system < 11 ){
			if( isdigit(*str) &&  (  (*str-'0') < i_num_system ) ){
				i_result += (*str - '0') * pow(i_num_system,i_len);
			}else{
				printf("Ошибка здесь ->%c %s . Заменено на 0 \n",str[0],str+1);
			}
		}else{

			if(*str > 64){ // to 16 bit system ABCDEF
				if( is_allowed(*str) && (  (*str - '0' - 7) < i_num_system ) ){
					i_result += (*str - '0' - 7 ) * pow(i_num_system,i_len);
				}else{
					printf("Ошибка здесь ->%c %s . Заменено на 0 \n",str[0],str+1);
				}
			}else{
				if( isdigit(*str) &&  (  (*str-'0') < i_num_system ) ){
					i_result += (*str - '0') * pow(i_num_system,i_len);
				}else{
					printf("Ошибка здесь ->%c %s . Заменено на 0 \n",str[0],str+1);
				}
			}

		}

		str++;i_len--;
	}
	return i_result;
}

char * dec_to_any(long num, int i_num_system,char * sz_res){
	int i_quotient = num;
	int temp,i_strlen = 0;

    while(i_quotient!=0){
         temp = i_quotient % i_num_system;

      //преобразовать целое число в символ
      if( temp < 10)
           temp =temp + 48;
      else
         temp = temp + 55;
      *sz_res = temp;
      sz_res++;i_strlen++;
      i_quotient = i_quotient / i_num_system;
  }
  	*sz_res = '\0';
	return strrev(sz_res - i_strlen);
}

int s_compare(char * sz_str,char * ch,char * sz_str2){
	char sz_res[2][1024];char sz_res2[2][1024];
	char * s1 = sz_str;int is_open = 0;char sz_sn1[64] = {0};
	int sz_sn1_counter = 0;char sz_s1[1024] = {0};int i_counter = 0;
	// sz_s1 - это число , в системе счисления sz_sn1
	while(*s1){
		if((*s1 == '(')){
			is_open = 1;s1++;
			continue;
		}
		if((*s1 == ')')){
			is_open = 0;s1++;
			continue;
		}
		if(is_open){
			sz_sn1[sz_sn1_counter] = *s1;
			sz_sn1_counter++;
		}else{
			sz_s1[i_counter] = *s1;
		}
		s1++;i_counter++;
	}
	sz_sn1[sz_sn1_counter] = '\0';
	sz_s1[i_counter] = '\0';
	strcpy(sz_res[0],sz_sn1);
	strcpy(sz_res[1],sz_s1);

	s1 = sz_str2;is_open = 0;char sz_sn2[64] = {0};
	sz_sn1_counter = 0;char sz_s2[1024] = {0};i_counter = 0;
	while(*s1){
		if((*s1 == '(')){
			is_open = 1;s1++;
			continue;
		}
		if((*s1 == ')')){
			is_open = 0;s1++;
			continue;
		}
		if(is_open){
			sz_sn2[sz_sn1_counter] = *s1;
			sz_sn1_counter++;
		}else{
			sz_s2[i_counter] = *s1;
		}
		s1++;i_counter++;
	}
	sz_sn2[sz_sn1_counter] = '\0';
	sz_s2[i_counter] = '\0';
	strcpy(sz_res2[0],sz_sn2);
	strcpy(sz_res2[1],sz_s2);
	/*Проверить результаты*/
	if(strcmp(ch,"<") == 0){
		if( any_to_dec(sz_res[1],atoi(sz_res[0]) ) < any_to_dec(sz_res2[1],atoi(sz_res2[0]))  ){
			printf("сравнение : %s[%s]",sz_res[1],sz_res[0]); printf(" %s ",ch);
			printf("%s[%s] Сравнение правильное! \n",sz_res2[1],sz_res2[0]);
			return 0;
		}else{
			printf("сравнение : %s[%s]",sz_res[1],sz_res[0]); printf(" %s ",ch);
			printf("%s[%s] Сравнение неверно! \n",sz_res2[1],sz_res2[0]);
			return 1;
		}
	}else if(strcmp(ch,">") == 0){
		if( any_to_dec(sz_res[1],atoi(sz_res[0]) ) > any_to_dec(sz_res2[1],atoi(sz_res2[0]))  ){
			printf("сравнение : %s[%s]",sz_res[1],sz_res[0]); printf(" %s ",ch);
			printf("%s[%s] Сравнение правильное! \n",sz_res2[1],sz_res2[0]);
			return 0;
		}else{
			printf("сравнение : %s[%s]",sz_res[1],sz_res[0]); printf(" %s ",ch);
			printf("%s[%s] Сравнение неверно! \n",sz_res2[1],sz_res2[0]);
			return 2;
		}
	}else if(strcmp(ch,"=") == 0){
		if( any_to_dec(sz_res[1],atoi(sz_res[0]) ) == any_to_dec(sz_res2[1],atoi(sz_res2[0]))  ){
			printf("сравнение : %s[%s]",sz_res[1],sz_res[0]); printf(" %s ",ch);
			printf("%s[%s] Сравнение правильное! \n",sz_res2[1],sz_res2[0]);
			return 0;
		}else{
			printf("сравнение : %s[%s]",sz_res[1],sz_res[0]); printf(" %s ",ch);
			printf("%s[%s] Сравнение неверно! \n",sz_res2[1],sz_res2[0]);
			return 3;
		}
	}
	return 0;
}
void lab7_handle(){
	char sz_line[SZ_MAXLEN] = {0};
	int i_numofnum = 0;
	char sz_temp[SZ_MAXLEN] = {0};
	FILE * f_file = fopen( "data.txt" , "r+");
	if(f_file){
	    while (fgets(sz_line, sizeof(sz_line), f_file) != NULL){
	    	printf("Строка : [%s]\n",sz_line);
	    	char sz_store[SZ_MAXSTORE][SZ_MAXLEN] = {0};
			char * s1 = sz_line;int i_s1 = 0;

			while(*s1){
				if( (*s1 != ' ' ) && (*s1 != ';' ) ){

					if(*s1 == '>' || *s1 == '<' || *s1 == '='){
						sz_temp[i_s1] = '\0';
						strcpy(sz_store[i_numofnum],sz_temp);
						i_numofnum++;
						i_s1 = 0;
						sz_temp[i_s1] = *s1;
						i_s1++;
						sz_temp[i_s1] = '\0';
						strcpy(sz_store[i_numofnum],sz_temp);
						i_numofnum++;
						i_s1 = 0;

					}else{
						sz_temp[i_s1] = *s1;
						i_s1++;
					}
				}

				s1++;
			}
			sz_temp[i_s1] = '\0';
			strcpy(sz_store[i_numofnum],sz_temp); // save last variable
			int i1;
			for(i1 = 0;i1 < SZ_MAXSTORE; i1 += 2){
				if(strlen(sz_store[i1+2]) == 0) break;int i_Res = 0;
				if( (i_Res = s_compare(sz_store[i1],sz_store[i1+1],sz_store[i1+2]) ) > 0 ){

					char sz_res[2][1024];
					char * s1 = sz_store[i1];int is_open = 0;char sz_sn1[64] = {0};
					int sz_sn1_counter = 0;char sz_s1[1024] = {0};int i_counter = 0;
					// sz_s1 - eto chislo , v sisteme schisleniya sz_sn1

					while(*s1){
						if((*s1 == '(')){
							is_open = 1;s1++;
							continue;
						}
						if((*s1 == ')')){
							is_open = 0;s1++;
							continue;
						}
						if(is_open){
							sz_sn1[sz_sn1_counter] = *s1;
							sz_sn1_counter++;
						}else{
							sz_s1[i_counter] = *s1;
						}
						s1++;i_counter++;
					}
					sz_sn1[sz_sn1_counter] = '\0';
					sz_s1[i_counter] = '\0';
					strcpy(sz_res[0],sz_sn1);
					strcpy(sz_res[1],sz_s1);

					//get secondary system num
					char * s2 = sz_store[i1+2];is_open = 0;char sz_sn2[64] = {0};
					sz_sn1_counter = 0;
					while(*s2){
						if((*s2 == '(')){
							is_open = 1;s2++;
							continue;
						}
						if((*s2 == ')')){
							is_open = 0;s2++;
							continue;
						}
						if(is_open){
							sz_sn2[sz_sn1_counter] = *s2;
							sz_sn1_counter++;
						}
						s2++;
					}
					sz_sn2[sz_sn1_counter] = '\0';
					char sz_tres[1024] = {0};
					switch(i_Res){
						case 1 : {
							dec_to_any( any_to_dec(sz_res[1],atoi(sz_res[0]))+1,atoi(sz_sn2) , sz_tres );
							break;
						}
						case 2 :{
							dec_to_any( any_to_dec(sz_res[1],atoi(sz_res[0]))-1,atoi(sz_sn2) , sz_tres );
							break;
						}
						case 3 :{
							dec_to_any( any_to_dec(sz_res[1],atoi(sz_res[0])),atoi(sz_sn2) , sz_tres );
							break;
						}
					}


					sprintf(sz_tres,"%s(%i)",sz_tres,atoi(sz_sn2));
					printf("%s\n",sz_tres);
					strcpy(sz_store[i1+2],sz_tres);
				}
			}
			printf("\n [Позиция до: %li",ftell(f_file));
			int ss = 0;
			if(sz_line[strlen(sz_line)-1] != '\n'){
                fseek ( f_file , 1-strlen(sz_line) , 1 );
			}else{
                fseek ( f_file , 0-strlen(sz_line) , 1 );
			}
            printf("\n [Позиция сдвига: %li\n",ftell(f_file));

			for( ; ss < strlen(sz_line) ; ss++ ){
				fputc(' ',f_file);
			}

            fseek ( f_file , -1-ss , 1 );

			printf("strlen : %i . Текущая позиция : %li , Очистка...\n",strlen(sz_line),ftell(f_file));
			system("pause");

			for(i1 = 0;i1 < SZ_MAXSTORE; i1++){
				if(strlen(sz_store[i1]) == 0) break;
				fputs(sz_store[i1],f_file);

			}
			if(sz_line[strlen(sz_line)-1] != '\n'){
                printf("\n not found \n");
				fputs("\n",f_file);
			}else{
                printf("\n not found \n");
			}
			printf("\n [позиция после: %li , %i]\n",ftell(f_file),strlen(sz_line));
			system("pause");
			fseek ( f_file , -1 , 1 );
			printf("[%c]",fgetc(f_file));
		}

	    fclose(f_file);
	}
}
void lab7(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"Меню#Лаб7>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab7_handle();
                break;
            }
            case 'H' :
            case 'h' : {
                lab7_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"Выход из Лаб7!\n");
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
#undef SZ_MAXLEN
#undef SZ_MAXNUM
#undef SZ_MAXSTORE
