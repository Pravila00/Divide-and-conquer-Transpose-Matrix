//g++ -O2 -o mDYV MatrizTraspuestaDyV.cpp
#include <iostream>
#include <ctime>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void DyV(int *matriz[],int tam){
    //El problema lo vamos a resolver con recursividad
    //Dividiremos en 4 submatrices hasta que el tam de una submatriz sea 1
    
    //Caso base 
    if(tam==2){
        int aux=matriz[0][1];
        matriz[0][1]=matriz[1][0];
        matriz[1][0]=aux;
    }

    else if(tam==1){
        //NO HACEMOS NADA LA TRANSPUESTA ES EL PROPIO ELEMENTO DE LA MATRIZ
    }

    else{
    //Definimos 4 matrices cuadradas con tamanio tam/2
        int n=tam/2;
        int **m11=new int*[n];
        int **m12=new int*[n];
        int **m21=new int*[n];
        int **m22=new int*[n];

        cout <<"GENERAMOS LAS MATRICES EN MEMORIA DINAMICA" <<endl;
        //Generamos las matrices en memoria dinamica
        for(int i=0;i<n;i++){
            m11[i]=new int [n];
            m12[i]=new int [n];
            m21[i]=new int [n];
            m22[i]=new int [n];
        }

        cout << "ASIGNAMOS LOS VALORES DE LA MATRIZ" <<endl;
        //Asignamos los valores de la matriz
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                m11[i][j]=matriz[i][j];
            }
        }

        for(int i=0;i<n;i++){
            for(int j=n;j<tam;j++){
                m12[i][j-n]=matriz[i][j];
            }
        }

        for(int i=n;i<tam;i++){
            for(int j=0;j<n;j++){
                m21[i-n][j]=matriz[i][j];
            }
        }

        for(int i=n;i<tam;i++){
            for(int j=n;j<tam;j++){
                m22[i-n][j-n]=matriz[i][j];
            }
        }

        cout << "LLAMAMAOS A LA FUNCION DE MANERA RECURSIVA";
        DyV(m11,n);
        DyV(m12,n);
        DyV(m21,n);
        DyV(m22,n);

        cout <<"REALIZAMOS LOS CAMBIOS NECESARIOS" <<endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                matriz[i][j]=m11[i][j];
            }
        }

        for(int i=0;i<n;i++){
            for(int j=n;j<tam;j++){
                matriz[i][j]=m21[i][j-n];
            }
        }

        for(int i=n;i<tam;i++){
            for(int j=0;j<n;j++){
                matriz[i][j]=m12[i-n][j];
            }
        }

        for(int i=n;i<tam;i++){
            for(int j=n;j<tam;j++){
                matriz[i][j]=m22[i-n][j-n];
            }
        }


        for(int i=0;i<n;i++){
            delete [] m11[i];
            delete [] m12[i];
            delete [] m21[i];
            delete [] m22[i];
        }

        cout <<"ELIMINAMOS LAS MATRICES DE MEMORIA DINAMICA" <<endl;
        delete [] m11;
        delete [] m12;
        delete [] m21;
        delete [] m22;
    }

}


template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

void inicializarMatriz(int *matriz[],int tam){
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            matriz[i][j]=aleatorio<0,9>();
        }
    }
}

int main(int argc, char**argv){
    int tam=atoi(argv[1]);
    int **matriz= new int *[tam];
    int aux;

    //Generamos la matriz en memoria dinamica
    for(int i=0;i<tam;i++){
        matriz[i]=new int [tam];
    }

    //Inicializacion matriz
    inicializarMatriz(matriz,tam);

     for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            cout << matriz[i][j] <<" ";
        }
        cout <<endl;
    }
    cout << "**************************"<<endl;

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;

    tantes=high_resolution_clock::now();
    //Algoritmo de fuerza
    DyV(matriz,tam);

    tdespues=high_resolution_clock::now();
    transcurrido = duration_cast<duration<double>>(tdespues - tantes);

    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            cout << matriz[i][j] <<" ";
        }
        cout <<endl;
    }

    for(int i=0;i<tam;i++){
        delete [] matriz[i];
    }

    delete [] matriz;

    

    //Salida de datos
    cout << tam << "\t" << transcurrido.count(); 


    return 0;

}