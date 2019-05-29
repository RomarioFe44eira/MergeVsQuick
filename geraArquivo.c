#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Editado Por Romário
//Modificado em 18/03/2018

int main(){
	srand((unsigned) time(NULL));
	FILE *ordenado, *invertido, *randomico;
	int tam, x;
	char nomeArquivo[255];
	printf("Informe o tamanho do arquivo ");
	scanf("%d", &tam);
	//Ordenado
	sprintf(nomeArquivo, "Ordenado%05d.txt", tam);
	ordenado = fopen(nomeArquivo, "w");  
		for (x=1;x<=tam;x++){
			fprintf(ordenado, "%d\n", x);
		}
	fclose(ordenado);

	//Invertido
	sprintf(nomeArquivo, "Invertido%05d.txt", tam);
	invertido = fopen(nomeArquivo, "w");
		for (x=tam;x>=1;x--){
			fprintf(invertido, "%d\n", x);
		}
	fclose(invertido);


	//Randomico
	sprintf(nomeArquivo, "Randomico%05d.txt", tam);
	randomico = fopen(nomeArquivo, "w");
		for(x=1; x<=tam; x++){
			fprintf(randomico, "%d\n", rand());
		}
	fclose(randomico);
    return 0;
}