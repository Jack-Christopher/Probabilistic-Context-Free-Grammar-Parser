
class State
{
private:
    Token leftSide;
    std::vector<Token> rightSide;
    int pointIdx;
    // [idx1, idx2]
    int idx1;
    int idx2;
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
    int getIdx1();
    int getIdx2();
    void setIdx1(int idx);
    void setIdx2(int idx);
    void move();
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

int State::getIdx1()
{
    return idx1;
}

int State::getIdx2()
{
    return idx2;
}

void State::setIdx1(int idx)
{
    this->idx1 = idx;
}

void State::setIdx2(int idx)
{
    this->idx2 = idx;
}

Token State::nextElement()
{
    Token t;
    if ( rightSide[pointIdx].getType() == Point )
        t = rightSide[pointIdx+1];
    return t;    
}

void State::move()
{
    // representa el hecho de un swap de un elemento con su siguiente en el State
    // simula: "el punto avanza"
    Token temp = rightSide[pointIdx];
    rightSide[pointIdx] = rightSide[pointIdx+1];
    rightSide[pointIdx+1] = temp;
}

State::~State()
{
}
