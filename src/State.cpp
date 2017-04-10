#include "State.h"
#include <iostream>
State::State(StateManager& stateManager)
    :_stateManager(stateManager)
{
}

StateManager& State::getStateManager() const
{
  return _stateManager;
}
