#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define MAXBITS 6
typedef struct Node{
	struct Node *child[2];
}node;

/////////////////////////////////////////////////////////////////////////////////////////////
void insert(ll x, node *root)
{
	for(ll i=MAXBITS;i>=0;i--)
	{	
		bool f = x & (1LL<<i);
		cout<<f;
		if(!root->child[f])
		{
			node *temp =  new node();
			temp->child[0] = temp->child[1] = 0;
			
			root->child[f] = temp;
		}
		root = root->child[f];		
	}
	cout<<"\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////
void preorder(node *root)
{
	if(root)
	{
		if(root->child[0])
			cout<<"0 ";
		preorder(root->child[0]);
		if(root->child[1])
			cout<<"1 ";
		preorder(root->child[1]);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
ll maxxor(ll x,node *root)
{
    node *temp=root;
    ll i,res=0;    
    
    for(i = MAXBITS;i>=0 && !(x&1LL<<i) && !temp->child[1] ;i--)            //skip leading zeroes
        temp = temp->child[0];
    
    for(;i>=0;i--)                
    {
        bool f = (x & (1LL<<i));        //select bit
        bool finv = f ^ 1;              //invert bit

        if ((temp->child[finv]))       //inverse matches
        {
            res = res + (1 << i); 	
            temp = temp->child[finv]; 
        }
        else							//go to other child	
            temp = temp->child[f];
    }
    return res;
}
/////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	ll n,q,x;
	cin>>n>>q;
	
	node *tree = new node();
	tree->child[0] = tree->child[1] = 0;
	
	for(ll i=0;i<n;i++)
	{
		cin>>x;
		insert(x,tree);
	}
	preorder(tree);
	cout<<"\n";
	
	while(q--)
	{
		cin>>x;
		cout<<maxxor(x,tree)<<"\n";
	}
	return 0;
}

