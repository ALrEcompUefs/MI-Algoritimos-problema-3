/*
Autor: Alisson Rodrigues de Carvalho Santos
Componente Curricular: Algoritmos e programação I
Concluido em: 27/12/2018
Declaro que este código foi elaborado por mim de forma individual e não contém nenhum
trecho de código de outro colega ou de outro autor, tais como provindos de livros e
apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código
de outra autoria que não a minha está destacado com uma citação para o autor e a fonte
do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
typedef struct trabalho {		//struct usada para os trabalhos antes de serem avaliados
       int codigo;
       char titulo_trabalho[400];
       char area_conhecimento[200];
       char autor[200],orientador[200];
       char coautor[200],coorientador[200];
	   char situacao_trabalho[50];
	   int Nota;      
}Trabalho;
typedef struct lista{		//celula da lista encadeada
	Trabalho dados;
	struct lista *proximo;
}Lista;
/*Prototipos para as funções principais*/
void avaliar_trabalhos(Lista *p1,int qtd_trabalhos,int *cont_trabalhos_aprovados,Trabalho vetor_auxiliar[]);
int escreve_trabalhos_aprovados(Trabalho vetor_aux[],int contador);
void reescreve_trabalhos_submetidos(Lista *p1,int cont_trabalhos);
void escreve_programacao(Lista *p1,int qtd_trabalhos);
Lista *leitura_programacao(Lista *p1,int *qtd_trabalhos);
void programacao_por_dia(Lista *p2,int qtd_trabalhos);
void programacao_por_area(Lista *p2,int qtd_trabalhos);
int retirar_trabalho(Lista *p1,int qtd_trabalhos);
/*Portotipos de funções de apoio*/
Lista *Leitura_de_dados_1(Lista *p1, int *qtd_trabalhos);
int  ordena_vetor(Trabalho vetor_aux[],int qtd_trabalhos);
Lista *reorganiza_lista(Lista *p1,Trabalho vetor_aux[],int qtd_trabalhos);
Lista *leitura_trabalhos_aprovados(Lista *p1,int *qtd_trabalhos);
void informa_usuario();
/*prototipos para funções da lista encadeada*/
Lista *inicializa();
Lista  *insere_no_final(Lista *p1, Trabalho cadastro);
void imprime_lista(Lista *p1);
void libera(Lista *p1);
Lista *busca(Lista *p1,int codigo);
Lista *retira(Lista *p1,int codigo);

