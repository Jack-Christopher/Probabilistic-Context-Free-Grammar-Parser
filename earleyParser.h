class EarleyParser
{
private:
    Grammar grammar;
    std::string text;
    std::vector<std::string> words; 
    Chart chart;
    void PREDICTOR(State s);
    void SCANNER(State s);
    void COMPLETER(State s);
    void setWords();
    void orderIndice();
    double compareByIndex(int index1, int index2);
public:
    EarleyParser() = default;
    EarleyParser(Grammar g, std::string text);
    void setGrammar(std::string fileName);
    void setChart(int n);
    void setText();
    void printChart();
    void printGrammar();
    bool process();
    void convertToProbabilisiticParser();
    ~EarleyParser();
};

EarleyParser::EarleyParser(Grammar g, std::string text)
{
    this->grammar = g;
    this->text = text;
}

/*
procedure PREDICTOR((A -> ...  @ B  ..., [i, j]))
    for each (B -> RHS) in grammar do
    chart[j].pushback(B -> @ RHS, [j, j]) 
*/

void EarleyParser::PREDICTOR(State s)
{
    int j = s.getIdx2();
    Nodo t = s.nextElement();
    State temp;

    for (int k = 0; k < grammar.indice.size(); k++ )
    {
        if (grammar.indice[k].commonLeftSide == t.getValue())
        {
            for (int p = 0; p < grammar.indice[k].commonProductions.size(); p++)
            {
                temp = grammar.productions[grammar.indice[k].commonProductions[p]].convertToState(0);
                temp.setIdx1(j);
                temp.setIdx2(j);
            
                if(!contains<State>(temp, chart.content[j]))
                    chart.content[j].push_back(temp);
            }
            break;
        }
    }
}

/*
procedure SCANNER((A -> ...  @ L  ..., [i, j]))
    if (L -> word[j]) is_in grammar
    chart[j + 1].pushback(L -> ... word[j] @  ..., [j, j + 1])
*/


void EarleyParser::SCANNER(State s) // indices [i, j]
{
    State temp = s;
    int j = temp.getIdx2();
    Nodo t = temp.nextElement();

    Production prod;
    prod.setLeftSide(t);
    Nodo tempNodo {words[j], Terminal};
    std::vector<Nodo> tempVector;
    tempVector.push_back(tempNodo);
    prod.setRightSide(tempVector);

    //Buscar producciones con el indice
    for (int k = 0; k < grammar.indice.size(); k++)
    {
        if (  t.getType() ==  Terminal && t.getValue() == words[j] ||
            ( grammar.indice[k].commonLeftSide == t.getValue() && 
            containsOnIndices<Production>(prod, grammar.productions, grammar.indice[k].commonProductions) )  )
        {
            temp.move();
            temp.setIdx1(j);
            temp.setIdx2(j+1);
            chart.content[j+1].push_back(temp);
            return;
        }
    }
}



/*
procedure COMPLETER((B -> ...  @, [j, k]))
    for each (A -> ...  @ B ..., [i, j]) in chart[j] do
        ADDTOCHART((A -> ...  B @ ..., [i, k]), chart[k])
*/

void EarleyParser::COMPLETER(State s) // indices [j, k]
{
    State eachState;
    int index;
    std::vector<State> temp = chart.content[s.getIdx1()];  //  chart[j]
    std::string leftSide = s.getLeftSide().getValue();          // "B"
    
    for (int k = 0; k < temp.size(); k++ )
    {
        eachState = temp[k];
        index = eachState.getPointIdx()+1;
        if (eachState.getRightSide().size() > index)
        {
            if( eachState.getRightSide()[index].getValue() == leftSide )
            {
                eachState.move();
                eachState.setIdx2(s.getIdx2());
                if ( !contains<State> (eachState, chart.content[s.getIdx2()]) )
                    chart.content[s.getIdx2()].push_back(eachState);
            }
        }
    }
}


void EarleyParser::setGrammar(std::string fileName)
{
    this->grammar.readGrammarFromTXT(fileName);
}

void EarleyParser::setWords()
{
    std::string temp = "";
    for (int k = 0; k < text.size(); k++)
    {
        if (text[k] != ' ')
            temp += text[k];
        else
        {
            if (temp != "")
            {
                words.push_back(temp);
                temp = "";
            }
        }
    }
    if (temp != "")
    {
        words.push_back(temp);
        temp = "";
    }
}

void EarleyParser::setChart(int n)
{
    chart.setUpChart(n);
    //chart.setContent(this->words);
}

