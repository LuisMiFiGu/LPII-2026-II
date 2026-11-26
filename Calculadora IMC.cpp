/*Realize un programa que permita registrar los pesos de los estudiantes de una seccion de 23.
Calcule el promedio general de pesos y usando de referencia su programa IMC calcule en que rango esta cada estudiante*/
#include <iostream>
using namespace std;
int main(){
float peso[23];
float altura[23];
float IMC=0;
int i=0;
for(i=0; i<23; i++){
	cout<<"\nINGRESE SU PESO ESTUDIANTE "<< i+1 <<":";
    cin>>peso[i];
    cout<<"\nINGRESE SU ALTURA ESTUDIANTE "<< i+1 <<":";
    cin>>altura[i];
    while(peso[i]==0){
	    cout<<"\nINGRESE OTRA VEZ SU PESO: ";
        cin>>peso[i];
    }
    while(altura[i]==0){
	    cout<<"\nINGRESE OTRA VEZ SU ALTURA: ";
        cin>>altura[i];
    }
altura[i]= altura[i]*0.01;
IMC= peso[i]/(altura[i]*altura[i]);
if(IMC<16.00){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE INFRAPESO: DELGADEZ SEVERA";
}else if(IMC>=16 && IMC<=16.99){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE INFRAPESO: DELGADEZ MODERADA";
}else if(IMC>=17.00 && IMC<=18.49){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE INFRAPESO: DELGADEZ ACEPTABLE";
}else if(IMC>=18.50 && IMC<=24.99){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE PESO NORMAL";
}else if(IMC>=25.00 && IMC<=29.99){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE SOBREPESO";
}else if(IMC>=30.00 && IMC<=34.99){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE OBESO: TIPO 1";
}else if(IMC>=35.00 && IMC<=40.0){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE OBESO: TIPO 2";
}else if(IMC>40.00){
	cout<<"ESTUDIANTE "<<i+1;
	cout<<" SU IMC (INDICE DE MASA CORPORAL) ES DE: "<<IMC;
	cout<<" SU CLASIFICACION ES DE OBESO: TIPO 3\n";
}
}
return 0;
}