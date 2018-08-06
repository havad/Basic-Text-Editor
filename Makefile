OBJ = main.o buffer.o printTitle.o displayText.o editMode.o commandMode.o modes.o deleteLine.o insertLine.o save.o copyPaste.o searchAndReplace.o
DEBUG = -g -O3 -Wall

exe: editor
	./editor test.txt

editor: $(OBJ)
	gcc -o $@ $^ $(DEBUG) -lncurses

main.o: main.c buffer.h commandMode.h displayText.h printTitle.h
	gcc -c $< $(DEBUG)

buffer.o: buffer.c buffer.h
	gcc -c $< $(DEBUG)

printTitle.o: printTitle.c printTitle.h
	gcc -c $< $(DEBUG)

displayText.o: displayText.c displayText.h buffer.h
	gcc -c $< $(DEBUG)

editMode.o: editMode.c editMode.h buffer.h
	gcc -c $< $(DEBUG)

commandMode.o: commandMode.c commandMode.h buffer.h editMode.h deleteLine.h modes.h save.h copyPaste.h insertLine.h searchAndReplace.h
	gcc -c $< $(DEBUG)

modes.o: modes.c modes.h
	gcc -c $< $(DEBUG)

deleteLine.o: deleteLine.c deleteLine.h buffer.h
	gcc -c $< $(DEBUG)

insertLine.o: insertLine.c insertLine.h buffer.h
	gcc -c $< $(DEBUG)

save.o: save.c save.h buffer.h
	gcc -c $< $(DEBUG)

copyPaste.o: copyPaste.c copyPaste.h buffer.h
	gcc -c $< $(DEBUG)

searchAndReplace.o: searchAndReplace.c searchAndReplace.h buffer.h displayText.h
	gcc -c $< $(DEBUG)

clean:
	rm -f editor $(OBJ)
