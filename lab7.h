#ifndef _LAB7_H
    #define _LAB7_h
    #include <stdio.h>
    #include <string.h>
    #include <math.h>
    #include <stdlib.h>
    #include <ctype.h>
    void lab7();
    void lab7_help();
    void lab7_handle();
    long any_to_dec(const char * str,int i_num_system); // любая система в десятичную
    char * dec_to_any(long num, int i_num_system,char * sz_res); // с десятичной в любую
    int is_allowed(char str ); // разрешенные символы
    int s_compare(char * sz_str,char * ch,char * sz_str2); // функция сравнение и возврат 1 , если ошибка в меньше , 2 , есди больше , 3 если равно
#endif // _LAB7_H
