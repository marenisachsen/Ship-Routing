//
//  ShipRouting.cpp
//  Ship Routing
//
// Created by Maren Mortensdatter Isachsen on 10/04/2021.
//

#include "ShipRouting.hpp"
#include <tgmath.h>


using namespace std;


    ShipRouting:: ShipRouting(vector<Node*> nodeGraf, vector<Edge*> kantGraf) :
nodeGraf(nodeGraf), kantGraf(kantGraf){};

void ShipRouting:: raskesteVei(Node* sluttNode){
    vector<Node*> noder = nodeGraf;
 
    
    while (noder.size() > 0) {
        Node* minste = finnMinsteNode(noder);
        vector<Node*>* hosliggendeNoder = finnHosliggendeNoder(minste);
        
        const auto size = hosliggendeNoder->size();
        for (int i = 0; i < size; i++) {
            Node* hosliggende = hosliggendeNoder->at(i);
            int distanse = distanseMellomNoder(minste, hosliggende) + minste->distanseTilStart - distanseTilSisteNode(minste, sluttNode) + distanseTilSisteNode(hosliggende, sluttNode);
        
            if (distanse < hosliggende->distanseTilStart) {
                hosliggende->distanseTilStart = distanse;
                hosliggende->forrige = minste;
            }
        }
    }
}


Node* ShipRouting:: finnMinsteNode(vector<Node*>& nodeGraf){
    //Lager en ny vektor
    //Finner størreslen til nodes og sjekket alle om de er den korteste
    auto size = nodeGraf.size();
    
    if (size == 0 ){
        return NULL;
    }
    
    int minstePosisjon = 0;
    Node* minste = nodeGraf.at(0);
    
    for(int i = 0; i < size; i++) {
        Node* nåværende = nodeGraf.at(i);
        if (nåværende->distanseTilStart < minste->distanseTilStart) {
            minste = nåværende;
            minstePosisjon = i;
        }
    }
    
    nodeGraf.erase(nodeGraf.begin() + minstePosisjon);
    
    return minste;
}

vector<Node*>* ShipRouting:: finnHosliggendeNoder(Node* node) {
    
    vector<Node*>* hosliggendeNoder = new vector<Node*>();
    const auto size = kantGraf.size();
    
    for (int i = 0; i < size; i++) {
        Edge* kant = kantGraf.at(i);
        Node* hosliggende = NULL;
        
    if (kant->node1 == node) {
        hosliggende = kant->node2;
        hosliggendeNoder->push_back(hosliggende);
        }
    }
    return hosliggendeNoder;
}


int ShipRouting:: distanseMellomNoder(Node* node1, Node* node2) {
    const auto size = kantGraf.size();
    for (int i = 0; i < size; i++) {
        Edge* kant = kantGraf.at(i);
        if (kant->SammenKoblet(node1, node2)) {
            return kant->vekt;
        }
    }
    return -1;
}


bool ShipRouting:: inneholder(vector<Node*>& nodeGraf, Node* node) {
    const auto size = nodeGraf.size();
    for (int i = 0; i < size; i ++){
        if (node == nodeGraf.at(i)) {
            return true;
        }
    }
    return false;
}

void ShipRouting:: printKortesteVei(Node* destinasjon) {
    
    Node* forrige = destinasjon;
    
    cout << "Distance from start: "
    << destinasjon->distanseTilStart<< endl;
    
    while (forrige!=NULL) {
        cout << forrige->id << " ";
        forrige=forrige->forrige;
    }
}

int ShipRouting::distanseTilSisteNode(Node* node1, Node* node2) {
    int u1 = node1->id % 103;
    int v1 = node1->id / 103;
    int u2 = node2->id % 103;
    int v2 = node2->id / 103;
    
    int distanseTilSluttNode = sqrt(pow((u2-u1),2)+pow((v2-v1),2));
    
    return distanseTilSluttNode;
}








