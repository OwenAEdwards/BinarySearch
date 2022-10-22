#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct output {
   int keyFromSearch;
   int numOfElementsSearched;
} output;

void sortDataStructAscendOrder(int *dataStruct, int numOfElements) {
   int temp, i, j, k;
   for (j = 0; j < numOfElements; ++j) {
      for (k = j + 1; k < numOfElements; ++k) {
         if (dataStruct[j] > dataStruct[k]) {
            temp = dataStruct[j];
            dataStruct[j] = dataStruct[k];
            dataStruct[k] = temp;
         }
      }
   }
}

int *randDataStructPopulator(int numOfElements,int *dataStruct) {
   srand(time(NULL));
   for (int i=0;i<=numOfElements;i++) {
      dataStruct[i]=rand()%100; // only numbers from 0 to 99
   }
   sortDataStructAscendOrder(dataStruct,numOfElements);
   return dataStruct;
}

output binarySearch(int numOfElements, int *dataStruct, int key) {
   int start=0,end=numOfElements-1; // we're starting at index 0 and ending at the last index
   int midpoint;
   int numOfElementsSearched;
   output o1;
   while (start<end) {
      midpoint=(start+end)/2; // the new midpoint is halfway between the start and the end
      // 3 cases below:
      // case 1: if the midpoint of the dataStruct is equal to the key, then return the key
      if (key==dataStruct[midpoint]) {
         o1.keyFromSearch=key;
         o1.numOfElementsSearched=numOfElementsSearched;
         return o1;
      }
      // case 2: if the midpoint of the dataStruct is less than the key, then let the new end searched be the midpoint (excluding
      // itself), essentially excluding the "right" side of the dataStruct and only considering the "left" side of the dataStruct
      if (key<dataStruct[midpoint]) {
         end=midpoint-1;
         numOfElementsSearched++;
      }
      // case 3: if the midpoint of the dataStruct is greater than the key, then let the new start searched be the midpoint 
      // (excluding itself), essentially excluding the "left" side of the dataStruct and only consider the "right" side of the
      // dataStruct
      if (key>dataStruct[midpoint]) {
         start=midpoint+1;
         numOfElementsSearched++;
      }
      // case 4: we never found the key we were looking for
      if (start==end) {
         o1.keyFromSearch=-1;
         return o1;
      }
   }
}

output linearSearch(int numOfElements, int *dataStruct, int key) {
   output o2;
   for (int i=0;i<numOfElements;i++) {
      if (dataStruct[i]==key) {
         o2.keyFromSearch=key;
         o2.numOfElementsSearched=i;
         return o2;
      }
   }
   o2.keyFromSearch=-1;
   return o2;
}

int main() {

   int numOfElements;
   int *dataStruct;
   int key=-2;

   printf("Number of elements in data structure (N): ");
   scanf("%d",&numOfElements);

   dataStruct=(int*)malloc(numOfElements*sizeof(int)); // allocating space in the data structure

   dataStruct=randDataStructPopulator(numOfElements,dataStruct);

   // error checking the key input
   while ( !( (key<100) && (key>=0) ) ) {
      printf("The key we're looking for (between 0 and 99): ");
      scanf("%d",&key);
   }
   
   output o1=binarySearch(numOfElements,dataStruct,key);
   if (o1.keyFromSearch!=-1) {
      printf("In the binary search, the key %d was found after %d elements were searched\n",
      o1.keyFromSearch,o1.numOfElementsSearched);
      output o2=linearSearch(numOfElements,dataStruct,key);
      printf("In the linear search, the key %d was found after %d elements were searched\n",
      o2.keyFromSearch,o2.numOfElementsSearched);
      printf("For reference, the worst-case for the binary search is log_2(%d) or %.2f",numOfElements,log2(numOfElements));
   }
   else {
      printf("The key was not found\n");
   }

   return 0;
}