#PBS -q cs6210
#PBS -l nodes=2:sixcore
#PBS -l walltime=00:05:00
#PBS -N MPI_D
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun --hostfile $PBS_NODEFILE -np 2 /nethome/schavan38/MPI-Barrier/Dissemination
