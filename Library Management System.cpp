#include <iostream>
#include <string>
#include <memory>
#include <limits> // 이 줄을 추가하세요

class Book {
public:
    int id;
    std::string title;
    std::string author;
    int price;
    std::string publisher;
    bool is_rented;
    std::shared_ptr<Book> next;

    Book(int id, const std::string& title, const std::string& author, int price, const std::string& publisher)
        : id(id), title(title), author(author), price(price), publisher(publisher), is_rented(false), next(nullptr) {}
};

class BookManager {
private:
    std::shared_ptr<Book> head;
    int book_count;

public:
    BookManager() : head(nullptr), book_count(0) {}

    void register_book();
    void display_books();
    void delete_book();
    void rent_book();
    void return_book();
};

int main() {
    BookManager manager;
    int choice;

    while (true) {
        std::cout << "\n도서관리 프로그램\n";
        std::cout << "1. 도서 등록\n2. 도서 출력\n3. 도서 삭제\n4. 도서 대여\n5. 도서 반납\n6. 종료\n선택하세요: ";
        std::cin >> choice;

        if (std::cin.fail()) { // 입력 오류 처리
            std::cin.clear(); // 오류 플래그 리셋
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기
            std::cout << "잘못된 입력입니다. 숫자를 입력하세요.\n";
            continue;
        }

        switch (choice) {
            case 1: manager.register_book(); break;
            case 2: manager.display_books(); break;
            case 3: manager.delete_book(); break;
            case 4: manager.rent_book(); break;
            case 5: manager.return_book(); break;
            case 6: std::cout << "프로그램을 종료합니다.\n"; return 0;
            default: std::cout << "잘못된 선택입니다. 다시 시도하세요.\n";
        }
    }
}

void BookManager::register_book() {
    std::string title, author, publisher;
    int price;

    std::cout << "도서 제목을 입력하세요: ";
    std::cin.ignore(); // 개행 문자 제거
    std::getline(std::cin, title);

    std::cout << "저자 이름을 입력하세요: ";
    std::getline(std::cin, author);

    std::cout << "도서 가격을 입력하세요: ";
    while (!(std::cin >> price)) { // 가격 입력 오류 처리
        std::cin.clear(); // 오류 플래그 리셋
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼 비우기
        std::cout << "잘못된 입력입니다. 다시 입력하세요: ";
    }

    std::cout << "출판사 이름을 입력하세요: ";
    std::cin.ignore(); // 개행 문자 제거
    std::getline(std::cin, publisher);

    auto new_book = std::make_shared<Book>(++book_count, title, author, price, publisher);
    new_book->next = head;
    head = new_book;

    std::cout << "도서가 등록되었습니다: ID " << new_book->id << ", 제목: " << new_book->title
              << ", 저자: " << new_book->author << ", 가격: " << new_book->price
              << ", 출판사: " << new_book->publisher << "\n";
}

void BookManager::display_books() {
    if (!head) {
        std::cout << "등록된 도서가 없습니다.\n";
        return;
    }

    std::cout << "\n등록된 도서 목록:\n";
    for (auto current = head; current; current = current->next) {
        std::cout << "ID: " << current->id << ", 제목: " << current->title
                  << ", 저자: " << current->author << ", 가격: " << current->price
                  << ", 출판사: " << current->publisher
                  << ", 대여 상태: " << (current->is_rented ? "대여됨" : "대여 안됨") << "\n";
    }
}

void BookManager::delete_book() {
    int id;
    std::cout << "삭제할 도서의 ID를 입력하세요: ";
    std::cin >> id;

    std::shared_ptr<Book> current = head, previous = nullptr;

    while (current && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (!current) {
        std::cout << "도서를 찾을 수 없습니다.\n";
        return;
    }

    if (!previous) head = current->next; // 헤드 삭제
    else previous->next = current->next; // 중간 노드 삭제

    std::cout << "도서가 삭제되었습니다: ID " << id << "\n";
}

void BookManager::rent_book() {
    int id;
    std::cout << "대여할 도서의 ID를 입력하세요: ";
    std::cin >> id;

    for (auto current = head; current; current = current->next) {
        if (current->id == id) {
            if (current->is_rented) {
                std::cout << "이 도서는 이미 대여되었습니다.\n";
            } else {
                current->is_rented = true;
                std::cout << "도서가 대여되었습니다: ID " << id << "\n";
            }
            return;
        }
    }
    std::cout << "도서를 찾을 수 없습니다.\n";
}

void BookManager::return_book() {
    int id;
    std::cout << "반납할 도서의 ID를 입력하세요: ";
    std::cin >> id;

    for (auto current = head; current; current = current->next) {
        if (current->id == id) {
            if (!current->is_rented) {
                std::cout << "이 도서는 대여되지 않았습니다.\n";
            } else {
                current->is_rented = false;
                std::cout << "도서가 반납되었습니다: ID " << id << "\n";
            }
            return;
        }
    }
    std::cout << "도서를 찾을 수 없습니다.\n";
}
