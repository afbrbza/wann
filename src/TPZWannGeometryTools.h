#pragma once

#include "ProblemData.h"
#include <TPZCylinderMap.h>
#include <TPZGeoMeshTools.h>
#include <TPZGmshReader.h>
#include <TPZRefPatternDataBase.h>
#include <TPZRefPatternTools.h>
#include <TPZVTKGeoMesh.h>
#include <pzcheckgeom.h>
#include <pzgeoel.h>
#include <pzgeoelbc.h>
#include <pzvec_extras.h>
#include <tpzchangeel.h>
#include <tpzgeoelrefpattern.h>

class TPZWannGeometryTools {

public:
  static TPZGeoMesh *CreateGeoMesh(ProblemData *simData);
  static void InsertXCoorInSet(const REAL x, std::set<REAL> &nodeCoordsX, const REAL tol);
  static REAL FindClosestX(const REAL x, const std::set<REAL> &nodeCoordsX, const REAL tol);
  static bool CheckXInSet(const REAL x, const std::set<REAL> &nodeCoordsX, const REAL tol);
  static void OrderIds(TPZGeoMesh *gmesh, ProblemData *SimData);

private:
  static TPZGeoMesh *ReadMeshFromGmsh(ProblemData *simData);
  static void ModifyGeometricMeshToCylWell(TPZGeoMesh *gmesh, ProblemData *SimData);
  static void CreatePressure2DEls(TPZGeoMesh *gmesh, ProblemData *SimData);
};