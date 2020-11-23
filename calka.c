#include <stdio.h>
#include <string.h>
#include <math.h>
#include "/usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h"

int a = 1;
int b = 4;

float y(float x) 
{ 

    return x*x; 
} 

float calka(int nr, int max) 
{ 
    float aa, bb;

    float dist;

    dist = (b - a) / max;

    bb = max - nr - dist;

    aa = bb - dist;

    float h = (bb-aa); 
  
    float s = y(aa)+y(bb); 
    
    s += 2*y(aa+h); 
  
    return((0.5)*s); 
    //return 2;
} 



main(int argc, char **argv)
{

    

    int liczba_procesu,numer_procesu;
    int tag=20;double suma;

    suma=0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &numer_procesu);
    MPI_Comm_size(MPI_COMM_WORLD, &liczba_procesu);
    if (numer_procesu == liczba_procesu-1)
    {
        suma = calka(numer_procesu, liczba_procesu);
        printf("\nNumer procesu = %d\n",numer_procesu); 
        printf("suma = %lf\n",suma);
        //wysylamy zmiennych do procesu ostatniego         
        MPI_Send(&suma, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
        }
//gdy proces ma numer wiekszy niz 0 i mniejszy niz proces ostatni
if (numer_procesu>0 && numer_procesu<liczba_procesu-1){ 
    //odbieramy zmienne a i suma od kolejnego

    MPI_Recv(&suma, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);

    suma += calka(numer_procesu, liczba_procesu);

    printf("\n proces = %d\n",numer_procesu);
    printf("suma = %lf\n",suma);
    //przeslanie zmiennych do poprzedniego procesu

    MPI_Send(&suma, 1, MPI_DOUBLE, numer_procesu-1,tag, MPI_COMM_WORLD);
    }
    if(numer_procesu == 0)
    {
        //pobieramy a i suma od kolejnego procesu

        MPI_Recv(&suma, 1, MPI_DOUBLE, numer_procesu+1, tag,MPI_COMM_WORLD, &status);
        suma = calka(numer_procesu, liczba_procesu);
        printf("\n proces = %d\n",numer_procesu); 
        printf("SUMA = %lf\n",suma);
    }
        MPI_Finalize();
}
