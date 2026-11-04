/*Realize un programa que permita el calculo de la serie fibonacci hasta una interaccion que el usuario quiera*/
#include <iostream>
using namespace std;
int main(){
	int n1=0;
	int n2=1;
	int resultado=0;
	int opcion=0;
	char controlBucle= 's';
	do{
    	cout<<"SELECCIONE CUANTAS INTERACCIONES QUIERA QUE SE REALIZE LA SERIE FIBONACCI: ";
    	cin>>opcion;
        while(opcion>0){
	    	resultado=n1+n2;
    		cout<<"\n"<<n1<< "+" <<n2<< "=" << resultado;
            n1=n2;
    	    n2=resultado;
	    	opcion--;
    	}
    	cout<<"\n\nEL FINAL DE LA SERIE FIBONACCI SELECCIONADA ES DE: "<<resultado;
    	n1=0;
    	n2=1;
	    cout<<"\nDESEA CONTINUAR (s/n): ";
	    cin>>controlBucle;
	}while(controlBucle=='s' || controlBucle=='S' || controlBucle==!'n' || controlBucle==!'N');
	return 0;
}
