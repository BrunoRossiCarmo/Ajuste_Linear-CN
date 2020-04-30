//tts Bruno Rossi disse: Calma que vou ajustar algumas coisas ainda pra evitar fazer corridão e parecer algo lógico!


#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<locale.h>


//------------Fazer-Subtituição-de-Linhas/Encontrar-Pivo--------------//
void substitut(double matriz[][9], int linha, int inicio_l, int inicio_c, int armazenador){
	double c;                  //------------> Carga útil
	int i;                 //-------------> Contador de Auxílio
	double constante;      //------------->  Constante da Linha = Linha_de_Baixo/pivo
	int contador;        //---------------> Contador de Coluna
	int som=inicio_l;        //--------------->  Somador útil para encontrar linha
	double pivo = 0;
	
	//-------------Encontra-o-Pivo------------------//
	for(i = inicio_l; i<linha; i++){
		if(fabs(matriz[i][inicio_c])>(fabs(pivo))){             //Se |matriz[0,1,...7][0,1,...7]| > |pivo|, o elemento dessa posição se torna pivo
			pivo = matriz[i][inicio_c]; 						//pivo = matriz[0,1,...,7][0,1,...,n]
			printf("\n|O valor do pivo é: %lf|\n", pivo);       
		}
	}
	
	//-------Encontrando-Linha-Para-Substituir-------------//
	while(matriz[som][inicio_c]!=pivo){
		som++;
		printf("\n|O valor do somador : %d|\n\n", som);
	}
	
	//------Trocar-Linhas-------//
	for(i=0;i<9;i++){
		c = matriz[som][i];
		matriz[som][i] = matriz[inicio_l][i];
		matriz[inicio_l][i] = c;
	}
	
	//--------Realizar-o-Método-de-Gauss--------------//
    i = armazenador;
	while(i<linha){
		if(matriz[i][inicio_c]!=0){
			constante = matriz[i][inicio_c]/pivo;
			printf("\n|O valor da constante é: %lf|\n\n",constante);
			for(contador=inicio_c;contador<9;contador++){
				matriz[i][contador] = matriz[i][contador] - (((matriz[inicio_l][contador]))*(constante));
			}
		}
		i++;
	}
}
//------------------------------------------------------//



int main(){
	
	//--------------Matriz------------------//
	int i = 8; //----------------> Oito Linhas
	int j = 9; //----------------> Nove Colunas
	double matriz[i][j]; //---------> Matriz que Iremos realizar o Método de Gauss com Pivotamento Parcial
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
  		fscanf(file, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &matriz[cont][0], &matriz[cont][1], &matriz[cont][2], &matriz[cont][3], &matriz[cont][4], &matriz[cont][5], &matriz[cont][6], &matriz[cont][7], &matriz[cont][8]);
	}
	//-------------------------------------------------------------//
	
	
	//------------Printando-a-Matriz-------------------------------//
	for (cont = 0; cont < i; cont++){
		for(cont2 = 0; cont2 < j ; cont2++){
			printf(" %.0lf ", matriz[cont][cont2]);
		}
		printf("\n");
	}
	//-----------------------------------------------------------//
	
	
	//--------------------Ajustando-A-Matriz/Encontrando-Pivo-----------------------//
	int full_cont = 0;
	int full_cont2 = 0;
	int armazenador = 1;
	while(full_cont2<7){
		substitut(matriz,i,full_cont,full_cont2,armazenador);
		full_cont++;
		full_cont2++;
		armazenador++;	
			//------------Printando-a-Matriz-------------------------------//
			for (cont = 0; cont < i; cont++){
				for(cont2 = 0; cont2 < j ; cont2++){
					printf(" %lf ", matriz[cont][cont2]);
				}
				printf("\n");
			}
			//-----------------------------------------------------------//
	}
	//-------------------------------------------------------------//

	
	//------------Printando-a-Matriz-------------------------------//
	printf("\n");
	for (cont = 0; cont < i; cont++){
		for(cont2 = 0; cont2 < j ; cont2++){
			printf(" %lf ", matriz[cont][cont2]);
		}
		printf("\n");
	}
	//-----------------------------------------------------------//

  	return 0;
}
