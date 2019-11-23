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
	struct Router *router;
	struct PC *pc;
}Arista;

int agregar_PC(PC **pc);
int agregar_Router(Router **router);
int crear_arista(Router *router,PC *pc, int origen, int destino);
void imprime_Routers(Router *router);
void imprime_PCs(PC *pc);
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
				agregar_Router(&router);
				break;
			}
			case 2:{
				agregar_PC(&pc);
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
					printf("id: %d \n",router->id);
					printf("Numero de Aristas: %d\n",router->nAristas);
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
					printf("id: %d \n",pc->id);
					printf("Numero de Aristas: %d\n",pc->nAristas);
					printf("Paquetes: %d\n",pc->paquetes);
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

int agregar_PC(PC **pc){

	PC *nuevo = (PC*)malloc(sizeof(PC));

	if(!nuevo)
		return 0;

	nuevo->id = rand() % 101;
	nuevo->paquetes = rand() % 101;
	nuevo->nAristas = 0;
	nuevo->arista = NULL;
	nuevo->sig = *pc;
	*pc = nuevo;
	nPCs++;
	return 1;
}

int agregar_Router(Router **router){

	Router *nuevo = (Router*)malloc(sizeof(Router));

	if(!nuevo)
		return 0;

	nuevo->id = rand() % 101;
	nuevo->arista = NULL;
	nuevo->sig = *router;
	*router = nuevo;
	nRouters++;
	return 1;
}

// int crear_arista(Router *router, Pc *pc, int origen, int destino){

// 	Pc *ori = busca_PC(router->pc,origen);
	
// 	if(!ori)
// 		return 0;

// 	Router *des = busca_Router(router,destino);

// 	if(!des)
// 		return 0;

// 	Arista *aux = busca_Arista(router->arista,origen,destino);

// 	if(!aux){
// 		Arista *arista = (Arista*)malloc(sizeof(Arista));
// 		arista->peso = rand() % 1 + 100;
// 		arista->router = des;
// 		arista->pc = 
// 	}

// }

void imprime_PCs(PC *pc){

	if(!pc)
		return;

	printf("%d\n",pc->id);
	imprime_PCs(pc->sig);
}

void imprime_Routers(Router *router){

	if(!router)
		return;

	printf("%d\n",router->id);
	imprime_Routers(router->sig);
}

Arista *busca_Arista(Arista *arista, int pc, int router){

	if(!arista)
		return NULL;

	if(arista->pc->id == pc && arista->router->id == router)
		return arista;
	return busca_Arista(arista->sig,pc,router);
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

	printf("%d\n",id);

	if(router->id == id)
		return router;
	return busca_Router(router->sig,id);
}