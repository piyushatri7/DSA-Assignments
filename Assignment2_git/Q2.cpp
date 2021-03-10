#include <bits/stdc++.h>
#define BUCK 10061

using namespace std;
template<class T1,class T2>
class llnode		//node structure
{
	public:
	llnode *next;
	T1 key;
	T2 val;
};
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
class ll
{
	public:
	llnode<T1,T2> *front;
	ll()
	{
		front=NULL;
	}
	void insertll(T1 key,T2 val);
	void erasell(T1 key);
	bool findll(T1 key);
	T2 access_key(T1 key);
	void printlist();	
};
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
void ll<T1,T2>::insertll(T1 key,T2 val)
{
	if(!front)		//empty list
	{
		llnode<T1,T2> *temp=new llnode<T1,T2>();
		temp->key=key;
		temp->val=val;
		temp->next=NULL;
		front=temp;
	}
	else
	{
		llnode<T1,T2> *t=front;
		if(front->key==key )		//if  single node and key match
			return;
		while(t->next)
		{
			if(t->key==key)			//if  multiple node and key,value match
				return;
			t=t->next;
		}
		//only allocate memory if key,val not present
		llnode<T1,T2> *temp=new llnode<T1,T2>();
		temp->key=key;
		temp->val=val;
		temp->next=NULL;
		t->next=temp;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
void ll<T1,T2>::printlist()
{
	llnode<T1,T2> *temp=front;
	while(temp)
	{
		cout<<"("<<temp->key<<","<<temp->val<<") ";
		temp=temp->next;
	}
	cout<<"\n";
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
void ll<T1,T2>::erasell(T1 key)
{
	if(front)
	{
		
		llnode<T1,T2> *temp1=front , *temp2=front;
		while(temp1 && temp1->key != key)
			temp1=temp1->next;
		
		if(temp1)					//if key exist
		{
			if(temp1==front)		//if key is at start of list
				front=temp1->next;
			else					//if key is at middle of list
			{
				while(temp2 && temp2->next!=temp1)
					temp2=temp2->next;
				temp2->next=temp2->next->next;	
			}
			delete temp1;
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
bool ll<T1,T2>::findll(T1 key)
{
	llnode<T1,T2> *temp=front;
	while(temp)
	{
		if(temp->key==key)
			return true;
		temp=temp->next;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
T2 ll<T1,T2>::access_key(T1 key)
{
	llnode<T1,T2> *temp=front;
	while(temp)
	{
		if(temp->key==key)
			return temp->val;
		temp=temp->next;
	}
	exit(1);
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1, class T2> 
class umap
{
	public:
	ll<T1,T2> htable[BUCK];				//array of chains
	
	void print_htable(); 
	/*
	long long hash(long long  key);
	long long hash(float key);
	*/
	long long hash(T1 key);
	
	void insert(T1 key,T2 value);
	void erase(T1 key);
	bool find(T1 key);
	T2 operator[](T1 key);
	
};
///////////////////////////////////////////////////////////////////////////////////////////

template<class T>
string tostr(T key)
{
	stringstream s;
    s<<key;
    return s.str();
}

template<class T1,class T2>
long long umap<T1,T2>::hash(T1 key)
{	
	string s=tostr(key);				//convert any type to  string
	
    long long hash_val = 0;
    long long mul = 1;
    long long prime = 43;					//73 83  cyclicity 4
    long long mod = 100000004987;				//determines how large mul can be
    
    for (long long i = 0; i < s.size(); i++)
    {
        hash_val = (hash_val%BUCK + (s[i] * mul)%BUCK)%BUCK;	//s[i] will be less than 256 ASCII range so mod not necessry
        mul = (mul%mod * prime%mod)%mod;
    }
    return hash_val;
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2> 
void umap<T1,T2>::insert(T1 key,T2 value)
{
	long long hval = hash(key);
	htable[hval].insertll(key,value);
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2> 
void umap<T1,T2>::erase(T1 key)
{
	long long hval= hash(key);
	htable[hval].erasell(key);
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2> 
void umap<T1,T2>::print_htable()
{
	for(int i=0;i<BUCK;i++)
	{
		if(htable[i].front)
			htable[i].printlist();
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2> 
bool umap<T1,T2>::find(T1 key)
{
	long long hval = hash(key);
	return (htable[hval].front)?true:false;
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1, class T2> 
T2 umap<T1,T2>::operator[](T1 key)
{
	long long hval = hash(key);
	return htable[hval].access_key(key);
}
///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//cout<<to_string(10.55);
	/*
	ll<string> list;
	string s;
	for(int i=0;i<5;i++)
	{
		cin>>s;
		list.insertll(s);
	}
	list.printlist();
	cout<<"find->";
	cin>>s;
	cout<<list.findll(s)<<"\n";
	cout<<"erase->";
	cin>>s;
	list.erasell(s);
	list.printlist();
	*/
	
	
	int a;
	float f1;
	string s1;
	/*
	umap<float,string> mp;
	
	cout<<"insert->\n";
	for(int i=0;i<5;i++)
	{
		cin>>f1>>s1;
		mp.insert(f1,s1);
	}
	*/
	/*
	11 asfa
	12 oushdf
	21 aoihf
	21 sdgf
	21 gs
	*/
	
	//cout<<mp.find(21);
	//cout<<mp[21];
	//mp.print_htable();
	
	/*	//Testing hash func
	unordered_map<long long,int> mp1;
	umap<float,string> mp;
	int i;
	for( i=1;i<20000;i++)		//hash values
		mp1[mp.hash(i)]++;
	cout<<(float)20000/float(mp1.size());
	*/
	return 0;
	
}

