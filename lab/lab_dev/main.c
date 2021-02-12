#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define GRAVITY_CONST ((double) 9.8)

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define CONVERT_DEG_TO_RAD(_degrees) ((_degrees) / 180.0 * M_PI)
#define CONVERT_RAD_TO_DEG(_radians) ((_radians) / M_PI * 180)

#define min(_x, _y) (((_x) < (_y)) ? (_x) : (_y))
#define max(_x, _y) (((_x) > (_y)) ? (_x) : (_y))

#define ERROR_EXIT(fmt, ...)                        \
        do {                                        \
            fprintf(stderr, fmt, ##__VA_ARGS__);    \
            exit(-1);                               \
        } while (0)

typedef struct rect {
    double width;
    double height;
} rect_t;

typedef struct point {
    double x;
    double y;
} point_t;

double task1_1(double start_velocity, double start_angle);
double task1_2(double start_velocity, double start_angle, double time_step);

double task2_1(double radius, rect_t *rect);
double task2_2(double radius, rect_t *rect, size_t niter, size_t *hit_points);

int main(int argc, const char *argv[])
{
    /* Initializing variables */
    int choice;
    char *remainder;

    /* For measuring time of iteration */
    struct timeval start, stop;
    double time_in_mill_start, time_in_mill_stop;

    /* VarCheck */
    if (argc != 2) {
        ERROR_EXIT("usage: %s #task\n", *argv);
    }

    /* Main part */
    choice = (int) strtol(*(argv + 1), &remainder, 10);
    if (*remainder != '\0') {
        ERROR_EXIT("Only `1` or `2` are allowed\n");
    }
    switch (choice) {
        case 1: /* Task #01 */
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
            gettimeofday(&start, NULL); /* Getting time in milliseconds precision */
            monte_carlo_distance = task1_2(start_velocity, start_angle, time_step);
            gettimeofday(&stop, NULL);

            time_in_mill_start = (double) (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
            time_in_mill_stop = (double) (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

            /* Final output */
            printf("[Classic physics way]:   Distance travelled: %.4lf\n", classic_distance);
            printf("[Monte-Carlo iteration]: Distance travelled: %.4lf (time for calc.: %lf ms)\n",
                   monte_carlo_distance, time_in_mill_stop - time_in_mill_start);
            printf("\nDifference in answer: %lf\n", classic_distance - monte_carlo_distance);
        }
            break;
        case 2: /* Task #02 */
        {
            /* Initializing variables */
            double radius;
            rect_t rect;
            size_t niter, hit_counter;
            double classic_area, monte_carlo_area;

            /* I/O flow */
            printf("Type radius: ");
            scanf("%lf", &radius);
            assert(radius > 0);

            printf("Type width: ");
            scanf("%lf", &rect.width);
            assert(rect.width > 0);

            printf("Type height: ");
            scanf("%lf", &rect.height);
            assert(rect.height > 0);

            printf("Type number of iterations: ");
            scanf("%lu", &niter);
            assert(niter > 0);

            /* Main part */
            srand(time(NULL));

            /* Classic geometry way */
            classic_area = task2_1(radius, &rect);

            /* Iteration Monte-Carlo */
            gettimeofday(&start, NULL); /* Getting time in milliseconds precision */
            monte_carlo_area = task2_2(radius, &rect, niter, &hit_counter);
            gettimeofday(&stop, NULL);

            time_in_mill_start = (double) (start.tv_sec) * 1000 + (double) (start.tv_usec) / 1000;
            time_in_mill_stop = (double) (stop.tv_sec) * 1000 + (double) (stop.tv_usec) / 1000;

            /* Final output */
            printf("[Classic geometry way]:  Area of cross section: %.4lf\n", classic_area);
            printf("[Monte-Carlo iteration]: Area of cross section: %.4lf, points hit: %lu (time for calc.: %lf ms)\n",
                   monte_carlo_area, hit_counter, time_in_mill_stop - time_in_mill_start);
            printf("\nDifference in answer: %lf\n", classic_area - monte_carlo_area);
        }
            break;
        default:
            ERROR_EXIT("No such choice allowed\n");
    }
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
    for (x = 0, y = 0, vy = start_velocity * sin(start_angle_rad); y >= 0;) {
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

static void ensure_rectange_is_correct(rect_t *rect)
{
    /* Main part */
    if (rect->height > rect->width) {
        double tmp = rect->width;
        rect->width = rect->height;
        rect->height = tmp;
    }
}

double task2_1(double radius, rect_t *rect)
{
    /* Initializing variables */
    double Sabo, Saoc;
    double ab, bo, alpha;

    /* Main part */
    /* If height is greater that width — swap them! */
    ensure_rectange_is_correct(rect);

    if (radius <= rect->height / 2) {
        return M_PI * radius * radius;
    } else if (2 * radius >= sqrt(rect->width * rect->width + rect->height * rect->height)) {
        return rect->width * rect->height;
    } else {
        /* Triangle ABO */
        bo = rect->height / 2;
        ab = sqrt((radius * radius) - (bo * bo));
        Sabo = (ab * bo) / 2;

        /* Sector AOC */
        alpha = CONVERT_RAD_TO_DEG(asin(bo / radius));
        Saoc = (M_PI * radius * radius * alpha) / 360;

        return 4 * (Sabo + Saoc);
    }
}

static int is_inside_shape(double radius, rect_t *rect, point_t *point)
{
    /* Returning value */
    return ((point->x * point->x + point->y * point->y) <= radius * radius) &&
           (fabs(point->y) <= rect->height / 2) && (fabs(point->x) <= rect->width / 2);
}

double task2_2(double radius, rect_t *rect, size_t niter, size_t *hit_points)
{
    /* Initializing variables */
    register size_t i;
    *hit_points = 0;
    point_t point;
    double x_limit, y_limit, bounding_search_value;

    /* Main part */
    ensure_rectange_is_correct(rect);

    x_limit = max(radius, rect->width / 2);
    y_limit = max(radius, rect->height / 2);

    bounding_search_value = 2 * x_limit * 2 * y_limit;

    for (i = 0; i < niter; ++i) {
        point.x = drand48() * 2 * x_limit - x_limit;
        point.y = drand48() * 2 * y_limit - y_limit;

        if (is_inside_shape(radius, rect, &point)) {
            ++*hit_points;
        }
    }

    return *hit_points * bounding_search_value / niter;
}
