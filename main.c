#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int comparaString(char a[], char b[]){
	int c;
	for(c=0; a[c] != '\0'; c++){
		if(a[c] != b[c])
		    return 0;
		}
		if(a[c] != b[c])
		    return 0;
		else
		    return 1;

}

int comparaStringMatriz(char a[], char b[30][30], int QtEstadosFinais){
	int c, i;
	int cont=0;
	
	int erro = 0;
	for(i=0; i<QtEstadosFinais; i++){
		for(c=0; a[c] != '\0'; c++){
			erro = 0;
			if(a[c] != b[i][c]){
			    cont = 0;
			    erro = 1;
			}    
		}
		
		if(erro == 0){
			if(a[c] != b[i][c]){
			   cont = 0;
			   break;
			}
			else{
				cont = 1;
				return 1;
				}
		}
	}
    return cont;
}

void inicializaMatriz(int T[30][30]){
	int i, j;

		for(i=0; i<30; i++){
			for(j=0; j<30; j++){
				T[i][j] = -1;
			}
		}
}

void tab(int qt, FILE *fp){
	int i;
	for(i=0; i< qt; i++)
		fprintf(fp, "\t");
	}
	
void CarregaHeader(FILE *fp, int tipo, char e[30][30], int qtEstados){
	if(tipo == 1){ // Função
		fprintf(fp, "#include <stdio.h>\n");
		fprintf(fp, "#include <stdlib.h>\n");
		fprintf(fp, "#include <conio.h>\n\n");

		fprintf(fp, "char f[200];\n");
		fprintf(fp, "int p;\n");
		
		int i;
		for(i=0; i<qtEstados; i++){
			fprintf(fp, "void %s();\n", e[i]);
		}
				
		fprintf(fp, "void Aceita();\n");
		fprintf(fp, "void Rejeita();\n\n");
		
	}
	else{ // GOTO
		
	}
}

void CarregaMainFuncao(FILE *fp, char q0[]){

	fprintf(fp, "int main(int argc, char *argv[]){\n");
	tab(1, fp);
	fprintf(fp, "p = 0;\n\n");
	tab(1, fp);
	fprintf(fp, "printf(\"Linha: \");\n");
	tab(1, fp);
	fprintf(fp, "gets(f);\n\n");
	tab(1, fp);
	fprintf(fp, "%s();\n\n", q0);
	tab(1, fp);
	fprintf(fp, "system(\"pause\");\n");
	tab(1, fp);
	fprintf(fp, "return 0;\n");
	fprintf(fp, "}");	
}

void CarregaAceitaRejeita(FILE *fp){
	
	fprintf(fp, "void Aceita(){\n");
	tab(1, fp);
	fprintf(fp, "printf(\"\\nAceita\\n\");\n");
	tab(1, fp);
	fprintf(fp, "getch();\n");
	tab(1, fp);
	fprintf(fp, "exit(0);\n");
	fprintf(fp, "}\n\n");
	
	fprintf(fp, "void Rejeita(){\n");
	tab(1, fp);
	fprintf(fp, "printf(\"\\nRejeita\\n\");\n");
	tab(1, fp);
	fprintf(fp, "getch();\n");
	tab(1, fp);
	fprintf(fp, "exit(0);\n");
	fprintf(fp, "}\n\n");	
}
	
