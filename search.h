#ifndef SEARCH
#define SEARCH

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>
#include <cstring>




const int movesX[4] = {0, 0, 1, -1};
const int movesY[4] = {1, -1, 0, 0};
const int movesQuantity = 4;

const int CORRIDOR = 0;
const int WALL     = 1;
const int SAND     = 2;
const int START    = 3;
const int PATH     = 4;

const int CORRIDOR_COST = 1;
const int SAND_COST     = 2;

const int INCORRECT_VALUE = -1;
const int NO_PATH         = 1;
const int SUCCESS         = 0;

typedef struct
{
    std::stack<std::pair<int, int>> pathDots;
    int pathCost;
    int pathLength;
} Response;



class THandler
{

public:
    THandler() {};
    bool readMap(void);
    void printMap(void);
    int findPath(void);
    ~THandler() {};

private:
    void addStartPoint(int value, int i, int j);
    void addFinishPoints(void);
    int getCost(std::pair<int, int> point);
    bool isValid(std::pair<int, int> point);
    bool isReachable(std::pair<int, int> point);
    Response AStar(std::pair<int, int> source, std::pair<int, int> destination);
    void printMapResult( std::stack<std::pair<int, int>> pathDots);
    


    std::vector<std::vector<int>> map;
    std::pair<int, int> source;
    std::vector<std::pair<int, int>> pointsFinish;
    
    int mapWidth; 
    int mapHeight;

};

int Heuristic(std::pair<int, int> current, std::pair<int, int> destination);
int getValue(char sign);



class Comparison
{
public:
    bool operator()(const std::pair<int, Response> &a, const std::pair<int, Response> &b)
    {
        return a.first > b.first;
    }
    ~Comparison(){};
};


#endif