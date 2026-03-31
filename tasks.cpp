#include "tasks.h"
#include <iostream>
#include <fstream>
#include <string>

#include <iostream>
#include <fstream>

using namespace std;

struct Node2 {
    int data;
    Node2* next;
    Node2(int val) : data(val), next(nullptr) {}
};

void Zad1() {
    Node2* first = nullptr;
    Node2* last = nullptr;

    // Ввод данных
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    if (n <= 0) {
        cout << "Список пуст!" << endl;
        return;
    }

    cout << "Введите " << n << " элементов: ";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        Node2* Newnode2 = new Node2(val);

        if (!first) {
            first = Newnode2;
            last = Newnode2;
        } else {
            last->next = Newnode2;
            last = Newnode2;
        }
    }
    last->next = first; // замыкаем в кольцо

    // Обработка
    ofstream file("output.txt");
    Node2* curr = first;
    Node2* prev = last;

    cout << "\nОбработка..." << endl;

    int count = n;
    while (count > 0) {
        // Перемещаемся на 3 шага (чтобы сделать шаг 4)
        for (int i = 0; i < 3; i++) {
            prev = curr;
            curr = curr->next;
        }

        // Выводим в файл и на экран
        file << curr->data << " ";
        cout << "Удален: " << curr->data << endl;

        // Удаляем узел
        prev->next = curr->next;
        Node2* toDelete = curr;
        curr = curr->next;
        delete toDelete;

        count--;
    }

    file.close();
    cout << "\nРезультат сохранен в файл output.txt" << endl;
}

struct Node42 {
    int data;
    Node42* prev;
    Node42* next;
    Node42(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyCircularList42 {
private:
    Node42* first;

public:
    DoublyCircularList42() : first(nullptr) {}

    void add(int val) {
        Node42* newNode = new Node42(val);
        if (!first) {
            first = newNode;
            first->prev = first;
            first->next = first;
        } else {
            Node42* last = first->prev;
            last->next = newNode;
            newNode->prev = last;
            newNode->next = first;
            first->prev = newNode;
        }
    }

    Node42* removeSymmetricNeighbors() {
        if (!first) return nullptr;

        bool changed = true;
        while (changed) {
            changed = false;
            Node42* current = first;
            do {
                if (current->prev->data == current->next->data) {
                    Node42* toDelete = current;

                    if (current == first && current->next == first) {
                        delete current;
                        first = nullptr;
                        return nullptr;
                    } else if (current == first) {
                        first = current->next;
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                        current = current->next;
                    } else {
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                        current = current->next;
                    }

                    delete toDelete;
                    changed = true;

                    if (!first) return nullptr;
                    if (current == first) break;
                } else {
                    current = current->next;
                }
            } while (current != first);
        }

        return first ? first->prev : nullptr;
    }

    void print() {
        if (!first) {
            std::cout << "Список пуст" << std::endl;
            return;
        }
        Node42* temp = first;
        do {
            std::cout << temp->data << " ";
            temp = temp->next;
        } while (temp != first);
        std::cout << std::endl;
    }

    ~DoublyCircularList42() {
        if (!first) return;
        Node42* current = first;
        Node42* next;
        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != first);
    }
};

void Zad2() {
    DoublyCircularList42 list;
    int n, val;

    std::cout << "\n3 Задача 42 " << std::endl;
    std::cout << "Введите количество элементов списка: ";
    std::cin >> n;

    std::cout << "Введите элементы списка: ";
    for (int i = 0; i < n; i++) {
        std::cin >> val;
        list.add(val);
    }

    std::cout << "Исходный список: ";
    list.print();

    Node42* last = list.removeSymmetricNeighbors();

    std::cout << "Список после удаления: ";
    list.print();

    if (last) {
        std::cout << "Адрес последнего элемента: " << last << std::endl;
        std::cout << "Значение последнего элемента: " << last->data << std::endl;
    } else {
        std::cout << "Список пуст" << std::endl;
    }
}


struct TList {
    Node42* first;
    Node42* last;
    Node42* current;

    TList() : first(nullptr), last(nullptr), current(nullptr) {}
};

void ToFirst(TList& L) {
    L.current = L.first;
}

void ToNext(TList& L) {
    if (L.current && L.current->next != L.first) {
        L.current = L.current->next;
    }
}

void SetData(TList& L, int D) {
    if (L.current) {
        L.current->data = D;
    }
}

bool IsLast(const TList& L) {
    return L.current == L.last;
}

void Zad3() {
    TList L;
    int n, val;

    std::cout << "\n Задача 45 " << std::endl;
    std::cout << "Введите количество элементов списка: ";
    std::cin >> n;

    std::cout << "Введите элементы списка: ";
    for (int i = 0; i < n; i++) {
        std::cin >> val;
        Node42* newNode = new Node42(val);
        if (!L.first) {
            L.first = newNode;
            L.last = newNode;
            L.current = newNode;
        } else {
            L.last->next = newNode;
            newNode->prev = L.last;
            L.last = newNode;
        }
    }

    if (L.first) {
        L.last->next = L.first;
        L.first->prev = L.last;
    }

    std::cout << "Исходный список: ";
    Node42* temp = L.first;
    for (int i = 0; i < n; i++) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    ToFirst(L);
    int index = 1;
    while (true) {
        if (index % 2 == 1) {
            SetData(L, 0);
        }
        if (IsLast(L)) break;
        ToNext(L);
        index++;
    }

    std::cout << "Список после обработки: ";
    temp = L.first;
    for (int i = 0; i < n; i++) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    std::cout << "Количество элементов: " << n << std::endl;
    std::cout << "Адрес первого элемента: " << L.first << std::endl;
    std::cout << "Адрес последнего элемента: " << L.last << std::endl;

    L.current = L.last;
    std::cout << "Адрес текущего элемента: " << L.current << std::endl;
    std::cout << "Значение текущего элемента: " << L.current->data << std::endl;
}


struct TListB {
    Node42* barrier;
    Node42* current;

