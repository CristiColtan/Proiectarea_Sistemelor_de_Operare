%{
	using namespace std;

	#include <iostream>
	#include <stdio.h>
	#include <string.h>
	#include <iomanip>

	int yylex();
	int yyerror(const char *msg);

	int intraInIF = 0;
   	int EsteCorecta = 1;
	char msg[500];

	class TVAR
	{
	    char* nume;
    		int intValoare;
    		float floatValoare;
    		double doubleValoare;
    		int tipValoare; 
		//0 pentru int, 1 pentru float, 2 pentru double
    	TVAR* next;
	  
	public:
	    	static TVAR* head;
		static TVAR* tail;
	        TVAR(char* n);
	        TVAR();
	        int exists(char* n);
                void add(char* n, int tip, int intVal= -1,float floatVal= 0.0f, double doubleVal= 0.0);
		int getTipValue(char* n);
		int getIntValue(char *n);
		float getFloatValue(char* n);
		double getDoubleValue(char* n);
	        void setValue(char* n, int v);
		void setValue(char* n, float v);
    	        void setValue(char* n, double v);
		void printVars();
	};

	TVAR* TVAR::head;
	TVAR* TVAR::tail;

	int GetValueBasedOnTypeInt(char* var, int tip, TVAR* ts) {
    switch(tip) {
        case 0:
            return ts->getIntValue(var);
        case 1:
            return ts->getFloatValue(var);
        case 2:
            return ts->getDoubleValue(var);
        default:
            break;
   		}
    return 0;
	}

	float GetValueBasedOnTypeFloat(char* var, int tip, TVAR* ts) {
    switch(tip) {
        case 0:
            return ts->getIntValue(var);
        case 1:
            return ts->getFloatValue(var);
        case 2:
            return ts->getDoubleValue(var);
        default:
            break;
    	}
    return 0.0f;
	}

	double GetValueBasedOnTypeDouble(char* var, int tip, TVAR* ts) {
    switch(tip) {
        case 0:
            return ts->getIntValue(var);
        case 1:
            return ts->getFloatValue(var);
        case 2:
            return ts->getDoubleValue(var);
        default:
            break;
  		}
    return 0.0;
	}

	int OperatieMatematica(char* var1, char* var2, char operand, TVAR* ts) {
    	int tip1 = ts->getTipValue(var1);
   	 	int tip2 = ts->getTipValue(var2);
    	int val1, val2;

    	val1 = GetValueBasedOnTypeInt(var1, tip1, ts);
    	val2 = GetValueBasedOnTypeInt(var2, tip2, ts);

   	 	switch(operand) {
        	case '+':
            	return val1 + val2;
        	case '-':
            	return val1 - val2;
        	case '*':
            	return val1 * val2;
        	case '/':
				if(val2 == 0)
				{
					printf("Eroare impartire 0!");
	   			} 
	  			else 
				{ 
                	return val1 / val2;
				}
        	default:
            break;
    		}
   	 	return 0;
	}

	float OperatieMatematicaFloat(char* var1, char* var2, char operand, TVAR* ts) {
    	int tip1 = ts->getTipValue(var1);
   	 	int tip2 = ts->getTipValue(var2);
    	float val1, val2;

    	val1 = GetValueBasedOnTypeFloat(var1, tip1, ts);
    	val2 = GetValueBasedOnTypeFloat(var2, tip2, ts);

   	 	switch(operand) {
        	case '+':
            	return val1 + val2;
        	case '-':
            	return val1 - val2;
        	case '*':
            	return val1 * val2;
        	case '/':
				if(val2 == 0)
				{
					printf("Eroare impartire 0!");
	   			} 
	  			else 
				{ 
                	return val1 / val2;
				}
        	default:
            break;
    		}
   	 	return 0;
	}

	double OperatieMatematicaDouble(char* var1, char* var2, char operand, TVAR* ts) {
    	int tip1 = ts->getTipValue(var1);
   	 	int tip2 = ts->getTipValue(var2);
    	double val1, val2;

    	val1 = GetValueBasedOnTypeDouble(var1, tip1, ts);
    	val2 = GetValueBasedOnTypeDouble(var2, tip2, ts);

   	 	switch(operand) {
        	case '+':
            	return val1 + val2;
        	case '-':
            	return val1 - val2;
        	case '*':
            	return val1 * val2;
        	case '/':
				if(val2 == 0)
				{
					printf("Eroare impartire 0!");
	   			} 
	  			else 
				{ 
                	return val1 / val2;
				}
        	default:
            break;
    		}
   	 	return 0;
	}

	TVAR::TVAR(char* n){
		this->nume = new char[strlen(n)+1];
		strcpy(this->nume, n);
		this->next = NULL;
	}

	TVAR::TVAR(){
		TVAR::head = NULL;
		TVAR::tail = NULL;
	}

	int TVAR::exists(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL) 
		{ 
			if(strcmp(tmp->nume,n) == 0)
	      		return 1;
        	tmp = tmp->next;
	  	}
	  	return 0;
	}

    void TVAR::add(char* n, int tip, int intVal, float floatVal, double doubleVal){
		TVAR* elem = new TVAR(n);

		switch(tip)
	{
	case 0: //int
        elem->intValoare = intVal;
        elem->tipValoare = 0;
        break;
    case 1: //float
        elem->floatValoare = floatVal;
        elem->tipValoare = 1;
        break;
    case 2: //double
        elem->doubleValoare = doubleVal;
        elem->tipValoare = 2;
        break;
    default:
        break;
		}

		if(head == NULL)
		{ 
			TVAR::head = TVAR::tail = elem;
		}
		else 
		{
			TVAR::tail->next = elem;
			TVAR::tail = elem;
		}
	}

	int TVAR::getTipValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume, n)==0)
				return tmp->tipValoare;
			tmp=tmp->next;
		}
		return -1;
	}

    int TVAR::getIntValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume,n) == 0)
				return tmp->intValoare;
	     	tmp = tmp->next;
	    }
		return -1;
	}

	float TVAR::getFloatValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume,n) == 0)
				return tmp->floatValoare;
	     	tmp = tmp->next;
	    }
		return -1.0f;
	}

	double TVAR::getDoubleValue(char* n){
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			if(strcmp(tmp->nume,n) == 0)
				return tmp->doubleValoare;
	     	tmp = tmp->next;
	    }
		return -1.0;
	}

	void TVAR::setValue(char* n, int v){
		TVAR* tmp = TVAR::head;
	    while(tmp != NULL)
	    {
			if(strcmp(tmp->nume,n) == 0)
			{
				tmp->intValoare = v;
				tmp->tipValoare = 0;
			}
			tmp = tmp->next;
	    }
	}

	void TVAR::setValue(char* n, float v){
		TVAR* tmp = TVAR::head;
	    while(tmp != NULL)
	    {
			if(strcmp(tmp->nume,n) == 0)
			{
				tmp->floatValoare = v;
				tmp->tipValoare = 1;
			}
			tmp = tmp->next;
	    }
	}

	void TVAR::setValue(char* n, double v){
		TVAR* tmp = TVAR::head;
	    while(tmp != NULL)
	    {
			if(strcmp(tmp->nume,n) == 0)
			{
				tmp->doubleValoare = v;
				tmp->tipValoare = 2;
			}
			tmp = tmp->next;
	    }
	}

	void TVAR::printVars(){
		cout<<"\nPrinting table of variables...\n";
		TVAR* tmp = TVAR::head;
		while(tmp != NULL)
		{
			cout<<tmp->nume<<"=";
			if(tmp->tipValoare == 0)
				cout<<tmp->intValoare<<"\n";
			else if(tmp->tipValoare == 1)
				cout<<setprecision(2)<<tmp->floatValoare<<"f\n";
			else if(tmp->tipValoare == 2)
				cout<<setprecision(2)<<tmp->doubleValoare<<"\n";
			tmp = tmp->next;
		}	  
	}

	TVAR* ts = NULL;
