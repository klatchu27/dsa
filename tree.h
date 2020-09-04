		
    	
class Tree
{
public:
    // primary and absolute essentials
    int n;
    int diameter;
    vector<set<long long int>> adj;

    // parent and depth info
    vector<long long int> tree_par;
    vector<long long int> depth;
    
    //strictly for lca
    vector<vector<long long int>> preprocess_lca;

    //strictly for r=euler path in which every node is repeated exactly 2 times
    vector<long long int> euler_path1;
    vector<long long int> first_occurance1;
    vector<long long int> last_occurance1;

    //strictly for r=euler path in which every node is repeated 2 times after every child
    vector<long long int> euler_path2;
    vector<long long int> first_occurance2;
    vector<long long int> last_occurance2;

    // if node has value associated with it
    vector<long long int> node_value;

    Tree(int m)
    {
        //essentials
        n = m;
        adj.resize(n);
        get_edge();
        find_parent_depth(0);                                                  
        first_occurance1.assign(n,0);
        last_occurance1.assign(n,0);
        first_occurance2.assign(n,0);
        last_occurance2.assign(n,-1);
        diameter = -1;
        node_value.assign(n,0);
        
        //non essentials
        preprocess_lca_fn();
        euler_path_fn(0);        
        #find_diameter();
        
    }

    void get_edge()
    {
        ll x,y;
        for(int i=0;i<n-1;i++)
        {
            cin>>x>>y;
            adj[x-1].insert(y-1);
            adj[y-1].insert(x-1);
        }
    }

    void preprocess_lca_fn()
    {
        int logn = (int)ceil(log2(n));
        preprocess_lca.assign(n,vector<long long int> (logn+1,-1));



        for(int i=0;i<n;i++)
            preprocess_lca[i][0] = tree_par[i];
        
        for(int j=1;j<=logn;j++)
        {
            for(int i=0;i<n;i++)
            {
                int x = preprocess_lca[i][j-1];
                if(x!=-1)
                    preprocess_lca[i][j] = preprocess_lca[x][j-1];
            }
        }
    }

    int dist(int u,int v)
    {
        return depth[u]+depth[v]-2*depth[lca(u,v)];
    }

    int lca(int u,int v)
    {
        int logn = (int)ceil(log2(n));
        
        if(depth[u]>depth[v]) swap(u,v);         

        if(depth[u]!=depth[v])
        {
            for( int j=logn; j>=0; j-- )
            {          
                if(preprocess_lca[v][j]!=-1 && depth[ preprocess_lca[v][j] ]>=depth[u])                
                    v = preprocess_lca[v][j];    
            }                
        }

        if(u==v) return u;
            
        for(int i=logn;i>=0;i--)
        {
            if(preprocess_lca[u][i]!=preprocess_lca[v][i])
                {u = preprocess_lca[u][i];v = preprocess_lca[v][i];}
        }

        return tree_par[u];
    }

    void find_parent_depth(int root=0)
    {
        
        tree_par.assign(n,-1);
        depth.assign(n,0);

        queue<long long int> q;
        q.push(root);
        while(!q.empty())
        {
            long long int top = q.front();
            q.pop();

            for(auto i: adj[top])
            {
                if(i!=tree_par[top])
                {
                    tree_par[i]=top;
                    depth[i] = depth[top]+1;
                    q.push(i);
                }
            }
        }

    }

    void find_diameter()
    {
        diameter = max_distance(max_distance(0).first).second;
    }

    pair<int,long long int> max_distance(int root)
    {
        pair<int,long long int> last;

        vector<int> vis(n,0);
        queue<pair<int,long long int>> q;
        q.push(make_pair(root,0));
        vis[root]=1;

        while(!q.empty())
        {
            pair<int,long long int> top = q.front();            
            q.pop();

            last = top;

            for(auto i: adj[top.first])
            {
                if(vis[i]==0)
                {     
                    vis[i]=1;               
                    q.push(make_pair(i,top.second+1));
                }
            }
        }
        return last;
    }

    void euler_path_fn(int root)
    {
        first_occurance1[root] = euler_path1.size();
        euler_path1.push_back(root);

        first_occurance2[root] = euler_path2.size();
        euler_path2.push_back(root);

        for(auto i: adj[root])
        {
            if(i!=tree_par[root])
            {
                euler_path_fn(i);
                last_occurance2[root] = euler_path2.size();
                euler_path2.push_back(root);
            }
           
        }
        if(last_occurance2[root]==-1)
            last_occurance2[root] = first_occurance2[root];

        last_occurance1[root] = euler_path1.size();
        euler_path1.push_back(root);
    }

};
