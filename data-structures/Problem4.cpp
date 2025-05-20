#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

struct Patient {
    char name[50];
    int severity;
    int arrival_time;

    Patient() {}
    Patient(const char* n, int s, int a) {
        strcpy(name, n);
        severity = s;
        arrival_time = a;
    }

    bool operator>(const Patient& other) const {
        if (severity != other.severity)
            return severity > other.severity;
        return arrival_time < other.arrival_time;
    }

    void print() const {
        cout << name;
    }
};

class MaxHeap {
private:
    Patient* heap;
    int capacity;
    int size;

    void swap(int i, int j) {
        Patient temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapify_up(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(index, parent);
                index = parent;
            } else break;
        }
    }

    void heapify_down(int index) {
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest != index) {
                swap(index, largest);
                index = largest;
            } else break;
        }
    }

public:
    MaxHeap(int cap = 100) {
        capacity = cap;
        size = 0;
        heap = new Patient[capacity];
    }

    ~MaxHeap() {
        delete[] heap;
    }

    void insert(Patient p) {
        if (size >= capacity) {
            cout << "Heap is full!\n";
            return;
        }
        heap[size] = p;
        heapify_up(size);
        size++;
    }

    Patient* peek() {
        if (size == 0) return nullptr;
        return &heap[0];
    }

    Patient extract_max() {
        if (size == 0) return Patient();
        Patient top = heap[0];
        heap[0] = heap[--size];
        heapify_down(0);
        return top;
    }

    void print_heap() {
        cout << "Heap: [";
        for (int i = 0; i < size; ++i) {
            cout << heap[i].name;
            if (i != size - 1) cout << ", ";
        }
        cout << "]\n";
    }

    bool is_empty() {
        return size == 0;
    }

    void load_from_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name;
            int severity, arrival_time;

            getline(ss, name, ',');
            ss >> severity;
            ss.ignore(1, ','); 
            ss >> arrival_time;

            Patient p(name.c_str(), severity, arrival_time);
            insert(p);
        }

        file.close();
    }
};

int main() {
    MaxHeap pq;

    pq.load_from_file("Problem4.txt");

    cout << "\nHeap after Insertions:\n";
    pq.print_heap();

    cout << "\nTreatment Order:\n";
    while (!pq.is_empty()) {
        Patient p = pq.extract_max();
        cout << "Treating: " << p.name << "\n";
    }

    return 0;
}
