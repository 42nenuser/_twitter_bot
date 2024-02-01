#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define WIDTH 1021
#define HEIGHT 1021
#define MAX_ITER 1000

typedef struct {
    double xmin, xmax, ymin, ymax;
    double a, b;
    int x, y;
} t_data;

typedef struct {
    double cre, cim;
} julia_constant;



int random_value1 = 3; 
int random_value2 = 7; 

julia_constant julia_sets[10] = {
    {0.285, 0.01},
    {-0.70176, -0.3842},
    {-0.8, 0.156},
    {-0.4, 0.6},
    {0.285, 0.0},
    {0.45, 0.1428},
    {-0.835, -0.2321},
    {-0.7269, 0.1889},
    {0.0, -0.8},
    {-0.8, 0.0}
};


void get_color_ppm(int iteration, int *r, int *g, int *b) {
   
   

    *r = iteration % 256;
    *g = (iteration * random_value1) % 256;
    *b = (iteration * random_value2) % 256;
}

int julia(double x, double y, double cre, double cim) {
    int iter = 0;
    while (x*x + y*y <= 4 && iter < MAX_ITER) {
        double x_new = x*x - y*y + cre;
        y = 2*x*y + cim;
        x = x_new;
        iter++;
    }
    return iter;
}


int mandelbrot(double x0, double y0) {
    double a = 0, b = 0, a2 = 0, b2 = 0;
    int iter = MAX_ITER;
    while (a2 + b2 <= 4 && iter > 0) {
        double ab = a * b;
        a = a2 - b2 + x0;
        b = 2 * ab + y0;
        a2 = a * a;
        b2 = b * b;
        iter--;
    }
    return iter;
}

void draw(t_data *data, FILE *fp) {
    int r, g, b;
    int result = mandelbrot(data->xmin + (data->xmax - data->xmin) * data->x / WIDTH,
                            data->ymin + (data->ymax - data->ymin) * data->y / HEIGHT);
    get_color_ppm(result, &r, &g, &b);
    fprintf(fp, "%d %d %d\n", r, g, b);
}

void draw_mandelbrot(t_data *data, FILE *fp) {
    data->x = 0;
    while (data->x < WIDTH) {
        data->y = 0;
        while (data->y < HEIGHT) {
            draw(data, fp);
            data->y++;
        }
        data->x++;
    }
}
void draw_julia(t_data *data, FILE *fp, double cre, double cim) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            double jx = data->xmin + (data->xmax - data->xmin) * x / WIDTH;
            double jy = data->ymin + (data->ymax - data->ymin) * y / HEIGHT;
            int result = julia(jx, jy, cre, cim);
            int r, g, b;
            get_color_ppm(result, &r, &g, &b);
            fprintf(fp, "%d %d %d\n", r, g, b);
        }
    }
}

int main(int argc, char *argv[]) {
    
     int fractal_choice = 1;
    
   
        random_value1 = atoi(argv[1]);
        random_value2 = atoi(argv[2]);
         fractal_choice = atoi(argv[3]);
   
    srand(time(NULL)); 
    int random_index = rand() % 10; 
    
  
    double cre = julia_sets[random_index].cre;
    double cim = julia_sets[random_index].cim;
   // double cre = -0.7, cim = 0.27015;
    t_data data;
    data.xmin = -2.0;
    data.xmax = 1.0;
    data.ymin = -1.5;
    data.ymax = data.ymin + (data.xmax - data.xmin) * HEIGHT / WIDTH;

    FILE *fp = fopen("mandelbrot.ppm", "w");
   

    fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
    if (fractal_choice == 1) {
        draw_mandelbrot(&data, fp);
    } else if (fractal_choice == 2) {
        draw_julia(&data, fp, cre, cim); 
    } else {
        printf("invalid fractall choice\n");
        return 1;
    }

    fclose(fp);
    return 0;
}
