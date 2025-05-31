#ifndef CPUSTATEFETCHER_H
#define CPUSTATEFETCHER_H

#include <QObject>
#include <QTimer>

class CCIMX_AbstractCPUStateDriver;

/**
 * @brief The CPUStateFetcher class
 * Provides CPU state information in a platform-independent manner.
 * Acts as an interface for retrieving CPU state without platform-specific details.
 */
class CPUStateFetcher : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor with optional parent.
     * @param parent Pointer to the QObject parent, default is nullptr.
     */
    explicit CPUStateFetcher(QObject* parent = nullptr);

    /**
     * @brief Destructor, cleans up resources.
     */
    ~CPUStateFetcher();

    /**
     * @brief The CPUState struct
     * Represents CPU usage state including idle, user, kernel and total time.
     * The total time concept differs between Linux and Windows.
     */
    struct CPUState {
        double idle;   ///< CPU idle time.
        double user;   ///< CPU user time.
        double kernel; ///< CPU kernel time.
        double tol;    ///< Total time (sum of above), platform-dependent meaning.
    } cpustate; ///< cpu state memorizer

    /**
     * @brief set_capture_state
     * Enables or disables the CPU state capture.
     * @param st True to enable capturing, false to disable.
     */
    void set_capture_state(bool st);

signals:
    /**
     * @brief flush_cpustate
     * Signal emitted when CPU state is updated.
     * @param state The current CPU state snapshot.
     */
    void flush_cpustate(const CPUStateFetcher::CPUState& state);

private:
    CCIMX_AbstractCPUStateDriver* platform_driver_base { nullptr }; ///< Platform-specific CPU state driver instance.

    /**
     * @brief setup_platform_relative
     * Sets up platform-specific CPU state driver implementation.
     */
    void setup_platform_relative();

    /**
     * @brief flush_once
     * Fetches the current CPU state once and emits the updated signal.
     */
    void flush_once();

    QTimer flush_timer; ///< Timer used for periodic CPU state fetching.
    int flush_msecs { 1500 }; ///< Timer interval in milliseconds for flushing CPU state.
};

/**
 * @brief The CCIMX_AbstractCPUStateDriver class
 * Abstract base class factory to provide platform-specific CPU state implementations.
 */
class CCIMX_AbstractCPUStateDriver {
public:
    CCIMX_AbstractCPUStateDriver() = default;
    virtual ~CCIMX_AbstractCPUStateDriver() = default;

    /**
     * @brief factory
     * Fills the CPUState structure with current CPU usage data.
     * @param state Reference to CPUState structure to populate.
     */
    virtual void factory(CPUStateFetcher::CPUState& state) = 0;
};

#endif // CPUSTATEFETCHER_H
