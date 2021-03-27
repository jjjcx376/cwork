#include <stdio.h>
#include "util.h"
#include "book_management.h"
#include "user_management.h"
#include <string.h>
#include <stdlib.h>

int search_menu()
{
    int option;
    char *input;
    printf("Please choose an option:\n");
    printf("1) Find books by title\n");
    printf("2) Find books by author\n");
    printf("3) Find books by year\n");
    printf("4) Return to previous menu\n");
    printf(" Option: ");
    input = get_input();
    option = atoi(input);
    printf("\n");
    return option;
}

void search_ui()
{
    int option;
    char *title, *author, *input;
    unsigned year;
    BookArray result;
    do
    {
        option = search_menu();
        if (option < 1 || option > 4)
        {
            printf("Sorry, the option you entered was invalid, please try again.\n");
        }
        else if (option == 1)
        {
            printf("Please enter title: ");
            title = get_input();
            result = find_book_by_title(title);
            if (result.length != 0)
            {
                display_books(&result);
            }
            else
            {
                printf("Sorry, the book you searched is not in library\n");
            }
        }
        else if (option == 2)
        {
            printf("Please enter author: ");
            author = get_input();
            result = find_book_by_author(author);
            if (result.length != 0)
            {
                display_books(&result);
            }
            else
            {
                printf("Sorry, the book you searched is not in library\n");
            }
        }
        else if (option == 3)
        {
            printf("Please enter year: ");
            input = get_input();
            year = atoi(input);
            result = find_book_by_year(year);
            if (result.length != 0)
            {
                display_books(&result);
            }
            else
            {
                printf("Sorry, the book you searched is not in library\n");
            }
        }
        printf("\n");
    } while (option != 4);
    printf("Returning to previous menu...\n");
}

int user_menu()
{
    int option;
    char *input;
    printf("Please choose an option:\n");
    printf("1) Borrow a book\n");
    printf("2) Return a book\n");
    printf("3) Search for books\n");
    printf("4) Display all books\n");
    printf("5) Log out\n");
    printf(" Option: ");
    input = get_input();
    option = atoi(input);
    printf("\n");
    return option;
}

void user_ui(User *user)
{
    int option, code;
    char *input;
    unsigned id;
    unsigned i;
    printf("(logged in as: %s)\n", user->username);
    do
    {
        option = user_menu();
        if (option < 1 || option > 6)
        {
            printf("Sorry, the option you entered was invalid, please try again.\n");
        }
        else if (option == 1)
        {
            printf("Enter the ID number of the book you wish to borrow: ");
            input = get_input();
            id = atoi(input);
            code = user_borrow_book(user, id);
            if (code == -1)
            {
                printf("Sorry, you already have a copy of this book on load.\n");
                continue;
            }
            else if (code == 1)
            {
                printf("Sorry, you already borrowed too much books\n");
                continue;
            }
            code = borrow_book(id);
            if (code == 0)
            {
                printf("You have successfully borrowed the book!\n");
            }
            else if (code == 1)
            {
                user_return_book(user, id);
                printf("Sorry, no any book copy in library\n");
            }
            else if (code == -1)
            {
                user_return_book(user, id);
                printf("Sorry, no such a book in library\n");
            }
        }
        else if (option == 2)
        {
            if (user->borrow_length == 0)
            {
                printf("No books in your borrow list\n");
            }
            else
            {
                printf("Bolow is the list of Books you are currently borrowing:\n");
                display_borrows(user);
                printf("Enter the ID number of the book you wish to return: ");
                input = get_input();
                id = atoi(input);
                code = user_return_book(user, id);
                if (code == -1)
                {
                    printf("Sorry, no such a book in your borrow list\n");
                }
                else
                {
                    return_book(id);
                    printf("Returned book successfully.\n");
                }
            }
        }
        else if (option == 3)
        {
            printf("Loading search menu...\n");
            search_ui();
        }
        else if (option == 4)
        {
            display_books(&book_stock);
        }
    } while (option != 5);
    printf("Logging out...\n");
}

