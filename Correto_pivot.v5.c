//Bruno Rossi Carmo
//Carlos Eduardo Capelini
//Gabriel Montenegro de Campos


#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<locale.h>


//------------Fazer-Subtituição-de-Linhas/Encontrar-Pivo--------------//
void substitut(int coluna, double matriz[][coluna], int linha, int inicio_l, int inicio_c, int armazenador){
	double c;                  //------------> Carga útil
	int i;                 //-------------> Contador de Auxílio
	double constante;      //------------->  Constante da Linha = Linha_de_Baixo/pivo
	int contador;        //---------------> Contador de Coluna
	int som=inicio_l;        //--------------->  Somador útil para encontrar linha
	double pivo = 0;
	
	//-------------Encontra-o-Pivo------------------//
	for(i = inicio_l; i<linha; i++){
		if(fabs(matriz[i][inicio_c])>(fabs(pivo))){             
			pivo = matriz[i][inicio_c]; 						     
		}
	}
	
	//-------Encontrando-Linha-Para-Substituir-------------//
	while(matriz[som][inicio_c]!=pivo){
		som++;
	}
	
	//------Trocar-Linhas-------//
	for(i=0;i<coluna;i++){
		c = matriz[som][i];
		matriz[som][i] = matriz[inicio_l][i];
		matriz[inicio_l][i] = c;
	}
	
	//--------Realizar-o-Método-de-Gauss--------------//
    i = armazenador;
	while(i<linha){
		if(matriz[i][inicio_c]!=0){
			constante = matriz[i][inicio_c]/pivo;
			for(contador=inicio_c;contador<coluna;contador++){
				matriz[i][contador] = matriz[i][contador] - (((matriz[inicio_l][contador]))*(constante));
			}
		}
		i++;
	}
}
//------------------------------------------------------//


//------------------Obter-Resultados------------------------------------------------//
void coef(int coluna, int linha, double matriz[][coluna]){
	coluna--; //------->Ajustes para encaixar na Matriz Computacional (inicia contagem no 0)<--- coluna inicia em 8 (0 até 8)
	linha--;  //------->Ajustes para encaixar na Matriz Computacional (inicia contagem no 0)<--- linha inicia em 7 (0 até 7)
	int i;  //--------->Contador auxiliar
	int dig = coluna-1; //--------->Dig representa o valor da coluna que irá decrescer para auxiliar na localização da diagonal
 	int dig2 = linha; //--------->Dig2 representa o valor da coluna que irá decrescer para auxiliar na localização da diagonal
	int cont = linha; //--------->Faz a contagem para o vetor resultado
	double resultado[linha]; //--------> Vetor com os valores de cada equação
	int contador = coluna-1; 
	
	//Inicia nossas iterações:
	for(i = linha; i>=0; i--){
		//Realiza as inversões de lados das constantes:
		while(contador>dig){
			if(dig == 0){
				matriz[dig2][coluna] = matriz[dig2][coluna] - (matriz[dig2][contador]*resultado[cont]);
				if(matriz[dig2][contador]=matriz[0][0]){
					matriz[dig2][coluna] = matriz[dig2][coluna];
				}
				cont--;
			}
			else if(matriz[dig2][contador]!=matriz[dig2][dig]&&dig2<linha){
				matriz[dig2][coluna] = matriz[dig2][coluna] - (matriz[dig2][contador]*resultado[cont]);
				cont--;
			}
			contador--;
		}
		contador = coluna-1;
		cont = linha;
		//Realiza o cálculo do coeficiente específico da equação:
		if(matriz[dig2][dig]!=0){
			matriz[dig2][coluna] = (matriz[dig2][coluna])/(matriz[dig2][dig]);
			resultado[dig2]=matriz[dig2][coluna];
		}

		dig--;
		dig2--;
	}
	
	for(i = 0; i<8; i++){
		printf("\nValores resultados: %lf\n",resultado[i]);
	}
}

//-------------------------------------------------------------------------------------------//


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
	while(full_cont2<i-1){
		substitut(j,matriz,i,full_cont,full_cont2,armazenador);
		full_cont++;
		full_cont2++;
		armazenador++;	
			//------------Printando-a-Matriz-------------------------------//
			printf("\n");
			for (cont = 0; cont < i; cont++){
				for(cont2 = 0; cont2 < j ; cont2++){
					printf(" %lf ", matriz[cont][cont2]);
				}
				printf("\n");
			}
			//-----------------------------------------------------------//
	}
	//-------------------------------------------------------------//
	
	//------------------Armazenando-Valores-Coeficientes------------//
	coef(j,i,matriz);
	//--------------------------------------------------------------//

  	return 0;
}
