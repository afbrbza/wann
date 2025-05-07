#pragma once

#include "ProblemData.h"
#include <Material/DarcyFlow/TPZMixedDarcyFlow.h>
#include <TPZGeoMeshTools.h>
#include <TPZMultiphysicsCompMesh.h>
#include <TPZVTKGenerator.h>
#include <pzcmesh.h>
#include <pzcompel.h>
#include <pzvec_extras.h>

class TPZWannPostProcTools {

public:
  static void GenerateTrainingData(TPZGeoMesh *gmesh, ProblemData *SimData);
  static void WriteWellboreVTK(TPZCompMesh *cmesh, ProblemData *SimData);
  static void WriteReservoirVTK(TPZCompMesh *cmesh, ProblemData *SimData);
  static void WriteVTKs(TPZCompMesh *cmesh, ProblemData *SimData);
  static void PostProcessAllData(TPZCompMesh *cmesh, TPZGeoMesh *gmesh, ProblemData *SimData);
};