void EarleyParser::setText() 
{
    std::cin.ignore();
    std::cout<< "\nIngrese una cadena para analizarla:\t";
    std::getline(std::cin, this->text);
    setWords();
    setChart(words.size());
}


void EarleyParser::printGrammar()
{
    this->grammar.print();
}

void EarleyParser::printChart()
{
    std::cout<< chart.toText();
}


// Main Function
bool EarleyParser::process()
{
    //add dummy start state
    State DSS = dummyStartState(this->grammar.getInitial());
    chart.content[0].push_back(DSS);

    for (int k = 0; k < words.size()+1; k++) // por cada chart[i]
    {
        for (int p = 0; p < chart.content[k].size(); p++)
        {
            if (chart.content[k][p].isIncomplete())
            {
                 if (chart.content[k][p].nextElement().getType() == NonTerminal)
                    PREDICTOR(chart.content[k][p]);
                else if (chart.content[k][p].nextElement().getType() == Terminal)
                    SCANNER(chart.content[k][p]);
            }
            else
                COMPLETER(chart.content[k][p]);
         }
    }
    
    DSS.move();

    if(contains<State>(DSS, chart.content[chart.content.size()-1]))
        return true;
    else
        return false;
}


void EarleyParser::convertToProbabilisiticParser()
{
    std::vector<double> tempVector;
    std::string nonValidProbabilityErrorMessage;
    std::string nonCorrectSumErrorMessage;
    int option;
    for (int k = 0; k < grammar.indice.size(); k++)
    {
        std::cout<< "\nLeft Side:\t"<<grammar.indice[k].commonLeftSide<<"\n";
        if (grammar.indice[k].commonProductions.size() > 1)
        {
            std::cout<< "Modificar?\t (1) SI \t (2) NO\n";
            std::cin>> option;
            nonValidProbabilityErrorMessage = "";
            nonCorrectSumErrorMessage = "";

            if (option == 1)
            {
                double total = 0;
                double probability = 0;
                for (int  p = 0; p < grammar.indice[k].commonProductions.size(); p++)
                {
                    std::cout<< "Production:\t"<<grammar.productions[grammar.indice[k].commonProductions[p]].toString() <<"\n";
                    std::cout<< "Nueva Probabilidad?\t";
                    std::cin>> probability;
                    if (probability > 1 || probability < 0)
                    {
                        nonValidProbabilityErrorMessage = "Probabilidad no valida\n";
                        break;
                    }
                    
                    tempVector.push_back(probability);
                    total += probability;
                }

                if (abs((1-total)*100) > 1)  // diferencia mayor a 0.01
                    nonCorrectSumErrorMessage = "La suma de las probabilidades no es 1\n";
            
                if (nonCorrectSumErrorMessage != "" || nonCorrectSumErrorMessage != "")
                {
                    std::cout<< nonValidProbabilityErrorMessage<< nonCorrectSumErrorMessage;
                    std::cout<< "Ha ocurrido un error, los cambios no fueron hechos\n";
                }
                else
                {
                    for (int t = 0; t < tempVector.size(); t++)
                        grammar.productions[grammar.indice[k].commonProductions[t]].setProbability(tempVector[t]);
                }
                tempVector.clear();
            }
        }
        else
        {
            std::cout<< "No puede modificarse la probabilidad de este nodo No-Terminal ";
            std::cout<< "porque solo dispone de una sola produccion\n";
            grammar.productions[grammar.indice[k].commonProductions[0]].setProbability(1);
        }
    }
    orderIndice();
    //se muestra los indices
    grammar.showIndice();
    std::cout<<"\n";
}


void EarleyParser::orderIndice()
{
    int tam, key, j;
    for (int k = 0; k < grammar.indice.size(); k++)
    {
        tam = grammar.indice[k].commonProductions.size();
        if ( tam > 1)
        {
            //INSERTION SORT para el indice de acuerdo a las probabilidades
            for (int i = 1; i < tam; i++)
            {
                key = grammar.indice[k].commonProductions[i];
                j = i - 1;

                while (j >= 0 && compareByIndex(grammar.indice[k].commonProductions[j], key))
                {
                    grammar.indice[k].commonProductions[j + 1] = grammar.indice[k].commonProductions[j];
                    j = j - 1;
                }
                grammar.indice[k].commonProductions[j + 1] = key;
            }           
        }
    }
}


double EarleyParser::compareByIndex(int index1, int index2)
{
    return ( grammar.productions[index1].getProbability() < grammar.productions[index2].getProbability() );
}


EarleyParser::~EarleyParser()
{
}
