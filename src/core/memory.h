#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include <string>

// Structure to represent a move in the game
struct MemoryEntry {
    int round;
    int pieceUID;
    bool isWhiteTurn;
    std::string initialLocation;
    std::string finalLocation;

    MemoryEntry(int r, int uid, bool turn, const std::string& initLoc, const std::string& finalLoc)
        : round(r), pieceUID(uid), isWhiteTurn(turn), initialLocation(initLoc), finalLocation(finalLoc) {}
};

class Memory {
public:
    // Adds a move to the memory system
    void addMove(int round, int pieceUID, bool isWhiteTurn, const std::string& initialLocation, const std::string& finalLocation);

    // Returns the latest move in the memory
    MemoryEntry getLastMove() const;

    // Returns the UID of the last piece that moved
    int getLastPieceMoved() const;

    // Removes the latest move from the memory (used for undo operations)
    void removeLastMove();

    // Returns the entire move history
    std::vector<MemoryEntry> getMoveHistory() const;

    // Clears the memory (resetting the game state)
    void clearMemory();

private:
    std::vector<MemoryEntry> moveHistory;  // Vector to store all moves

    // Helper function to log the current state of the memory to a file
    void logMemoryState() const;
};

#endif // MEMORY_H
