#ifndef DATAPROTOCOLIZEDCONTROLLER_H
#define DATAPROTOCOLIZEDCONTROLLER_H
#include "DataHeader.h"
#include "DataSinkerRouter.h"
#include <QObject>
class QSaveFile;
class ISinkerRouter;
class QElapsedTimer;
class DataSinker;
class DataProtocolizedController : public QObject {
    Q_OBJECT
public:
    explicit DataProtocolizedController(QObject* parent = nullptr, ISinkerRouter* sinker = new DataSinkerRouter);
    ISinkerRouter* get_router() const { return router; }

    ~DataProtocolizedController();
    /**
     * @brief reset reset the protocal machines
     */
    void reset();

public slots:
    void sendData(
        DataSinker* send_sinker,
        int chunkSize = DataHeaderUtils::DEF_CHUNK_SZ,
        qint64 startOffset = 0);
    void onBytes(const QByteArray& bytes);
signals:
    // frame is ready to be sent to other places
    void frameReady(const QByteArray& frame);
    // process for sendings
    void sendProgress(quint64 sent, quint64 total);
    // receiving process
    void receiveProgress(const QString& fileId, quint64 received, quint64 total);
    // parse dead :(
    void protocolError(const QString& reason);
    // parsing dead
    void parsingBad();
    // OK buffer
    void bufferOk(DataSinker* okSinker);

private:
    static constexpr int PARSE_TIMEOUT_MS = 5000;
    void sendStartFrame(quint64 fileId,
                        const QString& name,
                        quint64 totalSize);
    void sendDataFrame(quint64 fileId,
                       quint64 offset,
                       const QByteArray& chunk,
                       quint64 totalSize);
    void sendEndFrame(quint64 fileId,
                      quint64 totalSize);

    void parse();

    bool parseHeader();
    bool parseName();
    bool parseData();

    bool ensureSize(int need) const;

    DataHeaderUtils::DataHeader internal_header;
    QByteArray rx_buffer;
    quint64 sendFileSize { 0 };
    quint64 sendFileHasSent { 0 };
    DataHeaderUtils::CurrentState state {
        DataHeaderUtils::CurrentState::ReadingHeader
    };

    QString curFileIdStr; // string 形式的 fileId（方便信号里传）
    quint64 curReceived { 0 };

    DataSinker* send_sinker { nullptr };
    DataSinker* receive_sinker { nullptr };
    ISinkerRouter* router;
    QElapsedTimer* elapsed_timeout;
};

#endif // DATAPROTOCOLIZEDCONTROLLER_H
