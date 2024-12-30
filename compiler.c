  static void
  factor(void)
  {
     switch (type) {
     case TOK_IDENT:
     case TOK_NUMBER:
       next();
       break;
     case TOK_LPAREN:
       expect(TOK_LPAREN);
       expression();
       expect(TOK_RPAREN);
     }
   }
