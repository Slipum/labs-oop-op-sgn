#include "texts.h"

#include <QStringList>

#include <algorithm>
#include <unordered_set>
#include <vector>

#include "entrypoint/entrypoint.h"

QString doorState(DoorState state) {
    switch (state) {
        case DoorState::Opening: return QStringLiteral("открываются");
        case DoorState::Open: return QStringLiteral("открыты");
        case DoorState::Closing: return QStringLiteral("закрываются");
        case DoorState::Closed: return QStringLiteral("закрыты");
    }
}

QString cabinState(CabinState state) {
    switch (state) {
        case CabinState::Stopped: return QStringLiteral("остановка");
        case CabinState::PreparingToMove: return QStringLiteral("подготовка к движению");
        case CabinState::Moving: return QStringLiteral("движение");
        case CabinState::Blocked: return QStringLiteral("заблокирована");
        case CabinState::Unblocked: return QStringLiteral("разблокирована");
    }
}

QString controllerState(ControllerState state) {
    switch (state) {
        case ControllerState::Free: return QStringLiteral("свободен");
        case ControllerState::Moving: return QStringLiteral("движение");
        case ControllerState::UpdatingTarget: return QStringLiteral("обновление цели");
        case ControllerState::ReachingTarget: return QStringLiteral("достижение цели");
    }
}

QString direction(MoveDirection directionValue) {
    switch (directionValue) {
        case MoveDirection::Idle: return QStringLiteral("простой");
        case MoveDirection::Up: return QStringLiteral("вверх");
        case MoveDirection::Down: return QStringLiteral("вниз");
    }
}

QString pendingFloors(const std::unordered_set<int> &floors) {
    if (floors.empty()) {
        return QStringLiteral("пусто");
    }
    std::vector<int> sorted(floors.begin(), floors.end());
    std::sort(sorted.begin(), sorted.end());
    QStringList parts;
    for (int floor : sorted) {
        parts << QString::number(floor);
    }
    return parts.join(QStringLiteral(", "));
}
