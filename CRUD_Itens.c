#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include "luna.h"
#include "conio.c"

// Prototipos de funcao
void receberDados(struct tItem *item);
int incluir(struct tItem item, FILE *arq);
int listar(FILE *arq, struct tItem item);
int alterar(FILE *arq, int cod, struct tItem *item);
int excluir(int id);
int contarItens();
int consultar(FILE *arq, int cod, struct tItem *item);
int j;

//--- Main ---------------------------------------------------------------
int main(void) {
	struct tItem item;
	FILE *itens;
	int pesqId, opcao, qtdItens;
	system("cls");


	do {
		qtdItens=contarItens();
		opcao = menu();
		clrscr();
		switch (opcao) {
			case 10:
				item.id=qtdItens+1;
				receberDados(&item);
				if(incluir(item, itens))
					printf("Item adicionado com sucesso!");
				else
					printf("Um erro ocorreu, o item n�o foi adicionado!");

				break;
			case 11:

				if(!listar(itens, item))
					printf("Um erro ocorreu, o arquivo n�o foi aberto!");

				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 12:
				pesqId=receberId();

				if(!consultar(itens, pesqId, &item))
					printf("Item n�o encontrado!");
				else
					mostrarItem(item);

				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 13:
				pesqId=receberId();

				if(!alterar(itens, pesqId, &item))
					printf("Item n�o encontrado!");
				else
					printf("Item alterado!");
				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 14:
				pesqId=receberId();

				if(!excluir(pesqId))
					printf("Item n�o encontrado!");
				else
					printf("Item exclu�do!");
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
	desenharArte("artes/menu_itens.txt");

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
	printf("- <Incluir novo item>");
	gotoxy(5,11);
	printf("- <Listar todos os itens>");
	gotoxy(5,12);
	printf("- <Procurar um item>");
	gotoxy(5,13);
	printf("- <Alterar um item>");
	gotoxy(5,14);
	printf("- <Excluir um item>");
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
void receberDados(struct tItem *item) {
	printf(CIANO);
	char op;
		do {
		printf("Qual o tipo do item?\n");
		printf("%s[0] %c%s Armadura\n",CIANO, 175,VERDE);
		printf("%s[1] %c%s Elmo\n",CIANO, 175,VERDE);
		printf("%s[2] %c%s Luva\n",CIANO, 175,VERDE);
		printf("%s[3] %c%s Bota\n",CIANO, 175,VERDE);
		printf("%s[4] %c%s Calca\n",CIANO, 175,VERDE);
		printf("%s[5] %c%s Arma\n",CIANO, 175,VERDE);
		printf("%s[6] %c%s Cinto\n",CIANO, 175,VERDE);
		printf("%s[7] %c%s Arma Secundaria\n",CIANO, 175,VERDE);
		op=getch();
		(*item).tipo=op-'0';
		clrscr();
	} while((*item).tipo <0 || (*item).tipo>7);

	do {
		printf("Qual o nome do item?\n");
		fflush(stdin);
		gets((*item).nome);
		clrscr();
		if(strcmp((*item).nome,"")==0) {
			printf(VERMELHO);
			printf("ERRO! O nome nao pode ser vazio\n");
			printf(CIANO);
		}
	} while(strcmp((*item).nome,"")==0);

	do {
		printf("Qual a descricao do item?\n");
		fflush(stdin);
		gets((*item).descricao);
		clrscr();
		if(strcmp((*item).descricao,"")==0) {
			printf(VERMELHO);
			printf("ERRO! A descricao nao pode ser vazia\n");
			printf(CIANO);
		}
	} while(strcmp((*item).descricao,"")==0);

	printf("Qual a quantidade de ataque que o item garante?\n");
	scanf("%i", &(*item).ataque);
	clrscr();

	printf("Qual a quantidade de vida que o item garante?\n");
	scanf("%i", &(*item).vida);
	clrscr();

	printf("Qual a quantidade de mana que o item garante?\n");
	scanf("%i", &(*item).mana);
	clrscr();

	printf("Qual a quantidade de armadura que o item garante?\n");
	scanf("%i", &(*item).armadura);
	clrscr();

	printf("Qual a quantidade de resistencia que o item garante?\n");
	scanf("%i", &(*item).resistencia);
	clrscr();

	printf("Qual a quantidade de destreza que o item garante?\n");
	scanf("%i", &(*item).destreza);
	clrscr();

	printf("Qual a quantidade de forca que o item garante?\n");
	scanf("%i", &(*item).forca);
	clrscr();

	printf("Qual a quantidade de inteligencia que o item garante?\n");
	scanf("%i", &(*item).inteligencia);
	clrscr();

	printf("Qual a quantidade de vitalidade que o item garante?\n");
	scanf("%i", &(*item).vitalidade);
	clrscr();

	do {
		printf("Digite o valor do item:\n");
		scanf("%i", &(*item).valor);
		clrscr();
		if((*item).valor < 0) {
			printf(VERMELHO);
			printf("ERRO! O Valor nao pode ser negativo\n");
			printf(CIANO);
		}
	} while((*item).valor < 0);


}

//--- Inclus�o -----------------------------------------------------------
int incluir(struct tItem item, FILE *arq) {
	arq=fopen("data/itens.dat","ab");
	if(arq==NULL)
		return 0;

	fwrite(&item,sizeof(item),1,arq);
	fclose(arq);
	return 1;
}

//--- Listagem -----------------------------------------------------------
int listar(FILE *arq, struct tItem item) {
	arq=fopen("data/itens.dat","rb");
	if(arq==NULL)
		return 0;

	while(fread(&item,sizeof(item),1,arq))
		mostrarItem(item);


	fclose(arq);
	return 1;
}

//--- Consultar ----------------------------------------------------------
int consultar(FILE *arq, int cod, struct tItem *item) {
	arq=fopen("data/itens.dat","rb+");
	if(arq==NULL)
		return 0;

	while(fread(&*item,sizeof(*item),1,arq))
		if(cod==(*item).id)
			return 1;

	fclose(arq);
	return 0;
}

//--- Alterar -------------------------------------------------------------
int alterar(FILE *arq, int cod, struct tItem *item) {
	arq=fopen("data/itens.dat","rb+");
	if(arq==NULL)
		return 0;

	while(fread(&*item,sizeof(*item),1,arq)) {
		if(cod==(*item).id) {
			receberDados(&(*item));
			fseek(arq,-sizeof(*item),SEEK_CUR);
			fwrite(&*item,sizeof(*item),1,arq);
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
	struct tItem item;

	FILE *antigo = fopen("data/itens.dat","rb");
	FILE *novo = fopen("data/itens.bak","wb");
	while(fread(&item,sizeof(item),1,antigo)) {
		if(item.id != id) {
			item.id = i;
			fwrite(&item, sizeof(item), 1, novo);
			i++;
		}
	}

	fclose(antigo);
	fclose(novo);

	remove("data/itens.dat");
	rename("data/itens.bak","data/itens.dat");
	return 1;
}

//Fun��o para contar a quantidade de itens j� existentes
int contarItens() {
	int i=0;
	struct tItem item;
	FILE *itens;
	FILE *qtdItens;
	itens = fopen("data/itens.dat","rb");
	while(fread(&item,sizeof(item),1,itens))
		i++;
	fclose(itens);
	qtdItens = fopen("quantidadeItens.txt","w");
	fprintf(qtdItens,"%d",i);
	fclose(qtdItens);
	return i;
}

//Fun��o para receber o Id do item
int receberId(void) {
	printf(CIANO);
	int id;
	printf("Digite o Id do item: ");
	scanf("%d", &id);
	return id;
}
