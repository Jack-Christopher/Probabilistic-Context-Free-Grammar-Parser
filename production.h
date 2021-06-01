
class  Production
{
private:
    std::string leftSide;
    std::vector<std::string> rightSide;
public:
    Production(std::string leftSide, std::vector<std::string> rightSide);
    void readProduction(std::string production);
    std::string readLeftSide(std::string production);
    std::vector<std::string> readRightSide(std::string production);
    ~ Production();
};

 Production:: Production(std::string leftSide, std::vector<std::string> rightSide)
{
    this->leftSide = leftSide;
    this->rightSide = rightSide;
}

/* Example
   <  P  >    ::= <S>
<S> ::= <S> "+" <M> | <M>
<M> ::= <M> "*" <T> | <T>
<T> ::= "1" | "2" | "3" | "4"
*/


std::string readLeftSide(std::string production)
{
    std::string tempText = "";
    int index = 0;
    bool opened = false;
    while (production[index] != ':')
    {
        if  ( production[index] == '<')
        {   
            opened = true;
            continue;
        }

        if ( production[index] != ' ' && opened)
        {
            tempText += production;
        }        
        index++;
    }
}

std::vector<std::string> readRightSide(std::string production);




void Production::readProduction(std::string production)
{
    for (int k = 0; k < production.size(); k++)
    {
        std::string leftSide = readLeftSide(production);
        std::vector<std::string> rightSide= readRightSide(production);
    }
}


 Production::~ Production()
{
}
