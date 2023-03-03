#include <iostream>
#include <vector>
using namespace std;

namespace game_framework
{
    class TackShotter
    {
    public:
        TackShotter();
        ~TackShotter();
        string getName();
        int getSpeed();
        int getCost();
        int getLeftSkillCost();
        int getRightSkillCost();
        int getRange();
        int getSell(int index);
        bool getLeftSkill();
        bool getRightSkill();

    private:
        string _name;
        int _speed;
        int _cost;
        int _LeftSkillCost;
        int _RightSkillCost;
        int _range;
        vector<int> _sell;
        bool _leftSkill;
        bool _rightSkill;
    };
}
