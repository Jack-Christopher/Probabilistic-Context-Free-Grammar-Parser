template <class Tipo>
bool contains(Tipo t, std::vector<Tipo> container)
{
    for (int k = 0; k < container.size(); k++)
    {
        if (container[k] == t)
            return true;
    }
    return false;
}

template <class Tipo>
bool containsOnIndices(Tipo t, std::vector<Tipo> container, std::vector<int> positions)
{
    for (int k = 0; k < positions.size(); k++)
    {
        if (container[positions[k]] == t)
            return true;
    }
    return false;
}


template <class Tipo>
void print(std::vector<Tipo> container)
{
    for (int k = 0; k < container.size(); k++)
    {
        std::cout << container[k].toString() << "\n";
    }
    std::cout << "\n";
}

State dummyStartState(std::string S)
{
    Nodo leftSide{"TOP", NonTerminal};
    std::vector<Nodo> rightSide;
    Nodo n{S, NonTerminal};
    rightSide.push_back(n);

    State dummyStartState{leftSide, rightSide, 0};
    dummyStartState.setIdx1(0);
    dummyStartState.setIdx2(0);
    dummyStartState.setPointIdx(0);

    return dummyStartState;
}
