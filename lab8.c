#include "lab8.h"
extern char sz_menu[];

int is_logging = 0; char sz_logfile[1024] = {0};

struct node
{
  int data;
  struct node * left;
  struct node * right;
};

const char * sz_help8[] = {
    "������ � �������",
    "'1' ������������ ����",
    "'h' ��� 'H'. �������� ��� �������",
    "'E' ��� 'e'. ����� �� ���������"
};

struct tree
{
  struct node * root;	// ��������� �� ������ ������
  int count;			// ���������� ����� � ������
};

struct tree * tree_create(void){ // ������� ��� �������� ������
    struct tree * new_tree = malloc(sizeof * new_tree);
	if (new_tree == NULL) return NULL;
	new_tree->root = NULL;
	new_tree->count = 0;
	return new_tree;
}




/*
������� ������ ������������� ���� � ������
 ������ 1 � ������, ���� ������� �������� ����� �������,
 ��� 0, ���� ��������� �������� � ������ �����������.
*/
int bin_search(const struct tree * search_tree, int item){ // ������� ��� ������ ���� � ������
  const struct node * search_node;
  search_node = search_tree->root;
	for(;;)
	{
		if (search_node == NULL) return 0;
		else if (item == search_node->data) return 1;
		else if (item > search_node->data) search_node = search_node->right;
		else search_node = search_node->left;
	}
}


int insert(struct tree * search_tree, int item) // ������� ��� ������� ���� � �������� ��������� ������
{
	struct node * search_node, **new;

	new = &search_tree->root;
	search_node = search_tree->root;

	for(;;)
	{
		if(search_node == NULL) // ���� ������� ����� ������
		{
			search_node = *new = malloc(sizeof * search_node); // �������� ������ ��� ����� ����
			if(search_node != NULL) // ���� ������ ������� ����������
			{
				search_node->data = item; // ��������� � ������ ��������
				search_node->left = search_node->right=NULL; // �������� ��������� ��� ������ � ������� �������
				search_tree->count++; // �������� ��������� ��� ������ � ������� �������
				return 1;
			}
			else return 0;
		}
		else if(item == search_node->data) return 2; // ���� ����� ������� ����������
        else if(item > search_node->data) // ��������� �� ������ (����� , ������ )
        {
            new = &search_node->right;
			search_node = search_node->right;
		}
		else
		{
			new = &search_node->left;
			search_node = search_node->left;
		}
	}
}

//������� ��� �������� ���������� ���� ������ � ��� ��������
static void destroy_(struct node * search_node)
{
	if(search_node == NULL) return;
	destroy_(search_node->left);
	destroy_(search_node->right);
	free(search_node);
}

void destroy(struct tree * search_tree) //������� ��� ������� �������� ������
{
	destroy_(search_tree->root);
	free(search_tree);
}

int sz_help_data8 = sizeof(sz_help8) / sizeof(char *);

void traverse(const struct tree * search_tree)
{
    FILE *f_logging = fopen(sz_logfile,"w+");
	if(is_logging){

        if(f_logging == NULL){
            puts("������ ��� �������� �����\n");
            exit(1);
        }


	}
	struct node * stack[64] = {0};
	int count = 0;
	struct node * search_node = search_tree->root;
    int total = 0;

	for(;;)
	{
		while(search_node != NULL)
		{
			stack[count++] = search_node;
			total++;
			search_node = search_node->left;
		}
		stack[count] = '\0';

		if(count == 0) break ;
		search_node = stack[--count];
		if(search_node->data != 0){
            if(is_logging) fprintf(f_logging,"[%i],",search_node->data);
            printf("(%i),",search_node->data);
		}
		search_node = search_node->right;
	}


	fclose(f_logging);
}

void lab8_help(){
    int i = 0;
    for(;i < sz_help_data8;i++){
        printf("*** %s ***\n",sz_help8[i]);
    }
}

void ins(char * msg,struct tree * new_tree){
	int i_high[99][1] = {0}; // 99 - max high , 0 - left , 1 - right
	int level = 0;
	while(*msg){
		if(*msg == '('){
			level++; // spustilicb na urovenb nije
		}else if(*msg == ')'){
			i_high[level][0] = 0;
			level--;
		}else if(*msg == ','){
			i_high[level][0] = 1;
			//printf("Go to right level[%i] \n",level);
		}else{
			char a_num[10] = {0};int i_cn = 0;
			if(i_high[level][0] == 0){
				while((*msg) && ( (*msg != '(') && (*msg != ')') && (*msg != ',')) ){
					if(isdigit(*msg) || (*msg == '-') ){
						a_num[i_cn] = *msg;
						i_cn++;
						//printf("Left add level[%i][%c] \n",level,*msg );
					}
					msg++;
				}
				a_num[i_cn] = '\0';
				insert(new_tree,atoi(a_num));
				//printf("Left add level[%i][%i] \n",level,atoi(a_num) );
				msg--;
			}else{
				while((*msg) && ( (*msg != '(') && (*msg != ')') && (*msg != ',')) ){
					if(isdigit(*msg) || (*msg == '-')){
						a_num[i_cn] = *msg;
						i_cn++;
						//printf("Right add level[%i][%c] \n",level,*msg );
					}
					msg++;
				}
				a_num[i_cn] = '\0';
				insert(new_tree,atoi(a_num));
				//printf("Right add level[%i][%i] \n",level,atoi(a_num) );
				msg--;

			}

		}
		msg++;
	}
}

void lab8_handle(char * t_input,char * t_output){

    if(t_output != NULL){
        is_logging = 1;
        strcpy(sz_logfile,t_output);
    }

    struct tree * new_tree = tree_create(); // ������� ����� ������
    // test
    char sz_store[99][99] = {0}; int i_store = 0;char store[1024];
    // ���� ���� ����

    if(t_input != NULL){
       FILE* ff_input = fopen(t_input, "r");
        while (fgets(store, sizeof(store), ff_input)) {
            printf("%s", store);
        }
        fclose(ff_input);
    }else{

        printf("������� ���������->");
        fflush(stdin);
        scanf("%98[^\n]s",store);
        fflush(stdin);
    }
    char * str = store;
	strcpy(sz_store[i_store],store);
	char a_num[10] = {0};int i_cn = 0;
	while((*str) && ( (*str != '(') && (*str != ')') && (*str != ',')) ){
		if(isdigit(*str) || (*str == '-')){
			a_num[i_cn] = *str;
			i_cn++;
		}
		str++;
	}
	a_num[i_cn] = '\0';
	insert(new_tree,atoi(a_num));
	printf("\n ������ ������ ������ �������![%i] \n",atoi(a_num) );
	ins(str,new_tree);

    // end test

    traverse(new_tree); // ������� ��� ������ � ������

    puts("\n");
    destroy(new_tree); // ������� ������

}

void lab8(){
    int ch = 0,is_exit = 0;
    while(1){
        strcpy(sz_menu,"����#���8>");
        fprintf(stdout,sz_menu);
        fflush(stdin);
        switch(ch = getchar()){
            case '1' : {
                lab8_handle(NULL,NULL);
                break;
            }
            case 'H' :
            case 'h' : {
                lab8_help();
                break;
            }
            case 'e' :
            case 'E' :{
                fprintf(stdout,"����� �� ���8!\n");
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
