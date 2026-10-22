/*Realize un programa que permita realizar las siguientes operaciones con 2 valores:
sumas, restas, multiplicacion, divison, calculo de la raiz cuadrada, potencia al cuadrado y al cubo.
Su programa debe permitir al usuarioejecutar mas de una operacion si lo desea*/
#include <iostream>
#include <cmath>
using namespace std;

int main(){
    float val1=0;
    float val2=0;
    float resultado=0;
    char opcion;
    char controlBucle= 's';
    do{
    	cout<<"\nELIJA UNA OPCION \n1)SUMAR 2 VALORES \n2)RESTAR 2 VALORES \n3)MULTIPLICAR 2 VALORES \n4)DIVIDIR 2 VALORES";
    	cout<<"\n5)RAIZ CUADRADA A UN VALOR \n6)POTENCIA AL CUADRADO DE UN VALOR \n7)POTENCIA AL CUBO DE UN VALOR\n";
    	cin>>opcion;
    	switch (opcion){
		case '1':
			cout<<"\nINGRESE EL PRIMER VALOR: ";
			cin>>val1;
			cout<<"\nINGRESE EL SEGUNDO VALOR: ";
			cin>>val2;
    	    resultado=val1+val2;
    	    cout<<"\nEL RESULTADO ES: "<<resultado;
    	    break;
    	case '2':
    		cout<<"\nINGRESE EL PRIMER VALOR: ";
			cin>>val1;
			cout<<"\nINGRESE EL SEGUNDO VALOR: ";
			cin>>val2;
    	    resultado=val1-val2;
    	    cout<<"\nEL RESULTADO ES: "<<resultado;
    	    break;
    	case '3':
    		cout<<"\nINGRESE EL PRIMER VALOR: ";
			cin>>val1;
			cout<<"\nINGRESE EL SEGUNDO VALOR: ";
			cin>>val2;
		    resultado=val1*val2;
    	    cout<<"\nEL RESULTADO ES: "<<resultado;
    	    break;
    	case '4':
    		cout<<"\nINGRESE EL PRIMER VALOR: ";
			cin>>val1;
			cout<<"\nINGRESE EL SEGUNDO VALOR: ";
			cin>>val2;
			if(val2==0){
			    cout<<"\nNO SE PUEDE DIVIDIR POR 0";
			}else{
		        resultado=val1/val2;
    	        cout<<"\nEL RESULTADO ES: "<<resultado;
    	    }
    	    break;
    	case '5':
    		cout<<"\nINGRESE EL VALOR: ";
			cin>>val1;
			if(val1<0){
				cout<<"\nNO EXISTE RAIZ CUADRADA DE UN NUMERO NEGATIVO";
			}else{
	    	    resultado=sqrt(val1);
        	    cout<<"\nEL RESULTADO ES: "<<resultado;
        	}
    	    break;
    	case '6':
    		cout<<"\nINGRESE EL VALOR: ";
			cin>>val1;
		    resultado=val1*val1;
            cout<<"\nEL RESULTADO ES: "<<resultado;
        break;
    	case '7':
    		cout<<"\nINGRESE EL VALOR: ";
			cin>>val1;
		    resultado=val1*val1*val1;
    	    cout<<"\nEL RESULTADO ES: "<<resultado;
    	    break;
    	default:
    		cout<<"\nNO SE SELECCIONO NINGUNA OPCION\n";
    	    break;
	    }
     	cout<<"\nDESEA CONTINUAR (s/n)";
	    cin>>controlBucle;
	}while(controlBucle=='s' || controlBucle=='S' || controlBucle==!'n' || controlBucle==!'N');
    return 0;
}
