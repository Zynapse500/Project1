CC = g++

CPPFILES = $(wildcard src/*.cpp)

EXE = main.exe

INCLUDES = -I ./include -I ../glfw-3.2.bin.WIN32/include -I ..\glew-2.0.0\include

LIBRARIES = -L ../glfw-3.2.bin.WIN32/lib-mingw-w64 -L ..\glew-2.0.0\lib\Release\Win32

LIBS = -lopengl32 -lglu32 -lglew32 -lglfw3 

$(EXE): $(CPPFILES)
	@echo Compiling $(CPPFILES)...
	$(CC) -o $@ $^ $(INCLUDES) $(LIBRARIES) $(LIBS)
	@echo Done!

.PHONY: $(EXE)

run: $(EXE)
	@cd ..
	@echo
	@echo Executing program...
	@echo _____________________________
	@echo
	@$^
	@echo
	@echo _____________________________
	@echo Finished!