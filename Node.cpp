//
//  Node.cpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.


#include "Node.hpp"
#include <vector>

#define INT_MAX 100000000000




using namespace std;


    
    Node :: Node(int id, double u_vind, double v_vind) :
id(id), u_vind(u_vind), v_vind(v_vind), forrige(NULL), distanseTilStart(INT_MAX){};

double Node:: hentVektV(){
    return v_vind;
    }

double Node:: hentVektU(){
    return u_vind;
}






    








