
class Production
{
private:
    Token leftSide;
    std::vector<Token> rightSide;

public:
    Production() = default;
    Production(Token leftSide, std::vector<Token> rightSide);
    Token getLeftSide();
    std::vector<Token> getRightSide();
    void setLeftSide(Token LeftSide);
    void setRightSide(std::vector<Token> RightSide);
    std::vector<Production> readProduction(std::string production);
    void readLeftSide(std::string &production, int &index);
    std::vector<Token> readRightSide(std::string &production, int &index, int end);
    std::vector<std::vector<Token>> readRightSideHelper(std::string &production, int &index);
    std::string toString();
    ~Production();
};

Production::Production(Token leftSide, std::vector<Token> rightSide)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
}

Token Production::getLeftSide()
{
    return leftSide;
}

std::vector<Token> Production::getRightSide()
{
    return rightSide;
}

void Production::setLeftSide(Token LeftSide)
{
    this->leftSide = LeftSide;
}

void Production::setRightSide(std::vector<Token> RightSide)
{
    this->rightSide = RightSide;
}

void Production::readLeftSide(std::string &production, int &index)
{
    while (index < production.size() && production[index] != ':')
        index++;
    Token token;
    if (token.readToken(production, 0, index - 1)[0].getType() == NonTerminal)
    {
        leftSide = token.readToken(production, 0, index)[0];
    }
    else
        std::cout << "Produccion incorrecta\n";
    index += 3;
}

std::vector<Token> Production::readRightSide(std::string &production, int &index, int end)
{
    Token token;
    std::vector<Token> tokenList = token.readToken(production, index, end);
    return tokenList;
}

std::vector<std::vector<Token>> Production::readRightSideHelper(std::string &production, int &index)
{
    std::vector<std::vector<Token>> RightSideList;
    int prevIndex = index;

    while (index < production.size())
    {
        if (production[index] == '|')
        {
            RightSideList.push_back(readRightSide(production, prevIndex, index - 1));
            prevIndex = index + 1;
        }
        index++;
    }
    RightSideList.push_back(readRightSide(production, prevIndex, index));

    return RightSideList;
}

std::vector<Production> Production::readProduction(std::string production)
{
    int index = 0;
    std::vector<Production> productions;

    readLeftSide(production, index);
    std::vector<std::vector<Token>> tempList = readRightSideHelper(production, index);

    Production prod;
    prod.setLeftSide(leftSide);

    for (int k = 0; k < tempList.size(); k++)
    {
        prod.setRightSide(tempList[k]);        
        productions.push_back(prod);
    }

    return productions;
}

std::string Production::toString()
{
    std::string temp = "";
    temp += "[";
    temp += leftSide.getValue();
    temp += "] --> [  ";
    for (int k = 0; k < rightSide.size(); k++)
    {
        if (rightSide[k].getType() == Terminal)
        {
            temp += "\"";
            temp += rightSide[k].getValue();
            temp += "\"";
        }
        else if (rightSide[k].getType() != NullType)
            temp += rightSide[k].getValue();
        temp += "  ";
    }
    temp += "]   ";
    return temp;
}

Production::~Production()
{
}