void EscrevePorfuncao(FILE *fp, char estados[30][30], char alfabeto[], int t[30][30], int QtEstados, int QtAlfabeto, char f[30][30], int QtEstadosFinais, char q0[]){

    int i, j, aux = 0, aux2;

	CarregaHeader(fp, 1, estados, QtEstados); // Cabeçalho
	
	for(i = 0; i < QtEstados; i++){
        fprintf(fp, "void %s(){\n", estados[i] );

		for(j = 0; j < QtAlfabeto; j++){
			if(t[i][j] != -1){
				tab(aux, fp);
    			fprintf(fp, "\tif(f[p] == '%c'){\n",alfabeto[j] );
    			tab(aux, fp);
    			fprintf(fp, "\t\tp++;\n");
    			tab(aux, fp);
    			fprintf(fp, "\t\t%s();\n",estados[t[i][j]]);
    			tab(aux, fp);
    			fprintf(fp, "\t}\n");
    			tab(aux, fp);
    			fprintf(fp, "\telse{\n");
    			aux++;
			}
		}

		aux2 = aux;
		
		if(comparaStringMatriz(estados[i], f, QtEstadosFinais)){
            tab(aux, fp);
            fprintf(fp, "\tif(f[p] == 0)\n");
            tab(aux, fp);
            fprintf(fp, "\t\tAceita();\n");
            tab(aux, fp);
            fprintf(fp, "\telse\n");
            tab(aux, fp);
            fprintf(fp, "\t\tRejeita();\n");
		}
		else{
            tab(aux, fp);
            fprintf(fp, "\tRejeita();\n");
		}

		for(j = 0; j < aux2; j++){
            tab(aux, fp);
			fprintf(fp, "}\n");
			aux--;
		}
		fprintf(fp, "}\n\n");
	}
	
	CarregaAceitaRejeita(fp); // Funções Rejeita() e Aceita()
	CarregaMainFuncao(fp, q0); // Main Função
	
}

void EscrevePorGOTO(FILE *fp, char estados[30][30], char alfabeto[], int t[30][30], int QtEstados, int QtAlfabeto, char f[30][30], int QtEstadosFinais, char q0[]){
	
	int i, j, aux = 0, aux2;
	
	fprintf(fp, "#include <stdio.h>\n");
	fprintf(fp, "#include <stdlib.h>\n");
	fprintf(fp, "#include <conio.h>\n\n");

	fprintf(fp, "int main(int argc, char *argv[]){\n");
	tab(1, fp);
	fprintf(fp, "char f[200];\n");
	tab(1, fp);
	fprintf(fp, "int p = 0;\n\n");
	tab(1, fp);
	fprintf(fp, "printf(\"Linha: \");\n");
	tab(1, fp);
	fprintf(fp, "gets(f);\n\n");
	
	tab(1, fp);
	fprintf(fp, "goto %s;\n\n", q0);
	
	
	for(i = 0; i < QtEstados; i++){
        fprintf(fp, "\t%s:\n", estados[i] );

		for(j = 0; j < QtAlfabeto; j++){
			if(t[i][j] != -1){
				tab(aux +1, fp);
    			fprintf(fp, "\tif(f[p] == '%c'){\n",alfabeto[j] );
    			tab(aux +1, fp);
    			fprintf(fp, "\t\tp++;\n");
    			tab(aux +1, fp);
    			fprintf(fp, "\t\tgoto %s;\n",estados[t[i][j]]);
    			tab(aux +1, fp);
    			fprintf(fp, "\t}\n");
    			tab(aux +1, fp);
    			fprintf(fp, "\telse{\n");
    			aux++;
			}
		}

		aux2 = aux;
		
		if(comparaStringMatriz(estados[i], f, QtEstadosFinais)){
            tab(aux +1, fp);
            fprintf(fp, "\tif(f[p] == 0)\n");
            tab(aux +1, fp);
            fprintf(fp, "\t\tgoto Aceita;\n");
            tab(aux +1, fp);
            fprintf(fp, "\telse\n");
            tab(aux +1, fp);
            fprintf(fp, "\t\tgoto Rejeita;\n");
		}
		else{
            tab(aux +1, fp);
            fprintf(fp, "\tgoto Rejeita;\n");
		}

		for(j = 0; j < aux2; j++){
            tab(aux +1, fp);
			fprintf(fp, "}\n\n");
			aux--;
		}
	}
	
	fprintf(fp, "\tAceita:\n");
	tab(2, fp);
	fprintf(fp, "printf(\"\\nAceita\\n\");\n");
	tab(2, fp);
	fprintf(fp, "getch();\n");
	tab(2, fp);
	fprintf(fp, "return 0;\n\n");
	
	fprintf(fp, "\tRejeita:\n");
	tab(2, fp);
	fprintf(fp, "printf(\"\\nRejeita\\n\");\n");
	tab(2, fp);
	fprintf(fp, "getch();\n");
	tab(2, fp);
	fprintf(fp, "return 0;\n\n");	

	fprintf(fp, "}");
}

