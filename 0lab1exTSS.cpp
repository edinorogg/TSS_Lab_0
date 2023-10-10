#include <iostream>
#include <ctime>
using namespace std;

enum direction {
    clockwise,
    sizeerclockwise
};
template <typename T>
struct Node {
    T data;
    Node* next, * prev;
};

int josephus(int n, int k) {
    if (n == 1) {
        return 0; 
    }
    else {
       /* return (josephus(n - 1, k) + k - 1) % n + 1;*/
        int position = 0;
        for (int i = 1; i <= n; ++i) {
            position = (position + k) % i;
        }

        return position;
    }
}

int josephus_sizeerwise(int n, int k) {
    int newPos = 0;
    int prevPos = 0;
    if (n == 0) {
        return 1;
    }
    else {
         prevPos = josephus(n - 1, k); 
        newPos = (prevPos - k) % n;  
        if (newPos <= 0) {
            newPos += n;
        }
    }
    return newPos;

}

template<typename T>
class ringlist {
private:
    Node<T>* head, * tail;
    int size;
public:
    ringlist();
    ringlist(const ringlist<T>& l);
    ~ringlist();
    int getsize() { return size; };
    Node<T>* getElem(int);
    void clear();
    void delNode(Node<T>* node);
    void del(int pos);
    void insert(int pos);
    void addTail(T n);
    void addHead(T n);
    void GetList();
    void GetList(int pos);
    ringlist<T>& operator = (const ringlist<T>& l);
    Node<T>* getHead() const {
        return head;
    }

    Node<T>* getTail() const {
        return tail;
    }

};

template<typename T>
ringlist<T>::ringlist() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
ringlist<T>::ringlist(const ringlist<T>& l) {
    head = nullptr;
    tail = nullptr;
    size = 0;

    Node<T>* temp = l.head;

    do {
        addTail(temp->data);
        temp = temp->next;
    } while (temp != l.head);
}

template<typename T>
ringlist<T>::~ringlist<T>() {
    clear();
}

template<typename T>
void ringlist<T>::addHead(T n) {
    auto* temp = new Node<T>;

    if (size == 0) {
        temp->next = temp;
        temp->prev = temp;
        tail = temp;
        head = temp;
    }

    temp->prev = tail;
    temp->data = n;
    temp->next = head;
    tail->next = temp; //здесь немного странная реализация, попробую переписать

    if (head != nullptr) {
        head->prev = temp;
    }

    if (size != 0) {
        head = temp;
    }

    size++;
}

template<typename T>
void ringlist<T>::addTail(T n) {
    auto* temp = new Node<T>;

    if (size == 0) {
        temp->next = temp;
        temp->prev = temp;
        tail = temp;
        head = temp;
    }

    temp->next = head;
    temp->data = n;
    temp->prev = tail;
    head->prev = temp;

    if (tail != nullptr) {
        tail->next = temp;
    }

    if (size != 0) {
        tail = temp;
    }

    size++;
}

template<typename T>
void ringlist<T>::insert(int pos) {
    if (pos <  0 || pos > size - 1) {
        cout << "Incorrect position" << endl;
        return;
    }

    if (pos == size - 1) {
        T data;
        cout << "Input new data: ";
        cin >> data;
        addTail(data);
        return;
    }
    else if (pos == 0) {
        T data;
        cout << "Input new data: ";
        cin >> data;
        addHead(data);
        return;
    }

    int i = 0;

    Node<T>* Ins = head;

    while (i < pos) {
        Ins = Ins->next;
        i++;
    }

    Node<T>* prevIns = Ins->prev;

    auto* temp = new Node<T>;

    cout << "Input new data: ";
    cin >> temp->data;

    if (prevIns != nullptr && size != 1) {
        prevIns->next = temp;
    }

    temp->next = Ins;
    temp->prev = prevIns;
    Ins->prev = temp;

    size++;
}

template<typename T>
void ringlist<T>::delNode(Node<T>* node) {
    Node<T>* next, * prev;
    prev = node->prev;
    next = node->next;
    if (prev != nullptr && size != 1) {
        prev->next = node->next;
    }
    if (next != nullptr && size != 1) {
        next->prev = node->prev;
    }

    if (head == node) {
        head = next;
    }
    if (tail == node) {
        tail = prev;
    }

    delete node;
    size--;
}

