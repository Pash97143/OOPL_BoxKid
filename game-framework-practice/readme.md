# Leistungsstarkes Game Framework

LGF (Leistungsstarkes Game Framework) �O�@�ڰ�󳯰��ͦѮv�� Game Framework �[�W�ǳ\�\�઺ Powerful Game Framework�C

�M�פ��O�Ҫ������@�A��������D�Ϊ̥����L�Q�n�� feature�A�Х� issue�A���ϥδr�� :D

## Installation

1. �N���M�� clone �U��
2. �����즳�� Game Framework / �����ϥγo�� Game Framework.

�]�򥻤W�O�ۮe���®ج[���A�]���O����®ج[�s�W��h�� feature �H�έץ� bug�^

## Feature

### 2022-03-06

-   �ץ��F `CInteger` �� Bug�A�{�b�i�H���`�e�{�C
-   **�b�ץ�**�F `CMovingBitmap.showBitmap(double factor)` �� Bug�A�� `factor` ���� `0` �ɵ������ùϤ��C
-   �i�H���� `CMovingBitmap` ���Ϥ��C
-   �i�HŪ�J�h�� `CMovingBitmap` ���Ϥ��A�åB��ܱ��e�{���Ϥ��C
-   �i�HŪ�J�h�� `CMovingBitmap` ���Ϥ��A�åB�Q�� `SetAnimation(int delay, bool once)` �ӻs�@�ʵe�C
-   �o�� `CAnimation` ���@�k�C

### 2022-03-11

-   �� `CInteger` �i�H�ۥ���ܬO�_�n��ܫe�ɹs�C

### 2022-06-17

-   �iNew Feature�j�ץ��F���ù��ɪ�������D�A�åB�|�N�C����������m���C
-   �iNew Feature�j�N�ʵe�C�V������[�W��Ǯɶ��C
-   �iNew Feature�j�䴩�H `vector<string>` Ū���C�V���e���C
-   �iNew Feature�j�s�W�F `CTextDraw` ���O�A**�e�W��r�ɽШϥγo�����O���禡�A���ù����r�첾�~�|���T**
-   �iBug�j�ץ��F CMovngBitmap �b����ʵe�ɷ|�X�{���p bug�C

### 2023-02-22

-   �ХߤF�²b���]Purified�^�� Leistungsstarkes Game Framework �M�סA�i�����ظm��רð���C
-   �ק�F�ɮ׬[�c�A�q����N�Ҧ��� `.cpp` ��J `Source` ��Ƨ��A�אּ�b `Source` �إߤ@�Ӹ�Ƨ��[�c�Ӧs�� `.cpp` �ɮסC
-   �ק�F�ɮ׬[�c�A�N `/RES` ���s�R�W�� `Resources` ����M�W�١C
-   �Х� `GAME_TITLE` ���w�q�]`#define`�^�A�Ϯج[�ϥΪ̯���ܧ�C�����D�C
-   �N `mygame.cpp` ���Φ��T�Ӥ��P���ɮסA���O��@ `GameStateInit`�B`GameStateRun` �P `GameStateOver` �����O�C
-   ���c�F������ code �ϱo���ƪ� code �X�{�����ƴ�֡C
-   �����C���]�w�ѼƦ� `config.cpp`�A���ϥΪ̤����]������� `/Library` �P `/Core` ���{���X�C

## Documents

### void CMovingBitmap::LoadBitmap(char\* , COLORREF)

Ū���@�i�Ϥ��C

```c++
CMovingBitmap bitmap;
bitmap.LoadBitmap("RES/bitmap.bmp", RGB(255, 255, 255));
bitmap.SetLeftRight(0, 0);

# -- on show --

bitmap.ShowBitmap();
```

### void CMovingBitmap::LoadBitmap(vector<char\*>, COLORREF = CLR_INVALID);

Ū���h�i�Ϥ��A���ޭȱq `0` �}�l�C

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"}, RGB(255, 255, 255));
bitmap.SetLeftRight(0, 0);

# -- on show --

bitmap.ShowBitmap(); // �w�]�e�{�Ĥ@�i (index = 0)�C
```

### void CMovingBitmap::UnshowBitmap()

���÷�e�� `CMovingBitmap`�C

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.setLeftRight(0, 0);

# -- on show --
bitmap.showBitmap(); // �w�]�e�{�Ĥ@�i (index = 0)�C

/* Do something... */

bitmap.UnShowBitmap(); // ���ùϤ��C
```

### void CMovingBitmap::SelectShowBitmap(int select)

��ܭn�e�{�� `CMovingBitmap`�C

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetLeftRight(0, 0);
bitmap.SelectShowBitmap(1); // �]�w�e�{�ĤG�i�Ϥ�

# -- on show --

bitmap.showBitmap(); // �e�{�ĤG�i�Ϥ�
```

### void CMovingBitmap::SetAnimation(int delay, bool once)

�]�w��e�� `CMovingBitmap` ���@�Ӱʵe�C

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetLeftRight(0, 0);
bitmap.SelectShowBitmap(1); // �]�w�e�{�ĤG�i�Ϥ�
bitmap.SetAnimation(5, false); // �L���`���e�{

# -- on show --

bitmap.showBitmap(); // �e�{�ĤG�i�Ϥ�
```

### void CInteger::ShowBitmap(bool leadingZero)

��� `CInteger` �O�_�X�{�e�ɹs�C

```cpp
CInteger health = CInteger(4); //�]�w�̤j���׬� 4�A�w�]�� 5�C
health.SetInteger(1000);
health.SetTopLeft(312, 373);

# -- on show --
health.showBitmap(false); // ����ܫe�ɹs
```

### void CMovingBitmap::LoadBitmapByString(vector\<string> filename, COLORREF color)

�Q�� `vector<string>` Ū���h�i�Ϥ��A���ޭȱq `0` �}�l�C

```cpp
CMovingBitmap bitmap;
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.setLeftRight(0, 0);

# -- on show --
bitmap.showBitmap(); // �w�]�e�{�Ĥ@�i (index = 0)�C

/* Do something... */

bitmap.UnShowBitmap(); // ���ùϤ��C
```

### int CMovingBitmap::GetSelectShowBitmap()

��o�ثe�e�{���Ϥ����ޭȡC

### bool CMovingBitmap::IsAnimationDone()

�T�{�ʵe�O�_���b����A�ȭ���ʵe���b���� `ToggleAnimation()`�C

### void CMovingBitmap::ToggleAnimation()

�B��ʵe�@���A�åB�ϱo `IsAnimationDone()` �i�ΡC

### int CMovingBitmap::GetMovingBitmapFrame()

�T�{�o�� `CMovingBitmap` ���󦳦h�ִV�ʵe�C

### void CTextDraw::ChangeFontLog(CDC \*pDC, int size, string fontName, int weight)

����r���˦��B��r�P����C

```cpp
CDC *pDC = CDDraw::GetBackCDC();
CFont *fp;

pDC->SetBkMode(TRANSPARENT);
pDC->SetTextColor(RGB(255, 255, 255));

/* �ܧ�r��Aweight = 800 ������A500 ���@�� */
CTextDraw::ChangeFontLog(pDC, fp, 40, "Noto Sans TC", 800);
CTextDraw::Print(pDC, 50, 50, "Hello World!");
```

### void CTextDraw::Print(CDC \*pDC, int x, int y, string str)

�N��r�e�{�b���w���y�ФW�C

```cpp
CDC *pDC = CDDraw::GetBackCDC();
CFont *fp;

pDC->SetBkMode(TRANSPARENT);
pDC->SetTextColor(RGB(255, 255, 255));

/* �ܧ�r�� */
CTextDraw::ChangeFontLog(pDC, fp, 40, "Noto Sans TC");
CTextDraw::Print(pDC, 50, 50, "Hello World!");
```

## Example

### ���@�Ӫ��󤣰����ʵe�`��

```cpp
CMovingBitmap bitmap;

# -- onInit --
bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);
bitmap.SetAnimation(5, false);

# -- onShow --

bitmap.showBitmap();
```

### �I��@�Ӫ��󤧫����ʵe

```cpp
CMovingBitmap bitmap;

# -- onInit --

bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);
bitmap.SetAnimation(200, false);

# -- onEvent --
bitmap.ToggleAnimation(1);

# -- onShow --

if(bitmap.IsAnimationDone()){
    if (hidden_code[current_stage][i][j] == 0) {
		bitmap.showBitmap();
    }
}else{
    bitmap.showBitmap();
}
```

### �P�@�Ӫ���e�{���P�Ϥ�

```cpp
CMovingBitmap bitmap;

# -- onInit --

bitmap.LoadBitmap({"RES/bitmap1.bmp", "RES/bitmap2.bmp"});
bitmap.SetTopLeft(0, 0);

# -- onMove --
bitmap.SelectShowBitmap(1)

# -- onShow --
bitmap.showBitmap();
```

## ����

���� ��߻O�_��ޤj�� �����ͱб� �}�o�F�o�ӹC���ج[

�åB���� ��߻O�_��ޤj�� ���Ӻ~�б� �P�N�o�Ӯج[������}�ϥΡC
