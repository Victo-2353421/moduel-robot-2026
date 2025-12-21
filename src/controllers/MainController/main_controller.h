#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "../BaseController/base_controller.h"
#include "../PiquetController/piquet_controller.h"
#include "../PinceController/pince_controller.h"
#include "../PropulseurController/propulseur_controller.h"

class PiquetController;
class PinceController;
class PropulseurController;

/**
 * Interface to allow certain functions for the PinceController to call
 */
class IPinceHandler
{
public:
    virtual void onPinceReachedReloading() = 0;
    virtual void onPinceDroppedGamePieces() = 0;
};

/**
 * Interface to allow certain functions for the PiquetController to call
 */
class IPiquetHandler
{
public:
    virtual void onPiquetReachedIdle() = 0;
    virtual void onPiquetReachedReloading() = 0;
};

class MainController : public BaseController, public IPiquetHandler, public IPinceHandler
{
public:
    void initialize(BaseController *controller = nullptr) override;
    void update() override;

    void onPiquetReachedIdle() override;
    void onPiquetReachedReloading() override;
    void onPinceReachedReloading() override;
    void onPinceDroppedGamePieces() override;
private:
    PiquetController *_piquetController = nullptr;
    PinceController *_pinceController = nullptr;
    PropulseurController *_propulseurController = nullptr;
    bool _startedReloadingSequence = false;

    /**
     * Handles the robot movement
     */
    void handleMove();

    /**
     * Test function to manually start the reloading sequence
     */
    void checkForStartReloadingSequence();

    /**
     * Starts the reloading sequence
     */
    void startReloadingSequence();

    /**
     * Checks if the pince and piquet have reached their reloading position to go back to idle
     */
    void checkForReturnToIdle();
};

#endif
