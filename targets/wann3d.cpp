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

int main(int argc, char *argv[]) {

  TLaplaceExample1 exact; // Global variable to be used in the material objects
  exact.fDimension = 3;
  exact.fExact = TLaplaceExample1::ENone;

  std::string jsonfile = "wann3d.json";

  if (argc > 2) {
    std::cout << argv[0] << " being called with too many arguments." << std::endl;
    DebugStop();
  } else if (argc == 2) {
    jsonfile = argv[1];
  }

  if (jsonfile.find(".json") == std::string::npos) {
    jsonfile += ".json";
  }
  std::cout << "Using json file: " << jsonfile << std::endl;
  std::cout << "--------- Starting simulation ---------" << std::endl;
#ifdef PZ_LOG
  TPZLogger::InitializePZLOG();
#endif

  // Problem data
  ProblemData SimData;
  SimData.ReadJson(jsonfile);

  TPZGeoMesh *gmesh = TPZWannGeometryTools::CreateGeoMesh(&SimData);

  TPZMultiphysicsCompMesh *cmesh = TPZWannApproxTools::CreateMultiphysicsCompMesh(gmesh, &SimData, &exact);

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