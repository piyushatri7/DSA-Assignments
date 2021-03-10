#include <bits/stdc++.h>
using namespace std;
#define ll long long int

/////////////////////////////////////////////////////////////////////////////////////////////
ll k_len_substr(string s,ll k)
{
	ll orig_len = s.size();
	
	string suffix = "";
	vector<pair<string,ll>> suffixarr;
	for(ll i=s.size()-1 ; i>=0;i--)
	{
		suffix = s[i] + suffix;
		suffixarr.push_back({suffix,i});
	}
	
	
	sort(suffixarr.begin(),suffixarr.end());			//build suffix array
	/*
	for(ll i=0;i<suffixarr.size();i++)
		cout<<suffixarr[i].first<<" "<<suffixarr[i].second<<"\n";
	*/
	
	
	ll min_len= -1;		
	for(ll i = 0;i<(s.size() - k + 1);i++)
	{
		string s1 = suffixarr[i].first;
		string s2 = suffixarr[i+k-1].first;
		ll x = min(s1.size(),s2.size());
		
		ll j=0;
		while(j<x)
		{
			if(s1[j]!=s2[j])
				break;
			else
				j++;
		}
		min_len = max(min_len,j);
		
	}
	return min_len;
}
/////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	string s;
	ll k;
	cin>>s;
	
	cin>>k;
	cout<<"length of longest substring that appears in the text at least K times-> "<<k_len_substr(s,k)<<"\n";
	return 0;
}