    TListB() : barrier(nullptr), current(nullptr) {}
};

void LBToFirst(TListB& L) {
    if (L.barrier && L.barrier->next != L.barrier) {
        L.current = L.barrier->next;
    }
}

void LBToNext(TListB& L) {
    if (L.current) {
        L.current = L.current->next;
    }
}

void LBSetData(TListB& L, int D) {
    if (L.current && L.current != L.barrier) {
        L.current->data = D;
    }
}

bool IsBarrier(const TListB& L) {
    return L.current == L.barrier;
}

void Zad4() {
    TListB L;
    int n, val;

    std::cout << "\n Задача 48 " << std::endl;
    std::cout << "Введите количество элементов списка: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Список пуст!" << std::endl;
        return;
    }

    L.barrier = new Node42(0);
    L.barrier->next = L.barrier;
    L.barrier->prev = L.barrier;
    L.current = L.barrier;

    std::cout << "Введите элементы списка: ";
    Node42* last = L.barrier;
    for (int i = 0; i < n; i++) {
        std::cin >> val;
        Node42* newNode = new Node42(val);
        newNode->prev = last;
        newNode->next = L.barrier;
        last->next = newNode;
        L.barrier->prev = newNode;
        last = newNode;
    }

    std::cout << "Исходный список: ";
    Node42* temp = L.barrier->next;
    for (int i = 0; i < n; i++) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    LBToFirst(L);
    int index = 1;
    while (!IsBarrier(L)) {
        if (index % 2 == 1) {
            LBSetData(L, 0);
        }
        LBToNext(L);
        index++;
    }

    std::cout << "Список после обработки: ";
    temp = L.barrier->next;
    for (int i = 0; i < n; i++) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;

    std::cout << "Количество элементов: " << n << std::endl;

    // Вывод адреса последнего элемента
    if (L.barrier && L.barrier->prev != L.barrier) {
        std::cout << "Адрес последнего элемента: " << L.barrier->prev << std::endl;
        std::cout << "Значение последнего элемента: " << L.barrier->prev->data << std::endl;
    }

    L.current = L.barrier;
    std::cout << "Адрес текущего элемента: " << L.current << " (барьерный элемент)" << std::endl;
}


struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularList {
private:
    Node* head;

public:
    CircularList() : head(nullptr) {}

    void add(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
            head->next = head;
        } else {
            Node* temp = head;
            while (temp->next != head)
                temp = temp->next;
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void findMaxNegativeSequence() {
        if (!head) {
            std::cout << "Список пуст" << std::endl;
            return;
        }

        // Находим размер списка
        int size = 0;
        Node* temp = head;
        do {
            size++;
            temp = temp->next;
        } while (temp != head);

        int maxLength = 0;
        int maxStartIndex = 0;

        // Проверяем все возможные начальные позиции
        for (int start = 0; start < size; start++) {
            int currentLength = 0;

            // Ищем последовательность отрицательных чисел
            for (int i = 0; i < size; i++) {
                int index = (start + i) % size;
                Node* current = head;
                for (int j = 0; j < index; j++) {
                    current = current->next;
                }

                if (current->data < 0) {
                    currentLength++;
                    if (currentLength > maxLength) {
                        maxLength = currentLength;
                        maxStartIndex = start;
                    }
                } else {
                    currentLength = 0;
                }
            }
        }

        // Выводим результат
        if (maxLength > 0) {
            std::cout << "Максимальная последовательность отрицательных элементов (длина " << maxLength << "): ";
            Node* current = head;
            for (int i = 0; i < maxStartIndex; i++) {
                current = current->next;
            }

            for (int i = 0; i < maxLength; i++) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        } else {
            std::cout << "Отрицательные элементы не найдены" << std::endl;
        }
    }

    void print() {
        if (!head) {
            std::cout << "Список пуст" << std::endl;
            return;
        }
        Node* temp = head;
        do {
            std::cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        std::cout << std::endl;
    }

    ~CircularList() {
        if (!head) return;
        Node* current = head;
        Node* next;
        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != head);
    }
};

void Zad5() {
    CircularList list;
    int n, val;

    std::cout << "\n Задача 3 " << std::endl;
    std::cout << "Введите количество элементов списка: ";
    std::cin >> n;

    std::cout << "Введите элементы списка: ";
    for (int i = 0; i < n; i++) {
        std::cin >> val;
        list.add(val);
    }

    std::cout << "Исходный список: ";
    list.print();

    list.findMaxNegativeSequence();
}