char* concatenar(char a[], char b[]){
	int i, j;
	char *buffer;
    buffer=(char*)malloc((j-i+1)*1);
    
	for(i=0; a[i] != '\0'; i++){
		buffer[i] = a[i];
	}
	for(j=0; b[j] != '\0'; j++){
		buffer[i] = b[j];
		i++;
	}
	
	return (char *)buffer;
}
	
int main(int argc, char *argv[]) 
{
	char nome[10], q0[30], aux[30], cmd[30] = {"gcc "}, cmdStart[30] = {"start "};
	char Q[30][30], S[30], F[30][30];
	int T[30][30];
	int TpFuncao = 0, QtAlfabeto = 0, QtEstados = 0, QtEstadosFinais = 0;
	int i, j, exec;
	FILE *fp;
	
	
	inicializaMatriz(T);
	
	printf("Qual o nome do programa a ser gerado? ");
	gets(nome);
	

	for(i=0; nome[i] != '\0'; i++);
	nome[i++] = '.';
	nome[i++] = 'c';
	nome[i] = '\0';
	
	

	printf("\nGerar em funcao(1) ou Goto(2))? ");
	scanf("%d%*c", &TpFuncao);
	
	printf("\nQuantos simbolos tem o alfabeto? ");
	scanf("%d%*c", &QtAlfabeto);
	
	
	for(i = 0; i<QtAlfabeto; i++){
		printf("Qual o simbolo %d? ", i);
		fflush(stdin);
		scanf("%c", &S[i]);
		}

	
	printf("\nQuantos estados? ");
	scanf("%d%*c", &QtEstados);
	
	for(i=0; i<QtEstados; i++){
		printf("Qual o nome do estado %d? ", i);
		gets(Q[i]);
		}
		
    printf("\nQual o estado inicial? ");
	gets(q0);
	
	printf("\nQuantos estados finais? ");
	scanf("%d%*c", &QtEstadosFinais);
	
	for(i=0; i<QtEstadosFinais; i++){
        printf("Qual o estado final %d? ", i);
		gets(F[i]);
		}

	int x;
	for(i=0; i<QtEstados; i++){
		for(j=0; j<QtAlfabeto; j++){
			printf("Para o estado %s e o simbolo %c, qual o proximo estado?  ", Q[i], S[j]);
			gets(aux);
			
		    for(x=0; x < QtEstados; x++){
				if(comparaString(Q[x], aux)){
					T[i][j] = x;
					}
				}
			}
		}
	
	if((fp = fopen(nome, "wt")) == NULL){
		printf("Erro ao abrir arquivo!\n");
		getch();
		exit(0);
		}
		
	if(TpFuncao == 1){
		EscrevePorfuncao(fp,Q,S,T,QtEstados,QtAlfabeto,F, QtEstadosFinais, q0);
	}
	else if(TpFuncao == 2){
		EscrevePorGOTO(fp,Q,S,T,QtEstados,QtAlfabeto,F, QtEstadosFinais, q0);
	}
	
	fclose(fp);

	printf("#Programa gerado.\n");
	printf("Deseja executar (1 = SIM, 2 = NAO)? ");
	
	scanf("%d%*c", &exec);
	
	if(exec == 1){
		char buffer[30];
	    i=0;
		for(i=0; cmd[i] != '\0'; i++){
			buffer[i] = cmd[i];
		}
		for(j=0; nome[j] != '.'; j++){
			buffer[i] = nome[j];
			i++;
		}
        buffer[i++] = '.';
	    buffer[i++] = 'c';
	    buffer[i] = '\0';
		buffer[i++] = ' ';
	    buffer[i++] = '-';
	    buffer[i++] = 'o';
	    buffer[i++] = ' ';

	    for(j=0; nome[j] != '.'; j++){
			buffer[i] = nome[j];
			i++;
		}
		buffer[i] = '\0';

		
		system(buffer);

		i=0;
		for(i=0; cmdStart[i] != '\0'; i++){
			buffer[i] = cmdStart[i];
		}

		for(j=0; nome[j] != '.'; j++){
			buffer[i] = nome[j];
			i++;
		}

		buffer[i++] = '.';
	    buffer[i++] = 'e';
	    buffer[i++] = 'x';
	    buffer[i++] = 'e';
		buffer[i++] = '\0';
		
		system(buffer);
	}
	
	
 	system("pause");
	return 0;
}
