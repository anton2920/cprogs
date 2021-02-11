#include <stdio.h>
#include <math.h>
#include <assert.h>

#define GRAVITY_CONST ((double) 9.8)

#undef M_PI
#define M_PI ((double) 3.1415926535897932384626433832795)

#define CONVERT_DEG_TO_RAD(_degrees) ((_degrees) / 180.0 * M_PI)

double task1_1(double start_velocity, double start_angle);
double task1_2(double start_velocity, double start_angle, double time_step);

/* TODO: task_2 */
double task2_1();
double task2_2();

main()
{
    /* Initializing variables */
    double start_velocity, start_angle, time_step;
    double classic_distance, monte_carlo_distance;

    /* I/O flow */
    printf("Type starting velocity: ");
    scanf("%lf", &start_velocity);
    assert(start_velocity > 0);

    printf("Type angle: ");
    scanf("%lf", &start_angle);
    assert(start_angle > 0 && start_angle <= 90);

    printf("Type time step: ");
    scanf("%lf", &time_step);
    assert(time_step > 0);

    /* Main part */
    /* Classic physics way */
    classic_distance = task1_1(start_velocity, start_angle);

    /* Iteration Monte-Carlo */
    monte_carlo_distance = task1_2(start_velocity, start_angle, time_step);

    /* Final output */
    printf("[Classic physics way]:   Distance travelled: %.3lf\n", classic_distance);
    printf("[Monte-Carlo iteration]: Distance travelled: %.3lf\n", monte_carlo_distance);
}

double task1_1(double start_velocity, double start_angle)
{
    /* Initializing variables */
    double start_angle_rad, distance;

    /* Main part */
    start_angle_rad = CONVERT_DEG_TO_RAD(start_angle);
    distance = pow(start_velocity, 2.0) * sin(2 * start_angle_rad) / GRAVITY_CONST;

    /* Returning value */
    return distance;
}

double task1_2(double start_velocity, double start_angle, double time_step)
{
    /* Initializing variables */
    double start_angle_rad, distance;

    double vx, vy, x, y;

    /* Main part */
    start_angle_rad = CONVERT_DEG_TO_RAD(start_angle);
    vx = start_velocity * cos(start_angle_rad);
    for (x = 0, y = 0, vy = start_velocity * sin(start_angle_rad); y >= 0; )
    {
        x += vx * time_step;
        y += vy * time_step;
        vy -= GRAVITY_CONST * time_step;
    }

    /* Getting values from previous iteration */
    x -= vx * time_step;
    vy += GRAVITY_CONST * time_step;
    y -= vy * time_step;
    distance = x + ((vx * y) / vy);

    /* Returning value */
    return distance;
}