int main(){
        int escolha_menu_principal,quantidade_trabalhos=0,cont_trabalhos_aprovados=0,cont_trabalhos_programacao,escolha_submenu;
    	Lista *p1_cadastros; 			//ponteiro para o primeiro elemento da lista de cadastros
    	Trabalho *vetor_auxiliar;	    //vetor auxiliar usado na ordenação da lista
    	Lista *p2_trabalhos;				//Lista encadeada dos dados da programação
        int checagem; 					//variavel de apoio para checar a ocorrencia de erros em funções 1
        	setlocale(LC_ALL,"portuguese");
           do{
           		printf("Sistema de submissão de trabalhos para o semic\n");
            	printf("1-)Avaliar trabalhos\n2-)Consultar programacao\n3-)Remover trabalho\n4-)Instruções ao usuario\n5-)Sair do programa\n");
            	printf("Escolha: ");
            	scanf("%d",&escolha_menu_principal);
            	switch(escolha_menu_principal){
                     case 1:
                     	system("cls");
                     	p1_cadastros=Leitura_de_dados_1(p1_cadastros,&quantidade_trabalhos);
                     	/*aloca o vetor_axiliar para o total de trabalhos lidos*/
                     	vetor_auxiliar=(Trabalho*) malloc(quantidade_trabalhos*sizeof(Trabalho));
                     	avaliar_trabalhos(p1_cadastros,quantidade_trabalhos,&cont_trabalhos_aprovados,vetor_auxiliar);
                     	if(cont_trabalhos_aprovados!=0){
                     		reescreve_trabalhos_submetidos(p1_cadastros,quantidade_trabalhos);
                     		p1_cadastros=reorganiza_lista(p1_cadastros,vetor_auxiliar,cont_trabalhos_aprovados);
                     		escreve_programacao(p1_cadastros,cont_trabalhos_aprovados);
						 }
                     	libera(p1_cadastros);
                     	free(vetor_auxiliar);
                     	printf("Os arquivos serão atualizados\n\n reinicie o programa\n");
                     	exit(1);
                        break;
                     case 2:
                     	system("cls");
                     	p2_trabalhos=inicializa();
                     	p2_trabalhos=leitura_programacao(p2_trabalhos,&cont_trabalhos_programacao);
                     	printf("[1]-Progamação por dia\n[2]-Programação por area de conhecimento\n");
                     	printf("Escolha: ");
                     	scanf("%d",&escolha_submenu);
                     	switch(escolha_submenu){
                     		case 1:
                     			programacao_por_dia(p2_trabalhos,cont_trabalhos_programacao);
                     			break;
                     		case 2:
                     			programacao_por_area(p2_trabalhos,cont_trabalhos_programacao);
							 	break;	
						 }
            			system("pause");
            			system("cls");
            			libera(p2_trabalhos);
                          break;
                     case 3:
                     	system("cls");
                     	p1_cadastros=leitura_trabalhos_aprovados(p1_cadastros,&cont_trabalhos_aprovados);//ok
                     	retirar_trabalho(p1_cadastros,cont_trabalhos_aprovados);
                     	libera(p1_cadastros);
                     	system("cls");
                     	printf("\nOs arquivos serão atualizados\n\n reinicie o programa");
                     	exit(1);
                          break;
                     case 4:
                     	informa_usuario();
                          break;
                     case 5:
                     	//sai do programa
                          break;	     
                     default:
                          break; 
              }                                   
           }while(escolha_menu_principal!=5); 
	return 0;
} 
/* Inicializa a lista*/
Lista *inicializa(){
	return NULL;
}
/* Adiciona um novo elemento no inicio da lista*/
Lista  *insere_no_final(Lista *p1, Trabalho cadastro){	//p1 é o ponteiro para o primeiro item da lista
	Lista *nova,*aux;
	
		if(p1==NULL){		//caso não exista elementos na lista o novo elemento é o primeiro
			p1=(Lista *) malloc(sizeof(Lista));
			if(p1==NULL){
				printf("erro na alocação de memoria");
				exit(1);
			}
			p1->dados=cadastro;
			p1->proximo=NULL;
			return p1;
		}
		else{
			nova=(Lista *) malloc(sizeof(Lista)); //cria a nova celula
			if(nova==NULL){
				printf("erro na alocacao de memoria");
				exit(1);
			}
			aux=p1;
			while(aux->proximo!=NULL){ //procura o fim da lista
				aux=aux->proximo;
			}
			nova->dados=cadastro;
			aux->proximo=nova; 		// nova deve apontar para NULL ou o proximo elemento
			nova->proximo=NULL;				// p deve apontar para o novo primeiro elemento
			return p1; 
		}
}
/* Imprime toda lista*/
void imprime_lista(Lista *p1){
	Lista *aux;
	
		if(p1==NULL){
			printf("a lista esta vazia\n");
		}
		else{
			printf("Trabalhos submetidos\n");
			aux=p1;
			while(aux != NULL){
				printf("%d\n",aux->dados.codigo);
				puts(aux->dados.titulo_trabalho);
				puts(aux->dados.area_conhecimento);
				puts(aux->dados.autor);
				puts(aux->dados.orientador);
				puts(aux->dados.coautor);
				puts(aux->dados.coorientador);
				printf("%s",aux->dados.situacao_trabalho);
				printf("%d\n",aux->dados.Nota);
				aux=aux->proximo;
				puts("-----------------------------------------------------");
			}
		}
}
/* Destroi a lista encadeada e libera a meoria que era utilizada*/
void libera(Lista *p1){
	Lista * aux;
		while (p1 != NULL)
		{
			aux = p1;
			p1= p1->proximo;	
			free(aux);
		}
}
/*Busca e retorna o ponteiro para o item selecionado*/
Lista *busca(Lista *p1,int codigo){
	
	Lista *auxiliar;
	auxiliar=p1;
		while(auxiliar->dados.codigo!= codigo && auxiliar!=NULL){
			auxiliar=auxiliar->proximo;
		}
		if(auxiliar==NULL)
			return NULL;
		else{
			return auxiliar;
		}
				
}
/*retira uma celula da lista*/
Lista *retira(Lista *p1,int codigo){
	Lista  *aux_1, *aux_2;
		
		if(p1==NULL){
			printf("A lista esta vazia!!");
			return NULL;
		}	
		aux_1=p1;
		aux_2=aux_1->proximo;
		while(aux_2->dados.codigo != codigo && aux_2!=NULL){
			aux_1=aux_2;
			aux_2=aux_2->proximo;
		}
		if(aux_2==NULL){
			printf("elemento não encontrado");
		}
		else{
			aux_1->proximo=aux_2->proximo;
			free(aux_2);
		}
		return p1;		
}
/*Função leitura de dados 1
	realiza a leitura dos dados do arquivo de texo*/
