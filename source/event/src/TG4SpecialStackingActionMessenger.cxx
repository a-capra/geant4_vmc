//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2007 - 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file TG4SpecialStackingActionMessenger.cxx
/// \brief Implementation of the TG4SpecialStackingActionMessenger class
///
/// \author I. Hrivnacova; IPN, Orsay

#include "TG4SpecialStackingActionMessenger.h"
#include "TG4Globals.h"
#include "TG4SpecialStackingAction.h"

#include <G4UIcmdWithABool.hh>
#include <G4UIcmdWithAnInteger.hh>

//_____________________________________________________________________________
TG4SpecialStackingActionMessenger::TG4SpecialStackingActionMessenger(
  TG4SpecialStackingAction* stackingAction)
  : G4UImessenger(),
    fStackingAction(stackingAction),
    fSkipNeutrinoCmd(0),
    fWaitPrimaryCmd(0)

{
  /// Standard constructor

  fSkipNeutrinoCmd = new G4UIcmdWithABool("/mcTracking/skipNeutrino", this);
  fSkipNeutrinoCmd->SetGuidance("Option to skip neutrinos.");
  fSkipNeutrinoCmd->SetGuidance("By default this option is false.");
  fSkipNeutrinoCmd->SetParameterName("SkipNeutrino", false);
  fSkipNeutrinoCmd->AvailableForStates(
    G4State_PreInit, G4State_Init, G4State_Idle);

  fWaitPrimaryCmd = new G4UIcmdWithABool("/mcTracking/waitPrimary", this);
  fWaitPrimaryCmd->SetGuidance(
    "Option to track all secondaries before starting the next primary.");
  fWaitPrimaryCmd->SetGuidance("By default this option is true.");
  fWaitPrimaryCmd->SetParameterName("WaitPrimary", true);
  fWaitPrimaryCmd->AvailableForStates(
    G4State_PreInit, G4State_Init, G4State_Idle);
}

//_____________________________________________________________________________
TG4SpecialStackingActionMessenger::~TG4SpecialStackingActionMessenger()
{
  /// Destructor

  delete fSkipNeutrinoCmd;
  delete fWaitPrimaryCmd;
}

//
// public methods
//

//_____________________________________________________________________________
void TG4SpecialStackingActionMessenger::SetNewValue(
  G4UIcommand* command, G4String newValue)
{
  /// Apply command to the associated object.

  if (command == fSkipNeutrinoCmd) {
    fStackingAction->SetSkipNeutrino(
      fSkipNeutrinoCmd->GetNewBoolValue(newValue));
  }
  else if (command == fWaitPrimaryCmd) {
    fStackingAction->SetWaitPrimary(fWaitPrimaryCmd->GetNewBoolValue(newValue));
  }
}
