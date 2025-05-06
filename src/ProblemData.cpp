
#include <fstream>
#include <iostream>
#include <pzerror.h>
#include <string>

#include "ProblemData.h"

using namespace std;

// constructor
ProblemData::ProblemData() : m_VerbosityLevel(0)

{
  m_Wellbore.BCs.reserve(2);
  m_Reservoir.BCs.reserve(3);
}

// deconstructor
ProblemData::~ProblemData() {}

// readjson function. takes a json function as parameter and completes the required simulation data
void ProblemData::ReadJson(std::string file) {
  std::string path(std::string(INPUTDIR) + "/" + file);
  std::ifstream filejson(path);
  json input = json::parse(filejson, nullptr, true, true); // to ignore comments in json file

  if (input.find("MeshData") == input.end())
    DebugStop();
  json meshdata = input["MeshData"];
  if (meshdata.find("file") == meshdata.end())
    DebugStop();
  m_Mesh.file = meshdata["file"];
  if (meshdata.find("NumUniformRef") == meshdata.end())
    DebugStop();
  m_Mesh.NumUniformRef = meshdata["NumUniformRef"];
  if (meshdata.find("NumDirRef") == meshdata.end())
    DebugStop();
  m_Mesh.NumDirRef = meshdata["NumDirRef"];
  if (meshdata.find("Resolution") == meshdata.end())
    DebugStop();
  m_Mesh.Resolution = meshdata["Resolution"];
  if (meshdata.find("ToCylindrical") == meshdata.end())
    DebugStop();
  m_Mesh.ToCylindrical = meshdata["ToCylindrical"];

  if (input.find("WellboreData") == input.end())
    DebugStop();
  json wellbore = input["WellboreData"];
  if (wellbore.find("name") == wellbore.end())
    DebugStop();
  m_Wellbore.name = wellbore["name"];
  if (wellbore.find("perm") == wellbore.end())
    DebugStop();
  m_Wellbore.perm = wellbore["perm"];
  if (wellbore.find("pOrder") == wellbore.end())
    DebugStop();
  m_Wellbore.pOrder = wellbore["pOrder"];
  if (wellbore.find("radius") == wellbore.end())
    DebugStop();
  m_Wellbore.radius = wellbore["matid"];
  if (wellbore.find("length") == wellbore.end())
    DebugStop();
  m_Wellbore.length = wellbore["length"];
  if (wellbore.find("excentricity") == wellbore.end())
    DebugStop();
  m_Wellbore.excentricity = wellbore["excentricity"];
  if (wellbore.find("BCs") == wellbore.end())
    DebugStop();
  json bcs = wellbore["BCs"];
  for (int i = 0; i < bcs.size(); i++) {
    if (bcs[i].find("name") == bcs[i].end())
      DebugStop();
    std::pair<std::string, BoundaryData> bcpair;
    bcpair.first = bcs[i]["name"];
    if (bcs[i].find("type") == bcs[i].end())
      DebugStop();
    bcpair.second.type = bcs[i]["type"];
    if (bcs[i].find("value") == bcs[i].end())
      DebugStop();
    bcpair.second.value = bcs[i]["value"];
    m_Wellbore.BCs.insert(bcpair);
  }

  if (input.find("ReservoirData") == input.end())
    DebugStop();
  json reservoir = input["ReservoirData"];
  if (reservoir.find("name") == reservoir.end())
    DebugStop();
  m_Reservoir.name = reservoir["name"];
  if (reservoir.find("perm") == reservoir.end())
    DebugStop();
  m_Reservoir.perm = reservoir["perm"];
  if (reservoir.find("porosity") == reservoir.end())
    DebugStop();
  m_Reservoir.porosity = reservoir["porosity"];
  if (reservoir.find("pOrder") == reservoir.end())
    DebugStop();
  m_Reservoir.pOrder = reservoir["pOrder"];
  if (reservoir.find("height") == reservoir.end())
    DebugStop();
  m_Reservoir.height = reservoir["height"];
  if (reservoir.find("width") == reservoir.end())
    DebugStop();
  m_Reservoir.width = reservoir["width"];
  if (reservoir.find("length") == reservoir.end())
    DebugStop();
  m_Reservoir.length = reservoir["length"];
  if (reservoir.find("BCs") == reservoir.end())
    DebugStop();
  json bcsres = reservoir["BCs"];
  for (int i = 0; i < bcsres.size(); i++) {
    if (bcsres[i].find("name") == bcsres[i].end())
      DebugStop();
    std::pair<std::string, BoundaryData> bcpair;
    bcpair.first = bcsres[i]["name"];
    if (bcsres[i].find("type") == bcsres[i].end())
      DebugStop();
    bcpair.second.type = bcsres[i]["type"];
    if (bcsres[i].find("value") == bcsres[i].end())
      DebugStop();
    bcpair.second.value = bcsres[i]["value"];
    m_Reservoir.BCs.insert(bcpair);
  }

  if (input.find("FluidData") == input.end())
    DebugStop();
  json fluid = input["FluidData"];
  if (fluid.find("name") == fluid.end())
    DebugStop();
  m_Fluid.name = fluid["name"];
  if (fluid.find("viscosity") == fluid.end())
    DebugStop();
  m_Fluid.viscosity = fluid["viscosity"];
  if (fluid.find("density") == fluid.end())
    DebugStop();
  m_Fluid.density = fluid["density"];

  if (input.find("VerbosityLevel") == input.end())
    DebugStop();
  m_VerbosityLevel = input["VerbosityLevel"];
}

