#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <istream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::string line;
    std::getline(std::cin, line);

    std::istringstream st(line);
    std::vector<double> m_buf;
    // m_buf.reserve(3884502);
    while (true)
    {
        double val = 0;
        st >> val;
        if (st.eof())
        {
            break;
        }

        m_buf.push_back(val);
    }

    std::sort(std::begin(m_buf), std::end(m_buf));
    double sum = 0;
    for (auto v : m_buf)
    {
        sum += v;
    }

    std::cout << double(sum) << '\n';

    return 0;
}