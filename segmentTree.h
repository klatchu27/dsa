#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

class segmentTree {

public:
    
    long long int n,Default,qs,qe,ind,val;
    vector<long long int> a;
    vector<long long int> ST;
    long long int(*func)(long long int,long long int);

    segmentTree(vector<long long int> &b,long long int(*fun)(long long int,long long int),long long int def){
        n = b.size();
        a = b;
        ST.resize(4*n);

        Default = def;
        func = fun;
        constructSTUtil(0,n-1,0);
    }

    long long int queryST(long long int query_start,long long int query_end){            
        qs = max(query_start,0ll);
        qe = min(query_end,n-1);        
        return querySTUtil(0,n-1,0);
    }

    void updateST(long long int index,long long int value){
        ind = index;
        val = value;
        updateSTUtil(0,n-1,0);
    }

    void constructSTUtil(long long int ss,long long int se,long long int si){
        if(ss == se){
            ST[si] = a[ss];
            return;  
        }
        int mid = (ss + se)/2;
        int lix = 2*si + 1;
        int rix = 2*si + 2;
        constructSTUtil(ss,mid,lix);
        constructSTUtil(mid+1,se,rix);
        ST[si] = func(ST[lix],ST[rix]); 
    }

    void updateSTUtil(long long int ss,long long int se,long long int si){
        if(ind < ss || ind > se) return;
        if(ss == se){ ST[si] = val;a[ind] = val;return;}    
        int mid = (ss + se)/2;
        int lix = 2*si + 1;
        int rix = 2*si + 2;
        updateSTUtil(ss,mid,lix);
        updateSTUtil(mid+1,se,rix);
        ST[si] = func(ST[lix],ST[rix]);   
    }

    long long int querySTUtil(long long int ss,long long int se,long long int si){
        if (qe < ss || qs > se) 
            return Default;
        if (qs <= ss && qe >= se) return ST[si];
        int mid = (ss + se)/2;
        int lix = 2*si + 1;
        int rix = 2*si + 2;
        return func(querySTUtil(ss,mid,lix), querySTUtil(mid+1,se,rix));
    }

};