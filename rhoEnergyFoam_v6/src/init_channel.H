#include "Random.H"

// Set up the random number generator with a specified seed
Foam::Random rndGen(Foam::label(12345));

// Initialize with Poiseulle velocity profile
   forAll(U,cellI)
    {
        U[cellI].x()=3./2.*Foam::sqrt(1.4)*rm*(1.-Foam::pow(U.mesh().C()[cellI].y(),2)) + 0.01*rm*(rndGen.scalar01() * 2.0 - 1.0) ;
        U[cellI].y()= 0.05*Foam::sqrt(1.4)*rm*Foam::sin(0.5*M_PI*U.mesh().C()[cellI].y())*Foam::cos(2.*M_PI*U.mesh().C()[cellI].z()) + 0.01*rm*(rndGen.scalar01() * 2.0 - 1.0); 
        U[cellI].z()= 0.05*Foam::sqrt(1.4)*rm*Foam::sin(0.5*M_PI*U.mesh().C()[cellI].y())*Foam::sin(2.*M_PI*U.mesh().C()[cellI].z()) + 0.01*rm*(rndGen.scalar01() * 2.0 - 1.0); 
    }


      scalar dUx    = 0;
      scalar vol       = 0;
      volScalarField Ux = U.component(0) ;
      forAll (Ux, cellI)
      {
       dUx    += U[cellI].component(0)*mesh.V()[cellI];
       vol    += mesh.V()[cellI];
      }
//
      reduce(dUx,sumOp<scalar>())   ;//MPI all reduce
      reduce(vol      ,sumOp<scalar>());
      dUx     = dUx/vol;

      forAll (Ux, cellI)
      {
       U[cellI].component(0) = U[cellI].component(0) - dUx + Foam::sqrt(1.4)*rm;
      }
      rhoU = rho*U;

