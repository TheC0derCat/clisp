int walk(struct astnode node){
	int value = 0;
	switch(node.tok.type){
		case NUM: value = node.tok.data.num; break;
		case ADD: value = walk(node.branchs[0]) + walk(node.branchs[1]); break;
		case SUB: value = walk(node.branchs[0]) - walk(node.branchs[1]); break;
		case MUL: value = walk(node.branchs[0]) * walk(node.branchs[1]); break;
		case DIV: value = walk(node.branchs[0]) / walk(node.branchs[1]); break;
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
