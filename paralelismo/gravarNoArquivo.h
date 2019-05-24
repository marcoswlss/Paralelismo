#include <stdio.h>
void gravarNoArquivo(const char* nomeCampo,double valor);

/*int main (){
	
	gravarNoArquivo("maximo",123.123);
	gravarNoArquivo("minimo",444.222);
	gravarNoArquivo("xpto",666.655);
	return 0;
	
}*/

void gravarNoArquivo(const char* nomeCampo,double valor){
	
	FILE * pArquivo;
	pArquivo =fopen("meu_arquivo.txt","a");
	if(pArquivo != NULL){
		fprintf(pArquivo, "%s =[%lf]\n", nomeCampo,valor);
		
	}
	fclose(pArquivo);
}

