#ifndef ICM20608_H
#define ICM20608_H

#define AP3216CData_INVALID_VALUE   (0)

typedef struct {
    /* 3D Acceleration value */
    struct {
        int x;
        int y;
        int z;
    }g_acc;

    /* 3D Rolations dekta */
    struct {
        int x;
        int y;
        int z;
    }rol;

    int temperature;
}ICM20608Data;

#endif