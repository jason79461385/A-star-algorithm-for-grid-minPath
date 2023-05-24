#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x;
    int y;

    Point(int xVal, int yVal) : x(xVal), y(yVal) {}
};

struct Node {
    Point position;
    int g;
    int h;
    int f;
    Node* parent;

    Node(Point pos, int gVal, int hVal, Node* parentPtr)
        : position(pos), g(gVal), h(hVal), f(gVal + hVal), parent(parentPtr) {}
};

vector<Point> findShortestPath(vector<vector<int>>& grid, Point start, Point goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<int>> gValues(rows, vector<int>(cols, numeric_limits<int>::max()));
    vector<vector<int>> hValues(rows, vector<int>(cols, 0));

    auto compare = [](Node* a, Node* b) {
        return a->f > b->f;
    };
    priority_queue<Node*, vector<Node*>, decltype(compare)> openList(compare);

    Node* startNode = new Node(start, 0, 0, nullptr);
    openList.push(startNode);
    gValues[start.x][start.y] = 0;

    while (!openList.empty()) {
        Node* currentNode = openList.top();
        openList.pop();

        Point currentPosition = currentNode->position;

        if (currentPosition.x == goal.x && currentPosition.y == goal.y) {
            // Reached the goal, construct the shortest path
            vector<Point> shortestPath;
            Node* pathNode = currentNode;
            while (pathNode != nullptr) {
                shortestPath.push_back(pathNode->position);
                pathNode = pathNode->parent;
            }
            reverse(shortestPath.begin(), shortestPath.end());
            return shortestPath;
        }

        if (visited[currentPosition.x][currentPosition.y]) {
            continue;
        }

        visited[currentPosition.x][currentPosition.y] = true;

        vector<Point> neighbors;
        neighbors.push_back({ currentPosition.x - 1, currentPosition.y });
        neighbors.push_back({ currentPosition.x + 1, currentPosition.y });
        neighbors.push_back({ currentPosition.x, currentPosition.y - 1 });
        neighbors.push_back({ currentPosition.x, currentPosition.y + 1 });

        for (const Point& neighbor : neighbors) {
            int nx = neighbor.x;
            int ny = neighbor.y;

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] >= 0) {
                int ng = currentNode->g + grid[nx][ny];
                int nh = abs(nx - goal.x) + abs(ny - goal.y);
                int nf = ng + nh;

                if (ng < gValues[nx][ny]) {
                    gValues[nx][ny] = ng;
                    hValues[nx][ny] = nh;

                    Node* neighborNode = new Node(neighbor, ng, nh, currentNode);
                    openList.push(neighborNode);
                }
            }
        }
    }

    return vector<Point>();  // No path found
}
int main() {
    int n;
    cin>>n;
    vector<vector<int>> grid(n,vector<int>(n));
    for(int i = 0; i <n;i++)
	    for(int j = 0; j<n;j++)
		    cin>>grid[i][j];
	
    Point start = {0, 0};
    Point goal = {n-1, n-1};

    vector<Point> shortestPath = findShortestPath(grid, start, goal);

    if (shortestPath.empty()) {
        cout << "No path found." << endl;
    } else {
        cout << "Shortest path: ";
        for (const Point& point : shortestPath) {
            cout << "(" << point.x << "," << point.y << ") ";
        }
        cout << endl;
    }

    return 0;
}

