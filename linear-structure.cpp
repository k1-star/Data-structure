#include<iostream>
#include<algorithm>
#include<vector>
template<typename T>class list {

public:
	virtual void clear() = 0;
	virtual int length() const = 0;
	virtual void insert(const T& x, int i) = 0;
	virtual void remove(int i) = 0;
	virtual ~list() {};
	
};
template<typename T>class linklist :public list<T> {
public:
	struct node {
		T data;
		node* next;
		node(T value) :data(value), next(nullptr) {}//remember the syntex 
		~node() {};

	};
	node* head;
	int currentlength;//remember the difference between node and list

	linklist() :head(nullptr), currentlength(0) {}
	~linklist() {
		clear();
	}
	void clear() {
		node* current = head;
		while (current != nullptr) { node* next = current->next; delete current; current = next; }
		head = nullptr;
		currentlength = 0;
	}
	int length()const { return currentlength; }
	node* move(int i) const {
		if (i < 0 || i >= currentlength) return nullptr;
		node* current = head;
		for (int j = 0; j < i; j++) { current = current->next; }
		return current;
	}
	void insert(const T& x, int i) {
		if (i < 0 || i > currentlength) return; // 防止非法索引

		node* newNode = new node(x);
		if (i == 0) {
			newNode->next = head;  // 头插法
			head = newNode;
		}
		else {
			newNode->next = move(i - 1)->next;
			move(i - 1)->next = newNode;
		}
		currentlength++;
	}
	void remove(int i) {
		if (i < 0 || i >= currentlength) return;
		node* del = nullptr;
		if (i == 0) { del = head; head = head->next; }
		if (i > 0 && i <= currentlength) {
			node* pre = move(i - 1);
			del = pre->next;
			pre->next = del->next;
		}
		delete del;
		currentlength--;
	}
	

};
template<typename T>class dlinklist :public list<T> {
public:
	struct node {
		T data;
		node* pre;
		node* next;
		node(T value) :data(value), pre(nullptr), next(nullptr) {}
		~node() {}
	};
	int currentlength;
	node* head;
	dlinklist():currentlength(0),head(nullptr) {}
	~dlinklist() {
		clear();
	}
	void clear() { 
		node* current = head;
		for (int j = 0; j < currentlength; j++) {
			node* del = nullptr;
			del = current;
			current = current->next;
			delete del;
		}
		head = nullptr;
	}
	int length() const{ return currentlength; }
	void remove(int i) {
		if (i == 1) { clear(); }
		else {
			node* save = move(i - 1); node* del = save->next;
			save->next = save->next->next;
			save->next->next->pre = save;
			delete del;
		}
		currentlength--;
	}
	void insert(const T&x,int i) {
		if (i == 0) {
			node* newnode = new node(x);
			head = newnode;
		}
		else if (i == currentlength) {
			node* newnode = new node(x);
			node* save = move(i - 1);
			save->next = newnode;
			newnode->pre = save;
		}
		else {
			node* save = move(i - 1);
			node* newnode = new node(x);
			save->next->next->pre = newnode;
			newnode->next = save->next->next;
			save->next = newnode;
			newnode->pre = save;
		}
		currentlength++;
	}
	node* move(int i) {
		node* current = head;
		for (int j = 0; j < i; j++) { current = current->next; }
		return current;
	}
	void assemble(dlinklist<T>& b) {
		if (b.head == nullptr) return; 

		if (head == nullptr) { 
			head = b.head;
		}
		else {
			node* p = move(currentlength - 1); 
			p->next = b.head; 
			b.head->pre = p; 
		}
		currentlength += b.currentlength; 
		b.head = nullptr; 
		b.currentlength = 0; 
	}

	void cout() {
		node* now = head;
		for (int i = 0; i < currentlength; i++) { 
			std::cout << now->data;
		now = now->next;
		}
	}
};
template<typename T>class clinklist :public list<T> {
public:
	struct node {
		T data;
		node* pre;
		node* next;
		node(T value) :data(value), pre(nullptr), next(nullptr) {}
		~node() {}
	};
	int currentlength;
	node* head;
	clinklist() :currentlength(0), head(nullptr) {}
	~clinklist() {
		clear();
	}
	void clear() {
		node* current = head;
		for (int j = 0; j < currentlength; j++) {
			node* del = nullptr;
			del = current;
			current = current->next;
			delete del;
		}
		head = nullptr;
	}
	int length() const { return currentlength; }
	void remove(int i) {
		if (i == 1) { clear(); }
		else {
			node* save = move(i - 1); node* del = save->next;
			save->next = save->next->next;
			save->next->next->pre = save;
			delete del;
		}
		currentlength--;
	}
	void insert(const T& x, int i) {
		if (i == 0) {
			node* newnode = new node(x);
			head = newnode;
			head->next = head;
			head->pre = head;
		}
		else if (i == currentlength+1) {
			node* newnode = new node(x);
			node* save = move(i );
			save->next = newnode;
			newnode->pre = save;
			newnode->next = head;
			head->pre = newnode;
		}
		else {
			node* save = move(i - 1);
			node* newnode = new node(x);
			save->next->next->pre = newnode;
			newnode->next = save->next->next;
			save->next = newnode;
			newnode->pre = save;
		}
		currentlength++;
	}
	node* move(int i) {
		node* current = head;
		for (int j = 0; j < i; j++) { current = current->next; }
		return current;
	}
};


template <typename T>
class sqlist : public list<T> {
public:
	T* data;
	int maxSize;
	int currentLength;


	sqlist(int size = 10) : maxSize(size), currentLength(0) {
		data = new T[maxSize];
	}

	~sqlist() {
		delete[] data;
	}

	void clear() override {
		currentLength = 0;
	}

