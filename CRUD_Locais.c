#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "conio.c"
#include <string.h>
#include "luna.h"

// Prototipos de funcao
void receberDados(struct tLocal *local);
int incluir(struct tLocal local, FILE *arq);
int listar(FILE *arq, struct tLocal local);
int alterar(FILE *arq, int cod, struct tLocal *local);
int excluir(int id);
int contarItens();
void mostrarLocal(struct tLocal local);
int consultar(FILE *arq, struct tLocal *local, int id);

//--- Main ---------------------------------------------------------------
int main(void) {
	struct tLocal local;
	FILE *locais;
	int pesqId, opcao, qtdLocais;
	system("CLS");

	do {
		qtdLocais=contarLocais();
		opcao = menu();
		clrscr();
		switch (opcao) {
			case 10:
				local.id=qtdLocais+1;
				receberDados(&local);
				if(incluir(local, locais))
					printf("Local adicionado com sucesso!");
				else
					printf("Um erro ocorreu, o local nao foi adicionado!");

				break;
			case 11:

				if(!listar(locais, local))
					printf("Um erro ocorreu, o arquivo nao foi aberto!");

				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 12:
				pesqId=receberId();

				if(!consultar(locais, &local, pesqId))
					printf("Local nao encontrado!");
				else
					mostrarLocal(local);

				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 13:
				pesqId=receberId();

				if(!alterar(locais, pesqId, &local))
					printf("Local nao encontrado!");
				else
					printf("Local alterado!");
				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 14:
				pesqId=receberId();

				if(!excluir(pesqId))
					printf("Local não encontrado!");
				else
					printf("Local excluído!");
				printf(AMARELO);
				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;
				
			case 15:
				return 0;
		}
		clrscr();
	} while (opcao != 0);

	return 0;
}

//--- Menu --------------------------------------------------------------
int menu(void) {
	int posY=10;
	char tecla;
	printf(VERDE);
	desenharArte("artes/menu_locais.txt");

	printf(AMARELO);
	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOCE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOCD);
	printf("%c%41c\n",RETAV,RETAV);
	printf("%c%41c\n",RETAV,RETAV);
	printf("%c%41c\n",RETAV,RETAV);
	printf("%c%41c\n",RETAV,RETAV);
	printf("%c%41c\n",RETAV,RETAV);
	printf("%c%41c\n",RETAV,RETAV);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOBE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOBD);
	printf(CIANO);
	gotoxy(5,10);
	printf("- <Incluir novo Local>");
	gotoxy(5,11);
	printf("- <Listar todos os Locais>");
	gotoxy(5,12);
	printf("- <Procurar um Local>");
	gotoxy(5,13);
	printf("- <Alterar um Local>");
	gotoxy(5,14);
	printf("- <Excluir um Local>");
	gotoxy(5,15);
	printf("- <Sair>");


	while(tecla != 13) {
		printf(VERMELHO);
		gotoxy(4,posY);
		printf("%c",175);
		tecla=toupper(getch());
		gotoxy(4,posY);
		printf(" ");
		switch(tecla) {
			case 'H':
				if(posY>10)
					posY--;
				break;
			case 'P':
				if(posY<15)
					posY++;
				break;
			case 13:
				break;
		}
	}
	printf(RESETCOR);
	clrscr();
	return posY;
}

//--- Recebe os dados ----------------------------------------------------
void receberDados(struct tLocal *local) {
	char op;
	int i, idMonstro, qtdMons=0, loja;
	FILE *qtdMonstros;
	qtdMonstros = fopen("quantidadeMonstros.txt","r");
	fscanf(qtdMonstros,"%d",&qtdMons);
	fclose(qtdMonstros);
	for(i=0; i<3; i++)
		(*local).lojas[i]=0;//Nenhuma loja

	for(i=0; i<10; i++)
		(*local).monstros[i]=0;//Nenhum monstro

	i=0;

	do {
		printf(CIANO);
		printf("Qual o nome do local?\n");
		fflush(stdin);
		printf(VERDE);
		gets((*local).nome);
		clrscr();
		if(strcmp((*local).nome,"")==0) {
			printf(VERMELHO);
			printf("ERRO! O nome nao pode ser vazio\n");
		}
	} while(strcmp((*local).nome,"")==0);

	do {
		printf(CIANO);
		printf("Qual a descricao do local?\n");
		fflush(stdin);
		printf(VERDE);
		gets((*local).descricao);
		clrscr();
		if(strcmp((*local).descricao,"")==0) {
			printf(VERMELHO);
			printf("ERRO! A descricao nao pode ser vazia\n");
		}
	} while(strcmp((*local).descricao,"")==0);

	do {
		printf(CIANO);
		printf("Qual é o tipo do local?\n");
		printf("%s[0] %c%s Lugares diversos\n",CIANO, 175,VERDE);
		printf("%s[1] %c%s Cidade\n",CIANO, 175,VERDE);
		op=getch();
		(*local).tipo=op-'0';
		clrscr();
	} while((*local).tipo <0 || (*local).tipo>1);

	if((*local).tipo == 0) {
		do {
			do {
				printf(CIANO);
				printf("Qual o ID do inimigo que existe no local?\n");
				scanf("%d",&idMonstro);
				clrscr();
				if(idMonstro>qtdMons || idMonstro<1) {
					printf(VERMELHO);
					printf("ERRO! O monstro não foi encontrado, tente novamente!\n");
				}
			} while(idMonstro>qtdMons || idMonstro<1);

			(*local).monstros[i]=idMonstro;
			i++;

			if(i<=9) {
				printf("Deseja adicionar mais algum monstro?\n");
				printf("[%sS%s]im\n",VERDE,CIANO);
				printf("[%sN%s]ao\n",VERDE,CIANO);
				do {
					op=toupper(getch());
				} while(op != 'N' && op != 'S');
			}

		} while(op != 'N' && i<=9);
	} else {
		do {
			do {
				printf(CIANO);
				printf("Qual loja a cidade possui?\n");
				printf("[%s0%s] Ferreiro\n",VERDE,CIANO);
				printf("[%s1%s] Alquimista\n",VERDE,CIANO);
				printf("[%s2%s] Taverna\n",VERDE,CIANO);
				op=getch();
				loja=op-'0';
				clrscr();
			} while(loja<0 || loja>2);

			if((*local).lojas[loja]==1) {
				printf(VERMELHO);
				printf("Essa loja ja existe na cidade!\n");
			}else{
				(*local).lojas[loja]=1;
			}

			printf(CIANO);
			printf("Deseja adicionar mais alguma loja?\n");
			printf("[%sS%s]im\n",VERDE,CIANO);
			printf("[%sN%s]ao\n",VERDE,CIANO);		
			do {
				op=toupper(getch());
			} while(op != 'N' && op != 'S');
			clrscr();
		} while(op != 'N');
	}
}

