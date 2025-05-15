#include "PesudoAP3216C.h"

std::optional<AP3216CData> PesudoAP3216C::sync_read_once() {
	/*
	 * From DataSheet: AP3216C's range is
	 *		ALS 0 ~ 65535
	 *		PS 0 ~ 1023
	 *		IR 0 ~ 1023
	 */

	/* In this cases */
	AP3216CData data;
	data.als = rand() % 65536;
	data.ps = rand() % 1024;
	data.ir = rand() % 1024;
	/* Always return valid datas */
	return { data };
}
