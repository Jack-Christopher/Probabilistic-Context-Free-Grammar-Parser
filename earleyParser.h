class EarleyParser
{
private:
    Grammar grammar;
    std::string text;
    std::vector<std::string> words; 
    Chart chart;
public:
    EarleyParser() = default;
    EarleyParser(Grammar g, std::string text);
    void PREDICTOR(State s);
    void SCANNER(State s);
    void COMPLETER(State s);
    void setGrammar(std::string fileName);
    void setWords();
    void setChart(int n);
    void setText();
    void printChart();
    void printGrammar();
    bool process();
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
    std::vector<Production> prods = grammar.getProductions();
    State temp;
    for (int k = 0; k < prods.size(); k++)
    {
        if ((prods[k].getLeftSide() == t))
        {
            temp = prods[k].convertToState(0);
            temp.setIdx1(j);
            temp.setIdx2(j);
            
            if(!contains<State>(temp, chart.content[j]))
                chart.content[j].push_back(temp);
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

    if ( ( contains<Production>(prod, this->grammar.getProductions()) ) ||
         (t.getType() ==  Terminal && t.getValue() == words[j] ) )
    {
        temp.move();
        temp.setIdx1(j);
        temp.setIdx2(j+1);
        chart.content[j+1].push_back(temp);
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
    //se muestra los indices
    this->grammar.showIndice();
    std::cout<<"\n";

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



EarleyParser::~EarleyParser()
{
}
