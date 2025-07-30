#ifndef DATASINKERROUTER_H
#define DATASINKERROUTER_H
#include "ISinkerRouter.h"
class DataSinkerRouter : public ISinkerRouter {
public:
    DataSinker* createSinkerForSend(DataHeaderUtils::PayloadType type) override;
    DataSinker* createSinkerForReceive(DataHeaderUtils::PayloadType type) override;
};

#endif // DATASINKERROUTER_H