template<typename T>
void ringlist<T>::del(int pos) {

    if (pos < 0 || pos > size - 1)
    {
        cout << "Incorrect position \n";
        return;
    }

    int i = 0;

    Node<T>* del = head;

    while (i < pos) {
        del = del->next;
        i++;
    }

    Node<T>* prevDel = del->prev;
    Node<T>* afterDel = del->next;

    if (prevDel != nullptr && size != 1) {
        prevDel->next = afterDel;
    }
    if (afterDel != nullptr && size != 1) {
        afterDel->prev = prevDel;
    }

    if (pos == 0) {
        head = afterDel;
    }
    if (pos == size - 1) {
        tail = prevDel;
    }

    delete del;
    size--;
}
template<typename T>
void ringlist<T>::GetList() {
    if (size != 0) {
        Node<T>* temp = head;
        cout << "( ";
        while (temp->next != head) {
            cout << temp->data << ", ";
            temp = temp->next;
        }

        cout << temp->data << " )\n";
    }
}

template<typename T>
void ringlist<T>::clear() {
    while (size != 0) {
        del(0);
    }
}
template<typename T>
Node<T>* ringlist<T>::getElem(int pos) {
    Node<T>* temp = head;

    if (pos < 0 || pos > size - 1) {
        cout << "Неправильно определена позиция" << endl;
        return nullptr;
    }

    int i = 0;

    while (i < pos && temp != nullptr) {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr) {
        return nullptr;
    }
    else {
        return temp;
    }
}

template<typename T>
ringlist<T>& ringlist<T>::operator = (const ringlist<T>& l) {
    if (this == &l) {
        return *this;
    }

    this->~ringlist<T>();

    Node<T>* temp = l.head;

    do {
        addTail(temp->data);
        temp = temp->next;
    } while (temp != l.head);

    return *this;
}

template<typename T>
pair<int, T>Problem_Solution_For_ClockWise(ringlist<T> input, unsigned step) {
    if (step == 1) {
        int lastIdx = input.getsize() - 1;
        return make_pair(lastIdx, input.getElem(lastIdx)->data);
    }
    int pos = josephus(input.getsize(), step);
    Node<T>* front, *back;
    front = input.getHead();
    back = input.getHead();
    while (input.getsize() > 1) {
        for (int i = 1; i < step; i++) {
            back = front;
                front = front->next;

        }
        input.delNode(front);
        front = back->next;
    }
    return make_pair(pos, front->data);
}
template<typename T>
pair<int, T>Problem_Solution_For_sizeerWise(ringlist<T> input, unsigned step) {
    if (step == 1) {
                    return make_pair(0, input.getElem(0)->data);
                }
    int pos = josephus_sizeerwise(input.getsize(), step);
    Node<T>* front, * back;
    front = input.getTail();
    back = input.getTail();
        while (input.getsize() > 1) {
            for (int i = 1; i < step; i++) {
                back = front;
                front = front->prev;
            }
            input.delNode(front);
            front = back->prev;
        }
        return make_pair(pos, front->data);
};
template<typename T>
pair<int, T> Problem_Solution(ringlist<T> input, direction dir, unsigned step) {
    if (step == 0) {
        throw (string)("Шаг не может быть равен 0");
    }

    if (dir == clockwise) {
        return (Problem_Solution_For_ClockWise(input, step));
    }
    else if (dir == sizeerclockwise) {
        return (Problem_Solution_For_sizeerWise(input, step));
    }
    else {
        // Обработка других возможных значений dir
        throw invalid_argument("Неправильное направление: " + dir);
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(static_cast<unsigned int>(time(nullptr)));
    int size = 0, step = 0;
    cout << "Укажите количество элементов: ";
    cin >> size;
    cout << "Укажите шаг: ";
    cin >> step;

    auto input = new ringlist<int>;
    for (size_t i = 0; i < size; i++) {
        input->addTail(rand()%101);
    }

    try {
        auto pairClockWise = Problem_Solution(*input, clockwise, step);
        cout << "Направление по часовой стрелке: " << pairClockWise.first << ' ' << pairClockWise.second << endl;

        auto paircounterClockWise = Problem_Solution(*input, sizeerclockwise, step);
        cout << "Против часовой стрелки: " << paircounterClockWise.first << ' ' << paircounterClockWise.second << endl;
    }
    catch (string error) {
        cout << error << endl;
    }


    return 0;
}






