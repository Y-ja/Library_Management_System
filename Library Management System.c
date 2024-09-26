#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    int id; 
    char title[100]; 
    char author[100]; 
    int price; 
    char publisher[100]; 
    int is_rented; 
    struct Book* next; 
} Book;

Book* head = NULL;
int book_count = 0;

void register_book();
void display_books();
void delete_book();
void rent_book();
void return_book();

int main() {
    int choice;
    while (1) {
        printf("\n도서관리 프로그램\n");
        printf("1. 도서 등록\n2. 도서 출력\n3. 도서 삭제\n4. 도서 대여\n5. 도서 반납\n6. 종료\n선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: register_book(); break;
            case 2: display_books(); break;
            case 3: delete_book(); break;
            case 4: rent_book(); break;
            case 5: return_book(); break;
            case 6: printf("프로그램을 종료합니다.\n"); return 0;
            default: printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}

void register_book() {
    Book* new_book = (Book*)malloc(sizeof(Book));
    if (!new_book) {
        printf("메모리 할당 오류\n");
        return;
    }

    new_book->id = ++book_count;

    printf("도서 제목을 입력하세요: ");
    getchar();
    fgets(new_book->title, sizeof(new_book->title), stdin);
    new_book->title[strcspn(new_book->title, "\n")] = 0;

    printf("저자 이름을 입력하세요: ");
    fgets(new_book->author, sizeof(new_book->author), stdin);
    new_book->author[strcspn(new_book->author, "\n")] = 0;

    printf("도서 가격을 입력하세요: ");
    scanf("%d", &new_book->price);

    printf("출판사 이름을 입력하세요: ");
    getchar();
    fgets(new_book->publisher, sizeof(new_book->publisher), stdin);
    new_book->publisher[strcspn(new_book->publisher, "\n")] = 0;

    new_book->is_rented = 0;
    new_book->next = head;
    head = new_book;

    printf("도서가 등록되었습니다: ID %d, 제목: %s, 저자: %s, 가격: %d, 출판사: %s\n", 
           new_book->id, new_book->title, new_book->author, new_book->price, new_book->publisher);
}

void display_books() {
    if (!head) {
        printf("등록된 도서가 없습니다.\n");
        return;
    }

    printf("\n등록된 도서 목록:\n");
    for (Book* current = head; current; current = current->next) {
        printf("ID: %d, 제목: %s, 저자: %s, 가격: %d, 출판사: %s, 대여 상태: %s\n", 
               current->id, current->title, current->author, current->price, current->publisher, 
               current->is_rented ? "대여됨" : "대여 안됨");
    }
}

void delete_book() {
    int id;
    printf("삭제할 도서의 ID를 입력하세요: ");
    scanf("%d", &id);

    Book *current = head, *previous = NULL;

    while (current && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        printf("도서를 찾을 수 없습니다.\n");
        return;
    }

    if (!previous) head = current->next;
    else previous->next = current->next;

    free(current);
    printf("도서가 삭제되었습니다: ID %d\n", id);
}

void rent_book() {
    int id;
    printf("대여할 도서의 ID를 입력하세요: ");
    scanf("%d", &id);

    for (Book* current = head; current; current = current->next) {
        if (current->id == id) {
            if (current->is_rented) {
                printf("이 도서는 이미 대여되었습니다.\n");
            } else {
                current->is_rented = 1;
                printf("도서가 대여되었습니다: ID %d\n", id);
            }
            return;
        }
    }
    printf("도서를 찾을 수 없습니다.\n");
}

void return_book() {
    int id;
    printf("반납할 도서의 ID를 입력하세요: ");
    scanf("%d", &id);

    for (Book* current = head; current; current = current->next) {
        if (current->id == id) {
            if (!current->is_rented) {
                printf("이 도서는 대여되지 않았습니다.\n");
            } else {
                current->is_rented = 0;
                printf("도서가 반납되었습니다: ID %d\n", id);
            }
            return;
        }
    }
    printf("도서를 찾을 수 없습니다.\n");
}
