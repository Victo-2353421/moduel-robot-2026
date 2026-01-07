#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H

#include "controllers/BaseController/base_controller.h"
#include "controllers/PiquetController/piquet_controller.h"
#include "controllers/PinceController/pince_controller.h"
#include "controllers/PropulseurController/propulseur_controller.h"

class PiquetController;
class PinceController;
class PropulseurController;


class MainController : public BaseController
{
public:
    void initialize(BaseController *controller = nullptr) override;
    void update() override;

    void onPiquetReachedIdle();
    void onPiquetReachedReloading();
    void onPinceReachedReloading();
    void onPinceDroppedGamePieces();
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
