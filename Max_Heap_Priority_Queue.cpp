#include <iostream>
#include <vector>

class MaxHeap {
private:
    std::vector<int> heap;

    void heapify(int n, int i) {
        int largest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < n && heap[i] < heap[leftChild]) {
            largest = leftChild;
        }

        if (rightChild < n && heap[largest] < heap[rightChild]) {
            largest = rightChild;
        }

        if (largest != i) {
            std::swap(heap[i], heap[largest]);
            heapify(n, largest);
        }
    }

public:
    void insert(int newNum) {
        int size = heap.size();
        if (size == 0) {
            heap.push_back(newNum);
        } else {
            heap.push_back(newNum);
            for (int i = (size / 2) - 1; i >= 0; i--) {
                heapify(size, i);
            }
        }
    }

    void deleteNode(int num) {
        int size = heap.size();
        int i;
        for (i = 0; i < size; i++) {
            if (num == heap[i]) {
                break;
            }
        }

        std::swap(heap[i], heap[size - 1]);
        heap.pop_back();

        for (i = (heap.size() / 2) - 1; i >= 0; i--) {
            heapify(heap.size(), i);
        }
    }

    void printHeap() {
        std::cout << "Max-Heap array: ";
        for (int num : heap) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MaxHeap maxHeap;
    maxHeap.insert(3);
    maxHeap.insert(4);
    maxHeap.insert(9);
    maxHeap.insert(5);
    maxHeap.insert(2);

    maxHeap.printHeap();

    maxHeap.deleteNode(4);
    maxHeap.printHeap();

    return 0;
}
