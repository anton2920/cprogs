echo -e "mpiexec -f ./machinefile -n 3 ./main $1\n\n"
mpiexec -f ./machinefile -n 3 ./main $1
