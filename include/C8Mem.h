#ifndef C8MEM_H
#define C8MEM_H


class C8Mem
{
public:
    C8Mem();
    virtual ~C8Mem();

    virtual unsigned char Get(unsigned int address) = 0;
    virtual void Set(unsigned int address, unsigned char val) = 0;

protected:

private:
};

#endif // C8MEM_H
