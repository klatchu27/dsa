// #include<vector>
// #include<iostream>
// #include<algorithm>
// using namespace std;

/*
long long int Sum(long long int x,long long y)
{
    return x+y;     
}
long long int Min(long long int x,long long y)
{
    return x<y? x:y;     
}
long long int Max(long long int x,long long y)
{
    return x>y? x:y;     
}
*/
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

/*
Sample code to illustrate how to use the segmentTree class

int main()
{
    vector<long long int> a ={1,2,3,4,5};

    //creating a segmentTree object requires 3 arguments namely a vector , function to perform , default value incase of no overlap with segment
    //for a min segment tree pass Min() and +infinity eg: segmentTree stmin(a,Min,+LLONG_MAX); 
    //for a max segment tree pass Min() and +infinity eg: segmentTree stmax(a,Max,LLONG_MIN); 
    //below we create a segment tree to find sum of a segment and hence we pass Sum() and 0 as second and third argument 

    segmentTree stsum(a,Sum,0); //takes O(4*n)
    
    //To do query on a segment , just pass the query start index and query end index
    cout<<stsum.queryST(2,3)<<'\n'; //takes O(log(4*n))

    //To update a value just pass the index and the new value at that index as arguments
    stsum.updateST(2,100);  //takes O(log(4*n))

    cout<<stsum.queryST(1,3);   //takes O(log(4*n))
}
*/