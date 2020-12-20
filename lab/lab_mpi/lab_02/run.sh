echo -e "mpiexec -f ./machinefile -n 2 ./main $1\n\n"
mpiexec -f ./machinefile -n 2 ./main $1
