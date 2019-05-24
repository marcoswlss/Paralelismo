#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include "Dijkstra.h"
#include "gravarNoArquivo.h"
const int KEY = 456;
const int itens = 100000;

void* t1(void* arg);
void* t2(void* arg);
double valor[itens];
	

	
	
	double medias,media,soma,vari,desvio,mediana,menorValor;
	double maiorValor=0;
	int sem	= sem_create(KEY, 1);
	
int main ()
{
	void *retval;
	srand (time(NULL));
	

	//fazer isso faz o codigo rodar mas nao sei se esta dentro do PAI
	for(int i=0;i < itens;i++)
	{
			
		valor[i]= (rand() % 100000)/100.0;
		medias = medias + valor[i];
		//printf("%f \n",valor[i]);
					
	}
	media = medias / itens; 
				
	int id =fork();			
	if (id!=0)
	{
		sleep(1);
			

		
	
		int id2 =fork();
		if (id2 !=0)
		{
			sleep(1);
			for(int i=0;i < itens;i++)
			{
				valor[i]= (rand() % 100000)/100.0;
				medias = medias + valor[i];
			}
			media = medias / itens; 
			//printf("media : %f \n",media);
			pthread_t thread_A,thread_B;
			pthread_create(&thread_A,NULL, &t1,NULL);
			pthread_create(&thread_B,NULL,&t2,NULL);
			pthread_join(thread_A, &retval);
			pthread_join(thread_B, &retval);
			sem_delete(sem);
			printf("Missão dada e missão cumprida.\n");
			
		//filho2
		}
		else
		{
			
				//mediana mais certinha
			/*for(i=0;i<itens-1;i++){
			for(j=i+1;j<itens;j++){
				
				if(valor[i] > valor[j]){
					
					aux = valor[i];
					valor[i] = valor[j];
					valor[j] = aux;
				}
			}
			}
			
			if(itens%2){
				 mediana = valor[itens/2];
			} else {
				 mediana = (valor[itens/2-1]+valor[itens/2])/2;
			}*/
			
		
		
		
		
			//mediana
			mediana = valor[itens/2-1];
			menorValor = valor[0];

			//maior valor
			for(int i=0;i < itens;i++){
			
				if(valor[i]> maiorValor){
					maiorValor= valor [i];
				} 
				
				}
		  //menor valor
			for(int i=0;i < itens;i++){
			
				if(valor[i]< menorValor){
					menorValor= valor[i];
				} 
				
			}
			//printf("menorValor : %f \n",menorValor);
			//printf("maiorValor : %f \n",maiorValor);
			//printf("mediana : %f \n",mediana);
			//P(sem);
			gravarNoArquivo("Menor Valor",menorValor);
			gravarNoArquivo("Maior Valor",maiorValor);
			gravarNoArquivo("Mediana",mediana);
			//sem_delete(sem);

		}
			//criando threads
	
	//filho 1
	}
	else
	{
		
		for(int i=0; i< itens ;i++){
			soma = soma+((valor[i]-media)*(valor[i]-media));
			
        }
        

		vari=soma/itens;

        //arrumar isso (tentei arrumar mas nao consigo puxar da lib o sqrt) 
		desvio=sqrt(vari);
		//printf("Desvio : %f \n",desvio);
		//printf("variancia : %f \n",vari);
		
		gravarNoArquivo("Desvio",desvio);
		gravarNoArquivo("Variancia",vari);
	}

			
	
		
		return 0;
	}
	
	
	//ps ainda tenho q achar a lib de salvar no hd n to afim de escrever ela na mao *-*
	void* t1(void* arg){
		double soma,vari,desvio;
		for(int i=0; i< itens ;i++){
			soma = soma+((valor[i]-media)*(valor[i]-media));
        }
		vari=soma/itens;
        desvio=sqrt(vari);
       // printf("Vari T : %f \n",vari);
		//printf("Desvio T: %f \n",desvio);
		P(sem);
		gravarNoArquivo("Variancia da thread",vari);	
		gravarNoArquivo("Desvio da thread",desvio);
		V(sem);
	return NULL;
	}
	
	
//thread2-B
void* t2(void* arg)
{
	double menorValor,mediana;
	double maiorValor=0;
	//mediana
	mediana = valor[itens/2-1];

//maior valor
	for(int i=0;i < itens;i++)
	{
	
		if(valor[i]> maiorValor)
		{
			maiorValor= valor [i];
		} 
		
	}
//menor valor
	menorValor = valor[0];
	for(int i=0;i < itens;i++)
	{
	
		if(valor[i]< menorValor){
			menorValor= valor[i];
		} 	
	}
	//printf("Menor valor t : %f \n",menorValor);
	//printf("maior valor t: %f \n",maiorValor);
	//printf("mediana t %f \n",mediana);
	P(sem);
	gravarNoArquivo("Menor Valor da thread",menorValor);	
	gravarNoArquivo("Maior Valor da thread",maiorValor);
	gravarNoArquivo("Mediana da thread",mediana);
	V(sem);
	return NULL;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

		
	

