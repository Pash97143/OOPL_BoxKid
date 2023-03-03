#define PI 22 / 7

#include <iostream>
#include <vector>
#include "./dartMonkey.h"

using namespace std;

namespace game_framework
{
    DartMonkey::DartMonkey()
    {
        _name = "DartMonkey";
        _speed = 2;
        _cost = 250;
        _LeftSkillCost = 180;
        _RightSkillCost = 80;
        _range = 100;
        _sell.push_back(220);
        _sell.push_back(364);
        _sell.push_back(284);
        _sell.push_back(428);
        _leftSkill = false;
        _rightSkill = false;
    }
    DartMonkey::~DartMonkey()
    {
        _sell.clear();
    }
    string DartMonkey::getName()
    {
        return _name;
    }
    int DartMonkey::getSpeed()
    {
        return _speed;
    }
    int DartMonkey::getCost()
    {
        return _cost;
    }
    int DartMonkey::getLeftSkillCost()
    {
        return _LeftSkillCost;
    }
    int DartMonkey::getRightSkillCost()
    {
        return _RightSkillCost;
    }
    int DartMonkey::getRange()
    {
        return _range;
    }
    int DartMonkey::getSell(int index)
    {
        return _sell[index];
    }
    bool DartMonkey::getLeftSkill()
    {
        return _leftSkill;
    }
    bool DartMonkey::getRightSkill()
    {
        return _rightSkill;
    }

};
