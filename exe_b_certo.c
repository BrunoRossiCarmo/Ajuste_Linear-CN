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
	//F(x) = z + k*(1/sqrt(d))
	//d = x
	//g1(x) = 1
	//g2(x) = 1/sqrt(x)
	//soma1-> <g1,g2>; ; soma2-> <g2,g2>; soma3-> <g1,f> soma4-> <g2,f>
	//<g1,g1> = 1 = n; <g1,g2> = <g2,g1> = 1/sqrt(xi); <g2,g2> = 1/xi; <g1,f> = f(xi); <g2,f> = f(xi)/sqrt(xi)
	//a1 = z
	//a2 = k
	
	//Como estamos fazendo matrizes para resolução de um sistema de equações pela regra de Cramer+
    //então, temos que fazer A1 e A2 e calcular suas determinantes.
   
    // [ <g1,fx>   <g1,g2> ]  
    // [ <g2,fx>   <g2,g2> ]  // Matriz A1.
   
    // [ <g1,g1>   <g1,fx> ]  
    // [ <g2,g1>   <g2,fx> ]  // Matriz A2.
   
    // [ <g1,g1>   <g1,g2> ]  
    // [ <g2,g1>   <g2,g2> ]  // Matriz A.
   
    //a = Det(A1)/Det(A)
    //b = Det(A2)/Det(A)
   
	float a, b;
	float numa;// -> Det(A1)
	float numb;// -> Det(A2)
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
		soma1 = soma1 + (1/sqrt(x[i]));
		soma2 = soma2 + (1/x[i]);
		soma3 = soma3 + (f[i]);
		soma4 = soma4 + ((f[i])/sqrt(x[i]));
	}
	
	numa = ((soma3*soma2) - (soma1*soma4));
	numb = ((n*soma4) - (soma3*soma1));
	denom = ((n*soma2) - (soma1*soma1));
	
	a = numa/denom;
	b = numb/denom;
	
	printf("g(x) = %.4f + %.4f(1/sqrt(x))", a, b); 
	
	tensao = a + b*(1/sqrt(0.05));		
	
	printf("\n");
	printf("A tensao com Grao de 0.05mm equivale em: %.4f MPa",tensao);
	}
	
	return 0;
	
}
