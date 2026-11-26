/*Realize un programa que permita alusuario registrar 10 numeros y muestre repite cuanto se repite el numero 5, cual es el mayor y cual es el menor*/
#include <iostream>
using namespace std;
int main(){
	int i= 0;
	int numeros[10];
	int cont= 0;
	int mayor=0, menor=99999999;
	for(i=0; i<10; i++){
		cout<<"\nIngrese el "<< i+1 <<" numero: ";
    	cin>>numeros[i];
    	if(numeros[i] > mayor){
    		mayor= numeros[i];
		}
		if(numeros[i] < menor){
    		menor= numeros[i];
		}
    	if(numeros[i]==5){
		    cont++;
		}
	}
	cout<<"\nEl numero Mayor es el: "<< mayor;
	cout<<"\nEl numero Menor es el: "<< menor;
	if (cont>0){
	    cout<<"\nEl numero 5 se repitio "<< cont <<" veces";
    }else{
    	cout<<"\nEl numero 5 no se repitio";
	}
} 



