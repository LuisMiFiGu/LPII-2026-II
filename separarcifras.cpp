/*Realize un programa que permita separar en cifras numeros en un rango entre 10 y 99999, ademas de separarlas y mostrarlas en pantalla su programa debe ser capaz de identificar
si el numero ingresado es par, impar, primo o perfecto*/

#include <iostream>
using namespace std;
int main(){
	int val=0;
	int uni=0;
	int dec=0;
	int cen=0;
	int Muni=0;
	int Mdec=0;
	int cont=0;
	int perf=0;
	int i=1;
	cout<<"INGRESE UN VALOR DE 10 A 99999: ";
	cin>>val;
	if(val>=10 && val<=99999){
		uni= val % 10;
		dec= (val/10) % 10;
		cen= (val/100) % 10;
		Muni= (val/1000) % 10;
		Mdec= (val/10000) % 10;
		
		if(val%2==0){
			cout<<"\nSU VALOR ES PAR";
		}else{
		    cout<<"\nSU VALOR ES IMPAR";
	    }
	    
	    for(i=1; i<=val; i++){
	    	if(val%i==0){
	    		cont++;
			}
			if(!val==i && val%i==0){
				perf+=i;
			}
		}
	    
	    if(!cont>2){
	    	cout<<"\nSU VALOR ES PRIMO";
		}else{
			cout<<"\nSU VALOR NO ES PRIMO";
		}
		
		if(perf==val){
			cout<<"\nSU VALOR ES PERFECTO";
		}else{
		    cout<<"\nSU VALOR NO ES PERFECTO";	
		}
		
		cout<<"\nSU VALOR SEPARADO ("<<val<<") ES:\nUnidad: "<<uni<<"\nDecena: "<<dec<<"\nCentena: "<<cen<<"\nUnidad de Mil: "<<Muni<<"\nDecena de Mil: "<<Mdec;
	}else{
		cout<<"\nEL VALOR ELEGIDO NO CUMPLE CON LOS REQUISITOS";
	}

	return 0;
}