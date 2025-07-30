#include "DataProtocolizedController.h"
#include "FileSinker.h"
#include <QBuffer> // For collecting frames in memory
#include <QCoreApplication>
#include <QCryptographicHash> // For content verification of large files
#include <QDebug> // Used for debugging output
#include <QDir>
#include <QFile>
#include <QList> // For storing frames
#include <QRandomGenerator>
#include <QSignalSpy>
#include <QtTest/QtTest>

/**
 * @brief DataProtoTest class, used to test the file transfer functionality of DataProtocolizedController and FileSinker.
 *
 * This test class aims to verify the reliability of file transfer, including the integrity of small and large files
 * under sequential and random chunk transmission. Each test case will independently create sender and receiver
 * controller and Sinker instances to ensure isolation between tests. Received files will be saved to the current
 * working directory and cleaned up after the test.
 */
class DataProtoTest : public QObject {
    Q_OBJECT
private slots:
    /**
     * @brief Test case initialization.
     * Primarily responsible for creating a temporary directory for sender file operations.
     * Receiver files will be saved to the current working directory.
     */
    void initTestCase();

    /**
     * @brief Test case cleanup.
     * Primarily responsible for deleting the temporary directory and its contents created during the test.
     */
    void cleanupTestCase();

    /**
     * @brief Test small file sequential transfer.
     * Creates a small file and simulates sequential data block transfer, verifying the consistency of the received file content.
     */
    void test_smallFile_in_order();

    /**
     * @brief Test large file sequential transfer.
     * Creates a large file and simulates sequential data block transfer, verifying the consistency of the received file content.
     */
    void test_largeFile_in_order();

private:
    QString tempDir; // Directory for sender's temporary files

    // Helper function to generate random data for files
    QByteArray generateRandomData(qint64 size);
};

/**
 * @brief Implementation of initTestCase method.
 * Creates a temporary directory for testing.
 */
void DataProtoTest::initTestCase() {
    // Create a temporary directory for the sender, ensuring it's separate from the current working directory
    tempDir = QDir::tempPath() + "/test_protocal_sender";
    QDir().mkpath(tempDir);
    qDebug() << "Sender temp directory:" << tempDir;
    qDebug() << "Receiver files will be saved in current working directory:" << QDir::currentPath();
}

/**
 * @brief Implementation of cleanupTestCase method.
 * Deletes the sender's temporary directory and its contents created during the test.
 */
void DataProtoTest::cleanupTestCase() {
    QDir(tempDir).removeRecursively(); // Delete sender's temporary directory
    qDebug() << "Cleaned up sender temp directory:" << tempDir;

    // Since receiver files are saved in the current working directory and cleaned up individually after each test case,
    // no additional global cleanup logic is needed here.
}

/**
 * @brief Helper method to generate random byte array of a given size.
 * @param size The desired size of the byte array.
 * @return A QByteArray filled with random data.
 */
QByteArray DataProtoTest::generateRandomData(qint64 size) {
    QByteArray data;
    data.resize(static_cast<int>(size)); // Resize to the desired size
    QRandomGenerator* rng = QRandomGenerator::global(); // Get the global random generator
    for (int i = 0; i < data.size(); ++i) {
        data[i] = static_cast<char>(rng->generate()); // Fill each byte with a random value
    }
    return data;
}

/**
 * @brief Implementation of test_smallFile_in_order method.
 * Tests the scenario of small file sequential chunk transfer.
 */
void DataProtoTest::test_smallFile_in_order() {
    qDebug() << "Starting test_smallFile_in_order...";
    // 1. Prepare original file
    QString originalFileName = "hello.txt";
    QString originalFilePath = tempDir + "/" + originalFileName;
    QByteArray originalContent = "Hello QtTest\n";
    QFile f(originalFilePath);
    QVERIFY(f.open(QIODevice::WriteOnly));
    f.write(originalContent);
    f.close();
    qDebug() << "Created original file:" << originalFilePath;

    // 2. Create sender components
    // Sender's FileSinker is bound to the original file path
    FileSinker* testSenderSinker = new FileSinker(originalFilePath, 16);
    DataProtocolizedController* testSenderController = new DataProtocolizedController(testSenderSinker, this);

    // 3. Create receiver components
    // Receiver's FileSinker uses the original file path to derive the saved file name.
    // Note: FileSinker internally saves the file to QDir::current() path.
    FileSinker* testReceiverSinker = new FileSinker(originalFilePath, 4096);
    DataProtocolizedController* testReceiverController = new DataProtocolizedController(testReceiverSinker, this);

    // 4. Connect simulated "network" transmission: sender's frameReady signal connects to receiver's onBytes slot
    // Simulate direct transmission, no random chunking
    connect(testSenderController, &DataProtocolizedController::frameReady,
            testReceiverController, &DataProtocolizedController::onBytes);

    // 5. Determine the path where the received file will be saved
    // FileSinker internal logic: QFileInfo(filePath_).baseName() + "_received." + QFileInfo(filePath_).suffix()
    QString receivedFileName = QFileInfo(originalFileName).baseName() + "_received." + QFileInfo(originalFileName).suffix();
    QString expectedReceivedFilePath = QDir::current().filePath(receivedFileName);
    qDebug() << "Expected received file path:" << expectedReceivedFilePath;

    // Ensure no file with the same name exists previously to avoid interference
    QFile::remove(expectedReceivedFilePath);

    // 6. Send data
    testSenderController->sendData(16); // Send data, specifying chunk size

    // 7. Wait for file reception and saving to complete
    // Check if the file exists and its size matches the original file, ensuring content has been written
    QTRY_VERIFY_WITH_TIMEOUT(QFile::exists(expectedReceivedFilePath) && QFile(expectedReceivedFilePath).size() == originalContent.size(), 5000);

    // 8. Verify the content of the received file
    QFile receivedFile(expectedReceivedFilePath);
    QVERIFY(receivedFile.open(QIODevice::ReadOnly)); // Open the received file
    QCOMPARE(receivedFile.readAll(), originalContent); // Compare file content
    receivedFile.close();
    qDebug() << "File content verified for:" << expectedReceivedFilePath;

    // 9. Clean up resources
    delete testSenderController;
    delete testReceiverController;
    delete testSenderSinker;
    delete testReceiverSinker;
    QFile::remove(originalFilePath); // Delete original file
    QFile::remove(expectedReceivedFilePath); // Delete received file
    qDebug() << "Cleaned up files for test_smallFile_in_order.";
}

