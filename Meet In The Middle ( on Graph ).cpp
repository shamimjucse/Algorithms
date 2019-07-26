#include <bits/stdc++.h>
using namespace std;

/// Function to find minimum number ofswaps to make another permutation
int ShortestPath(int n, string start, string finish)
{
    unordered_map<string, bool> visited;
    unordered_map<string, int> dis;
    unordered_map<string, string> src;

    visited[start] = visited[finish] = true;
    dis[start] = dis[finish] = 0;
    src[start] = start;
    src[finish] = finish;

    queue<string> q;
    q.push(start);
    q.push(finish);

    while (!q.empty())
    {
        string u = q.front();
        q.pop();
        for (int i = 1; i < n; i++)///Adjacent list
        {
            string v = u;
            swap(v[i], v[i - 1]);
            if (!visited[v])
            {
                visited[v] = true;
                src[v] = src[u];// Make root of u and root of v equal
                dis[v] = dis[u] + 1;
                q.push(v);
            }
            /// If it is already visited and roots are different then answer is found
            else if (src[u] != src[v])
            {
                return dis[u] + dis[v] + 1;
            }
        }
    }
}
int main()
{
    string p1 = "1234", p2 = "4123";
    int n = p1.length();
    cout << ShortestPath(n, p1, p2);
    return 0;
}
/*
Given a permutation P = p1, p2, …., pn of first n natural numbers (1 ≤ n ≤ 10).
One can swap any two consecutive elements p(i) and p(i + 1) (1 ≤ i < n).
The task is to find the minimum number of swaps to change P to another
permutation P' = p'1, p’2, …., p’n.
*/
/**
 * Meet In The Middle : solution is similar to Dijkstra’s solution with some modifications.
 * 1. Let P be the start vertex and P' be the finish Vertex.
 * 2. Let both start and finish be roots. We start BFS from both the roots, start and finish at the same time but using only one queue.
 * 3. Push start and finish into queue’s back, visited [ start ] = visited [ finish ] = true.
 * 4. Let src [ u ] be the root of vertex u in BFS progression. So, src [ start ] = start and src [ finish ] = finish.
 * 5. Let dis [ u ] be the shortest distance from vertex u to it’s tree’s root. So dis [ start ] = dis [ finish ] = 0.
 * 6. While queue is not empty, pop() queue’s front which is vertex u then push() all vertices v which are adjacent with u and haven’t been
 *    visited yet (visited [ v ] = false) into queue’s back, then let dis [ v ] = dis [ u ] + 1, src [ v ] = src [ u ] and visited [ v ] = true.
 *    Especially, if v was visited and src [ v ] != src [ u ] then we can immediately return dis [ u ] + dis [ v ] + 1.
 */