void ProblemData::Print(std::ostream &out) {
  out << "\nSimulation inputs: \n\n";
  out << "Mesh Data:\n";
  out << "File: " << m_Mesh.file << std::endl;
  out << "Number of uniform refinements: " << m_Mesh.NumUniformRef << std::endl;
  out << "Number of directional refinements: " << m_Mesh.NumDirRef << std::endl;
  out << "VTK mesh resolution: " << m_Mesh.Resolution << std::endl;
  out << "Cylindrical map: " << (m_Mesh.ToCylindrical ? "Yes" : "No") << std::endl
      << std::endl;

  out << "Wellbore Data:\n";
  out << "Name: " << m_Wellbore.name << std::endl;
  out << "Material ID: " << m_Wellbore.matid << std::endl;
  out << "Permeability: " << m_Wellbore.perm << std::endl;
  out << "Polynomial order: " << m_Wellbore.pOrder << std::endl;
  out << "Radius: " << m_Wellbore.radius << std::endl;
  out << "Length: " << m_Wellbore.length << std::endl;
  out << "Excentricity: " << m_Wellbore.excentricity << std::endl;
  out << "Boundary conditions:\n";
  for (const auto &bc : m_Wellbore.BCs) {
    out << "  Name: " << bc.first << std::endl;
    out << "  Material ID: " << bc.second.matid << std::endl;
    out << "  Type: " << bc.second.type << std::endl;
    out << "  Value: " << bc.second.value << std::endl;
  }
  out << std::endl;

  out << "Reservoir Data:\n";
  out << "Name: " << m_Reservoir.name << std::endl;
  out << "Material ID: " << m_Reservoir.matid << std::endl;
  out << "Permeability: " << m_Reservoir.perm << std::endl;
  out << "Porosity: " << m_Reservoir.porosity << std::endl;
  out << "Polynomial order: " << m_Reservoir.pOrder << std::endl;
  out << "Height: " << m_Reservoir.height << std::endl;
  out << "Width: " << m_Reservoir.width << std::endl;
  out << "Length: " << m_Reservoir.length << std::endl;
  out << "Boundary conditions:\n";
  for (const auto &bc : m_Reservoir.BCs) {
    out << "  Name: " << bc.first << std::endl;
    out << "  Material ID: " << bc.second.matid << std::endl;
    out << "  Type: " << bc.second.type << std::endl;
    out << "  Value: " << bc.second.value << std::endl;
  }
  out << std::endl;

  out << "Fluid Data:\n";
  out << "Name: " << m_Fluid.name << std::endl;
  out << "Viscosity: " << m_Fluid.viscosity << std::endl;
  out << "Density: " << m_Fluid.density << std::endl
      << std::endl;

  out << std::endl;

  out << "Verbosity Level: " << m_VerbosityLevel << std::endl;
}