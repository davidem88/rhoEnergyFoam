//      Evaluate time step of Navier-Stokes equations
        volScalarField muEff(turbulence->muEff())  ;
        volScalarField k("k", thermo.Cp()*muEff/Pr);//thermal diffusivity

        scalar CoNum = 0.0;
        volScalarField lammax =  zero*U.component(0);
        if (mesh.nInternalFaces())
        {
         surfaceScalarField cave = fvc::interpolate(c) ;  
         surfaceScalarField un   = fvc::interpolate(mag(U));
         surfaceScalarField lambda = mag(un + cave);
         surfaceScalarField evmax    = lambda;
         surfaceScalarField evmu     = fvc:: interpolate(muEff/rho);
         surfaceScalarField eval     = fvc:: interpolate(k/rho/thermo.Cp());
         //dx is the distance between two centers projected along the face normal
         surfaceScalarField dx
         (
          1./mesh.surfaceInterpolation::deltaCoeffs()
         );

//       surfaceScalarField dx       = 1./mesh.surfaceInterpolation::nonOrthDeltaCoeffs();
         surfaceScalarField dx2      = sqr(dx);
         double dtdx_inv= max(evmax/dx).value() ;//inviscid limitation
         double dtdx_rmu= max(evmu/dx2).value() ;//viscous limitation
         double dtdx_ral= max(eval/dx2).value() ;//viscous limitation
 
         CoNum   = max(dtdx_inv,dtdx_rmu)     ;
         CoNum   = max(dtdx_ral,CoNum)        ;
         CoNum   = 1./CoNum;
        }
//
//
        runTime.setDeltaT
        (
         maxCo*CoNum
        );


