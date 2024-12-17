#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using Board = std::vector<std::vector<char>>;
using Line = std::vector<char>;

int find_xmas(const Board &board);
void print_board(const Board &board);

int find_cross_mas(const Board &board);

char sequence[] = {'X', 'M', 'A', 'S'};

struct Position
{
    int dx;
    int dy;
};

Position directions[] =
{
    { 0,-1},
    {-1,-1},
    {-1, 0},
    {-1, 1},
    { 0, 1},
    { 1, 1},
    { 1, 0},
    { 1,-1},
};

int main(int argc, char *argv[])
{
    std::string task = "1";
    if (argc < 2)
    {
        std::cout << "Missing input filename" << std::endl;
        return 1;
    }

    if (argc > 2)
    {
        task = argv[2];
    }

    std::string filename(argv[1]);
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    Board board;

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> l;
        for (char c : line)
        {
            l.emplace_back(c); 
        }

        board.emplace_back(l);
    }

    if (task == "1")
    {
        int count = find_xmas(board);
        std::cout << "Number of XMAS's: " << count << std::endl;
    }
    else
    {
        int count = find_cross_mas(board); 

        std::cout << "Number of X-MAS's: " << count << std::endl;
    }


    return 0;
}

int count_xmas(const Board &board, int x, int y);
int count_xmas(const Board &board, int x, int y, int dx, int dy, char *pattern = sequence, int length = 4);
int find_xmas(const Board &board)
{
    int count = 0;
    for (int y = 0; y < board.size(); y++)
    {
        const Line &line = board[y];
        for (int x = 0; x < line.size(); x++)
        {
            char c = line[x];
            if (c == 'X')
            {
                count += count_xmas(board, x, y);
            }
        }
    }

    return count;
}

void print_board(const Board &board)
{
    for (const auto &line : board)
    {
        for (char c : line)
        {
            std::cout << c;
        }

        std::cout << std::endl;
    }
}

int count_xmas(const Board &board, int x, int y)
{
    int count = 0;
    for (const Position &dir : directions)
    {
        count += count_xmas(board, x, y, dir.dx, dir.dy, sequence, 4);
    }

    return count;
}

int count_xmas(const Board &board, int x, int y, int dx, int dy, char *pattern, int length)
{
    int mx = x;
    int my = y;

    for (int i = 0; i < length; i++)
    { 
        if (mx < 0 || mx >= board[my].size() || my < 0 || my >= board.size())
        {
            return 0;
        }

        if (board[my][mx] != pattern[i])
        {
            return 0;
        }

        mx += dx;
        my += dy;
    }

    return 1;
}

int check_cross_mas(const Board &board, int x, int y);
int find_cross_mas(const Board &board)
{
    int count = 0;
    for (int y = 1; y < board.size() - 1; y++)
    {
        const Line &line = board[y];
        for (int x = 1; x < line.size() - 1; x++)
        {
            char c = line[x];
            if (c == 'A')
            {
                count += check_cross_mas(board, x, y);
            }
        }
    }

    return count;
}

Position positions[] =
{
    {-1, -1},
    {-1,  1},
    { 1,  1},
    { 1, -1},
};

char mas[] = {'M', 'A', 'S'};

int check_cross_mas(const Board &board, int x, int y)
{ 
    int first_diagonal = 0;
    first_diagonal += count_xmas(board, x - 1, y - 1, 1, 1, mas, 3);
    first_diagonal += count_xmas(board, x + 1, y + 1, -1, -1, mas, 3);

    int second_diagonal = 0;
    second_diagonal += count_xmas(board, x - 1, y + 1, 1, -1, mas, 3);
    second_diagonal += count_xmas(board, x + 1, y - 1, -1, 1, mas, 3);

    return (first_diagonal > 0 && second_diagonal > 0) ? 1 : 0;
}

