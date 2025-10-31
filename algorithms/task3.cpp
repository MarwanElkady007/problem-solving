#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Heap
{
private:
    vector<int> heap;
    bool isMaxHeap;
    int heapSize;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyDown(int i)
    {
        int left = leftChild(i);
        int right = rightChild(i);
        int extreme = i;

        if (isMaxHeap)
        {
            if (left < heapSize && heap[left] > heap[extreme])
                extreme = left;
            if (right < heapSize && heap[right] > heap[extreme])
                extreme = right;
        }
        else
        {
            if (left < heapSize && heap[left] < heap[extreme])
                extreme = left;
            if (right < heapSize && heap[right] < heap[extreme])
                extreme = right;
        }

        if (extreme != i)
        {
            swap(heap[i], heap[extreme]);
            heapifyDown(extreme);
        }
    }

    void heapifyUp(int i)
    {
        while (i > 0 && ((isMaxHeap && heap[parent(i)] < heap[i]) ||
                         (!isMaxHeap && heap[parent(i)] > heap[i])))
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    Heap(bool type = true)
    { // true = MaxHeap, false = MinHeap
        isMaxHeap = type;
        heapSize = 0;
    }

    void insert(int value)
    {
        heap.push_back(value);
        heapSize++;
        heapifyUp(heapSize - 1);
    }

    int extractMax()
    {
        if (!isMaxHeap)
        {
            cout << "This is not a max heap.\n";
            return -1;
        }
        return extractRoot();
    }

    int extractMin()
    {
        if (isMaxHeap)
        {
            cout << "This is not a min heap.\n";
            return -1;
        }
        return extractRoot();
    }

    int extractRoot()
    {
        if (heapSize == 0)
        {
            cout << "Heap is empty.\n";
            return -1;
        }
        int root = heap[0];
        heap[0] = heap[heapSize - 1];
        heap.pop_back();
        heapSize--;
        heapifyDown(0);
        return root;
    }

    void printTree(int index = 0, int indent = 0, bool isRight = false)
    {
        if (index >= heapSize)
            return;

        if (rightChild(index) < heapSize)
            printTree(rightChild(index), indent + 4, true);

        for (int i = 0; i < indent; i++)
            cout << " ";

        if (indent > 0)
            cout << (isRight ? "/-- " : "\\-- ");
        cout << heap[index] << endl;

        if (leftChild(index) < heapSize)
            printTree(leftChild(index), indent + 4, false);
    }

    bool empty() { return heapSize == 0; }
    void clear()
    {
        heap.clear();
        heapSize = 0;
    }

    vector<int> getHeap() const { return heap; }
};

// ---------------------- Priority Queue Using Heap ----------------------
class PriorityQueue
{
private:
    Heap heap; // max-heap

public:
    PriorityQueue() : heap(true) {}

    void insert(int value, int priority)
    {
        int encoded = priority * 10000 + value;
        heap.insert(encoded);
    }

    void extractHighestPriority()
    {
        if (heap.empty())
        {
            cout << "Priority Queue is empty.\n";
            return;
        }
        int encoded = heap.extractMax();
        int priority = encoded / 10000;
        int value = encoded % 10000;
        cout << "Extracted Element: " << value << " (Priority " << priority << ")\n";
    }

    void displayQueue()
    {
        if (heap.empty())
        {
            cout << "Priority Queue is empty.\n";
            return;
        }

        vector<int> temp = heap.getHeap();
        vector<pair<int, int>> items;

        for (int encoded : temp)
        {
            int priority = encoded / 10000;
            int value = encoded % 10000;
            items.push_back({priority, value});
        }

        // Sort by priority descending
        sort(items.begin(), items.end(), [](auto &a, auto &b)
             { return a.first > b.first; });

        cout << "Priority Queue (Highest -> Lowest):\n";
        for (auto &p : items)
            cout << "Value: " << p.second << "  (Priority: " << p.first << ")\n";
    }
};

// ---------------------- Heap Sort ----------------------
void heapSort(vector<int> &arr)
{
    int n = arr.size();
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        int parent = i;
        while (true)
        {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int largest = parent;
            if (left < n && arr[left] > arr[largest])
                largest = left;
            if (right < n && arr[right] > arr[largest])
                largest = right;
            if (largest != parent)
            {
                swap(arr[parent], arr[largest]);
                parent = largest;
            }
            else
                break;
        }
    }

    // Extract elements
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        int heapSize = i;
        int parent = 0;
        while (true)
        {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int largest = parent;
            if (left < heapSize && arr[left] > arr[largest])
                largest = left;
            if (right < heapSize && arr[right] > arr[largest])
                largest = right;
            if (largest != parent)
            {
                swap(arr[parent], arr[largest]);
                parent = largest;
            }
            else
                break;
        }
    }
}

