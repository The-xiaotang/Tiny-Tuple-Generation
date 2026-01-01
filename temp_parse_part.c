TreeNode *while_stmt(void) {
  TreeNode *t = newStmtNode(WhileK);
  match(WHILE);
  if (t != NULL)
    t->child[0] = exp();
  match(DO);
  if (t != NULL)
    t->child[1] = stmt_sequence();
  match(ENDDO);
  return t;
}

TreeNode *for_stmt(void) {
  TreeNode *t = newStmtNode(ForK);
  match(FOR);
  match(LPAREN);
  if (t != NULL)
    t->child[0] = for_assign();
  match(SEMI);
  if (t != NULL)
    t->child[1] = exp();
  match(SEMI);
  // Third part is assignment or increment
  if (t != NULL) {
      if (token == INC || token == DEC) {
           // Treat ++x as assignment statement logic?
           // Actually for_assign usually expects ID := ...
           // But here we might have ++ID.
           // Let's call assign_stmt() but verify it handles INC/DEC.
           t->child[2] = assign_stmt();
      } else {
           t->child[2] = for_assign();
      }
  }
  match(RPAREN);
  // match(DO); // User example didn't show DO, but TINY usually has it. "语句序列" implies block.
  // The user said: for(init; cond; inc) stmt-sequence
  // I'll stick to stmt-sequence which consumes until enddo/end/etc.
  // But stmt-sequence doesn't start with DO.
  // I will check if I should use DO or just parse sequence.
  // Existing `stmt_sequence` parses until ENDDO/END/etc.
  // So if I don't have DO/ENDDO, it will be hard to delimit.
  // I will use DO ... ENDDO to be safe and consistent with WHILE.
  // Or maybe `{` `}` if I supported it.
  // The user prompt (II) 1 says `while ... do ... enddo`.
  // (II) 2 says `for(...) stmt-sequence`.
  // I'll add `DO` and `ENDDO` to `for` logic to match `while`.
  match(DO); 
  if (t != NULL)
    t->child[3] = stmt_sequence();
  match(ENDDO);
  return t;
}
