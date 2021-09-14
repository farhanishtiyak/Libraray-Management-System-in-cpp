#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
#include <string.h>
#include <fstream>
#include<stdio.h>
using namespace std;

class Book
{
public:
    char BookNumber[12];
    char BookName[100];
    char AuthorName[80];

    void CreateBook()
    {
        cout << "\nNew Book Entry...\n";
        cout << "\nEnter the book number: ";
        cin >> BookNumber;
        cout << "\nEnter the Book Name: ";
        fflush(stdin);
        gets(BookName);
        cout << "\nEnter the Author's Name: ";
        fflush(stdin);
        gets(AuthorName);
        cout << "\n\n\nBook Created....";
    }

    void ShowBook()
    {
        cout << "\nBook Number : " << BookNumber;
        cout << "\nBook Name : ";
        puts(BookName);
        cout << "\nAuthor Name : ";
        puts(AuthorName);
    }

    void ModifyBook()
    {
        cout << "\nBook Number : " << BookNumber;
        cout << "\nModified Book Nmae : ";
        fflush(stdin);
        gets(BookName);
        cout << "\nModified Author Name : ";
        fflush(stdin);
        gets(AuthorName);
    }

    char *ReturnBookNumber()
    {
        return BookNumber;
    }

    void Report()
    {
        cout << BookNumber << setw(30) << BookName << setw(30) << AuthorName << endl;
    }

}; // Book class ends here

class Student
{
    char RollNumber[12];
    char StudentName[80];
    char StudentBookNumber[12];
    int token;

public:
    void CreateStudent()
    {
        system("CLS");
        cout << "\nNew Student Entry....\n";
        cout << "\nEnter the Roll Number : ";
        cin >> RollNumber;

        cout << "\n\nEnter the student name : ";
        fflush(stdin);
        gets(StudentName);
        token = 0;
        StudentBookNumber[0] = '\0';
        cout << "\n\n Student Record Created....";
    }

    void ShowStudent()
    {
        cout << "\nRoll Number : " << RollNumber;
        cout << "\n    Student Name : ";
        puts(StudentName);
        cout << "\nNo of Book Issued : " << token;
        if (token == 1)
        {
            cout << "\nBook Number : " << StudentBookNumber;
        }
    }

    void ModifyStudent()
    {
        cout << "\nRoll Number : " << RollNumber;
        cout << "\nModified student Name : ";
        fflush(stdin);
        gets(StudentName);
    }

    char *ReturnRollNumber()
    {
        return RollNumber;
    }
    char *ReturnStudentBookNumber()
    {
        return StudentBookNumber;
    }

    int ReturnToken()
    {
        return token;
    }

    void AddToken()
    {
        token = 1;
    }
    void ResetToken()
    {
        token = 0;
    }

    void GetStudentBookNumber(char t[])
    {
        strcpy(StudentBookNumber, t);
    }

    void Report()
    {
        cout << "\t" << RollNumber << setw(20) << StudentName << setw(10) << token << endl;
    }

}; // Student class ends here

fstream fp, fp1;
Book bk;
Student st;