// ---------------------- Main Menu ----------------------
int main()
{
    Heap maxHeap(true);
    Heap minHeap(false);
    PriorityQueue pq;
    int choice;

    do
    {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Heap Operations\n";
        cout << "2. Priority Queue\n";
        cout << "3. Heap Sort\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int hChoice;
            do
            {
                cout << "\n--- HEAP MENU ---\n";
                cout << "1. Insert (Max Heap)\n";
                cout << "2. Insert (Min Heap)\n";
                cout << "3. Extract Max\n";
                cout << "4. Extract Min\n";
                cout << "5. Display Max Heap Tree\n";
                cout << "6. Display Min Heap Tree\n";
                cout << "0. Back\n";
                cout << "Enter choice: ";
                cin >> hChoice;

                if (hChoice == 1)
                {
                    int n, val;
                    cout << "Enter number of elements: ";
                    cin >> n;
                    for (int i = 0; i < n; i++)
                    {
                        cout << "Enter element " << i + 1 << ": ";
                        cin >> val;
                        maxHeap.insert(val);
                    }
                }
                else if (hChoice == 2)
                {
                    int n, val;
                    cout << "Enter number of elements: ";
                    cin >> n;
                    for (int i = 0; i < n; i++)
                    {
                        cout << "Enter element " << i + 1 << ": ";
                        cin >> val;
                        minHeap.insert(val);
                    }
                }
                else if (hChoice == 3)
                {
                    cout << "Extracted Max: " << maxHeap.extractMax() << endl;
                }
                else if (hChoice == 4)
                {
                    cout << "Extracted Min: " << minHeap.extractMin() << endl;
                }
                else if (hChoice == 5)
                {
                    cout << "Max Heap Tree:\n";
                    maxHeap.printTree();
                }
                else if (hChoice == 6)
                {
                    cout << "Min Heap Tree:\n";
                    minHeap.printTree();
                }
            } while (hChoice != 0);
        }
        else if (choice == 2)
        {
            int pqChoice;
            do
            {
                cout << "\n--- PRIORITY QUEUE MENU ---\n";
                cout << "1. Insert (value & priority)\n";
                cout << "2. Extract Highest Priority\n";
                cout << "3. Display Queue\n";
                cout << "0. Back\n";
                cout << "Enter choice: ";
                cin >> pqChoice;

                if (pqChoice == 1)
                {
                    int n, value, priority;
                    cout << "Enter number of elements: ";
                    cin >> n;
                    for (int i = 0; i < n; i++)
                    {
                        cout << "Enter value: ";
                        cin >> value;
                        cout << "Enter priority (0–9): ";
                        cin >> priority;
                        pq.insert(value, priority);
                    }
                }
                else if (pqChoice == 2)
                {
                    pq.extractHighestPriority();
                }
                else if (pqChoice == 3)
                {
                    pq.displayQueue();
                }
            } while (pqChoice != 0);
        }
        else if (choice == 3)
        {
            int n;
            cout << "Enter number of elements: ";
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; i++)
            {
                cout << "Enter element " << i + 1 << ": ";
                cin >> arr[i];
            }

            heapSort(arr);
            cout << "Sorted array: ";
            for (int x : arr)
                cout << x << " ";
            cout << endl;
        }
    } while (choice != 0);

    cout << "Exiting program...\n";
    return 0;
}