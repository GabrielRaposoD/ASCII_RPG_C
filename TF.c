#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "luna.h"
#include "conio.c"

int main(void) {
	int escolha, sair=0, id, slots, qtdLocais=0, qtdItens=0;
	struct tFicha jogador;
	struct tLocal local;
	char tecla;
	HideCursor();
	srand(time(NULL));
	recolherDados(&qtdLocais, &qtdItens);
	system("cls");
	
	do {
		escolha=menu_inicial();
		switch(escolha) {
			case 25:
				printf(AMARELO);
				printf("Escolha uma das seguintes classes para o seu personagem:\n");
				escolherClasse(&jogador);

				do {
					printf("Qual o nome do seu personagem?\n");
					printf(VERDE);
					fflush(stdin);
					gets(jogador.nome);
					clrscr();
					if(strcmp(jogador.nome,"")==0) {
						printf(VERMELHO);
						printf("ERRO! O nome nao pode ser vazio\n");
						printf(CIANO);
					}
				} while(strcmp(jogador.nome,"")==0);
				salvarPersonagem(jogador);
				escrever("introducao.txt");
				sair=1;
				break;

			case 26:
				slots=contarSlots();
				if(slots==0) {
					printf(VERMELHO);
					printf("ERRO! Nenhum personagem salvo. Pressione qualquer tecla para voltar ao menu inicial");
					getch();
					break;
				}
				id=1;
				do {
					jogador=carregarPersonagem(id);
					mostrarPersonagem(jogador);
					fflush(stdin);
					tecla=toupper(getch());
					system("cls");
					switch(tecla) {
						case'M':
							if(id<slots)
								id++;
							break;

						case'K':
							if(id>1)
								id--;
							break;

						case 13:
							break;
							
						case 27:
							break;	
					}
				} while(tecla != 13 && tecla != 27);
				if(tecla == 13)
					sair=1;
				break;

			case 27:
				slots=contarSlots();
				if(slots==0) {
					printf(VERMELHO);
					printf("ERRO! Nenhum personagem salvo. Pressione qualquer tecla para voltar ao menu inicial");
					getch();
					break;
				}
				id=1;
				do {
					jogador=carregarPersonagem(id);
					mostrarPersonagem(jogador);
					fflush(stdin);
					tecla=toupper(getch());
					system("cls");
					switch(tecla) {
						case'M':
							if(id<slots)
								id++;
							break;

						case'K':
							if(id>1)
								id--;
							break;

						case 13:
							break;

						case 27:
							break;
					}
				} while(tecla != 13 && tecla != 27);

				if(tecla == 13) {
					excluirPersonagem(id);
					clrscr();
					printf(VERMELHO);
					printf("PERSONAGEM EXCLUIDO COM SUCESSO!");
					getch();
				}
				break;

			case 28:
				escrever("info.txt");
				break;

			case 29:
				return 0;
				break;
		}
	} while(sair != 1);

	do {
		if(jogador.vida<=0){
			clrscr();
			printf(VERMELHO);
			desenharArteXY("artes/morte.txt",30,5,0,1);
			getch();
			return;
		}
		local=carregarLocal(jogador.localAtual);
		escolha=menu_jogo(local, jogador);
		printf(CIANO);
		switch(escolha) {
			case 23:
				jogador.localAtual=viajar(qtdLocais);
				printf("%sViagem concluida! Aperte qualquer tecla para continuar",VERDE);
				getch();
				break;

			case 24:
				if(local.tipo==0) {
					jogador=explorar(jogador, local,qtdItens);
				} else {
					jogador=lojas(local, qtdItens, jogador);
				}
				break;

			case 25:
				mostrarPersonagem(jogador);
				getch();
				break;

			case 26:
				printf(VERDE);
				printf("Nome: %s%s\n",BRANCO,local.nome);
				printf(VERDE);
				printf("Descricao: %s%s\n",BRANCO,local.descricao);
				printf(VERDE);
				if(local.tipo==0)
					printf("E um local perigoso, cuidado ao explorar!\n");
				else
					printf("Aproveite para reabastecer seus recursos!\n");
				getch();
				break;

			case 27:
				jogador=inventario(jogador);
				break;
				
			case 28:
				salvarPersonagem(jogador);	
				break;
				
			case 29:
				salvarPersonagem(jogador);
				main();
				sair=2;
				break;
		}
	} while(sair != 2);


	return 0;
}

