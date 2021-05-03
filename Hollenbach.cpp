//
//  Hollenbach.cpp
//  Ship Routing
//
//  Created by Maren Mortensdatter Isachsen on 10/04/2021.
//

#include <math.h>

#include "Hollenbach.hpp"

using namespace std;

float Hollenbach:: hollenbach(skipParams ship, float fVel){
    // Hollenbach parameters given in the appendix.
    float a1[3] = {-0.3382, -0.7139, -0.2748};
    float a2[3] = {0.8086, 0.2558, 0.5747};
    float a3[3] = {-6.0258, -1.1606, -6.7610};
    float a4[3] = {-3.5632, 0.4534, -4.3834};
    float a5[3] = {9.4405, 11.222, 8.8158};
    float a6[3] = {0.0146, 0.4524, -0.1418};
    float a7[3] = {0, 0, -0.1258};
    float a8[3] = {0, 0, 0.0481};
    float a9[3] = {0, 0, 0.1699};
    float a10[3] = {0, 0, 0.0728};
    float b11[3] = {-0.57424, -1.50162, -5.3475};
    float b12[3] = {13.3893, 12.9678, 55.6532};
    float b13[3] = {90.596, -36.7985, -114.905};
    float b21[3] = {4.6614, 5.55536, 19.2714};
    float b22[3] = {-39.721, -45.8815, -192.388};
    float b23[3] = {-351.483, 121.82, 388.333};
    float b31[3] = {-1.14215, -4.33571, -14.3571};
    float b32[3] = {-12.3296, 36.0782, 142.738};
    float b33[3] = {459.254, -85.3741, -254.762};
    float d1[3] = {0.854, 0.032, 0.897};
    float d2[3] = {-1.228, 0.803, -1.457};
    float d3[3] = {0.497, -0.739, 0.767};
    float e1[3] = {2.1701, 1.9994, 1.8319};
    float e2[3] = {-0.1602, -0.1446, -0.1237};
    // Additional parameters seemingly unneeded for this
    // appliction.

    float f1[3] = {0.17, 0.15, 0.16};
    float f2[3] = {0.2, 0.1, 0.24};
    float f3[3] = {0.6, 0.5, 0.6};
    float g1[3] = {0.642, 0.42, 0.50};
    float g2[3] = {-0.635, -0.2, 0.66};
    float g3[3] = {0.15, 0, 0.5};
    float h1[3] = {1.204, 1.194, 1.206};
    


    // Hollenbach implementation as taught in TMR4247 Hydrodynamics.
    int Q = ship.loadC; // Load condition, shorthand
    
    float L_fn;
    if (ship.Los/ship.L < 1.0) {
        L_fn = ship.Los;
    } else if ((ship.Los/ship.L > 1.0)&&(ship.Los/ship.L < 1.1)) {
        L_fn = ship.L + (2.0/3.0)*(ship.Los-ship.L);
    } else {
        L_fn = 1.0667 * ship.L;
    }
        
    float Froude = fVel / sqrt(ship.g * L_fn);
    float FroudeCrit = d1[Q] + d2[Q]*ship.C_b + d3[Q]*ship.C_b*ship.C_b;
    
    float c1[3] = {Froude/FroudeCrit, 10*ship.C_b*(Froude/FroudeCrit-1), Froude/FroudeCrit};
    
    float C_R_FroudeCrit = powf(Froude/FroudeCrit, c1[Q]);
    if (C_R_FroudeCrit < 1.0){
        C_R_FroudeCrit = 1.0;
    }
    
    float C_R_Std = b11[Q]+b12[Q]*Froude+b13[Q]*powf(Froude,2.0)+ship.C_b*(b21[Q]+b22[Q]*Froude+b23[Q]*powf(Froude,2.0))+powf(ship.C_b,2.0)*(b31[Q]+b32[Q]*Froude+b33[Q]*powf(Froude,2.0));
    float kL = e1[Q] * powf(ship.L,e2[Q]);
    
    float C_R_Hb = C_R_Std * C_R_FroudeCrit * kL * powf(ship.T/ship.B,a1[Q]) * powf(ship.B/ship.L,a2[Q]) * powf(ship.Los/ship.Lwl,a3[Q]) * powf(ship.Lwl/ship.L,a4[Q]) * powf(ship.Dp/ship.TA,a6[Q]) * powf((1 - (ship.TA-ship.TF)/ship.L),a5[Q]) * powf(1-ship.NRud,a7[Q]) * powf(1-ship.NBrac, a8[Q]) * powf(1-ship.NBoss,a9[Q]) * powf(1-ship.NThr,a10[Q]);
    
    float Reynolds = 6.0 * Froude * sqrt(6.0*ship.g) / 1.1395 * 10E6;
    
    float C_F = 0.075 / powf((logf(Reynolds)-2.0),2.0);
    
    float deltaC_F = (100.0 * powf(ship.H*fVel,0.21) - 403)*powf(C_F,2.0);

    float theta = ship.C_b / ship.L * sqrt(ship.B*(ship.TA+ship.TF));
    float formFactor = 0.6*theta + 145*powf(theta,3.5);
    
    float C_R = C_R_Hb * ship.B * ship.T / ship.S - formFactor*C_F;
    
    float C_Ts = (C_F+deltaC_F)*(1.0+formFactor) + C_R;
    
    float R_Ts = 0.5 * ship.rho_SW * powf(fVel,2.0) * ship.S * C_Ts;
    return R_Ts;

}


