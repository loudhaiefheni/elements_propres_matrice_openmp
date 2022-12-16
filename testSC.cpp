
#include <petscmat.h>

int main(int argc, char **args){
	Mat				A;
	PetscViewer     fd;  
	char            file[PETSC_MAX_PATH_LEN] = "data/bcsstk01.mtx";
	PetscErrorCode	ierr;
	PetscInitialize(&argc, &args, (char *)0, help);
	//ierr=MatLoad(Mat mat, PetscViewer viewer);
	PetscOptionsGetString(NULL, NULL, "-f", file, sizeof(file), &flg);
	return 0;
}
