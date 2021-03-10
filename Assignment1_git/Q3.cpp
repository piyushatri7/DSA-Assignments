#include <iostream>
#include<string>
#include<time.h>
using namespace std;

/*
///////////////archived code for deque using DLL////////////////////////
template <typename T> 
class deque1
{
	public:
	T data;
	deque1 *next,*prev;
	deque1 *front=0,*rear=0;
	static int c;	
	
	deque1()		//O(1)
	{
		front=rear=0;		//initialize empty queue
	}
	
	void push_back(T x)				//O(1)
	{
		deque1 *temp=new deque1();
		temp->next=temp->prev=0;
		temp->data=x;
		
		if(front==0 && rear==0)		//empty queue
		{
			rear=front=temp;
		}
		else
		{
			rear->next=temp;
			temp->prev=rear;
			rear=temp;
		}
		c++;						//increase size
	}	

	void push_front(T x)			//O(1)
	{
		deque1 *temp=new deque1();
		temp->next=temp->prev=0;
		temp->data=x;
		
		if(front==0 && rear==0)
		{
			rear=front=temp;
		}
		else
		{
			front->prev=temp;
			temp->next=front;
			front=temp;
		}
		c++;
	}
	
	void pop_back()					//O(1)
	{
		if(rear == 0)		//empty queue
			return ;
		else if(rear->next==0 && rear->prev==0)			//single element
		{
			deque1 *temp=front;
			front=rear=0;
			delete temp;
			c--;
		}
		else
		{
			deque1 *temp=rear;
			rear=rear->prev;
			if(rear)
				rear->next=0;
			delete temp;
			c--;
		}
	}
	
	void pop_front()				//O(1)
	{
		if(front == 0)
			return ;
		else if(front->next==0 && front->prev==0)
		{
			deque1 *temp=front;
			front=rear=0;
			delete temp;
			c--;
		}
		else
		{
			deque1 *temp=front;
			front=front->next;
			if(front)
				front->prev=0;
			delete temp;
			c--;
		}
	}

	void printq1()					//O(n)
	{
		deque1 *temp=front;
		if(rear)			//rear has been deleted (empty queue)
		{
			while(temp)
			{
				cout<<temp->data<<" ";
				temp=temp->next;	
			}
			cout<<"\n";	
		}
	}	
	 
	T front1()						//O(1)
	{
			if(front==0)
			{
				cout << "queue empty!"; 
				exit(0); 
			}
			else
				return front->data;
	}
	
	T back1()						//O(1)
	{
			if(front==0)
			{
				cout << "queue empty!"; 
				exit(0); 
			}
			else
				return rear->data;
	}

	int size()						//O(1)
	{
		return c;
	}

	bool empty()					//O(1)
	{
		if(c)
			return false;
		return true;
	}

	deque1(int n,T x)				//O(n)
	{
		front=rear=0;
		while(n--)
			this->push_back(x);
	}
	
	void clear()					//O(n)
	{
		while(c)
		{
			this->pop_back();
			//cout<<c<<" ";
		}
		front=rear=0;
	}

	T& operator[](int index) 		//O(n)	//access dqueue as q[i]
	{ 
		if (index >= c) { 
			cout << " index out of bound, exiting"; 
			exit(0); 
		} 
		deque1 *temp = this->front;
		for(int i=0;i<index;i++)		//move to required element
		 temp=temp->next;
		 
		return temp->data;
	} 

	void resize(int n,T defval)		//O(n)
	{
		if(n<0)
		{
			cout<<"invalid size!\n";
		}
		else if(n<=c)
		{
			int diff=c-n;
			while(diff--)
				this->pop_back();
		}
		else
		{
			int diff=n-c;		
			while(diff--)
				this->push_back(defval);			
		}
		
	}
};


template <typename T> 		//static variable for size of deque
int deque1<T>::c = 0;
*/

/////////////////////deque using dynamic array///////////////////////
template <typename t>
class deque
{
	public:
	int len,st,ed,max;
	t *a;
	
	deque()
	{
		a=new t[1000];
		len=0;
		max=1000;
		st=ed=-1;	//unintialized list
	}
	
	deque(int n,t x)
	{
		a=new t[n];
		for(int i=0;i<n;i++)
			a[i]=x;
		max=n;	
		len=n;
		st=0;
		ed=n-1;
	}
	
