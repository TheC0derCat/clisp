struct astnode{
	struct token tok;
	struct astnode *branchs;
	int branch_count;
};
struct astnode parser(FILE *fptr){
	struct astnode node;
	node.tok = next_token(fptr);
	node.branchs = NULL;
	node.branch_count = 0;
	if(node.tok.type == OPENING_PAREN){
		node.tok = next_token(fptr);
		node.branchs = malloc(2 * sizeof(struct astnode));
		node.branchs[0] = parser(fptr);
		node.branchs[1] = parser(fptr);
		struct token last = next_token(fptr);
		if(last.type != CLOSING_PAREN){
			printf("enexpected token: ");
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
	if(node.branchs != NULL){
		print_ast(node.branchs[0], indentation + 1);
		print_ast(node.branchs[1], indentation + 1);
	}
}
