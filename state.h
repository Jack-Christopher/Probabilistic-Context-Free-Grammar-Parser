
class State
{
private:
    Nodo leftSide;
    std::vector<Nodo> rightSide;
    int pointIdx;
    // [idx1, idx2]
    int idx1;
    int idx2;
    float probability;

public:
    State() = default;
    State(Nodo leftSide, std::vector<Nodo> rightSide);
    State(Nodo leftSide, std::vector<Nodo> rightSide, int pointIdx);
    State(Nodo leftSide, std::vector<Nodo> rightSide, float probability);
    Nodo getLeftSide();
    std::vector<Nodo> getRightSide();
    void setLeftSide(Nodo LeftSide);
    void setRightSide(std::vector<Nodo> RightSide);
    void setPointIdx(int pointIdx);
    int getIdx1();
    int getIdx2();
    void setIdx1(int idx);
    void setIdx2(int idx);
    std::string toString();
    int getPointIdx();

    bool isIncomplete();
    void move();
    Nodo nextElement();
    bool operator ==(const State &t) const;
    ~State();
};

State::State(Nodo leftSide, std::vector<Nodo> rightSide)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
}

State::State(Nodo leftSide, std::vector<Nodo> rightSide, float probability)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
    this->probability = probability;
}

State::State(Nodo leftSide, std::vector<Nodo> rightSide, int pointIdx)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
    Nodo P {".", Point};
    this->rightSide.insert(this->rightSide.begin() + pointIdx, P);
}

Nodo State::getLeftSide()
{
    return leftSide;
}

std::vector<Nodo> State::getRightSide()
{
    return rightSide;
}

void State::setLeftSide(Nodo LeftSide)
{
    this->leftSide = LeftSide;
}

void State::setRightSide(std::vector<Nodo> RightSide)
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
    temp += "] --> [ ";
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
        temp += " ";
    }
    temp += "]\n";
    return temp;
}

bool State::isIncomplete()
{
    // SI EL PUNTO ESTA AL FINAL
    if ((pointIdx == rightSide.size() - 1) && (rightSide[pointIdx].getType() == Point))
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

int State::getPointIdx()
{
    return this->pointIdx;
}

Nodo State::nextElement()
{
    Nodo t;
    if (rightSide[pointIdx].getType() == Point)
        t = rightSide[pointIdx + 1];
    return t;
}

void State::move()
{
    // representa el hecho de un swap de un elemento con su siguiente en el State
    // simula: "el punto avanza"
    Nodo temp = rightSide[pointIdx];
    rightSide[pointIdx] = rightSide[pointIdx + 1];
    rightSide[pointIdx + 1] = temp;
    pointIdx++;
}

bool State::operator ==(const State &t) const
{
    if (this->rightSide == t.rightSide && this->leftSide == t.leftSide)
        return true;
    return false;
}

State::~State()
{
}
