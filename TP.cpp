#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;

struct partidos {
	char siglas[5];
	float votos;
	int lista;
};

partidos aux;

struct nodo{
	partidos info;
	nodo* sgte;
};
nodo*ret;
void agregarPrincipio (nodo*&L, partidos aux);
nodo* buscar (nodo*&C, int d);
void bubbleSort(nodo*&Q);
int n=0;
FILE*PASO;

int main() {
	PASO=fopen("paso.dat","wb+");
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
	fread(&aux, sizeof (partidos), 1, PASO);
	nodo*L=NULL;
	while (!feof(PASO)) {
		if (aux.votos>=1.5) {
			agregarPrincipio(L,aux);
			n++;
			fread(&aux, sizeof(partidos), 1, PASO);
		}
	}
	bubbleSort(L);
	buscar(L,51);
	while(L!=NULL){
		cout <<L->info.lista << endl;
	}
	if(ret!=NULL){
		cout<<"¡La lista " << ret->info.lista << " alcanzó un porcentaje de votos mayor al 51%!" << endl;
	}
	return 0;
}

void agregarPrincipio (nodo*&L, partidos x) {
	nodo*Nuevo=new nodo();
		Nuevo->info=x;
		Nuevo->sgte=L;
		L=Nuevo;
};

void bubbleSort(nodo*&Q){
	nodo*P;
	int t;
	P=Q;
	while(P->sgte != NULL){
		P=Q->sgte;
		while(P!=NULL){
			if (Q->info.lista > P->info.lista){
				t=P->info.lista;
				P->info.lista=Q->info.lista;
				Q->info.lista=t;
			}
			P=P->sgte;
		}
		Q=Q->sgte;
		P=Q->sgte;
	}
}


nodo* buscar (nodo*&C, int d){
	nodo*ret=C;
	while (ret!=NULL || ret->info.votos>=d){
		ret=ret->sgte;
	}
	return ret;
}
