#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "nodo.h"
#include "state.h"
#include "extra.h"
#include "production.h"
#include "grammar.h"
#include "chart.h"
#include "earleyParser.h"


int main()
{

    int n;

    EarleyParser EP;
    EP.setGrammar("grammar.txt");
    EP.printGrammar();
    EP.showGrammarIndice();

    std::cout<<"Ingrese la cantidad de cadenas que quiera analizar: ";std::cin>>n;
    
    for(int i=0; i<n; i++)
    {
        EP.setText();
        bool ACCEPTED = EP.process();
        EP.printChart();
        if (ACCEPTED)
            std::cout<< "Cadena aprobada\n\n";
        else
            std::cout<< "Cadena NO aprobada\n\n";
        
        EP.setProbabilitiesByGrammarInduction();
        EP.showGrammarIndice();
    }

    return 0;
}
