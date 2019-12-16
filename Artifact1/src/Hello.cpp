#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> lanes(4);
std::string::size_type lastHole;
std::string::size_type trackLength;

struct Position
{
    unsigned int speed;
    unsigned int x;
    vector<unsigned int> y;
};

// Returns lives and best move
pair<unsigned int, std::string> decide(Position position) // We use unsigned int throughout because everything will be 0 or positive.
{
    // If bike hasn't reached end
    if (position.x >= lastHole)
        return {0, "WAIT"};

    // Move forward
    if (position.speed == 0)
        return {0, "SPEED"};

    pair<unsigned int, string> minLives = {position.y.size(), "WAIT"};

    // Increase speed to make it to the end.
    {
    	Position newPosition = position;
        newPosition.speed += 1;
        newPosition.x += newPosition.speed;

        for (auto y : position.y)
        {
            for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
                    break;
                }
            }
        }

        if (newPosition.y.size() > 0)
        {
            unsigned int lives = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
            if (lives == 0)
                return {0, "SPEED"};

            if (lives < minLives.first)
                minLives = {lives, "SPEED"};
        }
    }

    // Keep going
    {
    	Position newPosition = position;
        newPosition.x += newPosition.speed;

        for (auto y : position.y)
        {
            for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
                    break;
                }
            }
        }

        if (newPosition.y.size() > 0)
        {
            unsigned int lives = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
            if (lives == 0)
                return {0, "WAIT"};

            if (lives < minLives.first)
                minLives = {lives, "WAIT"};
        }
    }

    // Jump
    {
    	Position newPosition = position;
        newPosition.x += newPosition.speed;

        for (auto y : position.y)
        {
            if (lanes[y][newPosition.x] == '0')
                newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
        }

        if (newPosition.y.size() > 0)
        {
            unsigned int lives = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
            if (lives == 0)
                return {0, "JUMP"};

            if (lives < minLives.first)
                minLives = {lives, "JUMP"};
        }
    }

    // Try moving up
    if (std::find(position.y.begin(), position.y.end(), 0) == position.y.end())
    {
    	Position newPosition = position;
        newPosition.x += newPosition.speed;
        newPosition.y = {};

        for (auto y : position.y)
        {
            bool stillAlive = true;
            for (unsigned int x = position.x + 1; x <= newPosition.x - 1; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }
            for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
            {
                if (lanes[y-1][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }

            if (stillAlive)
                newPosition.y.push_back(y - 1);
        }

        if (newPosition.y.size() > 0)
        {
            unsigned int lives = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
            if (lives == 0)
                return {0, "UP"};

            if (lives < minLives.first)
                minLives = {lives, "UP"};
        }
    }

    // Try moving down
    if (std::find(position.y.begin(), position.y.end(), lanes.size()-1) == position.y.end())
    {
    	Position newPosition = position;
        newPosition.x += newPosition.speed;
        newPosition.y = {};

        for (auto y : position.y)
        {
            bool stillAlive = true;
            for (unsigned int x = position.x + 1; x <= newPosition.x - 1; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }
            for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
            {
                if (lanes[y+1][x] == '0')
                {
                    stillAlive = false;
                    break;
                }
            }

            if (stillAlive)
                newPosition.y.push_back(y + 1);
        }

        if (newPosition.y.size() > 0)
        {
            unsigned int lives = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
            if (lives == 0)
                return {0, "DOWN"};

            if (lives < minLives.first)
                minLives = {lives, "DOWN"};
        }
    }

    // Slow down
    if (position.speed > 1)
    {
    	Position newPosition = position;
        newPosition.speed -= 1;
        newPosition.x += newPosition.speed;

        for (auto y : position.y)
        {
            for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
            {
                if (lanes[y][x] == '0')
                {
                    newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
                    break;
                }
            }
        }

        if (newPosition.y.size() > 0)
        {
            unsigned int lives = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
            if (lives == 0)
                return {0, "SLOW"};

            if (lives < minLives.first)
                minLives = {lives, "SLOW"};
        }
    }

    // Goal is for all bikes to make it.
    return minLives;
}

int main()
{
    int M; // the amount of motorbikes to control
    cin >> M;
    cin.ignore();
    int V; // the minimum amount of motorbikes that must survive
    cin >> V;
    cin.ignore();
    cin >> lanes[0];
    cin.ignore();
    cin >> lanes[1];
    cin.ignore();
    cin >> lanes[2];
    cin.ignore();
    cin >> lanes[3];
    cin.ignore();

    lastHole = 0;
    lastHole = max(lastHole, (lanes[0].rfind('0') != string::npos) ? lanes[0].rfind('0') : 0);
    lastHole = max(lastHole, (lanes[1].rfind('0') != string::npos) ? lanes[1].rfind('0') : 0);
    lastHole = max(lastHole, (lanes[2].rfind('0') != string::npos) ? lanes[2].rfind('0') : 0);
    lastHole = max(lastHole, (lanes[3].rfind('0') != string::npos) ? lanes[3].rfind('0') : 0);
    trackLength = lanes[0].length();

    // game loop
    while (1) {
        int S; // I feel the need, the need for speed!
        cin >> S;
        cin.ignore();

        Position currentPosition;
        currentPosition.speed = S;

        for (int i = 0; i < M; i++) {
            int X; // x coordinate of the motorbike
            int Y; // y coordinate of the motorbike
            int A; // indicates whether the motorbike is activated "1" or destroyed "0"
            cin >> X >> Y >> A; cin.ignore();

            if (A) {
                currentPosition.x = X;
                currentPosition.y.push_back(Y);
            }
        }

        cout << decide(currentPosition).second << endl;
    }
}
