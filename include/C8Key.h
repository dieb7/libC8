#ifndef D_C8Key_H
#define D_C8Key_H

///////////////////////////////////////////////////////////////////////////////
//
//  C8Key is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class C8Key
{
public:
    explicit C8Key();
    virtual ~C8Key();

    void Push(unsigned char k);
    void Release(unsigned char k);
    bool Get(unsigned char k);

    void Clear()
    {
        keys = 0;
    };

private:

    C8Key(const C8Key&);
    C8Key& operator=(const C8Key&);

    unsigned short keys;

    unsigned short getMask(unsigned char k)
    {
        return 0x1 << k;
    }

};

#endif  // D_C8Key_H
