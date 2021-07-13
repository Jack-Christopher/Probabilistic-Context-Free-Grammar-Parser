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
    EarleyParser EP;
    EP.setGrammar("grammar.txt");
    EP.printGrammar();
    EP.convertToProbabilisiticParser();
    EP.setText(); 
    bool ACCEPTED = EP.process();
    EP.printChart();

    if (ACCEPTED)
        std::cout<< "Cadena aprobada\n\n";
    else
        std::cout<< "Cadena NO aprobada\n\n";

    return 0;
}