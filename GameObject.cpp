#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
#include "Point2D.h"
#include "Model.h"
using namespace std;

GameObject::GameObject(char in_code) //constructor, sets display_code via input, id to 1, and state to 0
    {
        this->display_code = in_code;
        this->id_num = 1;
        this->state = 0;

        cout << "GameObject constructed" << endl;
    }
GameObject::GameObject(Point2D in_loc, int in_id, char in_code) //constructor, sets display code with input, id, location, and state to 0
    {
        this->display_code = in_code;
        this->id_num = in_id;
        this->location = in_loc;
        this->state = 0;
        cout << "GameObject constructed" << endl;
    }
GameObject::~GameObject()
    {
        cout << "GameObject destructed." << endl;
    }
Point2D GameObject::GetLocation() //returns the location for this object
    {
        return this->location;
    }
int GameObject::GetId() //returns the id for this object
    {
        return id_num;
    }
char GameObject::GetState() //returns the state for this object
    {
        return state;
    }
void GameObject::ShowStatus() //Outputs the information contained in class "(display_code)(id_num) at (location)"
    {
        cout << this->display_code << this->id_num << " at " << this->location << endl;
    }
void GameObject::DrawSelf(char *ptr)
    {
        if(this->id_num<10)
        {
        ptr[0] = this->display_code;
        ptr[1] = '0' + this->id_num; //ASCII conversion
        }
        else //case for id_num greater than 10
        {
            int num = this->id_num; //ex. 12
            string s = to_string(num);
            vector<int> digits;

            for (char c : s) 
            {
                digits.push_back(c - '0'); // Convert char '1' to int 1
            }
            int first = digits[0];
            int next = digits[1];
            ptr[0] = '0' + first;
            ptr[1] = '0' + next; //ASCII conversion
        }
    }
void GameObject::save(ofstream& file)
{
    file << this->display_code << endl;
    file << this->id_num << endl;
    file << (int) (unsigned char) this->state << endl; //cast to int
    file << this->location.x << endl;
    file << this->location.y << endl;
}

void GameObject::restore(ifstream& file, Model& model)
{
    file >> this->display_code;
    file >> this->id_num;
    int tempState; //temp cast
    file >> tempState;
    this->state = (char)tempState; //cast to char from int
    file >> this->location.x;
    file >> this->location.y;
}

char GameObject::GetDisplayCode()
{
    return this->display_code;
}