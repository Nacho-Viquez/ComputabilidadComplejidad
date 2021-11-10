%{ 
    #include <stdio.h>

    void yyerror(char *); 
    int yylex(void); 
%} 

%token ZERO UNO DOS TRES Fin

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
void yyerror(char *s) { 
    printf("La expresion es invalida\n"); 
     
} 
 
int main(void) { 
    yyparse(); 
    return 0; 
}