//--- Inclusão -----------------------------------------------------------
int incluir(struct tLocal local, FILE *arq) {
	arq=fopen("data/locais.dat","ab");
	if(arq==NULL)
		return 0;

	fwrite(&local,sizeof(local),1,arq);
	fclose(arq);
	return 1;
}

//--- Listagem -----------------------------------------------------------
int listar(FILE *arq, struct tLocal local) {
	arq=fopen("data/locais.dat","rb");
	if(arq==NULL)
		return 0;

	while(fread(&local,sizeof(local),1,arq))
		mostrarLocal(local);


	fclose(arq);
	return 1;
}

//--- Consultar ----------------------------------------------------------
int consultar(FILE *arq, struct tLocal *local, int id) {
	arq=fopen("data/locais.dat","rb");
	if(arq==NULL)
		return 0;

	while(fread(&*local,sizeof(*local),1,arq))
		if((*local).id == id)
			return 1;

	fclose(arq);
	return 0;
}

//--- Alterar -------------------------------------------------------------
int alterar(FILE *arq, int cod, struct tLocal *local) {
	arq=fopen("data/locais.dat","rb+");
	if(arq==NULL)
		return 0;

	while(fread(&*local,sizeof(*local),1,arq)) {
		if(cod==(*local).id) {
			receberDados(&(*local));
			fseek(arq,-sizeof(*local),SEEK_CUR);
			fwrite(&*local,sizeof(*local),1,arq);
			fseek(arq, 0,SEEK_CUR);
			return 1;
		}
	}
	fclose(arq);
	return 0;
}

//--- Excluir -------------------------------------------------------------
int excluir(int id) {
	int i=1;
	struct tLocal local;

	FILE *antigo = fopen("data/locais.dat","rb");
	FILE *novo = fopen("data/locais.bak","wb");
	while(fread(&local,sizeof(local),1,antigo)) {
		if(local.id != id) {
			local.id = i;
			fwrite(&local, sizeof(local), 1, novo);
			i++;
		}
	}

	fclose(antigo);
	fclose(novo);

	remove("data/locais.dat");
	rename("data/locais.bak","data/locais.dat");
	return 1;
}

//Função para contar a quantidade de locais já existentes
int contarLocais() {
	int i=0;
	struct tLocal local;
	FILE *locais;
	FILE *qtdLocais;
	locais = fopen("data/locais.dat","rb");
	while(fread(&local,sizeof(local),1,locais))
		i++;
	fclose(locais);
	qtdLocais = fopen("quantidadeLocais.txt","w");
	fprintf(qtdLocais,"%d",i);
	fclose(qtdLocais);
	return i;
}

//Função para receber o Id do local
int receberId(void) {
	int id;
	printf(CIANO);
	printf("Digite o Id do local: ");
	scanf("%d", &id);
	return id;
}

void mostrarLocal(struct tLocal local) {
	int i;
	printf("%sDescricao: %s\n",VERDE,local.descricao);
	printf(AMARELOC);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOCE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOCD);
	printf("%c%sID: %49d%s%5c\n",RETAV,VERDE,local.id,AMARELOC,RETAV);
	printf("%c%sNome: %47s%s%5c\n",RETAV,VERDE,local.nome,AMARELOC,RETAV);
	printf("%c%sTipo: %47d%s%5c\n",RETAV,VERDE,local.tipo,AMARELOC,RETAV);
	printf("%c%sFerreiro: %43d%s%5c\n",RETAV,VERDE,local.lojas[0],AMARELOC,RETAV);
	printf("%c%sAlquimista: %41d%s%5c\n",RETAV,VERDE,local.lojas[1],AMARELOC,RETAV);
	printf("%c%sTaverna: %44d%s%5c\n",RETAV,VERDE,local.lojas[2],AMARELOC,RETAV);
	printf("%c%sID dos monstros: ",RETAV,VERDE);
	for(i=0;i<10;i++){
		printf("[%s%d%s] ",VERMELHO,local.monstros[i],VERDE);
	}
	printf("%s%c\n",AMARELOC,RETAV);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOBE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOBD);
	
}
