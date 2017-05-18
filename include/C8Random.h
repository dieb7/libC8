#ifndef C8RANDOM_H
#define C8RANDOM_H


class C8Random
{
public:
    C8Random();
    virtual ~C8Random();

    virtual int Gen() = 0;

protected:

private:
};

#endif // C8RANDOM_H
