#include "memory.h"
#include "log.h"
#include "game/gameplay/gameplay_log.h"
#include <fstream>
#include <typeinfo>
#include "game/pieces/king.h"
#include "game/pieces/queen.h"
#include "game/pieces/bishop.h"
#include "game/pieces/knight.h"
#include "game/pieces/rook.h"
#include "game/pieces/pawn.h"

extern Logger logger;
extern Logger gameplayLogger;

// Helper function to determine piece notation based on type
std::string getPieceNotation(const Piece* piece) {
    if (dynamic_cast<const Pawn*>(piece)) return "";
    if (dynamic_cast<const Knight*>(piece)) return "N";
    if (dynamic_cast<const Bishop*>(piece)) return "B";
    if (dynamic_cast<const Rook*>(piece)) return "R";
    if (dynamic_cast<const Queen*>(piece)) return "Q";
    if (dynamic_cast<const King*>(piece)) return "K";
    return "";
}

void Memory::addMove(int round, int pieceUID, bool isWhiteTurn, const std::string& initialLocation, const std::string& finalLocation) {
    moveHistory.emplace_back(round, pieceUID, isWhiteTurn, initialLocation, finalLocation);

    // Find the piece by UID to get its type
    const Piece* piece = nullptr;
    for (const auto& p : pieces) {
        if (p->getUID() == pieceUID) {
            piece = p;
            break;
        }
    }

    std::string pieceNotation = getPieceNotation(piece);
    std::string moveDescription = (isWhiteTurn ? "White" : "Black") + std::string(" piece UID ") + std::to_string(pieceUID) +
                                  " moved from " + pieceNotation + initialLocation + " to " + pieceNotation + finalLocation;

    logger.log(LogLevel::INFO, "Move added to memory: " + moveDescription);
    gameplayLogger.log(LogLevel::POSITION, "Round " + std::to_string(round) + ": " + moveDescription);

    // Log the current state of the memory
    logMemoryState();
}

MemoryEntry Memory::getLastMove() const {
    if (!moveHistory.empty()) {
        MemoryEntry lastMove = moveHistory.back();
        const Piece* piece = nullptr;
        for (const auto& p : pieces) {
            if (p->getUID() == lastMove.pieceUID) {
                piece = p;
                break;
            }
        }
        std::string pieceNotation = getPieceNotation(piece);
        std::string moveDescription = (lastMove.isWhiteTurn ? "White" : "Black") + std::string(" piece UID ") + std::to_string(lastMove.pieceUID) +
                                      " moved from " + pieceNotation + lastMove.initialLocation + " to " + pieceNotation + lastMove.finalLocation;

        logger.log(LogLevel::DEBUG, "Retrieved last move from memory: " + moveDescription);
        return lastMove;
    }

    logger.log(LogLevel::WARNING, "No moves in memory to retrieve.");
    return MemoryEntry(-1, -1, false, "", "");
}

int Memory::getLastPieceMoved() const {
    if (!moveHistory.empty()) {
        int lastPieceUID = moveHistory.back().pieceUID;

        logger.log(LogLevel::DEBUG, "Last piece moved UID: " + std::to_string(lastPieceUID));
        return lastPieceUID;
    }

    logger.log(LogLevel::WARNING, "No moves in memory to retrieve the last piece UID.");
    return -1;
}

void Memory::removeLastMove() {
    if (!moveHistory.empty()) {
        MemoryEntry lastMove = moveHistory.back();
        const Piece* piece = nullptr;
        for (const auto& p : pieces) {
            if (p->getUID() == lastMove.pieceUID) {
                piece = p;
                break;
            }
        }
        std::string pieceNotation = getPieceNotation(piece);
        std::string moveDescription = (lastMove.isWhiteTurn ? "White" : "Black") + std::string(" piece UID ") + std::to_string(lastMove.pieceUID) +
                                      " moved from " + pieceNotation + lastMove.initialLocation + " to " + pieceNotation + lastMove.finalLocation;

        logger.log(LogLevel::INFO, "Removed last move from memory: " + moveDescription);
        gameplayLogger.log(LogLevel::POSITION, "Undo move: " + moveDescription);

        moveHistory.pop_back();
        logMemoryState();
    } else {
        logger.log(LogLevel::WARNING, "No moves in memory to remove.");
    }
}

std::vector<MemoryEntry> Memory::getMoveHistory() const {
    logger.log(LogLevel::DEBUG, "Retrieving entire move history from memory.");
    return moveHistory;
}

void Memory::clearMemory() {
    logger.log(LogLevel::INFO, "Clearing all moves from memory.");
    gameplayLogger.log(LogLevel::INFO, "Game reset: Memory cleared.");
    moveHistory.clear();
    logMemoryState();
}

void Memory::logMemoryState() const {
    std::ofstream memoryLogFile("logs/memory.log", std::ios::out | std::ios::trunc);  // Open file in truncate mode
    if (memoryLogFile.is_open()) {
        for (const auto& entry : moveHistory) {
            const Piece* piece = nullptr;
            for (const auto& p : pieces) {
                if (p->getUID() == entry.pieceUID) {
                    piece = p;
                    break;
                }
            }
            std::string pieceNotation = getPieceNotation(piece);
            memoryLogFile << "{" << entry.round << ", " << entry.pieceUID << ", " 
                          << (entry.isWhiteTurn ? "true" : "false") << ", " 
                          << pieceNotation + entry.initialLocation << ", " 
                          << pieceNotation + entry.finalLocation << "}" << std::endl;
        }
        memoryLogFile.close();
    } else {
        logger.log(LogLevel::ERROR, "Failed to open memory.log for writing.");
    }
}