	void push_back(t x)
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

	void push_front(t x)
	{
		if(st==-1 || ed==-1)		//empty deque
		{
			st=ed=0;
			a[st]=x;
			len=1;
			
		}
		else
		{	
			if(len==max)			//array size exhausted
			{	
				//cout<<"asd\n";			
				t *b=a;
				a=new t[max*2];
				
				for(int i=1;i<=len;i++)		//dont put anything in 0th index
					a[i]=b[(st+i)%max];		//copy data to new resized array
				
				st=0;
				ed=len;
				a[st]=x;
				len++;
				//cout<<"\nlala\n";
				delete[] b;					
			}
			else
			{
				st--;
				if(st<0)
					st=max-1;
				a[st]=x;
				len++;
			}
		}	
		
	}	
	
	void pop_back()
	{
		if(st==ed)			//delete last element
		{
			st=ed=-1;
			len=0;
		}
		else
		{
			
			len--;
			ed = (ed-1);
			if(ed<0)		//delete element at 0th  pos
				ed=max-1;
		}
	}

	void pop_front()
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
	
	void display()
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

	t& operator[](int index) 		//O(n)	//access dqueue as q[i]
	{ 
		if (index >= len || index<0) 		//invalid index
		{ 
			exit(1); 
		} 
		return a[(st+index)%max];
	} 

	void resize(int x,t d)
	{
		if(x<0 || x > INT_MAX)
			exit(1);
		
		if(x<len)
		{
			x=len-x;
			for(int i=0;i<x;i++)
				this->pop_back();
		}
		else
		{
			x=x-len;
			for(int i=0;i<x;i++)
				push_back(d);
		}
	}
};
int main()
{
	/*
	deque<int> d(100000,8);

    cout<<"size : "<<d.size()<<endl;

    int count = 0;
    for(int i=0; i<d.size(); i++){
        int temp = d[i];
        count++;
    }

    cout<<"1 lakh elements accessed ! "<<count<<endl;

    d.clear();

    cout<<"after clear - size : "<<d.size()<<endl;

    for(int i=0; i<50000; i++){
        d.push_back(2);
        d.push_front(1);
    }

    cout<<"1 lakh elements pushed !"<<endl;

    cout<<"after push - size : "<<d.size()<<endl;

    
    for(int i=0; i<50000; i++){
        d.pop_back();
        d.pop_front();
    }

    cout<<"1 lakh elements popped !"<<endl;

    cout<<"size : "<<d.size()<<endl;

    d.resize(10,2);

    cout<<"after resize : "<<d.size()<<endl;

    cout<<"front : "<<d.front()<<"  ";
    cout<<"back : "<<d.back()<<endl;
    */
	
	
	int t,option,n,d;
	string x;
	//deque<int> q1;
	//deque<double> q1;
	//deque<char> q1;
	
	
	deque<string> *q;
	
	cin>>t;
	
	while(t--)
	{
		cin>>option;
		if(option==1)
		{
			cin>>x;
			q->push_front(x);
			q->display();
		}
		else if(option==2)
		{
			q->pop_front();
			q->display();
		}
		else if(option==3)
		{
			cin>>x;
			q->push_back(x);
			q->display();
		}
		else if(option==4)
		{
			q->pop_back();
			q->display();
		}
		else if(option==5)
		{
			q=new deque<string>();
		}
		else if(option==6)
		{
			cin>>n>>x;
			q=new deque<string>(n,x);
			q->display();
		}
		else if(option==7)
		{
			cout<<q->front()<<"\n";
		}
		else if(option==8)
		{
			cout<<q->back()<<"\n";
		}
		else if(option==9)
		{
			if(q->empty())
				cout<<"true\n";
			else
				cout<<"false\n";	
		}
		else if(option==10)
		{
			cout<<q->size();
		}
		else if(option==11)
		{
			int a;
			string b;
			cin>>a>>b;
			q->resize(a,b);
			q->display();
		}
		else if(option==12)
		{
			q->clear();
		}
		else if(option==13)
		{
			cin>>n;
			cout<<(*q)[n]<<"\n";
		}
		else
		{
			q->display();
		}
	}
	
	
	delete q;
	return 0;
}
