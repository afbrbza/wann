#ifdef HAVE_CONFIG_H
#include <pz_config.h>
#endif

#include "TPZWannApproxTools.h"
#include "TPZWannGeometryTools.h"
#include "TPZWannPostProcTools.h"
#include <TPZLinearAnalysis.h>
#include <TPZSSpStructMatrix.h> //symmetric sparse matrix storage
#include <iostream>
#include <pzstepsolver.h>

using namespace std;

const int global_nthread = 32;

void PostProceDataForANN(TPZGeoMesh *gmesh, ProblemData *SimData, std::string &filename, const int npts);

int main() {
  std::cout << "--------- Starting simulation ---------" << std::endl;
#ifdef PZ_LOG
  TPZLogger::InitializePZLOG();
#endif

  // Problem data
  ProblemData SimData;
  SimData.ReadJson("wann3d.json");

  TPZGeoMesh *gmesh = TPZWannGeometryTools::CreateGeoMesh(&SimData);

  TPZMultiphysicsCompMesh *cmesh = TPZWannApproxTools::CreateMultiphysicsCompMesh(gmesh, &SimData);

  TPZLinearAnalysis analysis(cmesh);
  TPZSSpStructMatrix<STATE> skylstr(cmesh);
  skylstr.SetNumThreads(global_nthread);
  analysis.SetStructuralMatrix(skylstr);

  TPZStepSolver<STATE> step;
  step.SetDirect(ELDLt);
  analysis.SetSolver(step);

  analysis.Run();

  TPZWannPostProcTools::PostProcessAllData(cmesh, gmesh, &SimData);

  delete cmesh;
  delete gmesh;
  std::cout << "--------- Simulation finished ---------" << std::endl;
}