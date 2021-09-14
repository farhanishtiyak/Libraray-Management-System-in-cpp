#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;
class Book
{
public:
    int id;
    string name, writer, type;
    bool available;
    string getAvailability()
    {
        if (available)
            return "YES";
        else
            return "NO";
    }
    Book(int id, const string &name, const string &writer, const string &type, bool available) : id(id), name(name), writer(writer), type(type), available(available) {}
};
class Student
{
public:
    string roll, className, name;
    Student(const string &roll, const string &className, const string &name) : roll(roll), className(className),
                                                                               name(name) {}
};
class Date
{
public:
    int year, month, day;
    string getDate()
    {
        return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
    }
    Date(int day, int month, int year) : day(day), month(month), year(year) {}
};
class BorrowBook
{
public:
    int id;
    Date issueDate, expectedReturnDate;
    Book givenBook;
    Student student;
    BorrowBook(int id, const Date &issueDate, const Date &expectedReturnDate, const Book &givenBook,
               const Student &student) : id(id), issueDate(issueDate), expectedReturnDate(expectedReturnDate),
                                         givenBook(givenBook), student(student) {}
};
class Library
{
public:
    vector<Book> allBooks;
    vector<BorrowBook> allBorrowedBooks;
    void initBooksList()
    {
        Book b1 = Book(0, "The Alchemist", "Paulo Coelho", "Novel", true);
        Book b2 = Book(1, "Da Vinci Code", "Brown, Dan", "Crime", true);
        Book b3 = Book(2, "Harry Potter", "J.K. Rowling", "Fiction", true);
        Book b4 = Book(3, "New Moon", "Stephenie", "Fiction", true);
        allBooks.push_back(b1);
        allBooks.push_back(b2);
        allBooks.push_back(b3);
        allBooks.push_back(b4);
    }
    void printAllBooks()
    {
        int i = 0;
        cout << "\tID"
             << "\tName"
             << "\t\tWriter Name"
             << "\tType"
             << "\t\tAvailable" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        for (Book b : allBooks)
        {
            cout << "\t" << i << "\t" << b.name << "\t" << b.writer << "\t" << b.type << "\t\t"
                 << b.getAvailability() << endl;
            i++;
        }
    }
    void printAllAvailableBooks()
    {
        int i = 0;
        cout << "\tID"
             << "\tName"
             << "\t\tWriter Name"
             << "\tType"
             << "\t\tAvailable" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        for (Book b : allBooks)
        {
            if (b.available)
                cout << "\t" << i << "\t" << b.name << "\t" << b.writer << "\t" << b.type << "\t\t"
                     << b.getAvailability() << endl;
            i++;
        }
    }
    void insertBook()
    {
        string name, writer, type;
        cout << "Book Name:";
        cin.ignore();
        getline(cin, name);
        cout << "Writer Name:";
        getline(cin, writer);
        cout << "Book Type:";
        cin >> type;
        Book newBook = Book(allBooks.size() + 1, name, writer, type, true);
        allBooks.push_back(newBook);
        cout << "Insertion Done! New Books list:" << endl;
        printAllAvailableBooks();
    }
    void deleteBook()
    {
        int id;
        cout << "Enter the ID of the Book that you want to delete:" << endl;
        printAllAvailableBooks();
        cin >> id;
        allBooks.erase(allBooks.begin() + id);
        cout << "Deletion Done! New Books list:" << endl;
        printAllAvailableBooks();
    }
    void modify(Book b, string type)
    {
        string s;
        if (type == "Name")
        {
            cout << "Current Name " << b.name << endl;
            cout << "Enter update Name: ";
            cin.ignore();
            getline(cin, s);
            b.name = s;
        }
        else if (type == "Writer")
        {
            cout << "Current Writer Name " << b.writer << endl;
            cout << "Enter update Writer Name: ";
            cin.ignore();
            getline(cin, s);
            b.writer = s;
        }
        else if (type == "Type")
        {
            cout << "Current Type " << b.type << endl;
            cout << "Enter update Type:";
            cin >> s;
            b.type = s;
        }
        allBooks[b.id] = b;
        cout << "Modify done! Updated Books List: " << endl;
        printAllAvailableBooks();
    }
    void modifyBook()
    {
        int id, option;
        cout << "Enter the ID of the Book that you want to Modify:" << endl;
        printAllAvailableBooks();
        cout << "Enter Book ID:";
        cin >> id;
        Book b = allBooks.at(id);
        cout << "Enter what you want to modify of " << b.name << " : " << endl;
        cout << "    For Name type 1" << endl;
        cout << "    For Writer Name type 2" << endl;
        cout << "    For Writer Name type 3" << endl;
        cin >> option;
        if (option == 1)
            modify(b, "Name");
        else if (option == 2)
            modify(b, "Writer");
        else if (option == 3)
            modify(b, "Type");
    }
    void printAllBorrowedBooks()
    {
        if (allBooks.size() == 0)
        {
            cout << "No book borrowed yet!. Borrow a Book first" << endl;
            return;
        }
        else
        {
            cout << "\tID"
                 << "\tName"
                 << "\t\tWriter Name"
                 << "\tType"
                 << "\t\tavailable" << endl;
            for (Book b : allBooks)
            {
                if (!b.available)
                {
                    cout << "\t" << b.id << "\t" << b.name << "\t" << b.writer << "\t" << b.type << "\t\t"
                         << b.getAvailability() << endl;
                }
            }
        }
    }
    void borrowToStudent()
    {
        int id, daysCount;
        string name, roll, className;
        Date issueDate = currentDate();
        cout << "Enter the ID of the Book that you want to Borrow: " << endl;
        printAllAvailableBooks();
        cout << "Enter Book ID:";
        cin >> id;
        Book givenBook = allBooks.at(id);
        cout << "Enter the Student info who want the book: " << endl;
        cout << "    Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "    Enter Roll: ";
        cin >> roll;
        cout << "    Enter Class: ";
        cin >> className;
        cout << "Enter, 'How many days for': ";
        cin >> daysCount;
        Student toWhom = Student(roll, className, name);
        int years = (int)(daysCount / 365);
        int days = (int)((daysCount) % 365);
        int months = days / 30;
        days = days % 30;
        Date expectedReturnDate = Date(issueDate.day + days, issueDate.month + months, issueDate.year + years);
        BorrowBook newBorrow = BorrowBook(allBorrowedBooks.size(), issueDate, expectedReturnDate, givenBook, toWhom);
        allBorrowedBooks.push_back(newBorrow);
        makeBookAvailable(false, givenBook.id);
        cout << "Borrowed done! All Borrows list:" << endl;
        printAllBorrows();
    }
    void printAllBorrows()
    {
        if (allBorrowedBooks.size() == 0)
        {
            cout << "No book borrowed yet!. Borrow a Book first by clicking option '6'" << endl;
            return;
        }
        else
        {
            cout << "\tID"
                 << "\tRoll"
                 << "\tStudent Name"
                 << "\tClass"
                 << "\tBook Name"
                 << "\tWriter Name"
                 << "\tBorrowed Date"
                 << "\tExpected Return Date" << endl;
            cout << "---------------------------------------------------------------------------------------"
                 << "---------------------------" << endl;
            for (BorrowBook borrowBook : allBorrowedBooks)
            {
                Student student = borrowBook.student;
                cout << "\t" << borrowBook.id << "\t" << student.roll << "\t" << student.name << "\t"
                     << student.className
                     << "\t" << borrowBook.givenBook.name << "\t" << borrowBook.givenBook.writer << "\t"
                     << borrowBook.issueDate.getDate() << "\t" << borrowBook.expectedReturnDate.getDate() << endl;
            }
        }
    }
    void makeBookAvailable(bool available, int bookId)
    {
        Book returningBook = allBooks.at(bookId);
        returningBook.available = available;
        allBooks.at(returningBook.id) = returningBook;
    }
    void returnBook()
    {
        int id;
        cout << "Enter the ID of the Borrow that you want to Return: " << endl;
        printAllBorrows();
        cout << "Enter ID: ";
        cin >> id;
        makeBookAvailable(true, allBorrowedBooks.at(id).givenBook.id);
        allBorrowedBooks.erase(allBorrowedBooks.begin() + id);
        cout << "Return Done! " << endl;
        printAllAvailableBooks();
    }
    const Date currentDate()
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        return Date(tm.tm_mday, tm.tm_mon, tm.tm_year + 1900);
    }
    void printBook(Book b)
    {
        cout << "\tID"
             << "\tName"
             << "\t\tWriter Name"
             << "\tType"
             << "\t\tavailable" << endl;
        cout << "---------------------------------------------------------------------------------" << endl;
        cout << "\t" << b.id << "\t" << b.name << "\t" << b.writer << "\t" << b.type << "\t\t" << b.getAvailability() << endl;
    }
    void searchBook()
    {
        string str;
        cout << "Enter Book name to search: ";
        cin.ignore();
        getline(cin, str);
        int count = 0;
        string t = str;
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        for (Book b : allBooks)
        {
            string check = b.name;
            transform(check.begin(), check.end(), check.begin(), ::tolower);
            if (check == t)
            {
                count++;
                printBook(b);
                break;
            }
        }
        if (count == 0)
            cout << "No book found named " << str << endl;
    }
};

