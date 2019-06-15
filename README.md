# ComputerNetwork
Multithreading TCP/IP Server Repository
*****************************************MADE BY THE GOST LAB ****************************************************************************
--> This code belongs to Sammuel Ramos da Silva and contributors.
--> This code are a raw example for computer network with TCP/IP or UDP.
--> In this code the search occur in a text file, where the program (boyer moore) search some words in the file.
--> The UDP code have a minor bug. After send all the words for the search mechanism, if the package send by the 
    -- server is lost the client code does not close, because, exists in execution, some threads that lost his packages.
    -- If that occurr, you can close the client code: ctrl + z
--> To compile the code, in folder open the terminal and do:
    -- g++ -std=c++11 *.cpp -o  main -lpthread
    -- ./main

*****************************************MADE BY THE GOST LAB ****************************************************************************
******************************************************************************************************************************************
