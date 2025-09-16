#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<char, std::vector<char>> readInput(std::vector<char> &order);

void findDependentRec(const std::unordered_map<char, std::vector<char>> &g, std::unordered_set<char> &visited, char key, char curr, std::unordered_set<char> &dependent);
std::unordered_map<char, std::unordered_set<char>> findDependent(const std::unordered_map<char, std::vector<char>> &input, const std::vector<char> &order);

std::unordered_set<char> findInverseDependencies(const std::unordered_map<char, std::unordered_set<char>> &dependecies, const std::vector<char> &order);

void printResult(const std::unordered_map<char, std::unordered_set<char>> &m, const std::vector<char> &order);
void printSet(const std::unordered_set<char> &input);

void runAllTestCases();
void case1();
void case2();
void case3();
void assertCondition(bool condition, const char *assertionName);

int main()
{
    // runAllTestCases();

    std::vector<char> order;
    const std::unordered_map<char, std::vector<char>> &input = readInput(order);

    std::unordered_map<char, std::unordered_set<char>> result = findDependent(input, order);
    printResult(result, order);

    std::unordered_set<char> inverseDependencies = findInverseDependencies(result, order);
    printSet(inverseDependencies);

    return 0;
}

std::unordered_map<char, std::vector<char>> readInput(std::vector<char> &order)
{
    std::unordered_map<char, std::vector<char>> lines;
    std::vector<char> currLine;

    char symbol;
    bool isKey = true;
    char key;

    while (std::cin.get(symbol))
    {
        if (symbol == '\n' && !currLine.empty())
        {
            lines[key] = currLine;
            currLine.clear();
            isKey = true;
        }
        else if (symbol != ' ')
        {
            if (isKey)
            {
                key = symbol;
                order.push_back(key);
                isKey = false;
            }
            else
            {
                currLine.push_back(symbol);
            }
        }
    }

    if (!currLine.empty())
    {
        lines[key] = currLine;
    }

    return lines;
}

std::unordered_map<char, std::unordered_set<char>> findDependent(const std::unordered_map<char, std::vector<char>> &input, const std::vector<char> &order)
{
    std::unordered_map<char, std::unordered_set<char>> result;
    std::unordered_set<char> visited;

    for (int i = 0; i < order.size(); i++)
    {
        findDependentRec(input, visited, order[i], order[i], result[order[i]]);
        visited.clear();
    }

    return result;
}

void findDependentRec(const std::unordered_map<char, std::vector<char>> &g, std::unordered_set<char> &visited, char key, char curr,
                      std::unordered_set<char> &dependent)
{
    visited.insert(curr);

    if (!g.count(curr))
    {
        return;
    }

    auto neighbours = g.at(curr);
    for (char neighbour : neighbours)
    {
        if (neighbour == key)
        {
            dependent.insert(neighbour);
        }

        if (!visited.count(neighbour))
        {
            dependent.insert(neighbour);
            findDependentRec(g, visited, key, neighbour, dependent);
        }
    }
}

std::unordered_set<char> findInverseDependencies(const std::unordered_map<char, std::unordered_set<char>> &result, const std::vector<char> &order)
{
    std::unordered_set<char> intersection = result.at(order[0]);
    std::unordered_set<char> toExclude;

    for (int i = 1; i < order.size(); i++)
    {
        std::unordered_set<char> curr = result.at(order[i]);

        for (char c : intersection)
        {
            if (!curr.count(c))
            {
                toExclude.insert(c);
            }
        }

        for (char c : toExclude)
        {
            intersection.erase(c);
        }

        toExclude.clear();
    }

    return intersection;
}

void printResult(const std::unordered_map<char, std::unordered_set<char>> &m, const std::vector<char> &order)
{
    for (char key : order)
    {
        std::cout << key << " ";

        for (char c : m.at(key))
        {
            std::cout << c << " ";
        }

        std::cout << "\n";
    }
}

