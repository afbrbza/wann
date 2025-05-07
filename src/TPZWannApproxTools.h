#pragma once

#include "TPZWannGeometryTools.h"
#include <Material/DarcyFlow/TPZMixedDarcyFlow.h>
#include <Material/TPZLagrangeMultiplier.h>
#include <Material/TPZLagrangeMultiplierCS.h>
#include <Material/TPZNullMaterial.h>
#include <Material/TPZNullMaterialCS.h>
#include <Mesh/pzintel.h>
#include <TPZHDivApproxCreator.h>
#include <TPZMultiphysicsCompMesh.h>

class TPZWannApproxTools {

public:
  static TPZMultiphysicsCompMesh *CreateMultiphysicsCompMesh(TPZGeoMesh *gmesh, ProblemData *SimData);

private:
  static void AddPressureSkinElements(TPZCompMesh *cmesh, ProblemData *SimData, const int laglevel);
  static void AddWellboreElements(TPZVec<TPZCompMesh *> &meshvec, ProblemData *SimData, const int laglevel);
  static void EqualizePressureConnects(TPZCompMesh *cmesh, ProblemData *SimData);
  static void AddHDivBoundInterfaceElements(TPZCompMesh *cmesh, ProblemData *SimData);
  static void AddInterfaceElements(TPZMultiphysicsCompMesh *cmesh, ProblemData *SimData, const int laglevel);
};