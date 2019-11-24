#include<stdio.h>
#include<stdlib.h>

typedef struct PC{
	int id;
	int paquetes;
	int nAristas;
	struct PC *sig;
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
	struct Arista *sig;
	struct Router *Orouter;
	struct Router *Drouter;
	struct PC *pc;
}Arista;

int agregar_PC(PC **pc,Router *router);
int agregar_Router(Router **router,PC *pc);
int crear_arista(Router *router,PC *pc);
void imprime_Aristas(Arista *arista);
void imprime_Routers(Router *router);
void imprime_PCs(PC *pc);
Arista *busca_Arista(Arista *arista, int pc, int Orouter, int Drouter);
Router *busca_Router(Router *router, int id);
PC *busca_PC(PC *pc, int id);

int nRouters = 0, nPCs = 0;
int main(){

	Router *router = NULL;
	PC *pc = NULL;
	int op;

	do{

		printf("Seleccione una opcion\n");
		printf("1.-Agregar Router\n");
		printf("2.-Agregar PC\n");
		printf("3.-Buscar Router\n");
		printf("4.-Buscar PC\n");
		printf("5.-Imprime Routers\n");
		printf("6.-Imprime PCs\n");
		printf("7.-Salir\n");
		scanf("%d",&op);

		switch(op){

			case 1:{
				agregar_Router(&router,pc);
				break;
			}
			case 2:{
				agregar_PC(&pc,router);
				break;
			}
			case 3:{

				int busR;
				printf("Router a buscar\n");
				scanf("%d",&busR);
				if(busca_Router(router,busR) == NULL)
					printf("No se encontro\n");
				else{
					printf("Encontrado\n");
					printf("id: %d \n",busca_Router(router,busR)->id);
					printf("Numero de Aristas: %d\n",busca_Router(router,busR)->nAristas);
				}
				break;
			}
			case 4:{
				int busPC;
				printf("PC a buscar\n");
				scanf("%d",&busPC);
				if(busca_PC(pc,busPC) == NULL)
					printf("No se encontro\n");
				else{
					printf("Encontrado\n");
					printf("id: %d \n",busca_PC(pc,busPC)->id);
					printf("Numero de Aristas: %d\n",busca_PC(pc,busPC)->nAristas);
					printf("Paquetes: %d\n",busca_PC(pc,busPC)->paquetes);
				}
				break;
			}
			case 5:{
				imprime_Routers(router);
				break;
			}
			case 6:{
				imprime_PCs(pc);
				break;
			}
			case 7:{
				break;
				default:
				printf("Opcion Invalida\n");
				break;
			}
		}

	}while(op != 7);
return 0;
}

int agregar_PC(PC **pc, Router *router){

	int x = 0;
	PC *nuevo = (PC*)malloc(sizeof(PC));

	if(!nuevo)
		return 0;

	do{
		nuevo->id = rand() % 101;
		if (busca_PC(*(pc),nuevo->id) == NULL && busca_Router(router,nuevo->id) == NULL)
			x++;
	}while(x == 0);
	nuevo->paquetes = rand() % 101;
	nuevo->nAristas = 0;
	nuevo->arista = NULL;
	nuevo->sig = *pc;
	*pc = nuevo;
	nPCs++;
	return 1;
}

int agregar_Router(Router **router, PC *pc){

	Router *nuevo = (Router*)malloc(sizeof(Router));
	int x = 0;

	if(!nuevo)
		return 0;

	do{
		nuevo->id = rand() % 101;
		if(busca_Router(*(router),nuevo->id) == NULL && busca_PC(pc,nuevo->id) == NULL)
			x++;
	}while(x == 0);
	nuevo->arista = NULL;
	nuevo->sig = *router;
	*router = nuevo;
	nRouters++;
	return 1;
}

int crear_arista(Router *router, PC *pc){

	PC *Opc = NULL;
	Arista *aux = NULL;
	Router *Orouter = NULL, *Drouter = NULL;
	int x=0,y=0;

	do{
		int origen = rand() % 101;
		if(busca_PC(pc,origen) != NULL){
			Opc = busca_PC(pc,origen);
			y++;
		}else{
			if(busca_Router(router, origen) != NULL){
				Orouter = busca_Router(router, origen);
				y++;
			}
		}
	}while(y == 0);

	do{
		int destino = rand() % 101;
		if(busca_Router(router, destino) != NULL){
			Drouter = busca_Router(router, destino);
			x++;
		}
	}while(x == 0);

}

void imprime_Aristas(Arista *arista){

	if(!arista)
		return;

	printf("Peso: %d\n", arista->peso);
	printf("Origen Router: %d\n", arista->Orouter->id);
	printf("Destino Router%d\n", arista->Drouter->id);
	printf("PC: %d\n", arista->pc->id);
	return imprime_Aristas(arista->sig);
}

void imprime_PCs(PC *pc){

	if(!pc)
		return;

	printf("PC: %d\n",pc->id);
	printf("Paquetes %d\n", pc->paquetes);
	printf("Numero de Aristas: %d\n", pc->nAristas);
	imprime_Aristas(pc->arista);
	imprime_PCs(pc->sig);
}

void imprime_Routers(Router *router){

	if(!router)
		return;

	printf("Router: %d\n",router->id);
	printf("Numero de Aristas: %d\n", router->nAristas);
	imprime_Aristas(router->arista);
	imprime_Routers(router->sig);
}

Arista *busca_Arista(Arista *arista, int pc, int Orouter, int Drouter){

	if(!arista)
		return NULL;

	if(arista->pc->id == pc && arista->Drouter->id == Drouter)
		return arista;
	else{
		if(arista->Orouter->id == Orouter && arista->Drouter->id == Drouter)
			return arista;
		else{
			if(arista->Orouter->id == Orouter && arista->pc->id)
				return arista;
		}
	}
	return busca_Arista(arista->sig,pc,Orouter,Drouter);
}

PC *busca_PC(PC *pc, int id){

	if(!pc)
		return NULL;

	if(pc->id == id)
		return pc;
	return busca_PC(pc->sig,id);
}

Router *busca_Router(Router *router, int id){

	if(!router)
		return NULL;

	if(router->id == id)
		return router;
	return busca_Router(router->sig,id);
}