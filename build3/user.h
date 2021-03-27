#ifndef __USER_H__
#define __USER_H__

#define BORROW_LIST 10

typedef struct _User {
    char *username; //username
    char *password; //password
    unsigned int borrow_length; //number of borrows
    unsigned borrow_arr[BORROW_LIST]; //borrow array
}User;

void display_borrows(User* user);
int user_borrow_book(User* user, unsigned id);
int user_return_book(User* user, unsigned id);

#endif
