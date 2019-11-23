#include<stdio.h>
#include<stdlib.h>

typedef struct PC{
	int id;
	int paquetes;
	int nAristas;
	struct Pc *sig;
	struct Arista *arista;
}PC;
typedef struct Router{
	int id;
	int nAristas;
	struct Router *sig;
	struct Arista *arista;
}Router;
typedef struct Arista{
	int peso;
	struct Arista *sig;;
	struct Router *router;
	struct Pc *pc;
}Arista;

int agregar_PC(PC *pc, int id, int paquetes);
int agregar_Router(Router *router,int id);

int agregar_PC(PC *pc, int id, int paquetes){

	PC *nuevo = (PC*)malloc(sizeof(PC));

	if(!nuevo)
		return 0;

	nuevo->id = id;
	nuevo->paquetes = paquetes;
	nuevo->nAristas = 0;
	nuevo->arista = NULL;
	*pc = nuevo;
	return 1;
}

int agregar_Router(Router *router,int id){

	Router *nuevo = (Router*)malloc(sizeof(Router));

	if(!nuevo)
		return 0;

	nuevo->id = id;
	nuevo->arista = NULL;
	*router = nuevo;
	return 1;
}