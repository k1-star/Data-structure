#include<iostream>
#include<string>
template <typename T>
class Queue {
public:
	virtual bool empty()const = 0;
	virtual void clear() = 0;
	virtual int size()const = 0;
	virtual void enQueue(const T& x) = 0;
	virtual T deQueue() = 0;
	virtual T getHead()const = 0;
	virtual ~Queue() {}
};
template <typename T>class cqueue :public Queue<T> {
public:
	int front;
	int rear;
	T* base;
	int currentlength;
	cqueue() :front(0), rear(0), currentlength(0) { base = new T[10000]; }
	~cqueue() { clear(); delete[]base; }
	bool empty()const {
		return rear == front;
	}
	void clear()override { front = 0; rear = 0; currentlength = 0; }
	int size()const { return currentlength; }
	void enQueue(const T& x) { base[rear] = x; rear = (rear + 1) % 10000; currentlength++; }
	T deQueue() override {
		T temp = base[front];
		front = (front + 1) % 10000;
		currentlength--;
		return temp;
	}
	T getHead() const { return base[front]; }
};
struct point {
	int x;
	int y;
	int time = 0;
};
int main() {
	/*seqstack<int> Seqstack;
	Seqstack.push(1);
	std::cout << Seqstack.getTop();
	linkstack<int> Linkstack;
	Linkstack.push(1);
	std::cout << Linkstack.getTop();
	cqueue<int> cQueue;
	for (int i = 0; i < 20; i++) { cQueue.enQueue(i); }
	std::cout<<cQueue.deQueue();
	cQueue.enQueue(21);
	std::cout << cQueue.getHead();
	linkqueue<int>linkQueue;
	linkQueue.enQueue(520);
	std::cout << linkQueue.deQueue();*/
	cqueue<point>hold;
	int size = 0;
	std::cin >> size;
	int** arr = new int* [size]; bool** state = new bool* [size];
	for (int i = 0; i < size; i++) { std::string thisrow; arr[i] = new int[size]; state[i] = new bool[size]; std::cin >> thisrow; for (int j = 0; j < size; j++) { arr[i][j] = thisrow[j] - '0'; state[i][j] = 0; } }
	point init; std::cin >> init.x >> init.y; init.x--; init.y--;
	point dest; std::cin >> dest.x >> dest.y; dest.x--; dest.y--;
	state[init.x][init.y] = 1;
	init.time = 0;
	int step = 0;
	bool can = 0;
	hold.enQueue(init);

	while (hold.size() != 0) {
		point now = hold.deQueue();
		if (now.time != step)step = now.time;
		if (now.x == dest.x && now.y == dest.y) { can = 1; break; }
		if (now.x + 1 < size && state[now.x + 1][now.y] == 0 && arr[now.x + 1][now.y] == 0) { point right; right.x = now.x + 1; right.y = now.y; right.time = step + 1; state[now.x + 1][now.y] = 1; hold.enQueue(right); }
		if (now.x - 1 >= 0 && state[now.x - 1][now.y] == 0 && arr[now.x - 1][now.y] == 0) { point left; left.x = now.x - 1; left.y = now.y; left.time = step + 1; state[now.x - 1][now.y] = 1; hold.enQueue(left); }
		if (now.y + 1 < size && state[now.x][now.y + 1] == 0 && arr[now.x][now.y + 1] == 0) { point up;  up.y = now.y + 1; up.x = now.x; up.time = step + 1; state[now.x][now.y + 1] = 1; hold.enQueue(up); }
		if (now.y - 1 >= 0 && state[now.x][now.y - 1] == 0 && arr[now.x][now.y - 1] == 0) { point down; down.y = now.y - 1; down.x = now.x; down.time = step + 1; state[now.x][now.y - 1] = 1; hold.enQueue(down); }

	}

	if (can)
	{
		std::cout << step;
	}
	else
	{
		std::cout << -1;
	}
	for (int i = 0; i < size; i++) {
		delete[] arr[i];
		delete[] state[i];
	}
	delete[] arr;
	delete[] state;
	return 0;
}