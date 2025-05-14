#ifndef AP3216C_H
#define AP3216C_H

#define AP3216CData_INVALID_VALUE   (0)
#pragma pack(push, 1)
typedef struct {
    /* values */
    unsigned short ir, als, ps;
}AP3216CData;
#pragma pack(pop)
#endif