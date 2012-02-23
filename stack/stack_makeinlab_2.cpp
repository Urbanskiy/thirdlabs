#include <iostream>
#include <limits.h>

#define __ARGS_END__ INT_MAX

using namespace std;

typedef struct node
{
   int value;
   struct node * prev;

}TNode;

typedef struct Stack
{
    TNode * top;
}TStack;
//-------------------------------------------------------------
void Push(TStack * stack , int val, ... )
{
    TNode * temp;                       // make temp pointer to the top of stack
    int   * ptrArg = &val;              // ptrArg - pointer to first argument in func
    while((*ptrArg != __ARGS_END__ ) ){ // __ARGS_END__ macros that means end of argument list
        temp = stack->top;
        stack->top = new node;          // allocate new memory for PUSHED value and top pointer

        if(stack->top == NULL)                                      //*****************************
        {                                                           //
            cout << "Stack cannot allocate new memory" << endl;     // Check if not reach NULL ptr
        }                                                           //*****************************

        stack->top->value = *ptrArg;    // PUSH stack current argument in arg list
        stack->top->prev = temp;
        ptrArg++;                       // ptrArg -> next argument
    }
}
//-------------------------------------------------------------
int Pop(TStack * stack)
{
    try                                             //*********************************************
    {                                               //
        if(stack->top == NULL)                      //
        {                                           //
            throw "Error: Try to POP empty stack";  // Throw exception if trying to POP empty stack
        }                                           //
    }                                               //
    catch(const char * exc)                         //
    {                                               //
        cout << exc << endl;                        //
    }                                               //**********************************************

    TNode * temp;                       // make temp pointer to top
    int val;

    temp = stack->top;                  // initialize temp ptr
    val = temp->value;

    stack->top = stack->top->prev;      // top ptr to top->prev
    delete temp;                        // delete previous top
    cout << val << endl;

    return val;                         // return previous top value
}
//-------------------------------------------------------------
int Pop(TStack * stack, int amount)     // reloaded POP using to POP more then one element
{
    TNode * temp;                       // Already known pointer
    int val;

        while(amount-- && (stack->top != NULL)){ // pop amount times and check top equal NULL
            temp = stack->top;
            val = temp->value;

            stack->top = stack->top->prev;

            cout << temp->value << endl;
        }

    return 0;

}
//-------------------------------------------------------------
int Top(TStack * stack = NULL)      // I found a place to use default arg - yeah!
{
    // ******* check for mistakes *********
    try
    {
        if(stack == NULL)
        {
            throw "\n Argument of Top(TStack*) is empty or NULL";
        }
        else if(stack->top == NULL)
        {
            throw "\nCan't Top stack (stack is empty)";
        }
    }
    catch(const char * exc)     // catch mistakes
    {
        cout << exc << endl;    // print what happend
    }
    cout << stack->top->value << endl;      // print value of top stack
    return stack->top->value;               // return value of top stack(maybee need it)

}
//-------------------------------------------------------------
int main()
{
    TStack * myStack = new TStack;
    myStack->top = NULL;
    int (*tmpfunc)(TStack*);

    Push(myStack,0,__ARGS_END__);               // Push only one digit
    Push(myStack,1,2,3,4,5,__ARGS_END__);       // Push 1..5

    cout << "\nUsing Pop with 1 arg" << endl;
    Pop(myStack);           // Pop only last element (value = 5 in this example)
    cout << "Using Pop with N arg" << endl;
    Pop(myStack,3);         // Pop 3 last elements ( 4 3 2 )

    cout << "\nUsing normal TOP " << endl;
    Top(myStack);           // Top stack (1)
    cout << "Using TOP with mistake (no argument) " << endl;
    Top();

    /* ptr to func
    tmpfunc = &Top;
    (*tmpfunc)(myStack);
    tmpfunc = &Pop;
    (*tmpfunc)(myStack);
    (*tmpfunc)(myStack);
    */
   delete myStack;
   return 0;
}
