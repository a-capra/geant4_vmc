// $Id: TG4Polyhedra.h,v 1.1 2003/07/22 06:46:58 brun Exp $
// 
// Author: I. Hrivnacova, 12.10.2000 
//
// Class TG4Polyhedra
// ------------------
// G4Polyhedra class extented for public access method
// to the original parameters.

#ifndef TG4_POLYHEDRA_H
#define TG4_POLYHEDRA_H

#include <G4Polyhedra.hh>
#include <globals.hh>

class TG4Polyhedra : public G4Polyhedra
{
  public:
    TG4Polyhedra(const G4Polyhedra& rhs);
    // TG4Polyhedra(); --> moved to private
    virtual ~TG4Polyhedra();

    // methods 
   G4int GetNofZPlanes();
   G4double* GetRmin();
   G4double* GetRmax();
   G4double* GetZ();

  private:
    TG4Polyhedra();
    
    void CheckOrigin();
};

#endif //TG4_POLYHEDRA_H
