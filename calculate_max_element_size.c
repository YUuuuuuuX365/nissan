#include <stdio.h>
#include <float.h>

#define DIMENSION 3
#define MAX_NODES_ON_ELEMENT 10

/* Compute the maximum size of elements in a tetrahedral mesh.
 * node_of_element: element->node index array (Total_Element x TETRA_CONVEX)
 * node_coord: node coordinates (Total_Node x DIMENSION)
 * total_elements: number of elements in the mesh
 * lx_max, ly_max, lz_max: output maximum element side lengths in each dimension
 */
void calculate_max_element_size(int total_elements,
                                const int node_of_element[][MAX_NODES_ON_ELEMENT],
                                const double node_coord[][DIMENSION],
                                double *lx_max, double *ly_max, double *lz_max)
{
    double max_lx = 0.0, max_ly = 0.0, max_lz = 0.0;
    for (int e = 0; e < total_elements; ++e) {
        double xmin = DBL_MAX, xmax = -DBL_MAX;
        double ymin = DBL_MAX, ymax = -DBL_MAX;
        double zmin = DBL_MAX, zmax = -DBL_MAX;
        for (int n = 0; n < 4; ++n) { /* first 4 nodes define the tetra vertices */
            int nid = node_of_element[e][n];
            double x = node_coord[nid][0];
            double y = node_coord[nid][1];
            double z = node_coord[nid][2];
            if (x < xmin) xmin = x; if (x > xmax) xmax = x;
            if (y < ymin) ymin = y; if (y > ymax) ymax = y;
            if (z < zmin) zmin = z; if (z > zmax) zmax = z;
        }
        double lx = xmax - xmin;
        double ly = ymax - ymin;
        double lz = zmax - zmin;
        if (lx > max_lx) max_lx = lx;
        if (ly > max_ly) max_ly = ly;
        if (lz > max_lz) max_lz = lz;
    }
    if (lx_max) *lx_max = max_lx;
    if (ly_max) *ly_max = max_ly;
    if (lz_max) *lz_max = max_lz;
}

#ifdef TEST_MAIN
/* Minimal test driver */
int main(void) {
    int elements[2][MAX_NODES_ON_ELEMENT] = {
        {0,1,2,3},
        {1,2,3,4}
    };
    double nodes[5][DIMENSION] = {
        {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1}, {1,1,1}
    };
    double lx,ly,lz;
    calculate_max_element_size(2, elements, nodes, &lx, &ly, &lz);
    printf("max sizes: %f %f %f\n", lx, ly, lz);
    return 0;
}
#endif

