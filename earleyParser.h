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
    void PREDICTOR(State s, int idx, Grammar g);
    void SCANNER(State s, int idx, std::vector<std::string> w);
    void COMPLETER(State s, int idx,);
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
