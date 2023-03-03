#include <iostream>
#include <vector>
#include "../gameutil.h"

using namespace std;

namespace game_framework
{
    class DartMonkey
    {
    public:
        DartMonkey();
        ~DartMonkey();
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
        CMovingBitmap _image;
        CMovingBitmap _bulletImage;
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
