#include "sandbox.h"
#include "log.h"

extern Logger logger;

// Initialize sandbox configuration options
bool bypassKingCheck = false;
bool removeStalemate = false;
bool ignoreTurns = true;
bool ignorePieceMovementRestrictions = true;

void logSandboxConfig() {
    logger.log(LogLevel::DEBUG, "Bypass King Check: " + std::string(bypassKingCheck ? "Enabled" : "Disabled"));
    logger.log(LogLevel::DEBUG, "Remove Stalemate: " + std::string(removeStalemate ? "Enabled" : "Disabled"));
    logger.log(LogLevel::DEBUG, "Ignore Turns: " + std::string(ignoreTurns ? "Enabled" : "Disabled"));
    logger.log(LogLevel::DEBUG, "Ignore Piece Movement Restrictions: " + std::string(ignorePieceMovementRestrictions ? "Enabled" : "Disabled"));
}
