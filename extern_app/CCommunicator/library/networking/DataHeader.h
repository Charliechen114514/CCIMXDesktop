#ifndef DATAHEADER_H
#define DATAHEADER_H
#include <QByteArray>
#include <QtTypes>
namespace DataHeaderUtils {

#pragma pack(push, 1)
struct DataHeader {
    quint32 header_magic;
    quint16 protocol_version;
    quint8 current_state;
    quint8 payload_type;
    quint64 fileId;
    quint64 offset;
    quint64 totalSize;
    quint32 nameLen;
    quint32 payloadSize;
    quint32 header_crc;
};
#pragma pack(pop)

static constexpr const unsigned int
    DATAHEADER_SIZE
    = sizeof(DataHeader);

static constexpr quint32 HEADER_MAGIC = 0x00114514; //
static constexpr quint16 HEADER_VERSION = 1;

static constexpr const unsigned int DEF_CHUNK_SZ = 16 * 1024;

enum class OperationState : quint8 {
    Start = 1, ///< At header stage
    Data = 2,
    End = 3 ///< OK finished
};

enum class PayloadType {
    Text,
    Image,
    File,
    UnPublicMeta
};

enum class CurrentState {
    ReadingHeader,
    ReadingName,
    ReadingPayload
};

/**
 * @brief packUpHeader packup headers to the target
 * @return bytearrays for transmit
 */
QByteArray packUpHeader(const DataHeader& h);

/**
 * @brief readOutHeader readout header from stream, these is protocal session
 * @param stream_prepared
 * @param h
 * @return
 */
bool readOutHeader(QDataStream& stream_prepared, DataHeader& h);

/**
 * @brief fileId_generation
 * @return the fileID
 */
quint64 fileId_generation();

void printDataHeader(const DataHeader& header);

} ///< data header utils end

#endif // DATAHEADER_H
