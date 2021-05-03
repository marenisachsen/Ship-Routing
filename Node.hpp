//
//  Node.hpp
//  Ship Routing
//
// Created by Maren Mortensdatter Isachsen on 10/04/2021.
//
#pragma once
#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include <utility>

class Node {
    
    
public:
    int id;
    double u_vind;
    double v_vind;
    Node* forrige;
    int distanseTilStart;


Node(int id, double u_vind, double v_vind);
    double hentVektU();
    double hentVektV();


};





#endif /* Node_hpp */