void printSet(const std::unordered_set<char> &input)
{
    std::cout << "\n";

    for (char c : input)
    {
        std::cout << c << " ";
    }

    std::cout << "\n";
}

// TESTS

void runAllTestCases()
{
    case1();
    case2();
    case3();
}

void case1()
{
    std::unordered_map<char, std::vector<char>> testInput = {
        {'A', {'B'}},
        {'B', {'A'}}};

    std::vector<char> order = {'A', 'B'};

    std::unordered_map<char, std::unordered_set<char>> expectedDependencies = {
        {'A', {'B', 'A'}},
        {'B', {'A', 'B'}}};
    std::unordered_map<char, std::unordered_set<char>> actualDependencies = findDependent(testInput, order);
    assertCondition(actualDependencies == expectedDependencies, "Cyclic Dependencies");

    std::unordered_set<char> expectedInverseDependecies = {'A', 'B'};
    std::unordered_set<char> actualInverseDependecies = findInverseDependencies(actualDependencies, order);
    assertCondition(actualInverseDependecies == expectedInverseDependecies, "Inverse Dependencies Cyclic Example");
}

void case2()
{

    std::unordered_map<char, std::vector<char>> testInput =
        {{'A', {'B', 'C'}},
         {'B', {'C', 'E'}},
         {'C', {'G'}},
         {'D', {'A', 'F'}},
         {'E', {'F'}},
         {'F', {'H'}}};

    std::vector<char> order = {'A', 'B', 'C', 'D', 'E', 'F'};

    std::unordered_map<char, std::unordered_set<char>> expectedDependecies = {
        {'A', {'B', 'C', 'E', 'F', 'G', 'H'}},
        {'B', {'C', 'E', 'F', 'G', 'H'}},
        {'C', {'G'}},
        {'D', {'A', 'B', 'C', 'E', 'F', 'G', 'H'}},
        {'E', {'F', 'H'}},
        {'F', {'H'}}};
    std::unordered_map<char, std::unordered_set<char>> actualDependecies = findDependent(testInput, order);
    assertCondition(actualDependecies == expectedDependecies, "Example From Statement");

    std::unordered_set<char> expectedInverseDependecies = {};
    std::unordered_set<char> actualInverseDependecies = findInverseDependencies(actualDependecies, order);
    assertCondition(actualInverseDependecies == expectedInverseDependecies, "Inverse Dependencies Example From Statement");
}

void case3()
{
    std::unordered_map<char, std::vector<char>> testInput =
        {{'A', {'B', 'C'}},
         {'B', {'C', 'E'}},
         {'C', {'G', 'H'}},
         {'D', {'A', 'F'}},
         {'E', {'F'}},
         {'F', {'H'}}};

    std::vector<char> order = {'A', 'B', 'C', 'D', 'E', 'F'};

    std::unordered_map<char, std::unordered_set<char>> expectedDependecies = {
        {'A', {'B', 'C', 'E', 'F', 'G', 'H'}},
        {'B', {'C', 'E', 'F', 'G', 'H'}},
        {'C', {'G', 'H'}},
        {'D', {'A', 'B', 'C', 'E', 'F', 'G', 'H'}},
        {'E', {'F', 'H'}},
        {'F', {'H'}}};
    std::unordered_map<char, std::unordered_set<char>> actualDependecies = findDependent(testInput, order);
    assertCondition(actualDependecies == expectedDependecies, "Dependencies Example");

    std::unordered_set<char> expectedInverseDependecies = {'H'};
    std::unordered_set<char> actualInverseDependecies = findInverseDependencies(actualDependecies, order);
    assertCondition(actualInverseDependecies == expectedInverseDependecies, "Inverse Dependencies Example");
}

void assertCondition(bool condition, const char *assertionName)
{
    if (!condition)
    {
        std::cout << "Assertion Failed: " << assertionName << '\n';
    }
}