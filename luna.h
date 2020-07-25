#ifndef _LUNA_HEADER
#define _LUNA_HEADER 1
#include <stdio.h>
#include <string.h>
#include "conio2.h"

#define MAX_INV 50
#define MAX_POT 5

//Declarações das cores usadas no processo
#define RESETCOR "\033[0m"
#define VERDE "\033[1;32m"
#define AMARELO "\033[0;33m"
#define VERMELHO "\x1b[1;31m"
#define BRANCO "\x1B[1;37m"
#define AZUL "\033[1;34m"
#define CIANO "\033[1;36m"
#define AMARELOC "\033[01;33m"

//Declaração dos caracters da tabela ASCII
#define RETAH 205
#define RETAV 186
#define CANTOCD 187
#define CANTOBD 188
#define CANTOCE 201
#define CANTOBE 200

//Definições dos tipos de structs
struct tItem {
	int id;
	char nome[50];
	char descricao[100];
	int vida;
	int mana;
	int ataque;
	int armadura;
	int resistencia;
	int destreza;
	int forca;
	int inteligencia;
	int vitalidade;
	int valor;
	int tipo;
};

struct tFicha {
	int id;
	char nome[50];
	char classe[20];
	int ouro;
	int level;
	int proxL;
	int vida;
	int vidaMax;
	int mana;
	int armadura;
	int resistencia;
	int destreza;
	int forca;
	int inteligencia;
	int vitalidade;
	int inventario[50];
	struct tItem equipamentos[8];
	int qtdItens;
	int qtdPocoes;
	int localAtual;
	int experiencia;
	int experienciaTotal;
};

struct tMonstro {
	int id;
	char nome[50];
	char descricao[100];
	int level;
	int vida;
	int mana;
	int armadura;
	int resistencia;
	int destreza;
	int forca;
	int inteligencia;
	int vitalidade;
};

struct tLocal {
	int id;
	int tipo;
	char nome[50];
	char descricao[200];
	int monstros[10];
	int lojas [3];
};

int receberId(void);
int menu(void);
void bordear();

//Protótipos das funções TF
int menu_inicial();
void escrever(char *texto);
struct tFicha* criarJogador();
void escolherClasse(struct tFicha *novo);
void mostrarPersonagem(struct tFicha personagem);
void salvarPersonagem(struct tFicha jogador);
struct tFicha carregarPersonagem(int id);
int contarSlots();
void excluirPersonagem(int id);
struct tMonstro carregarMonstro(int id);
struct tLocal carregarLocal(int id);
struct tFicha explorar(struct tFicha jogador, struct tLocal local, int qtdItens);
struct tFicha lojas(struct tLocal local, int qtdItens, struct tFicha jogador);
int viajar(int max);
struct tFicha inventario(struct tFicha jogador);
void recolherDados(int *qtdLoc, int *qtdIte);
int menu_jogo(struct tLocal local, struct tFicha jogador);
struct tFicha ferreiro(struct tFicha jogador, int qtdItens);
struct tFicha taverna(struct tFicha jogador);
struct tFicha alquimista(struct tFicha jogador);
struct tFicha combate(struct tFicha jogador, struct tMonstro inimigo, int qtdItens);
int proximoLevel(struct tFicha jogador);
struct tFicha levelUp(struct tFicha jogador);

//Função usada nos diversos cruds para desenhar as artes ASCII lendo arquivos
void desenharArte(char *arte) {
	FILE *arteP;
	arteP = fopen(arte,"r");
	char string[100];
	while(fgets(string,sizeof(string),arteP) != NULL)
		printf("%s",string);

	fclose(arteP);
}

void desenharArteXY(char *arte, int x, int y, int incrementoX, int incrementoY) {
	FILE *arteP;
	arteP = fopen(arte,"r");
	char string[100];
	while(fgets(string,sizeof(string),arteP) != NULL){
		gotoxy(x,y);
		printf("%s",string);
		x+=incrementoX;
		y+=incrementoY;
	}

	fclose(arteP);
}

void mostrarItem(struct tItem item) {
	char tipo[17];
	if(item.tipo == 0) {
		strcpy(tipo,"Armadura");
	} else if(item.tipo == 1) {
		strcpy(tipo,"Elmo");
	} else if(item.tipo == 2) {
		strcpy(tipo,"Luva");
	} else if(item.tipo == 3) {
		strcpy(tipo,"Bota");
	} else if(item.tipo == 4) {
		strcpy(tipo,"Calca");
	} else if(item.tipo == 5) {
		strcpy(tipo,"Arma");
	} else if(item.tipo == 6) {
		strcpy(tipo,"Cinto");
	} else if(item.tipo == 7) {
		strcpy(tipo,"Arma Secundaria");
	}
	printf("%sDescricao: %s\n",VERDE,item.descricao);
	printf(AMARELOC);	
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOCE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOCD);
	printf("%c%sID: %32i%s%5c\n",RETAV,VERDE,item.id,AMARELOC,RETAV);
	printf("%c%sNome: %30s%s%5c\n",RETAV,VERDE,item.nome,AMARELOC,RETAV);
	printf("%c%sVida: %30i%s%5c\n",RETAV,VERDE,item.vida,AMARELOC,RETAV);
	printf("%c%sMana: %30i%s%5c\n",RETAV,VERDE,item.mana,AMARELOC,RETAV);
	printf("%c%sArmadura: %26i%s%5c\n",RETAV,VERDE,item.armadura,AMARELOC,RETAV);
	printf("%c%sResistencia: %23i%s%5c\n",RETAV,VERDE,item.resistencia,AMARELOC,RETAV);
	printf("%c%sDestreza: %26i%s%5c\n",RETAV,VERDE,item.destreza,AMARELOC,RETAV);
	printf("%c%sForca: %29i%s%5c\n",RETAV,VERDE,item.forca,AMARELOC,RETAV);
	printf("%c%sInteligencia: %22i%s%5c\n",RETAV,VERDE,item.inteligencia,AMARELOC,RETAV);
	printf("%c%sVitalidade: %24i%s%5c\n",RETAV,VERDE,item.vitalidade,AMARELOC,RETAV);
	printf("%c%sValor: %29i%s%5c\n",RETAV,VERDE,item.valor,AMARELOC,RETAV);
	printf("%c%sTipo: %30s%s%5c\n",RETAV,VERDE,tipo,AMARELOC,RETAV);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",CANTOBE,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,RETAH,CANTOBD);

}

void HideCursor(){
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

#endif