Lista *Leitura_de_dados_1(Lista *p1, int *qtd_trabalhos){
	int i;
	FILE *arquivo_1;
	Trabalho auxiliar; 	// recebe os valores lidos temporariamente
	
		p1=inicializa();	//inicializa a lista encadeada
		if((arquivo_1=fopen("trabalhos submetidos.txt","r"))==NULL){
			printf("Erro na abertura do arquivo!!\n");
			exit(1);
		}
		fscanf(arquivo_1,"%d",qtd_trabalhos);
		for(i=0;i<(*qtd_trabalhos);i++){
			fscanf(arquivo_1,"%d",&auxiliar.codigo);
			fgetc(arquivo_1);
			fgets(auxiliar.titulo_trabalho,400,arquivo_1);
			fgets(auxiliar.area_conhecimento,400,arquivo_1);
			fgets(auxiliar.autor,400,arquivo_1);
			fgets(auxiliar.orientador,400,arquivo_1);
			fgets(auxiliar.coautor,400,arquivo_1);
			fgets(auxiliar.coorientador,400,arquivo_1);
			fgets(auxiliar.situacao_trabalho,50,arquivo_1);
			p1=insere_no_final(p1,auxiliar);
		}
		return p1;
}	
/* Função avaliar trabalhos
	exibe os trabalhos para recebrem um conceito e uma nota*/
void avaliar_trabalhos(Lista *p1,int qtd_trabalhos,int *cont_trabalhos_aprovados,Trabalho vetor_auxiliar[]){
	Lista *aux;
	int i,j,escolha,checagem;	
	int nota;
		aux=p1;
		j=0;
		for(i=0;i<qtd_trabalhos;i++){
			if((checagem=strcmp(aux->dados.situacao_trabalho,"\n")==0)){
				/* Imprime o trabalho*/
				printf("%d\n",aux->dados.codigo);
				puts(aux->dados.titulo_trabalho);
				puts(aux->dados.area_conhecimento);
				puts(aux->dados.autor);
				puts(aux->dados.orientador);
				puts(aux->dados.coautor);
				puts(aux->dados.coorientador);
				printf("%s",aux->dados.situacao_trabalho);
				/*pergunta se o trabalho foi aprovado*/
				printf("Informe a situação do trabalho\n[1]Aprovado\n[2]Reprovado\n");
				printf("escolha: ");
				scanf("%d",&escolha);
				switch(escolha){
						case 1:
							strcpy(aux->dados.situacao_trabalho,"aprovado\n");
							printf("Informe a nota: ");
							getchar();
							scanf("%d",&nota);
							aux->dados.Nota=nota;
							(*cont_trabalhos_aprovados)++;
							/*copia o elemento que foi aprovado para o vetor*/
							vetor_auxiliar[j]=aux->dados;
							j++;
							break;
						case 2:
							strcpy(aux->dados.situacao_trabalho,"reprovado\n");
							break;	
						default:
								break;	
					}
			}
			aux=aux->proximo;
			system("cls");
		}
		if(*cont_trabalhos_aprovados==0){
			printf("Nenhum trabalho aprovado!!");
		}
		else{
			/*chama a função que escreve os trabalhos aprovados*/
			ordena_vetor(vetor_auxiliar,*cont_trabalhos_aprovados);	//ordena o vetor
			escreve_trabalhos_aprovados(vetor_auxiliar,*cont_trabalhos_aprovados); //escreve os trabalhos já ordenados
		}
}
/* Função escreve trabalhos aprovados
	escreve os trabalhos avaliados no arquivo de texto*/
