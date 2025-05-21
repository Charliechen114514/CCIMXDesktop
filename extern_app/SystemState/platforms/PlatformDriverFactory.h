#ifndef PLATFORMDRIVERFACTORY_H
#define PLATFORMDRIVERFACTORY_H
#include <QtClassHelperMacros>
class CCIMX_AbstractMemoryInfoDriver;
class CCIMX_AbstractCPUStateDriver;
class CCIMX_AbstractProcessBroswerDriver;

/**
 * @brief The PlatformDriverFactory class provides the platform driver factory
 * @note this is the factory for the platform drivers
 */
class PlatformDriverFactory {
public:
	PlatformDriverFactory() = default;
	Q_DISABLE_COPY(PlatformDriverFactory);

	/**
	 * @brief target_meminfo fetch the memory info driver
	 * @return the memory info driver
	 */
	static CCIMX_AbstractMemoryInfoDriver* meminfo_from_platform();

	/**
	 * @brief cpustate_from_platform fetch the cpu state driver
	 * @return
	 */
	static CCIMX_AbstractCPUStateDriver* cpustate_from_platform();

	/**
	 * @brief processdriver_from_platform fetch the process driver
	 * @return the process driver
	 */
	static CCIMX_AbstractProcessBroswerDriver* processdriver_from_platform();
};

#endif // PLATFORMDRIVERFACTORY_H
