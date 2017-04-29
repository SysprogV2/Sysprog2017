#ifndef FILE_BUFFER_H_
#define FILE_BUFFER_H_

#include <fstream>

using namespace std;

class Buffer {
public:
	/**
	 * Get the length of the file from the given file stream.
	 *
	 * @param fileStream
	 * @return
	 */
	static int getFileLength(ifstream *fileStream);

private:

    char *_file;                // File path
    int _bufferSize;        // Buffer size
    int _segments;          // Segments count

    char *_buffer;              // buffer
    int *_loadedSegments;       // loaded segments

    int _fileLength;        // length of file
    int _fileSegmentLength; // fileLength/_segments;
    int _fileCurrentPos;    // current position in file



    /**
     * Gets the symbol at the given position in the source file.
     *
     * @param position Position of the symbol in the source file
     * @return Symbol at the given position
     */
    char _getChar(int position);

    /**
     * Gets the index of the buffer element for the given source position.
     *
     * @param position Position of the symbol in the source file
     * @return Index of element in buffer array
     */
    int getBufferPosition(int position);

    /**
     * Loads the segment if not yet loaded
     *
     * @param segment segment from file to load
     * @param loadToPosition target position in the array
     */
    void loadSegment(int segment, int loadToPosition);

    /**
     * Gets the segment number for the given position.
     *
     * @param position The position
     * @return The segment number
     */
    int getSegmentNumber(int position);

public:
    /**
     * Creates a buffer.
     *
     * @param file File to buffer
     * @param size buffer size
     * @param segments Segment count.
     * @return
     */
    Buffer(char *file, int size = 500, int segments = 2);

    /**
     * @return The current position in the source file.
     */
    int getPosition();

    /**
     * @return Moves the position to the next character and returns it.
     */
    char getChar();

    /**
     * @return Moves the position to the last character and returns it.
     */
    char ungetChar();

    /**
     * Goes back and returns the symbol.
     * @param back Count of symbols to go back.
     * @return The char at the given position.
     */
    char ungetChar(int back);

    /**
     * @return True if the last character has been returned, else False.
     */
    bool isEnd();

    /**
     * @deprecated dummy method for compatibility. dont use.
     */
    void allocateBufferMemory();

    /**
     *
     * @deprecated dummy method for compatibility. dont use.
     * @param somebuffer
     */
    void load(void * somebuffer);

    /*
     * Destroys the object.
     */
    virtual ~Buffer();

    int getFileLength();
};

#endif /* FILE_BUFFER_H_ */
