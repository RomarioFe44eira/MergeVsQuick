#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Randomico1000000.txt
//Randomico750000.txt
//Randomico500000.txt

//Invertido1000000.txt
//Invertido750000.txt
//Invertido500000.txt

//Ordenado1000000.txt
//Ordenado750000.txt
//Ordenado500000.txt

#define CASO "Ordenado"
#define BASE_DIR "c:\\test\\Ordenado500000.txt"
#define DIR_LOG "c:\\test\\LogComparacoes.txt"

int bubbleSort(int *vetor, int tamanho);
int insertSort(int *vetor, int tamanho);
int selectSort(int *vetor, int tamanho);
int shellSort(int *vetor, int tamanho);
int particiona(int *v, int ini, int fim, int *aux);
void quickSort(int *v, int ini, int fim, int *aux);

void mergesort(int *v, int start, int end, int *aux);
void merge(int *v, int start, int middle, int end, int *aux);
void peneira(int *vet, int raiz, int fundo);
void heapsort(int *vet, int n);
void radixsort(int *vetor, int tamanho);
int performLog(char *algoritmo, int tamanho, double tempo);

double calculaTempo(int tempoInicial, int tempoFinal){
	return ((double)(tempoFinal - tempoInicial)*1000)/(double)CLOCKS_PER_SEC;
}
int performLog(char *algoritmo, int tamanho, double tempo){
	
	FILE *arquivo;	
	arquivo = fopen(DIR_LOG, "a");
	fprintf(arquivo, "Algoritmo: %s Sort | Tamanho:%d rows | Tempo: %.2f Milisegundos | %s \n", algoritmo, tamanho, tempo, CASO);	
	printf("Arquivo de log foi atualizado!.\n");
	return 0;
}
int existeArquivo(char *nome){
	FILE *arquivo;
	arquivo = fopen(nome, "r" );
	if(arquivo){
		fclose(arquivo);
		return 1;
	}
	return 0;
}

//ALGORITMOS DE ORDENAÇÃO.
int bubbleSort(int *vetor, int tamanho){    
	int i, continua, aux, rows = tamanho;
	clock_t tempoInicial, tempoFinal;   
    double tempo_gasto;		
	
    tempoInicial = clock();
    do{
        continua = 0;
        for(i = 0; i < tamanho-1; i++){
            if(vetor[i] > vetor[i+1]){
                aux = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux;                
                continua = i;
            }
        }
        tamanho--;
    }while(continua != 0);
    tempoFinal = clock();
	
    tempo_gasto = calculaTempo(tempoInicial, tempoFinal);	
	performLog("Bubble", rows, tempo_gasto);
    
	for(i = 0; i < tamanho; i++){       
        printf("%d\n", vetor[i]);
    }     
    printf("Rows: %d | Tempo Decorrido: %.2f ms", rows, tempo_gasto);         
    return 0;
}
int insertSort(int *vetor, int tamanho){	
	int i, j, aux, rows = tamanho;	    
	for(i = 1; i < tamanho; i++){
        aux = vetor[i];		
        for(j = i; (j > 0) && (aux < vetor[j-1]); j--)
            vetor[j] = vetor[j-1];        
        vetor[j] = aux;
    }
	return 0;
}
int selectionSort(int *vetor, int tamanho){
	int i, j, menor, troca, rows = tamanho;		
	for(i==0; i < tamanho-1;i++){
		menor = i;
		for(j = i+1; j<tamanho; j++){
			if(vetor[j] < vetor[menor])
				menor = j;
		}
		if(i != menor){
			troca = vetor[i];
			vetor[i] = vetor[menor];
			vetor[menor] = troca;
		}
	}	
	return 0;
}
int shellSort(int *vetor, int tamanho){    
    int i , j , gap, valor;		
    for (gap = tamanho/2; gap > 0; gap /= 2){
        for (i = gap; i < tamanho; i++){
            for (j = i-gap; j >= 0 && vetor[j] > vetor[j+gap]; j-=gap){
                valor = vetor[j+gap];
                vetor[j+gap] = vetor[j];
                vetor[j] = valor;
            }
		}	
	}	
    return 0;
}

int particiona(int *v, int ini, int fim, int *aux){	
	int pivo = v[fim];
	//printf("v[fim]: %d| aux: %d| Ini: %d | fim: %d \n", v[fim], aux, ini, fim);
	
	while(ini<fim){
		while( (ini < fim) && (v[ini] <= pivo) ) 
			ini++; 
		while( (ini < fim) && (v[fim] > pivo) ) 
			fim--; 
		if(ini < fim){  
			aux = (int *)v[ini];
			v[ini] = v[fim];
			v[fim] = (int)aux;
			//printf("AUX: %d\n", aux);
		}
	}	
	return ini;
}
void quickSort(int *v, int ini, int fim, int *aux){	
	if(ini < fim){				
		int meio = particiona(v, ini, fim, aux);
		quickSort(v,ini, meio-1, aux);
		quickSort(v,meio, fim, aux);
	}	
}

