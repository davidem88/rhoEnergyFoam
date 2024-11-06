     double tke = 0. ;
     double vol = 0. ;
     forAll (U,icell) {
     scalar uu = U[icell].component(0);
     scalar vv = U[icell].component(1);
     scalar ww = U[icell].component(2);
     tke += 0.5*mesh.V()[icell]*(uu*uu+vv*vv+ww*ww) ;
     vol += mesh.V()[icell];
     }
     tke = tke/vol;
//
     if (Pstream::master())//master process
     {
       std::ofstream diagn;
       diagn.open ("diagnostics.dat", std::ofstream::out | std::ofstream::app);
       diagn <<  runTime.timeName() << " " <<  tke  << " " << dpdx_prt.value() << " " << drhoUx_prt.value() <<" "<<Tbulk_prt.value()<<" "<<rhob_prt.value() <<std::endl;
       diagn.close();
}
