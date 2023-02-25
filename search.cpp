#include "search.h"

bool THandler::readMap(void)
{
    int sign;
    int i = 0;
    int j = -1;

    std::vector<int> line;

    while (std::cin) {

        sign = std::cin.get();

        if (sign == '\n' || sign == EOF) {
            i++;
            j = -1;

            this->map.push_back(line);
            line.clear();

            continue;
        }

        j++;

        int value = getValue(sign);

        if (value == INCORRECT_VALUE) {
            std::cout<< "Incorrect map"<< std::endl;
            return false;
        }

        addStartPoint(value, i, j);
        line.push_back(value);
    }

    this->mapWidth  = this->map[0].size(); 
    this->mapHeight = this->map.size(); 

    addFinishPoints();

    return true;
}


int THandler::findPath(void) {

    int pointsFinishSize = (int) this->pointsFinish.size();

    std::priority_queue<std::pair<int, Response>,
                        std::vector<std::pair<int, Response>>,
                        Comparison> answer;

    for (int i = 0; i < pointsFinishSize; i++) {
		Response response = AStar(source, this->pointsFinish[i]);
        if (response.pathLength != -1)
            answer.emplace(response.pathCost, response);

	}
    if (answer.empty()) {
        std::cout << "NO PATH" << std::endl;
        return NO_PATH;
    }

    Response response = answer.top().second;
    int pathLength = response.pathLength;
    std::cout << pathLength << std::endl;
    printMapResult(response.pathDots);

    return SUCCESS;
}






Response THandler::AStar(std::pair<int, int> source, std::pair<int, int> destination)
{
    std::priority_queue<std::pair<int, std::pair<int, int>>,
                        std::vector<std::pair<int, std::pair<int, int>>>,
                        std::greater<std::pair<int, std::pair<int, int>>>>
    priorityQueue;
 
    std::vector<std::vector<int>> distance(mapWidth, std::vector<int>(mapHeight, 0));
    std::vector<std::vector<std::pair<int, int>>> parent(mapWidth, std::vector<std::pair<int, int>>(mapHeight));

    distance[source.first][source.second] = 0;
    priorityQueue.emplace(0, source);

    Response response;
    response.pathLength = -1;
    response.pathCost   = 0;

    while (!priorityQueue.empty()) {
        std::pair<int, int> pointLower = priorityQueue.top().second;
        priorityQueue.pop();

        if (pointLower == destination) {

            response.pathLength = distance[pointLower.first][pointLower.second];
           
            while (pointLower != source) {
                response.pathCost += getCost(pointLower);
                response.pathDots.push(pointLower);
                pointLower = parent[pointLower.first][pointLower.second];
            }

            response.pathDots.push(source);
            return response;
        }

        for (int move = 0; move < movesQuantity; move++) {

            std::pair<int, int> neighbourPoint(pointLower.first + movesX[move], pointLower.second + movesY[move]);

            if (!isReachable(neighbourPoint))
                continue;

            double h = Heuristic(neighbourPoint, destination);
            double g = distance[pointLower.first][pointLower.second] + getCost(neighbourPoint); 

            if (!distance[neighbourPoint.first][neighbourPoint.second] || g < distance[neighbourPoint.first][neighbourPoint.second]) {
                distance[neighbourPoint.first][neighbourPoint.second] = g;
                parent[neighbourPoint.first][neighbourPoint.second] = pointLower;
                priorityQueue.emplace(h + g, neighbourPoint);
            }
        }
    }

    return response;
}


int Heuristic(std::pair<int, int> current, std::pair<int, int> destination)
{
    return abs(current.first - destination.first) + abs(current.second - destination.second);
}


int getValue(char sign)
{
    if (sign == ' ')
        return CORRIDOR;
    if (sign == '#')
        return WALL;
    if (sign == '.')
        return SAND;
    if (sign == 's')
        return START;

    return INCORRECT_VALUE;
}

void THandler::printMap()
{
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << this->source.first << ", " << this->source.second << std::endl;
    for (int i = 0; i < this->pointsFinish.size();i++)
    {
        std::cout << this->pointsFinish[i].first<< ", " << this->pointsFinish[i].second << std::endl;
    }

}

int THandler::getCost(std::pair<int, int> point)
{

    if (map[point.first][point.second] == CORRIDOR)
        return CORRIDOR_COST;

    if (map[point.first][point.second] == SAND)
        return SAND_COST; 

    return INCORRECT_VALUE;
}



bool THandler::isValid(std::pair<int, int> point)
{
    if (point.first > mapWidth - 1 || point.first < 0 ||
        point.second > mapHeight - 1 || point.second < 0)
    {
        return false;
    }
    return true;
}

bool THandler::isReachable(std::pair<int, int> point)
{
    return (isValid(point) && (map[point.first][point.second] != WALL)) ? true : false;
}


void THandler::addStartPoint(int value, int i, int j)
{
    if (value == START)
        this->source = std::make_pair(i, j);
}

void THandler::addFinishPoints(void)
{
    for (int j = 0; j < this->mapWidth; j++) {
        if (map[0][j] == 0) 
            this->pointsFinish.push_back(std::make_pair(0, j));
    }

    for (int j = 0; j < this->mapWidth; j++) {
        if (map[this->mapHeight - 1][j] == 0)
            this->pointsFinish.push_back(std::make_pair(this->mapHeight - 1, j));
    }

    for (int i = 0; i < this->mapHeight; i++) {
        if (map[i][0] == 0)
            this->pointsFinish.push_back(std::make_pair(i, 0));
    }

    for (int i = 0; i < this->mapHeight; i++) {
        if (map[i][this->mapWidth - 1] == 0)
            this->pointsFinish.push_back(std::make_pair(i, this->mapWidth - 1));
    }
}






void THandler::printMapResult(std::stack<std::pair<int, int>> pathDots)
{
    pathDots.pop();
    while (!pathDots.empty())
    {
        std::pair<int, int> point = pathDots.top();
        map[point.first][point.second] = 4;
        pathDots.pop();
    }



    for (int i = 0; i < mapHeight; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if (map[i][j] == CORRIDOR)
                std::cout << ' ';
            if (map[i][j] == WALL)
                std::cout << '#';
            if (map[i][j] == SAND)
                std::cout << '.';
            if (map[i][j] == START)
                std::cout << 's';
            if (map[i][j] == PATH)
                std::cout << '*';
        }
        std::cout << std::endl;
    }
}
