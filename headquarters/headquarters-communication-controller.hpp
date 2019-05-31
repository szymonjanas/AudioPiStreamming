#pragma once

#include "headquarters-communication.h"
#include "communication-state.hpp"
#include <memory>

class Communication_controler : private Communication
{
    Communication_state_converter converter;

public:
    Communication_controler(std::string zmqAddress);

    Request get_request_from_client();
    void send_replay(Replay replay);

};
