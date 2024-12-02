#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>


int first_task(const char *filename);
int second_task(const char *filename);

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "Missing input argument" << std::endl;
        return 1;
    }

    const char *task = "1";
    if (argc > 2)
    {
        task = argv[2]; 
    }

    if (0 == std::strncmp(task, "1", 1))
    {
        first_task(argv[1]);
    }
    else
    {
        second_task(argv[1]);
    }
}

int first_task(const char *filename)
{
    std::ifstream file_stream(filename);
    if (!file_stream.is_open())
    {
        std::cout << "Failed to open file " << filename << std::endl;

        return 1;
    }

    int first_in;
    int second_in;
    std::vector<int> first_list;
    std::vector<int> second_list;
    while (file_stream >> first_in >> second_in)
    {
        first_list.push_back(first_in);
        second_list.push_back(second_in);
    }

    std::sort(first_list.begin(), first_list.end(), std::less<int>());
    std::sort(second_list.begin(), second_list.end(), std::less<int>());

    int sum = 0;
    for (int i = 0; i < first_list.size(); i++)
    {
        int first = first_list[i];
        int second = second_list[i];

        int dist = std::abs(first - second);

        sum += dist;
    }

    std::cout << "Total distance: " << sum << std::endl;

    return 0;
}

int second_task(const char *filename)
{
    std::ifstream file_stream(filename);
    if (!file_stream.is_open())
    {
        std::cout << "Failed to open file " << filename << std::endl;

        return 1;
    }

    std::unordered_map<int, int> count;

    int first_in;
    int second_in;
    std::vector<int> first_list;
    std::vector<int> second_list;
    while (file_stream >> first_in >> second_in)
    {
        first_list.push_back(first_in);

        if (!count.contains(second_in))
        {
            count.insert({ second_in, 0 });
        }

        count[second_in]++;
    }

    int total = 0;
    for (int locationID : first_list)
    {
        if (count.contains(locationID))
        {
            int c = count[locationID];

            total += locationID * c;
        }
    }

    std::cout << "Total: " << total << std::endl;

    return 0;
}

