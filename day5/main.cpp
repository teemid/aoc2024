#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

using PageRules = std::unordered_map<int, std::vector<int>>;
using ManualUpdate = std::vector<int>;

void parse_input(std::ifstream &file, PageRules &page_rules, std::vector<ManualUpdate> &updates);
bool check_update(const PageRules &page_rules, const std::vector<int> &update);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Missing input filename argument" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open file" << filename << std::endl;
        return 1;
    }

    PageRules page_rules;
    std::vector<ManualUpdate> updates;

    parse_input(file, page_rules, updates); 

    int count = 0;
    for (const ManualUpdate &update : updates)
    {
        if (check_update(page_rules, update))
        {
            int mid_index = (update.size() + 0.5) / 2;

            int mid = update[mid_index];

            count += mid;
        }
    }

    std::cout << "Count: " << count << std::endl;

    /* for (const auto &update : updates) */
    /* { */
    /*     for (int page : update) */
    /*     { */
    /*         std::cout << page << ", "; */
    /*     } */

    /*     std::cout << std::endl; */
    /* } */

    return 0;
}

void parse_input(std::ifstream &file, PageRules &page_rules, std::vector<ManualUpdate> &updates)
{
    bool is_first_section = true;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            is_first_section = false;
            continue;
        }

        if (is_first_section)
        {
            size_t i;
            int first = std::stoi(line, &i);
            int second = std::stoi(line.substr(i + 1));

            if (!page_rules.contains(first))
            {
                page_rules[first] = {};
            }

            std::vector<int> &pages = page_rules[first];
            pages.emplace_back(second);
        }
        else
        {
            ManualUpdate update;
            std::stringstream ss(line);

            int page_number;
            while (ss >> page_number)
            {
                update.emplace_back(page_number);

                ss.get();
            }

            updates.emplace_back(update);
        }
    }
}

bool check_update(const PageRules &page_rules, const std::vector<int> &update)
{
    for (int i = 0; i < update.size(); i++)
    {
        int page = update[i];
        if (page_rules.contains(page))
        {
            const std::vector<int> &requirements = page_rules.at(page);
            for (int j = i; j >= 0; j--)
            {
                auto pos = std::find(requirements.begin(), requirements.end(), update[j]);
                if (pos != requirements.end())
                {
                    return false;
                }
            }
        }
    }

    return true;
}

