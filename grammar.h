class Grammar
{
private:
    std::vector<Production> productions;
    std::vector<std::string> NonTerminals;
    std::vector<std::string> Terminals;

public:
    Grammar() = default;
    Grammar(std::vector<Production> productions);
    void readGrammarFromTXT(std::string fileName);
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
        //std::cout << tempText;
        std::vector<Production> tempList = prod.readProduction(tempText);
        for (int k = 0; k < tempList.size(); k++)
        {
            productions.push_back(tempList[k]);
        }
    }
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
