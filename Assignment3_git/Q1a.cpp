#include <bits/stdc++.h>
using namespace std;
#define ll long long int

typedef struct suffixinfo 
{ 
    ll index;
    ll rank; 
    ll nextrank;
}suffix; 
/////////////////////////////////////////////////////////////////////////////////////////////
bool comparator(suffix a,  suffix b) 
{
	if(a.rank == b.rank)
	{
		if(a.nextrank < b.nextrank)
			return true;
		else
			return false;
	}
	else
	{
		if(a.rank < b.rank)
			return true;
		else
			return false;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
ll * build_suffix_arr(string str) 
{ 
	ll n = str.size();
	
    suffix suff[n]; 
  	
  	//initialize suffix array
    for (ll i = 0; i < n; i++) 
    { 
        suff[i].index = i; 
        suff[i].rank = str[i] - 'a';
		if((i+1) < n)
			suff[i].nextrank = str[i + 1] - 'a';
		else
			suff[i].nextrank = -1;
    } 
  
    sort(suff, suff+n, comparator); 				// nlogn time
  
    ll ind[n];  	// to get rank of (index + k)
    
    for (ll k = 4; k < 2*n; k = k*2) 
    { 
    /*
    	for(ll i = 0;i<n;i++)
        	cout<<suff[i].index<<" ";
        cout<<"\n";
    */    
        
        //initialize first suffix 
        ll count_rank = 0; 
        ll prev_rank = suff[0].rank; 
        
        suff[0].rank = 0; 
        ind[suff[0].index] = 0; 
  		
  		//for remaining suffix
        for (ll i = 1; i < n; i++) 
        { 	
        	if ((suff[i].rank == prev_rank) && (suff[i].nextrank == suff[i-1].nextrank)) 		//same rank and nextrank (no increment)
            { 
				prev_rank = suff[i].rank; 
				suff[i].rank = count_rank; 
			} 
			else																				// increment rank by 1
			{ 
				prev_rank = suff[i].rank; 
				suff[i].rank = ++count_rank; 
			}
            ind[suff[i].index] = i; 
        } 
  
        // find next rank 
        for (ll i = 0; i < n; i++) 
        { 
            ll kindex = suff[i].index + k/2;
			if(kindex < n)
				suff[i].nextrank = suff[ind[kindex]].rank;
            else
            	suff[i].nextrank = -1;
        } 
          
        sort(suff, suff+n, comparator); 	// Sort by first k characters 
    
        
    } 
  
    // Store indexes for suffix array
    ll *suffixarray = new ll[n]; 
    for (ll i = 0; i < n; i++) 
        suffixarray[i] = suff[i].index; 
  
    return  suffixarray; 
} 

/////////////////////////////////////////////////////////////////////////////////////////////
string min_lexico_rot(string in)
{
	ll orig_len = in.size();
	
	string s= in + in;
	string suffix = "";
	vector<pair<string,ll>> suffixarr;
	for(ll i=s.size()-1 ; i>=0;i--)
	{
		suffix = s[i] + suffix;
		suffixarr.push_back({suffix,i});
	}
	
	/*
	sort(suffixarr.begin(),suffixarr.end());			//build suffix array
	
	for(ll i=0;i<suffixarr.size();i++)
		cout<<suffixarr[i].first<<" "<<suffixarr[i].second<<"\n";			//suffix,index
	*/
	
	ll *suffixarray  = build_suffix_arr(s);
	
	ll rot_index ;
	for(ll i=0;i<s.size();i++)
	{
		if(suffixarray[i] < orig_len)
		{	
			rot_index = suffixarray[i];
			break;
		}
	}
	
	string minstr = "";
	for(ll i= 0 ;i<orig_len ;i++)
		minstr+= in[(i + rot_index)%orig_len];
	return minstr;
}
/////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	string s;
	ll k;
	cin>>s;
	
	/*
	ll *suffixarray  = build_suffix_arr(s);
	
	for(ll i=0;i<s.size();i++)
		cout<<suffixarray[i]<<" ";
	*/
	
	cout<<"minimum lexicographic rotation-> "<<min_lexico_rot(s)<<"\n";
	
	return 0;
}

