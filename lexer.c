const char* token_type_strings[] = {"OPENING_PAREN","CLOSING_PAREN","NUM","STR","ADD","SUB","MUL","DIV","MOD","FILE_END"};
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
void print_tok(struct token tok){
	if(tok.type == NUM)
		printf("%s: %d\n", token_type_strings[tok.type], tok.data.num);
	else
		printf("%s\n", token_type_strings[tok.type]);

}
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
		case '%': tok.type = MOD; break;
		case EOF: tok.type = FILE_END; fclose(fptr); break;
		default: tok = next_token(fptr);
	}
	return tok;
}
