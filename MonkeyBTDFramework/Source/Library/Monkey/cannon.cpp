#define PI 22 / 7

#include <iostream>
#include <vector>
#include "./cannon.h"

using namespace std;

namespace game_framework
{
    Cannon::Cannon()
    {
        _name = "Cannon";
        _speed = 1;
        _cost = 520;
        _LeftSkillCost = 380;
        _RightSkillCost = 180;
        _range = 120;
        _sell.push_back(460);
        _sell.push_back(764);
        _sell.push_back(604);
        _sell.push_back(908);
        _leftSkill = false;
        _rightSkill = false;
    }

    Cannon::~Cannon()
    {
        _sell.clear();
    }

    string Cannon::getName()
    {
        return _name;
    }

    int Cannon::getSpeed()
    {
        return _speed;
    }

    int Cannon::getCost()
    {
        return _cost;
    }

    int Cannon::getLeftSkillCost()
    {
        return _LeftSkillCost;
    }

    int Cannon::getRightSkillCost()
    {
        return _RightSkillCost;
    }

    int Cannon::getRange()
    {
        return _range;
    }

    int Cannon::getSell(int index)
    {
        return _sell[index];
    }

    bool Cannon::getLeftSkill()
    {
        return _leftSkill;
    }

    bool Cannon::getRightSkill()
    {
        return _rightSkill;
    }
}