```
!=============================================================
!
██████╗ ██╗  ██╗ ██████╗ ███████╗███╗   ██╗███████╗██████╗  ██████╗██╗   ██╗███████╗ ██████╗  █████╗ ███╗   ███╗    
██╔══██╗██║  ██║██╔═══██╗██╔════╝████╗  ██║██╔════╝██╔══██╗██╔════╝╚██╗ ██╔╝██╔════╝██╔═══██╗██╔══██╗████╗ ████║    
██████╔╝███████║██║   ██║█████╗  ██╔██╗ ██║█████╗  ██████╔╝██║  ███╗╚████╔╝ █████╗  ██║   ██║███████║██╔████╔██║    
██╔══██╗██╔══██║██║   ██║██╔══╝  ██║╚██╗██║██╔══╝  ██╔══██╗██║   ██║ ╚██╔╝  ██╔══╝  ██║   ██║██╔══██║██║╚██╔╝██║    
██║  ██║██║  ██║╚██████╔╝███████╗██║ ╚████║███████╗██║  ██║╚██████╔╝  ██║   ██║     ╚██████╔╝██║  ██║██║ ╚═╝ ██║    
╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝ ╚═════╝   ╚═╝   ╚═╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝    
!
! Compressible low-dissipative solver in OpenFOAM 
!
! D. Modesti, S. Pirozzoli, A low-dissipative solver for turbulent compressible flows on unstructured meshes,
! with OpenFOAM implementation, Comput. & Fluids 152 (2017) 14–23.
!
!=============================================================
```
`rhoEnergyFoam` is a compressible flow solver developed in the OpenFOAM library. The solver is based on a hybrid numerical scheme, in which an energy-conserving numerical flux is coupled with AUSM+up dissipative fluxes to enhance numerical stability and allow shock-capturing capabilities. A detailed description of the method can be found in the reference publication.                                                                                                                    

The solver is available for OF v2.1.1, v2.3.x, and v6. Follow readme.pdf for compiling and using the code.

How to cite the reference publication:
```
@article{modesti_17,
  title={A low-dissipative solver for turbulent compressible flows on unstructured meshes, with {O}pen{FOAM} implementation},
  author={D. Modesti and S. Pirozzoli},
  journal={Comput. \& Fluids},
  volume={152},
  pages={14--23},
  year={2017},
  publisher={Elsevier}
}
```
