const char* token_type_strings[] = {"OPENING_PAREN","CLOSING_PAREN","NUM","STR","ADD","SUB","MUL","DIV","MOD","AND","OR","NOT","FILE_END"};
enum token_type{
	OPENING_PAREN,
	CLOSING_PAREN,
	NUM,
	STR,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	AND,
	OR,
	NOT,
	FILE_END
};
enum token_category{
	OPERATOR,
	LITTERAL,
	OTHER
};
union token_data{
	int num;
	struct str_t str; 
};
struct token{
	enum token_type type;
	enum token_category category;
	union token_data data;
	struct str_t origin;
};
struct lexer_state{
	FILE *fptr;
	int line;
	struct token last;
};
void print_tok(struct token tok){
	if(tok.type == NUM)
		printf("%s%d\n", token_type_strings[tok.type], tok.data.num);
	else
		printf("%s\n", token_type_strings[tok.type]);

}
struct token next_token(struct lexer_state *lex){
	struct token tok;
	int ch = fgetc(lex->fptr);
	if(isdigit(ch)){
		tok.type = NUM;
		char buf[50];
		int buf_len = 0;
		while(isdigit(ch)){
			buf[buf_len++] = ch;
			ch = fgetc(lex->fptr);
		}
		buf[buf_len++] = '\0';
		tok.data.num = atoi(buf);
		tok.category = LITTERAL;
		fseek(lex->fptr, -1, SEEK_CUR); // this decrements the file pointer
		lex->last = tok;
		return tok;
	}
	switch(ch){
		case '(': tok.type = OPENING_PAREN; break;
		case ')': tok.type = CLOSING_PAREN; break;
		case '+': tok.type = ADD; tok.category = OPERATOR; break;
		case '-': tok.type = SUB; tok.category = OPERATOR; break;
		case '*': tok.type = MUL; tok.category = OPERATOR; break;
		case '/': tok.type = DIV; tok.category = OPERATOR; break;
		case '%': tok.type = MOD; tok.category = OPERATOR; break;
		case '&': tok.type = AND; tok.category = OPERATOR; break;
		case '|': tok.type = OR; tok.category = OPERATOR; break;
		case '!': tok.type = NOT; tok.category = OPERATOR; break;
		case EOF: tok.type = FILE_END; fclose(lex->fptr); break;
		default: tok = next_token(lex);
	}
	lex->last = tok;
	return tok;
}
