#include <stdio.h>
#include <stdlib.h>

// 0 tabanli indexlemede array içindeki i. dugumun childlarinin ve parentinin hesaplanmasi için makrolar
#define leftChild(i) (2 * i + 1)
#define rightChild(i) (2 * i + 2)
#define parent(i) ((i - 1) / 2)


typedef struct HeapArray {
	int* array;
	int maxSize;
	int size;
} HeapArray;


// Parametre olarak verilen kapasitede bir HeapArray olusturur.
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

// Parametre olarak verilen indexteki max-heap özellgini bozan indexteki elemani left ve right childlarindan büyük olaniyla degistirir
// ve degistirilen elemandan yine ayni prosedürü recursive olarak tekrarlar.
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


// Heapdeki maksimum degeri (root) silmeden döndürür.
int getMax(HeapArray* heap) {
	
	return heap->array[0];
	
}

// Heapdeki eleman sayisini döndürür.
int getSize(HeapArray* heap) {
	
	return heap->size;
	
}

// Heap dolu olup olmadigin kontrol eder.
int isEmpty(HeapArray* heap) {
	
	if (heap->size == 0)
		return 1;
	else
		return 0;
}

// Heapdeki maksimum degeri (root) döndürür
// ve root yerine sondaki elemani yazarak silip max-heap özelligini saglamak root için maxHeapify fonksiyonunu cagirir.
int extractMax(HeapArray* heap) {
	
	int max = heap->array[0];
	
	heap->array[0] = heap->array[heap->size - 1];
	heap->size = heap->size - 1;
	
	maxHeapify(heap, 0);
	
	return max;
	
}

// Parametre olarak verilen degeri heapin en sonuna ekler.
// Sondaki eleman parenti ile max-heap özelligini saglamiyorsa swap edip parenttan recursive olarak kontrole devam eder.
// Ekleme basarili ise 1 degil ise 0 döndürür.
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
		
		return 1; // Ekleme baþarýlý.
	}
	
	return 0; // Ekleme baþarýsýz.
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
