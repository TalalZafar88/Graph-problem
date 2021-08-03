#include <iostream>
#include <list>
using namespace std;

class helpergraph {
    int V;
    list<int> *adj;

public:

    helpergraph(int V) {
        this->V = V;
        adj = new list<int>[V];
    }

    void addEdge1(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
    void removeEdge1(int v, int w) {
        adj[v].pop_back();
        adj[w].pop_back();
    }


    bool helpcycle(int v, bool visited[], int parent) {

        visited[v] = true;

        list<int>::iterator i;

        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {

            if (!visited[*i])
            {
                if (helpcycle(*i, visited, v))
                    return true;
            }

            else if (*i != parent)
                return true;
        }
        return false;
    }
    
    bool cyclecheck() {

        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }

        for (int u = 0; u < V; u++)
        {
            if (!visited[u])
                if (helpcycle(u, visited, -1))
                    return true;

        }

        return false;
    }

};
class list1{
public:
    int weight;
    int src;
    int des;

 void add(int s,int d,int w){
        weight=w;
        src=s;
        des=d;

    }

};

class Graph {

private:
    int V;
    int **array;

public:

    Graph(){

    }
    void make(int V)
    {

        this->V=V;
        array=new int*[V];
        for(int i=0; i<V; ++i)
        {
            array[i]=new int[V];

        }

        for(int i=0; i<V; ++i)
        {
            for(int j=0; j<V; ++j)
            {

                if(i==j)
                    array[i][j]=0;
                else
                    array[i][j]=-99;

            }
        }
        
    }

    void addEdge(int src, int dest,int bandwidth)
    {

        array[src][dest]=bandwidth;
        array[dest][src]=bandwidth;

    }
    void removeEdge(int src, int dest)
    {

        array[src][dest]=-99;
        array[dest][src]=-99;

    }
    void swaping(list1 *a, list1 *b) {
        list1 t = *a;
        *a = *b;
        *b = t;
    }

    void printGraph()
    {

        for(int i=0;i<V; ++i)
        {
            for(int j=0; j<V; ++j)
            {
                cout<<array[i][j]<<" ";
            }
                cout<<endl;
        }

    }

    bool possibility(){

        bool flag=false;

        for(int i = 0; i < V; i++)
        {
            for (int j = i + 1; j < V; j++)
            {
                for (int k = j + 1; k < V; k++)
                {
                    if (min(array[i][j], array[j][k]) > array[i][k] || min(array[i][k], array[j][k]) > array[i][j] || min(array[i][j], array[i][k]) > array[j][k])
                        flag=true;
                }
            }

        }

        return flag;
        
    }
   
    int partition(list1 *array, int first, int last) {

        list1 pivot = array[last];
        int i = (first - 1);

        for (int j = first; j < last; j++)
        {
            if (array[j].weight > pivot.weight) {
                i++;
                swaping(&array[i], &array[j]);
            }
        }

        swaping(&array[i + 1], &array[last]);

        return (i + 1);
    }

    void quick(list1 *array, int first, int last) {
        if (first < last) {

            int pi = partition(array, first, last);
            
            quick(array, first, pi - 1);
            
            quick(array, pi + 1, last);
        }
    }

    void kruskal(list1 * egdes,int s)
    {
       
        quick(egdes,0,s-1);
        
        Graph t;
        t.make(V);
        helpergraph b(V);
        int z=V-1;
        int y=0;
        bool f=false;

        for(int i=0; i<s; ++i)
        {


                t.addEdge(egdes[i].src, egdes[i].des, egdes[i].weight);
                b.addEdge1(egdes[i].src, egdes[i].des);
                if(b.cyclecheck()){
                    t.removeEdge(egdes[i].src, egdes[i].des);
                    b.removeEdge1(egdes[i].src, egdes[i].des);
                    f=true;

                }

                y++;

                if(f)
                {

                    y--;
                    f=false;
                }

                if(z==y)
                {
                    break;
                }



        }

            cout << (t.V - 1) << endl;
            for (int i = 0; i < t.V; ++i)
            {
                for (int j = i+1; j < t.V; ++j)
                {


                    if (t.array[i][j] != -99)
                    {


                        cout << i << " " << j << " " << t.array[i][j] << endl;


                    }


                }

            }


    }

};

int main() {

    int cases;
    int computers;
    int k = 0;

    cin>>cases;

    int v = 0;
    Graph *a = new Graph[cases];

    for(int i=0 ; i<cases; ++i){
        cin >> computers;
        a[k].make(computers);
        int s = ((computers * computers) - computers);
        s = s / 2;
        list1 *egdes = new list1[s];
        int z = 0;
        for (int i = 0; i < computers; ++i) {
            for (int j = 0; j < computers; ++j) {

                cin >> v;
                a[k].addEdge(i, j, v);
                if (j > i) {
                    egdes[z].add(i, j, v);
                    z++;
                }

            }

        }

        k++;

        cout << "Case#" << i + 1 << ": ";
        if (a[i].possibility())
        {
            cout << "Impossible" << endl;
        } else {
            a[i].kruskal(egdes,z);
        }

        
    }
    return 0;

}