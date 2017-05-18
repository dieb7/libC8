#ifndef simpleC8Random_H
#define simpleC8Random_H

#include <cstdlib>
#include "C8Random.h"

class SimpleC8Random : public C8Random
{
    public:
        SimpleC8Random();
        virtual ~SimpleC8Random();

        int Gen() {return rand();};

    protected:

    private:
};

#endif // simpleC8Random_H
