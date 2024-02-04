cmake_minimum_required(VERSION 3.24)
project(S25195_PasswordManager)

set(CMAKE_CXX_STANDARD 23)

add_executable(S25195_PasswordManager main.cpp PasswordEntity.cpp PasswordEntity.h PasswordRepository.cpp PasswordRepository.h FileRepository.cpp FileRepository.h XORCipher.cpp XORCipher.h)
