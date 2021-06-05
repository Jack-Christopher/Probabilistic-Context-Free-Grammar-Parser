#include <iostream>
#include <vector>
#include <fstream>
#include "token.h"
#include "production.h"
#include "grammar.h"

int main()
{
    Grammar g;
    g.readGrammarFromTXT("grammar2.txt");
    g.print();
    
    return 0;
}
