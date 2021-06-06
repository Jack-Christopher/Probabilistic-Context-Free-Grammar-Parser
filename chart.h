class Chart
{
private:
    std::string *content;
    int chartSize;
public:
    Chart() = default;
    void setUpChart(int n);
    void setContent(std::vector<std::string> text);
    std::string toText();
    void swap(int idx1);
    ~Chart();
};


void Chart::setUpChart(int n)
{
    content = new std::string[n+1];
    chartSize = n+1;
}

void Chart::setContent(std::vector<std::string> text)
{
    // La cadena vacia indica el punto del Earley Parser,
    // por eso es colocada al inicio del chart
    *(content) = "";

    // Se rellenan los demas espacios con los valores de la cadena
    for (int k = 0; k < chartSize-1; k++)
    {
        *(content+k+1) = text[k];
    }
}

std::string Chart::toText()
{
    std::string temp = "";
    for (int k = 0; k < chartSize; k++)
    {
        temp += " ";
        if ( *(content+k)  == "")
            temp += "---void---";
        else
            temp += *(content+k);
        temp += " ";
    }
    return temp;
}

void Chart::swap(int idx1)
{
    // representa el hecho de un swap de un elemento con su siguiente en la lista
    // simula: "el punto avanza"
    std::string temp = *(content+idx1);
    *(content+idx1) = *(content+idx1 +1);
    *(content+idx1 +1) = temp;

}

Chart::~Chart()
{
    delete[] content;
}
