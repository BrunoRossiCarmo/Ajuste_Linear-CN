#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{	
	int i;
	int n;//quantidade de pontos
	float x[n];//vetor dos valores de x
	float f[n];//vetor dos valores de f(x)
	float soma1 = 0, soma2 = 0, soma3 = 0, soma4 = 0;
	float tensao;
	float e = 2.7183;//numero de euler, aproximado com 3 dígitos significativos
	
	/*Este problema eh linearizado por meio de uma transformação logarítmica ln f(x) ~ ln(a*e^bx) = ln a + bx
	Observando que as funções de ajuste são g1(x) = 1 e g2(x) = x e os parâmetros
	são a1 = ln a e a2 = b, reduzimos o problema a um caso de ajsute por função linearnos parâmetros 
	Chamando F(x) = ln f(x), temos então um novo problema F(x) ~ G(x) = a1 + a2x*/
	
	
	//[ <g1,g1>   <g1,g2> ]   *   [a1]   =   [ <g1,F> ]   
	//[ <g2,g1>   <g2,g1> ]       [a2]       [ <g2,F> ]
	
	/* obtemos a1 e a2 e, para finalizar, voltamos aos parâmetros
	iniciais a = e^a1 e b = a2 */
 	
	//Como estamos fazendo matrizes para resolução de um sistema de equações pela regra de Cramer+
    //então, temos que fazer A1 e A2 e calcular suas determinantes.
   
    // [ <g1,F>   <g1,g2> ]  
    // [ <g2,F>   <g2,g2> ]  // Matriz A1.
   
    // [ <g1,g1>   <g1,F> ]  
    // [ <g2,g1>   <g2,F> ]  // Matriz A2.
   
    // [ <g1,g1>   <g1,g2> ]  
    // [ <g2,g1>   <g2,g2> ]  // Matriz A.
   
    //g1(x) = 1
    //g2(x) = x
    //a1 = Det(A1)/Det(A)
    //a2 = Det(A2)/Det(A)
   
	float a1, a2;
	float a, b;
	float numa1;// -> Det(A1)
	float numa2;// -> Det(A2)
	float denom;// -> Det(A)
	
	printf("Digite a quantidade de pontos: ");
	scanf("%d", &n);
	if(n <= 0){
		printf("Naum eh possivel com essa quantidade de pontos");
	}
	
	else{
	printf("Quais sao os %d valores de x?\n ", n);
	for(i=0; i<n; i++){
		printf("x%d = ", i);	
		scanf("%f", &x[i]);
	}
	printf("\n");
	
	printf("Quais sa os %d valores de f(x)?\n ", n);
	for(i=0; i<n; i++){
		printf("f(x%d) = ", i);	
		scanf("%f", &f[i]);
	}
	printf("\n");
	
	for(i = 0; i<n; i++){
		soma1 = soma1 + (x[i]);
		soma2 = soma2 + (x[i]*x[i]);
		soma3 = soma3 + (log(f[i]));//log() -> logaritimo natural (ln)
		soma4 = soma4 + ((log(f[i]))*(x[i]));
	}
	
	numa1 = ((soma3*soma2) - (soma1*soma4));
	numa2 = ((n*soma4) - (soma3*soma1));
	denom = ((n*soma2) - (soma1*soma1));
	
	a1 = numa1/denom;
	a2 = numa2/denom;
	
	a = pow(e,a1);
	b = a2;
	
	printf("g(x) = %.4f*e^(%.4f*x)", a, b); 
	
	tensao = a*(pow(e,(b*0.05)));		
	
	printf("\n");
	printf("A tensao com Grao de 0.05mm equivale em: %.4f",tensao);
	}
	
	return 0;
}
