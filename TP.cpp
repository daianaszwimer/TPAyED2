#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

struct partidos{
	char siglas[5];
	float votos;
	int lista;
};

struct nodo{
	partidos info;
	nodo*sgte;
};
nodo*K;
partidos aux;
FILE*PASO;

void insertarOrdenado(nodo*&L, partidos x);
void agregarPrincipio(nodo*&L, partidos v);
int buscar(nodo*&L, float y);

int main(){
	PASO=fopen("paso.dat","wb+");
	cout << "Ingrese la primer lista, para terminar el ingreso de partidos al archivo, ingrese \"-1\" cuando el programa vuelva a pedirle una lista." << endl;
		cin >> aux.lista;
		while (aux.lista!=-1) {
			cout << "Ingrese las siglas del partido (hasta 5)" << endl;
			cin >> aux.siglas;
			cout << "Ingrese la cantidad porcentual de votos. Asegúrese de que entre todos los partidos no superen el 100% (ingrese resultados realistas)." << endl;
			cin >> aux.votos;
			fwrite(&aux, sizeof(partidos), 1, PASO);
			cout << "Ingrese la primer lista, para terminar el ingreso de partidos al archivo, ingrese \"-1\"." << endl;
			cin >> aux.lista;
		}
		rewind(PASO);
		fread(&aux, sizeof(partidos), 1, PASO);
		while (!feof(PASO)){
			if (aux.votos>=1.5){
				insertarOrdenado(K, aux);
			}
			fread(&aux, sizeof(partidos), 1, PASO);
		}
		int aux3;
		aux3=buscar(K, 51);
		cout << "¡La lista " << aux3 << " llegó al 51% de votos!" << endl;
		while (K!=NULL){
			cout << "La lista " << K->info.lista << " llegó al menos al 1.5% de votos." << endl;
			K=K->sgte;
		}
}

void insertarOrdenado (nodo*&L, partidos x){
	if (L==NULL || x.lista<L->info.lista){
		agregarPrincipio(L, x);
	}
	else{
		nodo*NUEVO=new nodo();
		NUEVO->info=x;
		NUEVO->sgte=NULL;
		nodo*aux2=L;
		nodo*ant=L;
		while(aux2!=NULL && aux2->info.lista<x.lista){
			ant=aux2;
			aux2=aux2->sgte;
		}
		ant->sgte=NUEVO;
		NUEVO->sgte=aux2;
	}
}
void agregarPrincipio (nodo*&L, partidos v){
	nodo*NUEVO=new nodo();
	NUEVO->info=v;
	NUEVO->sgte=L;
	L=NUEVO;
}

int buscar(nodo*&L, float y){
	nodo*aux4=L;
	while (aux4!=NULL && aux4->info.votos<y){
		aux4=aux4->sgte;
	}
	return aux4->info.lista;
}
