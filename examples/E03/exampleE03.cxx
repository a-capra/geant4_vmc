//------------------------------------------------
// The Virtual Monte Carlo examples
// Copyright (C) 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file exampleE03.cxx
/// \brief The Geant4 VMC example E03 application executable
///
/// The Geant4 VMC application executable
/// with explicitely instantiated TGeant3 or TGeant4 and linked 
/// with all libraries.
///
/// \date 31/01/2014
/// \author I. Hrivnacova; IPN, Orsay

#include "Ex03MCApplication.h"

#ifdef USE_GEANT4
#include "TG4RunConfiguration.h"
#include "TGeant4.h"
#endif

#ifdef USE_GEANT3
#include "TGeant3TGeo.h"
#endif

#include "TThread.h"
#include "TROOT.h"
#include "TInterpreter.h"

namespace {

// Utility function
void ProcessMacro(int argc, char** argv) {
  //G4cout << "Program arguments " << argc << "  ";
  //for (G4int i=0; i< argc; ++i) { G4cout << argv[i] << ",  "; }
  //G4cout << G4endl;

  G4int counter = 1;
  G4String macroName = argv[counter];
  G4String functionName = macroName;
  functionName.erase(functionName.find(".C"), 2);
  functionName += "(";
  while ( ++counter < argc ) {
    functionName += argv[counter];
    if ( counter < (argc - 1) ) functionName += ",";
  }
  functionName += ")";
  G4cout << "macroName: " << macroName << G4endl;
  G4cout << "functionName: " << functionName << G4endl;

  gROOT->LoadMacro(macroName);
  gInterpreter->ProcessLine(functionName);
}

}

int main(int argc, char** argv)
{
  // Initialize Root threading.
  // (Multi-threading is triggered automatically if Geant4 was built 
  //  in MT mode.)
#ifdef G4MULTITHREADED
   TThread::Initialize();
#endif

  // Create MC application (thread local)
  Ex03MCApplication* appl 
    =  new Ex03MCApplication("ExampleE03", 
                             "The examplE03 MC application");

#ifdef USE_GEANT4
  // RunConfiguration for Geant4 
  TG4RunConfiguration* runConfiguration 
    = new TG4RunConfiguration("geomRootToGeant4", "FTFP_BERT");

  // TGeant4
  TGeant4* geant4
    = new TGeant4("TGeant4", "The Geant4 Monte Carlo", runConfiguration,
                  argc, argv);

  // Customise Geant4 setting
  // (verbose level, global range cut, ..)
  geant4->ProcessGeantMacro("g4config.in");
  // Setting Geant4 visualization
  geant4->ProcessGeantMacro("g4vis.in");
#endif
  
#ifdef USE_GEANT3
  new TGeant3TGeo("C++ Interface to Geant3");
#endif

  // Run example
  if ( argc <= 1 ) {
    appl->InitMC("");
    appl->RunMC(5);
  }
  else {
    // Run from Root macro
    ProcessMacro(argc, argv);
  }

  delete appl;
}  