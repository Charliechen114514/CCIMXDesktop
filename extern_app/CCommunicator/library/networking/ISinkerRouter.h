#ifndef ISINKERROUTER_H
#define ISINKERROUTER_H
#include "DataHeader.h"
#include "DataSinker.h"
class ISinkerRouter {
public:
    virtual ~ISinkerRouter() = default;
    virtual DataSinker* createSinkerForSend(DataHeaderUtils::PayloadType type)
        = 0;

    virtual DataSinker* createSinkerForReceive(DataHeaderUtils::PayloadType type)
        = 0;
};

#endif // ISINKERROUTER_H
