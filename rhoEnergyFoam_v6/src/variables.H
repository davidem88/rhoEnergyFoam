
         volVectorField rhoUOld
         (
         IOobject
         (
         "rhoUOld",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedVector("rhoUOld",dimensionSet(1,-2,-1,0,0,0,0),vector(0,0,0))
         );

         surfaceScalarField rho_L
         (
         IOobject
         (
         "rho_L",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("rho_L",dimensionSet(1,-3,0,0,0,0,0),scalar(0))
         );

          surfaceScalarField rho_R
         (
         IOobject
         (
         "rho_R",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("rho_R",dimensionSet(1,-3,0,0,0,0,0),scalar(0))
         );
 
         surfaceScalarField c_L
         (
         IOobject
         (
         "c_L",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("c_L",dimensionSet(0,1,-1,0,0,0,0),scalar(0))
         );

          surfaceScalarField c_R
         (
         IOobject
         (
         "c_R",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("c_R",dimensionSet(0,1,-1,0,0,0,0),scalar(0))
         );
 
         surfaceScalarField p_L
         (
         IOobject
         (
         "p_L",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("p_L",dimensionSet(1,-1,-2,0,0,0,0),scalar(0))
         );
          surfaceScalarField p_R
         (
         IOobject
         (
         "p_R",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("p_R",dimensionSet(1,-1,-2,0,0,0,0),scalar(0))
         );
 
         surfaceScalarField M_L
         (
         IOobject
         (
         "M_L",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("M_L",dimensionSet(0,0,0,0,0,0,0),scalar(0))
         );
          surfaceScalarField M_R
         (
         IOobject
         (
         "M_R",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("M_R",dimensionSet(0,0,0,0,0,0,0),scalar(0))
         );

         surfaceScalarField c12
         (
         IOobject
         (
         "c12",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("c12",dimensionSet(0,1,-1,0,0,0,0),scalar(0))
         );

         surfaceScalarField m2
         (
         IOobject
         (
         "m2",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("m2",dimensionSet(0,0,0,0,0,0,0),scalar(0))
         );

         surfaceScalarField m0
         (
         IOobject
         (
         "m0",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("m0",dimensionSet(0,0,0,0,0,0,0),scalar(0))
         );


         surfaceScalarField U_L
         (
         IOobject
         (
         "U_L",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("U_L",dimensionSet(0,1,-1,0,0,0,0),scalar(0))
         );

         surfaceScalarField U_R
         (
         IOobject
         (
         "U_R",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("U_R",dimensionSet(0,1,-1,0,0,0,0),scalar(0))
         );

         surfaceVectorField Uvec_L
         (
         IOobject
         (
         "Uvec_L",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedVector("Uvec_L",dimensionSet(0,1,-1,0,0,0,0),vector(0 ,0 ,0))
         );

         surfaceVectorField Uvec_R
         (
         IOobject
         (
         "Uvec_R",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedVector("Uvec_R",dimensionSet(0,1,-1,0,0,0,0),vector(0,0,0))
         );

         surfaceVectorField momFlux
         (
         IOobject
         (
         "momFlux",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedVector("momFlux",dimensionSet(1,1,-2,0,0,0,0),vector(0,0,0))
         );
        
         
         surfaceVectorField vecDivU
         (
         IOobject
         (
         "vecDivU",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedVector("vecDivU",dimensionSet(0,0,-1,0,0,0,0),vector(0,0,0))
         );
       

         volScalarField rhoOld
         (
         IOobject
         (
         "rhoOld",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
        dimensionedScalar("rhoOld",dimensionSet(1,-3,0,0,0,0,0),scalar(0))
         );


         volScalarField rhoEOld
         (
         IOobject
         (
         "rhoEOld",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("rhoEOld",dimensionSet(1,-1,-2,0,0,0,0),scalar(0))
         );

       volScalarField ducSensor
         (
         IOobject
         (
         "ducSensor",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
        dimensionedScalar("ducSensor",dimensionSet(0,0,0,0,0,0,0),scalar(0))
         );

       volVectorField Mach
         (
         IOobject
         (
         "Mach",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
        dimensionedVector("Mach",dimensionSet(0,0,0,0,0,0,0),vector(0,0,0))
         );

       volScalarField c
         (
         IOobject
         (
         "c",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("c",dimensionSet(0,1,-1,0,0,0,0),scalar(0))
         );


         volScalarField H
         (
         IOobject
         (
             "H",
             runTime.timeName(),
             mesh,
             IOobject::NO_READ,
             IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("H",dimensionSet(0,2,-2,0,0,0,0),scalar(0))
         );
  
     
         surfaceScalarField enFlux
         (
         IOobject
         (
             "enFlux",
             runTime.timeName(),
             mesh,
             IOobject::NO_READ,
             IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("enFlux",dimensionSet(1,2,-3,0,0,0,0),scalar(0))
         );
         surfaceScalarField enVisFlux
         (
         IOobject
         (
             "enVisFlux",
             runTime.timeName(),
             mesh,
             IOobject::NO_READ,
             IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("enVisFlux",dimensionSet(1,2,-3,0,0,0,0),scalar(0))
         );

         volScalarField zero
         (
         IOobject
         (
         "zero",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("zero",dimless,scalar(0))
         );
         volScalarField ones
         (
         IOobject
         (
         "ones",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedScalar("ones",dimless,scalar(1))
         );
         volVectorField ones_vec
         (
         IOobject
         (
         "ones_vec",
         runTime.timeName(),
         mesh,
         IOobject::NO_READ,
         IOobject::NO_WRITE
         ),
         mesh,
         dimensionedVector("ones_vec",dimless,vector(1,0,0))
         );
         dimensionedScalar rhob_prt
         (
          "rhob_prt",
          dimensionSet(0,0,0,0,0,0,0),
          scalar(0.)
         );
         dimensionedScalar dpdx_prt
         (
         "dpdx_prt",
         dimensionSet(1,-2,-2,0,0,0,0),
         scalar(0.)
         ); 
         dimensionedScalar drhoUx_prt
         (
          "drhoUx_prt",
          dimensionSet(0,0,0,0,0,0,0),
          scalar(0.)
         ); 
        dimensionedScalar Tbulk_prt
         (
          "Tbulk_prt",
          dimensionSet(0,0,0,0,0,0,0),
          scalar(0.)
         ); 

