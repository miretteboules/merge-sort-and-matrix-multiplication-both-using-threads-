// CPP Program to implement merge sort using
// multi-threading
#include <iostream>
#include <pthread.h>
#include <fstream>

// number of elements in array
#define MAX 10

// number of threads
#define THREAD_MAX 2

using namespace std;

int * arr;
struct node {
  int left;
  int right;
} ;


//Function to merge back array in a sorted way
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r]
 
    // Initial index of first subarray
    int i = 0;
 
    // Initial index of second subarray
    int j = 0;
 
    // Initial index of merged subarray
    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of
    // L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of
    // R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
//function that handle multithreaded mergesort
void * mergeSort(void *a){
pthread_t threadleft;
pthread_t threadright;
node *p = (node *)a;
        node n1, n2;
        int m = (p->left+p->right)/2;
    

    if(p->left>= p->right){
        return NULL;//returns recursively
    }
   
     n1.left = p->left;
        n1.right =m;

        n2.left= m+1;
        n2.right =p->right;
    //hena anadiha b thread 1st half w a join
    pthread_create(&threadleft, NULL, mergeSort,&n1);
     pthread_join(threadleft, NULL);

    //anadiha b thread tani half w a join
    pthread_create(&threadright, NULL, mergeSort,&n2);
    pthread_join(threadright, NULL);

    //merging the 2 threads
    merge(arr,p->left,m,p->right);
}
 


// Driver Code
int main()
{ int i =0;
int x;

 ifstream is("input.txt");
 int size;
 is >> x;
 size=x;
  arr=(int*)malloc(sizeof(int)*size);
  while (is >> x)
   // and read integer from file
   arr[i++] = x;
 is.close();
node m;
m.left=0;
m.right=size-1;
pthread_t thread;
pthread_create(&thread, NULL, mergeSort,&m);
pthread_join(thread, NULL);

	// displaying sorted array
	cout << "Sorted array: ";
	for (int i = 0; i < size ; i++)
		cout << arr[i] << " ";

	

	return 0;
}
