/* jacobi.c - Poisson problem in 3d
 * 
 */
#include <math.h>

int jacobi(double ***u, double ***u_old, double ***f, int N, int delta, int iter_max, double *tolerance) {
    int i, j, k;
    int iter = 0;
    double d = 10000000000;
    double norm_diff;

    double delta_2 = delta*delta;
    double div_val = 1.0/6.0;
    
    double ***temp_pointer;

    while (d > *tolerance && iter < iter_max) {
        d = 0.0;
        for (i = 1; i < N - 1; ++i) {
            for (j = 1; j < N - 1; ++j) {
                for (k = 1; k < N - 1; ++k) {
                    // Make a delta square - done
                    double u_new = (u_old[i - 1][j][k] + u_old[i + 1][j][k]
                                 + u_old[i][j - 1][k] + u_old[i][j + 1][k]
                                 + u_old[i][j][k - 1] + u_old[i][j][k + 1]
                                 + delta_2 * f[i][j][k])*div_val;

                    // Make it a mult - done
                    u[i][j][k] = u_new;
                    norm_diff = u_new - u_old[i][j][k];
        
                    d += norm_diff * norm_diff;
                }
            }
        }
        d = sqrt(d);
        // Pointer redo
        temp_pointer = u;
        u = u_old;
        u_old = temp_pointer;
        iter++;
    }
    *tolerance = d;
    return iter;
}