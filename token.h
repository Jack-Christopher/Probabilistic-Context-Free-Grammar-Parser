enum Type {Verbo, Sustantivo};

class Token
{
private:
    std::string value;
    Type type;
    float probability;

public:
    Token(std::string value, Type type, float probability);
    ~Token();
};

Token::Token(std::string value, Type type, float probability)
{
    this->value = value;
    this->type = type;
    this->probability = probability;
}

Token::~Token()
{
}
