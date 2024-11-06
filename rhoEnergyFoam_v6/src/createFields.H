#include "createRDeltaT.H"

Info<< "Reading thermophysical properties\n" << endl;

/*
autoPtr<basicPsiThermo> pThermo
(
    basicPsiThermo::New(mesh)
);
basicPsiThermo& thermo = pThermo();

volScalarField& p = thermo.p();
volScalarField& e = thermo.e();
const volScalarField& T = thermo.T();
const volScalarField& psi = thermo.psi();
*/

autoPtr<psiThermo> pThermo
(
    psiThermo::New(mesh)
);
psiThermo& thermo = pThermo();
volScalarField& e = thermo.he();
volScalarField cv = thermo.Cv();




Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
//#include "perturbU.H"
/*
#include "rhoBoundaryTypes.H"
*/
//#include "tgv.H"
// U = - U ;
volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    thermo.rho()/*,
    rhoBoundaryTypes */
);

volVectorField rhoU
(
    IOobject
    (
        "rhoU",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    rho*U
);

volScalarField rhoE
(
    IOobject
    (
        "rhoE",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    rho*(e + 0.5*magSqr(U))
);


surfaceScalarField pos
(
    IOobject
    (
        "pos",
        runTime.timeName(),
        mesh
    ),
    mesh,
    dimensionedScalar("pos", dimless, 1.0)
);

surfaceScalarField neg
(
    IOobject
    (
        "neg",
        runTime.timeName(),
        mesh
    ),
    mesh,
    dimensionedScalar("neg", dimless, -1.0)
);

#include "readInput.H"
if (runTime.time().value() == 0.0 && channelCase)
{
    #include "init_channel.H"
}


volScalarField eps
(
    IOobject
    (
        "eps",
        runTime.timeName(),
        mesh
    ),
    mesh,
    dimensionedScalar("eps", dimensionSet(0,0,-2,0,0,0,0), epsilon)
);


dimensionedScalar dpdx_add
(
 "dpdx_add",
 dimensionSet(1,-2,-2,0,0,0,0),
 scalar(0.)
);
//
scalar dpdx_temp = 0.;
scalar drhoUx    = 0.;
scalar Tbulk     = 0.;
scalar vol       = 0.;
scalar rhob      = 0.;


/*
surfaceScalarField phi("phi", mesh.Sf() & fvc::interpolate(U));
surfaceScalarField phit("phit", mesh.Sf() & fvc::interpolate(rhoU));
*/
surfaceScalarField phi("phi", fvc::flux(U));
surfaceScalarField phit("phit", fvc::flux(rhoU));

Info<< "Creating turbulence model\n" << endl;
autoPtr<compressible::turbulenceModel> turbulence
(
    compressible::turbulenceModel::New
    (
        rho,
        U,
        phit,
        thermo
    )
);
//    #include "pressureGrad.H"
//  define RK coefficient 

scalarList rkCoeff(0) ;

rkCoeff.append(1./4.) ;
rkCoeff.append(1./3.) ;
rkCoeff.append(1./2.) ;
rkCoeff.append(1./1.) ;
