#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Contact {
    int id;
    char name[100];
    char phone[20];
    char email[100];
};

struct Node {
    int key;
    Contact contact;
    Node* left;
    Node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* createNode(int key, Contact contact) {
    Node* node = new Node;
    node->key = key;
    node->contact = contact;
    node->left = node->right = nullptr;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* root, int key, Contact contact, bool &success) {
    if (!root) {
        success = true;
        return createNode(key, contact);
    }

    if (key < root->key)
        root->left = insert(root->left, key, contact, success);
    else if (key > root->key)
        root->right = insert(root->right, key, contact, success);
    else {
        success = false;
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* search(Node* root, int key) {
    if (!root || root->key == key) return root;

    if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}

Node* findMin(Node* node) {
    while (node->left) node = node->left;
    return node;
}

Node* deleteNode(Node* root, int key, bool &deleted) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteNode(root->left, key, deleted);
    else if (key > root->key)
        root->right = deleteNode(root->right, key, deleted);
    else {
        deleted = true;

        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->key = temp->key;
        root->contact = temp->contact;
        root->right = deleteNode(root->right, temp->key, deleted);
    }

    if (!root) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);
        cout << "ID: " << root->key << ", Name: " << root->contact.name
             << ", Phone: " << root->contact.phone
             << ", Email: " << root->contact.email << endl;
        inorderTraversal(root->right);
    }
}

void printSpaces(int count) {
    for (int i = 0; i < count; ++i)
        cout << ' ';
}

int getMaxDepth(Node* root) {
    if (root == nullptr)
        return 0;
    int left = getMaxDepth(root->left);
    int right = getMaxDepth(root->right);
    return 1 + (left > right ? left : right);
}

void printLevel(Node* root, int level, int maxLevel, int indent) {
    if (level == 1) {
        printSpaces(indent);
        if (root) {
            cout << setw(3) << root->key;
        } else {
            cout << "   ";
        }
    } else if (level > 1) {
        if (root) {
            printLevel(root->left, level - 1, maxLevel, indent);
            printLevel(root->right, level - 1, maxLevel, indent);
        } else {
            printLevel(nullptr, level - 1, maxLevel, indent);
            printLevel(nullptr, level - 1, maxLevel, indent);
        }
    }
}

void printSlashes(Node* root, int level, int maxLevel, int indent) {
    if (level == 2) {
        printSpaces(indent - 2);
        if (root && root->left)
            cout << " /";
        else
            cout << "  ";

        printSpaces(4);

        if (root && root->right)
            cout << "\\ ";
        else
            cout << "  ";
    } else if (level > 2) {
        if (root) {
            printSlashes(root->left, level - 1, maxLevel, indent);
            printSlashes(root->right, level - 1, maxLevel, indent);
        } else {
            printSlashes(nullptr, level - 1, maxLevel, indent);
            printSlashes(nullptr, level - 1, maxLevel, indent);
        }
    }
}

void printTree(Node* root) {
    int maxLevel = getMaxDepth(root);
    int indent = 3 * (1 << (maxLevel - 1));

    for (int level = 1; level <= maxLevel; ++level) {
        printLevel(root, level, maxLevel, indent);
        cout << endl;

        if (level != maxLevel) {
            printSlashes(root, level + 1, maxLevel, indent);
            cout << endl;
        }

        indent /= 2;
    }
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

Contact* contactsArray = nullptr;
int contactsCount = 0;
int contactsCapacity = 0;

void ensureCapacity(int minCapacity) {
    if (contactsCapacity >= minCapacity) return;
    int newCapacity = contactsCapacity == 0 ? 4 : contactsCapacity * 2;
    while (newCapacity < minCapacity) newCapacity *= 2;

    Contact* newArray = new Contact[newCapacity];
    for (int i = 0; i < contactsCount; ++i) {
        newArray[i] = contactsArray[i];
    }
    delete[] contactsArray;
    contactsArray = newArray;
    contactsCapacity = newCapacity;
}

void addContactToArray(Contact c) {
    ensureCapacity(contactsCount + 1);
    contactsArray[contactsCount++] = c;
}

bool removeContactFromArray(int id) {
    for (int i = 0; i < contactsCount; ++i) {
        if (contactsArray[i].id == id) {
            for (int j = i; j < contactsCount - 1; ++j) {
                contactsArray[j] = contactsArray[j + 1];
            }
            contactsCount--;
            return true;
        }
    }
    return false;
}

int main() {
    Node* root = nullptr;
    int choice;

    while (true) {
        cout << "Address Book Application\n------------------------\n";
        cout << "1. Add New Contact\n2. Search for Contact\n3. Delete Contact\n";
        cout << "4. List All Contacts (Sorted by ID)\n5. Display Current Tree Structure\n------------------------\n";
        cout << "Enter operation (1-5): ";
        cin >> choice;

        if (choice == 1) {
            int id;
            Contact c;
            cout << "Enter unique ID (integer): ";
            cin >> id;
            cin.ignore();
            c.id = id;
            cout << "Enter name: ";
            cin.getline(c.name, 100);
            cout << "Enter phone: ";
            cin.getline(c.phone, 20);
            cout << "Enter email: ";
            cin.getline(c.email, 100);
                    bool success = false;
        root = insert(root, id, c, success);
        if (success) {
            cout << "Contact added successfully.\n";
            addContactToArray(c);
        } else {
            cout << "Error: Contact with ID " << id << " already exists.\n";
        }
    } else if (choice == 2) {
        int id;
        cout << "Enter ID to search for: ";
        cin >> id;
        Node* found = search(root, id);
        if (found) {
            cout << "Contact found:\n";
            cout << "ID: " << found->key << ", Name: " << found->contact.name
                 << ", Phone: " << found->contact.phone
                 << ", Email: " << found->contact.email << endl;
        } else {
            cout << "Contact not found.\n";
        }
    } else if (choice == 3) {
        int id;
        cout << "Enter ID to delete: ";
        cin >> id;

        bool removedFromArray = removeContactFromArray(id);
        if (!removedFromArray) {
            cout << "Contact not found.\n";
        } else {
            deleteTree(root);
            root = nullptr;

            bool dummy;
            for (int i = 0; i < contactsCount; ++i) {
                root = insert(root, contactsArray[i].id, contactsArray[i], dummy);
            }

            cout << "Contact deleted successfully and AVL tree rebuilt.\n";
        }
    } else if (choice == 4) {
        if (!root) {
            cout << "No contacts to display.\n";
        } else {
            cout << "Contacts (in order):\n";
            inorderTraversal(root);
        }
    } else if (choice == 5) {
        if (!root) {
            cout << "Tree is empty.\n";
        } else {
            cout << "Current AVL Tree Structure (IDs only):\n";
            printTree(root);
        }
    } else {
        cout << "Invalid choice. Exiting.\n";
        break;
    }

    cout << endl;
}

deleteTree(root);
delete[] contactsArray;
return 0;
}