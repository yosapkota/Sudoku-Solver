#ifndef _STACK_H
#define _STACK_H

#include <stdexcept>

const int STACK_SIZE = 10;

template <typename StackType>
class Stack {
public:
    Stack(void) {
        data = new StackType[STACK_SIZE];
        count = 0;
        capacity = STACK_SIZE;
    }
    ~Stack(void) { delete[] data; }

    void clear(void) { count = 0; }
    int size(void) { return count; }
    bool isEmpty(void) { return count == 0; }

    void push(const StackType &d) {

        if (count == capacity) {
            int
                    tmpCap = 2 * capacity;
            StackType
                    *tmpData = new StackType[tmpCap];

            if (tmpData == nullptr) {
                throw std::overflow_error("Stack is full");
            }

            for (int i=0; i < capacity; i++) {
                tmpData[i] = data[i];
            }

            delete[] data;

            data = tmpData;
            capacity = tmpCap;

        }

        data[count] = d;

        count++;
    }

    StackType pop(void) {

        if (!count)
            throw std::underflow_error("Stack is empty");

        count--;

        return data[count];

    }

    StackType peek(void) {

        if (!count)
            throw std::underflow_error("Stack is empty");

        return data[count-1];
    }

private:
    StackType
    //data[STACK_SIZE];
    *data;
    int
            count,
            capacity;
};

#endif
