#include "gameutil.h"

namespace game_framework
{
    class Box
    {
    public:
        Box();
        ~Box();

    private:
        CMovingBitmap image; // 圖片
        bool goal;           // 是否已經到達終點
    };

}
