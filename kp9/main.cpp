#include <iostream>

using namespace std;

class Point{
private:
    float _x = 0, _y = 0;

    int GetQuadrant(){
        if (_y >= 0){
            if (_x >= 0){
                return 1;
            }
            else{
                return 2;
            }
        }
        else{
            if (_x < 0){
                return 3;
            }
            else{
                return 4;
            }
        }
    }
public:
    Point() = default;

    Point(float x, float y)
    {
        _x = x;
        _y = y;
    }

    ~Point(){
    }

    void Input(){
        cout << "Input x coordinate: " << endl;
        cin >> _x;
        cout << "Input y coordinate: " << endl;
        cin >> _y;
    }

    void ShowPoints(){
        cout << "Points coordinates" << endl;
        cout << "x = " << _x << endl;
        cout << "y = " << _y << endl;
        cout << endl;
    }

    void ShowQuadrant(){
        int quadrant = GetQuadrant();
        cout << "The point is situated in " << quadrant << " quadrant" << endl;
    }

    Point operator++(){
        _x++;
        return *this;
    }

    Point operator++(int){
        _y++;
        return *this;
    }

    Point operator--(){
        _x--;
        return *this;
    }

    Point operator--(int){
        _y--;
        return *this;
    }

    bool operator==(Point point){
        if (_x == point._x && _y == point._y)
        {
            return true;
        }
        else{
            return false;
        }
    }
};

int main(){
    Point point;
    ++point;
    --point;
    point++;
    point++;
    while (true) {
        int k;
        cout << "1. Input coordinates \n2. Show point \n3. In which quadrant point is"
                "\n4. Increase x-coordinate by one \n5. Increase y-coordinate by one"
                "\n6. Decrease x-coordinate by one \n7. Decrease y-coordinate by one"
                "\n8. Create a new point and compare with current \n9. Exit \n";
        scanf("%i", &k);

        switch (k) {
            case 1:
                point.Input();
                continue;
            case 2:
                point.ShowPoints();
                continue;
            case 3:
                point.ShowQuadrant();
                continue;
            case 4:
                ++point;
                point.ShowPoints();
                continue;
            case 5:
                point++;
                point.ShowPoints();
                continue;
            case 6:
                --point;
                point.ShowPoints();
                continue;
            case 7:
                point--;
                point.ShowPoints();
                continue;
            case 8:
            {
                point.ShowPoints();
                Point newPoint;
                newPoint.Input();

                if (newPoint == point) {
                    cout << "Points are equal" << endl;
                } else {
                    cout << "Points are different" << endl;
                }
            }
                continue;
            case 9:
                return 0;
            default:
                continue;
        }
    }
}