%{ 
    void yyerror(char *); 
    int yylex(void); 
    int sym[26]; 
%} 

%token ZERO UNO DOS TRES Fin

%% 

eval: 
    C Fin {printf("Hola!\n "); return 0;}
    ;

C:  C C
    |'[' C ']'                
    | '['']'                  
    | '('')'    
    | '(' C ')' 
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
    return 0; 
} 
 
int main(void) { 
    yyparse(); 
    return 0; 
}