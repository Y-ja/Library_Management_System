# 📚 Library Management System in C

## 이 도서 관리 프로그램은 도서관의 도서를 등록하고 관리하기 위한 시스템입니다.
## 기능 🛠️

1. 도서 등록 📖: 새로운 도서를 등록합니다. 도서의 제목, 저자, 가격, 출판사 및 대여 상태를 입력받습니다.
2. 도서 출력 📜: 현재 등록된 도서 목록을 출력합니다. 각 도서의 ID, 제목, 저자, 가격, 출판사 및 대여 상태를 표시합니다.
3. 도서 삭제 ❌: 특정 ID를 가진 도서를 삭제합니다.
4. 도서 대여 🏠: 대여할 도서의 ID를 입력받아 도서를 대여합니다. 이미 대여된 도서는 대여할 수 없습니다.
5. 도서 반납 🔄: 대여 중인 도서를 반납합니다. 반납되지 않은 도서는 반납할 수 없습니다.

## 1. 구조체 정의 및 전역 변수 📊
```
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
```

- Book 구조체: 도서의 정보를 저장하는 구조체입니다.
```
    id: 도서의 고유 ID.
    title, author, publisher: 도서의 제목, 저자, 출판사.
    price: 도서 가격.
    is_rented: 대여 상태 (0: 대여 안됨, 1: 대여됨).
    next: 다음 도서를 가리키는 포인터.
    head: 도서 목록의 시작을 가리키는 포인터.
    book_count: 등록된 도서의 수를 기록합니다.
```

## 2. 메인 함수 및 메뉴 시스템 📋
```
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

```

- 메뉴 출력: 사용자가 선택할 수 있는 메뉴를 출력합니다.
- 사용자 입력 처리: 사용자가 입력한 선택에 따라 해당 기능을 호출합니다.
- 무한 루프: 프로그램이 종료될 때까지 계속해서 메뉴를 보여줍니다.

## 3. 도서 등록 함수 📖

```
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

```

- 메모리 할당: malloc을 사용하여 새로운 도서 객체를 생성합니다.
- 도서 정보 입력: 사용자에게 제목, 저자, 가격, 출판사를 입력받습니다.
- 대여 상태 초기화: 새로운 도서는 대여되지 않은 상태로 초기화합니다.
- 연결 리스트에 추가: 새로운 도서를 리스트의 앞에 추가합니다.

## 4. 도서 출력 함수 📜

```
void display_books() {
    if (!head) {
        printf("등록된 도서가 없습니다.\n"); // 도서가 없을 경우
        return;
    }

    printf("\n등록된 도서 목록:\n");
    for (Book* current = head; current; current = current->next) {
        // 도서 정보 출력
        printf("ID: %d, 제목: %s, 저자: %s, 가격: %d, 출판사: %s, 대여 상태: %s\n", 
               current->id, current->title, current->author, current->price, current->publisher, 
               current->is_rented ? "대여됨" : "대여 안됨");
    }
}

```

- 도서 목록 출력: 등록된 도서의 정보를 출력합니다.
- 비어있는 리스트 확인: 도서가 없으면 메시지를 표시합니다.

## 5. 도서 삭제 함수 ❌
```
void delete_book() {
    int id;
    printf("삭제할 도서의 ID를 입력하세요: ");
    scanf("%d", &id);

    Book *current = head, *previous = NULL;

    // 📖 도서 찾기
    while (current && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        printf("도서를 찾을 수 없습니다.\n"); // 📭 도서가 없을 경우
        return;
    }

    // 📑 도서 삭제
    if (!previous) head = current->next;
    else previous->next = current->next;

    free(current); // 💻 메모리 해제
    printf("도서가 삭제되었습니다: ID %d\n", id);
}
```

- ID 입력: 삭제할 도서의 ID를 입력받습니다.
- 도서 찾기 및 삭제: 도서를 찾고, 리스트에서 제거한 후 메모리를 해제합니다.

## 6. 도서 대여 및 반납 함수 🏠🔄
- 대여 함수
```
void rent_book() {
    int id;
    printf("대여할 도서의 ID를 입력하세요: ");
    scanf("%d", &id);

    for (Book* current = head; current; current = current->next) {
        if (current->id == id) {
            if (current->is_rented) {
                printf("이 도서는 이미 대여되었습니다.\n"); //이미 대여된 도서
            } else {
                current->is_rented = 1; //  대여 상태 변경
                printf("도서가 대여되었습니다: ID %d\n", id);
            }
            return;
        }
    }
    printf("도서를 찾을 수 없습니다.\n"); //  도서가 없을 경우
}

```
- 반납 함수
```
void return_book() {
    int id;
    printf("반납할 도서의 ID를 입력하세요: ");
    scanf("%d", &id);

    for (Book* current = head; current; current = current->next) {
        if (current->id == id) {
            if (!current->is_rented) {
                printf("이 도서는 대여되지 않았습니다.\n"); //  대여되지 않은 도서
            } else {
                current->is_rented = 0; //  대여 상태 변경
                printf("도서가 반납되었습니다: ID %d\n", id);
            }
            return;
        }
    }
    printf("도서를 찾을 수 없습니다.\n"); //  도서가 없을 경우
}

```

- 대여 및 반납: 입력한 ID에 해당하는 도서를 대여하거나 반납합니다.
- 상태 확인: 도서의 대여 상태에 따라 적절한 메시지를 출력합니다.