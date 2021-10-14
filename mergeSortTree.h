#include<vector>
#include<iostream>
#include<algorithm>

#define all(x) x.begin(),x.end()
typedef long long int ll;
using namespace std;

class mergeSortTree
{
    public:

    long long int n,qs,qe,val;
    vector<long long int> a;
    vector<vector<long long int>> mst;

    mergeSortTree(vector<long long int> &b)
    {
        n = b.size();
        mst.resize(4*n);
        a = b;
        constructMST(0,n-1,0);
    }

    long long int queryMST(long long int query_start,long long query_end,long long int value,long long int query_type = 1)
    {
        qs = query_start;
        qe = query_end;
        val = value;
        switch(query_type)
        {
            case 1: return queryMST1(0,n-1,0);break;
            case 2: return queryMST2(0,n-1,0);break;
            default: cout<<"wrong type\n";return 0;
        }
    }

    void constructMST(long long int ss,long long int se,long long int si)
    {
        if(ss == se){mst[si].push_back(a[ss]);return;}
        ll mid = (ss + se)/2;
        ll lix = 2*si + 1;
        ll rix = 2*si + 2;
        constructMST(ss,mid,lix);
        constructMST(mid+1,se,rix);

        mst[si].resize(mst[lix].size()+mst[rix].size());
        merge(mst[lix].begin(),mst[lix].end(),mst[rix].begin(),mst[rix].end(),mst[si].begin()); 
    }

    //returns no of elements in range [qs,qe] which are "striclty less" than val
    ll queryMST1(long long int ss,long long int se,long long int si)
    {
        if (qe < ss || qs > se) return 0;
        if (qs <= ss && qe >= se)
        {
            return lower_bound(mst[si].begin(),mst[si].end(),val)-mst[si].begin();
        }
        int mid = (ss + se)/2;
        int lix = 2*si + 1;
        int rix = 2*si + 2;
        return (queryMST1(ss,mid,lix)+ queryMST1(mid+1,se,rix));
    }

    //returns no of elements in range [qs,qe] which are "less than or equal" val
    ll queryMST2(long long int ss,long long int se,long long int si)
    {
        if (qe < ss || qs > se) return 0;
        if (qs <= ss && qe >= se)
        {
            return upper_bound(mst[si].begin(),mst[si].end(),val)-mst[si].begin();
        }
        int mid = (ss + se)/2;
        int lix = 2*si + 1;
        int rix = 2*si + 2;
        return (queryMST2(ss,mid,lix)+ queryMST2(mid+1,se,rix));
    }

};
//nothing