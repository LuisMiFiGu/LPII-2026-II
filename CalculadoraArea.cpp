/*Realice un programa que permitacalcular el area de un circulo, un cuadrado, un rectangulo y un triangulo equilatero, procure usar almenos 3 secuencias de escape para dar
formato a sus mensajes, considere que su menu de opciones sea facil de entendery agradable a la vista*/
#include <iostream>
using namespace std;
int main(){
	float val1=0;
	float val2=0;
	int opcion=0;
	float area=0;
	float pi=3.14;
	char controlBucle= 's';
	do{
	cout<<"\n\t\033[35mSELECCIONE CUAL FORMA QUIERE CALCULAR LA FORMA\033[0m\n";
	cout<<"\t\t\033[32m1) TRIANGULO EQUILATERO\033[0m\n\t\t\033[36m2) CUADRADO\033[0m\n\t\t\033[34m3) RECTANGULO\033[0m\n\t\t\033[33m4) CIRCULO\033[0m\n\tOPCION: ";
	cin>>opcion;
	switch(opcion){
		case 1:
			cout<<"\n\t\033[32mSELECCIONE LA BASE DEL TRIANGULO: \033[0m";
			cin>>val1;
			cout<<"\n\t\033[32mSELECCIONE LA ALTURA DEL TRIANGULO: \033[0m";
			cin>>val2;
			area=(val1 * val2)/2;
			cout<<"\n\t\033[32mEL AREA DEL TRIANGULO EQUILATERO ES DE: \033[0m"<<area;
		break;
		case 2:
			cout<<"\n\t\033[36mSELECCIONE LA LONGITUD DEL CUADRADO: \033[0m";
	    	cin>>val1;
	    	area=val1*val1;
	    	cout<<"\n\t\033[36mEL AREA DEL TRIANGULO EQUILATERO ES DE: \033[0m"<<area;
		break;	
		case 3:
			cout<<"\n\t\033[34mSELECCIONE LA BASE DEL RECTANGULO: \033[0m";
			cin>>val1;
			cout<<"\n\t\033[34mSELECCIONE LA ALTURA DEL RECTANGULO: \033[0m";
			cin>>val2;
			area=val1 * val2;
			cout<<"\n\t\033[34mEL AREA DEL RECTANGULO ES DE: \033[0m"<<area;
		break;	
		case 4:
			cout<<"\n\t\033[33mSELECCIONE EL RADIO DEL CIRCULO: \033[0m";
	    	cin>>val1;
	    	area=(val1*val1) * pi;
	    	cout<<"\n\t\033[33mEL AREA DEL CIRCULO ES DE: \033[0m"<<area;
		break;		
		default:
			cout<<"\n\t\033[31mNINGUNA FORMA FUE SELECCIONADA\033[0m\n";
		break;
	}
    cout<<"\n\t\033[35mDESEA CONTINUAR? (s/n) \033[0m";
	cin>>controlBucle;
	}while(controlBucle=='s' || controlBucle=='S' || controlBucle==!'n' || controlBucle==!'N');
	return 0;
}