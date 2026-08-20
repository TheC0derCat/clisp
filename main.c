#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
struct str_t{
	char * ptr;
	size_t len;
	size_t cap;
	bool is_slice;
};
const char* token_type_strings[] = {"OPENING_PAREN","CLOSING_PAREN","NUM","STR","ADD","SUB","MUL","DIV"};
enum token_type{
	OPENING_PAREN,
	CLOSING_PAREN,
	NUM,
	STR,
	ADD,
	SUB,
	MUL,
	DIV,
	FILE_END
};
union token_data{
	int num;
	struct str_t str; 
};
struct token{
	enum token_type type;
	union token_data data;
	struct str_t origin;
};
struct token next_token(FILE *fptr){
	struct token tok;
	int ch = fgetc(fptr);
	if(isdigit(ch)){
		tok.type = NUM;
		char buf[50];
		int buf_len = 0;
		while(isdigit(ch)){
			buf[buf_len++] = ch;
			ch = fgetc(fptr);
		}
		buf[buf_len++] = '\0';
		tok.data.num = atoi(buf);
		fseek(fptr, -1, SEEK_CUR); // this decrements the file pointer
		return tok;
	}
	switch(ch){
		case '(': tok.type = OPENING_PAREN; break;
		case ')': tok.type = CLOSING_PAREN; break;
		case '+': tok.type = ADD; break;
		case '-': tok.type = SUB; break;
		case '*': tok.type = MUL; break;
		case '/': tok.type = DIV; break;
		case EOF: tok.type = FILE_END; fclose(fptr); break;
		default: tok = next_token(fptr);
	}
	return tok;
}
struct astnode{
	struct token tok;
	struct astnode *branch1;
	struct astnode *branch2;
};
struct astnode parser(FILE *fptr){
	struct astnode node;
	node.tok = next_token(fptr);
	node.branch1 = NULL;
	node.branch2 = NULL;
	if(node.tok.type == OPENING_PAREN){
		node.branch1 = malloc(sizeof(struct astnode));
		node.branch2 = malloc(sizeof(struct astnode));
		*node.branch1 = parser(fptr);
		*node.branch2 = parser(fptr);

	}
	return node;
}
int main(int argc, char *argv[]){
	FILE *fptr = fopen(argv[1], "r");
	struct astnode node = parser(fptr);
	/*struct token tok = next_token(fptr);
	while(tok.type < FILE_END){
		if(tok.type == NUM)
			printf("%s: %d\n", token_type_strings[tok.type], tok.data.num);
		else
			printf("%s\n", token_type_strings[tok.type]);
		tok = next_token(fptr);
	}*/
	return 0;
}
