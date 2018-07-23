// Copyright (c) 2017, Lawrence Livermore National Security, LLC. Produced at
// the Lawrence Livermore National Laboratory. LLNL-CODE-734707. All Rights
// reserved. See files LICENSE and NOTICE for details.
//
// This file is part of CEED, a collection of benchmarks, miniapps, software
// libraries and APIs for efficient high-order finite element and spectral
// element discretizations for exascale applications. For more information and
// source code availability see http://github.com/ceed.
//
// The CEED research is supported by the Exascale Computing Project 17-SC-20-SC,
// a collaborative effort of two U.S. Department of Energy organizations (Office
// of Science and the National Nuclear Security Administration) responsible for
// the planning and preparation of a capable exascale ecosystem, including
// software, applications, hardware, advanced system engineering and early
// testbed platforms, in support of the nation's exascale computing imperative.
#include "../kernels.hpp"

// *****************************************************************************
void rMassMultAdd2D(const int, const int, const int,
                    const double*, const double*, const double*,
                    const double*, const double*, const double*,
                    double*);

void rMassMultAdd3D(const int, const int, const int,
                    const double*, const double*, const double*,
                    const double*, const double*, const double*,
                    double*);


// *****************************************************************************
void rMassMultAdd(const int DIM,
                  const int NUM_DOFS_1D,
                  const int NUM_QUAD_1D,
                  const int numElements,
                  const double* dofToQuad,
                  const double* dofToQuadD,
                  const double* quadToDof,
                  const double* quadToDofD,
                  const double* op,
                  const double* x,
                  double* __restrict__ y)
{
   dbg("\033[7mrMassMultAdd");
#ifndef __LAMBDA__
   const int blck = 256;
   const int grid = (numElements+blck-1)/blck;
#endif
   if (DIM==1) { assert(false); }
   if (DIM==2)
     call0(rMassMultAdd2D,id,grid,blck,
           NUM_DOFS_1D,NUM_QUAD_1D,
           numElements,dofToQuad,dofToQuadD,quadToDof,quadToDofD,op,x,y);
   if (DIM==3)
     call0(rMassMultAdd3D,id,grid,blck,
           NUM_DOFS_1D,NUM_QUAD_1D,
           numElements,dofToQuad,dofToQuadD,quadToDof,quadToDofD,op,x,y);
   pop();
}