
CMP = g++
CLASS = racecar
MAIN = project
EXEC = play_racecar

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) $(CLASS).o $(MAIN).o gfx.o -lX11 -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp gfx.o -lX11 -o $(CLASS).o

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -lX11 -std=c++11 -o $(MAIN).o

clean:
	rm $(MAIN).o
	rm $(CLASS).o
	rm $(EXEC)

