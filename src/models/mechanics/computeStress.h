//implementation to compute stress given elasticity matrix (CIJ) and
//strain/displacement-gradient

#ifndef COMPUTESTRESS_MECHANICS_H
#define COMPUTESTRESS_MECHANICS_H
//this source file is temporarily treated as a header file (hence
//#ifndef's) till library packaging scheme is finalized

#include "anisotropy.h" // Is this necessary? (Steve)

// Compute stress with displacement-gradient as input

// Mathematical formulation (3D): S -> stress vector, R -> stress tensor, C -> stiffness tensor, E -> strain vector
//
// Generalized Hooke's law:
// [ S(0) ]   [ C11 C12 C13 C14 C15 C16 ] [ E(0) ]
// [ S(1) ]   [ C21 C22 C13 C14 C15 C16 ] [ E(1) ]
// [ S(2) ]   [ C31 C32 C33 C34 C35 C36 ] [ E(2) ]
// [ S(3) ] = [ C41 C42 C43 C44 C45 C46 ] [ E(3) ]
// [ S(4) ]   [ C51 C52 C53 C54 C55 C56 ] [ E(4) ]
// [ S(5) ]   [ C61 C62 C63 C64 C65 C66 ] [ E(5) ]
//
// Strain vector definition: (using Ricci calculus notation, where commas in subscript refer to partial derivatives)
// E(0) = epsilon1 = epsilon11 = 1/2 ( u1,1 + u1,1 )
// E(1) = epsilon2 = epsilon22 = 1/2 ( u2,2 + u2,2 )
// E(2) = epsilon3 = epsilon33 = 1/2 ( u3,3 + u3,3 )
// E(3) = epsilon4 = 2*epsilon23 = ( u2,3 + u3,2 )
// E(4) = epsilon5 = 2*epsilon13 = ( u1,3 + u3,1 )
// E(5) = epsilon6 = 2*epsilon12 = ( u1,2 + u2,1 )
//
// Stress vector definition:
// S(0) = R[0][0] = sigma11
// S(1) = R[1][1] = sigma22
// S(2) = R[2][2] = sigma33
// S(3) = R[1][2] = R[2][1] = sigma23 = sigma32
// S(4) = R[0][2] = R[2][0] = sigma13 = sigma31
// S(5) = R[0][1] = R[1][0] = sigma12 = sigma21


template <int dim>
void computeStress(const dealii::Table<2, double>& CIJ, vectorgradType& ux, vectorgradType& R){
#if problemDIM==3
  dealii::Table<1, dealii::VectorizedArray<double> > S(6), E(6);
  E(0)=ux[0][0]; E(1)=ux[1][1]; E(2)=ux[2][2];
  E(3)=ux[1][2]+ux[2][1];
  E(4)=ux[0][2]+ux[2][0];
  E(5)=ux[0][1]+ux[1][0];
  for (unsigned int i=0; i<6; i++){
    S(i)=0.0;
    for (unsigned int j=0; j<6; j++){
      S(i)+=CIJ(i,j)*E(j);
    }
  }
  R[0][0]=S(0); R[1][1]=S(1); R[2][2]=S(2);
  R[1][2]=S(3); R[0][2]=S(4); R[0][1]=S(5);
  R[2][1]=S(3); R[2][0]=S(4); R[1][0]=S(5);     
#elif problemDIM==2
  dealii::Table<1, dealii::VectorizedArray<double> > S(3), E(3);
  E(0)=ux[0][0]; E(1)=ux[1][1]; 
  E(2)=ux[0][1]+ux[1][0];
  for (unsigned int i=0; i<3; i++){
    S(i)=0.0;
    for (unsigned int j=0; j<3; j++){
      S(i)+=CIJ(i,j)*E(j);
    }
  }
  R[0][0]=S(0); R[1][1]=S(1); 
  R[0][1]=S(2); R[1][0]=S(2); 
#elif problemDIM==1
  dealii::Table<1, dealii::VectorizedArray<double> > S(1), E(1);
  E(0)=ux[0][0]; 
  S(0)=CIJ(0,0)*E(0);
  R[0][0]=S(0); 
#endif			       
}

#endif
