//
//  main.cpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.
//

#include "main.hpp"

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>

int main() {
    
    skipParams skip {
    .rho_SW = 1025.0,
    .rho_A = 1.2,
    .g = 9.81,
    .visc=1.14E-6,
    .L=233.0 ,
    .Lwl=227.95 ,
    .Los= 234.5,
    .T=  11.0 ,
    .B=  32.2 ,
    .S= 9203.9  ,
    .C_b=  0.6039 ,
    .TA=    11.0,
    .TF=  11.0  ,
    .Dp=    4.5 ,
    .k =   0.14  ,
    .H=   150.0  ,
    .Cd=    0.82  ,
    .At_reg=    850.0  ,
    .At_bal=    910.0   ,
    .NRud=   0 ,
    .NBrac=   0,
    .NThr=    0 ,
    .NBoss=  0  ,
    .loadC= 0
    };
    
    Hollenbach h = Hollenbach();
    float hollenbach = h.hollenbach(skip, 5);
    
    Graph graf = Graph("u-wind.csv", "v-wind.csv", 22);

    vector<Node*> nodeGraf = graf.hentNodeGraf();
    vector<Edge*> kantGraf = graf.hentKantGraf();
    
    string shipP;
    int startNode = 0;
    int sluttNode = 5355;
    
    cout << "Vil du velge dine egne skips paramentere? (j/n):  ";
    cin >> shipP;
    if (shipP == "j") {
        
    }
    cout << "Skriv inn start node:  ";
    cin >> startNode;
    cout << "Skriv inn slutt node:  ";
    cin >> sluttNode;
    if (sluttNode > 5355) {
        cout << "ugyldig slutt node, må være mindre enn 5355" << ".\n"<< "Skriv inn slutt node:  ";
        cin >> sluttNode;
    }

    nodeGraf.at(startNode)->distanseTilStart = 0;
    ShipRouting sr = ShipRouting(nodeGraf, kantGraf);
    
    sr.raskesteVei(nodeGraf.at(sluttNode));
    sr.printKortesteVei(nodeGraf.at(sluttNode));
}