int escreve_trabalhos_aprovados(Trabalho vetor_aux[],int contador){
	int i=0,j;
	int checagem; //recebe o resultado da comparação de strings
	FILE *arquivo_2;
		if(contador==0){
			return 1;
		}
		/*Abre/cria o arquivo de texto que vai receber os trabalhos aprovados*/
		if((arquivo_2=fopen("Trabalhos avaliados.txt","w"))==NULL){
			printf("Erro na abertura do arquivo!!\n");
			exit(1);
		}
		fprintf(arquivo_2,"%d\n",contador); 	//escreve a quantidade de trabalhos aprovados	
		for(i=0;i<contador;i++){
			fprintf(arquivo_2,"%d\n",vetor_aux[i].codigo);
			fputs(vetor_aux[i].titulo_trabalho,arquivo_2);
			fputs(vetor_aux[i].area_conhecimento,arquivo_2);
			fputs(vetor_aux[i].autor,arquivo_2);
			fputs(vetor_aux[i].orientador,arquivo_2);
			fputs(vetor_aux[i].coautor,arquivo_2);
			fputs(vetor_aux[i].coorientador,arquivo_2);
			fputs(vetor_aux[i].situacao_trabalho,arquivo_2);
			fprintf(arquivo_2,"%d\n",vetor_aux[i].Nota);
		}
		fclose(arquivo_2);
    return 0;		
}
/*Função reescreve_trabalhos_subtemidos
	recebe os trabalhos que foram avaliados e os reescreve com a situção de aprovado ou reprovado*/
void reescreve_trabalhos_submetidos(Lista *p1,int cont_trabalhos){
	FILE * arquivo_1;
	int i;
	Lista *aux;
			if((arquivo_1=fopen("Trabalhos submetidos.txt","w"))==NULL){
				printf("Erro na abertura do arquivo!!");
				exit(1);
			}
			aux=p1;
			fprintf(arquivo_1,"%d\n",cont_trabalhos);
			for(i=0;i<cont_trabalhos;i++){
				fprintf(arquivo_1,"%d\n",aux->dados.codigo);
				fputs(aux->dados.titulo_trabalho,arquivo_1);
				fputs(aux->dados.area_conhecimento,arquivo_1);
				fputs(aux->dados.autor,arquivo_1);
				fputs(aux->dados.orientador,arquivo_1);
				fputs(aux->dados.coautor,arquivo_1);
				fputs(aux->dados.coorientador,arquivo_1);
				fputs(aux->dados.situacao_trabalho,arquivo_1);
				aux=aux->proximo;
			}	
			fclose(arquivo_1);
}
/*Função ordenar vetor	
	ordena o vetor com os trabalhos aprovados utilizando do algoritmo select short*/
