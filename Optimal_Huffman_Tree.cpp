/*DS PROJECT
* Group Members:
* Abdullah Gill - 20i-0503
* Waleed Adnan - 20i-0897
*/

#include<iostream>
#include<fstream>
#include<string>

using namespace std;
int len = 0; //global

//stores in linked list
struct values {

	char ch;
	int count;
	bool done;
	int index;

	void init(char c, int co, int i) {
		ch = c;
		count = co;
		done = false;
		index = i;

	}

	void print() {
		cout << "index: " << index << "char: " << ch << "  count: " << count << endl;
	}

};

//structure for node
struct node {
	char ch;
	int count;
	node* left;
	node* right;

	void init1() { //initializing variables
		ch = '0';
		count = 0;
		left = nullptr;
		right = nullptr;

	}

	void init(char c, int co) { //parametrised
		ch = c;
		count = co;
		left = nullptr;
		right = nullptr;

	}

	void print() {
		cout << "char: " << ch << "  count: " << count << endl;
	}
};

//node class
template<class T>
class Node {

public:
	T data;
	Node<T>* next;
	Node<T>* left;
	Node<T>* right;

	//constructor
	Node() {
		//data = 0;
		next = NULL;
		left = NULL;
		right = NULL;

	}

	Node(T value) {
		data = value;
		next = NULL;
		left = NULL;
		right = NULL;
	}

};

template<typename T>
class LinkedList {
private:
	Node<T>* head; // parent

public:
	int total;
	int done; // keeps the count
	float abr;

	LinkedList() {// constructor
		head = NULL;
		total = 0;
		done = 0;
		abr = 0;
	}
	Node<T>* getHead() {
		return head;
	}


	void setHead(Node<T>* temp) {
		head = temp;
	}

	bool IsEmpty() {
		if (head == NULL)
			return true;
		else false;
	}

	//insertion into the linked list
	void  insert(Node<T>* val) {
		// cout << "x is " << x << endl;
		 //cout << "linked list inserting " << endl;
		if (head == NULL) { //inserting at head
			//Node<T>* tem = new Node<T>();
			//tem->data = val;
			head = val;
			cout << "inserted: " << head->data.ch << endl;

		}

		else { // finding empty location
			Node<T>* current_node = head;

			while (current_node->next != NULL) {
				current_node = current_node->next;

			}

			if (current_node != NULL)
			{
				//Node<T>* tem = new Node<T>();
				//tem->data = val;

				//x->inserted = true;
				current_node->next = val;
				//cout << " inserted:" << val->data.ch << endl;
			}
		}

		total++;
	}


	void display() {

		Node<T>* current_node = head; // Initialize current
		while (current_node != NULL)

		{
			current_node->data.print();
			current_node = current_node->next;

		}
	}

	void cal_len() {
		Node<T>* current_node = head; // Initialize current

		while (current_node != NULL)
		{
			len = len + current_node->data.count;
			current_node = current_node->next;

		}
	}

	void delete_node(char ch) {
		Node<T>* temp = head;
		Node<T>* prev = NULL;
		if (temp != NULL && temp->data.ch == ch)
		{
			head = temp->next;
			delete temp;
			total--;
			return;
		}
		else
		{
			while (temp != NULL && temp->data.ch != ch)
			{
				prev = temp;
				temp = temp->next;
			}
			if (temp == NULL)
				return;
			prev->next = temp->next;
			delete temp;
			total--;
		}
	}
	//searches if the chareacter is in the linked list, if found adds in the frequency, else makes a new node for the character
	void search(char ch) {
		bool found = false;
		Node<T>* current_node = head; // Initialize current

		while (current_node != NULL)
		{
			if (current_node->data.ch == ch) {
				current_node->data.count++;
				found = true;
				break;
			}
			current_node = current_node->next;

		}
		if (found == false) {
			Node<T>* t = new Node<T>();
			t->data.init(ch, 1, total + 1);


			insert(t);
			cout << "Total: " << total << endl;
		}
	}

	//for task 1
	Node<T>* delete_min() {
		Node<T>* current_node = head; // Initialize current
		Node<T>* min_node = new Node<T>();
		int min = 999;
		while (current_node != NULL)
		{
			if (current_node->data.count < min and current_node->data.done == false) {
				min_node = current_node;
				min = current_node->data.count;
			}
			current_node = current_node->next; //next position

		}
		current_node = head; // Initialize current

		while (current_node != NULL)
		{
			if (current_node->data.index == min_node->data.index) {
				current_node->data.done = true;
				done++;
				break;
			}
			current_node = current_node->next;

		}
		cout << "returning: " << min_node->data.count << endl;
		return min_node;
	}

	void huffman_tree() {
		while (done != total - 1) {

			Node<T>* left = delete_min();
			Node<T>* right = delete_min();
			cout << "left: " << left->data.ch << endl;

			cout << "right: " << right->data.ch << endl;

			Node<T>* top = new Node<T>();
			top->data.init('n', left->data.count + right->data.count, total + 1);

			top->left = left;
			top->right = right;

			insert(top);

		}
		Node<T>* root = head; // Initialize current
		while (root->next != NULL)
		{
			root = root->next;

		}

		int arr[25];
		cal_code(root, arr, 0);
		abr = float(abr / len);
		cout << "Compression_ratio: " << float(8 / abr) << endl;

	}

