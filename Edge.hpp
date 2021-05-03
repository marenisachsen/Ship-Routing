//
//  Edge.hpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.
//
#pragma once
#ifndef Edge_hpp
#define Edge_hpp

#include <stdio.h>
#include "Node.hpp"


class Edge{



    public:
        Node* node1;
        Node* node2;
        float vekt;
        bool koblet;
    
        Edge(Node* node1, Node* node2, float vekt);
        float hentVekt();
        bool SammenKoblet(Node* node1, Node* node2);
};

#endif  /* Edge_hpp */

