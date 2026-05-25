#include "../vector.h"
#include <stdio.h>

int main(int argc, char** argv){
	VectorWorkspace* vws = VectorAllocate(24);

	PolarVector2D valocity_of_boat = {.magnitude=4, .angle.X = 120};
	
	PolarVector2D valocity_of_river = {.magnitude=2};
	
	Vector3D vectors[] = {*	PolarVector2DToCartesian(&valocity_of_river,vws), *PolarVector2DToCartesian(&valocity_of_boat, vws)};
	
	Vector3D* R = Resultant(vectors, 2, vws);

	PolarVector3D* Rp = CartesianVectorToPolar(R, vws);

	printf("The final angle of boat (with the shore / river): %.2f deg\nThe final valocity is: %.2f m/s\n", RTD(Rp->angle.X), Rp->magnitude);

	VectorFree(vws);
	return 0;
} 
