//     Add AUSM dissipation on pressure term
//     Reconstruct M_L and M_R at left and right cell states 
//     M_L = fvc::interpolate(Mach, pos, "reconstruct(M)") & (mesh.Sf()/(mesh.magSf()));
//     M_R = fvc::interpolate(Mach, neg, "reconstruct(M)") & (mesh.Sf()/(mesh.magSf()));
//     Reconstruct p_L = p_j  p_R = p_j+1
       p_L = fvc::interpolate(p, pos, "reconstruct(p)");
       p_R = fvc::interpolate(p, neg, "reconstruct(p)");
//     Reconstruct rho, U, c 
       rho_L= fvc::interpolate(rho, pos, "reconstruct(rho)") ;
       rho_R= fvc::interpolate(rho, neg, "reconstruct(rho)") ;
       U_L  = fvc::interpolate(U, pos, "reconstruct(U)")& (mesh.Sf()/(mesh.magSf())) ;
       U_R  = fvc::interpolate(U, neg, "reconstruct(U)")& (mesh.Sf()/(mesh.magSf())) ;
//     c_L  = fvc::interpolate(c, pos, "reconstruct(T)") ;
//     c_R  = fvc::interpolate(c, neg, "reconstruct(T)") ;
//     surfaceScalarField cave = fvc::interpolate(c) ;
       const labelUList& own = mesh.owner();
       surfaceScalarField duc = fvc::interpolate(ducSensor) ;
       volScalarField gamma = thermo.Cp()/thermo.Cv();
       surfaceScalarField gamm = fvc::interpolate(gamma);
       volScalarField cts = Foam::sqrt(2.*(gamma-1.)/(gamma+1.)*H);
       surfaceScalarField css = fvc::interpolate(cts);
       surfaceScalarField cs_R=css*css/max(css,-U_R) ;
       surfaceScalarField cs_L=css*css/max(css, U_L) ;
       c12=fvc::interpolate(c);
//     c12=Foam::sqrt(c_L*c_R);//min(cs_L,cs_R) ;
//     c12=min(cs_L,cs_R) ;
       M_L  = U_L/c12;
       M_R  = U_R/c12;
       m2= (U_L*U_L+U_R*U_R)/(2.*c12*c12) ;
       m0= Foam::sqrt( min( pos, max(m2,minfty) ) );       
//     Loop on all cells
       forAll(own,iface)
       {
        if(duc[iface] > ducLevelPress)
        {
         //  Left and Right state
         scalar pl = p_L[iface] ;
         scalar pr = p_R[iface] ;
         scalar ml = M_L[iface] ;
         scalar mr = M_R[iface] ;
         scalar ul = U_L[iface] ;
         scalar ur = U_R[iface] ;
         scalar dl = rho_L[iface] ;
         scalar dr = rho_R[iface] ;
//
         scalar fa = m0[iface]*(2.-m0[iface]);
         scalar alpha = 3./16.*(-4.+5.*fa*fa); 
//
         scalar p5p = p5 (ml , 1 , alpha) ;
         scalar p5m = p5 (mr ,-1 , alpha) ;
//
         scalar dpr = p5 (mr , 1 , alpha) - p5m ;
         scalar dpl = p5p  - p5(ml, -1, alpha)  ;
//       
         scalar pu = -ku*p5p*p5m*(dl + dr)*c12[iface]*fa*(ur-ul) ;
//
         scalar dp12 = pr*dpr - pl*dpl ; 
// 
         //Update p
         pave[iface] += duc[iface]*(- 0.5*(dp12) + pu)  ; // Pressure dissipation proportional to Ducros sensor
        }
       }
//
//
//     Add artificial dissipation on the processor boundaries
       forAll( mesh.boundaryMesh(), iPatch )
       {
        const polyPatch& patch = mesh.boundaryMesh()[iPatch] ;
        if ((patch.type()=="processor"))
        {
         forAll( patch , iface )
         {
          if(duc.boundaryField()[iPatch][iface] > ducLevelPress )
          {
           //  Left and Right state
           scalar pl = p_L.boundaryField()[iPatch][iface] ;
           scalar pr = p_R.boundaryField()[iPatch][iface] ;
           scalar ml = M_L.boundaryField()[iPatch][iface] ;
           scalar mr = M_R.boundaryField()[iPatch][iface] ;
           scalar ul = U_L.boundaryField()[iPatch][iface] ;
           scalar ur = U_R.boundaryField()[iPatch][iface] ;
           scalar dl = rho_L.boundaryField()[iPatch][iface] ;
           scalar dr = rho_R.boundaryField()[iPatch][iface] ;
//
           scalar fa = m0.boundaryField()[iPatch][iface]*(2.-m0.boundaryField()[iPatch][iface]);
           scalar alpha = 3./16.*(-4.+5.*fa*fa); 
// 
           scalar p5p = p5 (ml , 1 , alpha) ;
           scalar p5m = p5 (mr ,-1 , alpha) ;
//
           scalar dpr = p5 (mr , 1 , alpha) - p5m ;
           scalar dpl = p5p  - p5(ml, -1, alpha)  ;
//       
           scalar pu = -ku*p5p*p5m*(dl + dr)*c12.boundaryField()[iPatch][iface]*fa*(ur-ul) ;
//
           scalar dp12 = pr*dpr - pl*dpl ; 
 
           //Update p
           pave.boundaryFieldRef()[iPatch][iface] +=   duc.boundaryField()[iPatch][iface]*(- 0.5*(dp12) + pu)  ;
          }
         }
        }
       }
