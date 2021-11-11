%{ 
    #include <stdio.h>

    int yyerror(char *); 
    int yylex(void); 
%} 

%token ZERO UNO DOS TRES Fin Rechazo

%% 

eval: 
    C Fin {printf("Aceptada!\n "); return 0;}
    ;

C:  C C
    |'[' C ']'                   
    |'(' C ')' 
    | A B
    | 
    ;


A:  ZERO A UNO 
    | DOS
    ;

B:  UNO B
    | TRES A
    ;

%% 
int yyerror(char *s) { 
    printf("La expresion es invalida\n"); 
    return 0;
} 
 
int main(void) { 
    yyparse(); 
    return 0; 
}