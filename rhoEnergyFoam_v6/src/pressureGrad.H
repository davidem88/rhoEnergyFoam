//    Evaluate pressure gradient for channel flow
      dimensionedScalar dpdx
      (
       "dpdx",
       dimensionSet(1,-2,-2,0,0,0,0),
       scalar(1.)
      );
// 
      dpdx_temp = 0;
      drhoUx    = 0;
      Tbulk     = 0;
      vol       = 0;
      rhob      = 0;
      volScalarField rhoUx = rhoU.component(0) ;
      volVectorField flU   = fvc::div(momFlux) ;
      volScalarField flUx  = flU.component(0)  ;
      forAll (flUx, cellI)
      {
       dpdx_temp += flUx[cellI]*mesh.V()[cellI];
       drhoUx    += rhoUx[cellI]*mesh.V()[cellI];
       Tbulk     += rhoUx[cellI]*T[cellI]*mesh.V()[cellI];
       rhob      += rho[cellI]*mesh.V()[cellI];
       vol       += mesh.V()[cellI];
      }
//
      reduce(dpdx_temp,sumOp<scalar>());//MPI all reduce
      reduce(drhoUx,sumOp<scalar>())   ;//MPI all reduce
      reduce(Tbulk,sumOp<scalar>())    ;//MPI all reduce
      reduce(vol      ,sumOp<scalar>());
      reduce(rhob     ,sumOp<scalar>());
      
      dpdx_add   = dpdx_temp/vol*dpdx;
      dpdx_prt   = dpdx_add;
      rhob       = rhob/vol;
      drhoUx     = drhoUx/rhob/vol;
      Tbulk      = Tbulk/vol/drhoUx;
      drhoUx_prt = drhoUx;
      Tbulk_prt  = Tbulk;
      rhob_prt   = rhob;
