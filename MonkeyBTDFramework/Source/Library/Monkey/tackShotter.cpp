#define PI 22 / 7

#include <iostream>
#include <vector>
#include "./tackShotter.h"

using namespace std;

namespace game_framework
{
    TackShotter::TackShotter()
    {
        _name = "TackShotter";
        _speed = 1;
        _cost = 340;
        _LeftSkillCost = 180;
        _RightSkillCost = 90;
        _range = 70;
        _sell.push_back(300);
        _sell.push_back(444);
        _sell.push_back(372);
        _sell.push_back(516);
        _leftSkill = false;
        _rightSkill = false;
    }

    TackShotter::~TackShotter()
    {
        _sell.clear();
    }

    string TackShotter::getName()
    {
        return _name;
    }

    int TackShotter::getSpeed()
    {
        return _speed;
    }

    int TackShotter::getCost()
    {
        return _cost;
    }

    int TackShotter::getLeftSkillCost()
    {
        return _LeftSkillCost;
    }

    int TackShotter::getRightSkillCost()
    {
        return _RightSkillCost;
    }

    int TackShotter::getRange()
    {
        return _range;
    }

    int TackShotter::getSell(int index)
    {
        return _sell[index];
    }

    bool TackShotter::getLeftSkill()
    {
        return _leftSkill;
    }

    bool TackShotter::getRightSkill()
    {
        return _rightSkill;
    }
}