class Grammar
{
private:
    std::vector<Production> productions;
    std::vector<Token> NonTerminals;
    std::vector<Token> Terminals;

public:
    Grammar() = default;
    Grammar(std::vector<Production> productions);
    void readGrammarFromTXT(std::string fileName);
    void setElements();
    std::vector<Production> getProductions();
    void print();
    bool contains();
    ~Grammar();
};

Grammar::Grammar(std::vector<Production> productions)
{
    this->productions = productions;
}

bool Grammar::contains(Token t, std::vector<Token> vector)
{
    for (int k = 0; k < vector; k++)
    {
        if(vector[k] == t)
            return true;
    }
    return false;
}

void Grammar::readGrammarFromTXT(std::string fileName)
{
    std::ifstream file(fileName);
    std::string tempText;
    Production prod;
    while (std::getline(file, tempText))
    {
        //std::cout << tempText;
        std::vector<Production> tempList = prod.readProduction(tempText);
        for (int k = 0; k < tempList.size(); k++)
        {
            productions.push_back(tempList[k]);
        }
    }
}

void Grammar::setElements()
{
    for (int k = 0; k < productions.size(); k++)
    {
        auto temp  = productions[k].getRightSide();
        NonTerminals.push_back(productions[k].getLeftSide());
        for (int p = 0; p < temp.size(); p++)
        {
            if ((temp[p].getType() == Terminal) && !contains(temp[t], Terminals))
                Terminals.push_back(temp[p]);
            else if ((temp[p].getType() == NonTerminal) && !contains(temp[t], NonTerminals))
                NonTerminals.push_back(temp[p]);
        }
    }
}

std::vector<Production> Grammar::getProductions()
{
    return productions;
}

void Grammar::print()
{
    std::cout << "\n-------------- Grammar --------------\n";

    for (int k = 0; k < productions.size(); k++)
    {
        std::cout << productions[k].toString()<<"\n";
    }
    std::cout << "\n-------------------------------------\n";
}

Grammar::~Grammar()
{
}
