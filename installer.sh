wget https://github.com/rishalab/CPPJoules/releases/download/v1.0/CPP_Joules_linux.tar.gz
tar -xvzf CPP_Joules_linux.tar.gz 
rm CPP_Joules_linux.tar.gz
sudo cp cppJoules/include/* /usr/include
sudo cp cppJoules/libCPP_Joules.so /usr/lib