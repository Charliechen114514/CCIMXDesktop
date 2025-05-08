#include "CVImageImpl.h"
#include "CVImagePrivateOpencvImp.h"
CVImageImpl *CVImageImplFactory::target_impl()
{
	/* current we only support OpenCV */
	return new CVImageOpencvImpl;
}
