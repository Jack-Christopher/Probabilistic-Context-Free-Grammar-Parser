class Chart
{
private:
    std::vector<std::vector<State>> content;
    int chartSize;
public:
    Chart() = default;
    void setUpChart(int n);
    void setContent(std::vector<std::string> text);
    std::string toText();
    void swap(int Chart_i, int idx);
    ~Chart();
};


void Chart::setUpChart(int n)
{
    content.reserve(n+1);
    chartSize = n+1;
}

void Chart::setContent(std::vector<std::string> text)
{
    return;
}

std::string Chart::toText()
{
    std::string temp = "";
    for (int k = 0; k < content.size(); k++)
    {
        for (int p = 0; p < content[k].size(); p++)
        {
            temp += " ";
            temp += content[k][p].toString();
            temp += " ";
        }
    }
    return temp;
}

void Chart::swap(int Chart_i, int idx)
{
    // representa el hecho de un swap de un elemento con su siguiente en la lista i-esima del chart
    // simula: "el punto avanza"
    State temp = content[Chart_i][idx];
    content[Chart_i][idx] = content[Chart_i][idx+1];
    content[Chart_i][idx+1] = temp;

}

Chart::~Chart()
{

}
