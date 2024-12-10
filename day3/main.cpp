#include <fstream>
#include <iostream>
#include <string>

struct Multiplication
{
    int op1;
    int op2;
};

bool parse_multiplication(std::ifstream &file, Multiplication *m);
bool parse_do_or_dont(std::ifstream &file, bool *enable_do);
bool parse_number(std::ifstream &file, int *op);

int main(int argc, char *argv[])
{
    std::string task = "1";
    if (argc > 2)
    {
        task = argv[2];
    }

    bool parse_do_and_dont = false;
    if (task == "2")
    {
        parse_do_and_dont = true;
    }

    std::string filename(argv[1]);
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    bool enable_mul = true;
    int sum = 0;

    char c;
    while (file >> c)
    {
        if (c == 'm')
        {
            Multiplication m;
            if (!parse_multiplication(file, &m))
            {
                continue;
            }

            if (enable_mul)
            {
                sum += m.op1 * m.op2;
            }
        }
        else if (c == 'd')
        {
            if (!parse_do_and_dont)
            {
                continue;
            }

            if (!parse_do_or_dont(file, &enable_mul))
            {
                continue;
            }
        }
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}

static char mul_expression[] = {'u', 'l', '('};

bool parse_multiplication(std::ifstream &file, Multiplication *m)
{
    char c;
    for (int i = 0; i < 3; i++)
    {
        if (file.peek() != mul_expression[i])
        {
            return false;
        }

        file.get();
    }

    if (!parse_number(file, &m->op1))
    {
        return false;
    }

    if (file.peek() != ',')
    {
        return false;
    }

    file.get();

    if (!parse_number(file, &m->op2))
    {
        return false;
    }

    if (file.peek() != ')')
    {
        return false;
    }

    file.get();

    return true;
}

static char dont_expression[] = {'\'', 't', '(', ')'};

bool parse_do_or_dont(std::ifstream &file, bool *enable_do)
{
    if (file.peek() != 'o')
    {
        return false;
    }

    file.get();

    switch (file.peek())
    {
        case '(':
        {
            file.get();
            if (file.peek() == ')')
            {
                file.get();
                *enable_do = true;
                return true;
            }
        } break;
        case 'n':
        {
            file.get();
            for (int i = 0; i < 4; i++)
            {
                if (file.peek() != dont_expression[i])
                {
                    return false;
                }

                file.get();
            }

            *enable_do = false;

            return true;
        } break;
        default:
        {
            return false;
        } break;
    }

    return false;
}

bool parse_number(std::ifstream &file, int *op)
{
    char c;

    std::string n;

    file >> *op;

    return file.gcount() > 0;
}