//Função para a criacao do menu inicial
int menu_inicial() {
	int posY=25;
	char tecla;
	printf(AMARELO);

	clrscr();
	printf(BRANCO);
	desenharArte("artes/menu.txt");
	printf(CIANO);

	while(tecla != 13) {
		if(posY==25){
			printf(VERDE);
		}else
			printf(BRANCO);	
		gotoxy(5,25);
		printf("<Novo jogo>");
		if(posY==26){
			printf(VERDE);
		}else
			printf(BRANCO);
		gotoxy(5,26);
		printf("<Carregar jogo>");
		if(posY==27){
			printf(VERDE);
		}else
			printf(BRANCO);
		gotoxy(5,27);
		printf("<Excluir personagem>");
		if(posY==28){
			printf(VERDE);
		}else
			printf(BRANCO);
		gotoxy(5,28);
		printf("<Informacoes>");
		if(posY==29){
			printf(VERDE);
		}else
			printf(BRANCO);
		gotoxy(5,29);
		printf("<Sair>");
		fflush(stdin);
		tecla=toupper(getch());
		switch(tecla) {
			case 'H':
				if(posY>25)
					posY--;
				break;
			case 'P':
				if(posY<29)
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

int menu_jogo(struct tLocal local, struct tFicha jogador) {
	int posY=23;
	char tecla=0;
	clrscr();
	
	printf(BRANCO);
	desenharArteXY("artes/diana.txt",0,5,0,1);
	printf(AZUL);
	gotoxy(3,2);
	printf("Jogador: %s%s%s  Vida: %s%d/%d%s  Local: %s%s%s", CIANO,jogador.nome,AZUL,CIANO,jogador.vida,jogador.vidaMax,AZUL,CIANO,local.nome,AZUL);
	gotoxy(3,3);
	printf("Level: %s%d%s",CIANO, jogador.level,AZUL);
	gotoxy(3,4);
	printf("Ouro: %s%d%s",CIANO,jogador.ouro,AZUL);
	gotoxy(3,5);
	printf("Pocoes: %s%d/%d",CIANO,jogador.qtdPocoes,MAX_POT);

	while(tecla != 13) {
			if(posY==23){
		printf(VERDE);
		}else
			printf(AZUL);
		gotoxy(5,23);
		printf("Viajar");
		if(posY==24){
			printf(VERDE);
		}else
			printf(AZUL);
		gotoxy(5,24);
		if(local.tipo==0)
			printf("Explorar");
		else
			printf("Lojas");
		if(posY==25){
			printf(VERDE);
		}else
			printf(AZUL);
		gotoxy(5,25);
		printf("Minhas Informacoes");
		if(posY==26){
			printf(VERDE);
		}else
			printf(AZUL);
		gotoxy(5,26);
		printf("Informacoes do local atual");
		if(posY==27){
			printf(VERDE);
		}else
			printf(AZUL);
		gotoxy(5,27);
		printf("Inventario");
		if(posY==28){
			printf(VERDE);
		}else
			printf(AZUL);
		gotoxy(5,28);
		printf("Salvar Jogo");
		if(posY==29){
			printf(VERDE);
		}else
			printf(AZUL);
		gotoxy(5,29);
		printf("Salvar e voltar ao menu inicial");
		fflush(stdin);
		tecla=toupper(getch());
		switch(tecla) {
			case 'H':
				if(posY>23)
					posY--;
				break;
			case 'P':
				if(posY<29)
					posY++;
				break;
			case 13:
				break;
		}
	}
	printf(RESETCOR);
	system("cls");
	return posY;
}

//Função para mostrar as informações do jogo
void escrever(char *texto) {
	int i;
	FILE *info;
	info = fopen(texto,"r");
	char string[100];
	printf(BRANCO);
	while(fgets(string,sizeof(string),info) != NULL)
		for(i=0; string[i]!='\0'; i++) {
			printf("%c",string[i]);
			usleep(10000);
		}
	printf(AMARELO);
	printf("\nPressione qualquer tecla para continuar");
	getch();
	fclose(info);
}

//Função para fazer a escolha da classe do personagem principal
void escolherClasse(struct tFicha *novo) {
	struct tItem nada;
	int j;
	(*novo).localAtual=0;

	char classe;
	printf("%s[G]%suerreiro\n",VERDE,AMARELO);
	printf("%s[M]%saga\n",VERDE,AMARELO);
	printf("%s[L]%sadra\n",VERDE,AMARELO);
	printf("%s[A]%squeiro\n",VERDE,AMARELO);
	while(classe!='G' && classe!='M' && classe!='L' && classe!='A') {
		fflush(stdin);
		classe=getch();
		classe=toupper(classe);
	}
	system("cls");
	switch(classe) {
		case 'G':
			strcpy((*novo).classe,("Guerreiro"));
			(*novo).level=1;
			(*novo).ouro=0;
			(*novo).vida=80;
			(*novo).mana=20;
			(*novo).armadura=5;
			(*novo).resistencia=0;
			(*novo).destreza=8;
			(*novo).inteligencia=5;
			(*novo).forca=12;
			(*novo).vitalidade=10;
			break;
		case 'M':
			strcpy((*novo).classe,("Maga"));
			(*novo).level=1;
			(*novo).ouro=0;
			(*novo).vida=40;
			(*novo).mana=60;
			(*novo).armadura=0;
			(*novo).resistencia=5;
			(*novo).destreza=10;
			(*novo).inteligencia=15;
			(*novo).forca=5;
			(*novo).vitalidade=5;
			break;
		case 'L':
			strcpy((*novo).classe,("Ladra"));
			(*novo).level=1;
			(*novo).ouro=100;
			(*novo).vida=70;
			(*novo).mana=30;
			(*novo).armadura=3;
			(*novo).resistencia=2;
			(*novo).destreza=14;
			(*novo).inteligencia=8;
			(*novo).forca=8;
			(*novo).vitalidade=5;
			break;
		case 'A':
			strcpy((*novo).classe,("Arqueiro"));
			(*novo).level=1;
			(*novo).ouro=0;
			(*novo).vida=60;
			(*novo).mana=40;
			(*novo).armadura=3;
			(*novo).resistencia=2;
			(*novo).destreza=14;
			(*novo).inteligencia=7;
			(*novo).forca=7;
			(*novo).vitalidade=7;
			break;
	}
	(*novo).vidaMax=(*novo).vida;
	for(j=0; j<50; j++)
		(*novo).inventario[j]=0;

	for(j=0; j<8; j++)
		desequiparItem(j, &*novo);
	
	(*novo).proxL=proximoLevel(*novo);
	(*novo).experiencia=0;
	(*novo).experienciaTotal=0;
	(*novo).id=contarSlots()+1;
	(*novo).qtdItens=0;
	(*novo).qtdPocoes=5;
}

//Função para salvar os dados de um determinado personagens
void salvarPersonagem(struct tFicha jogador) {
	int i=1;
	struct tFicha aux;
	
	FILE *save;
	save = fopen("data/personagens.sav","r+b");
	if(save==NULL){
		save = fopen("data/personagens.sav","a+b");
	}	
	
	while(fread(&aux,sizeof(jogador),1,save)) {
		if(aux.id == jogador.id){
			fseek(save,-(sizeof(jogador)),SEEK_CUR);
			fwrite(&jogador,sizeof(jogador),1,save);
			fclose(save);
			return;
		}
	}
	
	fseek(save,0,SEEK_CUR);
	fwrite(&jogador,sizeof(jogador),1,save);
	fclose(save);
}

//Função para carregar os dados de um determinado personagens
struct tFicha carregarPersonagem(int id) {
	struct tFicha load;
	FILE *save;
	save = fopen("data/personagens.sav","rb");

	while(fread(&load,sizeof(load),1,save))
		if(id == load.id) {
			fclose(save);
			return load;
		}

	fclose(save);
}

//Função para saber quantos personagens já estão salvos
int contarSlots() {
	int i=0;
	struct tFicha aux;
	FILE *save;
	save = fopen("data/personagens.sav","rb");
	while(fread(&aux,sizeof(aux),1,save))
		i++;
	fclose(save);
	return i;
}

//Função para mostrar os dados do personagem
void mostrarPersonagem(struct tFicha personagem) {
	char arqClasse[25];
	int iVida=0, iMana=0, iArmadura=0, iResistencia=0, iDestreza=0, iForca=0, iInteligencia=0, iVitalidade=0, i;
	for(i=0;i<8;i++){
		iVida+=personagem.equipamentos[i].vida;
		iArmadura+=personagem.equipamentos[i].armadura;
		iResistencia+=personagem.equipamentos[i].resistencia;
		iDestreza+=personagem.equipamentos[i].destreza;
		iMana+=personagem.equipamentos[i].mana;
		iForca+=personagem.equipamentos[i].forca;
		iInteligencia+=personagem.equipamentos[i].inteligencia;
		iVitalidade+=personagem.equipamentos[i].vitalidade;
	}

	printf(BRANCO);
	if(strcmp(personagem.classe,"Guerreiro")==0){
		desenharArte("artes/Guerreiro.txt");
	}else if(strcmp(personagem.classe,"Maga")==0){
		desenharArte("artes/Maga.txt");
	}else if(strcmp(personagem.classe,"Ladra")==0){
		char arte[]={0x20,0x20,0x20,0x20,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x0A,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x0A,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x0A,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x0A,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x0A,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x0A,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x0A,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xDB,0xDB,0xDB,0xDB,0xB0,0xB0,0xB0,0xB0,0xDB,0xDB,0xB0,0xB0,0x0A,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0xB0,0xB0,0xB0,0xB0,0xDB,0xDB,0xB0,0xB0,0xB0,0xB0,0xDB,0xDB,0xB0,0xB0,0x0A,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB1,0xB1,0x0A,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0xDB,0x0A,0xB1,0xB1,0x20,0x20,0x20,0x20,0xB0,0xB0,0xB2,0xB2,0xB2,0xB2,0xB1,0xB1,0xB1,0xB1,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB0,0xB0,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xDB,0xDB,0x0A,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xDB,0xDB,0x0A,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB2,0xB2,0xB2,0xB2,0xB1,0xB1,0xDB,0xDB,0xDB,0xDB,0x0A,0x20,0x20,0xB0,0xB0,0xB0,0xB0,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xDB,0xDB,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0xB0,0xB0,0xB0,0xB0,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0x0A,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0x0A,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0x20,0x20,0xDB,0xDB,0xDB,0xDB,0xB1,0xB1};
		printf("%s",arte);
	}else if(strcmp(personagem.classe,"Arqueiro")==0){
		char arte[]={0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x20,0x20,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0xB0,0xB0,0xB0,0xB0,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x20,0x0A,0x20,0x20,0xB0,0xB0,0xB0,0xB0,0xB1,0xB1,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB0,0xB0,0xB0,0xB0,0x0A,0x20,0x20,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB2,0xB2,0xB2,0xB2,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB0,0xB2,0xB2,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x20,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0xB2,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB2,0xB2,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0xB1,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xDB,0xDB};
		printf("%s",arte);
	}
	desenharArte(arqClasse);
	gotoxy(78,1);
	printf(AMARELOC);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOCE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOCD);
	gotoxy(78,2);
	printf("%c%sNome: %30s%s%5c\n",RETAV,VERDE,personagem.nome,AMARELOC,RETAV);
	gotoxy(78,3);
	printf("%c%sClasse: %28s%s%5c\n",RETAV,VERDE,personagem.classe,AMARELOC,RETAV);
	gotoxy(78,4);
	printf("%c%sLevel: %29i%s%5c\n",RETAV,VERDE,personagem.level,AMARELOC,RETAV);
	gotoxy(78,5);
	printf("%c%sExp: %31i%s%5c\n",RETAV,VERDE,personagem.experiencia,AMARELOC,RETAV);
	gotoxy(78,6);
	printf("%c%sExp Total: %25i%s%5c\n",RETAV,VERDE,personagem.experienciaTotal,AMARELOC,RETAV);
	gotoxy(78,7);
	printf("%c%sProximo Level: %21i%s%5c\n",RETAV,VERDE,personagem.proxL,AMARELOC,RETAV);
	gotoxy(78,8);
	printf("%c%sOuro: %30i%s%5c\n",RETAV,VERDE,personagem.ouro,AMARELOC,RETAV);
	gotoxy(78,9);
	printf("%c%sVida: %27i/%1d%s%5c\n",RETAV,VERDE,personagem.vida,personagem.vidaMax+iVida,AMARELOC,RETAV);
	gotoxy(78,10);
	printf("%c%sMana: %30i%s%5c\n",RETAV,VERDE,personagem.mana+iMana,AMARELOC,RETAV);
	gotoxy(78,11);
	printf("%c%sArmadura: %26i%s%5c\n",RETAV,VERDE,personagem.armadura+iArmadura,AMARELOC,RETAV);
	gotoxy(78,12);
	printf("%c%sResistencia: %23i%s%5c\n",RETAV,VERDE,personagem.resistencia+iResistencia,AMARELOC,RETAV);
	gotoxy(78,13);
	printf("%c%sDestreza: %26i%s%5c\n",RETAV,VERDE,personagem.destreza+iDestreza,AMARELOC,RETAV);
	gotoxy(78,14);
	printf("%c%sForca: %29i%s%5c\n",RETAV,VERDE,personagem.forca+iForca,AMARELOC,RETAV);
	gotoxy(78,15);
	printf("%c%sInteligencia: %22i%s%5c\n",RETAV,VERDE,personagem.inteligencia+iInteligencia,AMARELOC,RETAV);
	gotoxy(78,16);
	printf("%c%sVitalidade: %24i%s%5c\n",RETAV,VERDE,personagem.vitalidade+iVitalidade,AMARELOC,RETAV);
	gotoxy(78,17);
	printf("%c%sSlot: %30i%s%5c\n",RETAV,VERDE,personagem.id,AMARELOC,RETAV);
	gotoxy(78,18);
	printf("%c%sElmo: %30s%s%5c\n",RETAV,VERDE,personagem.equipamentos[1].nome,AMARELOC,RETAV);
	gotoxy(78,19);
	printf("%c%sArmadura: %26s%s%5c\n",RETAV,VERDE,personagem.equipamentos[0].nome,AMARELOC,RETAV);
	gotoxy(78,20);
	printf("%c%sCinto: %29s%s%5c\n",RETAV,VERDE,personagem.equipamentos[6].nome,AMARELOC,RETAV);
	gotoxy(78,21);
	printf("%c%sArma: %30s%s%5c\n",RETAV,VERDE,personagem.equipamentos[5].nome,AMARELOC,RETAV);
	gotoxy(78,22);
	printf("%c%sBotas: %29s%s%5c\n",RETAV,VERDE,personagem.equipamentos[3].nome,AMARELOC,RETAV);
	gotoxy(78,23);
	printf("%c%sLuvas: %29s%s%5c\n",RETAV,VERDE,personagem.equipamentos[2].nome,AMARELOC,RETAV);
	gotoxy(78,24);
	printf("%c%sCalcas: %28s%s%5c\n",RETAV,VERDE,personagem.equipamentos[4].nome,AMARELOC,RETAV);
	gotoxy(78,25);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOBE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOBD);
}

//Função para mostrar os dados do personagem
void excluirPersonagem(int id) {
	int i=1;
	struct tFicha personagem;

	FILE *antigo = fopen("data/personagens.sav","rb");
	FILE *novo = fopen("data/personagens.bak","wb");
	while(fread(&personagem,sizeof(personagem),1,antigo)) {
		if(personagem.id != id) {
			personagem.id = i;
			fwrite(&personagem, sizeof(personagem), 1, novo);
			i++;
		}
	}

	fclose(antigo);
	fclose(novo);

	remove("data/personagens.sav");
	rename("data/personagens.bak","data/personagens.sav");
}

//Função parar retirar um item da aba de equipamentos e o colocar no inventario
int desequiparItem(int tipo, struct tFicha *personagem) {
	struct tItem nada;
	nada.id=0;
	strcpy(nada.descricao,"Nada");
	strcpy(nada.nome,"Nada");
	nada.armadura=0;
	nada.resistencia=0;
	nada.tipo=tipo;
	nada.valor=0;
	nada.vida=0;
	nada.inteligencia=0;
	nada.forca=0;
	nada.destreza=0;
	nada.vitalidade=0;
	nada.ataque=0;
	nada.mana=0;

	if((*personagem).equipamentos[tipo].id!=0) {
		(*personagem).inventario[(*personagem).qtdItens]=(*personagem).equipamentos[tipo].id;
		(*personagem).qtdItens++;
	}

	(*personagem).equipamentos[tipo]=nada;
	return 1;
}

//Função parar carregar um local direto de um arquivo
struct tLocal carregarLocal(int id) {
	struct tLocal load;

	if(id == 0) {
		int i;
		load.id=0;
		load.tipo=1;
		for(i=0; i<3; i++)
			load.lojas[i]=1;

		for(i=0; i<10; i++)
			load.monstros[i]=0;

		strcpy(load.nome,"Lunaris");
		strcpy(load.descricao,"Capital religiosa da religiao adorante a a deusa Diana, um dos maiores bastioes dos seres mortais adeptos a religiao lunar");
		return load;
	}

	FILE *save;
	save = fopen("data/locais.dat","rb");

	while(fread(&load,sizeof(load),1,save))
		if(id == load.id) {
			fclose(save);
			return load;
		}
}

//Função parar carregar um inimigo direto de um arquivo
struct tMonstro carregarMonstro(int id) {
	struct tMonstro load;
	FILE *save;
	save = fopen("data/monstros.dat","rb");

	while(fread(&load,sizeof(load),1,save))
		if(id == load.id) {
			fclose(save);
			return load;
		}
}

//Função parar carregar um item direto de um arquivo
struct tItem carregarItem(int id) {
	struct tItem load;
	FILE *save;
	save = fopen("data/itens.dat","rb");

	while(fread(&load,sizeof(load),1,save))
		if(id == load.id) {
			fclose(save);
			return load;
		}
}

//Função para viajar entre os possíveis locais existentes
int viajar(int max) {
	int i, id;
	char escolha;
	
	struct tLocal local;
	printf("Escolha um dos locais disponiveis para voce viajar:\n");
	printf(" -[%s0%s] Lunaris\n",VERDE,CIANO);
	for(i=1; i<=max; i++) {
		local=carregarLocal(i);
		printf(" -[%s%i%s] %s\n",VERDE,i,CIANO,local.nome);
	}
	do {
		fflush(stdin);
		escolha=getch();
		id=escolha-'0';
	} while(id<0 || id>max);

	return id;
}

//Função pré-combate
struct tFicha explorar(struct tFicha jogador, struct tLocal local, int qtdItens) {
	struct tMonstro inimigo;
	int i;
	
	do{
		i=rand()%10;
	}while(local.monstros[i]==0);
	inimigo=carregarMonstro(local.monstros[i]);
			
	printf(AZUL);
	bordear();
	printf(VERDE);
	gotoxy(3,3);
	printf("Enquanto voce explorava o local, uma criatura lhe atacou!");
	gotoxy(3,4);
	printf("Aperte qualquer botao para iniciar o combate!");
	getch();
	jogador=combate(jogador, inimigo,qtdItens);
	return jogador;
}

//Função que responsável por gerenciar o combate
struct tFicha combate(struct tFicha jogador, struct tMonstro inimigo, int qtdItens){
	int i, posy=25, escapou=0, jAtaque=0, varP, varN, iAtaque, danoJ, danoI, exp, ouro;
	char tecla;
	
	for(i=0;i<8;i++)
		jAtaque+=jogador.equipamentos[i].ataque;	
	
	jAtaque=jAtaque+jogador.forca+jogador.inteligencia;
	iAtaque=inimigo.forca+inimigo.destreza;
	
	clrscr();
	printf(AZUL);
	bordear();
	printf(BRANCO);
	desenharArteXY("artes/batalha.txt",20,12,0,1);
	printf(VERDE);
	gotoxy(3,10);
	printf(AZUL);
	for(i=0; i<120; i++)
		printf("\xB1");
	gotoxy(3,24);
	printf(AZUL);
	for(i=0; i<120; i++)
		printf("\xB1");
		
	for(i=24 ;i<30; i++) {
		gotoxy(16,i);
		printf("\xB1\xB1");
	}
	for(i=24 ;i<30; i++) {
		gotoxy(105,i);
		printf("\xB1\xB1");
	}		
		
	printf(AZUL);
	gotoxy(3,26);
	for(i=0; i<15; i++)
		printf("\xB1");
	gotoxy(3,28);
	for(i=0; i<15; i++)
		printf("\xB1");	
	gotoxy(3,29);
	gotoxy(106,26);
	for(i=0; i<15; i++)
		printf("\xB1");	
	gotoxy(106,28);
	for(i=0; i<15; i++)
		printf("\xB1");	
	do{
		srand(time(NULL));
		gotoxy(3,6);
		printf(VERDE);
		printf("Level do inimigo: %s%d       ",VERMELHO,inimigo.level);
		gotoxy(3,7);
		printf(VERDE);
		printf("Descricao do inimigo: %s%s       ",VERMELHO,inimigo.nome);
		gotoxy(3,8);
		printf(VERDE);
		printf("Vida do inimigo: %s%d      ",VERMELHO,inimigo.vida);
		gotoxy(3,9);
		printf(VERDE);
		printf("Descricao do inimigo: %s%s",VERMELHO,inimigo.descricao);
		printf(VERDE);
		gotoxy(107,25);
		printf("Level: %s%d",VERMELHO,jogador.level);
		gotoxy(107,27);
		printf(VERDE);
		printf("Vida: %s%d/%d ",VERMELHO,jogador.vida,jogador.vidaMax);
		gotoxy(107,29);
		printf(VERDE);
		printf("Pocoes: %s%d/%d",VERMELHO,jogador.qtdPocoes,MAX_POT);
		gotoxy(18,25);
		printf("Escolha uma de suas acoes!                                                             ");
		gotoxy(3,25);
		if(posy==25){
			printf(VERMELHO);
		}else
			printf(VERDE);
		printf("ATACAR");	
		gotoxy(3,27);
		if(posy==27){
			printf(VERMELHO);
		}else
			printf(VERDE);		
		printf("CORRER");
		gotoxy(3,29);
		if(posy==29){
			printf(VERMELHO);
		}else
			printf(VERDE);
		printf("USAR POCAO");
		fflush(stdin);
		tecla=toupper(getch());
		gotoxy(18,25);
		printf("                          ");
		printf(VERMELHO);
		switch(tecla) {			
			case 'P':
				if(posy<29){
					posy+=2;
					}
					
				break;
				
			case 'H':
				if(posy>25){
					posy-=2;
				}
				break;
				
			case 13:
				if(posy==25){
					danoI=0;
					varP=rand()%10;
					varN=rand()%10;
					danoJ=jAtaque+varP-varN-inimigo.armadura;
					inimigo.vida-=danoJ;
					if(inimigo.vida>0){
						varP=rand()%10;
						varN=rand()%10;
						danoI=iAtaque+varP-varN-jogador.armadura;
						if(danoI<0)
							danoI=0;
						jogador.vida-=danoI;
					}
					gotoxy(18,25);
					printf("Voce atingiu seu inimigo com %s%d%s de dano e recebeu %s%d%s de dano!",VERDE,danoJ,VERMELHO,VERDE,danoI,VERMELHO);					
				}else if(posy==27){
					i=rand()%100;
					gotoxy(18,25);
					if(i>54){
						escapou=1;
						printf("Voce conseguiu fugir! Pressione qualquer tecla para prosseguir");
					}else{
						danoI=0;						
						varP=rand()%10;
						varN=rand()%10;
						danoI=iAtaque+varP-varN-jogador.armadura;
						if(danoI<0)
							danoI=0;
						jogador.vida-=danoI;
						printf("Voce nao conseguiu fugir e recebeu %s%d%s de dano! Pressione quaquer tecla para prosseguir",VERDE,danoI,VERMELHO);		
					}												
				}else{
					gotoxy(18,25);
					if(jogador.qtdPocoes>0){				
						jogador.qtdPocoes--;
						jogador.vida=jogador.vidaMax;
						printf("Voce bebeu uma de suas pocoes e recuperou a sua vida!");
					}else
						printf("Voce nao tem mais pocoes!");
				}
				if(jogador.vida<=0){
					gotoxy(19,25);
					printf("Voce morreu!");
					getch();
					return jogador;
				}				
				
				getch();
				break;		
		}
	}while(inimigo.vida >0 && escapou != 1);
	clrscr();
	if(escapou==1){
	}
	else if(inimigo.vida<=0){	
		i=rand()%100;
		if(i>70){
			if(jogador.qtdItens>=MAX_INV){
				printf("Voce encontrou um item porem seu inventario estava cheio!");
			}else{				
				do{
					i=rand()%qtdItens;
				}while(i==0);
				jogador.inventario[jogador.qtdItens]=i;
				jogador.qtdItens++;
				printf("Parabens, voce obteve um item! Cheque seu inventario para descobrir qual foi\n");
			}
		}
		ouro=rand()%25;
		jogador.ouro+=ouro;
		exp=(rand()%50+1)*inimigo.level;
		jogador.experiencia+=exp;
		jogador.experienciaTotal+=exp;
		printf("Parabens, voce obteve %s%d%s pontos de experiencia e %s%d%s de ouro\n",VERDE,exp,VERMELHO,VERDE,ouro ,VERMELHO);
		if(jogador.experiencia>=jogador.proxL){
			jogador=levelUp(jogador);
			printf("Parabens, voce subiu para o level %s%d%s! Agora voce esta mais poderoso",VERDE,jogador.level,VERMELHO);
			jogador.proxL=proximoLevel(jogador);
		}
		getch();
	}	
	return jogador;
}

//Função que identifica e controla as possíveis lojas que podem ser escolhidas de acordo com a cidade
struct tFicha lojas(struct tLocal local, int qtdItens, struct tFicha jogador) {
	int i, j=0, meio=48, posY=14, comprar=0;
	char tecla;
	char t1[]={0xC9,0xCB,0xBB,0xC9,0xCD,0xBB,0xCB,0x20,0x20,0xCB,0xC9,0xCD,0xBB,0xCB,0xCD,0xBB,0xC9,0xBB,0xC9,0xC9,0xCD,0xBB,0x0A};
	char t2[]={0x20,0xBA,0x20,0xCC,0xCD,0xB9,0xC8,0xBB,0xC9,0xBC,0xBA,0xB9,0x20,0xCC,0xCB,0xBC,0xBA,0xBA,0xBA,0xCC,0xCD,0xB9};
	char t3[]={0x20,0xCA,0x20,0xCA,0x20,0xCA,0x20,0xC8,0xBC,0x20,0xC8,0xCD,0xBC,0xCA,0xC8,0xCD,0xBC,0xC8,0xBC,0xCA,0x20,0xCA};
	char f1[]={0xC9,0xCD,0xBB,0xC9,0xCD,0xBB,0xCB,0xCD,0xBB,0xCB,0xCD,0xBB,0xC9,0xCD,0xBB,0xCB,0xCB,0xCD,0xBB,0xC9,0xCD,0xBB};
	char f2[]={0xCC,0xB9,0x20,0xBA,0xB9,0x20,0xCC,0xCB,0xBC,0xCC,0xCB,0xBC,0xBA,0xB9,0x20,0xBA,0xCC,0xCB,0xBC,0xBA,0x20,0xBA};
	char f3[]={0xC8,0x20,0x20,0xC8,0xCD,0xBC,0xCA,0xC8,0xCD,0xCA,0xC8,0xCD,0xC8,0xCD,0xBC,0xCA,0xCA,0xC8,0xCD,0xC8,0xCD,0xBC};
	char a1[]={0xC9,0xCD,0xBB,0xCB,0x20,0x20,0xC9,0xCD,0xBB,0x20,0xCB,0x20,0xCB,0xCB,0xC9,0xCB,0xBB,0xCB,0xC9,0xCD,0xBB,0xC9,0xCB,0xBB,0xC9,0xCD,0xBB};
	char a2[]={0xCC,0xCD,0xB9,0xBA,0x20,0x20,0xBA,0xCD,0xCE,0xBB,0xBA,0x20,0xBA,0xBA,0xBA,0xBA,0xBA,0xBA,0xC8,0xCD,0xBB,0x20,0xBA,0x20,0xCC,0xCD,0xB9};
	char a3[]={0xCA,0x20,0xCA,0xCA,0xCD,0xBC,0xC8,0xCD,0xBC,0xC8,0xC8,0xCD,0xBC,0xCA,0xCA,0x20,0xCA,0xCA,0xC8,0xCD,0xBC,0x20,0xCA,0x20,0xCA,0x20,0xCA};
	clrscr();
	printf(AZUL);
	bordear();
	
	_setcursortype(_NOCURSOR);
	
	gotoxy(75,29);
	printf(VERMELHO);
	printf("ESC - Voltar");
	gotoxy(45,29);
	printf("ENTER - Selecionar Loja");
	gotoxy(3,29);
	printf("SETAS DO TECLADO - Navegar pelo menu");

	printf(CIANO);
	gotoxy(5,25);


	do{
		if(posY==14){
			printf(VERDE);
		}else
			printf(BRANCO);
		gotoxy(meio,13);		
		printf("%s",t1);
		gotoxy(meio,14);
		printf("%s",t2);
		gotoxy(meio,15);
		printf("%s",t3);
		if(posY==17){
			printf(VERDE);
		}else
			printf(BRANCO);
		gotoxy(meio,16);		
		printf("%s",f1);
		gotoxy(meio,17);
		printf("%s",f2);
		gotoxy(meio,18);
		printf("%s",f3);
		if(posY==20){
			printf(VERDE);
		}else
			printf(BRANCO);
		gotoxy(meio,19);		
		printf("%s",a1);
		gotoxy(meio,20);
		printf("%s",a2);
		gotoxy(meio,21);
		printf("%s",a3);
		fflush(stdin);	
		tecla=toupper(getch());
		switch(tecla) {
			case 'H':
				if(posY==17){
					posY=14;
				}
				else if(posY==20){
					posY=17;
				}
					
				break;
			case 'P':
				if(posY==14){
					posY=17;
				}
				else if(posY==17){
					posY=20;
				}
				break;
			case 13:
				if(posY == 14 && local.lojas[2]==1){
					comprar=1;
				}else if(posY == 17 && local.lojas[0]==1){
					comprar=1;
				}else if(posY == 20 && local.lojas[1]==1){
					comprar=1;
				}else if (posY == 14){				
					printf(VERMELHO);
					gotoxy(45,3);
					printf("Essa cidade nao tem uma taverna!!");
					getch();
					gotoxy(45,3);
					printf("                                 ");
				}else if (posY == 17){					
					printf(VERMELHO);
					gotoxy(45,3);
					printf("Essa cidade nao tem um ferreiro!!");
					getch();
					gotoxy(45,3);
					printf("                                 ");
				}else if (posY == 20){			
					printf(VERMELHO);
					gotoxy(45,3);
					printf("Essa cidade nao tem um alquimista!!");
					getch();
					gotoxy(45,3);
					printf("                                 ");
				}
				break;
				
			case 27:

				break;	
		}
	}while(comprar != 1 && tecla != 27);
	printf(RESETCOR);
	clrscr();
	
	if(comprar == 1 && posY == 17){
		jogador=ferreiro(jogador, qtdItens);
	}else 	if(comprar == 1 && posY == 20){
		jogador=alquimista(jogador);
	} else 	if(comprar == 1 && posY == 14){
		jogador=taverna(jogador);
	}
	
	
	return jogador;
}

//Função responsável por cuidar do encontro com a bruxa/alquimista, onde o personagem por reabastecer suas poções
struct tFicha alquimista(struct tFicha jogador){
	int qtd, valor;
	printf(AZUL);
	bordear();
	printf(BRANCO);
	desenharArteXY("artes/alquimista.txt",20,3,0,1);
	gotoxy(3,20);
	printf(VERDE);
	printf("Voce adentra a pequena cabana magica e se depara com a bruxa e alquimista Parmes!");
	gotoxy(3,21);
	printf("Parmes: %sQuantas pocoes voce deseja comprar, jovem aventureiro? Cada uma custa 20 de ouro",VERMELHO);
	gotoxy(3,22);
	printf(VERDE);
	printf("%s: %s",jogador.nome,VERMELHO);
	scanf("%d",&qtd);
	valor=qtd*20;
	if(qtd<=0){
		gotoxy(3,23);
		printf(VERDE);
		printf("Parmes: %sVolte quando tiver intencoes de comprar minhas pocoes!",VERMELHO);
	}else if(qtd+jogador.qtdPocoes>MAX_POT){
		gotoxy(3,23);
		printf(VERDE);
		printf("Parmes: %sInfelizmente voce nao pode carregar tantas pocoes assim, volte quando tiver espaco!",VERMELHO);
	}else if(valor>jogador.ouro){
		gotoxy(3,23);
		printf(VERDE);
		printf("Parmes: %sInfelizmente voce nao pode pagar por essas pocoes, volte quando tiver dinheiro!",VERMELHO);
	}else{
		gotoxy(3,23);
		printf(VERDE);
		printf("Parmes: %sAqui esta suas %d pocoes, faca bom proveito delas!",VERMELHO, qtd);
		jogador.ouro-=valor;
		jogador.qtdPocoes+=qtd;
	}
	getch();
	return jogador;
}

//Função responsável por cuidar do encontro com a taverna, onde o personagem pode dormir para recuperar suas energias
struct tFicha taverna(struct tFicha jogador){
	char tecla;
	clrscr();
	printf(AZUL);
	bordear();						
	gotoxy(3,2);
	printf(VERDE);
	printf("Bem vindo a a taverna, aventureiro, deseja pernoitear e recuperar suas energias por apenas 10 moedas de ouro?");
	gotoxy(3,3);	
	printf("        [%sS%s]im           [%sN%s]ao",CIANO,VERDE,VERMELHO,VERDE);
	
	do{		
		fflush(stdin);		
		tecla=toupper(getch());
	}while(tecla != 'N' && tecla != 'S');
	
	clrscr();
	printf(AZUL);
	bordear();
	gotoxy(3,2);
	printf(VERDE);
	if(tecla=='S'){
		if(jogador.ouro>10){		
			printf("Voce decidiu passar a densa noite em uma confortante cama na taverna da cidade.");
			gotoxy(3,3);
			printf("Apos acordar voce se sente revigorado e pronto para uma nova aventura.");
			jogador.ouro-=10;
			jogador.vida=jogador.vidaMax;
		}else{
			printf(VERMELHO);
			printf("Infelizmente voce nao tem ouro o suficente para alugar um quarto!");
		}
		
	}else{
		printf("Voce decidiu passar a densa noite nas ruas, o frio e forte e a escuridao mais ainda.");
		gotoxy(3,3);
		printf("Apos acordar voce se pergunta se era melhor ter encontrado um lugar decente para dormir.");		
		
	}
		gotoxy(3,4);
		printf("Aperte qualquer tecla para continuar.");	
		getch();
		
	return jogador;	
}

//Função responsável por cuidar do encontro com o ferreiro, onde o personagem compra itens		
struct tFicha ferreiro(struct tFicha jogador, int qtdItens){
	int id[5],i;
	char tecla;
	struct tItem ferreiro[5], aux;
	char f1[]={0xC9,0xCD,0xBB,0xC9,0xCD,0xBB,0xCB,0xCD,0xBB,0xCB,0xCD,0xBB,0xC9,0xCD,0xBB,0xCB,0xCB,0xCD,0xBB,0xC9,0xCD,0xBB};
	char f2[]={0xCC,0xB9,0x20,0xBA,0xB9,0x20,0xCC,0xCB,0xBC,0xCC,0xCB,0xBC,0xBA,0xB9,0x20,0xBA,0xCC,0xCB,0xBC,0xBA,0x20,0xBA};
	char f3[]={0xC8,0x20,0x20,0xC8,0xCD,0xBC,0xCA,0xC8,0xCD,0xCA,0xC8,0xCD,0xC8,0xCD,0xBC,0xCA,0xCA,0xC8,0xCD,0xC8,0xCD,0xBC};
	char a1[]={0xC9,0xCD,0xBB,0xCB,0x20,0x20,0xC9,0xCD,0xBB,0x20,0xCB,0x20,0xCB,0xCB,0xC9,0xCB,0xBB,0xCB,0xC9,0xCD,0xBB,0xC9,0xCB,0xBB,0xC9,0xCD,0xBB};
	
	FILE *itens;
	itens = fopen("data/itens.dat","rb");	
	for(i=0;i<5;i++){
		do{
			id[i]=rand()%qtdItens;
		}while(id[i]==0);	
		fseek(itens, 0, SEEK_SET);
		while(fread(&aux,sizeof(aux),1,itens)){
			if(id[i]==aux.id)
				ferreiro[i]=aux;
		}
	}
	fclose(itens);
	printf(AZUL);
	bordear();
	gotoxy(95,29);
	printf(VERMELHO);
	printf("ESC - Sair da Loja");
	gotoxy(70,29);
	printf("ENTER - Comprar Item");
	gotoxy(30,29);
	printf("SETAS DO TECLADO - Navegar pelo menu");
	printf(BRANCO);
	
	desenharArteXY("artes/ferreiro.txt",78,3,0,1);

	printf(BRANCO);
	gotoxy(40,3);		
	printf("%s",f1);
	gotoxy(40,4);
	printf("%s",f2);
	gotoxy(40,5);
	printf("%s",f3);
	
	
	printf(AMARELO);
	for(i=8;i<28;i++){
		gotoxy(81,i);
		printf("|");
	}
	gotoxy(3,7);
		printf(AMARELO);
		printf("______________________________________________________________________________");
		gotoxy(3,9);
		printf("______________________________________________________________________________|");
		gotoxy(3,11);
		printf("______________________________________________________________________________");
		gotoxy(3,13);
		printf("______________________________________________________________________________");
		gotoxy(3,15);
		printf("______________________________________________________________________________");
		gotoxy(3,17);
		printf("______________________________________________________________________________");
		gotoxy(3,19);
		printf("______________________________________________________________________________");
		gotoxy(3,21);
		printf("______________________________________________________________________________");
		gotoxy(3,23);
		printf("______________________________________________________________________________");
		gotoxy(3,25);
		printf("______________________________________________________________________________|");
		gotoxy(3,27);
		printf("______________________________________________________________________________|");
	i=0;
	do {
		printf(VERDE);
		gotoxy(3,8);
		printf("                                                                              ");
		gotoxy(3,8);
		printf("Nome: %s%s",BRANCO,ferreiro[i].nome);
		printf(VERDE);
		gotoxy(3,10);
		printf("                                                                              ");
		gotoxy(3,10);
		printf("Descricao: %s%s",BRANCO,ferreiro[i].descricao);
		printf(VERDE);
		gotoxy(3,12);
		printf("                                                                              ");
		gotoxy(3,12);
		printf("Ataque: %s%d",BRANCO,ferreiro[i].ataque);
		printf(VERDE);
		gotoxy(3,14);
		printf("                                                                              ");
		gotoxy(3,14);
		printf("Forca: %s%d",BRANCO,ferreiro[i].forca);
		printf(VERDE);
		gotoxy(3,16);
		printf("                                                                              ");
		gotoxy(3,16);
		printf("Inteligencia: %s%d",BRANCO,ferreiro[i].inteligencia);
		printf(VERDE);
		gotoxy(3,18);
		printf("                                                                              ");
		gotoxy(3,18);
		printf("Destreza: %s%d",BRANCO,ferreiro[i].destreza);
		printf(VERDE);
		gotoxy(3,20);
		printf("                                                                              ");
		gotoxy(3,20);
		printf("Vitalidade: %s%d",BRANCO,ferreiro[i].vitalidade);
		printf(VERDE);
		gotoxy(3,22);
		printf("                                                                              ");
		gotoxy(3,22);
		printf("Armadura: %s%d",BRANCO,ferreiro[i].armadura);
		printf(VERDE);
		gotoxy(3,24);
		printf("                                                                              ");
		gotoxy(3,24);
		printf("Resistencia: %s%d",BRANCO,ferreiro[i].resistencia);
		printf(VERDE);
		gotoxy(3,26);
		printf("                                                                              ");
		gotoxy(3,26);
		printf("Valor: %s%d",BRANCO,ferreiro[i].valor);
		fflush(stdin);
		tecla=toupper(getch());
		switch(tecla) {			
			case 'H':
				if(i<4){
					i++;
					}
					
				break;
				
			case 'P':
				if(i>0){
					i--;
				}
				break;
				
			case 13:
				if(jogador.ouro<ferreiro[i].valor){
					clrscr();	
					printf(VERMELHO);
					printf("Voce nao tem dinheiro o suficente para comprar o item! APERTE QUALQUER TECLA PARA CONTINUAR!");
					getch();
				}else if(jogador.qtdItens==MAX_INV){
					clrscr();	
					printf(VERMELHO);
					printf("Seu inventario esta cheio, nao e possível comprar o item! APERTE QUALQUER TECLA PARA CONTINUAR!");
					getch();
				}else{
					do{					
					clrscr();				
					printf(VERDE);
					printf("Tem certeza que deseja comprar o item %s%s?\n",BRANCO,ferreiro[i].nome);
					printf(VERDE);
					printf("[%sS%s]im           [%sN%s]ao",CIANO,VERDE,VERMELHO,VERDE);
					fflush(stdin);
					tecla=toupper(getch());
					}while(tecla != 'N' && tecla != 'S');
					if(tecla == 'S'){
						clrscr();
						jogador.inventario[jogador.qtdItens]=ferreiro[i].id;
						jogador.qtdItens++;
						jogador.ouro-=ferreiro[i].valor;
						printf("Parabens, o item foi adicionado com sucesso ao seu inventario! APERTE QUALQUER TECLA PARA CONTINUAR!");
						getch();
					}
				}
				return jogador;
				break;

			case 27:
				return jogador;
				break;
		}
	}while(1);	
}

//Função que mostra os itens que estão no inventário do personagem separados por tipo de itens, dando a possibilidade de equipar algum deles ou vende-los
struct tFicha inventario(struct tFicha jogador) {
	int i, j=0, pos=3, tam=5, tipo = 1, qtd[8], ouro;
	struct tItem aux, itensV[8][20];
	char tecla;
	for(i=0;i<8;i++){
		qtd[i]=0;
	}
	
	FILE *itens;
	itens = fopen("data/itens.dat","rb");
	for(i=0;i<jogador.qtdItens;i++){
		fseek(itens, 0, SEEK_SET);
		while(fread(&aux,sizeof(aux),1,itens)){
			if(jogador.inventario[i]==aux.id){
				itensV[aux.tipo][qtd[aux.tipo]]=aux;
				qtd[aux.tipo]++;
			}
		}
	}

	printf(AZUL);
	bordear();
	for(i=0; i<120; i++) {
		gotoxy(i,4);
		printf("\xB1");
	}
	gotoxy(3,2);
	printf("%sELMOS%s\xB1\xB1\n\n\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1",VERDE, AZUL);
	gotoxy(8,3);
	printf("\xB1\xB1");
	gotoxy(10,2);
	printf("%sARMADURAS%s\xB1\xB1\n\n\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1",VERDE, AZUL);
	gotoxy(19,3);
	printf("\xB1\xB1");
	gotoxy(21,2);
	printf("%sARMAS%s\xB1\xB1\n\n\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1",VERDE, AZUL);
	gotoxy(26,3);
	printf("\xB1\xB1");
	gotoxy(28,2);
	printf("%sCINTOS%s\xB1\xB1\n\n\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1",VERDE, AZUL);
	gotoxy(34,3);
	printf("\xB1\xB1");
	gotoxy(36,2);
	printf("%sLUVAS%s\xB1\xB1\n\n\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1",VERDE, AZUL);
	gotoxy(41,3);
	printf("\xB1\xB1");
	gotoxy(43,2);
	printf("%sBOTAS%s\xB1\xB1\n\n\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1",VERDE, AZUL);
	gotoxy(48,3);
	printf("\xB1\xB1");
	gotoxy(50,2);
	printf("%sCALCAS%s\xB1\xB1\n\n\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1\xB1",VERDE, AZUL);
	gotoxy(56,3);
	printf("\xB1\xB1");
	gotoxy(58,2);
	printf(VERDE);
	printf("Jogador: %s%15s   ",BRANCO,jogador.nome);
	printf(VERDE);
	printf("Pocoes: %s%d/5",BRANCO,5);
	gotoxy(58,3);
	printf(VERDE);
	printf("Quantidade de itens: %s%d/50",BRANCO,jogador.qtdItens);
	gotoxy(95,29);
	printf(VERMELHO);
	printf("ESC - Sair do inventario");
	gotoxy(76,29);
	printf("E - Equipar Item");
	gotoxy(58,29);
	printf("V - Vender Item");
	gotoxy(19,29);
	printf("SETAS DO TECLADO - Navegar pelo menu");


	do {
		if(qtd[tipo]==0){
			gotoxy(3,5);
			printf(VERMELHO);
			printf("Voce nao tem nenhum equipamento desse tipo!");
		}else{
			printf(BRANCO);
			gotoxy(3,5);
			printf("Nome do item: %s",itensV[tipo][j].nome);
			gotoxy(3,6);
			printf("Descricao do item: %s",itensV[tipo][j].descricao);
			gotoxy(3,7);
			printf("Ataque do item: %d",itensV[tipo][j].ataque);
			gotoxy(3,8);
			printf("Forca do item: %d",itensV[tipo][j].forca);
			gotoxy(3,9);
			printf("Inteligencia do item: %d",itensV[tipo][j].inteligencia);
			gotoxy(3,10);
			printf("Destreza do item: %d",itensV[tipo][j].destreza);
			gotoxy(3,11);
			printf("Vitalidade do item: %d",itensV[tipo][j].vitalidade);
			gotoxy(3,12);
			printf("Armadura do item: %d",itensV[tipo][j].armadura);
			gotoxy(3,13);
			printf("Resistencia do item: %d",itensV[tipo][j].resistencia);
			gotoxy(3,14);
			printf("Valor do item: %d",itensV[tipo][j].valor);
		}
		gotoxy(pos,3);
		printf(BRANCO);
		for(i=0; i<tam; i++) {
			printf("*");
		}
		fflush(stdin);
		tecla=toupper(getch());
		for(i=5;i<15;i++){
			gotoxy(3,i);
					printf("                                                                                                                                             ");
		}
		gotoxy(pos,3);
		for(i=0; i<tam; i++) {
			printf(" ");
		}
		
		switch(tecla) {
			case'K':
				if(pos== 50) {
					tam=5;
					pos=43;
					tipo = 3; // Botas
				} else if(pos == 43) {
					tam=5;
					pos=36;
					tipo = 2; //Luvas
				} else if(pos == 36) {
					tam=6;
					pos=28;
					tipo = 6; //Cintos
				} else if(pos == 28) {
					tam=5;
					pos=21;
					tipo = 5; //Armas
				} else if(pos == 21) {
					tam=9;
					pos=10;
					tipo = 0; //Armadura
				} else if(pos == 10) {
					tam=5;
					pos=3;
					tipo = 1; //Elmo
				}
				j=0;
				break;

			case'M':
				if(pos== 3) {
					tam=9;
					pos=10;
					tipo = 0; //Armadura
				} else if(pos == 10) {
					tam=5;
					pos=21;
					tipo = 5; //Armas
				} else if(pos == 21) {
					tam=6;
					pos=28;
					tipo = 6; //Cintos
				} else if(pos == 28) {
					tam=5;
					pos=36; 
					tipo = 2; //Luvas
				} else if(pos == 36) {
					tam=5;
					pos=43; 
					tipo = 3;// Botas
				} else if(pos == 43) {
					tam=6;
					pos=50;
					tipo = 4; // Calcas
				}
				j=0;
				break;
				
			case 'H':
				if(j<qtd[tipo]-1){
						j++;
					}
					
				break;
				
			case 'P':
				if(j>0){
					j--;
				
				}
				break;
				
			case 'E':
				if(qtd[tipo]>0){
					if(jogador.equipamentos[tipo].id==0){				
						jogador.equipamentos[tipo]=itensV[tipo][j];
						jogador.qtdItens--;
					}else{
						i=0;
						while(jogador.inventario[i]!=itensV[tipo][j].id){
							i++;
						}
						jogador.inventario[i]=jogador.equipamentos[tipo].id;
						jogador.equipamentos[tipo]=itensV[tipo][j];
						jogador.inventario[jogador.qtdItens]=0;
					}		
				}else{
					clrscr();
					printf(VERMELHO);
					printf("Voce nao tem nenhum item desse tipo para equipar!");
					getch();
				}
				return jogador;
				break;
			
			case 'V':
				clrscr();
				gotoxy(3,15);
				printf(VERDE);
				printf("Tem certeza que vender o item?\n");
				gotoxy(3,16);
				printf("[%sS%s]im           [%sN%s]ao",CIANO,VERDE,VERMELHO,VERDE);
				gotoxy(3,17);
				do{
					fflush(stdin);
					tecla=toupper(getch());
				}while(tecla != 'S' && tecla != 'N');
				gotoxy(3,19);
				if(tecla == 'S'){
					ouro=ceil(itensV[tipo][j].valor*0.70);			
					jogador.ouro+=ouro;
					printf("Voce vendeu o item por %d de ouro!",ouro);
					i=0;
					while(jogador.inventario[i]!=itensV[tipo][j].id){
						i++;
					}
					jogador.qtdItens--;
					jogador.inventario[i]=jogador.inventario[jogador.qtdItens];
					jogador.inventario[jogador.qtdItens]=0;
				}else
					printf("Voce desistiu da venda!");
				
				getch();
				return jogador;
				break;
			case 27:
				break;
		}
	} while(tecla != 27);

	return jogador;
}

//Função responsável por criar as bordas
void bordear() {
	int i;
	for(i=0; i<120; i++)
		printf("\xB1");

	for(i=0; i<28; i++) {
		gotoxy(0,i);
		printf("\xB1\xB1\n");
	}

	for(i=0; i<120; i++)
		printf("\xB1");


	for(i=1; i<30; i++) {
		gotoxy(119,i);
		printf("\xB1\xB1");
	}
}

//Função que recolhe as quantidades de locais e de itens
void recolherDados(int *qtdLoc, int *qtdIte){
	FILE *qtdLocais;
	FILE *qtdItens;
	qtdLocais = fopen("quantidadeLocais.txt","r");
	qtdItens = fopen("quantidadeItens.txt","r");
	fscanf(qtdLocais,"%d",&*qtdLoc);
	fscanf(qtdItens,"%d",&*qtdIte);
	fclose(qtdItens);
	fclose(qtdLocais);
}

//Funcao para calcular a condição para alcançar o próximo level
int proximoLevel(struct tFicha jogador){
	int base=1000, expoente=2, prox;
	prox=(base*(pow(jogador.level,2)));
	return prox;
}

//Funcao pra atribuicao de status caso a condicao de passar para o próximo level tenha sido atingida
struct tFicha levelUp(struct tFicha jogador){
	jogador.vitalidade+=2+jogador.vitalidade*0.5;
	jogador.forca+=2+jogador.forca*0.5;
	jogador.destreza+=2+jogador.destreza*0.5;
	jogador.inteligencia+=2+jogador.inteligencia*0.5;
	jogador.level++;
	jogador.experiencia=0;
	jogador.vidaMax+=jogador.vitalidade*0.5;
	jogador.mana+=jogador.inteligencia*0.5;
	return jogador;
}
