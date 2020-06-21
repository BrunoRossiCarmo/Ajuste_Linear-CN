//Bruno Rossi Carmo
//Gabriel de Campos
//Carlos Eduardos

#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<locale.h>
#include "pbPlots.h"      //--->Plotar o Grafico.
#include "supportLib.h"   //--->Plotar o Grafico.

//--------------------------------------------------Funções--------------------------------------------------//
//----------------Valores-Para-Montar-Vetor----------------//
void recebe_valores(int quantidade, double *var)
{ int i;
  for(i=0; i<quantidade; i++)     //Vai receber os valores da tabela.
  { printf("\nInsira (%d): ", i);
    scanf("%lf", &var[i]);
  }
}
//---------------------------------------------------------//
//-----------------Plotagem-----------------//
void plot_2(double *x, double *y)
{   ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = x;
	series->xsLength = 900;
	series->ys = y;
	series->ysLength = 900;
	series->linearInterpolation = true;
	series->lineType = L"solid";
	series->lineTypeLength = wcslen(series->lineType);
	series->color = GetGray(1);
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
    settings->title = L"Equacao Hall-Petch";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"Tensao do Limite de Escoamento";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"Tamanho dos Graos";
    settings->yLabelLength = wcslen(settings->yLabel);
	ScatterPlotSeries *s [] = {series};
	settings->scatterPlotSeries = s;
	settings->scatterPlotSeriesLength = 1;
	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	//Conversão para ARQUIVO PNG://
	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "Grafico_Func.png");
	DeleteImage(canvasReference->image);
}
//-------------------------------------------//
//----------------------------------------------------------------------------------------------------------//



//--------------------------------------------------Main--------------------------------------------------//
//----------------Entradas----------------//
int main()
{ 
   int quantidade;  // Ira nos indicar a quantidade de elementos.
   int j;
   printf("Qual a quantidade de elementos da Tabela? ");
   scanf("%d", &quantidade);
   double fx[quantidade];  // Valores de F(X) mostrados na tabela.
   double var[quantidade]; // Valores da variável em contraste com o F(X) na tabela. 
//----------------------------------------//  

//----------------Inserir Variavel----------------//
   printf("\nInsira os valores de D:\n");
   recebe_valores(quantidade,var); // Ira receber os valores do parâmetro da tabela.
   int i; 
   //Print:
   for(i=0; i<quantidade; i++)    // Atribui os valores.
   { printf("\n [%.2lf]", var[i]);
   }
//-----------------------------------------------//

//----------------Inserir Função-----------------//
   printf("\nInsira os valores de F(x):\n");
   recebe_valores(quantidade,fx); // Ira receber os valores de F(X) da tabela.
   //Print:
   for(i=0; i<quantidade; i++)
   { printf("\n [%.2lf]", fx[i]); // Atribui os valores.
   }
//-----------------------------------------------//

//----------------Plotagem----------------//  

    //Plotagem do Gráfico de Marcador Discreto//
    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
	series->xs = var;
	series->xsLength = 10;
	series->ys = fx;
	series->ysLength = 10;
	series->linearInterpolation = false;
	series->pointType = L"dots";
	series->pointTypeLength = wcslen(series->pointType);
	series->color = GetGray(1);
	ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
	settings->width = 1200;
	settings->height = 800;
	settings->autoBoundaries = true;
	settings->autoPadding = true;
    settings->title = L"Grafico Marcador Discreto";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"Tensao do Limite de Escoamento";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"Tamanho dos Graos";
    settings->yLabelLength = wcslen(settings->yLabel);
	ScatterPlotSeries *s [] = {series};
	settings->scatterPlotSeries = s;
	settings->scatterPlotSeriesLength = 1;
	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	DrawScatterPlotFromSettings(canvasReference, settings);
	//Conversão para ARQUIVO PNG://
	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "Grafico.png");
	DeleteImage(canvasReference->image);
//----------------------------------------//

//----------------Observações----------------//
//Estamos analisando a seguinte equação: F(x) = z + k*(1/sqrt(d))//
//g1(X) = 1.
//g2(x) = 1/sqrt(d)
//a1 = z
//a2 = k
//------------------------------------------//

//-----------------Somatorios-----------------//
   double sum_var       = 0;
   double sum_fx        = 0;
   double sum_var_fx    = 0;
   double sum_var_quadr = 0;
   
   for(i=0;i<quantidade;i++)
   { sum_var = sum_var + 1/sqrt(var[i]);              //Somatorio de 1/sqrt(d).
     sum_fx = sum_fx + fx[i];                         //Somatorio de f(x).
     sum_var_quadr = sum_var_quadr + 1/var[i];        //Somatorio de 1/d.
     sum_var_fx = sum_var_fx + 1/sqrt(var[i])*fx[i];  //Somatorio de 1/sqrt(d)*f(x).
   }
   
   //sum_var            //<g2,g1> ou <g1,g2>
   //sum_fx             //<g1,fx>
   //sum_var_fx         //<g2,fx>
   //sum_var_quadr      //<g2,g2> 

//-----------------Resolver e Encontrar Equação-----------------// 
   // [ <g1,fx> | <g1,g2> ]  
   // [ <g2,fx> | <g2,g2> ]  // Matriz A1.
   
   // [ <g1,g1> | <g1,fx> ]  
   // [ <g2,g1> | <g2,fx> ]  // Matriz A2.
   
   // [ <g1,g1> | <g1,g2> ]  
   // [ <g2,g1> | <g2,g2> ]  // Matriz A.
   
   //a1 = Det(A1)/Det(A)
   //a2 = Det(A2)/Det(A)
   
  double a1;
  double a2;
  a1 = ((sum_fx*sum_var_quadr) - (sum_var*sum_var_fx))/((quantidade*sum_var_quadr)-(sum_var*sum_var));
  a2 = ((quantidade*sum_var_fx) - (sum_fx*sum_var))/((quantidade*sum_var_quadr)-(sum_var*sum_var));
  printf("\nObservamos com isso que: F(n) = %.2lf + %.2lf * 1/sqrt(n)\n", a1, a2);
//----------------------------------------------------//

//------------------Resultado Tensao-------------------//
  double d = 0.05;
  double tensao = a1 + a2*(1/sqrt(0.05));
  printf("A tensao com Grao de 0,05 equivale em: %.4lf",tensao);
  //--------------------------------------------------//
  
//-----------------Plotagem-----------------//
  //Primeiro iremos inserir valores para serem adicionados nos gráficos:
  j = 0;
  double v;
  double resultado_fx[1050];
  double resultado_x[1050];
  for(v=0.006;v<0.105;v=v+0.0001)
  {  resultado_fx[j] = a1 + a2*(1/sqrt(v));
     resultado_x[j] = v;
     j++;
  }
  
  //Iremos agora plotar o gráfico individual:
  plot_2(resultado_x, resultado_fx);
  
//-----------------Calcular Ruido-----------------//
  //R(x) = [F(X) - G(X)]^2
  double gx[quantidade];
  double ruido = 0;
  for(i=0;i<quantidade;i++)
  { gx[i] = a1 + a2*(1/sqrt(var[i]));
    printf("\n [%.2lf]",ruido);
    ruido = ((fx[i] - gx[i])*(fx[i] - gx[i])) + ruido;
  }
  printf("\n [%.2lf]",ruido);
  printf("\nO R(X) apresentado equivale a %.4lf\n",ruido);
//-----------------------------------------------//
//----------------------------------------------------------------Parte_1_Finalizada----------------------------------------------------------------//
  return 0;
}
