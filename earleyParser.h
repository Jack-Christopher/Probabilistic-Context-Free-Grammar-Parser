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
    void COMPLETER(State s, int idx); // Aun en elaboracion
    void setGrammar(std::string fileName);
    void setWords();
    void setChart(int n);
    void setText();
    void printChart();
    void printGrammar();
    ~EarleyParser();
};

EarleyParser::EarleyParser(Grammar g, std::string text)
{
    this->grammar = g;
    this->text = text;
    //dummy start state
}

void EarleyParser::PREDICTOR(State s)
{
    int j = s.getIdx2();
    Token t = s.nextElement();
    std::vector<Production> prods = grammar.getProductions();
    State temp;
    for (int k = 0; k < prods.size(); k++)
    {
        if ((prods[k].getLeftSide().getValue() == t.getValue()) && (prods[k].getLeftSide().getType() == t.getType()))
        {
            temp = prods[k].convertToState(0);
            temp.setIdx1(j);
            temp.setIdx2(j);
            chart.getContent()[j].push_back(temp);
        }
    }
}

void EarleyParser::SCANNER(State s)
{
    State temp = s;
    int j = temp.getIdx2();
    Token t = temp.nextElement();
    std::vector<Production> prods = grammar.getProductions();
    if (t.getType() ==  Terminal)
    {
        temp.move();
        temp.setIdx1(j);
        temp.setIdx2(j+1);
        chart.getContent()[j+1].push_back(temp);
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
    chart.setContent(this->words);
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

EarleyParser::~EarleyParser()
{
}
