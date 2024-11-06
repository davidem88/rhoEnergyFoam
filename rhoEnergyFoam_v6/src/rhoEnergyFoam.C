////  =========                 |
//  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
//   \\    /   O peration     |
//    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
//     \\/     M anipulation  |
//-------------------------------------------------------------------------------
//License
//    This file is part of OpenFOAM.
//
//    OpenFOAM is free software: you can redistribute it and/or modify it
//    under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
//    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
//    for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.
//
//Application
//    rhoEnergyFoam 
//
//Description
//    Numerical solver for the solution of compressible shock-free flows.
//    The convective terms are discretized using Pirozzoli's scheme(JCP 2010),
//    density based splitting. The scheme allows conservation of the kinetic
//    energy in the inviscid incompressible limit.
//    midPoint interpolation must be selected in fvScheme dictionary. 
//    Viscous terms(Laplacians only) are evaluated directly, computing
//    the face normal gradients.
//    A third-order low-storage RK scheme is used for time integration.
//    The OpenFOAM labrary for turbulence models is included.
//      
//    Author: Davide Modesti (davide.modesti@uniroma1.it)
//    Last update 06/04/2017
//    Reference
//    D. Modesti and S. Pirozzoli A high-fidelity solver for turbulent compressible flows on unstructured meshes. Comput. & Fluids (2017)
//\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "psiThermo.H"
#include "turbulentFluidThermoModel.H"
#include "fixedRhoFvPatchScalarField.H"
//#include "directionInterpolate.H"
#include "localEulerDdtScheme.H"
#include "fvcSmooth.H"
//#include "Interpolation_IBM.C"

#include <fstream>      // std::ofstream
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
// AUSM useful functions
  float m1 (float rm,float sgn ) // Return M_1
   {
   float r ; 
   r = 0.5*(rm + sgn*mag(rm)) ;
   return r ; 
   }
///
  float m2 (float rm,float sgn ) // Return M_2
   {
   float r ; 
   r = sgn*0.25*(rm + sgn)*(rm + sgn) ;
   return r ; 
   }
///
  float p5 (float rm,float sgn ,float alpha) // Return p_5
   {
   float r ; 
   if (abs(rm)<1.)
   {
    r = m2(rm,sgn)*( (sgn*2-rm) - sgn*16*alpha*rm*m2(rm,-sgn) ) ;
   }
   else
   {
    r = 1./rm*m1(rm,sgn) ;
   }
   return r ; 
   }
///
  float m4 (float rm,float sgn ,float beta) // Return M_4
   {
   float r ; 
   if (abs(rm)<1)
   {
    r = m2(rm,sgn)*( 1 - sgn*16*beta*m2(rm,-sgn) ) ;
   }
   else
   {
    r = m1(rm,sgn) ;
   }
   return r ; 
   }
