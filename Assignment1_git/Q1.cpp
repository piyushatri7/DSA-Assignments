#include <iostream>
#include<string>
#include <iomanip> 
using namespace std;
#define ll long long int

/*
cout<<"\ndebugging\n";				(0-2)%3
*/

template <class T>
class stack
{
    public:
    int tp;
    T *st=new  T[100000];
    
	stack()
	{
	    tp = -1;
	}
	
	void push(T i)
	{
	    st[++tp] = i;
	}
 
	T pop()
	{
	    return st[tp--];
	}
	T top()
	{
		
			return st[tp];
		
	}
	
	bool empty()
	{
		if(tp == -1)
			return true;
		return false;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////

template <typename t>
class queue
{
	public:
	int len,st,ed,max;
	t *a;
	
	queue()
	{
		a=new t[1000];
		len=0;
		max=1000;
		st=ed=-1;	//unintialized list
	}
	
	void push(t x)
	{
		
		if(st==-1 || ed==-1)		//empty deque
		{
			st=ed=0;
			a[ed]=x;
			len=1;
		}
		
		else
		{	
			if(len==max)			//array size exhausted
			{				
				t *b=a;
				a=new t[max*2];
				
				for(int i=0;i<len;i++)
					a[i]=b[(st+i)%max];		//copy data to new resized array
				
				st=0;
				ed=len;
				a[ed]=x;
				len++;
				max=max*2;
				//cout<<"\nlala\n";
				delete[] b;					
			}
			else
			{
				ed++;
				a[ed]=x;
				len++;
			}
		}	
		
	}



	void pop()
	{
		if(st==ed)			//delete last element
		{
			st=ed=-1;
			len=0;
		}
		else
		{
			
			len--;
			st = (st+1);
			if(st==max)		//delete element at 0th  pos
				st=0;
		}
	}
	
	void printq()
	{
		for(int i =0;i<len;i++)
			cout<<a[(st+i)%max]<<" ";
		cout<<"\n";
	}

	int size()
	{
		return len;
	}

	t front()
	{
		if(len==0)
			exit(1);
		return a[st];
	}

	t back()
	{
		if(len==0)
			exit(1);
		return a[ed];
	}

	bool empty()
	{
		if(len==0)
			return true;
		return false;
	}

	void clear()
	{
		delete[] a;
		a=new t[1000];
		len=0;
		max=1000;
		st=ed=-1;	//unintialized list
	}

	
};

///////////////////////////////////////////////////////////////////////////////////////////

queue<string> breakexpr(string s)
{
	queue<string> q;
	for(ll i=0;i<s.size();i++)
	{
		//cout<<"a\n";
		if(s[i]=='(' )
			q.push("(");
		 if(s[i]==')' )
			q.push(")");
		 if(s[i]=='+' )
			q.push("+");
		 if(s[i]=='-' )
			q.push("-");
		 if(s[i]=='/' )
			q.push("/");
		 if(s[i]=='*' )
			q.push("*");
		 if(s[i]=='%' )
			q.push("%");
			
		string t;
		bool f=0;
		while(i<s.size() && s[i]!='(' && s[i]!=')' && s[i]!='+' && s[i]!='-' && s[i]!='/' && s[i]!='*' && s[i]!='%' )
		{	
			t.push_back(s[i]);
			f=1;
			i++;
		}
		if(f)
		{	
			q.push(t);
			i--;
		}
	}
	return q;
}
///////////////////////////////////////////////////////////////////////////////////////////

queue<string> token_to_postfix(queue<string> q)
{
	
	stack<string> s;
	queue<string> op;
	
	while(!q.empty())
	{
		string t=q.front();			//current token
		//cout<<"\ndebugging\n";

		if(t=="(")
			s.push(t);
		else if(t==")")
		{
			while(!s.empty() &&  s.top()!="(")
			{
				op.push(s.top());
				s.pop();
			}
			s.pop();			//pop "("			
		}
		else if(t=="+" || t=="-")
		{
			while(!s.empty() && ( s.top()=="+" || s.top()=="-" || s.top()=="/" || s.top()=="*" || s.top()=="%" ))
			{
				op.push(s.top());
				s.pop();
			}
			s.push(t);
		}
		else if(t=="/" || t=="*" || t=="%")
		{
			while(!s.empty() && ( s.top()=="/" || s.top()=="*" || s.top()=="%" ))
			{
				op.push(s.top());
				s.pop();
			}
			s.push(t);	
		}	
		else
			op.push(t);	
			
		q.pop();
	}
	
	while(!s.empty())			//remaining operators
	{
		op.push(s.top());
		s.pop();
	}
	return op;
}
///////////////////////////////////////////////////////////////////////////////////////////

double postfix_eval(queue<string> q)
{
	stack<double> s;
	while(!q.empty())
	{
		string t=q.front();
		//cout<<"\ndebugging\n";

		if(t=="+" || t=="%" || t=="*" || t=="/" || t=="-" )
		{
			double n1=s.top();
			s.pop();
			double n2=s.top();
			s.pop();
			if(t=="+")
				s.push(n2+n1);
			if(t=="-")
				s.push(n2-n1);
			if(t=="/")
				s.push(n2/n1);
			if(t=="*")
				s.push(n2*n1);
			if(t=="%")
			{	
				long long int x1=n1,x2=n2,t;
				t=x2%x1;				//simple cpp mod
				s.push(t);	
			}
		}
		else
		{
			double x= stod(t);
			s.push(x);
		}
		
		q.pop();
	}
	return s.top();
}
///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//cout<<"\ndebugging\n";
		
	/*
	for(int i=0;i<100000;i++)
	{
		s.push_back('9');
		s.push_back('*');
	}
	s.push_back('8');

	while(!q.empty())
	{
		cout<<q.front()<<" ";
		q.pop();
	}
		
	stack<string> q;
	
	q.push("ghj");
	q.push("sdf");
	q.push("ljlk");
	
	cout<<q.top();
	*/
	//////////////Driver code//////////////////////////////////////////////////

	string s;
	cin>>s;
		
	queue<string> q=breakexpr(s);
	
	q=token_to_postfix(q);
	
	cout<<fixed;				//for printing upto 5 decimal places
    cout<<setprecision(10);		
	cout<<postfix_eval(q);
}