%}

%union { char* sir; int val_int; double val_double; float val_float; }

%token TOK_PLUS TOK_MINUS TOK_MULTIPLY TOK_DIVIDE 

%token TOK_LEFT TOK_RIGHT 

%token TOK_PRINT TOK_ERROR

%token TOK_DECLARE_INT TOK_DECLARE_FLOAT TOK_DECLARE_DOUBLE

%token TOK_IF TOK_ELSE TOK_WHILE

%token TOK_GREATER_THAN TOK_LESS_THAN TOK_EQUALS

%token TOK_SCANF TOK_PRINTF TOK_GHILIMEA TOK_MODULO_D TOK_MODULO_F

%token <val_int> 	TOK_INT
%token <val_double> TOK_DOUBLE 
%token <val_float> 	TOK_FLOAT
%token <sir> 		TOK_VARIABLE

%type <val_int> 	EXPRESSION
%type <val_int> 	E
%type <val_double> 	D
%type <val_float> 	F

%start S

%left TOK_PLUS TOK_MINUS
%left TOK_MULTIPLY TOK_DIVIDE
%left TOK_IF TOK_ELSE

%%
S : 
    | I ';' S
	| INPUT_OUTPUT ';' S
	| CONTROL S
    | TOK_ERROR { EsteCorecta = 0; }
    ; 
