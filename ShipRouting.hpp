//
//  ShipRouting.hpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.
//

#ifndef ShipRouting_hpp
#define ShipRouting_hpp



#include <stdio.h>
#include "Node.hpp"
#include "Edge.hpp"
#include <vector>
#include "Graph.hpp"

using namespace std;

class ShipRouting{
    
    
public:
    vector<Node*> nodeGraf;
    vector<Edge*> kantGraf;
    
    ShipRouting(vector<Node*> nodeGraf, vector<Edge*> kantGraf);
    void raskesteVei(Node* sluttNode);
    Node* finnMinsteNode(vector<Node*>& nodeGraf);
    vector<Node*>* finnHosliggendeNoder(Node* node);
    int distanseMellomNoder(Node* node1, Node* node2);
    bool inneholder(vector<Node*>& nodeGraf, Node* node);
    void printKortesteVei(Node* destinasjon);
    int distanseTilSisteNode(Node* node1, Node* node2);
    
};





#endif /* ShipRouting_hpp */
