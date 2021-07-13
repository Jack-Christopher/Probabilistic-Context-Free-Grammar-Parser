struct Group
{
    std::string commonLeftSide;
    std::vector<int> commonProductions;
};

class Grammar
{
private:
    std::string initial;
    std::vector<Nodo> NonTerminals;
    std::vector<Nodo> Terminals;
    void setIndice();

public:
    Grammar() = default;
    Grammar(std::vector<Production> productions);
    std::vector<Group> indice;
    std::vector<Production> productions;
    void readGrammarFromTXT(std::string fileName);
    void setElements(std::string init);
    std::vector<Production> getProductions();
    std::string getInitial();
    void print();
    void showIndice();
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
    setIndice();
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

void Grammar::setIndice()
{
    bool visitedProductions[productions.size()];
    std::memset(visitedProductions, false, productions.size());
    Group tempGroup;

    for (int k = 0; k < productions.size(); k++)
    {
        if (!visitedProductions[k])
        {
            visitedProductions[k] = true;
            tempGroup.commonLeftSide = productions[k].getLeftSide().getValue();
            tempGroup.commonProductions.push_back(k);

            for (int p = 0; p < productions.size(); p++)
            {
                if ( productions[k].getLeftSide().getValue() == productions[p].getLeftSide().getValue() &&
                    (!visitedProductions[p] && p != k))
                {
                    visitedProductions[p] = true;
                    tempGroup.commonProductions.push_back(p);
                }
            }
            indice.push_back(tempGroup);
            tempGroup.commonProductions.clear();
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


void Grammar::showIndice()
{
    std::cout<< "INDICE:"<<"("<< indice.size()<<")"<<"\n";
    for (int k = 0; k < indice.size(); k++)
    {
        std::cout<< indice[k].commonLeftSide<<":\n";
        for (int p = 0; p < indice[k].commonProductions.size(); p++)
            std::cout<< "\t" <<productions[indice[k].commonProductions[p]].toString()<<"\n";
    }
}

Grammar::~Grammar()
{
}
