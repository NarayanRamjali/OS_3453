#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int rows; // Number of rows in output matrix
int cols; // Number of columns in output matrix
int rc; // Number of columns in matrixA/rows in matrixB

double** mat1; // First Input Matrix
double** mat2; // Second Input Matrix
double** matOut; // Output Matrix

void* matrixMultiplyR(void* id);
void* matrixMultiplyE(void* data);
void allocateMatrix(double ***matPtr, int n, int m);
void displayOutput(char *fileName,char *methodId);
int getMatrix(char *filename, int matrixId);
void removeExtension(char *filename);
int rowsMethod();
int elementsMethod();



#define M 3
#define K 2
#define N 3
#define NUM_THREADS 10

int A [M][K] = { {1,4}, {2,5}, {3,6} };          
int B [K][N] = { {8,7,6}, {5,4,3} };
int C [M][N];

struct v {
   int i; /* row */
   int j; /* column */
};
void *runner(void *param); /* the thread */

int main(int argc, char *argv[]) {

         
	printf("\nInput matrix a:\n");
  
          FILE *pToFile;
          pToFile  = fopen("a.txt","r");
          char input[1000];
          while( fgets( input, 1000, pToFile)){
 
                 printf(input);
         }

          printf("\nInput matrix b:\n");
 
           pToFile = fopen("b.txt","r");
                    while( fgets( input, 1000, pToFile)){
                   printf(input);
           }
	           fclose(pToFile);
	
	printf("\nCreated worker thread           for row    \n");
	

	printf("\nMatrix C = A * B:\n");

   int i,j, count = 0;
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         //Assign a row and column for each thread
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /* Now create the thread passing it data as a parameter */
         pthread_t tid;       //Thread ID
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
       	 pthread_create(&tid,&attr,runner,data);
         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);
         count++;
	}
   }
   //Print out the resulting matrix
      for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
	 printf("\nTotal execution time using   threads is    ms\n\n");
}
	
	
//The thread will begin control in this function
	
void *runner(void *param) {
   struct v *data = param; // the structure that holds our data
   int n, sum = 0; //the counter and sum
   //Row multiplied by column
      for(n = 0; n< K; n++){
            sum += A[data->i][n] * B[n][data->j];
  }
   //assign the sum to its coordinate
   C[data->i][data->j] = sum;
   //Exit the thread
   pthread_exit(0);
}                                                                                     
