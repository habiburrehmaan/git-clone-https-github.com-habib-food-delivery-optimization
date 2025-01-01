#include <iostream>
#include <string>
using namespace std;

const int maxVertices = 100;
const int maxRest = 10;
const int maxOrders = 20;
const int maxRiders = 5;

struct Order {
    char name[50];
    int destination;
    int maxWeight;
    bool assigned;
};

struct Restaurant {
    char name[50];
    int location;
    Order* orders;
    int orderCount;
};

struct Rider {
    int currentLocVertex;
    int destinationtalWeight;
    bool available;
    int* path;
    int pathDist;
};

class GridGraph {
private:
    int** adjMatrix;
    int size;
    int* distances;
    int* predecessor;

public:
    GridGraph(int n) : size(n) {
        adjMatrix = new int* [maxVertices];
        for (int i = 0; i < maxVertices; ++i) {
            adjMatrix[i] = new int[maxVertices];
            for (int j = 0; j < maxVertices; ++j) {
                adjMatrix[i][j] = 0;
            }
        }
        distances = new int[maxVertices];
        predecessor = new int[maxVertices];
        createGraph();
    }

    ~GridGraph() {
        for (int i = 0; i < maxVertices; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
        delete[] distances;
        delete[] predecessor;
    }

    void createGraph() {
        for (int i = 0; i < size * size; i++) {
            if (i % size != size - 1) {
                adjMatrix[i][i + 1] = adjMatrix[i + 1][i] = 1;
            }
            if (i + size < size * size) {
                adjMatrix[i][i + size] = adjMatrix[i + size][i] = 1;
            }
        }
    }

    void bfs(int start) {
        for (int i = 0; i < maxVertices; ++i) {
            distances[i] = -1;
            predecessor[i] = -1;
        }
        distances[start] = 0;
        int queue[maxVertices], front = 0, rear = 0;
        queue[rear++] = start;

        while (front != rear) {
            int currentLoc = queue[front++];
            for (int i = 0; i < size * size; i++) {
                if (adjMatrix[currentLoc][i] == 1 && distances[i] == -1) {
                    distances[i] = distances[currentLoc] + 1;
                    predecessor[i] = currentLoc;
                    queue[rear++] = i;
                }
            }
        }
    }



    void printGraph() {
        cout << "Grid Layout Visualization:" << endl;
        for (int i = 0; i < size * size; i++) {
            cout << i + 1;
            if ((i + 1) % size != 0) {
                if (adjMatrix[i][i + 1] == 1) {
                    cout << " - ";
                } else {
                    cout << "   ";
                }
            }
            if (i % size == size - 1) {
                cout << endl;
                if (i + size < size * size) {
                    for (int j = 0; j < size; j++) {
                        if (adjMatrix[i - size + 1 + j][i + 1 + j] == 1) {
                            cout << "|   ";
                        } else {
                            cout << "    ";
                        }
                    }
                    cout << endl;
                }
            }
        }
        cout << endl;
    }
};


int main() {
    cout << "\t\t\tFood Delivery Routing Optimization" << endl << endl;
    int total_tc;
    cout << "Enter the total number of test cases for the program: ";
    cin >> total_tc;

    for (int t = 0; t < total_tc; ++t) {
        cout << "\n\t\t\t[Test Case #" << t + 1 << "]" << endl << endl;

        int maxGSize;
        cout << "Enter the the maximum Grid Size of Map: ";
        cin >> maxGSize;

        int N, I, R;
        cout << "Enter the size N of the NxN grid: ";
        cin >> N;

        if (N < 1 || N > maxGSize) {
            cout << "Invalid grid size. Please enter a value between 1 and " << maxGSize << "." << endl;
            continue;
        }

        GridGraph graph(N);

        graph.printGraph();


        Restaurant* restaurants = new Restaurant[maxRest];
        Rider* riders = new Rider[maxRiders];

        cout << "Enter the number of Riders(I): ";
        cin >> I; // Input number of riders
        cout << "Enter the number of Restaurants(R): ";
        cin >> R; // Input number of restaurants



            for (int j = 0; j < restaurants[i].orderCount; ++j) {
                cout << "Enter the Order Name: ";
                cin.ignore();
                cin.getline(restaurants[i].orders[j].name, 50);
                cout << "Enter the Destination vertex: ";
                cin >> restaurants[i].orders[j].destination;
                cout << "Enter the maximum Weight Count: ";
                cin >> restaurants[i].orders[j].maxWeight;
                restaurants[i].orders[j].assigned = false;
            }
        }


        for (int i = 0; i < I; ++i) {
            riders[i].path = new int[maxVertices];
            if (i < R) {
                riders[i].currentLocVertex = restaurants[i].location;
                riders[i].destinationtalWeight = 0;
                riders[i].available = true;
            }
            else {
                riders[i].available = false;
            }
        }




                if (optimalRider != -1) {

                    graph.getPath(riders[optimalRider].currentLocVertex, restaurants[i].orders[j].destination, riders[optimalRider].path, riders[optimalRider].pathDist);
                    riders[optimalRider].currentLocVertex = restaurants[i].orders[j].destination;
                    riders[optimalRider].destinationtalWeight += minDistance;
                    restaurants[i].orders[j].assigned = true;
                    cout << "Order " << restaurants[i].orders[j].name << " assigned to Rider " << optimalRider + 1;
                    cout << " with path: ";
                    for (int l = 0; l < riders[optimalRider].pathDist; ++l) {
                        cout << riders[optimalRider].path[l];
                        if (l < riders[optimalRider].pathDist - 1) cout << "->";
                    }
                    cout << endl;
                }
                else {
                    cout << "Order " << restaurants[i].orders[j].name << " cannot be delivered within weight constraints." << endl;
                }
            }
        }

        int totalRiderDis = 0;
        for (int k = 0; k < I; ++k) {
            if (riders[k].available) {
                totalRiderDis += riders[k].destinationtalWeight;
                cout << "Rider " << k + 1 << " Total Distance: " << riders[k].destinationtalWeight << endl;
            }
        }
        cout << "The total Distance Covered by all Riders: " << totalRiderDis << endl << endl;
        cout << endl << endl;


        for (int i = 0; i < R; ++i) {
            delete[] restaurants[i].orders;
        }
        delete[] restaurants;

        for (int i = 0; i < I; ++i) {
            delete[] riders[i].path;
        }
        delete[] riders;
    }
    return 0;
}
