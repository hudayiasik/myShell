#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int i,j;
float* cerateArr(int size){
     float* arr =(float*) malloc(size*sizeof(float));
     return arr;
}
void randomArr(float* arr){
    srand(time(NULL));   // Initialization, should only be called once.
    int r; 
    for (i = 0; i < sizeof(arr); i++){
        r = rand()%10;
        *(arr+i) =r;
    }

}
printArr(float* arr){
    for (i = 0; i < sizeof(arr); i++){
        printf("%f",*(arr+i));
    }
}
void swap(int a,int b;){

}
sortArr(int* arr){
    for (i = 0; i < sizeof(arr); i++){
         for (j = 1; j < sizeof(arr); j++){
            if(*(arr+i)<*(arr+j))
            printf("%f",*(arr+i));
    }
    }
}

int main(){

    return 0;
}