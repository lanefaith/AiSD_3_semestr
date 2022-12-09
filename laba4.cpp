#include <iostream>
#include <random>
#include <queue>

using namespace std;

struct Elem { //binary tree structure
    int key = 0;
    Elem* left = nullptr, *right = nullptr, *parent = nullptr;
};

int get_max(Elem* root) { //finding the maximum element in the tree
    Elem* tmp = new Elem;
    tmp = root;
    while (tmp->right != nullptr) tmp = tmp->right;
    return tmp->key;
}

int get_min(Elem* root) { //finding the minimum element in the tree
    Elem* tmp = root;
    while (tmp->left != nullptr) tmp = tmp->left;
    return tmp->key;
}

void preorder(Elem* current) { // preorder
    cout << current->key << " ";
    if (current->left) preorder(current->left);
    if (current->right) preorder(current->right);
}

void inorder(Elem* current) { // inorder
    if (current->left) inorder(current->left);
    cout << current->key << " ";
    if (current->right) inorder(current->right);
}

void postorder(Elem* current) { // postorder
    if (current->left) postorder(current->left);
    if (current->right) postorder(current->right);
    cout << current->key << " ";
}

bool search_elem(int value, Elem* root) { // checking for the existence of an element in the tree
    Elem* tmp = root;
    while (tmp != nullptr) {
        if (tmp->key == value) break;
        if (tmp->key > value) tmp = tmp->left;
        else tmp = tmp->right;
    }
    return (tmp != nullptr);
}

Elem* find_next(Elem*& root, int elem) { // search for the next element in the tree after the specified one
    Elem* cur = root, * next = nullptr;
    while (cur != nullptr) {
        if (cur->key > elem) {
            next = cur;
            cur = cur->left;
        }
        else  cur = cur->right;
    }
    return next;
}

Elem* find_prev(Elem*& root, int elem){ //search for the previous element in the tree after the specified one
    Elem* cur = root, * parent = nullptr;
    while (cur != nullptr) {
        if (cur->key < elem) {
            parent = cur;
            cur = cur->right;
        }
        else cur = cur->left;
    }
    return parent;
}

int tab = 0;

struct Generator {
    int random;
};

Generator random() {  //random number generator up to 100 to fill the tree
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> point(0, 100000);
    int random = point(mt);
    struct Generator Gen_elem;
    Gen_elem.random = random;
    return Gen_elem;
}

void draw_tree(Elem* root) { //draw the tree
    if (!root) return;
    tab += 5;
    draw_tree(root->right);
    for (int i = 0; i < tab; i++) cout << " ";
    cout << "->";
    cout << root->key << endl;
    draw_tree(root->left);
    tab -= 5;
    return;
}

void add(int elem, Elem*& root){ // adding a new randomly generated element to the tree
    if (!root) {
        root = new Elem;
        root->key = elem;
        root->left = 0;
        root->right = 0;
        return;
    }
    else{
        if (root->key > elem) add(elem, root->left);
        else add(elem, root->right);
    }
}

void sort_tree(Elem*& root) { //creating a tree and sorting it
    root = nullptr;
    int amount;
    cout << "Enter the number of elements in the tree (up to 100):" << endl;
    cin >> amount;
    if (amount == 0) {
        cout << "No elements.";
        return;
    }
    for (int i = 0; i < amount; i++){
        Generator rand_elem = random();
        int random = rand_elem.random;
        if (random > 100) amount++;
        if (random < 100) add(random, root);
    }
    cout << "Tree: " << endl;
    draw_tree(root);
    cout << endl;
}

Elem* min_elem(Elem*& root) {
    struct Elem* cur = root;
    while (cur && cur->left != nullptr) cur = cur->left;
    return cur;
}

Elem* delete_elem(Elem*& root, int elem) { //removing an element from the tree
    if (root == nullptr) return root;
    if (elem < root->key) root->left = delete_elem(root->left, elem);
    else if (elem > root->key) root->right = delete_elem(root->right, elem);
    else {
        Elem* tmp;
        if (root->left == nullptr) {
            tmp = root->right;
            free(root);
            return tmp;
        }
        else if (root->right == nullptr) {
            tmp = root->left;
            free(root);
            return tmp;
        }
        else if (root->left == nullptr && root->right == nullptr) {
            if (root->key == elem) return nullptr;
            else return root;
        }
        tmp = min_elem(root->right);
        root->key = tmp->key;
        root->right = delete_elem(root->right, tmp->key);
    }
    return root;
}

void bypassing_in_width(Elem*& root){ // bypassing of a tree in width
    if (root == nullptr) return;
    queue<Elem*>q;
    q.push(root);
    while (q.empty() == false) {
        Elem* node = q.front();
        cout << node->key << " ";
        q.pop();
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
}

int main() {
    int a, chek=0;
    Elem* root = new Elem;
    Elem* tmp = new Elem;
    sort_tree(root);
    int num, value;
    cout << "Select a function, enter its number: \n";
    while (1) {
        cout << "\n1. Get the min\n";
        cout << "2. Get the max\n";
        cout << "3. Preorder\n";
        cout << "4. Inorder\n";
        cout << "5. Postorder\n";
        cout << "6. Search an elem\n";
        cout << "7. Find the next\n";
        cout << "8. Find the prev\n";
        cout << "9. Delete an elem\n";
        cout << "10. Bypassing in width\n";
        cout << "11. Draw the tree\n";
        cout << "0. End the program\n\n";
        cin >> num;
        switch (num) {
        case 1:
            a = get_min(root);
            cout << "\nMinimum: " << a << "\n\n";
            break;
        case 2:
            a = get_max(root);
            cout << "\nMaximum: " << a << "\n\n";
            break;
        case 3:
            preorder(root);
            break;
        case 4:
            inorder(root);
            break;
        case 5:
            postorder(root);
            break;
        case 6:
            cout << "Enter the value you want to find" << endl;
            cin >> value; 
            if (search_elem(value, root)) cout << "Element exists" << endl;
            else cout << "Element does not exist" << endl;
            break;
        case 7:
            cout << "Enter a value" << endl;
            cin >> value;
            tmp = nullptr;
            tmp = find_next(root, value);
            if (tmp != nullptr) cout << "Next element of " << value << " is " << tmp->key;
            else cout << "No next element";
            break;
        case 8:
            cout << "Enter a value" << endl;
            cin >> value;
            tmp = nullptr;
            tmp = find_prev(root, value);
            if (tmp != nullptr) cout << "Previous element of " << value << " is " << tmp->key;
            else cout << "No previous element";
            break;
        case 9:
            cout << "Enter a value" << endl;
            cin >> value;
            delete_elem(root, value);
            draw_tree(root);
            break;
        case 10:
            bypassing_in_width(root);
            break;
        case 11:
            draw_tree(root);
            break;
        case 0:
            chek = 1;
            break;
        default:
            cout << "\nTry again\n";
        }
        if (chek == 1) break; // check the flag for the request to terminate the program
    }
    return 0;
}