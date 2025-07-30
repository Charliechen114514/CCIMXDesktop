#include "DataSinkerRouter.h"
#include "FileSinker.h"
#include "ImageSinker.h"
#include "MemorySinker.h"
#include "MetaInfoSinker.h"
DataSinker* DataSinkerRouter::createSinkerForSend(DataHeaderUtils::PayloadType type) {
    switch (type) {
    case DataHeaderUtils::PayloadType::Text:
        return new MemorySinker;
    case DataHeaderUtils::PayloadType::Image:
        return new ImageSinker("");
    case DataHeaderUtils::PayloadType::File:
        return new FileSinker("");
    case DataHeaderUtils::PayloadType::UnPublicMeta:
        return new MetaInfoSinker;
    default:
        return new MemorySinker;
    }
}

DataSinker* DataSinkerRouter::createSinkerForReceive(DataHeaderUtils::PayloadType type) {
    switch (type) {
    case DataHeaderUtils::PayloadType::Text:
        return new MemorySinker;
    case DataHeaderUtils::PayloadType::Image:
        return new ImageSinker("");
    case DataHeaderUtils::PayloadType::File:
        return new FileSinker("");
    case DataHeaderUtils::PayloadType::UnPublicMeta:
        return new MetaInfoSinker;
    default:
        return new MemorySinker;
    }
}
