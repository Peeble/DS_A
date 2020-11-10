#include <iostream>
#include <vector>
#include <random>

// Not an entirely working solution
// Populates a vector with Points objects, randomly generates x and y values for each object
// Distance between points is put into an array and then sorted
// then print value of [0] value of array

struct Points
{
    double x, y;
};

class UnitSquare
{
public:
    std::vector<Points> mySquare;

    void output()
    {
        populate(mySquare);

        double distances[10];

        for (int i = 0; i < 9; i++)
        {
            for (int j = i + 1; j < 9; j++)
            {
            distances[i] = distance(mySquare[i], mySquare[j]);
            std:: cout << "Distance between: (" << mySquare[i].x << ", " << mySquare[i].y << ") and (" << mySquare[j].x << ", " << mySquare[j].y << ") is: " << distances[i] << std::endl;
            }
        }
        // not working
        std::sort(distances, distances+10);

        std::cout << "Shortest distance between points is: " << distances[0];
    }

private:
    void populate(std::vector<Points> &vect)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<> dist(0, 1);
        
        for (int i = 0; i <= 10; i++)
        {
            Points temp;
            temp.x = dist(rng);
            temp.y = dist(rng);

            vect.push_back(temp);
        }

        std::cout << "Vector size: " << vect[10].y << std::endl;
    }

    double distance(Points one, Points two)
    {
        double result = sqrt(pow((two.x - one.x), 2) + pow((two.y - one.y), 2)); 
        return result;
    }
};