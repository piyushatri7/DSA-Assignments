#include <bits/stdc++.h>
using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////

bool checksmall(string s1,string s2)
{
    if(s1.size() < s2.size())
        return true;
    else if(s1.size() > s2.size())
        return false;
    else
    {
        for(int i=0;i<s1.size();i++)
        {    if(s1[i]<s2[i])
                return true;
            if(s1[i]>s2[i])
                return false;
        }
        return false;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////

string multiply(string s1,string s2)
{
    if(checksmall(s1,s2))        //make s2 larger for better chache performance
    {
        string s3=s1;
        s1=s2;
        s2=s3;
    }
    
    int n1=s1.size();
    int n2=s2.size();
    int f1=0,f2=0;
    
    f1=(s1[0]=='-')?1:0;        //check for negative nos
    f2=(s2[0]=='-')?1:0;
    
    int val[n1+n2]={0},mul;
    
    for(int i=n1-1;i>=f1;i--)
    {
        for(int j=n2-1;j>=f2;j--)
        {
            mul = (s1[i]-'0') * (s2[j]-'0') + val[i+j+1];        // d1*d2 + previous carry
            val[i+j+1]=mul%10;                                    //digit
            val[i+j]=val[i+j] + mul/10;                                    //carry
        }
    }
    
    int i,j;
    string s;
    for(i=0;i<(n1+n2) && val[i]==0 ;i++)    //move past leading zero
        ;        
    
    if(i==n1+n2)                //ans == 0
        s.push_back('0');
    else
    {    
        if(f1^f2)                //if one of the numbers is negative
            s.push_back('-');
        for(; i<n1+n2 ; i++)
            s.push_back(val[i] + '0');
    }
    return s;
}
///////////////////////////////////////////////////////////////////////////////////////////

string divby2(string s) 
{ 
    
    vector<int> v; 
    string res;
    int mod=0,q;
    int f=0,i,j;
    
    f=(s[0]=='-')?1:0;        //check for negative num

    for (i=f; i<s.size();i++) 
    { 
        mod = mod*10 + (s[i] - '0'); 
        q = mod/2; 
        v.push_back(q); 
        mod = mod%2;         
    } 
    
    for(i=0;i<v.size() && v[i]==0 ;i++)    //move past leading zeros
        ;        
    
    if(i==v.size())                //ans == 0
        res.push_back('0');
    else
    {    
        if(f)                //if one of the numbers is negative
            res.push_back('-');
        for(; i<v.size(); i++)
            res.push_back(v[i] + '0');
    }
    return res;
} 
///////////////////////////////////////////////////////////////////////////////////////////

void revstr(string &s)        //reverse string
{
    int n=s.size();
    int i=0,j=n-1;
    while(i<j)
    {
        char t=s[i];
        s[i]=s[j];
        s[j]=t;
        i++;
        j--;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////

string absdiff(string s1,string s2)            //absolute difference
{
    if(s1==s2)                //same string
        return "0";
    if(s1=="0")                //one of the strings is 0
        return s2;
    if(s2=="0")
        return s1;
    
    string res;
    if(checksmall(s1,s2))    //put larger number in s1
    {
        string s3=s1;
        s1=s2;
        s2=s3;
    }
    
    //cout<<s1<<"\n"<<s2<<"\n";
    int n1=s1.size(),n2=s2.size(),borrow=0,diff;
    
    revstr(s1);
    revstr(s2);
    //cout<<s1<<"\n"<<s2<<"\n";
    
    for(int i=0;i<n2;i++)                
    {
        diff=(s1[i]-'0') - (s2[i]-'0') - borrow;
        if(diff<0)
        {
            diff+=10;
            borrow=1;
        }
        else
            borrow=0;
        
        res.push_back(diff + '0');
    }
    
    for(int i=n2;i<n1 ;i++)        //remainig digits
    {
        diff=s1[i] - '0' - borrow;
        if(diff<0)
        {
            diff+=10;
            borrow=1;
        }
        else
            borrow=0;
        
        res.push_back(diff + '0');
    }
    
    for(int i=res.size()-1;i>=1;i--)            //remove leading zero if any
        if(res[i]=='0')
            res.pop_back();
        else
            break;
    
    revstr(res);
    return res;
}
///////////////////////////////////////////////////////////////////////////////////////////

string fact(unsigned long long int n)
{
    if(n<0)
    {
        cout<<"invalid input";
        exit(0);
    }
    if(n==0 || n==1)
        return "1";
    
    string s1="1",s2;
    for(unsigned long long int i=2;i<=n;i++)
    {
        s2=to_string(i);
        s1=multiply(s1,s2);
    }
    
    //cout<<s1.size()<<"\n";
    return s1;    
    
}
///////////////////////////////////////////////////////////////////////////////////////////

string fastexp(string a,string b)
{
    if(b=="0")
        return "1";
    if(b=="1")
        return a;
    
    string bby2=divby2(b);            //divide exp by 2 
    
    string t=fastexp(a,bby2);		//[MODIFIED AFTER SUBMISSION] store function call
    
    if(( b[b.size()-1] - '0') % 2)
            return  multiply(a , multiply( t, t ) );
    else
        return multiply( t, t );
    
}
///////////////////////////////////////////////////////////////////////////////////////////

string gcd_by_subtraction(string a, string b) 
{ 
    while(a != b)  
    {  
        if(checksmall(a,b))
        {
            b=absdiff(b,a);
            //cout<<b<<" ";
        }
        else
        {
            a=absdiff(a,b);
            //cout<<a<<" ";
        }  
        //cout<<"a ";    
    }  
    return a;  
} 
///////////////////////////////////////////////////////////////////////////////////////////

string mod_by_sub(string s1,string s2)
{
    //cout<<s1<<" "<<s2<<"\n";    
    while(!checksmall(s1,s2))
        s1=absdiff(s1,s2);

    return s1;
}
///////////////////////////////////////////////////////////////////////////////////////////

string long_modulous(string s1,string s2)
{
    if(checksmall(s1,s2))            //s1 is smaller than s2
        return s1;
    
    string mod="";
    for(int i=0;i<s1.size();i++)
    {
        /*
        if(mod.size() < s2.size())        
            mod.push_back(s1[i]);
        else if(checksmall(mod,s2))
            mod.push_back(s1[i]);
        else
        {    
            mod=mod_by_sub(mod,s2);
            mod.push_back(s1[i]);
        }
        */
        
        if(!checksmall(mod,s2))
            mod=mod_by_sub(mod,s2);
            
        mod.push_back(s1[i]);
        
        //cout<<mod<<" "<<mod.size()<<"\n";
        
        if(mod=="0")        // in case mod becomes zero during calculation
            mod="";
    }
    
    mod=mod_by_sub(mod,s2);        //if last operation was push_back
    return mod;
}
///////////////////////////////////////////////////////////////////////////////////////////

string euclid_gcd(string a, string b)
{
    if (a[0] == '0')
    {    
        int i;
        for( i=0;i<a.size();i++)        //check if a is just a string of zeroes
            if(a[i]!='0')
                 break;
                 
        if(i==a.size())
            return b;
    }
    //cout<<a<<"\n" ;
    return euclid_gcd(long_modulous(b,a), a); 
} 
///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
   
    //////////////Driver code//////////////////////////////////////////////////
    
    string s1,s2;
    int q,option;
    cin>>q;
    while(q--)
    {
        cin>>option;
        
        if(option == 1)
        {
            cin>>s1>>s2;
            cout<<fastexp(s1,s2)<<"\n";
        }
        else if(option==2)
        {
            cin>>s1>>s2;
            cout<<euclid_gcd(s1,s2)<<"\n";
        }
        else
        {
            unsigned long long int n;
            cin>>n;
            cout<<fact(n)<<"\n";
        }
    }
    return 0;
}

