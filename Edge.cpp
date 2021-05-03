//
//  Edge.cpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.
//

#include "Edge.hpp"



Edge :: Edge(Node* node1, Node* node2, float vekt) :
node1(node1), node2(node2), vekt(vekt){};

bool Edge:: SammenKoblet(Node* node1, Node* node2){
    return((node1 == this->node1 && node2 == this->node2)||(node1 == this->node2 && node2 == this->node1));
}

float Edge:: hentVekt() {
    return vekt;
}


