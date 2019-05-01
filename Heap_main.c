#include <stdio.h>
#include <stdlib.h>

// 0 tabanl� indexlemede array i�indeki i. d���m�n childlar�n�n ve parent�n�n hesaplanmas� i�in makrolar
#define leftChild(i) (2 * i + 1)
#define rightChild(i) (2 * i + 2)
#define parent(i) ((i - 1) / 2)


typedef struct HeapArray {
	int* array;
	int maxSize;
	int size;
} HeapArray;


// Parametre olarak verilen kapasitede bir HeapArray yap�s� olu�turur.
HeapArray* createHeapArray(int maxSize) {
	
	HeapArray* heap = malloc(sizeof(HeapArray));
	
	if (heap != NULL) {
		
		heap->size = 0;
		heap->maxSize = maxSize;
		heap->array = malloc(maxSize * sizeof(int));
		
		if (heap->array != NULL)
			return heap;
		
		else {
			free(heap);
			return NULL;
		}
		
	}
	
	return NULL;
		
}

// Parametre olarak verilen indexteki max-heap �zelli�ini bozan indexteki eleman� left ve right childlar�ndan b�y�k olan�yla de�i�tirir
// ve de�i�tirilen elemandan yine ayn� prosed�r� recursive olarak tekrarlar.
void maxHeapify(HeapArray* h, int index) {
	
	int largest_index;
	
	int left = leftChild(index);
	int right = rightChild(index);
	
	
	if ((left < h->size) && (h->array[left] > h->array[index]))
		largest_index = left;
	
	else
		largest_index = index;
		
	if ((right < h->size) && (h->array[right] > h->array[largest_index]))
		largest_index = right;
	
	if (largest_index != index) {
		
		int temp = h->array[index];
		h->array[index] = h->array[largest_index];
		h->array[largest_index] = temp;
		
		maxHeapify(h, largest_index);
		
	}
}


// Heapdeki en b�y�k de�eri (root) silmeden d�nd�r�r.
int getMax(HeapArray* heap) {
	
	return heap->array[0];
	
}

// Heapdeki eleman say�s�n� d�nd�r�r.
int getSize(HeapArray* heap) {
	
	return heap->size;
	
}

// Heap dolu mu bo� mu kontrol eder.
int isEmpty(HeapArray* heap) {
	
	if (heap->size == 0)
		return 1;
	else
		return 0;
}

// Heapdeki en b�y�k de�eri (root) d�nd�r�r
// ve root yerine sondaki eleman� yazarak silip max-heap �zelli�ini sa�lamak root i�in maxHeapify fonksiyonunu �a��r�r.
int extractMax(HeapArray* heap) {
	
	int max = heap->array[0];
	
	heap->array[0] = heap->array[heap->size - 1];
	heap->size = heap->size - 1;
	
	maxHeapify(heap, 0);
	
	return max;
	
}

// Parametre olarak verilen de�eri heapin en sonuna ekler
// Sondaki eleman parent� ile max-heap �zelli�i sa�lam�yorsa swap edip parenttan recursive olarak kontrole devam eder.
// Ekleme ba�ar�l� ise 1 de�il ise 0 d�nd�r�r.
int insert(HeapArray* heap, int value) {
	
	if (heap->size < heap->maxSize) {
		
		heap->array[heap->size] = value;
		heap->size = heap->size + 1;
		
		int index = heap->size - 1;
		int parent_index = parent(index);
		
		while ((parent_index >= 0) && (heap->array[parent_index] < heap->array[index])) {
			
			int temp = heap->array[parent_index];
			heap->array[parent_index] = heap->array[index];
			heap->array[index] = temp;
			
			index = parent_index;
			parent_index = parent(index);
		}
		
		return 1; // Ekleme ba�ar�l�.
	}
	
	return 0; // Ekleme ba�ar�s�z.
}



int main() {
	
	HeapArray* heap = createHeapArray(20);
	
	insert(heap, 5);
	insert(heap, 10);
	insert(heap, 1);
	insert(heap, 4);
	
	printf("En buyuk deger: %d\n", getMax(heap));
	
	printf("Heapteki elemanlar: ");
	
	int size = heap->size;
	int i;
	
	for (i = 0; i < size; i++)
		printf("%d ", extractMax(heap));
	
	if (isEmpty(heap))
		printf("\nHeap bos !\n");
		
	insert(heap, 48);
	
	if (!isEmpty(heap))
		printf("Heap bos degil !\n");
		
	return 0;
}
