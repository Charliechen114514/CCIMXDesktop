#ifndef CPUSTATEFETCHER_H
#define CPUSTATEFETCHER_H
#include <QObject>
#include <QTimer>
class CCIMX_AbstractCPUStateDriver;
/* This class is expected to fetch the cpu state */
class CPUStateFetcher : public QObject {
	Q_OBJECT
public:
	explicit CPUStateFetcher(QObject* parent = nullptr);
	~CPUStateFetcher();

	struct CPUState {
		double idle;
		double user;
		double kernel;
        double tol;
	} cpustate;
	void set_capture_state(bool st);
signals:
	void flush_cpustate(const CPUStateFetcher::CPUState& state);

private:
	CCIMX_AbstractCPUStateDriver* platform_driver_base { nullptr };
	void setup_platform_relative();
	/* this is used to flush the cpu state */
	void flush_once();
	QTimer flush_timer;
	int flush_msecs { 1500 };
};

class CCIMX_AbstractCPUStateDriver {
public:
	CCIMX_AbstractCPUStateDriver() = default;
	virtual ~CCIMX_AbstractCPUStateDriver() = default;
	/* driver is expected to make a stat back, locating in platforms */
	virtual void factory(CPUStateFetcher::CPUState& state) = 0;
};

#endif // CPUSTATEFETCHER_H