void WriteBook()
{
    char ch;
    fp.open("book.txt", ios::out | ios::app);
    do
    {
        system("CLS");
        bk.CreateBook();
        fp.write((char *)&bk, sizeof(Book));
        cout << "\n\n.....Do you want to add more record.....(y/n) : ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void WriteStudent()
{
    char ch;
    fp.open("student.txt", ios::out | ios::app);
    do
    {
        system("CLS");
        st.CreateStudent();
        fp.write((char *)&st, sizeof(Student));
        cout << "\n\n.....Do you want to add more record.....(y/n) : ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

void DisplaySpecificBook(char n[])
{
    cout << "\nBook Details...\n";
    int flag = 0;

    fp.open("book.txt", ios::in);

    while (fp.read((char *)&bk, sizeof(Book)))
    {
        if (strcmpi(bk.ReturnBookNumber(), n) == 0)
        {
            bk.ShowBook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\n\nBook Does not Exist...\n";
    }
    int ch = std::cin.get();

}

void DisplaySpecificStudent(char n[])
{
    cout << "\nStudent Details...\n";
    int flag = 0;

    fp.open("Student.txt", ios::in);

    while (fp.read((char *)&st, sizeof(Student)))
    {
        if (strcmpi(st.ReturnRollNumber(), n) == 0)
        {
            st.ShowStudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
    {
        cout << "\n\nStudent Does not Exist...\n";
    }
    int ch = std::cin.get();

}

void ModifyBook()
{
    char n[12];
    int found = 0;
    system("CLS");
    cout << "\n\nModified Book Record...\n";
    cout << "\nEnter the book number : ";
    cin >> n;

    fp.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&bk, sizeof(Book)) && found == 0)
    {
        if (strcmpi(bk.ReturnBookNumber(), n) == 0)
        {
            bk.ShowBook();
            cout << "\nEnter the new details of book...\n";
            bk.ModifyBook();

            int pos = -1 * sizeof(bk);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&bk, sizeof(Book));
            cout << "\n\n\tRecord Uptxted...\n";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRecord Not Found...\n";
    }
    int ch = std::cin.get();
}

void ModifyStudent()
{
    char n[12];
    int found = 0;
    system("CLS");
    cout << "\n\nModified Student Record...\n";
    cout << "\nEnter the Roll number : ";
    cin >> n;

    fp.open("student.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.ReturnRollNumber(), n) == 0)
        {
            st.ShowStudent();
            cout << "\nEnter the new details of student...\n";
            st.ModifyStudent();

            int pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&st, sizeof(Student));
            cout << "\n\n\tRecord Uptxted...\n";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
    {
        cout << "\n\nRecord Not Found...\n";
    }
    int ch = std::cin.get();
}

void DeleteStudent()
{
    char n[12];
    int flag = 0;
    system("CLS");
    cout << "\n\n\tDelete Student...";
    cout << "\n\n\nEnter the Roll Number : ";
    cin >> n;
    fp.open("student.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&st, sizeof(Student)))
    {
        if (strcmpi(st.ReturnRollNumber(), n) != 0)
        {
            fp2.write((char *)&st, sizeof(Student));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("student.txt");
    rename("temp.txt", "student.txt");
    if (flag == 1)
    {
        cout << "\n\n\tRecord Deleted...\n";
    }
    else
    {
        cout << "\n\n\tRecord not found...";
    }
    int ch = std::cin.get();
}

void DeleteBook()
{
    char n[12];
    int flag = 0;
    system("CLS");
    cout << "\n\n\tDelete Book...";
    cout << "\n\n\nEnter the Book Number : ";
    cin >> n;
    fp.open("book.txt", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.txt", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&bk, sizeof(Book)))
    {
        if (strcmpi(bk.ReturnBookNumber(), n) != 0)
        {
            fp2.write((char *)&bk, sizeof(Book));
        }
        else
        {
            flag = 1;
        }
    }
    fp2.close();
    fp.close();
    remove("book.txt");
    rename("Temp.txt", "book .txt");
    if (flag == 1)
    {
        cout << "\n\n\tRecord Deleted...\n";
    }
    else
    {
        cout << "\n\n\tRecord not found...";
    }
    int ch = std::cin.get();
}

void DisplayAllStudent()
{
    system("CLS");
    fp.open("student.txt", ios::in);
    if (!fp)
    {
        cout << "\nFile could not be open";
        int ch = std::cin.get();
        return;
    }
    cout << "\n\n\tStudent List\n\n";
    cout << "........................................................................\n";
    cout << "\tRoll_Number" << setw(10) << "  Student Name  " << setw(10) << "Book Issued\n";
    cout << "........................................................................\n";

    while (fp.read((char *)&st, sizeof(Student)))
    {
        st.Report();
    }
    fp.close();
    int ch = std::cin.get();
}

void DisplayAllBook()
{
    system("CLS");
    fp.open("book.txt", ios::in);
    // if (!fp)
    // {
    //     cout << "\nFile could not be open";
    //     int ch = std::cin.get();
    //     return;
    // }
    cout << "\n\n\tBook List\n\n";
    cout << "........................................................................\n";
    cout << "\tBook Number" << setw(10) << "  Book Name" << setw(20) << "Author name\n";
    cout << "........................................................................\n";

    while (fp.read((char *)&bk, sizeof(Book)))
    {
        bk.Report();
    }
    fp.close();
    int ch = std::cin.get();
}

void BookIssue()
{
    char StudentRoolNumber[12], BookNumber[12];
    int found = 0, flag = 0;
    system("CLS");
    cout << "\n\nBook Issue....";
    cout << "\n\n\tEnter The Student Roll Number : ";
    cin >> StudentRoolNumber;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.ReturnRollNumber(), StudentRoolNumber) == 0)
        {
            found = 1;
            if (st.ReturnToken() == 0)
            {
                cout << "\n\n\tEnter the Book Number : ";
                cin >> BookNumber;
                while (fp1.read((char *)&bk, sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(bk.ReturnBookNumber(), BookNumber) == 0)
                    {
                        flag = 1;
                        st.AddToken();
                        st.GetStudentBookNumber(bk.ReturnBookNumber());

                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(Student));
                        cout << "\n\n\t*****Book Issued succesfully\n\nPlease Note: Write the book issue txte in backside of your book and return book within 15 days, Fine Rs. 1 for each day after 15 days period.*****";
                    }
                }
                if (flag == 0)
                {
                    cout << "\n*****Book Number Does not exist.*****\n";
                }
            }
            else
            {
                cout << "\n*****You Haven't Returned The Last Book.*****";
            }
        }
    }
    if (found == 0)
    {
        cout << "\n*****Student record not exist*****";
    }
    fp.close();
    fp1.close();
    int ch = std::cin.get();
}

void BookDeposit()
{
    char StudentRoolNumber[12], BookNumber[12];
    int found = 0, flag = 0, day, fine;
    system("CLS");
    cout << "\n\nBook deposit....";
    cout << "\n\n\tEnter The Student Roll Number : ";
    cin >> StudentRoolNumber;
    fp.open("student.txt", ios::in | ios::out);
    fp1.open("book.txt", ios::in | ios::out);
    while (fp.read((char *)&st, sizeof(Student)) && found == 0)
    {
        if (strcmpi(st.ReturnRollNumber(), StudentRoolNumber) == 0)
        {
            found = 1;
            if (st.ReturnToken() == 0)
            {

                while (fp1.read((char *)&bk, sizeof(Book)) && flag == 0)
                {
                    if (strcmpi(bk.ReturnBookNumber(), st.ReturnStudentBookNumber()) == 0)
                    {
                        flag = 1;
                        bk.ShowBook();
                        cout << "\n\nEnter the total days after you deposited the book : ";
                        cin >> day;
                        if (day > 15)
                        {
                            fine = (day - 15) * 1;
                            cout << "\n\nYou have to paid fine Rs. " << fine;
                        }

                        st.ResetToken();

                        int pos = -1 * sizeof(st);
                        fp.seekg(pos, ios::cur);
                        fp.write((char *)&st, sizeof(Student));
                        cout << "\n\n\t*****Book Deposited Successfully*****";
                    }
                }
                if (flag == 0)
                {
                    cout << "\n*****Book Number Does not exist*****\n";
                }

                else
                {
                    cout << "\n*****No book is issued*****";
                }
            }
        }
        if (found == 0)
        {
            cout << "\n*****Student record not exist*****";
        }
        fp.close();
        fp1.close();
        int ch = std::cin.get();
    }
}

void start()
{
    system("CLS");

    cout << "****************LIBRARAY";

    cout << "  MANAGEMENT  ";

    cout << "SYSTEM****************";
    
}
void AdminMenu()
{
    system("CLS");
    int ch2;
    cout << "\n\n\n\t*****Administrator Menu*****";
    cout << "\n\n\n\t1. Create Or Write Student Record";
    cout << "\n\n\n\t2. Display All Student Record";
    cout << "\n\n\n\t3. Display Specific Student Record";
    cout << "\n\n\n\t4. Modify Student Record";
    cout << "\n\n\n\t5. Delete Student Record";
    cout << "\n\n\n\t6. Create Or Write Book";
    cout << "\n\n\n\t7. Display All Book";
    cout << "\n\n\n\t8. Display Specific Book";
    cout << "\n\n\n\t9. Modify Book Record";
    cout << "\n\n\n\t10. Delete Book Record";
    cout << "\n\n\n\t11. Back To Main Menu";
    cout << "\n\n\n\tPlease Enter your Choice (1-11):  ";

    cin >> ch2;
    switch (ch2)
    {
    case 1:
        WriteStudent();
        system("PAUSE");
        break;
    case 2:
        DisplayAllStudent();
        system("PAUSE");
        break;
    case 3:
        char num[12];
        system("CLS");
        cout << "\n\n\tPlease Enter the Roll Number: ";
        cin >> num;
        DisplaySpecificStudent(num);
        system("PAUSE");
        break;
    case 4:
        ModifyStudent();
        system("PAUSE");
        break;
    case 5:
        DeleteStudent();
        system("PAUSE");
        break;
    case 6:
        WriteBook();
        system("PAUSE");
        break;
    case 7:
        DisplayAllBook();
        system("PAUSE");
    case 8:
    {
        char num[12];
        system("CLS");
        cout << "\n\n\tPlease Enter the Book Number: ";
        cin >> num;
        DisplaySpecificBook(num);
        system("PAUSE");
        break;
    }
    case 9:
        ModifyBook();
        system("PAUSE");
        break;
    case 10:
        DeleteBook();
        system("PAUSE");
        break;
    case 11:
        return;

    default:
        cout << "Invalid Choice, Try Again...";
        break;
    }
    AdminMenu();
}

int main()
{
    char ch;
    start();

    do
    {
        
        cout << "\n\n\n\t*****Main Menu*****";
        cout << "\n\n\n\t1. Book Issue";
        cout << "\n\n\n\t2. Book Deposit";
        cout << "\n\n\n\t3. Administrator Menu";
        cout << "\n\n\n\t4. Exit";
        cout << "\n\n\tPlease Select Your Option (1-4): ";
        ch = getche();
        switch (ch)
        {
        case '1':
            BookIssue();
            break;
        case '2':
            BookDeposit();
            break;
        case '3':
            AdminMenu();
            break;
        case '4':
            exit(0);
            break;
        default:
            cout << "Invalid Choice";
            break;
        }

    } while (ch != 4);
    return 0;
}