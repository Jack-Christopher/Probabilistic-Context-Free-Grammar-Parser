class Grammar
{
private:
    std::string initial;
    std::vector<Production> productions;
    std::vector<Nodo> NonTerminals;
    std::vector<Nodo> Terminals;

public:
    Grammar() = default;
    Grammar(std::vector<Production> productions);
    void readGrammarFromTXT(std::string fileName);
    void setElements(std::string init);
    std::vector<Production> getProductions();
    std::string getInitial();
    void print();
    ~Grammar();
};

Grammar::Grammar(std::vector<Production> productions)
{
    this->productions = productions;
}

void Grammar::readGrammarFromTXT(std::string fileName)
{
    std::ifstream file(fileName);
    std::string tempText;
    Production prod;
    while (std::getline(file, tempText))
    {
        std::vector<Production> tempList = prod.readProduction(tempText);
        for (int k = 0; k < tempList.size(); k++)
        {
            productions.push_back(tempList[k]);
        }
    }

    std::string init;
    std::cout<< "Ingrese el simbolo inicial:\t";
    std::cin>> init;
    std::cin.ignore();
    setElements(init);
}

void Grammar::setElements(std::string init)
{
    for (int k = 0; k < productions.size(); k++)
    {
        NonTerminals.push_back(productions[k].getLeftSide());
        if (productions[k].getLeftSide().getValue() == init)
            this->initial = init;

        auto temp = productions[k].getRightSide();
        for (int p = 0; p < temp.size(); p++)
        {
            if ((temp[p].getType() == Terminal) && !contains<Nodo>(temp[p], Terminals))
                Terminals.push_back(temp[p]);
            else if ((temp[p].getType() == NonTerminal) && !contains<Nodo>(temp[p], NonTerminals))
                NonTerminals.push_back(temp[p]);
        }
    }
}


std::vector<Production> Grammar::getProductions()
{
    return this->productions;
}

std::string Grammar::getInitial()
{
    return this->initial;
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
