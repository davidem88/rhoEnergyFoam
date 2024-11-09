      scalar trelax = 1.;

//    Info<< "TRELAX " << trelax << " " << runTime.value()/10. << " "<< nl << endl;

      scalar tbulk= 0.;
      scalar voll  = 0.;
      scalar drhoUxl    = 0.;
      forAll (T, cellI)
      {
       drhoUxl   += rhoU[cellI].component(0)*mesh.V()[cellI];
       tbulk     += rhoU[cellI].component(0)*T[cellI]*mesh.V()[cellI];
       voll      += mesh.V()[cellI];
      }
//
      reduce(drhoUxl,sumOp<scalar>());//MPI all reduce
      reduce(tbulk ,sumOp<scalar>());//MPI all reduce
      reduce(voll ,sumOp<scalar>());//MPI all reduce
//
      tbulk = tbulk/voll ; 
      drhoUxl= drhoUxl/voll ;
      tbulk = tbulk/drhoUxl ;

      Tbulk_target = trelax*Tbulk_target + (1.-trelax)*tbulk ;
//
      

      forAll (T, cellI)
      {
       scalar rhos = rho[cellI] ;
       scalar ri   = 1./rhos;
       scalar rhou = rhoU[cellI].component(0);
       scalar rhov = rhoU[cellI].component(1);
       scalar rhow = rhoU[cellI].component(2);
       scalar uu   = rhou*ri; 
       scalar vv   = rhov*ri;
       scalar ww   = rhow*ri;
       scalar qq  = 0.5*(uu*uu+vv*vv+ww*ww);
       scalar ttnew = Tbulk_target + T[cellI] - tbulk;
       scalar pp    = rho[cellI]*ttnew;
       rhoE[cellI]  = pp*cv[cellI] + rho[cellI]*qq;
      }