	int length() const override {
		return currentLength;
	}

	void insert(const T& x, int i) override {
		if (i < 0 || i > currentLength) {
			throw std::out_of_range("Index out of range");
		}
		if (currentLength == maxSize) {
			resize();
		}
		for (int j = currentLength; j > i; j--) {
			data[j] = data[j - 1];
		}
		data[i] = x;
		currentLength++;
	}

	void remove(int i) override {
		if (i < 0 || i >= currentLength) {
			throw std::out_of_range("Index out of range");
		}
		for (int j = i; j < currentLength - 1; j++) {
			data[j] = data[j + 1];
		}
		currentLength--;
	}
	T* rotate(int i) {
		int ptr = 0; int k = 0; int length = currentLength;
		T* lll = new T[length];
		for (int y = 0; y < length; y++)lll[y] = data[(i + y) % length];
		
		return lll;
	}
	void sort() {
		for (int i = 0; i < currentLength-1; i++) {
			for (int j = 0; j < currentLength - i-1; j++) {
				if (data[j] > data[j + 1]) { T temp = data[j]; data[j] = data[j + 1]; data[j + 1] = temp; }
		}
		}
	}
	void reverse(int p, int q) {
		if (p > q)std::swap(p, q);
		int k = 0;
		k = (q-p) / 2+ 1;
		int time = 0;
		while (time++ < k) {
			std::swap(data[p + time-1], data[q - time-1]);
		}
	}
	void reversewagons(int& size, int*& number, int& time, int*& change) {
		sqlist<int>train;
		train.data = number;
		train.currentLength = size;
		for (int i = 0; i < time; i++) { train.reverse(change[2 * i], change[2 * i + 1]); }
		for (int i = 0; i < size;i++) {
			std::cout << train.data[i];
		}
	}
private:
	void resize() {
		maxSize *= 2;
		T* newData = new T[maxSize];
		for (int i = 0; i < currentLength; i++) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
	}
	
};



int main() {
	linklist<int> ll;
	int q = 10; int w = 10; int e = 10;
	ll.insert(q, 0);
	ll.insert(w, 1);
	ll.insert(e, 1);

	std::cout << "Length: " << ll.length() << std::endl;
	ll.remove(1);
	std::cout << "Length: " << ll.length() << std::endl;
	std::cout << "The single node template was shown above." << std::endl;
	dlinklist<int> lzh;
	int l = 1; int z = 2;
	lzh.insert(l, 0); lzh.insert(z, 1);
	std::cout << "Length: " << lzh.length()<<std::endl;
	std::cout << "The double node template was shown above." << std::endl;
	clinklist<int> djy;
	int a = 1; int b = 2;
	djy.insert(a, 0); djy.insert(b, 1);
	std::cout << "Length: " << djy.length() << std::endl;
	std::cout << "The cycle node template was shown above." << std::endl;
	sqlist<int> ppp;
	for (int i = 0; i < 10; i++) { ppp.insert( i, i); }
	int *ptr=ppp.rotate(3);
	for (int k = 0; k < 10; k++)std::cout << ptr[k];
	std::cout << std::endl;
	delete[]ptr;
	ppp.sort();
	for (int k = 0; k < 10; k++)std::cout << ppp.data[k];
	std::cout <<std::endl<< "sqlist over"<<std::endl;

//****************************************************	
//solutions to problem 2597
	/*
	int size = 0; int k = 0; int time = 0; int j = 0;
	std::cin >> size;
	int* p = new int[size];
	while (k++ < size) { std::cin >> p[k-1]; }
	std::cin >> time;
	int* reverse = new int[2 * time];
	while (j++ < 2 * time) { std::cin >> reverse[j - 1]; }
	sqlist<int>solution;
	solution.reversewagons(size, p , time, reverse);
	std::cout << std::endl<<"Now here's an example of using iterator: ";
	
	// 使用迭代器遍历 vector
	std::vector<int> vec = { 1, 2, 3, 4, 5 };
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	*/
	//************************************************
	//solutions to problem 2598 一定要记得更新currentlength!!!!!!!!!!
	/*
	std::cin >> size; k = 0;  j = 0;
	dlinklist<int>task;
	while (k++ < size) { std::cin >> j; task.insert(j, k-1); }
	dlinklist<int>less, more;
	int thresh = 0;
	std::cin >> thresh;
	dlinklist<int>::node* queue = task.head; 
	while (queue!=nullptr) {
		if (queue->data < thresh)less.insert(queue->data, less.currentlength );
		if (queue->data >= thresh)more.insert(queue->data, more.currentlength );
		queue = queue->next;
	};
	less.assemble(more);
	less.cout();
	*/
	//**********************************************
	//solutions to problem 2599
	/*
	dlinklist<int> fir, sec; int firsize = 0; int secsize = 0; int c = 0;
	std::cin >> firsize; for (int i = 0; i < firsize; i++) { std::cin >> c; fir.insert(c, i); };
	std::cin >> secsize; for (int i = 0; i < secsize; i++) { std::cin >> c; sec.insert(c, i); };
	dlinklist<int>::node* firnow = fir.head; dlinklist<int>::node* secnow = sec.head;
	dlinklist<int>nodecrease; int x = 0; 
	while (firnow&&secnow) {
		if (firnow->data < secnow->data) { nodecrease.insert(firnow->data, x); x++; firnow = firnow->next; }
		else { nodecrease.insert(secnow->data, x); x++; secnow = secnow->next; }
	}
	if (firnow) { while (firnow) { nodecrease.insert(firnow->data, x); x++; firnow = firnow->next; } }
	if (secnow) { while (secnow) { nodecrease.insert(secnow->data, x); x++; secnow = secnow->next; } }
	nodecrease.cout();
	*/
	return 0;
}