// Main
int main(int argc, char *argv[])
{
    #define NO_CONTROL
    #include "postProcess.H"

//  #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"
    #include "createFieldRefs.H"
    #include "createTimeControls.H"

    #include "readThermophysicalProperties.H"
    #include "variables.H"
//  #include "Set_Immersed_Boundary.H"


    //  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    turbulence->validate();

    Info<< nl << "Starting time loop" << endl;
    Info<< "Start Timing = " << runTime.clockTimeIncrement() << " s"
        << nl << endl;

//  while (runTime.loop()) //Start time loop
    while (runTime.run()) //Start time loop
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;
        runTime++;



//     Saving quantities at preavious time step
       rhoOld  = rho; 
       rhoUOld = rhoU; 
       rhoEOld = rhoE; 
//     RK Time step
       for (int cycle =0; cycle < rkCoeff.size(); cycle++)
       {
//     Speed of sound and Mach number
        c = Foam::sqrt(thermo.Cp()/thermo.Cv()/psi);
        Mach = U/c ;
//      Interpolated quantities at cell faces     
        surfaceScalarField rhoave = fvc:: interpolate(rho) ;
        surfaceVectorField Uave   = fvc:: interpolate(U)   ;
//      Flux at the intercell
        phi    = fvc:: interpolate(U)    & mesh.Sf() ;
        phit   = fvc:: interpolate(rhoU) & mesh.Sf() ; //flux in turbulent model
//      Enthalpy
        H    = (rhoE + p)/rho ;
//      Enthalpy at the intercell
        surfaceScalarField Have = fvc:: interpolate(H) ;
//      Pressure at the intercell
        surfaceScalarField pave = fvc::interpolate(p)  ;    
 
        #include "sensor.H" //Ducros sensor 
        if(pressArtDiff)
        {
         #include "AUSM.H"    // AUSM+up dissipation on pressure term, add dissipation on pave
        }
//
//      Evaluate viscous terms
//
//      Divergence of the velocity        
        vecDivU.component(0) = fvc::interpolate(fvc::div(U));
        vecDivU.component(1) = fvc::interpolate(fvc::div(U));
        vecDivU.component(2) = fvc::interpolate(fvc::div(U));
//
// 
        volScalarField muEff(turbulence->muEff());
        volTensorField tauMC("tauMC", muEff*dev2(Foam::T(fvc::grad(U))));
        surfaceScalarField  muave  = fvc::interpolate(muEff);//mu at cell faces
//
        volScalarField k("k", thermo.Cp()*muEff/Pr);//thermal diffusivity
//
        surfaceScalarField kave=fvc::interpolate(k);//k at cell faces. alphaEff=muEff/Prt
        //momentum viscous flux
        surfaceVectorField momVisFlux = muave*(fvc::snGrad(U)*mesh.magSf());//-  2./3.*vecDivU*mesh.magSf()) ;
        //energy viscous flux
        surfaceScalarField heatFlux =  kave*fvc::snGrad(T)*mesh.magSf();
        surfaceScalarField visWork  =  (momVisFlux + fvc::dotInterpolate(mesh.Sf(), tauMC) ) & Uave;
        enVisFlux = heatFlux + visWork ;
//
        // Total fluxes, Eulerian + viscous 
        surfaceScalarField rhoFlux   = rhoave*phi                                     ;
        momFlux                      = rhoave*Uave*phi + pave*mesh.Sf() - momVisFlux  ;
        enFlux                       = rhoave*Have*phi - enVisFlux        ;
//
        if(convArtDiff)
        {
         #include "AUSM_conv.H"    // AUSM+up dissipation on convective terms, add dissipation on rhoFlux,momFlux,enFlux
        }
//
// 
        
        volScalarField rhoFl = fvc::div(rhoFlux);
        volVectorField momFl = fvc::div(momFlux) - fvc::div(tauMC);
        volScalarField enFl  = fvc::div(enFlux)  ;

        if (channelCase){
         #include "pressureGrad.H" // forcing term to keep a constant mass flow rate in channel flow
        }
        // RK sub-step
        rho  = rhoOld + rkCoeff[cycle]*runTime.deltaT()*(
                - rhoFl);         
//
        rhoU = rhoUOld + rkCoeff[cycle]*runTime.deltaT()*(
                - momFl + dpdx_add*ones_vec);
//
        volScalarField work = U & ones_vec ;
        rhoE = rhoEOld + rkCoeff[cycle]*runTime.deltaT()*(
                -enFl + dpdx_add*work );

        //Update primitive variables and boundary conditions
        U.ref() = rhoU() / rho();
        U.correctBoundaryConditions();
	/*Edited*/
        rhoU.boundaryFieldRef()         = rho.boundaryField()*U.boundaryField();

        e = rhoE/rho - 0.5*magSqr(U);
        e.correctBoundaryConditions();
        //Thermodinamic library
        thermo.correct();
        /*Edited*/
        rhoE.boundaryFieldRef() =
            rho.boundaryField()*
            (
                e.boundaryField() + 0.5*magSqr(U.boundaryField())
            );
//
        p.ref() = rho() / psi();
        p.correctBoundaryConditions();
	/*Edited*/        
	rho.boundaryFieldRef() = psi.boundaryField()*p.boundaryField(); //psi=1/(R*T)

 	if (Tbulk_target>0.&& channelCase) {
         #include "tbforce.H"
        }


       }//end of RK time integration
       turbulence->correct(); //turbulence model
       runTime.write();
//
        #include "diagnostics.H" //print tke on diagnostics.dat
        #include "step.H"        //Evaluate Courant Number
        #include "setDeltaT.H"   //Andjust time step
//
// 
    }
        runTime.write();
    Info<< "Start Timing = " << runTime.clockTimeIncrement() << " s"
        << nl << endl;

    Info<< "End\n" << endl;

    return 0;
}
// ************************************************************************* //
