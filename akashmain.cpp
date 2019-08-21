#include <iostream>
using namespace std;
int submain()
{
	cout<<"\n       Akash Verma\n";
	cout<<"     RA1811029010047\n";
}
struct node {
    char data;
    node *next;
};
class list
{
private:
    node *top;
public:
    list() { top=NULL; }
    ~list() { while (!isEmpty()) {
            pop();
        }
    }
    char peek();
    bool isEmpty();
    void push(char new_data);
    char pop();
};
bool list::isEmpty() {
    return (top==NULL);
}
char list::peek() {
    if (!isEmpty()) {
        char value = top->data;
        return value;
    } else {
        cout << "Stack is empty!!" << endl;
        exit(1);
    }
}
void list::push(char new_data) {
    node *temp = new node;
    temp->data=new_data;
    temp->next=top;
    top=temp;
}
char list::pop() {
    if (!isEmpty()) {
        char value=top->data;
        node *oldtop = top;
        top=top->next;
        delete oldtop;
        return value;
    } else {
        cout << "You cannot pop an empty stack!" << endl;
        exit(1);
    }
}
int prec(char c)
{
    if(c == '^')
        return 3;
    else if(c == '*' || c == '/')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else if(c=='#')
        return -2;
    else
        return -1;
}
bool isOperand(char s) {
    return (s>='a'&&s<='z'||s>='A'&&s<='Z');
}
bool isOperator(char s) {
    return (s=='+'||s=='/'||s=='-'||s=='*'||s=='^');
}
bool isValidChar (char s) {
    return (isOperator(s)||isOperand(s)||s=='('||s==')');
}
bool isValidInfix (string s) {
    int l = s.length();
    for(int i=0;i<l;i++) {
        if (!isValidChar(s[i])) {
            return false;
            break;
        }
    }
}
void infixToPrefix(string s)
{
    list *input = new list;
    int l = s.length();
    string init;
    for(int i=0;i<l;i++) {
        input->push(s[i]);
    }
    list *output = new list;
    list *oper = new list;
    while(!input->isEmpty()) {
        char val = input->pop();
        if (isOperand(val)) {
            output->push(val);
        } else if (val==')') {
            oper->push(val);
        } else if(isOperator(val)) {
            bool pushed=false;
            while(!pushed) {
                if (oper->isEmpty()||oper->peek()==')'||prec(val)>=prec(oper->peek())) {
                    oper->push(val);
                    pushed=true;
                } else {
                    output->push(oper->pop());
                }
            }
        } else if (val=='(') {
            while (oper->peek()!=')') {
                output->push(oper->pop());
            }
            oper->pop();
        }
    }
    while(!oper->isEmpty()) {
        output->push(oper->pop());
    }
    while (!output->isEmpty()) {
        init+=output->pop();
    }
    cout << "Prefix notation: " << init << endl;
    delete input;
}
void infixToPostfix(string s)
{
    list *input = new list;
    int l = s.length();
    string ns;
    for(int i = 0; i < l; i++)
    {
        if (isOperand(s[i])) {
            ns+=s[i];
        }
        else if(s[i] == '(') {
            input->push('(');
        }
        else if(s[i] == ')')
        {
            while(!input->isEmpty()&&input->peek()!='(')
            {
                ns+=input->pop();
            }
            if(input->peek()=='(')
            {
                input->pop();
            }
        }
        else{
            while(!input->isEmpty()&&prec(s[i])<=prec(input->peek()))
            {
                char c = input->peek();
                input->pop();
                ns += c;
            }
            input->push(s[i]);
        }
    }
    while(!input->isEmpty())
    {
        char c = input->pop();
        if (c!='(' && c!=')') {
            ns+=c;
        }
    }
    cout << "Postfix notation: " << ns << endl;
    delete input;
}
int main( ) {
	submain();
    char Infix_expression[100];
    char tryAgain;
    do {
        cout<<"\nEnter the Infix Expression : ";
        cin>>Infix_expression;
        cout << "Infix notation: " << Infix_expression << endl;
        if (isValidInfix(Infix_expression)) {
            infixToPrefix(Infix_expression);
            infixToPostfix(Infix_expression);
        } else {
            cout << "Infix variable ranges from A to Z either in lower or upper case only " << endl;
            cout << "Please check your infix expression" << endl;
        }
        cout<<"Do you want to try again (y/n)? : ";
        cin>>tryAgain;
        tryAgain=tolower(tryAgain);
    }
    while (tryAgain!='n');
    return 0;
}