int librarian_menu()
{
    int option;
    char *input;
    printf("Please choose an option:\n");
    printf("1) Add a book\n");
    printf("2) Remove a book\n");
    printf("3) Search for books\n");
    printf("4) Display all books\n");
    printf("5) Log out\n");
    printf(" Option: ");
    input = get_input();
    option = atoi(input);
    printf("\n");
    return option;
}

void librarian_ui()
{
    int option;
    Book book;
    char *title, *author, *input;
    printf("(logged in as: librarian)\n");
    do
    {
        option = librarian_menu();
        if (option < 1 || option > 5)
        {
            printf("Sorry, the option you entered was invalid, please try again.\n");
        }
        else if (option == 1)
        {
            printf("Enter the title of the book you wish to add: ");
            title = get_input();
            printf("Enter the author of the book you wish to add: ");
            author = get_input();
            printf("Enter the year that the book you wish to add: ");
            input = get_input();
            book.year = atoi(input);
            printf("Enter the number of copies of the book you wish to add: ");
            input = get_input();
            book.copies = atoi(input);
            if (book.year == 0 || book.copies == 0)
            {
                printf("Sorry, you attempted to add an invlaid book, please try again.\n");
            }
            else
            {
                book.title = strdup(title);
                book.authors = strdup(author);
                add_book(book);
                printf("Book was successfully added!\n");
            }
        }
        else if (option == 2)
        {

            printf("Enter the id of the book you wish to remove: ");
            input = get_input();
            book.id = atoi(input);
            if (0 == remove_book(book))
            {
                printf("Book was successfully removed!\n");
            }
            else
            {
                printf("Sorry, no such a book in library\n");
            }
        }
        else if (option == 3)
        {
            printf("Loading search menu...\n");
            search_ui();
        }
        else if (option == 4)
        {
            display_books(&book_stock);
        }
        printf("\n");
    } while (option != 5);
    printf("Logging out...\n");
}

int main_menu()
{
    int option;
    char *input;
    printf("\n");
    printf("Please choose an option:\n");
    printf("1) Register an account\n");
    printf("2) Login\n");
    printf("3) Search for books\n");
    printf("4) Display all books\n");
    printf("5) Quit\n");
    printf(" Option: ");
    input = get_input();
    option = atoi(input);
    printf("\n");
    return option;
}

int main(int argc, char const *argv[])
{
    int option;
    char *username, *password;
    User *session;
    User user;
    FILE *output;
    init_database();
    init_users();
    do
    {
        option = main_menu();
        if (option < 1 || option > 5)
        {
            printf("Sorry, the option you entered was invalid, please try again.\n");
        }
        else if (option == 1)
        {
            printf("Please enter a username: ");
            username = get_input();
            printf("Please enter a password: ");
            password = get_input();
            if (find_user(username) != NULL)
            {
                printf("Sorry, registration unsuccessful, the username you entered already exists.\n");
            }
            else
            {
                user.username = strdup(username);
                user.password = strdup(password);
                user.borrow_length = 0;
                add_user(user);
                printf("Registered library account successfully!\n");                
            }
        }
        else if (option == 2)
        {
            printf("Please enter a username: ");
            username = get_input();
            printf("Please enter a password: ");
            password = get_input();
            if (strcmp(username, "librarian") == 0)
            {
                if (strcmp(password, "librarian") == 0)
                {
                    librarian_ui();
                }
                else
                {
                    printf("Sorry, login unsuccessful, the password you entered was wrong.\n");
                }
            }
            else
            {
                session = find_user(username);
                if (session == NULL)
                {
                    printf("Sorry, no user found.\n");
                }
                else if (strcmp(session->password, password) == 0)
                {
                    user_ui(session);
                }
                else
                {
                    printf("Sorry, login unsuccessful, the password you entered was wrong.\n");
                }
            }
        }
        else if (option == 3)
        {
            printf("Loading search menu...\n");
            search_ui();
        }
        else if (option == 4)
        {
            display_books(&book_stock);
        }
        printf("\n");
    } while (option != 5);
    printf("Thank you for using the library!\n");
    printf("Goodbye!\n");
    output = fopen("books.txt", "w");
    store_books(output);
    fclose(output);
    output = fopen("users.txt", "w");
    store_users(output);
    fclose(output);
    return 0;
}
