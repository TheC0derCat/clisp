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
		node.tok = next_token(fptr);
		node.branch1 = malloc(sizeof(struct astnode));
		node.branch2 = malloc(sizeof(struct astnode));
		*node.branch1 = parser(fptr);
		*node.branch2 = parser(fptr);
		struct token last = next_token(fptr);
		if(last.type != CLOSING_PAREN){
			puts("enexpected token");
			print_tok(last);
			exit(0);
		}
	}
	return node;
}
void print_ast(struct astnode node, int indentation){
	for(int i = 0; i < indentation; i++){
		printf("\t");
	}
	print_tok(node.tok);
	if(node.branch1 != NULL){
		print_ast(*node.branch1, indentation + 1);
		print_ast(*node.branch2, indentation + 1);
	}
}
