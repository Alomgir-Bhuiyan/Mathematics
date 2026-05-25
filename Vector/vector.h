#ifndef _VECTOR__H
#define _VECTOR__H
#include <stdint.h>

typedef enum _Axis {X, Y, Z} Axis;


typedef struct {
	double X, Y, Z;
} Planer3D;

typedef struct {
	double X, Y;
} Planer2D;

typedef struct _Vector3D {
	double i, j, k;
	Planer3D angle;
} Vector3D;


typedef struct {
	void* allocated_space;
} VectorWorkspace ;


typedef struct {
	double magnitude;
	Planer3D angle;
} PolarVector3D;


typedef struct {
	double magnitude;
	Planer2D angle;
} PolarVector2D;


double RTD(double radian); //Converts radian to degree


double DTR(double degree); //Converts degree to radian

double Magnitude(Vector3D* Ū); //Gives the magnitude of a vector 


double AngleWith(Vector3D* Ū, Axis axis); //Gives the angle with a specific axis 


Planer3D GetAngles(Vector3D* V); //Returns all the angles 


VectorWorkspace* VectorAllocate(size_t bytes); //Allocate heap for the output to be stored


void VectorFree(void* addr); //Frees the memory that was alloated to store the output


Vector3D* PolarVector3DToCartesian(PolarVector3D* V,VectorWorkspace*); //Converts polar vector to cartesian
			

PolarVector3D* CartesianVectorToPolar(Vector3D* V, VectorWorkspace*); //Converts cartesian vector to polar


Vector3D* Resultant(Vector3D vectors[], uint32_t vectorc, VectorWorkspace*); //Gives the resultant of vectors


double DotProduct(Vector3D* V, Vector3D* V_); //Gives the dot product of two vector


Vector3D* CrossProduct(Vector3D* Ā, Vector3D* Ē, VectorWorkspace* allocated_memory); //Gives the cross product of 2 vectors



Vector3D* UnitVector(Vector3D* Ā, VectorWorkspace*); //Returns the unit vector of the following vector 


double AngleBetween(Vector3D* V, Vector3D* V_); //Gives the angle between two vector


Vector3D* PolarVector2DToCartesian(PolarVector2D* V, VectorWorkspace*); //Convert from 2D polar vector to cartesian


Vector3D* VectorSubtraction(Vector3D vectors[], uint32_t vectorc, VectorWorkspace* mem); //Subtract vectors


Vector3D* VectorAddition(Vector3D vectors[], uint32_t vectorc, VectorWorkspace* allocated_memory); //Add vectors together 


Vector3D Negate(Vector3D v); //Its negate a vector

#endif 
