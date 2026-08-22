int walk(struct astnode node){
	int value = 0;
	switch(node.tok.type){
		case NUM: value = node.tok.data.num; break;
		case ADD:
			  for(int i = 0; i < node.branch_count; i++){
				  value += walk(node.branchs[i]); 
			  }
			  break;
		case SUB:
			  value = walk(node.branchs[0]); 
			  for(int i = 1; i < node.branch_count; i++){
				  value -= walk(node.branchs[i]); 
			  }
			  break;
		case MUL:
			  value = walk(node.branchs[0]); 
			  for(int i = 1; i < node.branch_count; i++){
				  value *= walk(node.branchs[i]); 
			  }
			  break;
		case DIV:
			  value = walk(node.branchs[0]); 
			  for(int i = 1; i < node.branch_count; i++){
				  int thing = walk(node.branchs[i]); 
				  if(thing == 0){
					  puts("you cant divide by zero you silly goober");
					  exit(1);
				  }
				  value /= thing; 
			  }
			  break;
		default: puts("unexpected node");
	}
	return value;
	/*switch(node.tok.type){
		case NUM: return node.tok.data.num;
		case ADD: return walk(node.branchs[0]) + walk(node.branchs[1]);
		case SUB: return walk(node.branchs[0]) - walk(node.branchs[1]);
		case MUL: return walk(node.branchs[0]) * walk(node.branchs[1]);
		case DIV: return walk(node.branchs[0]) / walk(node.branchs[1]);
		default: puts("unexpected node");
	}*/
}
