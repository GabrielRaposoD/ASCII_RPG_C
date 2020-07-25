#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "luna.h"
#include "conio.c"

// Prototipos de funcao
void receberDados(struct tMonstro *monstro);
int incluir(struct tMonstro monstro, FILE *arq);
int listar(FILE *arq, struct tMonstro monstro);
int alterar(FILE *arq, int cod, struct tMonstro *monstro);
int excluir(int id);
int contarMonstros();
void mostrarMonstro(struct tMonstro monstro);
int consultar(FILE *arq, int cod, struct tMonstro *monstro);

//--- Main ---------------------------------------------------------------
int main(void) {
	struct tMonstro monstro;
	FILE *monstros;
	int pesqId, opcao, qtdMonstros;
	system("cls");

	do {
		qtdMonstros=contarMonstros();
		opcao = menu();
		clrscr();
		switch (opcao) {
			case 10:
				monstro.id=qtdMonstros+1;
				receberDados(&monstro);
				if(incluir(monstro, monstros))
					printf("Inimigo adicionado com sucesso!");
				else
					printf("Um erro ocorreu, o Inimigo não foi adicionado!");

				break;
			case 11:

				if(!listar(monstros, monstro))
					printf("Um erro ocorreu, o arquivo não foi aberto!");

				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 12:
				pesqId=receberId();

				if(!consultar(monstros, pesqId, &monstro))
					printf("Inimigo não encontrado!");
				else
					mostrarMonstro(monstro);

				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 13:
				pesqId=receberId();

				if(!alterar(monstros, pesqId, &monstro))
					printf("Inimigo não encontrado!");
				else
					printf("Inimigo alterado!");
				printf("\nPressione qualquer tecla para continuar");
				getch();
				break;

			case 14:
				pesqId=receberId();

				if(!excluir(pesqId))
					printf("Inimigo não encontrado!");
				else
					printf("Inimigo excluído!");
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
	desenharArte("artes/menu_inimigos.txt");

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
	printf("- <Incluir novo Inimigo>");
	gotoxy(5,11);
	printf("- <Listar todos os Inimigo>");
	gotoxy(5,12);
	printf("- <Procurar um Inimigo>");
	gotoxy(5,13);
	printf("- <Alterar um Inimigo>");
	gotoxy(5,14);
	printf("- <Excluir um Inimigo>");
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
void receberDados(struct tMonstro *monstro) {
	printf(CIANO);
	char op;
	do {
		printf("Qual o nome do Inimigo?\n");
		fflush(stdin);
		gets((*monstro).nome);
		clrscr();
		if(strcmp((*monstro).nome,"")==0) {
			printf(VERMELHO);
			printf("ERRO! O nome nao pode ser vazio\n");
			printf(CIANO);
		}
	} while(strcmp((*monstro).nome,"")==0);

	do {
		printf("Qual a descricao do Inimigo?\n");
		fflush(stdin);
		gets((*monstro).descricao);
		clrscr();
		if(strcmp((*monstro).descricao,"")==0) {
			printf(VERMELHO);
			printf("ERRO! A descricao nao pode ser vazia\n");
			printf(CIANO);
		}
	} while(strcmp((*monstro).descricao,"")==0);

	do {
		printf("Qual o level do Inimigo?\n");
		scanf("%i", &(*monstro).level);
		clrscr();
		if((*monstro).level<1) {
			printf(VERMELHO);
			printf("ERRO! O level do Inimigo nao pode ser menor que 1!\n");
			printf(CIANO);
		}
	} while((*monstro).level<1);

	do {
		printf("Qual a quantidade de vida que o Inimigo tem?\n");
		scanf("%i", &(*monstro).vida);
		clrscr();
		if((*monstro).vida<1){
			printf(VERMELHO);
			printf("ERRO! A vida do Inimigo nao pode ser menor que 1!\n");
			printf(CIANO);
		}
	} while((*monstro).vida<1);

	do {
		printf("Qual a quantidade de armadura que o Inimigo tem?\n");
		scanf("%i", &(*monstro).armadura);
		clrscr();
		if((*monstro).armadura<0){
			printf(VERMELHO);
			printf("ERRO! A vida do armadura nao pode ser menor que 0!\n");
			printf(CIANO);
		}
	} while((*monstro).armadura<0);

	do {
		printf("Qual a quantidade de resistencia que o Inimigo tem?\n");
		scanf("%i", &(*monstro).resistencia);
		clrscr();
		if((*monstro).resistencia<0) {
			printf(VERMELHO);
			printf("ERRO! A vida do resistencia nao pode ser menor que 0!\n");
			printf(CIANO);
		}
	} while((*monstro).resistencia<0);

	do {
		printf("Qual a quantidade de destreza que o Inimigo tem?\n");
		scanf("%i", &(*monstro).destreza);
		clrscr();
		if((*monstro).destreza<1) {
			printf(VERMELHO);
			printf("ERRO! A vida do destreza nao pode ser menor que 1!\n");
			printf(CIANO);
		}
	} while((*monstro).destreza<1);

	do {
		printf("Qual a quantidade de inteligencia que o Inimigo tem?\n");
		scanf("%i", &(*monstro).inteligencia);
		clrscr();
		if((*monstro).inteligencia<1) {
			printf(VERMELHO);
			printf("ERRO! A vida do inteligencia nao pode ser menor que 1!\n");
			printf(CIANO);
		}
	} while((*monstro).inteligencia<1);

	do {
		printf("Qual a quantidade de forca que o Inimigo tem?\n");
		scanf("%i", &(*monstro).forca);
		clrscr();
		if((*monstro).destreza<1) {
			printf(VERMELHO);
			printf("ERRO! A vida do forca nao pode ser menor que 1!\n");
			printf(CIANO);
		}
	} while((*monstro).forca<1);

	do {
		printf("Qual a quantidade de vitalidade que o Inimigo tem?\n");
		scanf("%i", &(*monstro).vitalidade);
		clrscr();
		if((*monstro).vitalidade<1) {
			printf(VERMELHO);
			printf("ERRO! A vida do vitalidade nao pode ser menor que 1!\n");
			printf(CIANO);
		}
	} while((*monstro).vitalidade<1);
}

//--- Inclusão -----------------------------------------------------------
int incluir(struct tMonstro monstro, FILE *arq) {
	arq=fopen("data/monstros.dat","ab");
	if(arq==NULL)
		return 0;

	fwrite(&monstro,sizeof(monstro),1,arq);
	fclose(arq);
	return 1;
}

//--- Listagem -----------------------------------------------------------
int listar(FILE *arq, struct tMonstro monstro) {
	arq=fopen("data/monstros.dat","rb");
	if(arq==NULL)
		return 0;

	while(fread(&monstro,sizeof(monstro),1,arq))
		mostrarMonstro(monstro);

	fclose(arq);
	return 1;
}

//--- Consultar ----------------------------------------------------------
int consultar(FILE *arq, int cod, struct tMonstro *monstro) {
	arq=fopen("data/monstros.dat","rb+");
	if(arq==NULL)
		return 0;

	while(fread(&*monstro,sizeof(*monstro),1,arq))
		if(cod==(*monstro).id)
			return 1;

	fclose(arq);
	return 0;
}

//--- Alterar -------------------------------------------------------------
int alterar(FILE *arq, int cod, struct tMonstro *monstro) {
	arq=fopen("data/monstros.dat","rb+");
	if(arq==NULL)
		return 0;

	while(fread(&*monstro,sizeof(*monstro),1,arq)) {
		if(cod==(*monstro).id) {
			receberDados(&(*monstro));
			fseek(arq,-sizeof(*monstro),SEEK_CUR);
			fwrite(&*monstro,sizeof(*monstro),1,arq);
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
	struct tMonstro monstro;

	FILE *antigo = fopen("data/monstros.dat","rb");
	FILE *novo = fopen("data/monstros.bak","wb");
	while(fread(&monstro,sizeof(monstro),1,antigo)) {
		if(monstro.id != id) {
			monstro.id = i;
			fwrite(&monstro, sizeof(monstro), 1, novo);
			i++;
		}
	}

	fclose(antigo);
	fclose(novo);

	remove("data/monstros.dat");
	rename("data/monstros.bak","data/monstros.dat");
	return 1;
}

//Função para contar a quantidade de monstros já existentes
int contarMonstros() {
	int i=0;
	struct tMonstro monstro;
	FILE *monstros;
	FILE *qtdMonstros;
	monstros = fopen("data/monstros.dat","rb");
	while(fread(&monstro,sizeof(monstro),1,monstros))
		i++;
	fclose(monstros);
	qtdMonstros = fopen("quantidadeMonstros.txt","w");
	fprintf(qtdMonstros,"%d",i);
	fclose(qtdMonstros);
	return i;
}

//Função para receber o Id do monstros
int receberId(void) {
	printf(CIANO);
	int id;
	printf("Digite o Id do monstro: ");
	scanf("%d", &id);
	return id;
}

void mostrarMonstro(struct tMonstro monstro) {
	printf("%sDescricao: %s\n",VERDE,monstro.descricao);
	printf(AMARELOC);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOCE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOCD);
	printf("%c%sID: %32i%s%5c\n",RETAV,VERDE,monstro.id,AMARELOC,RETAV);
	printf("%c%sNome: %30s%s%5c\n",RETAV,VERDE,monstro.nome,AMARELOC,RETAV);
	printf("%c%sVida: %30i%s%5c\n",RETAV,VERDE,monstro.vida,AMARELOC,RETAV);
	printf("%c%sArmadura: %26i%s%5c\n",RETAV,VERDE,monstro.armadura,AMARELOC,RETAV);
	printf("%c%sResistencia: %23i%s%5c\n",RETAV,VERDE,monstro.resistencia,AMARELOC,RETAV);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOBE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOBD);
}
