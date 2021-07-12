#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include "nodo.h"
#include "state.h"
#include "extra.h"
#include "production.h"
#include "grammar.h"
#include "chart.h"
#include "earleyParser.h"

int main()
{
    EarleyParser EP;
    EP.setGrammar("grammar.txt");
    EP.printGrammar();

    //Se setean de forma automática las probabilidades de acuerdo a cada producción de la gramática
    EP.setProbabilities();

    //Saltamos una línea para leer el texto
    std::cin.ignore();

    //Se lee la cadena a ser reconocida
    EP.setText(); 

    //Se procesa
    bool ACCEPTED = EP.process();
    EP.printChart();

    if (ACCEPTED)
        std::cout<< "Cadena aprobada\n\n";
    else
        std::cout<< "Cadena NO aprobada\n\n";
    
    
    return 0;
}


