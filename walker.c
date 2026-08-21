int walk(struct astnode node){
	switch(node.tok.category){
		case OPERATOR:
			int value = 0;
			switch(node.tok.type){
				case NUM: return node.tok.data.num;
				case ADD: return walk(node.branchs[0]) + walk(node.branchs[1]);
				case SUB: return walk(node.branchs[0]) - walk(node.branchs[1]);
				case MUL: return walk(node.branchs[0]) * walk(node.branchs[1]);
				case DIV: return walk(node.branchs[0]) / walk(node.branchs[1]);
			}
			return value;
			break;
		case LITTERAL:
			break;
	}
	switch(node.tok.type){
		case NUM: return node.tok.data.num;
		case ADD: return walk(node.branchs[0]) + walk(node.branchs[1]);
		case SUB: return walk(node.branchs[0]) - walk(node.branchs[1]);
		case MUL: return walk(node.branchs[0]) * walk(node.branchs[1]);
		case DIV: return walk(node.branchs[0]) / walk(node.branchs[1]);
		/*case ADD: return walk(*node.branch1) + walk(*node.branch2);
		case SUB: return walk(*node.branch1) - walk(*node.branch2);
		case MUL: return walk(*node.branch1) * walk(*node.branch2);
		case DIV: return walk(*node.branch1) / walk(*node.branch2);
		case MOD: return walk(*node.branch1) % walk(*node.branch2);*/
		default: puts("unexpected node");
	}
}