CONTROL : IF_STATEMENT
        | WHILE_STATEMENT
        ;
IF_STATEMENT : TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT ';' '}' TOK_ELSE '{' S '}'
        {
            if($3 == 1){
				int value = ts->getIntValue($8) + $10;
				ts->setValue($6,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
		}
			| TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}' TOK_ELSE '{' S '}'
			{
				if($3 == 1){
				int value = ts->getIntValue($8) - $10;
				ts->setValue($6,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' S '}' TOK_ELSE '{' S '}' //neharcodat
		{
			if($3 == 1){
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
		}
			| TOK_IF TOK_LEFT EXPRESSION TOK_RIGHT '{' S '}' {} //nehardcodat 
			/*| TOK_IF TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT';' '}' 
			{
				if(ts->getIntValue($3) > $5){
				int value = ts->getIntValue($10) + $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT TOK_VARIABLE TOK_LESS_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT';' '}' 
			{
				if(ts->getIntValue($3) < $5){
				int value = ts->getIntValue($10) + $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN TOK_VARIABLE TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT';' '}' 
			{
				if(ts->getIntValue($3) > ts->getIntValue($5)){
				int value = ts->getIntValue($10) + $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT TOK_VARIABLE TOK_LESS_THAN TOK_VARIABLE TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT';' '}' 
			{
				if(ts->getIntValue($3) < ts->getIntValue($5)){
				int value = ts->getIntValue($10) + $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT';' '}' 
			{
				if(ts->getIntValue($3) > $5){
				int value = ts->getIntValue($10) - $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT TOK_VARIABLE TOK_LESS_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}' 
			{
				if(ts->getIntValue($3) < $5){
				int value = ts->getIntValue($10) - $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN TOK_VARIABLE TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}' 
			{
				if(ts->getIntValue($3) > ts->getIntValue($5)){
				int value = ts->getIntValue($10) - $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}
			| TOK_IF TOK_LEFT TOK_VARIABLE TOK_LESS_THAN TOK_VARIABLE TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}' 
			{
				if(ts->getIntValue($3) < ts->getIntValue($5)){
				int value = ts->getIntValue($10) - $12;
				ts->setValue($8,value);
                printf("IF TRUE\n");
            }
            else{
                printf("IF FALSE\n");
            }
			}*/
		;
WHILE_STATEMENT : TOK_WHILE TOK_LEFT EXPRESSION TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}'
                {
					printf("WHILE\n");
					int aux,aux2;
					aux = ts->getIntValue($6);
					aux2 = ts->getIntValue($8);
					while(aux2> 1){
						aux2=aux2-$10;
					}
					aux = aux2;
					ts->setValue($6,aux);
                }
				| TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}'
				{
					printf("WHILE\n");
					int expresie = ts->getIntValue($3);
					//$5
					int aux,aux2;
					aux = ts->getIntValue($8);
					aux2 = ts->getIntValue($10);
					while(expresie > $5){
						aux2 = aux2 - $12;
						expresie = expresie - $12;
					}
					aux = aux2;
					ts->setValue($8,aux);
				}
				| TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_LESS_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_MINUS TOK_INT ';' '}'
				{
					printf("WHILE\n");
					int expresie = ts->getIntValue($3);
					//$5
					int aux,aux2;
					aux = ts->getIntValue($8);
					aux2 = ts->getIntValue($10);
					while(expresie < $5){
						aux2 = aux2 - $12;
						expresie = expresie - $12;
					}
					aux = aux2;
					ts->setValue($8,aux);
				}
				| TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_GREATER_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT ';' '}'
				{
					printf("WHILE\n");
					int expresie = ts->getIntValue($3);
					//$5
					int aux,aux2;
					aux = ts->getIntValue($8);
					aux2 = ts->getIntValue($10);
					while(expresie > $5){
						aux2 = aux2 + $12;
						expresie = expresie + $12;
					}
					aux = aux2;
					ts->setValue($8,aux);
				}
				| TOK_WHILE TOK_LEFT TOK_VARIABLE TOK_LESS_THAN E TOK_RIGHT '{' TOK_VARIABLE '=' TOK_VARIABLE TOK_PLUS TOK_INT ';' '}'
				{
					printf("WHILE\n");
					int expresie = ts->getIntValue($3);
					//$5
					int aux,aux2;
					aux = ts->getIntValue($8);
					aux2 = ts->getIntValue($10);
					while(expresie < $5){
						aux2 = aux2 + $12;
						expresie = expresie + $12;
					}
					aux = aux2;
					ts->setValue($8,aux);
				}
				| TOK_WHILE TOK_LEFT EXPRESSION TOK_RIGHT '{' S '}' //nehardcodat
				{
					printf("WHILE\n");
				}

                ;
EXPRESSION : E TOK_GREATER_THAN E { $$ = ($1 > $3) ? 1 : 0; }
           | E TOK_LESS_THAN E { $$ = ($1 < $3) ? 1 : 0; }
           | E TOK_EQUALS E { $$ = ($1 == $3) ? 1 : 0; }
		   | TOK_VARIABLE TOK_GREATER_THAN E { $$ = (ts->getIntValue($1) > $3) ? 1 : 0; }
		   | TOK_VARIABLE TOK_LESS_THAN E { $$ = (ts->getIntValue($1) < $3) ? 1 : 0; }
		   | TOK_VARIABLE TOK_EQUALS E { $$ = (ts->getIntValue($1) == $3) ? 1 : 0; }
		   | TOK_VARIABLE TOK_GREATER_THAN TOK_VARIABLE { $$ = (ts->getIntValue($1) > ts->getIntValue($3)) ? 1 : 0; }
		   | TOK_VARIABLE TOK_LESS_THAN TOK_VARIABLE { $$ = (ts->getIntValue($1) < ts->getIntValue($3)) ? 1 : 0; }
		   | TOK_VARIABLE TOK_EQUALS TOK_VARIABLE { $$ = (ts->getIntValue($1) == ts->getIntValue($3)) ? 1 : 0; }
           | TOK_LEFT EXPRESSION TOK_RIGHT { $$ = $2; }
           ;
INPUT_OUTPUT : TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA TOK_RIGHT { printf("%s",$4); }
    		 | TOK_SCANF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA ',' '&' TOK_VARIABLE TOK_RIGHT TOK_INT
			 {
        		printf("\n%s\n",$4);
				//int temp=0; NU MERGE SCANF NU STIU DE CE
				//scanf("%d", &temp);
				ts->setValue($8,$10);
    		 }
			 | TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_MODULO_D TOK_VARIABLE TOK_GHILIMEA ',' TOK_VARIABLE TOK_RIGHT 
			 { printf("%s %d %s\n",$4,ts->getIntValue($9),$6); }

    		 | TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_MODULO_D TOK_GHILIMEA ',' TOK_VARIABLE TOK_RIGHT 
			 { printf("%s %d\n",$4,ts->getIntValue($8)); }
			 | TOK_SCANF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA ',' '&' TOK_VARIABLE TOK_RIGHT TOK_DOUBLE
			 {
        		printf("\n%s\n",$4);
				//int temp=0; NU MERGE SCANF NU STIU DE CE
				//scanf("%d", &temp);
				ts->setValue($8,$10);
    		 }
			 | TOK_SCANF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_GHILIMEA ',' '&' TOK_VARIABLE TOK_RIGHT TOK_FLOAT
			 {
        		printf("\n%s\n",$4);
				//int temp=0; NU MERGE SCANF NU STIU DE CE
				//scanf("%d", &temp);
				ts->setValue($8,$10);
    		 }
    		 | TOK_PRINTF TOK_LEFT TOK_GHILIMEA TOK_VARIABLE TOK_MODULO_F TOK_GHILIMEA ',' TOK_VARIABLE TOK_RIGHT 
			 { printf("%s %.2f\n",$4,ts->getFloatValue($8)); }

             ;
I : TOK_VARIABLE '=' E
    {
		if(ts != NULL)
		{
			if(ts->exists($1) == 1)
			{
				ts->setValue($1, $3);
			}
			else 
			{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!",@1.first_line, @1.first_column, $1);
	    		yyerror(msg);
	    		YYERROR;
	  		}
		}
		else
		{
	  		sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $1);
	  		yyerror(msg);
	  		YYERROR;
		}
    }
	| TOK_VARIABLE '=' F
	{
		if(ts != NULL)
		{
			if(ts->exists($1) == 1)
			{
				ts->setValue($1, $3);
			}
			else 
			{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $1);
	    		yyerror(msg);
	    		YYERROR;
	  		}
		}
		else
		{
	  		sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $1);
	  		yyerror(msg);
	  		YYERROR;
		}
	}
	| TOK_VARIABLE '=' D
	{
		if(ts != NULL)
		{
			if(ts->exists($1) == 1)
			{
				ts->setValue($1, $3);
			}
			else 
			{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $1);
	    		yyerror(msg);
	    		YYERROR;
	  		}
		}
		else
		{
	  		sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $1);
	  		yyerror(msg);
	  		YYERROR;
		}
	}
    | TOK_DECLARE_INT TOK_VARIABLE
    {
		if(ts != NULL)
		{
			if(ts->exists($2) == 0)
			{
				ts->add($2, 0);
			}
			else
			{
				sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
				yyerror(msg);
				YYERROR;
			}
		}
		else
		{
			ts = new TVAR();
			ts->add($2, 0);
		}
    }
	| TOK_DECLARE_FLOAT TOK_VARIABLE
	{
		if(ts != NULL)
		{
			if(ts->exists($2) == 0)
			{
				ts->add($2, 1);
			}
			else
			{
				sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
				yyerror(msg);
				YYERROR;
			}
		}
		else
		{
			ts = new TVAR();
			ts->add($2, 1);
		}
	}//conversii
	| TOK_DECLARE_DOUBLE TOK_VARIABLE '=' TOK_LEFT TOK_DECLARE_DOUBLE TOK_RIGHT TOK_VARIABLE
	{
		double value=GetValueBasedOnTypeDouble($7,ts->getTipValue($7),ts);
		if (ts != NULL) {
            if (ts->exists($2) == 0) {
                ts->add($2, 2, -1, -1.0, value); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add($2, 2, -1, -1.0, value); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
	}
	| TOK_DECLARE_FLOAT TOK_VARIABLE '=' TOK_LEFT TOK_DECLARE_FLOAT TOK_RIGHT TOK_VARIABLE
	{
		float value=GetValueBasedOnTypeFloat($7,ts->getTipValue($7),ts);
		if (ts != NULL) {
            if (ts->exists($2) == 0) {
                ts->add($2, 1, -1, value, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add($2, 1, -1, value, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
	}
	| TOK_DECLARE_INT TOK_VARIABLE '=' TOK_LEFT TOK_DECLARE_INT TOK_RIGHT TOK_VARIABLE
	{
		int value=GetValueBasedOnTypeInt($7,ts->getTipValue($7),ts);
		if (ts != NULL) {
            if (ts->exists($2) == 0) {
                ts->add($2, 0, value, -1.0f, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add($2, 0, value, -1.0f, -1.0); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
	}
	| TOK_DECLARE_FLOAT TOK_VARIABLE '=' TOK_FLOAT
    {
        if (ts != NULL) {
            if (ts->exists($2) == 0) {
                ts->add($2, 1, -1, $4); // Adaugă variabila și valoarea sa float în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add($2, 1, -1, $4); // Adaugă variabila și valoarea sa float în tabelul de variabile
        }
    }
    | TOK_DECLARE_DOUBLE TOK_VARIABLE '=' TOK_DOUBLE
    {
        if (ts != NULL) {
            if (ts->exists($2) == 0) {
                ts->add($2, 2, -1, -1.0, $4); // Adaugă variabila și valoarea sa double în tabelul de variabile
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add($2, 2, -1, -1.0, $4); // Adaugă variabila și valoarea sa double în tabelul de variabile
        }
    }
	| TOK_DECLARE_INT TOK_VARIABLE '=' TOK_INT
    {
        if (ts != NULL) {
            if (ts->exists($2) == 0) {
                ts->add($2, 0);
				ts->setValue($2,$4);
            } else {
                sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
                yyerror(msg);
                YYERROR;
            }
        } else {
            ts = new TVAR();
            ts->add($2, 0, $4);
        }
    }
	| TOK_DECLARE_DOUBLE TOK_VARIABLE
	{
		if(ts != NULL)
		{
			if(ts->exists($2) == 0)
			{
				ts->add($2, 2);
			}
			else
			{
				sprintf(msg,"%d:%d Eroare semantica: Declaratii multiple pentru variabila %s!", @1.first_line, @1.first_column, $2);
				yyerror(msg);
				YYERROR;
			}
		}
		else
		{
			ts = new TVAR();
			ts->add($2, 2);
		}
	}
    | TOK_PRINT TOK_VARIABLE
    {
		if(ts != NULL)
		{
			if(ts->exists($2) == 1)
			{
				int tipul = ts->getTipValue($2);
				if(tipul == 0)
				{
					if(ts->getIntValue($2) == -1)
					{
						sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost initializata!", @1.first_line, @1.first_column, $2);
						yyerror(msg);
						YYERROR;
					}
					else
					{
						printf("%d\n",ts->getIntValue($2));
					}
				}
				else if(tipul == 1)
				{
					if(ts->getFloatValue($2) == -1)
					{
						sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost initializata!", @1.first_line, @1.first_column, $2);
						yyerror(msg);
						YYERROR;
					}
					else
					{
						printf("%.2ff\n",ts->getFloatValue($2));
					}
				}
				else if(tipul == 2){
					if(ts->getDoubleValue($2) == -1)
					{
						sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost initializata!", @1.first_line, @1.first_column, $2);
						yyerror(msg);
						YYERROR;
					}
					else
					{
						printf("%.2f\n",ts->getDoubleValue($2));
					}
				}
	  		}
	  		else
	  		{
				sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $2);
				yyerror(msg);
				YYERROR;
	  		}
		}
		else
		{
			sprintf(msg,"%d:%d Eroare semantica: Variabila %s este utilizata fara sa fi fost declarata!", @1.first_line, @1.first_column, $2);
			yyerror(msg);
			YYERROR;
		}
    }
    ;
E : E TOK_PLUS E { $$ = $1 + $3; }
    | E TOK_MINUS E { $$ = $1 - $3; }
    | E TOK_MULTIPLY E { $$ = $1 * $3; }
    | E TOK_DIVIDE E 
	{
		if($3 == 0)
		{
			sprintf(msg,"%d:%d Eroare semantica: Impartire la zero!", @1.first_line, @1.first_column);
	      	yyerror(msg);
	      	YYERROR;
	    } 
	  	else 
		{ 
			$$ = $1 / $3; 
		} 
	}
    | TOK_LEFT E TOK_RIGHT { $$ = $2; }
    | TOK_INT { $$ = $1; }
	| TOK_VARIABLE TOK_PLUS TOK_VARIABLE {	$$ = OperatieMatematica($1,$3,'+',ts); }
	| TOK_VARIABLE TOK_MINUS TOK_VARIABLE { $$ = OperatieMatematica($1,$3,'-',ts); }
	| TOK_VARIABLE TOK_MULTIPLY TOK_VARIABLE { $$ = OperatieMatematica($1,$3,'*',ts); }
	| TOK_VARIABLE TOK_DIVIDE TOK_VARIABLE  { $$ = OperatieMatematica($1,$3,'/',ts); }
	| TOK_VARIABLE TOK_PLUS E { $$ = GetValueBasedOnTypeInt($1,ts->getTipValue($1),ts)+$3; }
	| TOK_VARIABLE TOK_MINUS E { $$ = GetValueBasedOnTypeInt($1,ts->getTipValue($1),ts)-$3; }
	| TOK_VARIABLE TOK_MULTIPLY E { $$ = GetValueBasedOnTypeInt($1,ts->getTipValue($1),ts)*$3; } 
	| TOK_VARIABLE TOK_DIVIDE E { $$ = GetValueBasedOnTypeInt($1,ts->getTipValue($1),ts)/$3; }
    ;
D : D TOK_PLUS D { $$ = $1 + $3; }
    | D TOK_MINUS D { $$ = $1 - $3; }
    | D TOK_MULTIPLY D { $$ = $1 * $3; }
    | D TOK_DIVIDE D
	{
		if($3 == 0)
		{
			sprintf(msg,"%d:%d Eroare semantica: Impartire la zero!", @1.first_line, @1.first_column);
	      	yyerror(msg);
	      	YYERROR;
	    } 
	  	else 
		{ 
			$$ = $1 / $3; 
		} 
	}
    | TOK_LEFT D TOK_RIGHT { $$ = $2; }
	| TOK_DOUBLE {$$ = $1; }
	| TOK_VARIABLE TOK_PLUS TOK_VARIABLE {	$$ = OperatieMatematicaDouble($1,$3,'+',ts); }
	| TOK_VARIABLE TOK_MINUS TOK_VARIABLE { $$ = OperatieMatematicaDouble($1,$3,'-',ts); }
	| TOK_VARIABLE TOK_MULTIPLY TOK_VARIABLE { $$ = OperatieMatematicaDouble($1,$3,'*',ts); }
	| TOK_VARIABLE TOK_DIVIDE TOK_VARIABLE  { $$ = OperatieMatematicaDouble($1,$3,'/',ts); }
	| TOK_VARIABLE TOK_PLUS E { $$ = GetValueBasedOnTypeDouble($1,ts->getTipValue($1),ts)+$3; }
	| TOK_VARIABLE TOK_MINUS E { $$ = GetValueBasedOnTypeDouble($1,ts->getTipValue($1),ts)-$3; }
	| TOK_VARIABLE TOK_MULTIPLY E { $$ = GetValueBasedOnTypeDouble($1,ts->getTipValue($1),ts)*$3; } 
	| TOK_VARIABLE TOK_DIVIDE E { $$ = GetValueBasedOnTypeDouble($1,ts->getTipValue($1),ts)/$3; }
    ;
F : F TOK_PLUS F { $$ = $1 + $3; }
    | F TOK_MINUS F { $$ = $1 - $3; }
    | F TOK_MULTIPLY F { $$ = $1 * $3; }
    | F TOK_DIVIDE F
	{
		if($3 == 0)
		{
			sprintf(msg,"%d:%d Eroare semantica: Impartire la zero!", @1.first_line, @1.first_column);
	      	yyerror(msg);
	      	YYERROR;
	    } 
	  	else 
		{ 
			$$ = $1 / $3; 
		} 
	}
    | TOK_LEFT F TOK_RIGHT { $$ = $2; }
	| TOK_FLOAT {$$ = $1; }
	| TOK_VARIABLE TOK_PLUS TOK_VARIABLE {	$$ = OperatieMatematicaFloat($1,$3,'+',ts); }
	| TOK_VARIABLE TOK_MINUS TOK_VARIABLE { $$ = OperatieMatematicaFloat($1,$3,'-',ts); }
	| TOK_VARIABLE TOK_MULTIPLY TOK_VARIABLE { $$ = OperatieMatematicaFloat($1,$3,'*',ts); }
	| TOK_VARIABLE TOK_DIVIDE TOK_VARIABLE  { $$ = OperatieMatematicaFloat($1,$3,'/',ts); }
	| TOK_VARIABLE TOK_PLUS E { $$ = GetValueBasedOnTypeFloat($1,ts->getTipValue($1),ts)+$3; }
	| TOK_VARIABLE TOK_MINUS E { $$ = GetValueBasedOnTypeFloat($1,ts->getTipValue($1),ts)-$3; }
	| TOK_VARIABLE TOK_MULTIPLY E { $$ = GetValueBasedOnTypeFloat($1,ts->getTipValue($1),ts)*$3; } 
	| TOK_VARIABLE TOK_DIVIDE E { $$ = GetValueBasedOnTypeFloat($1,ts->getTipValue($1),ts)/$3; }
    ;
%%

int main()
{
	yyparse();
	
	if(EsteCorecta == 1)
	{
		cout<<"CORECT\n";	
	}	

	ts->printVars();
	return 0;
}

int yyerror(const char *msg)
{
	cout<<"EROARE: "<<msg<<endl;	
	return 1;
}
