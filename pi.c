#include <stdio.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include "/usr/lib/x86_64-linux-gnu/openmpi/include/mpi.h"

int main(int argc, char **argv)
{
    int n, myid, numprocs, i; 
    double PI25DT = 3.141592653589793238462643; 
    double mypi, pi, sum; 

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&myid); 
    n=atoi(argv[1])*numprocs;
    sum = 0.0; 
    for (i = myid ; i < n; i += numprocs) { 
        sum += pow((-1),i)*(4.0 / (2*i+1)); 
        } 
    mypi = sum; 
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, 
    MPI_COMM_WORLD); 
    if (myid == 0)  
        printf("pi is approximately %.16f, Error is %.16f\n",pi, fabs(pi - PI25DT));
    
    MPI_Finalize(); 
    return 0;
    }
