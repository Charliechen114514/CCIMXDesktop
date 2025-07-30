#include "FileSinker.h"

FileSinker::FileSinker(const QString& filePath, int chunkSize)
    : DataSinker(DataHeaderUtils::PayloadType::File)
    , filePath_(filePath)
    , chunkSize_(chunkSize)
    , file_(filePath) { }

void FileSinker::setFilePath(const QString& filePath) {
    filePath_ = filePath;
    file_.setFileName(filePath_);
}

QString FileSinker::provide_name() {
    return QFileInfo(filePath_).fileName();
}

quint64 FileSinker::size() {
    return QFileInfo(filePath_).size();
}

qint64 FileSinker::id_generator() {
    return DataHeaderUtils::fileId_generation();
}

bool FileSinker::receiveEnd() {
    if (saveFile_) {
        if (!saveFile_->commit()) {
            qCritical() << "[FileDataSinker] commit() failed:" << saveFile_->errorString();
            saveFile_->cancelWriting();
            saveFile_.reset(nullptr);
            return false;
        }
        saveFile_.reset(nullptr);
        emit accept_data_receive();
    }
    return true;
}

void FileSinker::consume_name(const QString& name) {
    QString saveFileName = QFileInfo(name).baseName() + "_received." + QFileInfo(name).suffix();
    QString savePath = QDir::current().filePath(saveFileName);

    saveFile_.reset(new QSaveFile(savePath));
    if (!saveFile_->open(QIODevice::WriteOnly)) {
        qCritical() << "[FileSinker] consume_name() cannot open save file:" << savePath
                    << ", error:" << saveFile_->errorString();
        saveFile_.reset(nullptr);
    } else {
        qDebug() << "[FileSinker] Ready to receive file:" << savePath;
    }
}

bool FileSinker::consumeChunkBuffer(const QByteArray& chunk) {
    if (!saveFile_) {
        qCritical() << "[FileSinker] No active saveFile_ when writing chunk!";
        return false;
    }
    qint64 written = saveFile_->write(chunk);
    if (written != chunk.size()) {
        qCritical() << "[FileSinker] Write size mismatch";
        return false;
    }
    return true;
}

QByteArray FileSinker::requestChunkForEncoding(quint64 offset, quint64 bytesForRead) {
    if (!file_.isOpen()) {
        if (!file_.open(QIODevice::ReadOnly)) {
            qCritical() << "[FileDataSinker] Cannot open file for read:" << filePath_;
            return {};
        }
    }
    file_.seek(offset);
    return file_.read(static_cast<qint64>(bytesForRead));
}

void FileSinker::sendEnd() {
    if (file_.isOpen()) {
        file_.close();
    }
}

void FileSinker::resetSelf() {
    filePath_ = "";
    if (file_.isOpen()) {
        file_.close();
    }
    saveFile_.reset(nullptr);
}
