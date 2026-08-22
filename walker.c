struct token walk(struct astnode node){
	struct token tok;
	int value = 0;
	switch(node.tok.type){
		case NUM: value = node.tok.data.num; break;
		case ADD:
			  for(int i = 0; i < node.branch_count; i++){
				  value += walk(node.branchs[i]).data.num; 
			  }
			  tok.type = NUM;
			  break;
		case SUB:
			  value = walk(node.branchs[0]).data.num; 
			  for(int i = 1; i < node.branch_count; i++){
				  value -= walk(node.branchs[i]).data.num; 
			  }
			  tok.type = NUM;
			  break;
		case MUL:
			  value = walk(node.branchs[0]).data.num; 
			  for(int i = 1; i < node.branch_count; i++){
				  value *= walk(node.branchs[i]).data.num; 
			  }
			  tok.type = NUM;
			  break;
		case DIV:
			  value = walk(node.branchs[0]).data.num; 
			  for(int i = 1; i < node.branch_count; i++){
				  int thing = walk(node.branchs[i]).data.num; 
				  if(thing == 0){
					  fprintf(stderr, "you cant divide by zero you silly goober\n");
					  exit(1);
				  }
				  value /= thing; 
			  }
			  tok.type = NUM;
			  break;
		case AND:
			  value = walk(node.branchs[0]).data.num; 
			  for(int i = 1; i < node.branch_count; i++){
				  value = value && walk(node.branchs[i]).data.num; 
			  }
			  tok.type = NUM;
			  break;
		case OR:
			  for(int i = 0; i < node.branch_count; i++){
				  value = value || walk(node.branchs[i]).data.num; 
			  }
			  tok.type = NUM;
			  break;
		case NOT:
			  value = !(walk(node.branchs[0]).data.num);
			  tok.type = NUM;
			  break;
		default: puts("unexpected node");
	}
	tok.data.num = value;
	return tok;
}
