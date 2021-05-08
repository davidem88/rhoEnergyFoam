Making dependency list for source file rhoEnergyFoam.C
g++ -std=c++11 -m64 -Dlinux64 -DWM_ARCH_OPTION=64 -DWM_DP -DWM_LABEL_SIZE=64 -Wall -Wextra -Wold-style-cast -Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof -Wno-attributes -O3  -DNoRepository -ftemplate-depth-100 -IBCs/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/finiteVolume/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/transportModels/compressible/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/thermophysicalModels/basic/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/thermophysicalModels/specie/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/TurbulenceModels/turbulenceModels/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/TurbulenceModels/compressible/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/dynamicMesh/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/meshTools/lnInclude  -IlnInclude -I. -I/home/xters/OpenFOAM/OpenFOAM-6/src/OpenFOAM/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/OSspecific/POSIX/lnInclude   -fPIC -c rhoEnergyFoam.C -o /home/xters/OpenFOAM/OpenFOAM-6/platforms/linux64GccDPInt64Opt/applications/solvers/compressible/rhoEnergyFoam/rhoEnergyFoam.o
In file included from ./createFields.H:111:0,
                 from /home/xters/OpenFOAM/OpenFOAM-6/src/OpenFOAM/lnInclude/postProcess.H:135,
                 from rhoEnergyFoam.C:113:
./readInput.H: In function ‘int main(int, char**)’:
./readInput.H:1:12: warning: unused variable ‘pressArtDiff’ [-Wunused-variable]
 const bool pressArtDiff =
            ^
./readInput.H:4:12: warning: unused variable ‘convArtDiff’ [-Wunused-variable]
 const bool convArtDiff =
            ^
./readInput.H:8:8: warning: unused variable ‘sigma’ [-Wunused-variable]
 scalar sigma =
        ^
./readInput.H:11:8: warning: unused variable ‘kp’ [-Wunused-variable]
 scalar kp =
        ^
./readInput.H:14:8: warning: unused variable ‘ku’ [-Wunused-variable]
 scalar ku =
        ^
./readInput.H:17:8: warning: unused variable ‘ducLevelPress’ [-Wunused-variable]
 scalar ducLevelPress =
        ^
./readInput.H:20:8: warning: unused variable ‘ducLevelConv’ [-Wunused-variable]
 scalar ducLevelConv =
        ^
In file included from rhoEnergyFoam.C:119:0:
createFieldRefs.H:6:6: warning: variable ‘inviscid’ set but not used [-Wunused-but-set-variable]
 bool inviscid(true);
      ^
In file included from rhoEnergyFoam.C:120:0:
/home/xters/OpenFOAM/OpenFOAM-6/src/finiteVolume/lnInclude/createTimeControls.H:38:8: warning: unused variable ‘maxDeltaT’ [-Wunused-variable]
 scalar maxDeltaT =
        ^
g++ -std=c++11 -m64 -Dlinux64 -DWM_ARCH_OPTION=64 -DWM_DP -DWM_LABEL_SIZE=64 -Wall -Wextra -Wold-style-cast -Wnon-virtual-dtor -Wno-unused-parameter -Wno-invalid-offsetof -Wno-attributes -O3  -DNoRepository -ftemplate-depth-100 -IBCs/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/finiteVolume/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/transportModels/compressible/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/thermophysicalModels/basic/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/thermophysicalModels/specie/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/TurbulenceModels/turbulenceModels/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/TurbulenceModels/compressible/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/dynamicMesh/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/meshTools/lnInclude  -IlnInclude -I. -I/home/xters/OpenFOAM/OpenFOAM-6/src/OpenFOAM/lnInclude -I/home/xters/OpenFOAM/OpenFOAM-6/src/OSspecific/POSIX/lnInclude   -fPIC -Xlinker --add-needed -Xlinker --no-as-needed /home/xters/OpenFOAM/OpenFOAM-6/platforms/linux64GccDPInt64Opt/applications/solvers/compressible/rhoEnergyFoam/rhoEnergyFoam.o -L/home/xters/OpenFOAM/OpenFOAM-6/platforms/linux64GccDPInt64Opt/lib \
    -lfiniteVolume -lfvOptions -lcompressibleTransportModels -lfluidThermophysicalModels -lspecie -lrhoCentralFoam -lturbulenceModels -lcompressibleTurbulenceModels -lmeshTools -lOpenFOAM -ldl  \
     -lm -o /home/xters/OpenFOAM/OpenFOAM-6/platforms/linux64GccDPInt64Opt/bin/rhoEnergyFoam
