#include "gameutil.h"

namespace game_framework
{
    class Box
    {
    public:
        Box();
        ~Box();

    private:
        CMovingBitmap image; // �Ϥ�
        bool goal;           // �O�_�w�g��F���I
    };

}
