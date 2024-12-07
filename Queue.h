#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class QueueNode
{
public:
    T data;
    QueueNode<T> *next;

    QueueNode(T data) : data(data), next(nullptr) {}
};

template <typename T>
class Queue
{
private:
    QueueNode<T> *frontNode;
    QueueNode<T> *rearNode;
    int size;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), size(0) {}

    ~Queue()
    {
        while (!empty())
        {
            dequeue();
        }
    }

    void enqueue(T data)
    {
        QueueNode<T> *newNode = new QueueNode<T>(data);
        if (rearNode != nullptr)
        {
            rearNode->next = newNode;
        }
        rearNode = newNode;
        if (frontNode == nullptr)
        {
            frontNode = newNode;
        }
        size++;
    }

    void dequeue()
    {
        if (empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        QueueNode<T> *temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr)
        {
            rearNode = nullptr;
        }
        delete temp;
        size--;
    }

    T front() const
    {
        if (empty())
        {
            throw std::runtime_error("Queue is empty");
        }
        return frontNode->data;
    }

    bool empty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }
};

#endif