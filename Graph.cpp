//
//  Graph.cpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.
//

#include "Graph.hpp"
#include "Edge.hpp"


using namespace std;
    
    
 Graph::Graph(string uFile, string vFile, float hollenbach){
    this -> uFile = uFile;
    this -> vFile = vFile;
    this -> hollenbach = hollenbach;
    lagNodeGraf();
    lagKantGraf();
}

void Graph::lagNodeGraf(){
    ifstream myFileU;
    ifstream myFileV;
    myFileU.open(uFile);
    myFileV.open(vFile);
    
    int id = 0;
    
    while(myFileU.good() && myFileV.good()){
        string lineU;
        string lineV;
        
        while(getline(myFileU, lineU, ';') && getline(myFileV, lineV, ';')){
            if(!lineU.empty() || !lineV.empty()){
                nodeGraf.push_back(new Node(id ,atof(lineU.c_str()) , atof(lineV.c_str())));
                id++;
            }
        }
    };

    myFileU.close();
    myFileV.close();
}

void Graph::lagKantGraf(){
    //legger inn kanter for noden oppe til venstre
    kantGraf.push_back(new Edge(nodeGraf[0], nodeGraf[1], nodeGraf[0]->hentVektU() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[0], nodeGraf[103], nodeGraf[0]->hentVektV() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[0], nodeGraf[104], hollenbach));
    
    //legger inn kanter for noden oppe til høyre
    kantGraf.push_back(new Edge(nodeGraf[102], nodeGraf[101], -nodeGraf[102]->hentVektU() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[102], nodeGraf[102+103], nodeGraf[102]->hentVektV() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[102], nodeGraf[102+102], hollenbach));
    
    //legger inn kanter for noden nede til venstre
    kantGraf.push_back(new Edge(nodeGraf[5253], nodeGraf[5254], nodeGraf[5253]->hentVektU() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[5253], nodeGraf[5253-103], -nodeGraf[5253]->hentVektV() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[5253], nodeGraf[5253-102], hollenbach));
    
    //legger inn kanter for noden nede til høyre
    kantGraf.push_back(new Edge(nodeGraf[5355], nodeGraf[5354], -nodeGraf[5355]->hentVektU() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[5355], nodeGraf[5355-103], -nodeGraf[5355]->hentVektV() + hollenbach));
    kantGraf.push_back(new Edge(nodeGraf[5355], nodeGraf[5355-104], hollenbach));
    
    //legger inn kanter for nodene til venstre
    for (int i = 1; i < 51; i ++) {
        kantGraf.push_back(new Edge(nodeGraf[i*103], nodeGraf[i*103+1], nodeGraf[i*103]->hentVektU() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103], nodeGraf[i*103+103], nodeGraf[i*103]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103], nodeGraf[i*103-103], -nodeGraf[i*103]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103], nodeGraf[i*103-102],  hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103], nodeGraf[i*103+104],  hollenbach));
    }
    
    //legge inn kanter for nodene til toppen
    for (int i = 1; i < 102; i ++) {
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+1], nodeGraf[i]->hentVektU() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-1], -nodeGraf[i]->hentVektU() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+103], nodeGraf[i]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+102],  hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+104],  hollenbach));
    }
    
    //legge inn kanter for nodene på bunnen
    for (int i = 5254; i < 5355; i ++) {
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+1], nodeGraf[i]->hentVektU() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-1], -nodeGraf[i]->hentVektU() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-103], -nodeGraf[i]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-102],  hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-104],  hollenbach));
    }
    
    //legger inn kanter for nodene på høyre side
    for (int i = 1; i < 51; i ++) {
        kantGraf.push_back(new Edge(nodeGraf[i*103 + 102], nodeGraf[i*103-1], -nodeGraf[i*103+102]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103 + 102], nodeGraf[i*103+102+103], nodeGraf[i*103+102]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103+102], nodeGraf[i*103+102-103], -nodeGraf[i*103+102]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103], nodeGraf[i*103-102],  hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i*103], nodeGraf[i*103+104],  hollenbach));
    }
    
    for (int i = 104; i < 5251; i++) {
        
        if ((i+1) % 103 == 0) {
            continue;
        }
        
        if (i % 103 == 0) {
            continue;
        }
        
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+103], nodeGraf[i]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-103], -nodeGraf[i]->hentVektV() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+1], nodeGraf[i]->hentVektU() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-1], -nodeGraf[i]->hentVektU() + hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-104], hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i-102], hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+102], hollenbach));
        kantGraf.push_back(new Edge(nodeGraf[i], nodeGraf[i+104], hollenbach));
    }
}

vector<Node*> Graph::hentNodeGraf(){
    return nodeGraf;
}

vector<Edge*> Graph :: hentKantGraf(){
    return kantGraf;
}
