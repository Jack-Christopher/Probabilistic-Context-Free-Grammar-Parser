class Chart
{
public:
    std::vector<std::vector<State>> content;
    int chartSize;
    Chart() = default;
    void setUpChart(int n);
    std::vector<std::vector<State>> getContent();
    std::string toText();
    ~Chart();
};


void Chart::setUpChart(int n)
{
    std::vector<State> temp;
    for (int k = 0; k <= n; k++)
        content.push_back(temp);
    chartSize = n+1;
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
        temp += "Chart[";
        temp += std::to_string(k);
        temp += "]:\n";

        for (int p = 0; p < content[k].size(); p++)
        {
            temp += "\t[";
            temp += std::to_string(content[k][p].getIdx1());
            temp += ", ";
            temp += std::to_string(content[k][p].getIdx2());
            temp += "]\t";
            temp += " ";
            temp += content[k][p].toString();
            
        }
        temp += "\n";
    }
    return temp;
}

Chart::~Chart()
{

}
