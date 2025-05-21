#ifndef CPUSTATEFETCHER_H
#define CPUSTATEFETCHER_H
#include <QObject>
#include <QTimer>
class CCIMX_AbstractCPUStateDriver;
/**
 * @brief The CPUStateFetcher class provides the cpu state
 * @note this is the interface for the cpu state with non
 * platform related
 */
class CPUStateFetcher : public QObject {
	Q_OBJECT
public:
	explicit CPUStateFetcher(QObject* parent = nullptr);
	~CPUStateFetcher();

	/**
	 * @brief The CPUState class provides the cpu state
	 * infos
	 */
	struct CPUState {
		double idle; ///< idle time
		double user; ///< user time
		double kernel; ///< kernel time
		double tol; ///< sums above, the var is seperate as linux and windows makes different in tol time concept
	} cpustate;

	/**
	 * @brief set_capture_state set the capture state
	 * @param st the state to set, enable(true) or disable(false)
	 */
	void set_capture_state(bool st);
signals:
	/**
	 * @brief flush_cpustate the signal to flush the cpu state carried
	 * @param state the cpu state to flush
	 */
	void flush_cpustate(const CPUStateFetcher::CPUState& state);

private:
	CCIMX_AbstractCPUStateDriver* platform_driver_base { nullptr };
	void setup_platform_relative();
	/* this is used to flush the cpu state */
	void flush_once();
	QTimer flush_timer;
	int flush_msecs { 1500 };
};

/**
 * @brief The CCIMX_AbstractCPUStateDriver class
 * factory class to provide the correct cpu state impls
 */
class CCIMX_AbstractCPUStateDriver {
public:
	CCIMX_AbstractCPUStateDriver() = default;
	virtual ~CCIMX_AbstractCPUStateDriver() = default;
	/* driver is expected to make a stat back, locating in platforms */
	virtual void factory(CPUStateFetcher::CPUState& state) = 0;
};

#endif // CPUSTATEFETCHER_H
