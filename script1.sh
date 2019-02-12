#PBS -q cs625000
#PBS -l nodes=2:sixcore
#PBS -l walltime=00:10:00
#PBS -N MPI_D
OMPI_MCA_mpi_yield_when_idle=0
/usr/lib64/openmpi/bin/mpirun --hostfile $PBS_NODEFILE -np 2 /nethome/aindoria3/Final_OpenMp/test_combined 50 2
/usr/lib64/openmpi/bin/mpirun --hostfile $PBS_NODEFILE -np 2 /nethome/aindoria3/Final_OpenMp/test_combined 50 4
/usr/lib64/openmpi/bin/mpirun --hostfile $PBS_NODEFILE -np 2 /nethome/aindoria3/Final_OpenMp/test_combined 50 6
/usr/lib64/openmpi/bin/mpirun --hostfile $PBS_NODEFILE -np 2 /nethome/aindoria3/Final_OpenMp/test_combined 50 8
/usr/lib64/openmpi/bin/mpirun --hostfile $PBS_NODEFILE -np 2 /nethome/aindoria3/Final_OpenMp/test_combined 50 10
/usr/lib64/openmpi/bin/mpirun --hostfile $PBS_NODEFILE -np 2 /nethome/aindoria3/Final_OpenMp/test_combined 50 12
