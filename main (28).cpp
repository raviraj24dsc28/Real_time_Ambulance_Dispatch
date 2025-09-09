#include <bits/stdc++.h>
using namespace std;

// Graph to represent city roads
class Graph {
    int V; 
    unordered_map<int, vector<pair<int,int>>> adj; // node -> {neighbor, distance}

public:
    Graph(int V) { this->V = V; }
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    // Dijkstra for shortest path
    int shortestPath(int src, int dest) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[src] = 0;
        pq.push(make_pair(0, src));

        while(!pq.empty()) {
            pair<int,int> node = pq.top(); pq.pop();
            int d = node.first;
            int u = node.second;

            if(u == dest) return d;

            for(auto &edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if(dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        return -1; // not reachable
    }
};

// Hospital class
class Hospital {
public:
    int id;
    int ambulances;
    Hospital(int id, int amb) : id(id), ambulances(amb) {}
};

// Emergency Dispatch System
class EmergencySystem {
    Graph g;
    unordered_map<int, Hospital*> hospitals; 

public:
    EmergencySystem(int V) : g(V) {}

    void addHospital(int id, int amb) {
        hospitals[id] = new Hospital(id, amb);
    }

    void addRoad(int u, int v, int w) {
        g.addEdge(u, v, w);
    }

    void requestAmbulance(int accidentLoc) {
        int bestHospital = -1, minDist = INT_MAX;

        for(auto &it : hospitals) {
            Hospital* h = it.second;
            if(h->ambulances > 0) {
                int dist = g.shortestPath(accidentLoc, h->id);
                if(dist != -1 && dist < minDist) {
                    minDist = dist;
                    bestHospital = h->id;
                }
            }
        }

        if(bestHospital == -1) {
            cout << "❌ No ambulance available right now!\n";
        } else {
            hospitals[bestHospital]->ambulances--;
            cout << "✅ Ambulance dispatched from Hospital " << bestHospital 
                 << " to Accident Location " << accidentLoc 
                 << " | Distance = " << minDist << "\n";
        }
    }
};

// Main Driver
int main() {
    EmergencySystem system(6);

    // Adding hospitals
    system.addHospital(1, 2);
    system.addHospital(4, 1);

    // Adding roads
    system.addRoad(0, 1, 5);
    system.addRoad(1, 2, 10);
    system.addRoad(2, 3, 2);
    system.addRoad(1, 4, 3);
    system.addRoad(4, 5, 7);

    // Emergency requests
    system.requestAmbulance(0);
    system.requestAmbulance(3);
    system.requestAmbulance(5);
    system.requestAmbulance(2);

    return 0;
}
