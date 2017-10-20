#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

struct partidos {
	char siglas[5];
	float votos;
	int lista;
};
struct nodo{
	partidos info;
	nodo* sgte;
};
partidos aux;
void agregarPrincipio (nodo*&L, partidos x);
void insertarOrdenado (nodo*&L, partidos x);
nodo* buscar (nodo*&C, int d);
nodo*C;
nodo*ret=C;

int main(){
	FILE*PASO;
	nodo*L=NULL;
	PASO=fopen("PASO.dat","wb+");
	cout << "Ingrese la primer lista, para terminar el ingreso de partidos al archivo, ingrese \"-1\"." << endl;
	cin >> aux.lista;
	while (aux.lista!=-1) {
		cout << "Ingrese las siglas del partido (hasta 5)" << endl;
		cin >> aux.siglas;
		cout << "Ingrese la cantidad porcentual de votos." << endl;
		cin >> aux.votos;
		fwrite(&aux, sizeof(partidos), 1, PASO);
		cout << "Ingrese la primer lista, para terminar el ingreso de partidos al archivo, ingrese \"-1\"." << endl;
		cin >> aux.lista;
	}
	rewind(PASO);
	fread(&aux, sizeof(partidos), 1, PASO);
	while (!feof(PASO)){
		if (aux.votos>=1.5) {
			insertarOrdenado(L, aux);
		}
		fread(&aux, sizeof(partidos), 1, PASO);
	}
	fclose(PASO);
	ret=buscar(L,51);
	while (L!=NULL){
		cout << L->info.lista << endl;
		L=L->sgte;
	}
	cout << ret << endl;
}

void insertarOrdenado (nodo*&L, partidos x) {
	if (L==NULL || x.votos<L->info.votos) {
		agregarPrincipio (L, x);
	}
	else {
		nodo*Nuevo= new nodo();
		Nuevo->info=x;
		Nuevo->sgte= NULL;
		nodo*aux2=L;
		nodo*ant=L;
		while (aux2!=NULL && aux2->info.votos<x.votos) {
			ant=aux2;
			aux2=aux2->sgte;
		}
		ant->sgte=Nuevo;
		Nuevo->sgte=aux2;
	}
};

void agregarPrincipio (nodo*&L, partidos x) {
	nodo*Nuevo=new nodo();
		Nuevo->info=x;
		Nuevo->sgte=L;
		L=Nuevo;
};

nodo* buscar (nodo*&C, int d){
	while (ret!=NULL && ret->info.votos<d){
		ret=ret->sgte;
	}
	return ret;
}