int  ordena_vetor(Trabalho vetor_aux[],int qtd_trabalhos){
	int i,j,maior;
	Trabalho aux;
		for(i=0;i<qtd_trabalhos-1;i++){
			maior=i; //a posição atual de i é posta para ser o maior valor
			for(j=i+1;j<qtd_trabalhos;j++){ 	//procura o maior elemento apartir do elemento depois do maior
				if((vetor_aux[j].Nota)>(vetor_aux[maior].Nota)){
					maior=j;	//a posição maior nota é selecionada
				}
			}
			aux=vetor_aux[maior];	//aux recebe a struct com a maior nota
			vetor_aux[maior]=vetor_aux[i];	// a strcut com uma nota menor é trocada para posição da strcut com a maior nota
			vetor_aux[i]=aux;	//a posição i recebe a maior nota
		}
	return 0;
}
/* Função reogarniza lista
	libera a lista encadeada e a recria apenas com os trabalhos aprovados*/
Lista *reorganiza_lista(Lista *p1,Trabalho vetor_aux[],int qtd_trabalhos){
	int i,j,area,codigo;
	char area_conhecimento_char[7][100]={"1-Ciencias da Saude\n","2-Ciencias Exatas\n","3-Ciencias Agrarias\n","4-Engenharias\n","5-Ciencias Sociais Aplicadas\n",
								"6-Ciencias Humanas\n","7-Linguistica, Letras e Artes\n"};
	int area_conhecimento_convertida[7];
	Trabalho *vetor_aux2;
		/*Libera a lista encadeada*/
		libera(p1);
		p1=inicializa();
		/*Converte as strings para um valor interio*/
		for(i=0;i<7;i++){
			area_conhecimento_convertida[i]=atoi(area_conhecimento_char[i]);
		}
		vetor_aux2=(Trabalho*) malloc(qtd_trabalhos*sizeof(Trabalho));
		/*organiza o vetor por area de conhecimento*/
		j=0;
		for(area=0;area<7;area++){
			for(i=0;i<qtd_trabalhos;i++){
				codigo=atoi(vetor_aux[i].area_conhecimento);
				if(codigo==area_conhecimento_convertida[area]){
					vetor_aux2[j]=vetor_aux[i];
					j++;
				}
			}
		}
		/* recria a lista agora com os trabalhos aprovados*/
		for(i=0;i<qtd_trabalhos;i++){
			p1=insere_no_final(p1,vetor_aux2[i]);
		}
		free(vetor_aux2);
		return p1;
}	
/*Função escreve programação
	escreve a programação em um arquivo binario*/
void escreve_programacao(Lista *p1,int qtd_trabalhos){
	FILE *arquivo_3;
	int i,checagem,area,total=0;
	Lista *aux;
	Trabalho dados_aux;
		if((arquivo_3=fopen("programacao semic.bin","wb"))==NULL){
			printf("Erro na abertura do arquivo!!\n");
			exit(1);
		}
		fwrite(&qtd_trabalhos,sizeof(int),1,arquivo_3);
		aux=p1;
		for(i=0;i<qtd_trabalhos;i++){
			if(total>=64){
				break;
			}
			dados_aux=aux->dados;
			fwrite(&dados_aux,sizeof(Trabalho),1,arquivo_3);
			aux=aux->proximo;
			total++;
		}	
}	
/*Função leitura da programação
	Lê o arquivo binario com a programação*/
Lista *leitura_programacao(Lista *p2,int *qtd_trabalhos){
	FILE * arquivo_3;
	Lista *aux;
	Trabalho aux_dados;
	int i;
		if((arquivo_3=fopen("programacao semic.bin","rb"))==NULL){
			printf("Erro na abertura do arquivo!!\n\n");
			exit(1);
		}
		fread(qtd_trabalhos,sizeof(int),1,arquivo_3);
		for(i=0;i<(*qtd_trabalhos);i++){
			fread(&aux_dados,sizeof(Trabalho),1,arquivo_3);
			p2=insere_no_final(p2,aux_dados);
		}
		fclose(arquivo_3);
	return p2;		//retorna o ponteiro do primeiro elemento da lista
}
/* Função mostrar programação
	exibe a programação*/
