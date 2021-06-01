class Grammar
{
private:
    std::vector<Production> productions;
    std::vector<std::string> NonTerminals;
    std::vector<std::string> Terminals;

public:
    Grammar();
    Grammar(std::vector<Productions> productions);
    void readGrammarFromTXT(std::string fileName);
    ~Grammar();
};

Grammar::Grammar(std::vector<Production> productions)
{
    this.productions = productions;
}

void readGrammarFromTXT(std::string fileName)
{
    std::string fullName = fileName + ".txt"
    std::ifstream file(fullName);
    std::string tempText;
    while (std::getline(file, tempText))
    {
        readProduction(tempText);
        std::cout<< "\n";
    }
}


Grammar::~Grammar()
{
}