/**
 * @brief Implementation of test_largeFile_in_order method.
 * Tests the scenario of large file sequential chunk transfer.
 */
void DataProtoTest::test_largeFile_in_order() {
    qDebug() << "Starting test_largeFile_in_order...";
    // 1. Prepare original large file (e.g., 10 MB)
    const qint64 fileSize = 10 * 1024 * 1024; // 10 MB
    const int chunkSize = 4096; // 4 KB chunk size
    QString originalFileName = "large_file_in_order.bin";
    QString originalFilePath = tempDir + "/" + originalFileName;
    QByteArray originalContent = generateRandomData(fileSize); // Generate random data

    QFile f(originalFilePath);
    QVERIFY(f.open(QIODevice::WriteOnly));
    f.write(originalContent);
    f.close();
    qDebug() << "Created original large file:" << originalFilePath << "size:" << originalContent.size() << "bytes";

    // 2. Create sender components
    FileSinker* testSenderSinker = new FileSinker(originalFilePath, chunkSize);
    DataProtocolizedController* testSenderController = new DataProtocolizedController(testSenderSinker, this);

    // 3. Create receiver components
    FileSinker* testReceiverSinker = new FileSinker(originalFilePath, chunkSize);
    DataProtocolizedController* testReceiverController = new DataProtocolizedController(testReceiverSinker, this);

    // 4. Connect simulated "network" transmission (in-order)
    connect(testSenderController, &DataProtocolizedController::frameReady,
            testReceiverController, &DataProtocolizedController::onBytes);

    // 5. Determine the path where the received file will be saved
    QString receivedFileName = QFileInfo(originalFileName).baseName() + "_received." + QFileInfo(originalFileName).suffix();
    QString expectedReceivedFilePath = QDir::current().filePath(receivedFileName);
    qDebug() << "Expected received file path:" << expectedReceivedFilePath;

    QFile::remove(expectedReceivedFilePath); // Ensure no old file exists

    // 6. Send data
    testSenderController->sendData(chunkSize);

    // 7. Wait for file reception and saving to complete
    QTRY_VERIFY_WITH_TIMEOUT(QFile::exists(expectedReceivedFilePath) && QFile(expectedReceivedFilePath).size() == originalContent.size(), 30000); // Increased timeout for large files

    // 8. Verify the content of the received file using cryptographic hash for efficiency
    QFile receivedFile(expectedReceivedFilePath);
    QVERIFY(receivedFile.open(QIODevice::ReadOnly));

    QCryptographicHash originalHash(QCryptographicHash::Sha256);
    originalHash.addData(originalContent);
    QByteArray originalFileHash = originalHash.result();

    QCryptographicHash receivedHash(QCryptographicHash::Sha256);
    receivedHash.addData(&receivedFile); // Add file content to hash calculator
    QByteArray receivedFileHash = receivedHash.result();
    receivedFile.close();

    QCOMPARE(receivedFileHash, originalFileHash);
    qDebug() << "File content verified for:" << expectedReceivedFilePath;

    // 9. Clean up resources
    delete testSenderController;
    delete testReceiverController;
    delete testSenderSinker;
    delete testReceiverSinker;
    QFile::remove(originalFilePath);
    QFile::remove(expectedReceivedFilePath);
    qDebug() << "Cleaned up files for test_largeFile_in_order.";
}

// Register the test class so it can be discovered and run by the QtTest framework
QTEST_MAIN(DataProtoTest)
#include "test_protocal.moc" // Include moc file, generated by Qt's moc tool
