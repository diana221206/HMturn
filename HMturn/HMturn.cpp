#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    T* data;         
    int front;       
    int rear;        
    int capacity;    
    int size;        

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[(front + i) % capacity];
        }
        delete[] data;
        data = newData;
        front = 0;
        rear = size;
        capacity = newCapacity;
    }

public:
    Queue(int initialCapacity = 10)
        : capacity(initialCapacity), size(0), front(0), rear(0) {
        data = new T[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    void enqueue(const T& item) {
        if (size == capacity) {
            resize(capacity * 2); 
        }
        data[rear] = item;
        rear = (rear + 1) % capacity;
        ++size;
    }

    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        front = (front + 1) % capacity;
        --size;

        if (size > 0 && size == capacity / 4) {
            resize(capacity / 2);
        }
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return data[front];
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }
};

int main() {
    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    std::cout << "Front element: " << q.peek() << std::endl;

    q.dequeue();
    std::cout << "Front element after dequeue: " << q.peek() << std::endl;

    return 0;
}
