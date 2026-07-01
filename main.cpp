#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>
#include <string>
#include <stdexcept>
using namespace std;

// ========== TASK 1: DATA STRUCTURES ==========

// Goods Structure
struct Goods {
    string name;
    string type;
    double weight;
    Goods(string n = "", string t = "", double w = 0) : name(n), type(t), weight(w) {}
};

// ========== TASK 2: QUEUE IMPLEMENTATION ==========

class TruckQueue {
private:
    queue<string> truckQueue;
    
public:
    void enQueue(string truckName) {
        truckQueue.push(truckName);
        cout << truckName << " has arrived and joined the queue." << endl;
    }
    
    void deQueue() {
        if (!truckQueue.empty()) {
            cout << truckQueue.front() << " is now being loaded." << endl;
            truckQueue.pop();
        } else {
            cout << "No trucks in queue." << endl;
        }
    }
    
    void displayFront() {
        if (!truckQueue.empty()) {
            cout << "Next truck to load: " << truckQueue.front() << endl;
        } else {
            cout << "Queue is empty." << endl;
        }
    }
    
    void displayAll() {
        queue<string> temp = truckQueue;
        cout << "Truck Queue: ";
        if (temp.empty()) {
            cout << "Empty";
        }
        while (!temp.empty()) {
            cout << "[" << temp.front() << "] ";
            temp.pop();
        }
        cout << endl;
    }
};

// ========== TASK 3: SORTING ALGORITHMS ==========

// Bubble Sort (Descending)
void bubbleSortDescending(vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] < arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// QuickSort (Descending)
int partitionDescending(vector<double>& arr, int low, int high) {
    double pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] >= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSortDescending(vector<double>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionDescending(arr, low, high);
        quickSortDescending(arr, low, pi-1);
        quickSortDescending(arr, pi+1, high);
    }
}

// ========== TASK 4: AVL TREE ==========

struct CargoNode {
    double weight;
    string name;
    int height;
    CargoNode* left;
    CargoNode* right;
    
    CargoNode(double w, string n) : weight(w), name(n), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    CargoNode* root;
    
    int getHeight(CargoNode* node) {
        return node ? node->height : 0;
    }
    