void merge(int *v, int start, int middle, int end,int *aux) {
	int i, p1, p2;
	
	p1 = start;     
	p2 = middle+1;  
	i = start;   
	while (p1<=middle && p2<=end) {
		
		if (v[p1] <= v[p2])
			aux[i++] = v[p1++];  
		else
			aux[i++] = v[p2++];
	}
	while (p1<=middle)
		aux[i++] = v[p1++];   
	while (p2<=end)
		aux[i++] = v[p2++];

	for (i=start; i<=end; i++)
		v[i] = aux[i]; 
}
void mergesort(int *v, int start, int end,int *aux) {
	int middle;
	
	if (start < end) {              
		middle = (start+end)/2;       
		mergesort(v, start, middle, aux);   
		mergesort(v, middle+1, end, aux);   
		merge(v, start, middle, end, aux);  
	}
}
void heapsort(int *vet, int n) {
	int i, tmp;
	for (i = (n / 2); i >= 0; i--) {
		peneira(vet, i, n - 1);
	}
	for (i = n-1; i >= 1; i--) {
		tmp = vet[0];
		vet[0] = vet[i];
		vet[i] = tmp;
		peneira(vet, 0, i-1);
	}
}
void peneira(int *vet, int raiz, int fundo) {
	int pronto, filhoMax, tmp;
	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		}
		else if (vet[raiz * 2] > vet[raiz * 2 + 1]) {
			filhoMax = raiz * 2;
		}
		else {
			filhoMax = raiz * 2 + 1;
		}

	if (vet[raiz] < vet[filhoMax]) {
		tmp = vet[raiz];
		vet[raiz] = vet[filhoMax];
		vet[filhoMax] = tmp;
		raiz = filhoMax;
    }
	else {
      pronto = 1;
	}
  }
}
void radixsort(int *vetor, int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }
    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }
    free(b);
}

int menuPrincipal(){
    int escolha = 0;
    do{        
        printf("Ordenar por: \n");
        printf("1 - Bubble Sort\n");
        printf("2 - Insertion Sort\n");
        printf("3 - Selection Sort\n");
		printf("4 - Shell Sort\n");
		printf("5 - Quick Sort\n");
		printf("6 - Merge Sort\n");
		printf("7 - Heap Sort\n");
		printf("8 - Radix Sort\n");
        printf("9 - Cancelar\n\n");
        printf("Informe sua escolha: ");
        scanf("%d", &escolha);
    }while(escolha <0 && escolha > 9);
    return escolha;      
}
int main(){
	char dir[255];			
    do{
        printf("Informe o diretorio do arquivo a ser Ordenado: ");
        gets(dir);
        if(strlen(dir) == 0){            
            strcpy(dir, BASE_DIR);
        }       
        existeArquivo(dir) != 1 ?printf("Diretorio do arquivo invalido!\n"): printf("Arquivo localizado..\n");            
    }while(existeArquivo(dir) != 1);
	
	FILE *ptr_arquivo = NULL;
	ptr_arquivo = fopen(dir, "r");
	(!ptr_arquivo)?printf("Erro ao abrir o arquivo!\n"):printf("Arquivo Aberto com sucesso para leitura.\n");
	
	
	int fileSizeRows = 0, *vetor, *tmp, i;
    char aux[25];

    while(fgets(aux, sizeof(aux), ptr_arquivo) != NULL){ 
		fileSizeRows++;
	}

	vetor = (int *) calloc(fileSizeRows, sizeof(int));
	tmp = (int *) calloc(fileSizeRows, sizeof(int));
	
	if(tmp == NULL || vetor == NULL){
		printf("Memoria insuficiente\n");
		exit(EXIT_FAILURE);
	}
	
	rewind(ptr_arquivo);
	
    for(i = 0; i < fileSizeRows; i++){
		fgets(aux, sizeof(aux), ptr_arquivo);
		vetor[i] = atoi(aux);
	}	
	
	clock_t tempoInicial, tempoFinal;   
    double tempo_gasto;	
	tempoInicial = clock();
	
	char tipoOrdenacao[30];
	
	switch(menuPrincipal()){
        case 1:
			strcpy(tipoOrdenacao, "Bubble");
			bubbleSort(vetor, fileSizeRows);
		break;        
		case 2:
			strcpy(tipoOrdenacao, "Insert");
			insertSort(vetor,fileSizeRows);break;		
		case 3:
			strcpy(tipoOrdenacao, "Selection");
			selectionSort(vetor,fileSizeRows);
		break;
		case 4:
			strcpy(tipoOrdenacao, "Shell");
			shellSort(vetor,fileSizeRows);
		break;
		case 5:
			strcpy(tipoOrdenacao, "Quick");
			quickSort(vetor, 0,fileSizeRows, tmp);
		break;
		case 6:
			strcpy(tipoOrdenacao, "Merge");
			mergesort(vetor, 0, fileSizeRows, tmp);
		break;
		case 7:
			strcpy(tipoOrdenacao, "Heap");
			heapsort(vetor, fileSizeRows);
		break;
		case 8:
			strcpy(tipoOrdenacao, "Radix");
			radixsort(vetor, fileSizeRows);
		break;
		
		case 9:
			printf("Cancelamento solicitado\n");
			exit(1);
		break;		
    }

	tempoFinal = clock();	
    tempo_gasto = calculaTempo(tempoInicial, tempoFinal);	
	printf("Ordenacao Concluida.\n");
	performLog(tipoOrdenacao, fileSizeRows, tempo_gasto);
	printf("Algoritmo: %s | tempo: %f | Linhas: %d \n", tipoOrdenacao, tempo_gasto, fileSizeRows);
	
	
	fclose(ptr_arquivo);
    return 0;
}