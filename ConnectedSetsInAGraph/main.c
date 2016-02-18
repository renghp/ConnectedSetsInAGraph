#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamanhoGrafo 11	//TROQUE O NUMERO DE VERTICES AQUI!!!
#define true 1
#define false 0


//algoritmo de Renan Luigi Martins Guarese
//algoritmo de busca em profundidade retirado da disciplina de Estrutura de Dados da UFRGS


static int max;
int cont;
int posicao[tamanhoGrafo];			//infelizmente nao consegui fazer funcionar declarar os 
static int maiores[tamanhoGrafo];		//vetores e matrizes com a variavel "max" lida do arquivo
static  int grafo[tamanhoGrafo][tamanhoGrafo];	

void insereNaMatriz(char *umaLinha){

    	char * posi;
	int entraresta, saiaresta;

   	posi = strtok(umaLinha, " ()");
	saiaresta = atoi(posi);
	//printf("\nAresta: %d ", saiaresta);
	
	while(posi != NULL)
	{
		
		posi = strtok(NULL, " ()\n\t\0");
		//printf("%s", posi);
		if (posi!=NULL)
		{
			entraresta = atoi(posi);
			//printf("%d ", entraresta);
			grafo[saiaresta][entraresta]=1;
			
		}
	}
}

void leArquivo()
{



static const char nomeArquivo[] = "grafo.txt";
   FILE *arquivo = fopen ( nomeArquivo, "r" );
   if ( arquivo != NULL )
   {
      char linha [200]; 
	//char * pch;
	
	fgets ( linha, sizeof linha, arquivo);	//ignora a primeira linha
	
	max = atoi( fgets ( linha, sizeof linha, arquivo ));		//define o valor da segunda linha como "max"  									// max = numero de vertices do grafo
int i, j;
 
  for(i=0;i<max;i++)	//para inicializar o grafo com 0
    for(j=0;j<max;j++)
      grafo[i][j]=0;

      while ( fgets ( linha, sizeof linha, arquivo) != NULL ) //vai passando as linhas
      {
	insereNaMatriz(linha);
	
      }
      fclose (arquivo );
   }
   else
   {
      perror ( nomeArquivo ); // indica um erro caso o arquivo nao abra
   }

}



	

void visita (int vis[max], int v)
{
     printf(" %d",v);
     vis[v]= true;
}

void buscaProf (int grafo[max][max], int v, int vis[max])
{
    int w;
    visita(vis,v);
    for(w = 0; w<max ; w++)    //percorre os vértices adjacentes a v
      if ((grafo[v][w]== 1) && (vis[w]==false))  //encontra um vértice adjacente a v que ainda nao tenha sido visitado
        {
            buscaProf(grafo, w, vis); //chamada recursiva para o vértice adjacente a v
            cont++;			//incrementa o contador de posicao
            posicao[v]=cont;
        }
}


void bubbleSort (int *maiores, int posicaoTemp[max], int n) {       //funcao bubble sort retirada de http://rosettacode.org/wiki/Bubble_Sort#C e modificada por Renan Guarese para ordenar o vetor 'maiores' de acordo com o vetor 'posicao'
    int i, t, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < n; i++) {
            if (posicao[i] > posicao[i - 1]) {
                t = maiores[i];
                maiores[i] = maiores[i - 1];
                maiores[i - 1] = t;
                s = 1;
                t = posicaoTemp[i];
                posicaoTemp[i] = posicaoTemp[i - 1];
                posicaoTemp[i - 1] = t;
                s = 1;
            }
        }
    }
}

void organizaMaiores(int posicao[max], int maiores[max])
{
    int i, j, maior=0;

    for (i=0; i<max; i++)
    {
        maiores[i] = i;
    }
//printf("foi1");
    bubbleSort(maiores, posicao, max);
//printf("foi2");

}

void inverteGrafo(int grafo[max][max])      //espelha a matriz
{
    int i, j, k;

    for (i = 0; i<max; i++)
        for (j=0; j<max; j++)
    {
        if (i>j)
        {
            k = grafo[i][j];
            grafo[i][j] = grafo[j][i];
            grafo[j][i] = k;
        }

    }
//printf ("%d", grafo[0][1]);
    //return grafo;
}

void imprimeNaOrdemMaiores(int grafo[max][max], int maiores[max], int posicao[max], int vis2[max])
{
printf("\nComponentes Conexos do Grafo:\n{ ");
    int i;
    for (i=0; i<max; i++)
    {


        if (vis2[maiores[i]]==false)
        {
            printf("{");
            buscaProf(grafo,maiores[i], vis2);
            printf(" } ");
        }
    }

printf("}\n\n");
}


int main()
{

leArquivo();		//le o arquivo e ja salva os arestas do grafo na matriz

char ass;

printf("Trabalho de Renan Luigi Martins Guarese\nFavor ler o arquivo \"leia-me\" antes de prosseguir! \nAperte Qualquer Tecla para Continuar\n");
scanf("%c", &ass);



for (cont=0; cont<max; cont++)
    posicao[cont]=0;

cont = 0;



    int i,j;

    int vis[max];
    int vis2[max];


 



    for (i=0;i<max;i++)
        vis[i]=false; //inicializando vetor de vertices visitados

    for (i=0;i<max;i++)
        vis2[i]=false; //inicializando vetor de vertices visitados



puts("Caminhamentos em Profundidade a partir de cada vertice do Grafo\n(usando sempre a mesma lista de vertices visitados):");
    for (i=0; i<max; i++)		//faz uma busca em profundidade a partir de cada vertice do grafo 
{					//para ter certeza de que percorreu todo o grafo e poder gravar 
    buscaProf(grafo,i, vis);		//no vetor posicao a quantidade de vezes que cada vertice é acessado
	printf("\n");    		
}

//buscaProf(grafo,0, vis);

printf("\n");


    inverteGrafo(grafo);    //inverte o grafo (espelha sua matriz) para percorrermos ele ao contrario e achar os componentes conexos



   organizaMaiores(posicao, maiores);		//organiza o vetor maiores de forma que ele esteja em ordem crescente 
						//em relação ao vetor posicao (bubble sort muito louco)


//for (i=0; i<max; i++)                                 //imprime a lista com os maiores ja organizados
//   printf ("maiores[%d] = %d\n", i, maiores[i]);

//   for (i=0; i<max; i++)                              //imprime a lista com os coeficientes de posicao
//   printf ("\nposicao[%d] = %d", i, posicao[i]);





imprimeNaOrdemMaiores(grafo,maiores,posicao,vis2);	//faz uma busca em profundidade no grafo invertido na ordem dada pelo vetor posicao
							//isso vai fazer com que sejam impressos na tela todos os componentes conexos

    for (i=0;i<max;i++)		//zera novamente as listas de vertices visitados
    {   vis[i]=false;
        vis2[i]=false;
    }
         


inverteGrafo(grafo);    //inverte o grafo de volta ao normal


    //system("PAUSE");


}
