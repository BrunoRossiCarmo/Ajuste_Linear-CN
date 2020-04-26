//tts Bruno Rossi disse: Calma que vou ajustar algumas coisas ainda pra evitar fazer corridão e parecer algo lógico!


#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<locale.h>


//----------Encontrar-Pivo-------------//
float max_pivo(float matriz[][9], int linha){
	int f;
	int i = linha;
	float pivo;
	f = 0;
	pivo = 0;
	while(f!=i){
		if(fabs(matriz[f][1])>fabs(pivo)){
			pivo = (matriz[f][1]);
		}
		f++;
	}
	printf("\nO valor do Pivô será: %.0f\n", pivo);
	return pivo;
}
//-------------------------------------------------//

//------------Fazer-Subtituição-de-Linhas--------------//
void substitut(float matriz[][9],float pivo){
	int i= 0;
	int c;      //--------------> Carga de Valor
	int cont = 0;
	while(matriz[i][1]!=pivo){
		i++;
	}
	while(cont!=9){
		c = matriz[i][cont];
		matriz[i][cont]=matriz[0][cont];
		matriz[0][cont]= c;
		cont++;
	}
}
//------------------------------------------------------//

//------------Realizar-Ajustes-Para-Iniciar-Processo-----------------//
void do_it(float matriz[][9], int linha, int coluna, float pivo, int inicio){
	int cont = 1;
	int cont2 = 0;
	int pass;
	float constant;
	while(cont<linha){
		if(matriz[cont][coluna]!=0){
			constant = (matriz[cont][coluna])/(pivo);
			pass = cont;
		}
		cont++;
	}
	while (cont2 != 9){
		matriz[pass][cont2] =  (matriz[pass][cont2]) - (constant*(matriz[inicio][cont2]));
		cont2++;
	}			
}
//-------------------------------------------------------------------//



int main(){
	
	//--------------Matriz------------------//
	int i = 8; //----------------> Oito Linhas
	int j = 9; //----------------> Nove Colunas
	float matriz[i][j]; //---------> Matriz que Iremos realizar o Método de Gauss com Pivotamento Parcial
	int k = i-1; //--------------> Iterações
	setlocale(LC_ALL,"");
	//--------------------------------------//
	
	//----------Abetura-de-Arquivo---------//
	FILE *file; 
	file = fopen("MATRIZ.txt","r");//--------------->  Abrir Arquivo
	if(file==NULL){
    	printf("Erro ao abrir arquivo!\n"); 
  	}
  	//------------------------------------//
  	
  	//--------Leitura-de-Variáveis-----------//
  	int cont;    //---------------> Contador para Laço de Repetição
  	int cont2;  //----------------> Contador para Laço de Repetição
  	rewind(file);
  	//---------------------------------------//
  	
  	//-----------------------Lendo-a-Matriz-------------------------//
  	for(cont = 0; cont<i;cont++){
  		fscanf(file, "%f %f %f %f %f %f %f %f %f", &matriz[cont][0], &matriz[cont][1], &matriz[cont][2], &matriz[cont][3], &matriz[cont][4], &matriz[cont][5], &matriz[cont][6], &matriz[cont][7], &matriz[cont][8]);
	}
	//-------------------------------------------------------------//
	
	//------------Printando-a-Matriz-------------------------------//
	for (cont = 0; cont < i; cont++){
		for(cont2 = 0; cont2 < j ; cont2++){
			printf(" %.0f ", matriz[cont][cont2]);
		}
		printf("\n");
	}
	//-----------------------------------------------------------//
	
	//------------Encontrar-Pivo------------------//
	float pivo;
	pivo = max_pivo(matriz,i);
	substitut(matriz, pivo);
	//-------------------------------------------//
	
	//------------Printando-a-Matriz-------------------------------//
	printf("\n");
	for (cont = 0; cont < i; cont++){
		for(cont2 = 0; cont2 < j ; cont2++){
			printf(" %.0f ", matriz[cont][cont2]);
		}
		printf("\n");
	}
	//--------------------------------------------------------------//
	
	//--------------Primeira-Iteração---------------------//
	do_it(matriz, i, 0, pivo, 0);
	//----------------------------------------------------//
	
	//------------Printando-a-Matriz-------------------------------//
	printf("\n");
	for (cont = 0; cont < i; cont++){
		for(cont2 = 0; cont2 < j ; cont2++){
			printf(" %.0f ", matriz[cont][cont2]);
		}
		printf("\n");
	}
	//--------------------------------------------------------------//
	
	
  	return 0;
}
