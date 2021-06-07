
bool contains(Token t, std::vector<Token> container)
{
    for (int k = 0; k < container.size(); k++)
    {
        auto v = container[k];
        if (container[k] == t)
            return true;
    }
    return false;
}