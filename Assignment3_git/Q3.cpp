#include <bits/stdc++.h> 
#define ll long long 
using namespace std; 
  
typedef struct heapnode 
{ 
    ll val; 
    ll i; 				//index of file
}node; 

void swap(node &x, node &y) 
{ 
    node temp = x; 
    x = y; 
    y = temp; 
} 
    
node getmin(node harr[]) 
{ 
	return harr[0]; 
} 
 
void heapify(node a[],ll hsize,ll i) 
{ 
    ll l = 2*i + 1; 
    ll r = 2*i + 2; 
    ll min = i;
	 
    if (l < hsize && a[l].val < a[i].val) 
        min = l; 
    if (r < hsize && a[r].val < a[min].val) 
        min = r; 
    if (min != i) 
	{ 
        swap(a[i], a[min]); 
        heapify(a,hsize,min); 
    } 
} 
    
void buildheap(node a[],ll hsize) 
{  
    for (ll i = (hsize - 1) / 2; i >= 0; i--) 
        heapify(a,hsize,i); 
}
	
void replacemin(node a[],ll hsize,node x) 
{ 
    a[0] = x; 
    heapify(a,hsize,0); 
} 

ll merger(ll k,FILE* in)
{
	if(k<=0)
		return k;
	return merger(k/2,in);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void swap(ll &a, ll &b) 
{ 
    ll t = a; 
    a = b; 
    b = t; 
} 

ll partition(ll a[], ll l, ll r) 
{ 
    ll pivot = a[r];    
    ll i = (l - 1); 
  
    for (ll j = l; j <= r - 1; j++) 
    { 
        if (a[j] <= pivot) 
        { 
            i++;    
            swap(a[i], a[j]); 
        } 
    } 
    swap(a[i + 1], a[r]); 
    return (i + 1); 
} 

void qsort(ll a[], ll l, ll r) 
{ 
    if (l < r) 
    { 
        ll part = partition(a, l, r); 
        qsort(a, l, part - 1); 
        qsort(a, part + 1, r); 
    } 
}  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void mergefiles(char* outfile, ll n, ll k) 
{ 
    FILE* in[k]; 
    for (ll i = 0; i < k; i++) 
	{ 
        char *tempfile; 
  		string s = to_string(i);
		tempfile = (char*)s.c_str();
        in[i] = fopen(tempfile, "r");		 
    }
    
	//merger(k,in[0]);
    FILE* out = fopen(outfile, "w");       
    node harr[k]; 
    ll i; 
    for (i = 0; i < k; i++) 
	{ 
        if (fscanf(in[i], "%lld," , &harr[i].val) == EOF) 			//input file is empty  
            break; 
  		
        harr[i].i = i; 
    } 
	
    buildheap(harr, i); 
  
    ll count = 0; 
  
  	cout<<"\nfiles merged completely-> ";
	long long c = 0;
    while (count != k) 
	{ 
        node root = getmin(harr); 
        fprintf(out, "%lld,", root.val); 
  
        if (fscanf(in[root.i], "%lld,",   &root.val)  == EOF)
		{ 
			cout<<root.i<<" ";
            root.val = LLONG_MAX; 
            count++;           
        } 
  
        replacemin(harr,k,root); 				//add next element of file
    } 
    
	cout<<"\n\n";
	 
    for (ll i = 0; i < k; i++) 		//close input files 
        fclose(in[i]); 
  
    fclose(out); 					//close output file
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void createparts(char* infile, ll part_size, ll k) 
{ 
    FILE* in = fopen(infile, "r"); 
  
    FILE *out[k]; 			    //temp output files 
    char *tempfile;
	merger(k,in);	 
    for (ll i = 0; i < k; i++) 
	{ 
  		string s = to_string(i);
		tempfile = (char*)s.c_str();
		 
        out[i] = fopen(tempfile, "w"); 	// create files
    }
	
    ll* arr = new ll[part_size]; 			//array to sort numbers 
  	//vector<ll> arr(part_size);
    bool endfile = true; 
    ll op_num = 0; 
  	
  	cout<<"generating temp file-> ";
  	
    ll i; 
    while (endfile) 
	{ 
        for (i = 0; i < part_size; i++) 
		{ 
            if (fscanf(in, "%lld,", &arr[i]) == EOF) 
			{ 
                endfile = false; 
                break; 
            } 
        } 
          
        qsort(arr, 0, i-1); 						// sort using quick sort 
          
        for (ll j = 0; j < i; j++) 					// store sorted arr to temp file
            fprintf(out[op_num], "%lld,", arr[j]); 
  
        op_num++;
		cout<<op_num<<" "; 
    } 
  	cout<<"\n";
  	
    // close input and output files 
    for (ll i = 0; i < k; i++) 
        fclose(out[i]); 
  	
  	delete[] arr;
    fclose(in); 
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void deletetempfiles(ll k)
{	
	cout<<"deleting temp files -> ";
	for(ll i = 0;i<k;i++)				//leave 5 files to check output
	{
		string istr = to_string(i);
		const char *fname = istr.c_str();
		
		if( remove( fname ) != 0 )
	    	perror( "Error deleting file" );
		cout<<fname<<" ";	    	
    }
    cout<<"\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

int main(int argc, char** argv) 
{   

	//give parameters as   input.txt output.txt   in execute options
	
    ll k = 200; 					// No. of Partitions of input file.     
    ll part_size = 5*100000 ; 			// The size of each partition (number of zeroes = (number of zeores in input - 3)) 
  
    char *in = argv[1]; 
    char *out = argv[2]; 
    
    createparts(in, part_size, k);    	// create sorted parts
    
	mergefiles(out, part_size, k); 		// K-way merging 
	
	deletetempfiles(k);
	
  
    return 0; 
} 
