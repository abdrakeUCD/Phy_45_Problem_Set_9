#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int N;			// number of grid points
	double L;		// length of rod
	double kappa;		// diffusion coefficient
	long double tau;	// discrete time spacing
	long double h;		// discrete space spacing
	double *tt;		// time array
	double *tt_n;		// new time array (used as swap)
} DiffusionParams;

void initialize(DiffusionParams *params)
{
	printf("\nHow many grid points would you like to compute? (Must be an even number.)\n");
	scanf("%i", &(params->N));

	params->L = 1.0;
	params->kappa = 1.0;

	params->h = params->L / (params->N - 1);
	long double stability = (0.4 * params->h * params->h)/(params->kappa); // \tau < \frac{0.4h^2}{\kappa} to meet stability criterion

	printf("\nInitializing diffusion equation with:\n");
	printf("  Length = %lf\n  Diffusion Coefficient (kappa) = %lf\n  Grid Spacing (h) = %12.6Lf\n", params->L, params->kappa, params->h);
	printf("To satisfy stability, tau must be < %20.15Lf. Enter tau:\n", stability);
	scanf("%Lf", &(params->tau));
	printf("\ntau succesfully initialized as %20.15Lf\n", params->tau);

	params->tt = malloc(params->N * sizeof(double));
	params->tt_n = malloc(params->N * sizeof(double));

	// initializing temperature array to 0
	for(int i =0; i<params->N; i++)
	{
		params->tt[i] = 0.0;
		params->tt_n[i] = 0.0;
	}
	
	// boundary conditions
	params->tt[0] = 0.0;
	params->tt[params->N - 1] = 0.0;
	params->tt[params->N / 2] = (1.0)/(params->h); // delta function at center
}

void print_progress_bar(int current_step, int total_steps)
{
    // This function will print a simple progress bar to the terminal
    float progress = (float)current_step / total_steps;
    int bar_width = 50;  // width of the progress bar in characters

    int pos = bar_width * progress;
    printf("[");
    for (int i = 0; i < bar_width; i++)
    {
        if (i < pos)
            printf("#");
        else
            printf(" ");
    }
    printf("] %3.0f%%\r", progress * 100);
    fflush(stdout);
}

void evolve(DiffusionParams *params, int nStep, int plot_step)
{
	FILE *file = fopen("diffusion_data.txt", "w");

	printf("\n\nProgress in Computation:\n");
	// time evolution loop
	for(int iStep = 0; iStep < nStep; iStep++)
	{
		// save current temperature profile
		for(int i = 0; i < params->N; i++)
		{
			fprintf(file, "%lf ", params->tt[i]);
		}
		fprintf(file, "\n");

		// compute new temperature (finite difference method)
		for(int i = 1; i < params->N - 1; i++)
		{
			params->tt_n[i] = params->tt[i] + (params->kappa * params->tau / (params->h * params->h)) * (params->tt[i + 1] + params->tt[i - 1] - 2 * params->tt[i]);
		}
		
		// swap arrays
		double *temp = params->tt;
		params->tt = params->tt_n;
		params->tt_n = temp;
		
		print_progress_bar(iStep + 1, nStep);
	}

	fclose(file);

	printf("\n");
}


int main()
{	
	DiffusionParams params;
	initialize(&params);
	
	int nStep = params.N; 	// number of time steps
	int plot_step = 5; 	// steps between plots
	
	evolve(&params, nStep, plot_step);

	free(params.tt);
	free(params.tt_n);

	return 0;
}
