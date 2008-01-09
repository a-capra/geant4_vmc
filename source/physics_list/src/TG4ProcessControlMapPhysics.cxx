// $Id$

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007, Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: vmc@pcroot.cern.ch
//-------------------------------------------------

/// \file TG4ProcessControlMapPhysics.cxx
/// \brief Implementation of the TG4ProcessControlMapPhysics class 
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4ProcessControlMapPhysics.h"
#include "TG4ProcessControlMap.h"
#include "TG4Globals.h"

#include <TVirtualMCDecayer.h>
#include <TVirtualMC.h>

#include <G4ParticleDefinition.hh>
#include <G4ProcessManager.hh>

//_____________________________________________________________________________
TG4ProcessControlMapPhysics::TG4ProcessControlMapPhysics(const G4String& name)
  : TG4VPhysicsConstructor(name)
{
/// Standard constructor

  FillMap();
}

//_____________________________________________________________________________
TG4ProcessControlMapPhysics::TG4ProcessControlMapPhysics(
                                           G4int verboseLevel,
                                           const G4String& name)
  : TG4VPhysicsConstructor(name, verboseLevel)
{
/// Standard constructor

  FillMap();
}

//_____________________________________________________________________________
TG4ProcessControlMapPhysics::~TG4ProcessControlMapPhysics() 
{
/// Destructor
}

//
// private methods
//

//_____________________________________________________________________________
void TG4ProcessControlMapPhysics::FillMap()
{
/// Fill the process control map with known G4 process names

  TG4ProcessControlMap* controlMap = TG4ProcessControlMap::Instance();

  controlMap->Add("msc", kMULS); 

  controlMap->Add("eIoni", kLOSS); 
  controlMap->Add("muIoni", kLOSS); 
  controlMap->Add("hIoni", kLOSS); 
  controlMap->Add("ionIoni", kLOSS); 

  controlMap->Add("Decay", kDCAY); 

  controlMap->Add("compt", kCOMP); 
  controlMap->Add("phot", kPHOT); 
  
  controlMap->Add("eBrem", kBREM); 
  controlMap->Add("muBrems", kBREM); 

  controlMap->Add("annihil", kANNI); 

  controlMap->Add("conv", kPAIR); 
  controlMap->Add("muPairProd", kPAIR); 

  controlMap->Add("HadronCapture", kHADR);
  controlMap->Add("HadronFission", kHADR);
  
  controlMap->Add("PiMinusAbsorptionAtRest", kHADR); 
  controlMap->Add("PionMinusAbsorptionAtRest", kHADR); 
  controlMap->Add("KaonMinusAbsorption", kHADR); 
  controlMap->Add("KaonMinusAbsorptionAtRest", kHADR); 
  controlMap->Add("CHIPSNuclearAbsorptionAtRest", kHADR); 
  
  controlMap->Add("AntiProtonAnnihilationAtRest", kHADR); 
  controlMap->Add("AntiNeutronAnnihilationAtRest", kHADR);

  controlMap->Add("HadronElastic", kHADR); 
  controlMap->Add("hElastic", kHADR); 
  controlMap->Add("CHIPSElasticScattering", kHADR); 
  
  controlMap->Add("PionMinusInelastic", kHADR); 
  controlMap->Add("PionPlusInelastic", kHADR); 
  controlMap->Add("KaonPlusInelastic", kHADR); 
  controlMap->Add("KaonMinusInelastic", kHADR); 
  controlMap->Add("KaonZeroLInelastic", kHADR); 
  controlMap->Add("KaonZeroSInelastic", kHADR); 
  controlMap->Add("LambdaInelastic", kHADR); 
  controlMap->Add("ProtonInelastic", kHADR); 
  controlMap->Add("AntiProtonInelastic", kHADR); 
  controlMap->Add("NeutronInelastic", kHADR); 
  controlMap->Add("AntiNeutronInelastic", kHADR); 
  controlMap->Add("LambdaInelastic", kHADR); 
  controlMap->Add("AntiLambdaInelastic", kHADR); 
  controlMap->Add("SigmaMinusInelastic", kHADR); 
  controlMap->Add("AntiSigmaMinusInelastic", kHADR); 
  controlMap->Add("SigmaPlusInelastic", kHADR); 
  controlMap->Add("AntiSigmaPlusInelastic", kHADR); 
  controlMap->Add("XiMinusInelastic", kHADR); 
  controlMap->Add("AntiXiMinusInelastic", kHADR); 
  controlMap->Add("XiZeroInelastic", kHADR); 
  controlMap->Add("AntiXiZeroInelastic", kHADR); 
  controlMap->Add("OmegaMinusInelastic", kHADR); 
  controlMap->Add("AntiOmegaMinusInelastic", kHADR); 
  controlMap->Add("DeuteronInelastic", kHADR); 
  controlMap->Add("dInelastic", kHADR); 
  controlMap->Add("TritonInelastic", kHADR); 
  controlMap->Add("tInelastic", kHADR); 
  controlMap->Add("AlphaInelastic", kHADR); 
  controlMap->Add("alphaInelastic", kHADR); 
  controlMap->Add("He3Inelastic", kHADR); 
  controlMap->Add("ionInelastic", kHADR); 
  controlMap->Add("PhotonInelastic", kHADR); 

  controlMap->Add("nKiller", kHADR); 

  controlMap->Add("muMinusCaptureAtRest", kMUNU); 
  controlMap->Add("PositronNuclear", kNoG3Controls); 
  controlMap->Add("ElectroNuclear", kNoG3Controls); 
  
  controlMap->Add("Cerenkov", kCKOV);
  controlMap->Add("Scintillation", kNoG3Controls);
  controlMap->Add("OpAbsorption", kLABS);
  controlMap->Add("OpRayleigh", kRAYL);
  controlMap->Add("OpBoundary", kLABS);
}  

//
// protected methods
//

//_____________________________________________________________________________
void TG4ProcessControlMapPhysics::ConstructParticle()
{
/// Instantiate particles - nothing to be done here
}

//_____________________________________________________________________________
void TG4ProcessControlMapPhysics::ConstructProcess()
{
/// Loop over all particles and their processes and check if
/// the process is present in the map

  TG4ProcessControlMap* controlMap = TG4ProcessControlMap::Instance();
  G4bool success = true;

  theParticleIterator->reset();
  while ((*theParticleIterator)())
  {
    G4ProcessVector* processVector 
      = theParticleIterator->value()->GetProcessManager()->GetProcessList();
    for (G4int i=0; i<processVector->length(); i++) {
    
      G4String processName = (*processVector)[i]->GetProcessName();

      if ( controlMap->GetControl(processName) == kNoG3Controls &&
           processName != "Transportation" &&
           processName != "PositronNuclear" && 
           processName != "ElectroNuclear" &&
           processName != "Scintillation" && 
           processName != "stackPopper" ) {
           
        G4String text = "Unknown process control for ";
        text += processName;
        TG4Globals::Warning(
          "TG4ProcessControlMapPhysics", "ConstructProcess", text);
        success = false;  
      }
    }              
  }
    
  if ( VerboseLevel() > 0 ) {
    if ( success )    
      G4cout << "### Processes mapped to VMC controls ok." << G4endl;
    else   
      G4cout << "### Processes mapped to VMC controls: some proceess unknown." 
             << G4endl;
  }    
}
