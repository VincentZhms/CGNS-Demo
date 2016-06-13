#include <iostream>
#include "cgnslib.h"

int writeStrucMesh3D(const char* fname, const char* bname, const char* zname, \
    double* NodeX, double* NodeY, double* NodeZ, \
    int XN, int YN, int ZN){
    int ier, fn, cell_dim = 3, phys_dim = 3, BaseIndex, ZoneIndex, CoordIndex;
    ZoneType_t ZoneType = CGNS_ENUMV(Structured);
    DataType_t DataType = CGNS_ENUMV(RealDouble);
    cgsize_t isize[3][3];
    /* vertex size */
    isize[0][0]=XN;
    isize[0][1]=YN;
    isize[0][2]=ZN;
    /* cell size */
    isize[1][0]=isize[0][0]-1;
    isize[1][1]=isize[0][1]-1;
    isize[1][2]=isize[0][2]-1;
    /* boundary vertex size (always zero for structured grids) */
    isize[2][0]=0;
    isize[2][1]=0;
    isize[2][2]=0;

    ier = cg_open(fname, CG_MODE_WRITE, &fn);
    if (ier != CG_OK) {cg_error_exit();}
    ier = cg_base_write(fn, bname, cell_dim, phys_dim, &BaseIndex);
    ier = cg_zone_write(fn, BaseIndex, zname, *isize, ZoneType, &ZoneIndex);
    ier = cg_coord_write(fn, BaseIndex, ZoneIndex, DataType, \
        "CoordinateX", NodeX, &CoordIndex);
    ier = cg_coord_write(fn, BaseIndex, ZoneIndex, DataType, \
        "CoordinateY", NodeY, &CoordIndex);
    ier = cg_coord_write(fn, BaseIndex, ZoneIndex, DataType, \
        "CoordinateZ", NodeZ, &CoordIndex);
    ier = cg_close(fn);

    return ier;
}

int writeStrucMesh2D(const char* fname, const char* bname, const char* zname, \
    double* NodeX, double* NodeY, int XN, int YN){
    int ier, fn, cell_dim = 2, phys_dim = 2, BaseIndex, ZoneIndex, CoordIndex;
    ZoneType_t ZoneType = CGNS_ENUMV(Structured);
    DataType_t DataType = CGNS_ENUMV(RealDouble);
    cgsize_t isize[3][2];
    /* vertex size */
    isize[0][0]=XN;
    isize[0][1]=YN;
    /* cell size */
    isize[1][0]=isize[0][0]-1;
    isize[1][1]=isize[0][1]-1;
    /* boundary vertex size (always zero for structured grids) */
    isize[2][0]=0;
    isize[2][1]=0;

    ier = cg_open(fname, CG_MODE_WRITE, &fn);
    if (ier != CG_OK) {cg_error_exit();}
    ier = cg_base_write(fn, bname, cell_dim, phys_dim, &BaseIndex);
    ier = cg_zone_write(fn, BaseIndex, zname, *isize, ZoneType, &ZoneIndex);
    ier = cg_coord_write(fn, BaseIndex, ZoneIndex, DataType, \
        "CoordinateX", NodeX, &CoordIndex);
    ier = cg_coord_write(fn, BaseIndex, ZoneIndex, DataType, \
        "CoordinateY", NodeY, &CoordIndex);
    ier = cg_close(fn);

    return ier;
}

int main(int argc, char* argv[]){
    const char* fname = "grid2d.cgns";
    const char* bname = "Base";
    const char* zname = "Fluid";
//     // 9 rows, 17 cols, 21 depths
    // const int XN = 21, YN = 17, ZN = 9;
    // double NodeX[ZN][YN][XN], NodeY[ZN][YN][XN], NodeZ[ZN][YN][XN];
    const int XN = 21, YN = 17;
    double NodeX[YN][XN], NodeY[YN][XN];

    for (int i = 0; i < XN; i++) {
        for (int j = 0; j < YN; j++) {
            NodeX[j][i] = i;
            NodeY[j][i] = j;
        }
    }

/*    writeStrucMesh3D(fname, bname, zname, \
        &NodeX[0][0][0], &NodeY[0][0][0], &NodeZ[0][0][0], \
        XN, YN, ZN); */
    writeStrucMesh2D(fname, bname, zname, \
        &NodeX[0][0], &NodeY[0][0], XN, YN);

    return 0;
}
