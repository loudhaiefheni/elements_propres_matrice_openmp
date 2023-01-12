
#include <petscksp.h>

static char help[] = "Solves a tridiagonal linear system with KSP.\n\n";

int main(int argc, char **args)
{
	Vec         x;       /* approx solution, RHS, exact solution */
	PetscCall(PetscInitialize(&argc, &args, (char *)0, help));
	PetscCall(VecCreate(PETSC_COMM_SELF, &x));
	return 0;
}
