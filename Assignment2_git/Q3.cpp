#include <bits/stdc++.h>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
class node
{
	public:
	T1 val1;
	T2 val2;
	node<T1,T2> *left,*right;
	int height,freq;
};
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
class ordered_map
{
	public:
	node<T1,T2> *root=NULL;
	int count=0;
	
	
	int height(node<T1,T2> *root);
	node<T1,T2>* ll(node<T1,T2> *par);
	node<T1,T2>* rr(node<T1,T2> *par);
	node<T1,T2>* lr(node<T1,T2> *par);
	node<T1,T2>* rl(node<T1,T2> *par);
	node<T1,T2>* insert_util(node<T1,T2> *root,T1 x,T2 y);
	void insert(T1 x,T2 y);
	
	node<T1,T2>* inordersucc(node<T1,T2> *root);
	node<T1,T2>* erase_util(node<T1,T2> *root,T1 x);
	void erase(T1 x);
	
	void inorder(node<T1,T2> *root);
	
	bool find_util(node<T1,T2> *root,T1 x);
	bool find(T1 x);
	
	T2& retrieve_util(node<T1,T2> *root,T1 x);
	T2& operator[](T1 x);
	
	void clear_util(node<T1,T2> *root);
	void clear();
	
	
	int size()
	{
		return count;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
int ordered_map<T1,T2>::height(node<T1,T2> *root)
{
	if(root)
		return root->height;
	return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
node<T1,T2>* ordered_map<T1,T2>::ll(node<T1,T2> *par)
{
	
	node<T1,T2> *child=par->left;
	par->left=child->right;
	child->right=par;
	
	par->height=max(height(par->left),height(par->right)) + 1;
	child->height=max(height(child->left),height(child->right)) + 1;
	
	
	return child;
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
node<T1,T2>* ordered_map<T1,T2>::rr(node<T1,T2> *par)
{
	
	node<T1,T2> *child=par->right;
	par->right=child->left;
	child->left=par;
	
	par->height = max(height(par->left),height(par->right)) + 1;
	child->height = max(height(child->left),height(child->right)) + 1;
	
	return child;
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
node<T1,T2>* ordered_map<T1,T2>::lr(node<T1,T2> *par)
{
	par->left=rr(par->left);
	return ll(par);
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
node<T1,T2>* ordered_map<T1,T2>::rl(node<T1,T2> *par)
{
	par->right=ll(par->right);
	return rr(par);
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
node<T1,T2>* ordered_map<T1,T2>::insert_util(node<T1,T2> *root,T1 x,T2 y)
{
	if(root)
	{
		if(x < root->val1)				//go left
		{
			//cout<<"a\n";
			root->left=insert_util(root->left,x,y);
			if(height(root->left)-height(root->right)==2)
			{
				if(x < root->left->val1)
					root=ll(root);
				else
					root=lr(root);
			}
		}
		else if(x > root->val1)			//go right
		{	
			root->right=insert_util(root->right,x,y);
			if(height(root->right)-height(root->left)==2)
			{
				//cout<<"b\n";
				if(x > root->right->val1)
					root=rr(root);
				else
					root=rl(root);
					
			}
		}
		else				//key already present
			;//root->val2=y;
		
	}
	else					//new node create
	{
			root=new node<T1,T2>();
			root->val1=x;
			root->val2=y;
			root->left=0;
			root->right=0;
			root->height=0;
			root->freq=1;
			count++;	
	}
	
	
	root->height=max(height(root->left),height(root->right)) + 1;
	return root;
}

template<class T1,class T2>
void ordered_map<T1,T2>::insert(T1 x,T2 y)
{
	root=insert_util(root,x,y);
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
node<T1,T2> * ordered_map<T1,T2>::inordersucc(node<T1,T2> *root) 
{ 
    node<T1,T2> *cur = root; 
    
    while (cur->left != NULL) 
        cur = cur->left; 
  
    return cur; 
} 

template<class T1,class T2>
node<T1,T2> * ordered_map<T1,T2>::erase_util(node<T1,T2> *root,T1 x)
{
	if(root)		//bst delete
	{	
		if(x < root->val1)
			root->left=erase_util(root->left,x);
		else if(x > root->val1)
			root->right=erase_util(root->right,x);
		else if((root->val1) == x)			
		{		
	        if( (root->left == NULL) || (root->right == NULL) ) 
	        { 
	            node<T1,T2> *temp = root->left ? root->left : root->right; 
	  
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
		        node<T1,T2> *temp = inordersucc(root->right); 	  
		        root->val1 = temp->val1;
				root->val2 = temp->val2;  	  
		        root->right = erase_util(root->right, temp->val1); 
	    	}
	    } 			
	}
	else
		return root;
	
	//avl balancing
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

template<class T1,class T2>
void ordered_map<T1,T2>::erase(T1 x)
{
	root=erase_util(root,x);
	if(count>0)			//cant delete from empty tree
		count--;
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
void ordered_map<T1,T2>::inorder(node<T1,T2> *root)
{
	if(root)
	{
		inorder(root->left);
		cout<<"("<<root->val1<<","<<root->val2<<") ";
		inorder(root->right);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
bool ordered_map<T1,T2>::find_util(node<T1,T2> *root,T1 x)
{
	if(root)
	{
		if(x < root->val1)  
			return find_util(root->left,x);
		else if(x > root->val1) 
			return find_util(root->right,x);
		else if(x == root->val1)
			return true;
	}
	return false;
}
template<class T1,class T2>
bool ordered_map<T1,T2>::find(T1 x)
{
	return find_util(root,x);
}
///////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2>
T2& ordered_map<T1,T2>::retrieve_util(node<T1,T2> *root,T1 x)			//retrieve value
{
	if(root)
	{
		if(x < root->val1)  
			return retrieve_util(root->left,x);
		else if(x > root->val1) 
			return retrieve_util(root->right,x);
		else if(x == root->val1)
			return root->val2;
	}
	
}
template<class T1,class T2>
T2& ordered_map<T1,T2>::operator[](T1 x)
{
	if(find(x))
	{
		return retrieve_util(root,x);
	}
	else
	{
		T2 temp;
		insert( x , temp);
		return retrieve_util(root,x);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
template<class T1,class T2>
void ordered_map<T1,T2>::clear_util(node<T1,T2> *root)
{
	if(root)
	{
		clear_util(root->left);
		clear_util(root->right);
		delete root;
	}
}
template<class T1,class T2>
void ordered_map<T1,T2>::clear()
{
	clear_util(root);			
	ordered_map<T1,T2>::root=NULL;
	ordered_map<T1,T2>::count=0;			//update count after clear		
}
///////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	int t;
	string s;
	ordered_map<int,string> tree;
	//cout<<height(root);
	int n;
	/*
	cin>>n;
	while(n--)
	{
		//int x;
		//cin>>x;
		//cout<<n<<" ";
		
		root=insert(root,2*n);
	}
	*/
	int val=1000;
	/*
	tree.insert( 9 , val); 
    tree.insert( 5, val); 
    tree.insert( 10, val); 
    tree.insert( 0, val); 
    tree.insert( 6, val); 
    tree.insert( 11, val); 
    tree.erase(5);
    //tree.insert( -1, val); 
   	//tree.insert( 1, val); 
    //tree.insert( 2, val); 
    tree[2]=69;
    tree[1]=val;
    tree[1]=-10;
    tree.clear();
    */
    tree.insert( 1 , "af"); 
    tree.insert( 2 , "sgdaf"); 
    tree.insert( 3 , "adgs"); 
    //tree.erase(2);
    //cout<<tree[2];
	//cout<<"\n"<<tree.size()<<"\n ";
	
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
    
	//cout<<tree.find(tree.root,-100);
	/*
	tree.clear();
	tree.erase(5);
	tree.erase(9);
	cout<<tree.size()<<"\n";
	*/
	tree.inorder(tree.root);
	
	return 0;
}
