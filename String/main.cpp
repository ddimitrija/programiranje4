
#include <iostream>
#include <cstring>
using namespace std;

class SSOString {
    union {
        char local[14];
        char* heap;
    };

    short len;
    short cap;
    bool isLong;

public:
    SSOString() {
        local[0] = '\0';
        len = 0;
        cap = 14;
        isLong = false;
    }

    SSOString(const char* str) {
        if (str == nullptr) str = "";

        len = strlen(str);

        if (len < 14) {
            strcpy(local, str);
            cap = 14;
            isLong = false;
        }
        else {
            cap = len;
            heap = new char[cap + 1];
            strcpy(heap, str);
            isLong = true;
        }
    }

    SSOString(const SSOString& other) {
        len = other.len;
        cap = other.cap;
        isLong = other.isLong;

        if (isLong) {
            heap = new char[cap + 1];
            strcpy(heap, other.heap);
        }
        else {
            strcpy(local, other.local);
        }
    }

    ~SSOString() {
        if (isLong) {
            delete[] heap;
        }
    }

    SSOString& operator=(const SSOString& other) {
        if (this == &other) return *this;

        if (isLong) delete[] heap;

        len = other.len;
        cap = other.cap;
        isLong = other.isLong;

        if (isLong) {
            heap = new char[cap + 1];
            strcpy(heap, other.heap);
        }
        else {
            strcpy(local, other.local);
        }

        return *this;
    }

    char& operator[](short index) {
        if (isLong) return heap[index];
        return local[index];
    }

    short size() const {
        return len;
    }

    short capacity() const {
        return cap;
    }

    SSOString& operator+(const char* str) {
        if (str == nullptr || str[0] == '\0') return *this;

        short newSize = len + strlen(str);
        char* temp = new char[newSize + 1];

        if (isLong)
            strcpy(temp, heap);
        else
            strcpy(temp, local);

        strcat(temp, str);

        if (isLong)
            delete[] heap;

        if (newSize < 14) {
            strcpy(local, temp);
            cap = 14;
            isLong = false;
        }
        else {
            heap = temp;
            cap = newSize;
            isLong = true;
            temp = nullptr;
        }

        len = newSize;
        delete[] temp;

        return *this;
    }

    friend ostream& operator<<(ostream& out, const SSOString& str) {
        if (str.isLong)
            out << str.heap;
        else
            out << str.local;

        return out;
    }
};

int main() {
    SSOString a("hello");
    SSOString b("this is a longer string");

    cout << a << " " << a.size() << " " << a.capacity() << endl;
    cout << b << " " << b.size() << " " << b.capacity() << endl;

    a + " world";
    b + " and more text";

    cout << a << endl;
    cout << b << endl;

    SSOString c = b;
    cout << c << endl;

    SSOString d;
    d = a;
    cout << d << endl;

    d[0] = 'H';
    cout << d << endl;

    return 0;
}
