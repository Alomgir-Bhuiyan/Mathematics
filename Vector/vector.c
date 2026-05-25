#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "vector.h"


double RTD(double radian) {
	return radian*(180/M_PI);
}

double DTR(double degree) {
	return degree*(M_PI/180);
}

double Magnitude(Vector3D* Ū) {
	return sqrt(pow(Ū->i, 2)+pow(Ū->j, 2)+pow(Ū->k, 2));
}

double AngleWith(Vector3D* Ū, Axis axis) {
	double U = Magnitude(Ū);
	if(!axis) {
		return acos(Ū->i/U);
	}else if(axis==1) {
		return acos(Ū->j/U);
	}
	return acos(Ū->k/U);
}

Planer3D GetAngles(Vector3D* V){
	return (Planer3D){AngleWith(V, X), AngleWith(V, Y), AngleWith(V, Z)};
}

void VectorFree(void* addr){
	free(addr);
}

VectorWorkspace* VectorAllocate(size_t bytes){
	return malloc(bytes);
}

PolarVector3D* CartesianVectorToPolar(Vector3D* V, VectorWorkspace* allocated_memory){
	PolarVector3D* polar = (PolarVector3D*)allocated_memory;
	polar->magnitude = Magnitude(V);
	polar->angle = GetAngles(V);

	return polar;
}

Vector3D* PolarVectorToCartesian(PolarVector3D* V, VectorWorkspace* allocated_memory){
	Vector3D* cartesian = (Vector3D*)allocated_memory;

	*cartesian = (Vector3D){.i=V->magnitude*cos(V->angle.X), .j=V->magnitude*cos(V->angle.Y), .k=V->magnitude*cos(V->angle.Z)};

	cartesian->angle = GetAngles(cartesian);

	return cartesian;
}

Vector3D* PolarVector2DToCartesian(PolarVector2D* V, VectorWorkspace* allocated_memory){
	Vector3D* cartesian = (Vector3D*)allocated_memory;

	cartesian->i = V->magnitude*cos(DTR(V->angle.X));
	cartesian->j = V->magnitude*sin(DTR(V->angle.X));

	return cartesian;
}


Vector3D* Resultant(Vector3D vectors[], uint32_t vectorc, VectorWorkspace* allocated_memory){

	Vector3D *Ro = (Vector3D*)allocated_memory;
	*Ro = (Vector3D){0};

	for (uint32_t i =0; i <vectorc; i++){
		Ro->i += vectors[i].i;
		Ro->j += vectors[i].j;
		Ro->k += vectors[i].k;
	}
	Ro->angle = GetAngles(Ro);

	return Ro;
}

double DotProduct(Vector3D* V, Vector3D* V_){
	return V->i*V_->i + V->j*V_->j + V->k*V_->k;
}

double AngleBetween(Vector3D* V, Vector3D* V_){
	double dot_product = DotProduct(V, V_);
	double v = Magnitude(V);
	double v_ = Magnitude(V_);

	double θ = acos(dot_product/(v*v_));

	return θ;
}

Vector3D* CrossProduct(Vector3D* Ā, Vector3D* Ē, VectorWorkspace* allocated_memory){
	Vector3D* Ro = (Vector3D*)allocated_memory;

	Ro->i = Ā->j*Ē->k - Ē->j*Ā->k;
	Ro->j = -Ā->i*Ē->k + Ē->i*Ā->k;
	Ro->k = Ā->i*Ē->j - Ē->i*Ā->j;

	Ro->angle = GetAngles(Ro);

	return Ro;
}

Vector3D* UnitVector(Vector3D* Ā, VectorWorkspace* allocated_memory){
	Vector3D* Res = (Vector3D*)allocated_memory;

	double A = Magnitude(Ā);
	*Res = (Vector3D){Ā->i/A, Ā->j/A, Ā->k/A, {0}};
	Res->angle = GetAngles(Res);

	return Res;
}

Vector3D* VectorAddition(Vector3D vectors[], uint32_t vectorc, VectorWorkspace* allocated_memory){
	Vector3D* Ro = (Vector3D*)allocated_memory;
	*Ro = (Vector3D){0};

	for(uint32_t i = 0; i<vectorc; i++){
		Ro->i += vectors[i].i;
		Ro->j += vectors[i].j;
		Ro->k += vectors[i].k;
	}

	Ro->angle = GetAngles(Ro);

	return Ro;
};

Vector3D Negate(Vector3D v) {
	return (Vector3D){-v.i, -v.j, -v.k, {0}};
}

Vector3D* VectorSubtraction(Vector3D vectors[], uint32_t vectorc, VectorWorkspace* mem){
	Vector3D* Ro = (Vector3D*)mem;

	*Ro = vectors[0];

	for(uint32_t i = 1; i < vectorc; i++){
		Ro->i -= vectors[i].i;
		Ro->j -= vectors[i].j;
		Ro->k -= vectors[i].k;
	}

	Ro->angle = GetAngles(Ro);

	return Ro;
}

