#/////For SFML AND C++ AND SQLite but also the c++ connector folder for mysql//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# Define the paths to the MySQL and SFML include and lib directories
SFML_INCLUDE = "C:\SFML-2.5.1_(VS_Code)\include"
SFML_LIB = "C:\SFML-2.5.1_(VS_Code)\lib"

all: compile_link

compile_link: compile_main compile_sqlite link

compile_main:
	g++ -c main.cpp -I$(SFML_INCLUDE)

compile_sqlite:
	gcc -c sqlite3.c

link:
	g++ main.o sqlite3.o -o main -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:
	rm -f main.*o sqlite3.o




#/////For SFML AND C++ AND MYSQL//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# Define the paths to the MySQL and SFML include and lib directories
#MYSQL_INCLUDE = "C:\Program Files\MySQL\MySQL Server 8.0\include"
#MYSQL_LIB = "C:\Program Files\MySQL\MySQL Server 8.0\lib"
#SFML_INCLUDE = "C:\SFML-2.5.1_(VS_Code)\include"
#SFML_LIB = "C:\SFML-2.5.1_(VS_Code)\lib"

#all: compile link

#compile:
#	g++ -c main.cpp -I$(SFML_INCLUDE) -I$(MYSQL_INCLUDE) -DSFML_STATIC

#link:
#	g++ main.o -o main -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(MYSQL_LIB) -lmysqlclient

#clean:
#	rm -f main.*o



#For SFML and C++//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#all:compile link

#compile:
#	g++ -c main.cpp -I"C:\SFML-2.5.1_(VS_Code)\include" -DSFML_STATIC

#link:
#	g++ main.o -o main -L"C:\SFML-2.5.1_(VS_Code)\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

#clan:
#	rm -f main.*o

#2nd change//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# g++ -c main.cpp -I"C:\SFML-2.5.1_(VS_Code)\include" -DSFML_STATIC

# g++ main.o -o main -L"C:\SFML-2.5.1_(VS_Code)\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows

# or

# g++ main.o -o main -L"C:\SFML-2.5.1_(VS_Code)\lib" -lsfml-graphics -lsfml-window -lsfml-system



#/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#original link:
#g++ main.o -o main -L"C:\SFML-2.5.1_(VS_Code)\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindowsclan: rm -f main.*o