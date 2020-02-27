#ifndef __CS267_COMMON_H__
#define __CS267_COMMON_H__

//
//  tuned constants
//
#define density 0.0005
#define mass    0.01
#define cutoff  0.01
#define min_r   (cutoff/100)
#define dt      0.0005

inline int min( int a, int b ) { return a < b ? a : b; }
inline double min( double a, double b ) { return a < b ? a : b; }
inline int max( int a, int b ) { return a > b ? a : b; }

//
//  saving parameters
//
const int NSTEPS = 1000;
const int SAVEFREQ = 10;

//
// particle data structure
//
typedef struct 
{
  double x;
  double y;
  double vx;
  double vy;
  double ax;
  double ay;
} particle_t;

//
//  timing routines
//
double read_timer( );

//
//  simulation routines
//
void set_size( int n, double &size);
void init_particles( int n, particle_t *p, double &size );
void apply_force( particle_t &particle, particle_t &neighbor , double *dmin, double *davg, int *navg, double &size);
void move( particle_t &p,  double &size);


//
//  I/O routines
//
//FILE *open_save( char *filename, int n );
void save( FILE *f, int n, particle_t *p, double &size );

//
//  argument processing routines
//
int find_option( int argc, char **argv, const char *option );
int read_int( int argc, char **argv, const char *option, int default_value );
double read_double( int argc, char **argv, const char *option, double default_value );
char *read_string( int argc, char **argv, const char *option, char *default_value );

#endif
