#ifndef OOP5_QT_TEXTS_H
#define OOP5_QT_TEXTS_H

#include <QString>
#include <unordered_set>

#include "entrypoint/entrypoint.h"

namespace ElevatorTexts {

QString doorState(DoorState state);
QString cabinState(CabinState state);
QString controllerState(ControllerState state);
QString direction(MoveDirection direction);
QString pendingFloors(const std::unordered_set<int> &floors);

} // namespace ElevatorTexts

#endif // OOP5_QT_TEXTS_H
