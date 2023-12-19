#include <stdio.h>
#include <stdbool.h>

// Структура узла списка
struct Node {
    int key;
    int value;
    struct Node* next;
};

// Функция поиска значения по ключу в списке
int search(struct Node* head, int key) {
    struct Node* current = head;
    
    // Проходим по списку и ищем узел с заданным ключом
    while (current != NULL) {
        if (current->key == key) {
            return current->value; // Возвращаем значение, если ключ найден
        }
        current = current->next;
    }
    
    // Если ключ не найден, возвращаем -1
    return -1;
}

int main() {
    // Создание списка для тестирования
    struct Node node1 = {1, 10, NULL};
    struct Node node2 = {2, 20, NULL};
    struct Node node3 = {3, 30, NULL};
    struct Node node4 = {4, 40, NULL};
    
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    
    // Поиск значения по ключу
    int key = 3;
    int value = search(&node1, key);
    
    if (value != -1) {
        printf("Значение по ключу %d: %d\n", key, value);
    } else {
        printf("Ключ %d не найден\n", key);
    }
    
    return 0;
}