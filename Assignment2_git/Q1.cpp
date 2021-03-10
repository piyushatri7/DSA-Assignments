#include <bits/stdc++.h>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class node
{
	public:
	T val;
	node<T> *left,*right;
	long long height,freq,nodec;
};
///////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class avltree
{
	public:
	node<T> *root=NULL;
	long long count=0;
	long long height(node<T> *root);
};
///////////////////////////////////////////////////////////////////////////////////////////
class demo
{
	public:
	int rno;
	int marks;
	
	demo()
	{
		rno=0;
		marks=0;	
	}
	demo(int a)
	{
		rno=a;
		marks=0;	
	}
	demo(int a,int b)
	{
		rno=a;
		marks=b;	
	}	
	
	bool operator<(demo obj)
	{
		return (rno<obj.rno);
	}
	bool operator>(demo obj)
	{
		return (rno>obj.rno);
	}
	bool operator==(demo obj)
	{
		return (rno==obj.rno);
	}
	bool operator<=(demo obj)
	{
		return (rno<=obj.rno);
	}
	bool operator>=(demo obj)
	{
		return (rno>=obj.rno);
	}
};
///////////////////////////////////////////////////////////////////////////////////////////
template <class T>
long long height(node<T> *root)
{
	if(root)
		return root->height;
	return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////
template <class T>
long long node_count(node<T> *root)
{
	if(root)
		return root->nodec;
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
node<T>* ll(node<T> *par)
{
	
	node<T> *child=par->left;
	par->left=child->right;
	child->right=par;
	
	par->nodec = par->freq + node_count(par->left) + node_count(par->right);			//parent count first
	child->nodec = child->freq + node_count(child->left) + node_count(child->right);
	
	par->height=max(height(par->left),height(par->right)) + 1;							//parent height first
	child->height=max(height(child->left),height(child->right)) + 1;
	
	
	return child;
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
node<T>* rr(node<T> *par)
{
	
	node<T> *child=par->right;
	par->right=child->left;
	child->left=par;
	
	par->nodec =par->freq + node_count(par->left) + node_count(par->right);
	child->nodec = child->freq + node_count(child->left) + node_count(child->right);
	
	par->height = max(height(par->left),height(par->right)) + 1;
	child->height = max(height(child->left),height(child->right)) + 1;
	
	return child;
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
node<T>* lr(node<T> *par)
{
	par->left=rr(par->left);
	return ll(par);
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
node<T>* rl(node<T> *par)
{
	par->right=ll(par->right);
	return rr(par);
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
node<T>* insert(node<T> *root,T x)
{
	if(root)
	{
		if(x < root->val)				//go left
		{
			//cout<<"a\n";
			root->left=insert(root->left,x);
			root->nodec = root->freq + node_count(root->left) + node_count(root->right);	
			
			if(height(root->left)-height(root->right)==2)
			{
				if(x < root->left->val)
					root=ll(root);
				else
					root=lr(root);
			}
		}
		else if(x > root->val)			//go right
		{	
			root->right=insert(root->right,x);
			root->nodec = root->freq + node_count(root->left) + node_count(root->right);	
			
			if(height(root->right)-height(root->left)==2)
			{
				//cout<<"b\n";
				if(x > root->right->val)
					root=rr(root);
				else
					root=rl(root);
					
			}
		}
		else
		{
			(root->freq)++;
			(root->nodec)++;
		}	
	}
	else					//empty tree
	{
			root=new node<T>();
			root->val=x;
			root->left=0;
			root->right=0;
			root->height=0;
			root->freq=1;
			root->nodec=1;	
	}
	
	root->height=max(height(root->left),height(root->right)) + 1;
	return root;
}

///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
node<T> * inordersucc(node<T> *root) 
{ 
    node<T> *cur = root; 
    
    while (cur->left != NULL) 
        cur = cur->left; 
  
    return cur; 
} 

template <class T>
node<T> * remove(node<T> *root,T x)
{
	if(root)		//bst delete
	{	
		if(x < root->val)
			root->left=remove(root->left,x);
		else if(x > root->val)
			root->right=remove(root->right,x);
		else if((root->freq - 1)==0)			//check repeated element
		{		
	        if( (root->left == NULL) || (root->right == NULL) ) 
	        { 
	            node<T> *temp = (root->left) ? (root->left) : (root->right); 
	  
	            if (temp == NULL) 	// No child case 
	            { 
	                temp = root; 
	                root = NULL; 
	            } 
	            else 				//One child case 
	             *root = *temp; 
	                            
	            delete temp; 
	        } 
	        else
			{
				//cout<<"a\n";
		        node<T> *temp = inordersucc(root->right); 	  
		        root->val = temp->val; 
				root->freq = temp->freq;
				temp->freq = 1;	  		//this is so that the node is deleted and not just freq is decreased
		        root->right = remove(root->right, temp->val); 
	    	}
	    } 
		else
			(root->freq)--;
			
		if(root)
			root->nodec = root->freq + node_count(root->left) + node_count(root->right);				
	}
	else
		return root;
	
	//cout<<"d\n";
	if(root)
	{
		root->height = max(height(root->left),height(root->right)) + 1;
		//cout<<root->height<<"\n";
		
		if(abs(height(root->right)-height(root->left)) == 2 )		//imbalance
		{
			//cout<<"c\n";
			if(height(root->left) > height(root->right))
			{
				//cout<<"c\n";
				//cout<<height(root->left->left)<<","<<height(root->left->right)<<"\n";
				//cout<<"\n";
				//inorder(root);
				if(height(root->left->left) >= height(root->left->right) ) 		//ll
				{
					//cout<<"ll\n";
					root= ll(root);
					/*
					cout<<"\n";
					inorder(root);
					*/
				}
				else if(height(root->left->left) < height(root->left->right))	//lr
				{
					//cout<<"lr\n";
					return lr(root);
				}
			}
			else if(height(root->left) < height(root->right))			
			{
				//cout<<"b\n";
				if(height(root->right->left) <= height(root->right->right))		//rr
				{
					//cout<<"rr\n";
					return rr(root);
				}
				else if(height(root->right->left) > height(root->right->right))	//rl
				{
					//cout<<"rl\n";
					return rl(root);
				}
			}
		}
	}
	else
		return root;
	
	return root;	
}

///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
bool search(node<T> *root,T x)
{
	if(root)
	{
		if(x < root->val)  
			return search(root->left,x);
		else if(x > root->val) 
			return search(root->right,x);
		else if(x == root->val)
			return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
int count_occur(node<T> *root,T x)
{
	if(root)
	{
		if(x < root->val)  
			return count_occur(root->left,x);
		else if(x > root->val) 
			return count_occur(root->right,x);
		else if(x == root->val)
			return root->freq;
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void close_val(node<T> *root,T x,T &cl)
{
	if(root)
	{
		if(abs(cl-x) > abs(root->val-x))
			cl=root->val;
		if(abs(cl-x) == abs(root->val-x))		//alwways take smaller value
			cl=min(root->val,cl);
				
		if(x < root->val)  
			close_val(root->left,x,cl);
		else if(x > root->val) 
			close_val(root->right,x,cl);
		else if(x == root->val)
			cl=root->val;
	}
	//return cl;
}
//specialized for strings

void close_val(node<string> *root,string x,string &cl)
{
	if(root)
	{	
		if(abs(cl.compare(x)) > abs(root->val.compare(x)))
			cl=root->val;
		if(abs(cl.compare(x)) == abs(root->val.compare(x)))		//always take smaller value
			cl=min(root->val,cl);
				
		if(x < root->val)  
			close_val(root->left,x,cl);
		else if(x > root->val) 
			close_val(root->right,x,cl);
		else if(x == root->val)
		{
			cl = x;
			return ;
		}
		
		/*
		cl=root->val;
		if(x.compare(root->val)==0)
			return ;
		else if(x.compare(root->val) < 0)
			close_val(root->left,x,cl);
		else
			close_val(root->right,x,cl);
		*/
	}
}
template <class T>
T closest_ele(node<T> *root,T x)
{
	if(root)
	{
		T cl;
		cl=root->val;
		close_val(root,x,cl);
		return cl;
	}	
}
///////////////////////////////////////////////////////////////////////////////////////////
template <class T>							//assuming the lower bound exists
void lower(node<T> *root,T x,T &lb)
{
	if(root)
	{
		if(root->val < x)
			return lower(root->right,x,lb);
		else if(root->val >= x)
		{
			lb=root->val;
			return lower(root->left,x,lb);
		}
	}
}

template <class T>
T lower_bound(node<T> *root,T x)
{
	if(root)
	{
		T lb;
		lower(root,x,lb);
		return lb;
	}
	//return INT_MIN;
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
T upper(node<T> *root,T x,T &ub)				//assuming the upper bound exists
{
	if(root)
	{
		if(root->val <= x)
			return upper(root->right,x,ub);
		else if(root->val > x)
		{
			ub=root->val;
			return upper(root->left,x,ub);
		}	
	}
}

template <class T>
T upper_bound(node<T> *root,T x)
{	
	if(root)
	{
		T ub;
		upper(root,x,ub);
		return ub;
	}
	//return INT_MIN;
}
///////////////////////////////////////////////////////////////////////////////////////////
template <class T>
T Kthlargest(node<T> *root,int k)
{
	if(root)
	{
		if( k>(node_count(root->right)) && k<=(root->freq + node_count(root->right)))
			return root->val;
		else if(k > (root->freq + node_count(root->right)))
		{
			k = k - node_count(root->right) - root->freq;
			return Kthlargest(root->left,k);
		}
		else
			return Kthlargest(root->right,k);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
template <class T1,class T2,class T3>				//all parameters can be off diff type like int ,long long int,float
void count_left_greater(node<T1> *root,T2 l,T3 &count)
{
	if(root)
	{
		if(root->val < l)
		{
			count = count - node_count(root->left) -root->freq;
			count_left_greater(root->right,l,count);
		}
		else
			count_left_greater(root->left,l,count);
	}
}
template <class T1,class T2,class T3>
void count_right_greater(node<T1> *root,T2 r,T3 &count)
{
	if(root)
	{
		if(root->val > r)
		{
			count = count - node_count(root->right) - root->freq;
			count_right_greater(root->left,r,count);
		}
		else
			count_right_greater(root->right,r,count);
	}
}
template <class T1,class T2>					//tree can be string and l,r can be long long
long long rangecount(node<T1> *root,T2 l,T2 r)
{
	long long n=root->nodec; 
	
	long long lrange=n, rrange=n;
	count_left_greater(root,l,lrange);
	count_right_greater(root,r,rrange);
	
	return (lrange + rrange - n);
}
///////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void inorder(node<T> *root)
{
	if(root)
	{
		inorder(root->left);
		int x=root->freq;
		while(x--)
			cout<<"("<<root->val<<","<<root->freq<<","<<root->height<<","<<root->nodec<<") ";
		inorder(root->right);
	}
}

//specialized inorder for demo class
void inorder(node<demo> *root)
{
	if(root)
	{
		inorder(root->left);
		int x=root->freq;
		while(x--)
			cout<<"("<<(root->val).rno<<","<<(root->val).marks<<") ";
		inorder(root->right);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	
	int t;
	string s;
	node<double> *avlObj=0;
	
	avlObj=insert(avlObj,2.0);
	avlObj=insert(avlObj,2.5);
	avlObj=insert(avlObj,1.5);
	avlObj=insert(avlObj,1.0);
	avlObj=insert(avlObj,3.0);
	avlObj=insert(avlObj,5.3);
	avlObj=insert(avlObj,3.5);
	avlObj=insert(avlObj,6.7);
	avlObj=insert(avlObj,4.3);
	avlObj=insert(avlObj,2.1);
	avlObj=insert(avlObj,1.0);
	avlObj=insert(avlObj,8.9);
	avlObj=insert(avlObj,3.8);
	avlObj=insert(avlObj,6.9);
	avlObj=insert(avlObj,6.7);
	/*
	int n = 100;
	
	for (int i = 1; i <= n; i ++) 
	{
		//demo d(i,100);
		root=insert(root,i);
	}
	inorder(root);
	cout << "\n\n";
	
	
	for (int i = 1; i <= n; i += 4) 
		root=remove(root,i);
	inorder(root);
	
	cout << endl;
	cout << endl;
	
	for (int i = 1; i <= n; i += 13) 
		root=insert(root,i);
	*/
	/*
	root = insert(root, 25); 		//root=remove(root,10);
	root = insert(root, 53);
	root = insert(root, 26);	
	root = insert(root, 86);
	root = insert(root, 24);
	root = insert(root, 38);
	root = insert(root, 56);	
	root = insert(root, 36);
	root = insert(root, 18);
	*/
	/*		
				26
			   /   \
			24		53
		   / \      / \
		 18	  25  38   86
		 		  / \
		 		 36  56
	*/
				
	//cout<<rangecount(root,30,100);
	/*
	root=remove(root,38);
	root=remove(root,25);
	root=remove(root,26);
	root=remove(root,56);
	root=remove(root,53);
	root=remove(root,18);
	root=remove(root,36);
	*/
	cout<<"(value,freq,height,nodecount)\n\n";
	inorder(avlObj);
	cout << endl;
	//cout<<height(root);
	/*
	int n;
	string a="aaa";
	string b="bbb";
	string c="ccc";
	root = insert(root, a); 
    root = insert(root, b);  
    root = insert(root, c);  root = insert(root, c);  root = insert(root, c); 
     */
    
	/*	
	root = insert(root, 9); 
    root = insert(root, 5);  
    root = insert(root, 10); 
    root = insert(root, 0); 
    root = insert(root, 6); 	root = insert(root, 6); root = insert(root, 6); 
    root = insert(root, 11); 
    root = insert(root, -1); 
    root = insert(root, 1); 
    root = insert(root, 2); 
	cout<<"\n";
	*/
	/*
	 The constructed AVL Tree would be 
            9 
           /  \ 
          1    10 
        /  \     \ 
       0    5     11 
      /    /  \ 
     -1   2    6 
    */
    /*
    for(int i=0;i<4;i++)
    {
    	
    	cin>>s;
    	root = insert(root, s); 
	}
    */
    /*
	inorder(root);
	cout<<"\nenter element->";
	
	cin>>t;
	//cout<<"\n"<<search(root,t);
	//cout<<"\n"<<count_occur(root,t);
	//cout<<closest_ele(root,t);
	//cout<<lower_bound(root,t);
	//cout<<upper_bound(root,t);
	root=remove(root,t);
	cout<<"\n";
	inorder(root);
	//root=remove(root,10);
	cout<<"\n";
	inorder(root);
	int k;
	cout<<"enter k ";
	cin>>k;
	cout<<Kthlargest(root,k);
	*/
	//inorder(root);
	//cout<<rangecount(root,-2,-1);
	//cout<<lower_bound(root,8);
	//string st="cbc";
	//cout<<closest_ele(root,st);
	
	return 0;
}
