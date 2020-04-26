#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<locale.h>


//----------Encontrar-Pivo-------------//
int max_pivo(int matriz[][9], int linha){
	int f;
	int i = linha;
	int pivo;
	f = 0;
	pivo = 0;
	while(f!=i){
		if(fabs(matriz[f][1])>fabs(pivo)){
			pivo = (matriz[f][1]);
		}
		f++;
	}
	printf("\nO valor do Piv� ser�: %d\n",pivo);
	return pivo;
}

void substitut(int matriz[][9],int pivo){
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

int main(){
	
	//--------------Matriz------------------//
	int i = 8; //----------------> Oito Linhas
	int j = 9; //----------------> Nove Colunas
	int matriz[i][j]; //---------> Matriz que Iremos realizar o M�todo de Gauss com Pivotamento Parcial
	setlocale(LC_ALL,"");
	
	//----------Abetura-de-Arquivo---------//
	FILE *file; 
	file = fopen("MATRIZ.txt","r");//--------------->  Abrir Arquivo
	if(file==NULL){
    	printf("Erro ao abrir arquivo!\n"); 
  	}
  	
  	//--------Leitura-de-Vari�veis-----------//
  	int cont;    //---------------> Contador para La�o de Repeti��o
  	int cont2;  //----------------> Contador para La�o de Repeti��o
  	rewind(file);
  	
  	//-----------------------Lendo-a-Matriz-------------------------//
  	for(cont = 0; cont<i;cont++){
  		fscanf(file, "%d %d %d %d %d %d %d %d %d", &matriz[cont][0], &matriz[cont][1], &matriz[cont][2], &matriz[cont][3], &matriz[cont][4], &matriz[cont][5], &matriz[cont][6], &matriz[cont][7], &matriz[cont][8]);
	}
	
	//------------Printando-a-Matriz-------------------------------//
	for (cont = 0; cont < i; cont++){
		for(cont2 = 0; cont2 < j ; cont2++){
			printf(" %d ", matriz[cont][cont2]);
		}
		printf("\n");
	}
	
	//------------Encontrar-Pivo------------------//
	int pivo;
	pivo = max_pivo(matriz,i);
	substitut(matriz, pivo);
	
	//------------Printando-a-Matriz-------------------------------//
	printf("\n");
	for (cont = 0; cont < i; cont++){
		for(cont2 = 0; cont2 < j ; cont2++){
			printf(" %d ", matriz[cont][cont2]);
		}
		printf("\n");
	}
	
  	return 0;
}
