#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


int first_task(const char *filename);
int second_task(const char *filename);
void print_all(const std::vector<std::vector<int>> &rows);
std::vector<int> diff_row(const std::vector<int> &row);
int count_level_errors(const std::vector<int> &row);
bool all_positive(const std::vector<int> &row, int *error_count = nullptr);
bool all_negative(const std::vector<int> &row, int *error_count = nullptr);

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

    return 0;
}

int first_task(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> rows;
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int in;
        std::vector<int> row;
        while (iss >> in)
        {
            row.push_back(in);
        }

        rows.push_back(row);
    }

    std::vector<std::vector<int>> diff_rows;
    for (const auto &row : rows)
    {
        diff_rows.push_back(diff_row(row));
    }

    int safe = 0;
    int unsafe = 0;
    for (const auto &row : diff_rows)
    {
        bool is_safe = true;
        for (int e : row)
        {
            int ae = std::abs(e);
            if (ae < 1 || 3 < ae)
            {
                is_safe = false;
                break;
            }
        }


        if (is_safe)
        {
            if (all_positive(row) || all_negative(row))
            {
                safe++;
                continue;
            }
        }

        unsafe++;
    }

    std::cout << "Safe: " << safe << std::endl;
    std::cout << "Unsafe: " << unsafe << std::endl;

    return 0;
}

void print_all(const std::vector<std::vector<int>> &rows)
{
    for (const auto &row : rows)
    {
        for (int e : row)
        {
            std::cout << e << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

}

std::vector<int> diff_row(const std::vector<int> &row)
{
    std::vector<int> diff_row;

    int last = row[0];
    for (int i = 1; i < row.size(); i++)
    {
        int diff = row[i] - last;
        last = row[i];

        diff_row.push_back(diff);
    }

    return diff_row;
}

bool all_positive(const std::vector<int> &row, int *error_count)
{
    int errors = 0;
    bool ok = true;
    for (int e : row)
    {
        if (e < 0)
        {
            ok = false;
            errors++;
        }
    }

    if (error_count)
    {
        *error_count = errors;
    }

    return ok;
}

bool all_negative(const std::vector<int> &row, int *error_count)
{
    int errors = 0;
    bool ok = true;
    for (int e : row)
    {
        if (e > 0)
        {
            ok = false;
            errors++;
        }
    }

    if (error_count)
    {
        *error_count = errors;
    }

    return ok;
}

int second_task(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<std::vector<int>> rows;
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        int in;
        std::vector<int> row;
        while (iss >> in)
        {
            row.push_back(in);
        }

        rows.push_back(row);
    }

    std::vector<std::vector<int>> diff_rows;
    for (const auto &row : rows)
    {
        diff_rows.push_back(diff_row(row));
    }

    int safe = 0;
    int unsafe = 0;
    for (const auto &row : diff_rows)
    {
        int level_errors = count_level_errors(row);
        bool is_safe = level_errors < 2;
        std::cout << "Level errors: " << level_errors;
        if (is_safe)
        {
            int error_count;
            if (row[0] > 0)
            {
                all_positive(row, &error_count);
            }
            else
            {
                all_negative(row, &error_count);
            }

            std::cout << ", " << "monotone errors: " << error_count << std::endl;

            if (error_count < 2)
            {
                safe++; 
                continue;
            }
        }

        unsafe++;
    }

    std::cout << "Safe: " << safe << std::endl;
    std::cout << "Unsafe: " << unsafe << std::endl;

    return 0;
}

int count_level_errors(const std::vector<int> &row)
{
    int error_count = 0;
    for (int e : row)
    {
        int ae = std::abs(e);
        if (ae < 1 || 3 < ae)
        {
            error_count++;
        }
    }

    return error_count;
}

