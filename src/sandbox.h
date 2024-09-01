#ifndef SANDBOX_H
#define SANDBOX_H

// Sandbox configuration options
extern bool bypassKingCheck;
extern bool removeStalemate;
extern bool ignoreTurns;
extern bool ignorePieceMovementRestrictions;

// Function to log the sandbox configuration
extern void logSandboxConfig();

#endif // SANDBOX_H