void programacao_por_dia(Lista *p2,int qtd_trabalhos){
	int i,dia,checagem,hora,minuto,total=0;
	Lista *aux;
		aux=p2;
		dia=1;
		hora=8;
		minuto=0;
		system("cls");
		for(i=0;i<qtd_trabalhos;i++){
			if(total>=64){				//deixa apenas o numero de apresentações estipuladas
				break;
			}
			puts("-------------------------------------------------------");
			printf("Dia:%d              Horario:%d:%d\n",dia,hora,minuto);
			puts("-------------------------------------------------------");
			printf("Código %d\n",aux->dados.codigo);
			puts(aux->dados.titulo_trabalho);
			puts(aux->dados.area_conhecimento);
			printf("Autor:%s",aux->dados.autor);
			printf("Orientador:%s",aux->dados.orientador);
			if(checagem=(strcmp(aux->dados.coautor,"nenhum\n"))!=0){
				printf("Coautor:%s",aux->dados.coautor);
			}
			if(checagem=(strcmp(aux->dados.coorientador,"nenhum\n"))!=0){
				printf("Coorientador:%s",aux->dados.coorientador);
			}
			printf("Nota:%d\n",aux->dados.Nota);
			aux=aux->proximo;
			/*altualização do horario e do dia*/
			dia= i>32?2:1; 		//verifica se já passaram as apresentações do dia//
			minuto+=15;
			if(minuto==60){
				hora++;
				minuto=0;
			}
			total++; 	//variavel que checa o total de trabalhos
		}
		puts("-------------------------------------------------------");
}
/* Função programacao por area
	Exibe a programação pela area de conhecimento*/
void programacao_por_area(Lista *p2,int qtd_trabalhos){
	char area_conhecimento[7][100]={"1-Ciencias da Saude\n","2-Ciencias Exatas\n","3-Ciencias Agrarias\n","4-Engenharias\n","5-Ciencias Sociais Aplicadas\n",
								"6-Ciencias Humanas\n","7-Linguistica, Letras e Artes\n"};
	int i,checagem,dia=1,hora=8,minuto=0,area,total=0;
	Lista *aux;
			for(area=0;area<7;area++){
				aux=p2;
				for(i=0;i<qtd_trabalhos;i++){
					if(total>=64){			//limita o total de apresentações a 64
						break; //encerra o laço
					}
					checagem=strcmp(aux->dados.area_conhecimento,area_conhecimento[area]);
					if(checagem==0){
						puts("-------------------------------------------------------");
						printf("Dia:%d              Horario:%d:%d\n",dia,hora,minuto);
						puts("-------------------------------------------------------");
						printf("Código %d\n",aux->dados.codigo);
						puts(aux->dados.titulo_trabalho);
						puts(aux->dados.area_conhecimento);
						printf("Autor:%s",aux->dados.autor);
						printf("Orientador:%s",aux->dados.orientador);
						if(checagem=(strcmp(aux->dados.coautor,"nenhum\n"))!=0){
							printf("Coautor:%s",aux->dados.coautor);
						}
						if(checagem=(strcmp(aux->dados.coorientador,"nenhum\n"))!=0){
							printf("Coorientador:%s",aux->dados.coorientador);
						}
						printf("Nota:%d\n",aux->dados.Nota);
						/*atualização do horario e do dia*/
						minuto+=15;
						if(minuto==60){
						hora++;
						minuto=0;
						}
						aux=aux->proximo;
						continue;
					}
					else{
						aux=aux->proximo;
						continue;
					}
					total++; //variavel que checa o total de trabalhos
				}
			}
			puts("-------------------------------------------------------");						
}	
/*Função retirar trabalhos
	retira um trabalho da programação*/
