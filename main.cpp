#include <iostream>
#include <vector>
#include <fstream>
#include "token.h"
#include "state.h"
#include "production.h"
#include "grammar.h"
#include "chart.h"
#include "earleyParser.h"

int main()
{
    EarleyParser EP;
    EP.setGrammar("grammar.txt");
    EP.printGrammar();
    EP.setText();
    //EP.printChart();

    return 0;
}