	void cal_code(Node<T>* root, int a[], int size) {
		if (root->left) {
			a[size] = 0;
			cal_code(root->left, a, size + 1);
		}
		if (root->right) {

			a[size] = 1;
			cal_code(root->right, a, size + 1);
		}
		if (root->left == NULL && root->right == NULL) {

			cout << "character: " << root->data.ch << "   code: ";
			abr = abr + (root->data.count * size);
			for (int i = 0; i < size; i++) {
				cout << a[i];
			}
			cout << endl;
		}
	}

};

template<class T>
class priority_queue
{
	T** arr;
	int capacity;
	int curr_size;
	float abr;

public:
	// Constructor
	priority_queue() {
		capacity = 1;
		arr = new T * [capacity];
		curr_size = 0;
		abr = 0;
	}

	priority_queue(int c) {
		capacity = c;
		arr = new T * [capacity];
		curr_size = 0;
		abr = 0;
	}
	// to get index of parent
	int parent(int i) {
		return (i - 1) / 2;
	}

	// to get index of left child 
	int left(int i) {
		return (2 * i + 1);
	}

	// to get index of right child 
	int right(int i) {
		return (2 * i + 2);
	}
	bool isEmpty() {
		if (curr_size == 0)
			return true;
		else
			return false;
	}

	void insertKey(T* data)
	{
		cout << "***inserting into priority queue***" << endl;
		if (curr_size == capacity)
		{
			cout << "\nOverflow: Could not insertKey\n";
			return;
		}
		curr_size++;
		int i = curr_size - 1;
		arr[i] = data;
		cout << "insert at index: " << i << endl;
		cout << "inserting" << data->count << " " << data->ch << endl;
		//if parent is larger than the child swap
		while (i != 0 && arr[parent(i)]->count > arr[i]->count)

		{
			//	cout << "checking parent : " << endl;
			T* temp = arr[parent(i)];
			arr[parent(i)] = arr[i];
			arr[i] = temp;
			i = parent(i);
		}

		cout << "Displaying: " << endl;
		display();

	}

	void check_left_right(int i)
	{
		int l = left(i);
		int r = right(i);
		int swap_with = i;
		cout << "parent: " << arr[i]->count << endl;
		//cout << "left: " << arr[l]->count << " " << arr[l]->ch << " right: " << arr[r]->count << endl;
		if (l < curr_size && arr[l]->count < arr[swap_with]->count)
			swap_with = l;
		if (r < curr_size && arr[r]->count < arr[swap_with]->count)
			swap_with = r;

		if (swap_with != i)
		{
			cout << "yes swapping" << endl;
			T* temp = arr[swap_with];
			arr[swap_with] = arr[i];
			arr[i] = temp;
			check_left_right(swap_with);
		}

	}

	T* delete_min()
	{
		cout << "in deleteing priority" << endl;

		T* null_message = new T;
		null_message->init1();
		if (curr_size <= 0)
			return null_message;
		if (curr_size == 1)
		{
			curr_size--;
			return arr[0];
		}

		T* temp = arr[0];
		arr[0] = arr[curr_size - 1];
		curr_size--;
		cout << "Current size is: " << curr_size << endl;
		cout << "deleting : " << temp->count << " " << temp->ch << endl;
		int i = 0;
		check_left_right(0);
		display();

		return temp;
	}

	void display() {
		cout << "Displaying priority queue: " << endl;
		for (int i = 0; i < curr_size; i++) {
			cout << i << " " << arr[i]->count << " " << arr[i]->ch << endl;
		}
	}

	void huffman_tree() {
		while (curr_size != 1) {
			T* left = delete_min();
			T* right = delete_min();
			cout << "left: " << left->ch << endl;
			cout << "right: " << right->ch << endl;

			T* top = new node;
			top->init('n', left->count + right->count);

			top->left = left;
			top->right = right;

			insertKey(top);
		}

		T* root = delete_min();
		int arr[25];

		cal_code(root, arr, 0);
		abr = float(abr / len);
		cout << "Compression_ratio: " << float(8 / abr) << endl;

	}

	void cal_code(node* root, int a[], int size) { //calculates the total frequency
		if (root->left) {
			a[size] = 0;
			cal_code(root->left, a, size + 1);
		}
		if (root->right) {
			a[size] = 1;
			cal_code(root->right, a, size + 1);
		}
		if (root->left == NULL && root->right == NULL) {
			cout << "character: " << root->ch << "   code: ";
			abr = abr + (root->count * size);
			for (int i = 0; i < size; i++) {
				cout << a[i];
			}
			cout << endl;
		}
	}

};

int main() {
	cout << "***DATA PROJECT***" << endl;
	string filename;
	LinkedList<values> ll;
	cout << "Input file name: ";
	cin >> filename;
	string line;
	ifstream MyReadFile(filename);
	while (getline(MyReadFile, line)) {
		line = line + ".";
		int i = 0;
		while (line[i] != '.') {
			ll.search(line[i]);
			i++;
		}
	}

	MyReadFile.close();

	ll.display();
	ll.cal_len();
	cout << "len of file: " << len << endl;

	priority_queue<node> huffman(ll.total);

	Node<values>* current_node = ll.getHead();

	while (current_node != NULL)
	{
		node* temp = new node;
		temp->init(current_node->data.ch, current_node->data.count);
		huffman.insertKey(temp);
		current_node = current_node->next;
	}

	cout << "\n****TASK 1****" << endl;
	ll.huffman_tree();

	//huffman.display(); //displaying priority queue
	cout << "\n****TASK 2****" << endl;
	huffman.huffman_tree();

	return 0;
}