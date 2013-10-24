#include "graph.h"
#include <fstream>
int main()
{
    Graph<int, int> a;
    fstream fin;
    fin.open("in", ios::in);
    fin>>a;
   /* a.addNode(6);
    a.addNode(7);
    a.addNode(13);
    a.addEdge(0,1,2);
    a.addEdge(0,2,5);
    a.addEdge(0,2,6);
    a.addEdge(2,0,5);
    a.addNode(9);
    //a.removeNode(1);
    a.addEdge(1,3,9);
    a.removeEdge(3);
    */
    fin.close();
    cout<<a<<endl;
    /*vector<int> res=a.Dijkstra(0, 999999);
    for (auto i : res)
        cout<<i<<" ";
    cout<<endl;
    */

    /*Graph<int, int> b=a.BFS();
    cout<<b<<endl;*/

}
