//     Add AUSM dissipation on the convective terms
//     Reconstruct M_L = M_j  M_R = M_j+1
       volScalarField rhoH = rho*H ;
//
       const labelUList& own = mesh.owner();
       surfaceScalarField duc = fvc::interpolate(ducSensor) ;
//
//     Reconstruct M_L = M_j  M_R = M_j+1
//
       surfaceVectorField rhoU_R=fvc::interpolate(rhoU,   neg, "reconstruct(U)") ;
       surfaceVectorField rhoU_L=fvc::interpolate(rhoU,   pos, "reconstruct(U)") ;
       surfaceScalarField rhoH_L=fvc::interpolate(rhoH, pos, "reconstruct(T)") ;
       surfaceScalarField rhoH_R=fvc::interpolate(rhoH, neg, "reconstruct(T)") ;
//
       scalar beta = 1./8. ;
       M_L  = U_L/c12;
       M_R  = U_R/c12;
//
       forAll(own,iface)
       {
        if(duc[iface] > ducLevelConv)
        {
         scalar ml = M_L[iface] ;
         scalar mr = M_R[iface] ;
         scalar pl = p_L[iface] ;
         scalar pr = p_R[iface] ;

         scalar fa = m0[iface]*(2.-m0[iface]);

         scalar dml = m4(ml,1.,beta) - m4(ml,-1.,beta) ;
         scalar dmr = m4(mr,1.,beta) - m4(mr,-1.,beta) ;
         scalar dp = -kp/fa*max(1-sigma*m2[iface],0)*(pr-pl)/(rhoave[iface]*c12[iface]*c12[iface]);
//         
         scalar dm12  = dmr - dml - 2.*dp;
         scalar m12   = 0.5*(ml + mr)  - 0.5*dm12 ;
//
         scalar dw1 = (0.5*dm12 -mag(m12))*rho_L[iface] + (0.5*dm12 + mag(m12))*rho_R[iface];
         scalar dw2 = (0.5*dm12 -mag(m12))*rhoU_L[iface].component(0) + (0.5*dm12 + mag(m12))*rhoU_R[iface].component(0);
         scalar dw3 = (0.5*dm12 -mag(m12))*rhoU_L[iface].component(1) + (0.5*dm12 + mag(m12))*rhoU_R[iface].component(1);
         scalar dw4 = (0.5*dm12 -mag(m12))*rhoU_L[iface].component(2) + (0.5*dm12 + mag(m12))*rhoU_R[iface].component(2);
         scalar dw5 = (0.5*dm12 -mag(m12))*rhoH_L[iface] + (0.5*dm12 + mag(m12))*rhoH_R[iface];

         //Update convective fluxes
         rhoFlux[iface] -= 0.5*c12[iface]*dw1*mesh.magSf()[iface] ;
         momFlux[iface].component(0) -= 0.5*c12[iface]*dw2*mesh.magSf()[iface]  ;
         momFlux[iface].component(1) -= 0.5*c12[iface]*dw3*mesh.magSf()[iface]  ;
         momFlux[iface].component(2) -= 0.5*c12[iface]*dw4*mesh.magSf()[iface]  ;
         enFlux[iface] -= 0.5*c12[iface]*dw5*mesh.magSf()[iface] ;
//
        }
       }
//
//     Add artificial dissipation on processor boundaries
       forAll( mesh.boundaryMesh(), iPatch )
       {
       const polyPatch& patch = mesh.boundaryMesh()[iPatch] ;
       if ((patch.type()=="processor"))
        {
         forAll( mesh.boundaryMesh()[iPatch], iface )
         {
          if(duc.boundaryField()[iPatch][iface]> ducLevelConv)
          {
           scalar ml = M_L.boundaryField()[iPatch][iface] ;
           scalar mr = M_R.boundaryField()[iPatch][iface] ;
           scalar pl = p_L.boundaryField()[iPatch][iface] ;
           scalar pr = p_R.boundaryField()[iPatch][iface] ;
//
           scalar fa = m0.boundaryField()[iPatch][iface]*(2.-m0.boundaryField()[iPatch][iface]);
//  
           scalar dml = m4(ml,1.,beta) - m4(ml,-1.,beta) ;
           scalar dmr = m4(mr,1.,beta) - m4(mr,-1.,beta) ;
           scalar dp = -kp/fa*max(1-sigma*m2.boundaryField()[iPatch][iface],0)*(pr-pl)/(rhoave.boundaryField()[iPatch][iface]*c12.boundaryField()[iPatch][iface]*c12.boundaryField()[iPatch][iface]);
//         
           scalar dm12  = dmr - dml;
           scalar m12   = 0.5*(ml + mr)  - 0.5*dm12 + dp;
//
           scalar dw1 = (0.5*dm12 -mag(m12))*rho_L.boundaryField()[iPatch][iface] + (0.5*dm12 + mag(m12))*rho_R.boundaryField()[iPatch][iface];
           scalar dw2 = (0.5*dm12 -mag(m12))*rhoU_L.boundaryField()[iPatch][iface].component(0) + (0.5*dm12 + mag(m12))*rhoU_R.boundaryField()[iPatch][iface].component(0);
           scalar dw3 = (0.5*dm12 -mag(m12))*rhoU_L.boundaryField()[iPatch][iface].component(1) + (0.5*dm12 + mag(m12))*rhoU_R.boundaryField()[iPatch][iface].component(1);
           scalar dw4 = (0.5*dm12 -mag(m12))*rhoU_L.boundaryField()[iPatch][iface].component(2) + (0.5*dm12 + mag(m12))*rhoU_R.boundaryField()[iPatch][iface].component(2);
           scalar dw5 = (0.5*dm12 -mag(m12))*rhoH_L.boundaryField()[iPatch][iface] + (0.5*dm12 + mag(m12))*rhoH_R.boundaryField()[iPatch][iface];
//
	   /*Edited*/
           rhoFlux.boundaryFieldRef()[iPatch][iface] -= 0.5*c12.boundaryField()[iPatch][iface]*dw1*mesh.magSf().boundaryField()[iPatch][iface] ;
           momFlux.boundaryFieldRef()[iPatch][iface].component(0) -= 0.5*c12.boundaryField()[iPatch][iface]*dw2*mesh.magSf().boundaryField()[iPatch][iface]  ;
           momFlux.boundaryFieldRef()[iPatch][iface].component(1) -= 0.5*c12.boundaryField()[iPatch][iface]*dw3*mesh.magSf().boundaryField()[iPatch][iface]  ;
           momFlux.boundaryFieldRef()[iPatch][iface].component(2) -= 0.5*c12.boundaryField()[iPatch][iface]*dw4*mesh.magSf().boundaryField()[iPatch][iface]  ;
           enFlux.boundaryFieldRef()[iPatch][iface] -= 0.5*c12.boundaryField()[iPatch][iface]*dw5*mesh.magSf().boundaryField()[iPatch][iface] ;
//
          }
         }
        }
       }

