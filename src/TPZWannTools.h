#pragma once

#include "ProblemData.h"
#include <Material/DarcyFlow/TPZMixedDarcyFlow.h>
#include <Material/TPZLagrangeMultiplier.h>
#include <Material/TPZLagrangeMultiplierCS.h>
#include <Material/TPZNullMaterial.h>
#include <Material/TPZNullMaterialCS.h>
#include <TPZCylinderMap.h>
#include <TPZGeoMeshTools.h>
#include <TPZGmshReader.h>
#include <TPZHDivApproxCreator.h>
#include <TPZMultiphysicsCompMesh.h>
#include <TPZRefPatternDataBase.h>
#include <TPZRefPatternTools.h>
#include <TPZVTKGeoMesh.h>
#include <pzcheckgeom.h>
#include <pzgeoel.h>
#include <pzgeoelbc.h>
#include <pzvec_extras.h>
#include <tpzchangeel.h>
#include <tpzgeoelrefpattern.h>

class TPZWannTools {
public:
  static TPZGeoMesh *CreateGeoMesh(ProblemData *simData);
  static void ModifyGeometricMeshToCylWell(TPZGeoMesh *gmesh, ProblemData *SimData);
  static void CreatePressure2DElsAndOrderIds(TPZGeoMesh *gmesh, ProblemData *SimData);
  static TPZMultiphysicsCompMesh *CreateMultiphysicsCompMesh(TPZGeoMesh *gmesh, ProblemData *SimData);

private:
  static void InsertXCoorInSet(const REAL x, std::set<REAL> &nodeCoordsX, const REAL tol);
  static REAL FindClosestX(const REAL x, const std::set<REAL> &nodeCoordsX, const REAL tol);
};