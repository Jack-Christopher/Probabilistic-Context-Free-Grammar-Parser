class Chart
{
private:
    std::vector<std::vector<State>> content;
    int chartSize;
public:
    Chart() = default;
    void setUpChart(int n);
    void setContent(std::vector<std::string> text);
    std::vector<std::vector<State>> getContent();
    std::string toText();
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

std::vector<std::vector<State>> Chart::getContent()
{
    return content;
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

Chart::~Chart()
{

}
