#ifndef C8RANDOM_H
#define C8RANDOM_H

#include <cstdlib>

class C8Random
{
    public:
        C8Random();
        virtual ~C8Random();

        int Gen() {return rand();};

    protected:

    private:
};

#endif // C8RANDOM_H
