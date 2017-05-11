#ifndef D_C8Display_H
#define D_C8Display_H

///////////////////////////////////////////////////////////////////////////////
//
//  C8Display is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class C8Display
{
public:
    explicit C8Display();
    virtual ~C8Display();

    void Clear();

    bool Draw(unsigned char x, unsigned char y, unsigned char data);

    void setPixel(unsigned char x, unsigned char y, bool val);
    bool getPixel(unsigned char x, unsigned char y);

private:

    C8Display(const C8Display&);
    C8Display& operator=(const C8Display&);

    unsigned char  mem[8][32];

};

#endif  // D_C8Display_H
