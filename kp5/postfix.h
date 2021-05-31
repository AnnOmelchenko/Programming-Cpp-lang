using namespace std;

#ifndef MAIN_CPP_POSTFIX_H
#define MAIN_CPP_POSTFIX_H


#define MAX_LEN 256

void push(char *_stack, int &_ptr, char data);
char pop(char *_stack, int &_ptr);
void PostfixNotation(const char *_infix, char *_postfix);

#endif //MAIN_CPP_POSTFIX_H
