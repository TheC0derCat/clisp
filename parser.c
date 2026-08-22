struct astnode{
	struct token tok;
	struct astnode *branchs;
	int branch_count;
};
struct astnode parser(struct lexer_state *lex){
	struct astnode node;
	node.tok = next_token(lex);
	node.branchs = NULL;
	node.branch_count = 0;
	if(node.tok.type == OPENING_PAREN){
		node.tok = next_token(lex);
		node.branchs = malloc(1 * sizeof(struct astnode));
		for(node.branch_count = 0; true; node.branch_count++){
			node.branchs = realloc(node.branchs, (node.branch_count+1) * sizeof(struct astnode));
			node.branchs[node.branch_count] = parser(lex);
			if(node.branchs[node.branch_count].tok.type == CLOSING_PAREN)
				break;
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
