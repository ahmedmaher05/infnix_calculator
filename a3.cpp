#include <iostream>
#include "stack.h"
#include <sstream>
#include<string>
#include <stdlib.h>
#include<math.h>
#include <iomanip>

using namespace std;
 //test
/* void numstackcontent(Stack<double> numstack)
 {
    float k1;
    cout<<"numstack content"<<'\n';
    while(!numstack.isempty())
    {
        k1=numstack.pop();
        cout<<k1<<"  ";
    }
 }
*/
/*void charstackcontent(Stack<char> charstack)
{

    char  k2;
    cout<<'\n'<<"charstack content"<<'\n';
    while(!charstack.isempty())
    {
        k2=charstack.pop();
        cout<<k2<<'\n';

    }
}*/

bool isFloat( string myString ) {
    istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

bool equalorhigherprior(char top,char entered) //exp>mul&div>add&sub [mod and fact !!!!!]
{
    if((top=='^'&&(entered=='%'||entered=='^'||entered=='x'||entered=='/'||entered=='+'||entered=='-'))
        ||(top=='x'&&(entered=='%'||entered=='x'||entered=='/'||entered=='+'||entered=='-'))
        ||(top=='/'&&(entered=='%'||entered=='x'||entered=='/'||entered=='+'||entered=='-'))
        ||(top=='%'&&(entered=='%'||entered=='x'||entered=='/'||entered=='+'||entered=='-'))
        ||(top=='+'&&(entered=='+'||entered=='-'))
        ||(top=='-'&&(entered=='+'||entered=='-')))
      return true;
    else
        return false;

}

double evaluate(double op1,char op,double op2)
{
    switch(op)
    {
    case '^' :
               return pow(op1,op2) ; break;
    case 'x' :
               return op1*op2; break;
    case '/' :
               return op1/op2; break;
    case '+' :
               return op1+op2; break;
    case '-' :
               return op1-op2; break;
    case '%' : return int(op1)%int(op2);break;
    }

}

bool isspecialchar(char ch)
{

    // To avoid undefined behavior
    if(ch=='!')
        return false;
        else if(ch==')')
        return false;
        else if(ch=='(')
        return false;
    else if(ch=='x')
        return true;
    else if ( islower( ch ))
             {
        return false;
             }
    else if ( isupper( ch ) )
        {
        return false;
        }
    else if ( isdigit( ch ) )
        {
        return false;
        }
    else
        {
        return true ;
        }

}

int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main(int argc , char *argv[])
{
    if(argc==1)
        {
        cout<<"0.00";
        return 0;
        }
    Stack<double>numstack;
    Stack<char>charstack;
    char op;
    int x =0;
    double op1,op2;
    bool notvalid=false;
    int a=0;
    int b=0;
    for(int i=1;i<argc;i++)
    {
        if(argv[1][0]=='!')
             notvalid=true;
        if(argv[i][0]!='('&&argv[i][0]!=')'&&argv[i][0]!='!'&&argv[i][0]!='^'&&argv[i][0]!='x'&&argv[i][0]!='/'&&argv[i][0]!='%'&&argv[i][0]!='+'&&argv[i][0]!='-'&&!isFloat(argv[i]))
            notvalid=true;

        if(i>1&&!isFloat(argv[i])&&!isFloat(argv[i-1])&&argv[i][0]!='('&&argv[i][0]!=')'&&argv[i-1][0]!='('&&argv[i-1][0]!=')')
        {
            if(isspecialchar(*argv[i-1])&&isspecialchar(*argv[i]))
                notvalid=true;

        }
        if(argv[i][1]!='\0'&&isspecialchar(argv[i][0])&&isspecialchar(argv[i][1]))
            notvalid=true;

        if(argv[i][0]=='(')
            a++;
        if(argv[i][0]==')')
            b++;
        if(argv[1][0]=='^'||argv[1][0]=='x'||argv[1][0]=='/'||argv[1][0]=='%'||argv[1][0]==')')
            notvalid=true;
        if((argv[i-1][0]=='^'||argv[i-1][0]=='x'||argv[i-1][0]=='/'||argv[i-1][0]=='%'||argv[i-1][0]=='('||argv[i-1][0]=='+'||argv[i-1][0]=='-')&&argv[i][0]=='!')
            notvalid=true;
        if(isFloat(argv[i-1])&&isFloat(argv[i]))
        notvalid=true;
        if(argv[i-1][0]=='('&&(argv[i][0]==')'||argv[i][0]=='!'||argv[i][0]=='^'||argv[i][0]=='x'||argv[i][0]=='/'||argv[i][0]=='%'))
            notvalid=true;
            if(i==(argc-1))
            {
                if(argv[i][0]=='^'||argv[i][0]=='x'||argv[i][0]=='/'||argv[i][0]=='%'||argv[i][0]=='('||argv[i][0]=='+'||argv[i][0]=='-'&&argv[i][0]=='\0')
           {
               notvalid=true;
            }

            }
     if(((argv[1][0]=='+'||argv[1][0]=='-')&&argv[1][1]=='\0')||(argc==2&&(argv[1][0]=='-'&&argv[1][1]=='-'||argv[1][0]=='+'&&argv[1][1]=='+')))
     {
              notvalid=true;

     }

    }

   if(argc==2&&(argv[1][0]=='^'||argv[1][0]=='x'||argv[1][0]=='/'||argv[1][0]=='%'||argv[1][0]==')'||argv[1][0]=='('||argv[1][0]=='!'))
           {
               notvalid=true;
            }

    for(int i=1;i<argc;i++)
    {


         if(notvalid||a!=b)
        {
            cout<<"Invalid Expression";
            return 0;
        }

        else
        {
           if(argv[i][0]=='(')
           {
            charstack.push(argv[i][0]);
           }

           else if(isFloat(argv[i]))
              {
            double x=atof(argv[i]);
            numstack.push(x);
            //cout<<"testt"<<i<<argc;
                      if(i==(argc-1))
                    {
                       // cout<<"arguments end";
                        while(!charstack.isempty())
                        {
                            op=charstack.pop();
                            op2=numstack.pop();
                            op1=numstack.pop();
                            if(op=='/'&&op2==0)
                           {
                               cout<<"Invalid Expression";
                               return 0;
                           }
                            numstack.push(evaluate(op1,op,op2));
                        }
                    }
              }
           else if(argv[i][0]=='^'||argv[i][0]=='x'||argv[i][0]=='/'||argv[i][0]=='%'||argv[i][0]=='+'||argv[i][0]=='-')
            {
                if(charstack.topindex==-1)
                {
                    charstack.push(argv[i][0]);
                }
                else if(equalorhigherprior(charstack.top(),argv[i][0])&&numstack.topindex>=1&&charstack.topindex>=0) //checks if top elem is equal or higher priority than argv[i][0]
                {

                    while(equalorhigherprior(charstack.top(),argv[i][0])&&numstack.topindex>=1&&charstack.topindex>=0)

                         {

                           op=charstack.pop();
                           op2=numstack.pop();
                           op1=numstack.pop();

                           if(op=='/'&&op2==0)
                           {
                               cout<<"Invalid Expression";
                               return 0;
                           }
                           numstack.push(evaluate(op1,op,op2));
                            if(charstack.topindex<0||numstack.topindex<=0)
                            break;
                          }

                    charstack.push(argv[i][0]);
                }

                else
                {
                    charstack.push(argv[i][0]);

                }

            }

            else if(argv[i][0]=='!')

            {

                if(charstack.topindex!=-1)
                {
                    if(numstack.top()<0||(fmod(numstack.top(),2)!=0&&fmod(numstack.top(),2)!=1))
                    {
                        cout<<"Invalid Expression";
                        return 0;
                    }
                    else
                    {

                        x=numstack.pop();
                       numstack.push(factorial(x));

                       if(i==(argc-1))
                    {
                        while(!charstack.isempty())
                        {
                            op=charstack.pop();
                            op2=numstack.pop();
                            op1=numstack.pop();
                             if(op=='/'&&op2==0)
                           {
                               cout<<"Invalid Expression";
                               return 0;
                           }
                            numstack.push(evaluate(op1,op,op2));
                        }
                    }

                    }
            }
            else
            {
                if(numstack.top()<0||(fmod(numstack.top(),2)!=0&&fmod(numstack.top(),2)!=1))
                    {
                        cout<<"Invalid Expression";
                        return 0;
                    }
              numstack.push(factorial(numstack.pop()));

            }
            }

           else if(argv[i][0]==')')
            {
                 a:if( charstack.top()=='(')
                      {
                      charstack.pop();
                      if(i==(argc-1))
                    {
                       // cout<<"arguments end";
                        while(!charstack.isempty())
                        {
                            op=charstack.pop();
                            op2=numstack.pop();
                            op1=numstack.pop();
                             if(op=='/'&&op2==0)
                           {
                               cout<<"Invalid Expression";
                               return 0;
                           }
                            numstack.push(evaluate(op1,op,op2));
                        }
                    }
                      }

                else
                {
                op=charstack.pop();
                op2=numstack.pop();
                op1=numstack.pop();
                 if(op=='/'&&op2==0)
                           {
                               cout<<"Invalid Expression";
                               return 0;
                           }
                numstack.push(evaluate(op1,op,op2));
                  goto a;

               }

            }

    }
    }
    cout<<std::fixed;
    cout<<setprecision(2)<<numstack.top();
 //cout<<'\n'<<" op1 "<<numstack.top()<<" op "<<charstack.top()<<" result is "<<setprecision(2)<<evaluate(numstack.top(),charstack.pop(),numstack.pop())<<" op2 "<<numstack.top();
    return 0;
}
