%{ 
    #include <stdlib.h> 
    void yyerror(char *); 
    #include "y.tab.h" 
%} 
 
%% 
  
    /* integers que acepta G2*/ 
0 {yylval = 0; return ZERO;}
1 {yylval = 1; return UNO;}
2 {yylval = 2; return DOS;}
3 {yylval = 3; return TRES;}
[\n] {return Fin;}

    /* operators, parentesis miedo */ 
[()\[\]] { return *yytext; } 
 

    /* anything else is an error */ 
.  {return Rechazo;}

%% 
int yywrap(void) { 
    return 1; 

}