enum Type
{
    Terminal,
    NonTerminal,
    Inicial,
    NullType
};

class Token
{
private:
    std::string value;
    Type type;
    //float probability;

public:
    Token();
    Token(std::string value, Type type); //, float probability);
    Type getType();
    std::string getValue();
    void setValues(std::string value, Type type);
    std::vector<Token> readToken(std::string &text, int start, int end);
    ~Token();
};
Token::Token()
{
    this->value = "--void--";
    this->type = NullType;
}

Token::Token(std::string value, Type type) //, float probability)
{
    this->value = value;
    this->type = type;
    //this->probability = probability;
}

Type Token::getType()
{
    return type;
}

std::string Token::getValue()
{
    return value;
}

void Token::setValues(std::string value, Type type)
{
    this->value = value;
    this->type = type;
}

std::vector<Token> Token::readToken(std::string &text, int start, int end)
{
    bool opened = false;
    bool nonTerminal;
    std::string tempText = "";
    Token token;
    std::vector<Token> tokenList;
    //std::cout << "okok 1\n";
    for (int k = start; k <= end; k++)
    {
        if (text[k] != ' ')
        {
            if (text[k] == '<')
            {
                opened = true;
                nonTerminal = true;
            }
            else if (text[k] == '\"' && !opened)
            {
                opened = true;
                nonTerminal = false;
            }
            else if (opened && (text[k] == '>' || text[k] == '\"'))
            {
                opened = false;
                if (nonTerminal)
                    token.setValues(tempText, NonTerminal);
                else
                    token.setValues(tempText, Terminal);
                tokenList.push_back(token);
                tempText = "";
            }
            else if (opened)
                tempText += text[k];
        }
    }
    return tokenList;
}

Token::~Token()
{
}
