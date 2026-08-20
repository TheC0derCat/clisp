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
		return tok;
	}
	switch(ch){
		case '(': tok.type = OPENING_PAREN; break;
		case ')': tok.type = CLOSING_PAREN; break;
		case '+': tok.type = ADD; break;
		case '-': tok.type = SUB; break;
		case '*': tok.type = MUL; break;
		case '/': tok.type = DIV; break;
		case EOF: tok.type = FILE_END; break;
		default: tok = next_token(fptr);
	}
	return tok;
}
int main(int argc, char *argv[]){
	FILE *fptr = fopen(argv[1], "r");
	struct token tok = next_token(fptr);
	while(tok.type < FILE_END){
		if(tok.type == NUM)
			printf("%s: %d\n", token_type_strings[tok.type], tok.data.num);
		else
			printf("%s\n", token_type_strings[tok.type]);
		tok = next_token(fptr);
	}
	fclose(fptr);
	return 0;
}
