// external libs
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include<string.h>
// internal files
#include"str.c"
#include"lexer.c"
#include"parser.c"
#include"walker.c"
// program entry
int main(int argc, char *argv[]){
	FILE *fptr = fopen(argv[1], "r");
	struct lexer_state lex;
	lex.fptr = fptr;
	struct astnode node = parser(&lex);
	print_ast(node, 0);
	int result = walk(node);
	printf("result: %d\n", result);
	return 0;
}