int retirar_trabalho(Lista *p1,int qtd_trabalhos){
	int codigo,i,qtd_trabalhos_submetidos,num=0;
	Lista *aux,*aux2;
	Trabalho *vetor_aux;
	FILE *arquivo_2,*arquivo_4;	
	
	printf("Informe o codigo do trabalho a ser retirado: ");
	scanf("%d",&codigo);	
	/*Lê o arquivo de trabalhos submetidos para a atualizar o trabalho que foi removido*/
	aux=Leitura_de_dados_1(aux,&qtd_trabalhos_submetidos);
	aux2=busca(aux,codigo); 	//aux2 recebe o endereço do trabalho que sera removido
	if(aux2==NULL){
		printf("elemento não existe\n\n");
		return 0;
	}
	strcpy(aux2->dados.situacao_trabalho,"Removido\n"); 	//a situação é atualizada para removido
	reescreve_trabalhos_submetidos(aux,qtd_trabalhos_submetidos);	//reescreve o arquivo
	libera(aux);
	/*Retira o trabalho do arquivo de trabalhos aprovados*/
	retira(p1,codigo);
	if(qtd_trabalhos_submetidos==0){
		arquivo_2=fopen("Trabalhos avaliados.txt","w");
		fprintf(arquivo_2,"%d",0);
		fclose(arquivo_2);
		arquivo_4=fopen("programacao semix.bin","wb");
		fwrite(&num,sizeof(int),1,arquivo_4);
		fclose(arquivo_4);
		printf("O arquivo agora esta vazio\n\n");
		return 0;
	}
	qtd_trabalhos--; //diminue o contador de trabalhos
	vetor_aux=(Trabalho*) malloc(qtd_trabalhos*sizeof(Trabalho));
	aux2=p1;
	
	for(i=0;i<qtd_trabalhos;i++){
		vetor_aux[i]=aux2->dados;
		aux2=aux2->proximo;
	}
	escreve_trabalhos_aprovados(vetor_aux,qtd_trabalhos);
	escreve_programacao(p1,qtd_trabalhos);
	return 1;
}
/*Função Leitura Trabalhos aprovados
	Lê o arquivo com os trabalhos aprovados*/
Lista *leitura_trabalhos_aprovados(Lista *p1,int *qtd_trabalhos){
	int i;
	FILE *arquivo_4;
	Trabalho auxiliar; 	// recebe os valores lidos temporariamente
		p1=inicializa();	//inicializa a lista encadeada
		if((arquivo_4=fopen("Trabalhos avaliados.txt","r"))==NULL){
			printf("Erro na abertura do arquivo!!\n");
			exit(1);
		}
		fscanf(arquivo_4,"%d",qtd_trabalhos);
		for(i=0;i< *qtd_trabalhos;i++){
			
			fscanf(arquivo_4,"%d",&auxiliar.codigo);
			fgetc(arquivo_4);
			fgets(auxiliar.titulo_trabalho,400,arquivo_4);
			fgets(auxiliar.area_conhecimento,400,arquivo_4);
			fgets(auxiliar.autor,400,arquivo_4);
			fgets(auxiliar.orientador,400,arquivo_4);
			fgets(auxiliar.coautor,400,arquivo_4);
			fgets(auxiliar.coorientador,400,arquivo_4);
			fgets(auxiliar.situacao_trabalho,50,arquivo_4);
			fscanf(arquivo_4,"%d",&auxiliar.Nota);
			p1=insere_no_final(p1,auxiliar);
		}
		return p1;	
}
/*Função informa usuario
	imprime informações para o usuario*/
void informa_usuario(){
	system("cls");
	puts("Não utilize acentos para área de conhecimento siga o modelo seguinte:\"1-Ciencias da Saude \"");
	puts("As áreas de conhecimento estão na ordem dada no pedido(Problema)");
	puts("Siga o modelo de exemplo que foi enviado junto ao codigo para castrar mais trabalhos");
	puts("Os arquivos são criados na mesma pasta em que esta o programa executavl");
	system("pause");
}
