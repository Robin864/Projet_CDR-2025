#include "Strategy.h"

#include "strat-0.h"

Strategy::Strategy() {}

/**
 * @brief Converts coordinates based on the team's perspective.
 *
 * Adjusts the given coordinates (_x, _y) to reflect the perspective of the team.
 * The y-coordinate is adjusted based on the team factor, which depends on whether
 * the team is yellow or not.
 *
 * @param _x The x-coordinate to be converted.
 * @param _y The y-coordinate to be converted.
 *
 * @return A string representing the converted coordinates in the format "(x, y)".
 *
 * @note The board width is assumed to be 2000 units. The y-coordinate is adjusted
 *       based on the team's perspective to ensure consistency in the coordinate system.
 */
String Strategy::teamCoord(int _x, int _y)
{
    int teamFactor = (team == 'y' ? 0 : 1), boardWidth = 2000;
    
    int newY = abs((boardWidth * teamFactor) - _y);
    return (String) "(" + _x + "," + newY + ")";
}

/**
 * @brief Sets up the strategy.
 *
 * Initializes the strategy by setting up the movement component.
 * This method should be called to prepare the strategy for use.
 *
 * @note This method calls the `setup` method of the `Movement` class to initialize movement-related configurations.
 *
 * @see Movement::setup()
 */
void Strategy::setup()
{
    movement.setup();
}

/**
 * @brief Selects the team based on the state of the TEAM_PIN.
 *
 * Determines the team by reading the digital state of the TEAM_PIN.
 * Sets the team to 'b' if the pin is LOW, and 'y' if the pin is HIGH.
 * Logs an error if the pin state is invalid.
 *
 * @note This method is typically called by an interrupt to dynamically select the team.
 */
void Strategy::selectTeam()
{
    if (digitalRead(TEAM_PIN) == LOW)
        team = 'b';
    else if (digitalRead(TEAM_PIN) == HIGH)
        team = 'y';
    else
        ERROR("unable to select team");
}

/**
 * @brief Initializes the strategy and sets up the robot in its starting zone.
 *
 * Automatically prepares the strategy by positioning the robot in its designated starting area.
 * This method should be called to ensure the robot is ready for operation from its starting position.
 *
 * @see Movement::init()
 */
void Strategy::init()
{
    movement.init();
}

/**
 * @brief Executes a specific action based on its type.
 *
 * Takes an action as input and performs the corresponding operation based on the action's type.
 * The action types include movements, rotations, and interactions with objects like planks and pots.
 *
 * @param action The action to be executed, containing type and parameters.
 *
 * @note The method uses a switch statement to determine the action type and execute the appropriate
 *       movement or interaction. If the action type is unrecognized, an error is logged.
 */
void Strategy::execAction(Action action)
{
    switch (action.type)
    {
        case gotoAbsolute:
            movement.moveTo(Point2D(action.param1, action.param2));
            break;
        case gotoRelative:
            movement.moveBy(Point2D(action.param1, action.param2));
            break;
        case rotateAbsolute:
            movement.rotateTo(action.param1);
            break;
        case rotateLeft:
            movement.rotateLeftBy(action.param1);
        case rotateRight:
            movement.rotateRightBy(action.param1);
            break;
        case grabPlank:
            Serial.println("Grabing plank...");
            break;
        case ungrabPlank:
            Serial.println("Ungrabing plank...");
            break;
        case grabPot:
            Serial.println("Grabing pot...");
            break;
        case ungrabPot:
            Serial.println("Ungrabing pot...");
            break;
        default:
            ERROR("wrong action type");
            break;
    }
}

/**
 * @brief Executes the game strategy.
 *
 * Iterates through a list of actions and executes each one using the `execAction` method.
 * After all actions are executed, calls the `fullstop` method to halt the robot's operations.
 *
 * @note This method orchestrates the sequence of actions that define the robot's strategy during the game.
 */
void Strategy::game()
{
    for (const auto& action : actions)
    {
        execAction(action);
    }

    fullstop();
}

/**
 * @brief Stops all movements of the robot.
 *
 * Calls the `fullstop` method of the `Movement` class to halt all movements immediately.
 * This method is used to ensure the robot comes to a complete stop.
 *
 * @see Movement::fullstop()
 */
void Strategy::fullstop()
{
    movement.fullstop();
}