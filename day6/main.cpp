#include <fstream>
#include <iostream>
#include <vector>
#include <string>

enum class Cell : unsigned char
{
    NotVisited,
    Visited,
    Obstruction = 255,
};

struct Position
{
    int x;
    int y;
};

using Line = std::vector<Cell>;
using Map = std::vector<Line>;

void parse_input(std::ifstream &file, Map &map, Position &guard);
void turn_guard(Position &guard_direction);
int visited_positions(Map &map);
bool is_inside_map(Position position, int max_x, int max_y);


int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        std::cout << "Missing input filename" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open file " << filename << std::endl;
        return 1;
    }

    Map map;
    Position guard;
    Position guard_direction = { 0, -1 };
    std::vector<Position> path = { };

    parse_input(file, map, guard);

    path.emplace_back(guard);

    int max_y = map.size();
    int max_x = map[max_y - 1].size();

    while (true)
    {
        Position peek;
        peek.x = guard.x + guard_direction.x;
        peek.y = guard.y + guard_direction.y;

        if (!is_inside_map(peek, max_x, max_y))
        {
            break;
        }

        if (map[peek.y][peek.x] == Cell::Obstruction)
        {
            turn_guard(guard_direction);
        }
        else
        {
            guard = peek;
            map[peek.y][peek.x] = Cell::Visited;
            path.emplace_back(peek);
        }
    }

    int count = visited_positions(map);

    std::cout << "Visited positions: " << count << std::endl;

    return 0;
}

bool is_inside_map(Position position, int max_x, int max_y)
{
    return position.x >= 0 && position.x < max_x && position.y >= 0 && position.y < max_y;
}

void parse_input(std::ifstream &file, Map &map, Position &guard)
{
    int y = 0;
    std::string line;
    while (std::getline(file, line))
    {
        Line map_line;
        int x = 0;
        for (char c : line)
        {
            switch (c)
            {
                case '#': map_line.emplace_back(Cell::Obstruction); break;
                case '^':
                {
                    map_line.emplace_back(Cell::Visited);
                    guard.x = x;
                    guard.y = y;
                } break;
                case '.': map_line.emplace_back(Cell::NotVisited); break;
                default: break; 
            }

            x++;
        }

        map.emplace_back(map_line);

        y++;
    }
}

void turn_guard(Position &guard_direction)
{
    if (guard_direction.y == -1)
    {
        guard_direction = {1, 0};
    }
    else if (guard_direction.y == 1)
    {
        guard_direction = {-1, 0};
    }
    else if (guard_direction.x == -1)
    {
        guard_direction = {0, -1};
    }
    else
    {
        guard_direction = {0, 1};
    }
}

int visited_positions(Map &map)
{
    int count = 0;
    for (const Line &line : map)
    {
        for (Cell cell : line)
        {
            if (cell == Cell::Visited)
            {
                count++;
            }
        }
    }

    return count;
}