    int getBalance(CargoNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
    
    CargoNode* rotateRight(CargoNode* y) {
        CargoNode* x = y->left;
        CargoNode* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        
        return x;
    }
    
    CargoNode* rotateLeft(CargoNode* x) {
        CargoNode* y = x->right;
        CargoNode* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        
        return y;
    }
    
    CargoNode* insert(CargoNode* node, double weight, string name) {
        if (!node) {
            return new CargoNode(weight, name);
        }
        
        if (weight < node->weight) {
            node->left = insert(node->left, weight, name);
        } else if (weight > node->weight) {
            node->right = insert(node->right, weight, name);
        } else {
            return node;
        }
        
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);
        
        if (balance > 1 && weight < node->left->weight) return rotateRight(node);
        if (balance < -1 && weight > node->right->weight) return rotateLeft(node);
        if (balance > 1 && weight > node->left->weight) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && weight < node->right->weight) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        
        return node;
    }
    
    CargoNode* search(CargoNode* node, double weight) {
        if (!node || node->weight == weight) return node;
        if (weight < node->weight) return search(node->left, weight);
        return search(node->right, weight);
    }
    
    void inOrder(CargoNode* node) {
        if (node) {
            inOrder(node->left);
            cout << "  " << node->name << " (" << node->weight << "kg)" << endl;
            inOrder(node->right);
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    void insert(double weight, string name) {
        if (weight <= 0) {
            throw invalid_argument("Weight must be positive!");
        }
        if (name.empty()) {
            throw invalid_argument("Name cannot be empty!");
        }
        root = insert(root, weight, name);
        cout << "✓ Inserted: " << name << " (" << weight << "kg)" << endl;
    }
    
    bool search(double weight) {
        CargoNode* result = search(root, weight);
        if (result) {
            cout << "✓ Found: " << result->name << " (Weight: " << weight << "kg)" << endl;
            return true;
        }
        cout << "✗ Item with weight " << weight << "kg not found." << endl;
        return false;
    }
    
    void display() {
        cout << "\n=== AVL Tree Inventory (Sorted by Weight) ===" << endl;
        inOrder(root);
        if (!root) cout << "  Tree is empty." << endl;
        cout << endl;
    }
};

// ========== MAIN DEMONSTRATION ==========

int main() {
    cout << "=========================================" << endl;
    cout << "   SWIFT-LOAD LOGISTICS SYSTEM DEMO      " << endl;
    cout << "=========================================" << endl << endl;
    
    // ----- TASK 1: Goods Data Structure -----
    cout << "=== TASK 1: Goods Data Structure ===" << endl;
    Goods g1("Laptop", "Electronics", 2.5);
    Goods g2("Monitor", "Electronics", 5.0);
    Goods g3("Keyboard", "Accessories", 0.8);
    
    cout << "Goods created:" << endl;
    cout << "  " << g1.name << " | " << g1.type << " | " << g1.weight << "kg" << endl;
    cout << "  " << g2.name << " | " << g2.type << " | " << g2.weight << "kg" << endl;
    cout << "  " << g3.name << " | " << g3.type << " | " << g3.weight << "kg" << endl;
    
    // Update weight
    g1.weight = 3.0;
    cout << "\nUpdated Laptop weight: " << g1.weight << "kg" << endl << endl;
    
    // ----- TASK 2: FIFO Queue Demonstration -----
    cout << "=== TASK 2: FIFO Truck Queue ===" << endl;
    TruckQueue tq;
    tq.enQueue("Truck A");
    tq.enQueue("Truck B");
    tq.enQueue("Truck C");
    tq.displayAll();
    tq.deQueue();
    tq.displayAll();
    cout << endl;
    
    // ----- TASK 3: Sorting Algorithms -----
    cout << "=== TASK 3: Sorting 12 Cargo Weights ===" << endl;
    vector<double> weights = {120, 55, 87, 200, 33, 145, 99, 66, 180, 75, 90, 130};
    vector<double> weightsCopy = weights;
    
    cout << "Original weights: ";
    for (double w : weights) cout << w << " ";
    cout << endl;
    
    // Measure Bubble Sort
    auto start = chrono::high_resolution_clock::now();
    bubbleSortDescending(weights);
    auto end = chrono::high_resolution_clock::now();
    auto bubbleTime = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "\nBubble Sort Result: ";
    for (double w : weights) cout << w << " ";
    cout << endl;
    cout << "Bubble Sort Time: " << bubbleTime.count() << " microseconds" << endl;
    
    // Measure QuickSort
    start = chrono::high_resolution_clock::now();
    quickSortDescending(weightsCopy, 0, weightsCopy.size() - 1);
    end = chrono::high_resolution_clock::now();
    auto quickTime = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "\nQuickSort Result: ";
    for (double w : weightsCopy) cout << w << " ";
    cout << endl;
    cout << "QuickSort Time: " << quickTime.count() << " microseconds" << endl << endl;
    
    // ----- TASK 4: AVL Tree Demonstration -----
    cout << "=== TASK 4: AVL Tree Implementation ===" << endl;
    AVLTree tree;
    
    try {
        tree.insert(2.5, "Laptop");
        tree.insert(5.0, "Monitor");
        tree.insert(0.8, "Keyboard");
        tree.insert(8.0, "Desktop");
        tree.insert(0.3, "Mouse");
        tree.insert(3.5, "Tablet");
        
        tree.display();
        
        cout << "Search Tests:" << endl;
        tree.search(2.5);
        tree.search(10.0);
        
        cout << "\nError Handling Test:" << endl;
        try {
            tree.insert(-5.0, "Invalid");
        } catch (const exception& e) {
            cout << "  Error caught: " << e.what() << endl;
        }
        
        try {
            tree.insert(10.0, "");
        } catch (const exception& e) {
            cout << "  Error caught: " << e.what() << endl;
        }
        
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "\n=========================================" << endl;
    cout << "           DEMO COMPLETE                 " << endl;
    cout << "=========================================" << endl;
    
    return 0;
}