int main()
{
    Library library;
    library.initBooksList();
    int choice;
    while (1)
    {
        system("cls");
        cout << "----------------------------------------------------------" << endl;
        cout << "----------------Library Management System-----------------" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "Please chose an option: \n";
        cout << "\t1. Show All Books \t\n";
        cout << "\t2. Search Book \t\n";
        cout << "\t3. Add New Book \t\n";
        cout << "\t4. Modify a Book \t\n";
        cout << "\t5. Delete a Book \t\n";
        cout << "\t6. Borrow Book to a Student \t\n";
        cout << "\t7. All Borrow List \t\n";
        cout << "\t8. Borrowed Books List \t\n";
        cout << "\t9. Return Book to Library \t\n";
        cout << "\t10. Exit the Program \t\n";

        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            library.printAllBooks();
            system("PAUSE");
            break;
        case 2:
            library.searchBook();
            system("PAUSE");
            break;
        case 3:
            library.insertBook();
            system("PAUSE");
            break;
        case 4:
            library.modifyBook();
            system("PAUSE");
            break;
        case 5:
            library.deleteBook();
            system("PAUSE");
            break;
        case 6:
            library.borrowToStudent();
            system("PAUSE");
            break;
        case 7:
            library.printAllBorrows();
            system("PAUSE");
            break;
        case 8:
            library.printAllBorrowedBooks();
            system("PAUSE");
            break;
        case 9:
            library.returnBook();
            system("PAUSE");
            break;
        case 10:
            exit(0);
            break;
        default:
            cout << "You enter invalid input\nre-enter the input\n"
                 << endl;
            break;
        }
    }
    return 0;
}