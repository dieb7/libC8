#ifndef D_SimpleC8Display_H
#define D_SimpleC8Display_H

#include "C8Display.h"

///////////////////////////////////////////////////////////////////////////////
//
//  SimpleC8Display is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class SimpleC8Display : public C8Display
{
public:
    SimpleC8Display();
    virtual ~SimpleC8Display();

    void Clear();

    bool Draw(unsigned char x, unsigned char y, unsigned char data);

    void setPixel(unsigned char x, unsigned char y, bool val);
    bool getPixel(unsigned char x, unsigned char y);

    bool shouldDraw()
    {
        return drawFlag;
    };
    void drawn()
    {
        drawFlag = false;
    };

private:
    bool drawFlag;

    unsigned char  mem[8][32];

};

#endif  // D_SimpleC8Display_H
