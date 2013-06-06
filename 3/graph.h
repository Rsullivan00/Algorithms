#include <vector>
#include <list>
#include <cassert>
#include <queue>
#include <algorithm>

class graph
{
public:
	// pre: none
	// post: creates a graph with nvertices vertices and 0 edges

	typedef std::list<int>::iterator iterator;
	typedef std::list<int>::const_iterator const_iterator;

	graph(int nvertices = 0)
	{ data = std::vector<std::list<int> >(nvertices);
	}

	// pre: none
	// post: returns the number of vertices in this graph
	int n() const
	{	
		return data.size();
	}

	// pre: 0 <= i, j < # of vertices
	// post: yes iff (i, j) is an edge

	bool is_edge(int i, int j) const
	{
		assert(i >= 0 && i < n() && j >= 0 && j < n());
		for (const_iterator x = data[i].begin(); x != data[i].end(); ++x)
			if (*x == j)
				return true;

		return false;
	}

	void add_edge(int i, int j)
	{
		assert(i >= 0 && i < n() && j >= 0 && j < n());

		if (is_edge(i, j))
			return;

		data[i].push_front(j);
		data[j].push_front(i);

	}

	// running time: O(n+m)

	int bfs1(int start, std::vector<int> & parent) 
	{
        bool color[n()];
		std::queue<int> q;
		int ans = 0;
		
		// initialization
		parent[start] = start;
        color[start] = true;
		q.push(start);

		while (!q.empty())
		{
			int u = q.front();	
			q.pop();
			++ans;

			for (const_iterator x = data[u].begin(); x != data[u].end(); ++x)
				if (parent[*x] == -1)
				{
					parent[*x] = u;
                    color[*x] = !color[u];
					q.push(*x);
				}
				else
                {
					if (parent[u] != *x)
						acyclic = false;
                    if (color[u] == color[*x])
                        bipartite = false;
                }
		}

		return ans;
	}

    void dfs1(int start, std::vector<int>& parent, std::vector<int>& first,
                std::vector<int>& last, int& time, std::vector<bool>& color)
    {
        //initialize
        first[start] = time++;

        for (const_iterator x = data[start].begin(); x != data[start].end(); ++x)
        {
            if (parent[*x] == -1)
            {
                parent[*x] = start;
                color[*x] = !color[start];
                dfs1(*x, parent, first, last, time, color);
            }
            else if (color[*x] == color[start])
                    bipartite = false;
        }

        last[start] = time++;
    }

    void dfs()
	{
		std::vector<int> parent(n(), -1);
		std::vector<int> first(n(), -1);
		std::vector<int> last(n(), -1);
		std::vector<bool> color(n());

		int time = 0;
		int ncc = 0;

		for (int start = 0; start < n(); ++start)
		{
			if (parent[start] == -1)
			{
				parent[start] = start;
                color[start] = true;
				dfs1(start, parent, first, last, time, color);
				++ncc;
			}
		}
	}
	

	// running time: O(n+m)

	bool is_connected() 
	{
		std::vector<int> parent(n(), -1);
		return (bfs1(0, parent) == n());
	}

	// running time: Theta(n+m)

	int cc() 
	{
		int ans = 0;
		std::vector<int> parent(n(), -1);
		for (int i = 0; i < n(); ++i)
			if (parent[i] == -1)
			{
				++ans;
				bfs1(i, parent);
			}

		return ans;
	}

	bool is_acyclic() 
	{
		acyclic = true;

		std::vector<int> parent(n(), -1);
		for (int i = 0; i < n(); ++i)
			if (parent[i] == -1)
				bfs1(i, parent);
	
		return acyclic;
	}

    bool is_bipartite()
    {
        bipartite = true;
        dfs();

        return bipartite;
    }

    //Returns the length of the shortest cycle. 
    //if the graph is acyclic, returns -1 for undefined.
    int girth()
    {
        if (is_acyclic())
            return -1;

        std::vector<int> parent(n(), -1);
        int minC = 2147483647;

        for (int i = 0; i < n(); ++i)
        {
            for (const_iterator j = data[i].begin(); j != data[i].end(); ++j)
            {
                remove_edge(i, *j);
                int d = distance(i, *j);
                if(d != -1)
                    minC = std::min(minC, d);
                add_edge(i, *j);
            }
        }
        return minC;
    }

    //Uses DFS to track the shortest distance between two vertices.
    //Returns -1 if no path exists.
 	int distance(int start, int end) 
	{
        std::vector<int> parent(n(), -1);
		std::queue<int> q;
		int d = 0;
		
		// initialization
		parent[start] = start;
		q.push(start);

		while (!q.empty())
		{
			int u = q.front();	
			q.pop();
            if(u == end)
                return d;
			++d;
            std::cout << u << std::endl;

			for (const_iterator x = data[u].begin(); x != data[u].end(); ++x)
				if (parent[*x] == -1)
				{
					parent[*x] = u;
					q.push(*x);
				}
		}

		return -1;
	}

    void remove_edge(int from, int to){
        assert(is_edge(from, to));
        data[from].remove(to);
        data[to].remove(from);
    }

    
/*
    std::vector<std::vector<int> > get_paths(int start, int end){
        std::vector<std::vector<int> > paths; 
        std::vector<int> parent(n(), -1);
        std::queue<int> q;
        parent[start] = start;
        q.push(start);
        int l = 0;

        while(!q.empty()){
            int v = q.front();
            q.pop();

            std::vector<int> p;
            p.push_back(v);
            for(const_iterator x = data[v].begin(); x != data[v].end(); ++x){
                if(parent[*x] == -1){
                    parent[*x] = v;
                    q.push(*x);
                    p.push_back(*x);
                    if(*x == end){
                        paths.push_back(p);
                        break;
                    }
                }
            }
        }

        return paths;
    }
*/
private:
	std::vector<std::list<int> > data;
	bool acyclic;
    bool bipartite;

};

std::ostream & operator << (std::ostream & os, const graph & g)
{
	int n = g.n();
	os << n << std::endl;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n; ++j)
			if (g.is_edge(i, j))
				os << "(" << i << ", " << j << ")" << " ";
	}
	return os;
}	

std::istream & operator >>(std::istream & is, graph & g)
{
	int n, i, j;
	is >> n;
	graph temp(n);
	while (is >> i && is >> j)
		temp.add_edge(i, j);

	g = temp;
	return is;
}

