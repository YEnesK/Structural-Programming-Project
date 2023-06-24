#include <stdio.h>
#include <math.h>
#include <time.h>

#define MAX 100000

void IntroSort(int* data, int begin , int end );
void IntrosortUtil(int* data, int begin, int end, int depthLimit );
void InsertionSort(int* data, int begin , int end);
void MaxHeapify(int* data, int heapSize, int index , int begin);
void Heapify(int* data, int begin, int end, int heapSize );
void HeapSort(int* data, int begin, int end );
int Bolme(int* data, int left, int right );

int main(){
	
	int data[MAX];
	int i;
	
	srand(time(NULL));
	for(i=0 ; i<MAX ; i++){
		data[i] =1+rand()%100;
		printf("%d - " , data[i]);
	}
	printf("\n\n\n");
	
	
	IntroSort(data, 0, MAX-1);
	
	printf("\n\n\n");
	
	for(i=0 ; i<MAX ; i++){
		printf("%d\t" , data[i]);
	}
		
}
void swap(int* data, int i, int j){
	
  int temp = data[i];
  data[i] = data[j];
  data[j] = temp;
  
}

void InsertionSort(int* data, int begin , int end ) {                   //Kýsmen sýralanmýþ dizilerde oldukça verimlidir.
	int i , j , key , left , right;
	
	left = begin;
	right = end;
	
	for (i = left+1 ; i <= right ; i++)
	{
			
		key = data[i];
		j = i - 1;
	

		while ( (j >= left) && (data[j] > key) )
		{
			
			
			data[j + 1] = data[j];
			j--;	
		}
		data[j + 1] = key;
	}
}

void MaxHeapify(int* data, int heapSize, int index , int begin) {
	int left = (index + 1) * 2 - 1;                                   // Üçgen kurulur
	int right = (index + 1) * 2;
	int largest = 0;
	int temp;
	int i;
	

	if (left < heapSize && data[begin+left] > data[begin+index])
		largest = left;
	else
		largest = index;

	if (right < heapSize && data[begin+right] > data[begin+largest])
		largest = right;

	if (largest != index)                                                      //en büyük sayý üçgenin üstüne gelir
	{
		temp = data[begin+index];
		data[begin+index] = data[begin+largest];
		data[begin+largest] = temp;
		
	

		MaxHeapify(data, heapSize, largest , begin);
	}
}

void HeapSort(int* data, int begin , int end) {
	int heapSize = end-begin+1;
	int p , i , j , temp;

	for (p = (heapSize-1 ) / 2 ; p >= 0 ; p--)                             //Döngü tamamlandýðýnda herhangi bir sayý kendisinden büyük bir sayýnýn üstünde bulunmaz.
		MaxHeapify(data, heapSize, p , begin);                             //Yani en büyük sayý aðacýn en üstündedir.

	for (i = end-begin ; i > 0 ; i--)
	{
		
		temp = data[begin+i];
		data[begin+i] = data[begin];
		data[begin] = temp;
		
		heapSize--;
		MaxHeapify(data, heapSize, begin , begin);
	}
	
}

int Bolme(int* data, int left, int right ) {             // son elemaný bulunmasý gereken yere koyar ve kendisinden küçük elemanlarý soluna koyar 
	int pivot = data[right];
	int temp;
	int i = left;
	int j = left;

	for (j = left ; j < right ; j++)
	{
	
		
		if (data[j] <= pivot)
		{
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
			i++;
		}
	}

	data[right] = data[i];
	data[i] = pivot;

	return i;                                                     // son elemanýn en son konumunu döndürür
}


int findPivot(int* data, int a1, int b1, int c1)
{
	if(data[a1] < data[b1] && data[b1] < data[c1])
  		return b1;
  	
	if(data[a1] < data[c1] && data[c1] < data[b1])
  		return c1;
  
	if(data[b1] < data[a1] && data[a1] < data[c1])
  		return a1;
  
	if(data[b1] < data[c1] && data[c1] < data[a1])
		return c1;
  
	if(data[c1] < data[a1] && data[a1] < data[b1])
		return a1;
  
	if(data[c1] < data[b1] && data[b1] < data[a1])
		return b1;
}

void IntroSort(int* data, int begin , int end ) {
	int depthLimit;
	
	depthLimit = 2 * floor(log(end-begin)/log(2));
	
	
	
	IntrosortUtil(data, begin, end, depthLimit);
	
	}

	


void IntrosortUtil(int* data, int begin, int end, int depthLimit ){
	int size , temp,i;
	int p , pivot;
	size = end - begin;
	
	
	if (size < 16)
	{
	//	printf("Insertion Sort\t");
		InsertionSort(data, begin , end );
	}
	else if (depthLimit == 0)
	{
	//	printf("Heap Sort\t");
		HeapSort(data, begin, end );
	}
	else
	{
	//	printf("Quick Sort\t");
		depthLimit = depthLimit - 1;
		
		/*pivot = findPivot(data , begin , begin + (size / 2)+1  , end);
		
		swap(data , pivot , end);*/
		
		p = Bolme(data, begin, end );                                     //Kýsmi sýralama
		IntrosortUtil(data, begin, p-1, depthLimit);
		IntrosortUtil(data, p+1, end, depthLimit );
	}
	
	
}
