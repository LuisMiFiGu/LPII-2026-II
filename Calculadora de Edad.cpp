/*Realize un programa que a partir de una fecha ingresada calcule una edad, valide la fecha ingresada*/

#include <iostream>
using namespace std;
int main(){
	int year=0;
	int mes=0;
	int dia=0;
	int i=0;
    cout<<"INGRESE SU DIA DE NACIMIENTO: ";
    cin>>dia;
    cout<<"\nINGRESE SU MES DE NACIMIENTO: ";
    cin>>mes;
    cout<<"\nINGRESE SU YEAR DE NACIMIENTO: ";
    cin>>year;
    
    while (dia<1 || dia>31){
	cout<<"\nVALOR INCORRECTO, INGRESE SU DIA DE NACIMIENTO: ";
    cin>>dia;
    }
        
    while (mes<1 || mes>12){
	cout<<"\nVALOR INCORRECTO, INGRESE SU MES DE NACIMIENTO: ";
    cin>>mes;
    }
        
    while (year<1900 || year>2026){
	cout<<"\nVALOR INCORRECTO, INGRESE SU YEAR DE NACIMIENTO: ";
    cin>>year;
    }
	return 0;
}