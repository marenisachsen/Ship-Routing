//
//  Graph.hpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "Node.hpp"
#include "Edge.hpp"
#include "Hollenbach.hpp"

using namespace std;

class Graph{
    
public:
    string uFile;
    string vFile;
    int filelength = 103;
    vector<Node*> nodeGraf;
    vector<Edge*> kantGraf;
    float hollenbach;
    
    Graph(string uFile, string vFile, float hollenbach);
    void lagNodeGraf();
    vector<Node*> hentNodeGraf();
    vector<Edge*> hentKantGraf();
    pair<double,double> hentVerdi(int i, int j);
    void lagKantGraf();
};


#endif /* Graph_hpp */
