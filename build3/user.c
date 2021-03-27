#include "user.h"
#include "book_management.h"

void display_borrows(User* user)
{
    unsigned i;
    Book* book;
    printf("%-10s%-50s%-50s%-8s%s\n", "ID", "Title", "Authors", "year", "copies");
    for (i = 0;i < user->borrow_length; ++i)
    {
        book = find_book_by_id(user->borrow_arr[i]);
        if (book != NULL)
        {
            display_book(book);
        }
    }
}

int user_borrow_book(User* user, unsigned id)
{
    unsigned i;
    for (i = 0;i < user->borrow_length; ++i)
    {
        if (user->borrow_arr[i] == id)
        {
            return -1;
        }
    }
    if (user->borrow_length == BORROW_LIST)
    {
        return 1;
    }
    user->borrow_arr[user->borrow_length] = id;
    ++user->borrow_length;
    return 0;
}

int user_return_book(User* user, unsigned id)
{
    unsigned i;
    for (i = 0;i < user->borrow_length; ++i)
    {
        if (user->borrow_arr[i] == id)
        {
            for (;i < user->borrow_length - 1; ++i)
            {
                user->borrow_arr[i] = user->borrow_arr[i + 1];
                --user->borrow_length;
                return 0;
            }
        }
    }
    return -1;
}
