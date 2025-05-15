#ifndef AP3216C_H
#define AP3216C_H

#define AP3216CData_INVALID_VALUE (0)
typedef struct {
	/* values */
	unsigned short ir, als, ps;
} AP3216CData;

/* for the range of the values */
static constexpr unsigned int MIN_IR_VALUE { 0 };
static constexpr unsigned int MIN_ALS_VALUE { 0 };
static constexpr unsigned int MIN_PS_VALUE { 0 };
static constexpr unsigned int MAX_IR_VALUE { 1024 };
static constexpr unsigned int MAX_ALS_VALUE { 65535 };
static constexpr unsigned int MAX_PS_VALUE { 1024 };

#endif
