#include "Graph.h"
#include "CSVReader.hpp"
#include "algorithm"
#include "cctype"
#include <iostream>
#include "Image.h"
#include "BFS.cpp"
#include "Dijkstra.cpp"

string getAirportName(int IATA);
int getAirportNum(string airportName);
vector<vector<string>> IATAList;

template <typename V>
void printPath(Graph<V>& g, const vector<V>& path);

int main() {
	std::cout << "Loading the dataset ...";
    vector<vector<string>> data = readCSV("dataset.csv");
	std::cout << " done\n";
	std::cout << "Loading the IATA list ...";
	IATAList = readCSV("airports.csv");
	std::cout << " done\n";

    Graph<int> g(data);
	string src, dst;
	int srcNumber, dstNumber;

	std::cout << "Please choose the IATA code of the source Airport: ";
	std::cin >> src;
	srcNumber = getAirportNum(src);

	std::cout << "Please choose the IATA code of the destination Airport: ";
	std::cin >> dst;
	dstNumber = getAirportNum(dst);

	std::cout << "Writing the BFS on the source airport ... ";
	BFS(g, srcNumber);

	std::cout << "BFS done\n" << "The cheapest flight from the " << src << " to " << dst << " is: ";
	vector<int> path = dijkstraSSSP(g, srcNumber, dstNumber);
	
	for (int i = 0; i < path.size(); i++) {
		if (i == path.size() - 1)
			std::cout << getAirportName(path[i]) << std::endl;
		else
			std::cout << getAirportName(path[i]) << " -> ";
	}

	printPath(g, path);

    return 0;
}

string getAirportName(int IATA) {
	for (int i = 1; i < IATAList.size(); i++) {
		if (stoi(IATAList[i][1]) == IATA) {
			return IATAList[i][2];
		}
	}
	//if the given airpot doesn't exist
	return "none";
}

int getAirportNum(string airportName) {
	for (int i = 1; i < IATAList.size(); i++) {
		if (IATAList[i][2] == airportName) {
			return stoi(IATAList[i][1]);
		}
	}
	
	//if the given airpot doesn't exist
	return -1;
}

template <typename V>
void printPath(Graph<V>& g, const vector<V>& path) {
    ofstream outputfile;
    outputfile.open("Path.csv");
	outputfile << "airport,lat,lon\n";
    const vector<pair<long double, long double>>& vertexLoc = g.getVertexLoc();
    for (int i = 0; i < path.size(); i++) {
        outputfile << getAirportName(path[i]) << ", ";
		outputfile << vertexLoc[g.getVertexIdx(path[i])].first << ", ";
		outputfile << vertexLoc[g.getVertexIdx(path[i])].second;
        outputfile << std::endl;
    }
    outputfile.close();
}
