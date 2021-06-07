
class State
{
private:
    Token leftSide;
    std::vector<Token> rightSide;
    int pointIdx;
    // [idx1, idx2]
    int indx1;
    int indx2;
    float probability;

public:
    State() = default;
    State(Token leftSide, std::vector<Token> rightSide);
    State(Token leftSide, std::vector<Token> rightSide, float probability);
    Token getLeftSide();
    std::vector<Token> getRightSide();
    void setLeftSide(Token LeftSide);
    void setRightSide(std::vector<Token> RightSide);
    void setPointIdx(int pointIdx);
    std::string toString();
    bool isIncomplete();
    Token nextElement();
    ~State();
};

State::State(Token leftSide, std::vector<Token> rightSide)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
}

State::State(Token leftSide, std::vector<Token> rightSide, float probability)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
    this->probability = probability;
}

Token State::getLeftSide()
{
    return leftSide;
}

std::vector<Token> State::getRightSide()
{
    return rightSide;
}

void State::setLeftSide(Token LeftSide)
{
    this->leftSide = LeftSide;
}

void State::setRightSide(std::vector<Token> RightSide)
{
    this->rightSide = RightSide;
}

void State::setPointIdx(int pointIdx)
{
    this->pointIdx = pointIdx;
}

std::string State::toString()
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

bool State::isIncomplete()
{
    if ((pointIdx == rightSide.size() -1) && (rightSide[pointIdx].getType() == Point ))
        return false;
    return true;
}

Token State::nextElement()
{
    Token t;
    if ( rightSide[pointIdx].getType() == Point )
        t = rightSide[pointIdx+1];
    return t;    
}

State::~State()
{
}
