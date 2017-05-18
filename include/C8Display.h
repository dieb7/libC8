#ifndef C8DISPLAY_H
#define C8DISPLAY_H


class C8Display
{
public:
    C8Display();
    virtual ~C8Display();

    virtual void Clear() = 0;

    virtual bool Draw(unsigned char x, unsigned char y, unsigned char data) = 0;

    virtual void setPixel(unsigned char x, unsigned char y, bool val) = 0;
    virtual bool getPixel(unsigned char x, unsigned char y) = 0;

    virtual bool shouldDraw() = 0;
    virtual void drawn() = 0;

protected:

private:
};

#endif // C8DISPLAY_H
