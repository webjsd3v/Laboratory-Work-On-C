#ifndef _LAB8_H
    #define _LAB8_h
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>

    void lab8();
    void lab8_help();
    void lab8_handle(char * t_input,char * t_output);
    struct tree * tree_create(void); // Функция для создания дерева
    int bin_search(const struct tree * search_tree, int item); // Функция для поиска узла в дереве
    int insert(struct tree * search_tree, int item); // Функция для вставки узла в бинарное поисковое дерево
    void traverse(const struct tree * search_tree); // тестовая пробежка по дереву и сохранение в массив результатов. сохранение в стек 64 результата
    void destroy(struct tree * search_tree);//функция для полного удаления дерева
    void ins(char * msg,struct tree * new_tree); // читаем строку по порядку , заполняя наше дерево
    //static void destroy_(struct node * search_node);
#endif // _LAB8_H
